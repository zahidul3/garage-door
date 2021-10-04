/*
 * sl_gatt_service_garage.h
 *
 *  Created on: Oct 3, 2021
 *      Author: zahidhaq
 */

#ifndef SL_GATT_SERVICE_GARAGE_H_
#define SL_GATT_SERVICE_GARAGE_H_

#include "sl_bt_api.h"

/**************************************************************************//**
 * Bluetooth stack event handler.
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_gatt_service_garage_on_event(sl_bt_msg_t *evt);

#endif /* SL_GATT_SERVICE_GARAGE_H_ */
