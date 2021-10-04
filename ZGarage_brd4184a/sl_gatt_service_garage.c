/*
 * sl_gatt_service_garage.c
 *
 *  Created on: Oct 3, 2021
 *      Author: zahidhaq
 */


// -----------------------------------------------------------------------------
// Public function definitions
#include "stdbool.h"
#include "sl_status.h"
#include "gatt_db.h"
#include "app_assert.h"
#include "app_log.h"
#include "garage_control.h"
#include "sl_gatt_service_garage.h"

static void garage_system_boot_cb(void)
{
  sl_status_t sc;
  app_log_info("garage_system_boot_cb\n\r");
}

static void garage_connection_opened_cb(sl_bt_evt_connection_opened_t *data)
{
  (void)data;
  // Reset garage state
  GarageControl_PinClear();
}

static void garage_connection_closed_cb(sl_bt_evt_connection_closed_t *data)
{
  (void)data;
  // Reset garage state
  GarageControl_PinClear();
}

static void garage_process_write(uint8_t* data)
{
  uint32_t accessCode = *((uint32_t*)data);

  if(accessCode == GARAGE_ACCESS_CODE)
    {
      app_log_critical("Garage access GRANTED!!!\n\r");
      GarageControl_Open();
    }
  else
    {
      app_log_error("Invalid ACCESS code!!!\n\r");
    }

  app_log_debug("Garage access code written: 0x%04x", accessCode);
}

static void garage_write_cb(sl_bt_evt_gatt_server_user_write_request_t *data)
{
  sl_status_t sc;
  uint8_t att_errorcode = 0;

  if (data->value.len == 4) {
      garage_process_write(&data->value.data[0]);
  } else {
    app_log_error("Invalid length written!!!\n\r");
    att_errorcode = 0x0D; // Invalid Attribute Value Length
  }
//
//  sc = sl_bt_gatt_server_send_user_write_response(data->connection,
//                                                  data->characteristic,
//                                                  att_errorcode);
  //app_assert_status(sc);
}

void sl_gatt_service_garage_on_event(sl_bt_msg_t *evt)
{

  if (gattdb_garage_access == evt->data.evt_gatt_server_user_write_request.characteristic) {
      garage_write_cb(&evt->data.evt_gatt_server_user_write_request);
  }

  // Handle stack events
//  switch (SL_BT_MSG_ID(evt->header)) {
//    case sl_bt_evt_system_boot_id:
//      garage_system_boot_cb();
//      break;
//
//    case sl_bt_evt_connection_opened_id:
//      garage_connection_opened_cb(&evt->data.evt_connection_opened);
//      break;
//
//    case sl_bt_evt_connection_closed_id:
//      garage_connection_closed_cb(&evt->data.evt_connection_closed);
//      break;
//
//    case 0xa08a0://sl_bt_evt_gatt_server_user_write_request_id:
//      if (gattdb_garage_access == evt->data.evt_gatt_server_user_write_request.characteristic) {
//          garage_write_cb(&evt->data.evt_gatt_server_user_write_request);
//      }
//      break;
//  }
}
