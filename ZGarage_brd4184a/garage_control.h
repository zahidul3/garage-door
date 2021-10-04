/*
 * garage_control.h
 *
 *  Created on: Oct 3, 2021
 *      Author: zahidhaq
 */

#ifndef GARAGE_CONTROL_H_
#define GARAGE_CONTROL_H_

#define GARAGE_ACCESS_CODE 0x12345678

void GarageControl_init(void);
void GarageControl_PinSet(void);
void GarageControl_PinClear(void);
void GarageControl_Open(void);

#endif /* GARAGE_CONTROL_H_ */
