/*
 * bsp.h
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "board_config.h"
#include "stm32f4xx_hal_tim.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} PinDef_t;

void bsp_init(void);

uint32_t bsp_cycles(void);
uint32_t bsp_cycles_to_us(uint32_t cycles);

/* GPIO */
void bsp_gpio_out(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState initial);
void bsp_gpio_in_pullup(GPIO_TypeDef *port, uint16_t pin);
void bsp_gpio_af(GPIO_TypeDef *port, uint16_t pin, uint32_t af, uint32_t pull);

/* PWM */
void bsp_pwm_timer_init(TIM_HandleTypeDef *h,
                        TIM_TypeDef *tim,
                        uint32_t tim_clk_hz,
                        uint32_t freq_hz);

void bsp_pwm_channel_init(TIM_HandleTypeDef *h, uint32_t channel);
void bsp_pwm_set(TIM_HandleTypeDef *h, uint32_t channel, int duty255);

#endif
