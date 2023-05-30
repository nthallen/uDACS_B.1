/** @file serial_num.h
 * This file must define:
 *  CAN_BOARD_ID: The CAN Identifier for the board. This must be unique on a specific CAN Bus
 *  SUBBUS_BOARD_SN: The serial number of this board among boards of the same SUBBUS_BOARD_TYPE
 *  SUBBUS_BUILD_NUM:
 *  SUBBUS_SUBFUNCTION: The board type code as defined in "SYSCON Memory Maps and Subbus Board IDs"
 *  SUBBUS_BOARD_ID: Board Identification number (*not* the CAN_BOARD_ID). Defines the type of board
 *     SUBBUS_SUBFUNCTION may be the same as SUBBUS_BOARD_ID if there is no significant
 *     configuration difference between boards. If different, the SUBBUS_BOARD_ID values
 *     should be documented along with the SUBBUS_BOARD_SN etc. in the board's Specifications document
 *  SUBBUS_BOARD_INSTRUMENT_ID: Number that maps to Instrument name. (not yet used as of 4/18/19)
 *  SUBBUS_BOARD_REV: String encapsulating almost anything here
 */
#ifndef SERIAL_NUM_H_INCLUDED
#define SERIAL_NUM_H_INCLUDED
#include "uDACS_pins.h"

// These parameters are common to all boards built with this code
#define SUBBUS_BOARD_FIRMWARE_REV "V2.0"
#define SUBBUS_BOARD_BUILD_NUM 14
#define HAVE_RTC

// This repository is specific to uDACS Rev B.1
// The .1 version differs from earlier uses of Rev B due to
// different components being installed and different components
// connected remotely, both requiring changes to the START
// definition. As of 5/30/23, we have decided that START
// changes warrant a separate repository.
//
// We will maintain unique SN values for all Rev B boards.
#define SUBBUS_SUBFUNCTION 14 // uDACS Rev B
#define SUBBUS_SUBFUNCTION_HEX E // 14 in hex
#define SUBBUS_BOARD_ID 3 // B.1
#define SUBBUS_BOARD_BOARD_REV "Rev B.1"

/**
 * Build definitions
 * 1: Initial build
 */
#if ! defined(SUBBUS_BOARD_SN)
#error Must define SUBBUS_BOARD_SN in Build Properties
#endif

#if ! defined(SUBBUS_SUBFUNCTION)
// subfunction should be 14 for Rev B
#error Must define SUBBUS_SUBFUNCTION
#endif

// Serial Numbers 1 through 4 are on board IDs 1 and 2
// Their firmware is in another repository
#if SUBBUS_SUBFUNCTION == 14

  #if SUBBUS_BOARD_SN == 5
  #define SUBBUS_BOARD_INSTRUMENT_ID 10
  #define SUBBUS_BOARD_INSTRUMENT "FOCAL"
  #define SUBBUS_BOARD_BOARD_TYPE "OE uDACS"
  #define SUBBUS_BOARD_LOCATION "CO2"
//  #define uDACS_B	// Need this out to disable spi_ps.c/.h
  #endif

  #if SUBBUS_BOARD_SN == 6
  #define SUBBUS_BOARD_INSTRUMENT_ID 10
  #define SUBBUS_BOARD_INSTRUMENT "FOCAL"
  #define SUBBUS_BOARD_ID 3
  #define SUBBUS_BOARD_BOARD_TYPE "OE uDACS"
  #define SUBBUS_BOARD_LOCATION "Methane"
  //  #define uDACS_B	// Need this out to disable spi_ps.c/.h
  #endif

  #if SUBBUS_BOARD_SN == 7
  #define SUBBUS_BOARD_INSTRUMENT_ID 10
  #define SUBBUS_BOARD_INSTRUMENT "FOCAL"
  #define SUBBUS_BOARD_ID 3
  #define SUBBUS_BOARD_BOARD_TYPE "OE uDACS"
  #define SUBBUS_BOARD_LOCATION "CO2 Backup"
  //  #define uDACS_B	// Need this out to disable spi_ps.c/.h
  #endif

  #if SUBBUS_BOARD_SN == 8
  #define SUBBUS_BOARD_INSTRUMENT_ID 10
  #define SUBBUS_BOARD_INSTRUMENT "FOCAL"
  #define SUBBUS_BOARD_ID 3
  #define SUBBUS_BOARD_BOARD_TYPE "OE uDACS"
  #define SUBBUS_BOARD_LOCATION "Methane Backup"
  //  #define uDACS_B	// Need this out to disable spi_ps.c/.h
  #endif

  #if SUBBUS_BOARD_SN == 9
  #define SUBBUS_BOARD_INSTRUMENT_ID 10
  #define SUBBUS_BOARD_INSTRUMENT "Test"
  #define SUBBUS_BOARD_ID 3
  #define SUBBUS_BOARD_BOARD_TYPE "Spare uDACS"
  #define SUBBUS_BOARD_LOCATION "Stock"
  //  #define uDACS_B	// Need this out to disable spi_ps.c/.h
  #endif

#else
  #error Unsupported SUBFUNCTION number
#endif

#ifndef SUBBUS_BOARD_LOCATION
  #error SUBBUS_BOARD_LOCATION not defined
#endif

#ifndef SUBBUS_SUBFUNCTION_HEX
#if SUBBUS_SUBFUNCTION >= 10
#error SUBBUS_SUBFUNCTION_HEX must be defined for SUBFUNC values >= 10
#else
#define SUBBUS_SUBFUNCTION_HEX SUBBUS_SUBFUNCTION
#endif
#endif

#ifdef CAN_BOARD_ID

#define SUBBUS_BOARD_DESC_STR(SN,ID) SUBBUS_BOARD_INSTRUMENT " " SUBBUS_BOARD_BOARD_TYPE " " \
SUBBUS_BOARD_BOARD_REV " " SUBBUS_BOARD_FIRMWARE_REV \
" S/N:" #SN " CAN ID:" #ID " " SUBBUS_BOARD_LOCATION
#define SUBBUS_BOARD_DESC_XSTR(SUBBUS_BOARD_SN,CAN_BOARD_ID) SUBBUS_BOARD_DESC_STR(SUBBUS_BOARD_SN,CAN_BOARD_ID)
#define SUBBUS_BOARD_DESC SUBBUS_BOARD_DESC_XSTR(SUBBUS_BOARD_SN,CAN_BOARD_ID)

#else

#define SUBBUS_BOARD_DESC_STR(SN) SUBBUS_BOARD_INSTRUMENT " " SUBBUS_BOARD_BOARD_TYPE " " \
SUBBUS_BOARD_BOARD_REV " " SUBBUS_BOARD_FIRMWARE_REV \
" S/N:" #SN " " SUBBUS_BOARD_LOCATION
#define SUBBUS_BOARD_DESC_XSTR(SUBBUS_BOARD_SN) SUBBUS_BOARD_DESC_STR(SUBBUS_BOARD_SN)
#define SUBBUS_BOARD_DESC SUBBUS_BOARD_DESC_XSTR(SUBBUS_BOARD_SN)

#endif // CAN_BOARD_ID


#define SUBBUS_BOARD_REV_STR(SN,SF) "V" #SF ":0:" SUBBUS_BOARD_DESC
#define SUBBUS_BOARD_REV_XSTR(SN,SF) SUBBUS_BOARD_REV_STR(SN,SF)
#define SUBBUS_BOARD_REV SUBBUS_BOARD_REV_XSTR(SUBBUS_BOARD_SN,SUBBUS_SUBFUNCTION_HEX)

#endif
