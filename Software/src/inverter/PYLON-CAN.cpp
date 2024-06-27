#include "../include.h"
#ifdef PYLON_CAN
#include "../datalayer/datalayer.h"
#include "../lib/miwagner-ESP32-Arduino-CAN/CAN_config.h"
#include "../lib/miwagner-ESP32-Arduino-CAN/ESP32CAN.h"
#include "PYLON-CAN.h"

#define SEND_0  //If defined, the messages will have ID ending with 0 (useful for some inverters)
//#define SEND_1 //If defined, the messages will have ID ending with 1 (useful for some inverters)
#define INVERT_LOW_HIGH_BYTES  //If defined, certain frames will have inverted low/high bytes \
                               //useful for some inverters like Sofar that report the voltages incorrect otherwise
//#define SET_30K_OFFSET  //If defined, current values are sent with a 30k offest (useful for ferroamp)

/* Do not change code below unless you are sure what you are doing */
//Actual content messages
CAN_frame_t PYLON_7310 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x7310,
                          .data = {0x01, 0x00, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00}};
CAN_frame_t PYLON_7320 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x7320,
                          .data = {0x4B, 0x00, 0x05, 0x0F, 0x2D, 0x00, 0x56, 0x00}};

CAN_frame_t PYLON_4210 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4210,
                          .data = {0xA5, 0x09, 0x30, 0x75, 0x9D, 0x04, 0x2E, 0x64}};
CAN_frame_t PYLON_4220 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4220,
                          .data = {0x8C, 0x0A, 0xE9, 0x07, 0x4A, 0x79, 0x4A, 0x79}};
CAN_frame_t PYLON_4230 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4230,
                          .data = {0xDF, 0x0C, 0xDA, 0x0C, 0x03, 0x00, 0x06, 0x00}};
CAN_frame_t PYLON_4240 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4240,
                          .data = {0x7E, 0x04, 0x62, 0x04, 0x11, 0x00, 0x03, 0x00}};
CAN_frame_t PYLON_4250 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4250,
                          .data = {0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
CAN_frame_t PYLON_4260 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4260,
                          .data = {0xAC, 0xC7, 0x74, 0x27, 0x03, 0x00, 0x02, 0x00}};
CAN_frame_t PYLON_4270 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4270,
                          .data = {0x7E, 0x04, 0x62, 0x04, 0x05, 0x00, 0x01, 0x00}};
CAN_frame_t PYLON_4280 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4280,
                          .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
CAN_frame_t PYLON_4290 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4290,
                          .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

CAN_frame_t PYLON_7311 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x7311,
                          .data = {0x01, 0x00, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00}};
CAN_frame_t PYLON_7321 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x7321,
                          .data = {0x4B, 0x00, 0x05, 0x0F, 0x2D, 0x00, 0x56, 0x00}};

CAN_frame_t PYLON_4211 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4211,
                          .data = {0xA5, 0x09, 0x30, 0x75, 0x9D, 0x04, 0x2E, 0x64}};
CAN_frame_t PYLON_4221 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4221,
                          .data = {0x8C, 0x0A, 0xE9, 0x07, 0x4A, 0x79, 0x4A, 0x79}};
CAN_frame_t PYLON_4231 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4231,
                          .data = {0xDF, 0x0C, 0xDA, 0x0C, 0x03, 0x00, 0x06, 0x00}};
CAN_frame_t PYLON_4241 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4241,
                          .data = {0x7E, 0x04, 0x62, 0x04, 0x11, 0x00, 0x03, 0x00}};
CAN_frame_t PYLON_4251 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4251,
                          .data = {0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
CAN_frame_t PYLON_4261 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4261,
                          .data = {0xAC, 0xC7, 0x74, 0x27, 0x03, 0x00, 0x02, 0x00}};
CAN_frame_t PYLON_4271 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4271,
                          .data = {0x7E, 0x04, 0x62, 0x04, 0x05, 0x00, 0x01, 0x00}};
CAN_frame_t PYLON_4281 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4281,
                          .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
CAN_frame_t PYLON_4291 = {.FIR = {.B =
                                      {
                                          .DLC = 8,
                                          .FF = CAN_frame_ext,
                                      }},
                          .MsgID = 0x4291,
                          .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

static int16_t max_charge_current = 0;
static int16_t max_discharge_current = 0;

void update_values_can_inverter() {  //This function maps all the values fetched from battery CAN to the correct CAN messages
  //There are more mappings that could be added, but this should be enough to use as a starting point
  // Note we map both 0 and 1 messages

  if (datalayer.battery.status.voltage_dV > 10) {  //div0 safeguard
    max_charge_current = (datalayer.battery.status.max_charge_power_W * 100) / datalayer.battery.status.voltage_dV;
    if (max_charge_current > datalayer.battery.info.max_charge_amp_dA) {
      max_charge_current =
          datalayer.battery.info
              .max_charge_amp_dA;  //Cap the value to the max allowed Amp. Some inverters cannot handle large values.
    }
    max_discharge_current =
        (datalayer.battery.status.max_discharge_power_W * 100) / datalayer.battery.status.voltage_dV;
    if (max_discharge_current > datalayer.battery.info.max_discharge_amp_dA) {
      max_discharge_current =
          datalayer.battery.info
              .max_discharge_amp_dA;  //Cap the value to the max allowed Amp. Some inverters cannot handle large values.
    }
  } else {
    max_charge_current = 0;
    max_discharge_current = 0;
  }

  //Charge / Discharge allowed
  PYLON_4280.data.u8[0] = 0;
  PYLON_4280.data.u8[1] = 0;
  PYLON_4280.data.u8[2] = 0;
  PYLON_4280.data.u8[3] = 0;
  PYLON_4281.data.u8[0] = 0;
  PYLON_4281.data.u8[1] = 0;
  PYLON_4281.data.u8[2] = 0;
  PYLON_4281.data.u8[3] = 0;

  //Voltage (370.0)
  PYLON_4210.data.u8[0] = (datalayer.battery.status.voltage_dV >> 8);
  PYLON_4210.data.u8[1] = (datalayer.battery.status.voltage_dV & 0x00FF);
  PYLON_4211.data.u8[0] = (datalayer.battery.status.voltage_dV >> 8);
  PYLON_4211.data.u8[1] = (datalayer.battery.status.voltage_dV & 0x00FF);

  //Current (15.0)
  PYLON_4210.data.u8[2] = (datalayer.battery.status.current_dA >> 8);
  PYLON_4210.data.u8[3] = (datalayer.battery.status.current_dA & 0x00FF);
  PYLON_4211.data.u8[2] = (datalayer.battery.status.current_dA >> 8);
  PYLON_4211.data.u8[3] = (datalayer.battery.status.current_dA & 0x00FF);

  // BMS Temperature (We dont have BMS temp, send max cell voltage instead)
#ifdef INVERT_LOW_HIGH_BYTES  //Useful for Sofar inverters
  PYLON_4210.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
  PYLON_4210.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
  PYLON_4211.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
  PYLON_4211.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
#else
  PYLON_4210.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
  PYLON_4210.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
  PYLON_4211.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
  PYLON_4211.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
#endif
  //SOC (100.00%)
  PYLON_4210.data.u8[6] = (datalayer.battery.status.reported_soc / 100);  //Remove decimals
  PYLON_4211.data.u8[6] = (datalayer.battery.status.reported_soc / 100);  //Remove decimals

  //StateOfHealth (100.00%)
  PYLON_4210.data.u8[7] = (datalayer.battery.status.soh_pptt / 100);
  PYLON_4211.data.u8[7] = (datalayer.battery.status.soh_pptt / 100);

  // Status=Bit 0,1,2= 0:Sleep, 1:Charge, 2:Discharge 3:Idle. Bit3 ForceChargeReq. Bit4 Balance charge Request
  if (datalayer.battery.status.current_dA < 0) {
    PYLON_4251.data.u8[0] = (0x11);  // Charge
  } else if (datalayer.battery.status.current_dA > 0) {
    PYLON_4251.data.u8[0] = (0x12);  // Discharge
  } else if (datalayer.battery.status.current_dA == 0) {
    PYLON_4251.data.u8[0] = (0x13);  // Idle
  }

#ifdef INVERT_LOW_HIGH_BYTES  //Useful for Sofar inverters
  //Voltage (370.0)
  PYLON_4210.data.u8[0] = (datalayer.battery.status.voltage_dV & 0x00FF);
  PYLON_4210.data.u8[1] = (datalayer.battery.status.voltage_dV >> 8);
  PYLON_4211.data.u8[0] = (datalayer.battery.status.voltage_dV & 0x00FF);
  PYLON_4211.data.u8[1] = (datalayer.battery.status.voltage_dV >> 8);

#ifdef SET_30K_OFFSET
  //Current (15.0)
  PYLON_4210.data.u8[2] = ((datalayer.battery.status.current_dA + 30000) & 0x00FF);
  PYLON_4210.data.u8[3] = ((datalayer.battery.status.current_dA + 30000) >> 8);
  PYLON_4211.data.u8[2] = ((datalayer.battery.status.current_dA + 30000) & 0x00FF);
  PYLON_4211.data.u8[3] = ((datalayer.battery.status.current_dA + 30000) >> 8);
#else
  PYLON_4210.data.u8[2] = (datalayer.battery.status.current_dA & 0x00FF);
  PYLON_4210.data.u8[3] = (datalayer.battery.status.current_dA >> 8);
  PYLON_4211.data.u8[2] = (datalayer.battery.status.current_dA & 0x00FF);
  PYLON_4211.data.u8[3] = (datalayer.battery.status.current_dA >> 8);
#endif

  // BMS Temperature (We dont have BMS temp, send max cell voltage instead)
  PYLON_4210.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
  PYLON_4210.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
  PYLON_4211.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
  PYLON_4211.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);

  //Maxvoltage (eg 400.0V = 4000 , 16bits long) Discharge Cutoff Voltage
  PYLON_4220.data.u8[0] = (datalayer.battery.info.max_design_voltage_dV & 0x00FF);
  PYLON_4220.data.u8[1] = (datalayer.battery.info.max_design_voltage_dV >> 8);
  PYLON_4221.data.u8[0] = (datalayer.battery.info.max_design_voltage_dV & 0x00FF);
  PYLON_4221.data.u8[1] = (datalayer.battery.info.max_design_voltage_dV >> 8);

  //Minvoltage (eg 300.0V = 3000 , 16bits long) Charge Cutoff Voltage
  PYLON_4220.data.u8[2] = (datalayer.battery.info.min_design_voltage_dV & 0x00FF);
  PYLON_4220.data.u8[3] = (datalayer.battery.info.min_design_voltage_dV >> 8);
  PYLON_4221.data.u8[2] = (datalayer.battery.info.min_design_voltage_dV & 0x00FF);
  PYLON_4221.data.u8[3] = (datalayer.battery.info.min_design_voltage_dV >> 8);

#ifdef SET_30K_OFFSET
  //Max ChargeCurrent
  PYLON_4220.data.u8[4] = ((max_charge_current + 30000) & 0x00FF);
  PYLON_4220.data.u8[5] = ((max_charge_current + 30000) >> 8);
  PYLON_4221.data.u8[4] = ((max_charge_current + 30000) & 0x00FF);
  PYLON_4221.data.u8[5] = ((max_charge_current + 30000) >> 8);

  //Max DischargeCurrent
  PYLON_4220.data.u8[6] = ((30000 - max_discharge_current) & 0x00FF);
  PYLON_4220.data.u8[7] = ((30000 - max_discharge_current) >> 8);
  PYLON_4221.data.u8[6] = ((30000 - max_discharge_current) & 0x00FF);
  PYLON_4221.data.u8[7] = ((30000 - max_discharge_current) >> 8);
#else
  //Max ChargeCurrent
  PYLON_4220.data.u8[4] = (max_charge_current & 0x00FF);
  PYLON_4220.data.u8[5] = (max_charge_current >> 8);
  PYLON_4221.data.u8[4] = (max_charge_current & 0x00FF);
  PYLON_4221.data.u8[5] = (max_charge_current >> 8);

  //Max DishargeCurrent
  PYLON_4220.data.u8[6] = (max_discharge_current & 0x00FF);
  PYLON_4220.data.u8[7] = (max_discharge_current >> 8);
  PYLON_4221.data.u8[6] = (max_discharge_current & 0x00FF);
  PYLON_4221.data.u8[7] = (max_discharge_current >> 8);
#endif

  //Max cell voltage
  PYLON_4230.data.u8[0] = (datalayer.battery.status.cell_max_voltage_mV & 0x00FF);
  PYLON_4230.data.u8[1] = (datalayer.battery.status.cell_max_voltage_mV >> 8);
  PYLON_4231.data.u8[0] = (datalayer.battery.status.cell_max_voltage_mV & 0x00FF);
  PYLON_4231.data.u8[1] = (datalayer.battery.status.cell_max_voltage_mV >> 8);

  //Min cell voltage
  PYLON_4230.data.u8[2] = (datalayer.battery.status.cell_min_voltage_mV & 0x00FF);
  PYLON_4230.data.u8[3] = (datalayer.battery.status.cell_min_voltage_mV >> 8);
  PYLON_4231.data.u8[2] = (datalayer.battery.status.cell_min_voltage_mV & 0x00FF);
  PYLON_4231.data.u8[3] = (datalayer.battery.status.cell_min_voltage_mV >> 8);

  //Max temperature per cell
  PYLON_4240.data.u8[0] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4240.data.u8[1] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4241.data.u8[0] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4241.data.u8[1] = (datalayer.battery.status.temperature_max_dC >> 8);

  //Max/Min temperature per cell
  PYLON_4240.data.u8[2] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
  PYLON_4240.data.u8[3] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4240.data.u8[2] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
  PYLON_4240.data.u8[3] = (datalayer.battery.status.temperature_min_dC >> 8);

  //Max temperature per module
  PYLON_4270.data.u8[0] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4270.data.u8[1] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4271.data.u8[0] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4271.data.u8[1] = (datalayer.battery.status.temperature_max_dC >> 8);

  //Min temperature per module
  PYLON_4270.data.u8[2] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
  PYLON_4270.data.u8[3] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4271.data.u8[2] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
  PYLON_4271.data.u8[3] = (datalayer.battery.status.temperature_min_dC >> 8);
#else
  //Voltage (370.0)
  PYLON_4210.data.u8[0] = (datalayer.battery.status.voltage_dV >> 8;
  PYLON_4210.data.u8[1] = (datalayer.battery.status.voltage_dV & 0x00FF);
  PYLON_4211.data.u8[0] = (datalayer.battery.status.voltage_dV >> 8);
  PYLON_4211.data.u8[1] = (datalayer.battery.status.voltage_dV & 0x00FF);

#ifdef SET_30K_OFFSET
  //Current (15.0)
  PYLON_4210.data.u8[2] = ((datalayer.battery.status.current_dA + 30000) >> 8);
  PYLON_4210.data.u8[3] = ((datalayer.battery.status.current_dA + 30000) & 0x00FF);
  PYLON_4211.data.u8[2] = ((datalayer.battery.status.current_dA + 30000) >> 8);
  PYLON_4211.data.u8[3] = ((datalayer.battery.status.current_dA + 30000) & 0x00FF);
#else
  PYLON_4210.data.u8[2] = (datalayer.battery.status.current_dA >> 8);
  PYLON_4210.data.u8[3] = (datalayer.battery.status.current_dA & 0x00FF);
  PYLON_4211.data.u8[2] = (datalayer.battery.status.current_dA >> 8);
  PYLON_4211.data.u8[3] = (datalayer.battery.status.current_dA & 0x00FF);
#endif

  // BMS Temperature (We dont have BMS temp, send max cell voltage instead)
  PYLON_4210.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
  PYLON_4210.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);
  PYLON_4211.data.u8[4] = ((datalayer.battery.status.temperature_max_dC + 1000) >> 8);
  PYLON_4211.data.u8[5] = ((datalayer.battery.status.temperature_max_dC + 1000) & 0x00FF);

  //Maxvoltage (eg 400.0V = 4000 , 16bits long) Discharge Cutoff Voltage
  PYLON_4220.data.u8[0] = (datalayer.battery.info.max_design_voltage_dV >> 8);
  PYLON_4220.data.u8[1] = (datalayer.battery.info.max_design_voltage_dV & 0x00FF);
  PYLON_4221.data.u8[0] = (datalayer.battery.info.max_design_voltage_dV >> 8);
  PYLON_4221.data.u8[1] = (datalayer.battery.info.max_design_voltage_dV & 0x00FF);

  //Minvoltage (eg 300.0V = 3000 , 16bits long) Charge Cutoff Voltage
  PYLON_4220.data.u8[2] = (datalayer.battery.info.min_design_voltage_dV >> 8);
  PYLON_4220.data.u8[3] = (datalayer.battery.info.min_design_voltage_dV & 0x00FF);
  PYLON_4221.data.u8[2] = (datalayer.battery.info.min_design_voltage_dV >> 8);
  PYLON_4221.data.u8[3] = (datalayer.battery.info.min_design_voltage_dV & 0x00FF);

#ifdef SET_30K_OFFSET
  //Max ChargeCurrent
  PYLON_4220.data.u8[4] = ((max_charge_current + 30000) >> 8);
  PYLON_4220.data.u8[5] = ((max_charge_current + 30000) & 0x00FF);
  PYLON_4221.data.u8[4] = ((max_charge_current + 30000) >> 8);
  PYLON_4221.data.u8[5] = ((max_charge_current + 30000) & 0x00FF);

  //Max DischargeCurrent
  PYLON_4220.data.u8[6] = ((30000 - max_discharge_current) >> 8);
  PYLON_4220.data.u8[7] = ((30000 - max_discharge_current) & 0x00FF);
  PYLON_4221.data.u8[6] = ((30000 - max_discharge_current) >> 8);
  PYLON_4221.data.u8[7] = ((30000 - max_discharge_current) & 0x00FF);
#else
  //Max ChargeCurrent
  PYLON_4220.data.u8[4] = (max_charge_current >> 8);
  PYLON_4220.data.u8[5] = (max_charge_current & 0x00FF);
  PYLON_4221.data.u8[4] = (max_charge_current >> 8);
  PYLON_4221.data.u8[5] = (max_charge_current & 0x00FF);

  //Max DishargeCurrent
  PYLON_4220.data.u8[6] = (max_discharge_current >> 8);
  PYLON_4220.data.u8[7] = (max_discharge_current & 0x00FF);
  PYLON_4221.data.u8[6] = (max_discharge_current >> 8);
  PYLON_4221.data.u8[7] = (max_discharge_current & 0x00FF);
#endif

  //Max cell voltage
  PYLON_4230.data.u8[0] = (datalayer.battery.status.cell_max_voltage_mV >> 8);
  PYLON_4230.data.u8[1] = (datalayer.battery.status.cell_max_voltage_mV & 0x00FF);
  PYLON_4231.data.u8[0] = (datalayer.battery.status.cell_max_voltage_mV >> 8);
  PYLON_4231.data.u8[1] = (datalayer.battery.status.cell_max_voltage_mV & 0x00FF);

  //Min cell voltage
  PYLON_4230.data.u8[2] = (datalayer.battery.status.cell_min_voltage_mV >> 8);
  PYLON_4230.data.u8[3] = (datalayer.battery.status.cell_min_voltage_mV & 0x00FF);
  PYLON_4231.data.u8[2] = (datalayer.battery.status.cell_min_voltage_mV >> 8);
  PYLON_4231.data.u8[3] = (datalayer.battery.status.cell_min_voltage_mV & 0x00FF);

  //Max temperature per cell
  PYLON_4240.data.u8[0] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4240.data.u8[1] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4241.data.u8[0] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4241.data.u8[1] = (datalayer.battery.status.temperature_max_dC & 0x00FF);

  //Max/Min temperature per cell
  PYLON_4240.data.u8[2] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4240.data.u8[3] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
  PYLON_4240.data.u8[2] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4240.data.u8[3] = (datalayer.battery.status.temperature_min_dC & 0x00FF);

  //Max temperature per module
  PYLON_4270.data.u8[0] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4270.data.u8[1] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4271.data.u8[0] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4271.data.u8[1] = (datalayer.battery.status.temperature_max_dC & 0x00FF);

  //Min temperature per module
  PYLON_4270.data.u8[2] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4270.data.u8[3] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
  PYLON_4271.data.u8[2] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4271.data.u8[3] = (datalayer.battery.status.temperature_min_dC & 0x00FF);
#endif

  //Max/Min cell voltage
  PYLON_4230.data.u8[0] = (datalayer.battery.status.cell_max_voltage_mV >> 8);
  PYLON_4230.data.u8[1] = (datalayer.battery.status.cell_max_voltage_mV & 0x00FF);
  PYLON_4230.data.u8[2] = (datalayer.battery.status.cell_min_voltage_mV >> 8);
  PYLON_4230.data.u8[3] = (datalayer.battery.status.cell_min_voltage_mV & 0x00FF);

  //Max/Min temperature per cell
  PYLON_4240.data.u8[0] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4240.data.u8[1] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4240.data.u8[2] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4240.data.u8[3] = (datalayer.battery.status.temperature_min_dC & 0x00FF);

  //Max/Min temperature per module
  PYLON_4270.data.u8[0] = (datalayer.battery.status.temperature_max_dC >> 8);
  PYLON_4270.data.u8[1] = (datalayer.battery.status.temperature_max_dC & 0x00FF);
  PYLON_4270.data.u8[2] = (datalayer.battery.status.temperature_min_dC >> 8);
  PYLON_4270.data.u8[3] = (datalayer.battery.status.temperature_min_dC & 0x00FF);

  //In case we run into any errors/faults, we can set charge / discharge forbidden
  if (datalayer.battery.status.bms_status == FAULT) {
    PYLON_4280.data.u8[0] = 0xAA;
    PYLON_4280.data.u8[1] = 0xAA;
    PYLON_4280.data.u8[2] = 0xAA;
    PYLON_4280.data.u8[3] = 0xAA;
    PYLON_4281.data.u8[0] = 0xAA;
    PYLON_4281.data.u8[1] = 0xAA;
    PYLON_4281.data.u8[2] = 0xAA;
    PYLON_4281.data.u8[3] = 0xAA;
  }
}

void receive_can_inverter(CAN_frame_t rx_frame) {
  switch (rx_frame.MsgID) {
    case 0x4200:  //Message originating from inverter. Depending on which data is required, act accordingly
      if (rx_frame.data.u8[0] == 0x02) {
        send_setup_info();
      }
      if (rx_frame.data.u8[0] == 0x00) {
        send_system_data();
      }
      break;
    default:
      break;
  }
}

void send_can_inverter() {
  // No periodic sending, we only react on received can messages
}

void send_setup_info() {  //Ensemble information
  //Amount of cells
  PYLON_7320.data.u8[0] = datalayer.battery.info.number_of_cells;
  //Modules in series (not really how EV packs work, but let's map it to a reasonable Pylon value)
  PYLON_7320.data.u8[2] = (datalayer.battery.info.number_of_cells / 15);
  //Capacity in AH
  if (datalayer.battery.status.voltage_dV > 10) {  //div0 safeguard
    PYLON_7320.data.u8[6] = (datalayer.battery.info.total_capacity_Wh / (datalayer.battery.status.voltage_dV / 10));
  }

#ifdef SEND_0
  ESP32Can.CANWriteFrame(&PYLON_7310);
  ESP32Can.CANWriteFrame(&PYLON_7320);
#endif
#ifdef SEND_1
  ESP32Can.CANWriteFrame(&PYLON_7311);
  ESP32Can.CANWriteFrame(&PYLON_7321);
#endif
}

void send_system_data() {  //System equipment information
#ifdef SEND_0
  ESP32Can.CANWriteFrame(&PYLON_4210);
  ESP32Can.CANWriteFrame(&PYLON_4220);
  ESP32Can.CANWriteFrame(&PYLON_4230);
  ESP32Can.CANWriteFrame(&PYLON_4240);
  ESP32Can.CANWriteFrame(&PYLON_4250);
  ESP32Can.CANWriteFrame(&PYLON_4260);
  ESP32Can.CANWriteFrame(&PYLON_4270);
  ESP32Can.CANWriteFrame(&PYLON_4280);
  ESP32Can.CANWriteFrame(&PYLON_4290);
#endif
#ifdef SEND_1
  ESP32Can.CANWriteFrame(&PYLON_4211);
  ESP32Can.CANWriteFrame(&PYLON_4221);
  ESP32Can.CANWriteFrame(&PYLON_4231);
  ESP32Can.CANWriteFrame(&PYLON_4241);
  ESP32Can.CANWriteFrame(&PYLON_4251);
  ESP32Can.CANWriteFrame(&PYLON_4261);
  ESP32Can.CANWriteFrame(&PYLON_4271);
  ESP32Can.CANWriteFrame(&PYLON_4281);
  ESP32Can.CANWriteFrame(&PYLON_4291);
#endif
}
#endif
