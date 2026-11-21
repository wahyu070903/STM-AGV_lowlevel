/*
 * bps.c
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */


#include "bsp.h"
#include <string.h>

void bsp_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* DWT cycle counter untuk pengukuran waktu loop */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL  |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t bsp_cycles(void)
{
    return DWT->CYCCNT;
}

uint32_t bsp_cycles_to_us(uint32_t cycles)
{
    return cycles / (SystemCoreClock / 1000000UL);
}

/* ----------------------------- GPIO ----------------------------- */
void bsp_gpio_out(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState initial)
{
    GPIO_InitTypeDef g = {0};
    HAL_GPIO_WritePin(port, pin, initial);
    g.Pin   = pin;
    g.Mode  = GPIO_MODE_OUTPUT_PP;
    g.Pull  = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &g);
}

void bsp_gpio_in_pullup(GPIO_TypeDef *port, uint16_t pin)
{
    GPIO_InitTypeDef g = {0};
    g.Pin  = pin;
    g.Mode = GPIO_MODE_INPUT;
    g.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(port, &g);
}

void bsp_gpio_af(GPIO_TypeDef *port, uint16_t pin, uint32_t af, uint32_t pull)
{
    GPIO_InitTypeDef g = {0};
    g.Pin       = pin;
    g.Mode      = GPIO_MODE_AF_PP;
    g.Pull      = pull;
    g.Speed     = GPIO_SPEED_FREQ_HIGH;
    g.Alternate = af;
    HAL_GPIO_Init(port, &g);
}

/* ----------------------------- PWM ------------------------------ */
void bsp_pwm_timer_init(TIM_HandleTypeDef *h, TIM_TypeDef *tim,
                        uint32_t tim_clk_hz, uint32_t freq_hz)
{
    uint32_t ticks = tim_clk_hz / freq_hz;
    uint32_t psc   = ticks / 65536UL;            /* agar ARR muat 16-bit */
    uint32_t arr   = ticks / (psc + 1UL) - 1UL;

    memset(h, 0, sizeof(*h));
    h->Instance               = tim;
    h->Init.Prescaler         = psc;
    h->Init.CounterMode       = TIM_COUNTERMODE_UP;
    h->Init.Period            = arr;
    h->Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    h->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(h);
}

void bsp_pwm_channel_init(TIM_HandleTypeDef *h, uint32_t channel)
{
    TIM_OC_InitTypeDef oc = {0};
    oc.OCMode     = TIM_OCMODE_PWM1;
    oc.Pulse      = 0;
    oc.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(h, &oc, channel);
    HAL_TIM_PWM_Start(h, channel);
}

void bsp_pwm_set(TIM_HandleTypeDef *h, uint32_t channel, int duty255)
{
    if (duty255 < 0)   duty255 = 0;
    if (duty255 > 255) duty255 = 255;

    uint32_t arr     = __HAL_TIM_GET_AUTORELOAD(h);
    uint32_t compare = ((arr + 1UL) * (uint32_t)duty255) / 255UL;
    __HAL_TIM_SET_COMPARE(h, channel, compare);
}
