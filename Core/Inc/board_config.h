/*
 * board_config.h
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#ifndef INC_BOARD_CONFIG_H_
#define INC_BOARD_CONFIG_H_

#include "stm32f4xx_hal.h"

#define APB1_TIMER_CLK_HZ       84000000UL
#define APB2_TIMER_CLK_HZ       168000000UL

#define DRIVE_PWM_TIM           TIM8
#define DRIVE_PWM_TIM_CLK_EN()  __HAL_RCC_TIM8_CLK_ENABLE()
#define DRIVE_PWM_TIM_CLK_HZ    APB2_TIMER_CLK_HZ
#define DRIVE_PWM_FREQ_HZ       20000UL

#define DRIVE_RPWM_PORT         GPIOC
#define DRIVE_RPWM_PIN          GPIO_PIN_8
#define DRIVE_RPWM_CH           TIM_CHANNEL_3
#define DRIVE_RPWM_AF           GPIO_AF3_TIM8

#define DRIVE_LPWM_PORT         GPIOC
#define DRIVE_LPWM_PIN          GPIO_PIN_9
#define DRIVE_LPWM_CH           TIM_CHANNEL_4
#define DRIVE_LPWM_AF           GPIO_AF3_TIM8

#define DRIVE_REN_PORT          GPIOD
#define DRIVE_REN_PIN           GPIO_PIN_6
#define DRIVE_LEN_PORT          GPIOD
#define DRIVE_LEN_PIN           GPIO_PIN_7

#define DRIVE_ENC_TIM           TIM3
#define DRIVE_ENC_TIM_CLK_EN()  __HAL_RCC_TIM3_CLK_ENABLE()
#define DRIVE_ENC_A_PORT        GPIOB
#define DRIVE_ENC_A_PIN         GPIO_PIN_4
#define DRIVE_ENC_B_PORT        GPIOB
#define DRIVE_ENC_B_PIN         GPIO_PIN_5
#define DRIVE_ENC_AF            GPIO_AF2_TIM3
#define DRIVE_ENC_FILTER        6
#define DRIVE_ENC_REVERSE       0

#define GEAR_RATIO              0.076f
#define WHEEL_DIAMETER          0.48f        // meter
#define PPR                     400
#define ENCODER_MULTIPLIER      4
#define SPEED_INTERVAL_MS       20


#define STEER_PWM_TIM           TIM12
#define STEER_PWM_TIM_CLK_EN()  __HAL_RCC_TIM12_CLK_ENABLE()
#define STEER_PWM_TIM_CLK_HZ    APB1_TIMER_CLK_HZ
#define STEER_PWM_FREQ_HZ       490UL
#define STEER_VRM_PORT          GPIOB
#define STEER_VRM_PIN           GPIO_PIN_14
#define STEER_VRM_CH            TIM_CHANNEL_1
#define STEER_VRM_AF            GPIO_AF9_TIM12

#define STEER_CW_CCW_PORT       GPIOD
#define STEER_CW_CCW_PIN        GPIO_PIN_8
#define STEER_EXT_VR_PORT       GPIOD
#define STEER_EXT_VR_PIN        GPIO_PIN_9
#define STEER_ALM_RST_PORT      GPIOD
#define STEER_ALM_RST_PIN       GPIO_PIN_10

#define STEER_ENC_BITS          13
#define STEER_ENC_PIN_LIST                                   \
    { GPIOE, GPIO_PIN_2  }, { GPIOE, GPIO_PIN_4  },          \
    { GPIOE, GPIO_PIN_5  }, { GPIOE, GPIO_PIN_6  },          \
    { GPIOE, GPIO_PIN_7  }, { GPIOE, GPIO_PIN_8  },          \
    { GPIOE, GPIO_PIN_9  }, { GPIOE, GPIO_PIN_10 },          \
    { GPIOE, GPIO_PIN_11 }, { GPIOE, GPIO_PIN_12 },          \
    { GPIOE, GPIO_PIN_13 }, { GPIOE, GPIO_PIN_14 },          \
    { GPIOE, GPIO_PIN_15 }
#define STEER_ENC_ACTIVE_LOW    1

/* Parameter steering */
#define MAX_ANGULAR             0.785398f    /* 45 derajat (rad) */
#define MIN_PWM                 40
#define MAX_PWM                 255
#define CORRECTION              118.80f      /* offset encoder (derajat) */

#define STEER_PID_KP            1200.0f
#define STEER_PID_KI            0.0f
#define STEER_PID_KD            0.0f
#define STEER_PID_SAMPLE_MS     10

/* ============================ CAN ============================== */
/* bxCAN1 internal. Butuh transceiver 3.3V (mis. SN65HVD230). */
#define CAN_INSTANCE            CAN1
#define CAN_CLK_EN()            __HAL_RCC_CAN1_CLK_ENABLE()
#define CAN_RX_PORT             GPIOD
#define CAN_RX_PIN              GPIO_PIN_0
#define CAN_TX_PORT             GPIOD
#define CAN_TX_PIN              GPIO_PIN_1
#define CAN_AF                  GPIO_AF9_CAN1
/* 500 kbps @ APB1=42MHz: 42M / 6 = 7 MHz, 14 TQ -> 500k, sample point 85.7% */
#define CAN_PRESCALER           6
#define CAN_BS1                 CAN_BS1_11TQ
#define CAN_BS2                 CAN_BS2_2TQ
#define CAN_SJW                 CAN_SJW_1TQ

/* ===================== SERIAL DEBUG (USART2) =================== */
/* Sambungkan USB-Serial adapter 3.3V ke PA2 (TX) dan PA3 (RX) */
#define DEBUG_UART              USART2
#define DEBUG_UART_CLK_EN()     __HAL_RCC_USART2_CLK_ENABLE()
#define DEBUG_UART_IRQn         USART2_IRQn
#define DEBUG_UART_IRQHandler   USART2_IRQHandler
#define DEBUG_UART_TX_PORT      GPIOA
#define DEBUG_UART_TX_PIN       GPIO_PIN_2
#define DEBUG_UART_RX_PORT      GPIOA
#define DEBUG_UART_RX_PIN       GPIO_PIN_3
#define DEBUG_UART_AF           GPIO_AF7_USART2
#define DEBUG_UART_BAUD         115200

#endif /* INC_BOARD_CONFIG_H_ */
