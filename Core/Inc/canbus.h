/*
 * canbus.h
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#ifndef INC_CANBUS_H_
#define INC_CANBUS_H_

#include <stdint.h>
#include <stdbool.h>

typedef union {
    int32_t value;
    uint8_t bytes[4];
} CanMsg_32t;

typedef union {
    float   value;
    uint8_t bytes[4];
} CanMsg_Flt;

typedef struct {
    uint32_t id;
    uint8_t  len;
    uint8_t  data[8];
} CanRcv_t;

extern uint32_t can_tx_errors;

bool can_init(void);
void can_send(uint32_t can_id, uint8_t length, const uint8_t *data);
bool can_receive(CanRcv_t *result);


#endif /* INC_CANBUS_H_ */
