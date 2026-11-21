/*
 * steering.c
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#include "steering.h"
#include "bsp.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef DEG_TO_RAD
#define DEG_TO_RAD 0.017453292519943295f
#endif

static const PinDef_t enc_pins[STEER_ENC_BITS] = { STEER_ENC_PIN_LIST };

static TIM_HandleTypeDef htim_steer;

/* --------------------------- PID (setara PID_v1, mode DIRECT) --------------------------- */
static float Setpoint = 0.0f;
static float Input    = 0.0f;
static float Output   = 0.0f;

static struct {
    float    kp, ki, kd;
    float    i_term;
    float    last_input;
    uint32_t last_ms;
} pid;

static void pid_init(void)
{
    const float dt = STEER_PID_SAMPLE_MS / 1000.0f;
    pid.kp = STEER_PID_KP;
    pid.ki = STEER_PID_KI * dt;
    pid.kd = STEER_PID_KD / dt;
    pid.i_term     = 0.0f;
    pid.last_input = Input;
    pid.last_ms    = HAL_GetTick();
}

static float clampf(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static void pid_compute(void)
{
    uint32_t now = HAL_GetTick();
    if (now - pid.last_ms < STEER_PID_SAMPLE_MS) return;
    pid.last_ms = now;

    float error = Setpoint - Input;
    float dIn   = Input - pid.last_input;

    pid.i_term = clampf(pid.i_term + pid.ki * error, -MAX_PWM, MAX_PWM);
    Output     = clampf(pid.kp * error + pid.i_term - pid.kd * dIn, -MAX_PWM, MAX_PWM);

    pid.last_input = Input;
}

/* ------------------------------------ Encoder ------------------------------------ */
static uint16_t read_encoder(void)
{
    uint16_t data = 0;
    for (int i = 0; i < STEER_ENC_BITS; i++) {
        GPIO_PinState s = HAL_GPIO_ReadPin(enc_pins[i].port, enc_pins[i].pin);
#if STEER_ENC_ACTIVE_LOW
        if (s == GPIO_PIN_RESET) data |= (1u << i);
#else
        if (s == GPIO_PIN_SET)   data |= (1u << i);
#endif
    }
    return data;
}

static int decode_bcd(uint16_t data)
{
    uint8_t ones      = (data >> 0)  & 0x0F;
    uint8_t tens      = (data >> 4)  & 0x0F;
    uint8_t hundreds  = (data >> 8)  & 0x0F;
    uint8_t thousands = (data >> 12) & 0x01;

    if (ones > 9 || tens > 9 || hundreds > 9 || thousands > 1) return -1;

    int value = ones + tens * 10 + hundreds * 100 + thousands * 1000;
    if (value > 1024) return -1;
    return value;
}

static float encoder_to_rad(void)
{
    int position = decode_bcd(read_encoder());
    if (position < 0) return NAN;

    float encoder_angle  = (float)position * 360.0f / 1024.0f;
    float steering_angle = encoder_angle - 180.0f;

    if (steering_angle >= 180.0f) steering_angle -= 360.0f;
    if (steering_angle < -180.0f) steering_angle += 360.0f;

    return (steering_angle - CORRECTION) * DEG_TO_RAD;
}

/* ------------------------------------ Public API ------------------------------------ */
void steering_init(void)
{
    for (int i = 0; i < STEER_ENC_BITS; i++) {
        bsp_gpio_in_pullup(enc_pins[i].port, enc_pins[i].pin);
    }

    bsp_gpio_out(STEER_CW_CCW_PORT,  STEER_CW_CCW_PIN,  GPIO_PIN_RESET);
    bsp_gpio_out(STEER_EXT_VR_PORT,  STEER_EXT_VR_PIN,  GPIO_PIN_SET);
    bsp_gpio_out(STEER_ALM_RST_PORT, STEER_ALM_RST_PIN, GPIO_PIN_RESET);

    STEER_PWM_TIM_CLK_EN();
    bsp_pwm_timer_init(&htim_steer, STEER_PWM_TIM, STEER_PWM_TIM_CLK_HZ, STEER_PWM_FREQ_HZ);
    bsp_pwm_channel_init(&htim_steer, STEER_VRM_CH);
    bsp_gpio_af(STEER_VRM_PORT, STEER_VRM_PIN, STEER_VRM_AF, GPIO_NOPULL);
    bsp_pwm_set(&htim_steer, STEER_VRM_CH, 0);

    pid_init();
}

void steering_test_enc_input(char *out, uint16_t out_size)
{
    int n = snprintf(out, out_size, "ENC:");
    for (int i = 0; i < STEER_ENC_BITS && n < (int)out_size - 3; i++) {
        n += snprintf(out + n, out_size - n, " %d",
                      HAL_GPIO_ReadPin(enc_pins[i].port, enc_pins[i].pin) == GPIO_PIN_SET);
    }
}

float steering_read_angle(void)
{
    return encoder_to_rad();
}

void steering_change_dir(int dir)
{
    HAL_GPIO_WritePin(STEER_CW_CCW_PORT, STEER_CW_CCW_PIN,
                      dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void steering_set_degree(float rad)
{
    Setpoint = clampf(rad, -MAX_ANGULAR, MAX_ANGULAR);
}

void steering_update(void)
{
    float angle = encoder_to_rad();
    if (isnan(angle)) {
        bsp_pwm_set(&htim_steer, STEER_VRM_CH, 0);
        return;
    }

    Input = angle;
    pid_compute();

    if (fabsf(Output) < MIN_PWM) {
        bsp_pwm_set(&htim_steer, STEER_VRM_CH, 0);
        return;
    }

    steering_change_dir(Output > 0);

    int pwm = (int)fabsf(Output);
    if (pwm > MAX_PWM) pwm = MAX_PWM;
    if (pwm > 0 && pwm < MIN_PWM) pwm = MIN_PWM;

    bsp_pwm_set(&htim_steer, STEER_VRM_CH, pwm);
}
