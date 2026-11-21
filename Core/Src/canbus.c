/*
 * canbus.c
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#include "canbus.h"
#include "bsp.h"
#include <string.h>

uint32_t can_tx_errors = 0;

static CAN_HandleTypeDef hcan;

bool can_init(void)
{
    CAN_FilterTypeDef f = {0};

    CAN_CLK_EN();

    memset(&hcan, 0, sizeof(hcan));
    hcan.Instance                  = CAN_INSTANCE;
    hcan.Init.Prescaler            = CAN_PRESCALER;
    hcan.Init.Mode                 = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth        = CAN_SJW;
    hcan.Init.TimeSeg1             = CAN_BS1;
    hcan.Init.TimeSeg2             = CAN_BS2;
    hcan.Init.TimeTriggeredMode    = DISABLE;
    hcan.Init.AutoBusOff           = ENABLE;
    hcan.Init.AutoWakeUp           = DISABLE;
    hcan.Init.AutoRetransmission   = ENABLE;
    hcan.Init.ReceiveFifoLocked    = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;

    if (HAL_CAN_Init(&hcan) != HAL_OK) return false;

    /* Pin diset setelah HAL init agar menimpa MspInit CubeMX */
    bsp_gpio_af(CAN_RX_PORT, CAN_RX_PIN, CAN_AF, GPIO_PULLUP);
    bsp_gpio_af(CAN_TX_PORT, CAN_TX_PIN, CAN_AF, GPIO_NOPULL);

    /* Filter: terima semua ID ke FIFO0 (filter ID dilakukan di app) */
    f.FilterBank           = 0;
    f.FilterMode           = CAN_FILTERMODE_IDMASK;
    f.FilterScale          = CAN_FILTERSCALE_32BIT;
    f.FilterIdHigh         = 0;
    f.FilterIdLow          = 0;
    f.FilterMaskIdHigh     = 0;
    f.FilterMaskIdLow      = 0;
    f.FilterFIFOAssignment = CAN_RX_FIFO0;
    f.FilterActivation     = ENABLE;
    f.SlaveStartFilterBank = 14;
    if (HAL_CAN_ConfigFilter(&hcan, &f) != HAL_OK) return false;

    return (HAL_CAN_Start(&hcan) == HAL_OK);
}

void can_send(uint32_t can_id, uint8_t length, const uint8_t *data)
{
    CAN_TxHeaderTypeDef hdr;
    uint32_t mailbox;
    uint8_t  buf[8] = {0};

    if (length > 8) length = 8;
    memcpy(buf, data, length);

    hdr.StdId              = can_id;
    hdr.ExtId              = 0;
    hdr.IDE                = CAN_ID_STD;
    hdr.RTR                = CAN_RTR_DATA;
    hdr.DLC                = length;
    hdr.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0 ||
        HAL_CAN_AddTxMessage(&hcan, &hdr, buf, &mailbox) != HAL_OK) {
        can_tx_errors++;
    }
}

bool can_receive(CanRcv_t *result)
{
    CAN_RxHeaderTypeDef hdr;

    if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0) return false;
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &hdr, result->data) != HAL_OK) return false;

    if (hdr.RTR != CAN_RTR_DATA) return false;

    result->id  = (hdr.IDE == CAN_ID_STD) ? hdr.StdId : hdr.ExtId;
    result->len = (uint8_t)hdr.DLC;
    return true;
}

