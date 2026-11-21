/*
 * steering.h
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#ifndef INC_STEERING_H_
#define INC_STEERING_H_

#include <stdint.h>

void  steering_init(void);
void  steering_update(void);             /* panggil tiap loop (baca encoder + PID) */
void  steering_set_degree(float rad);    /* setpoint dalam RADIAN (nama dipertahankan dari kode lama) */
float steering_read_angle(void);         /* radian, NAN jika encoder invalid */
void  steering_change_dir(int dir);
void  steering_test_enc_input(char *out, uint16_t out_size);


#endif /* INC_STEERING_H_ */
