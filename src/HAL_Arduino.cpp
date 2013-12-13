/**
 * Arduino implementation of the Gainspan HAL functions
 */

extern "C" {
#include "hardware/GS_HAL.h"
}

#include <Arduino.h>
#include <ctype.h>

#define GAINSPAN_SERIAL Serial1

#define DEBUG_RAW_DATA

/** Public Method Implementation **/
void GS_HAL_uart_set_comm_port(uint32_t baudRate) {
  GAINSPAN_SERIAL.begin(baudRate);
}

static void print_char(uint8_t c) {
  #ifdef DEBUG_RAW_DATA
  static int ignore = -1;
  // Make sure that every \r, \n or \r\n results in printing exactly
  // \r\n, but don't introduce extra linebreaks because of this.
  if (c == ignore) {
    // skip
    ignore = -1;
  } else if (c == '\r') {
    Serial.print("\r\n");
    ignore = '\n';
  } else if (c == '\n') {
    Serial.print("\r\n");
  } else if (isprint(c)) {
    Serial.write(c);
  } else {
    Serial.print('\\');
    Serial.print(c >> 4, HEX);
    Serial.print(c & 0xf, HEX);
  }
  #endif
}

void GS_HAL_uart_send(const uint8_t* txBuf, uint16_t numToWrite) {
  GAINSPAN_SERIAL.write(txBuf, numToWrite);
  while (numToWrite--)
    print_char(*txBuf++);
}

uint16_t GS_HAL_uart_recv(uint8_t* rxBuf, uint16_t numToRead, bool block) {
  uint16_t read = 0;
  // Keep getting data if we have a number of bytes to fetch
  while (read < numToRead) {
    int c = GAINSPAN_SERIAL.read();
    if (c >= 0) {
      rxBuf[read++] = (uint8_t)c;
      print_char(c);
    } else if (!block) {
      return read;
    }
  }
  return read;;
}

void GS_HAL_print(char* strBuf){
	Serial.println(strBuf);
}

void MSTimerInit(void)
{
}

uint32_t MSTimerGet(void)
{
    return millis();
}

uint32_t MSTimerDelta(uint32_t start)
{
    return millis() - start;
}

void MSTimerDelay(uint32_t ms)
{
	delay(ms);
}

/* Dummy */
bool GS_HAL_store_data(uint16_t address, uint8_t* writeBuf, uint8_t numToWrite){
  return false;
}

/* Dummy */
bool GS_HAL_read_data(uint16_t address, uint8_t* readBuf, uint8_t numToRead){
  return false;
}


/* vim: set sw=2 sts=2 et: */
