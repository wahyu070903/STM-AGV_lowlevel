/*
 * drive.h
 *
 *  Created on: Nov 20, 2026
 *      Author: Orsted-793
 */

#ifndef INC_DRIVE_H_
#define INC_DRIVE_H_

#include <stdint.h>

void    drive_init(void);
void    drive_set_speed(int speed);      /* -255..255 */
int32_t drive_get_count(void);
void    drive_measure_speed(void);       /* panggil tiap loop */
float   drive_get_speed_rpm(void);       /* RPM roda */


#endif /* INC_DRIVE_H_ */
