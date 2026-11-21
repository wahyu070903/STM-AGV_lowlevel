/*
 * drivve.c
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#include "drive.h"
#include "bsp.h"
#include <string.h>

static TIM_HandleTypeDef htim_pwm;
static TIM_HandleTypeDef htim_enc;

static int32_t  enc_count  = 0;
static uint16_t last_raw   = 0;
static int32_t  last_count = 0;
static uint32_t last_time  = 0;
static float    speed_rpm  = 0.0f;


static void sync_count(void)
{
    uint16_t raw = (uint16_t)__HAL_TIM_GET_COUNTER(&htim_enc);
    int16_t  d   = (int16_t)(raw - last_raw);
    last_raw = raw;

	#if DRIVE_ENC_REVERSE
		enc_count -= d;
	#else
		enc_count += d;
	#endif
}

void drive_init(void)
{
    /* ---- Enable BTS7960 ---- */
    bsp_gpio_out(DRIVE_REN_PORT, DRIVE_REN_PIN, GPIO_PIN_SET);
    bsp_gpio_out(DRIVE_LEN_PORT, DRIVE_LEN_PIN, GPIO_PIN_SET);

    /* ---- PWM ---- */
    DRIVE_PWM_TIM_CLK_EN();
    bsp_pwm_timer_init(&htim_pwm, DRIVE_PWM_TIM, DRIVE_PWM_TIM_CLK_HZ, DRIVE_PWM_FREQ_HZ);
    bsp_pwm_channel_init(&htim_pwm, DRIVE_RPWM_CH);
    bsp_pwm_channel_init(&htim_pwm, DRIVE_LPWM_CH);
    bsp_gpio_af(DRIVE_RPWM_PORT, DRIVE_RPWM_PIN, DRIVE_RPWM_AF, GPIO_NOPULL);
    bsp_gpio_af(DRIVE_LPWM_PORT, DRIVE_LPWM_PIN, DRIVE_LPWM_AF, GPIO_NOPULL);
    drive_set_speed(0);

    /* ---- Encoder (mode quadrature hardware, x4) ---- */
    TIM_Encoder_InitTypeDef e = {0};
    DRIVE_ENC_TIM_CLK_EN();

    memset(&htim_enc, 0, sizeof(htim_enc));
    htim_enc.Instance           = DRIVE_ENC_TIM;
    htim_enc.Init.Prescaler     = 0;
    htim_enc.Init.CounterMode   = TIM_COUNTERMODE_UP;
    htim_enc.Init.Period        = 0xFFFF;
    htim_enc.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    e.EncoderMode  = TIM_ENCODERMODE_TI12;
    e.IC1Polarity  = TIM_ICPOLARITY_RISING;
    e.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    e.IC1Prescaler = TIM_ICPSC_DIV1;
    e.IC1Filter    = DRIVE_ENC_FILTER;
    e.IC2Polarity  = TIM_ICPOLARITY_RISING;
    e.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    e.IC2Prescaler = TIM_ICPSC_DIV1;
    e.IC2Filter    = DRIVE_ENC_FILTER;
    HAL_TIM_Encoder_Init(&htim_enc, &e);

    bsp_gpio_af(DRIVE_ENC_A_PORT, DRIVE_ENC_A_PIN, DRIVE_ENC_AF, GPIO_PULLUP);
    bsp_gpio_af(DRIVE_ENC_B_PORT, DRIVE_ENC_B_PIN, DRIVE_ENC_AF, GPIO_PULLUP);

    HAL_TIM_Encoder_Start(&htim_enc, TIM_CHANNEL_ALL);

    last_raw   = (uint16_t)__HAL_TIM_GET_COUNTER(&htim_enc);
    enc_count  = 0;
    last_count = 0;
    last_time  = HAL_GetTick();
}

void drive_set_speed(int speed)
{
    if (speed >  255) speed =  255;
    if (speed < -255) speed = -255;

    if (speed > 0) {
        bsp_pwm_set(&htim_pwm, DRIVE_LPWM_CH, 0);
        bsp_pwm_set(&htim_pwm, DRIVE_RPWM_CH, speed);
    } else if (speed < 0) {
        bsp_pwm_set(&htim_pwm, DRIVE_RPWM_CH, 0);
        bsp_pwm_set(&htim_pwm, DRIVE_LPWM_CH, -speed);
    } else {
        bsp_pwm_set(&htim_pwm, DRIVE_RPWM_CH, 0);
        bsp_pwm_set(&htim_pwm, DRIVE_LPWM_CH, 0);
    }
}

int32_t drive_get_count(void)
{
    sync_count();
    return enc_count;
}

void drive_measure_speed(void)
{
    uint32_t now = HAL_GetTick();

    if (now - last_time >= SPEED_INTERVAL_MS) {
        int32_t current = drive_get_count();
        int32_t delta   = current - last_count;
        float   dt      = (now - last_time) / 1000.0f;

        float counts_per_wheel_rev = (float)PPR * ENCODER_MULTIPLIER * GEAR_RATIO;

        speed_rpm = ((float)delta * 60.0f) / (counts_per_wheel_rev * dt);

        last_count = current;
        last_time  = now;
    }
}

float drive_get_speed_rpm(void)
{
    return speed_rpm;
}
