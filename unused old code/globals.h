//------------------------------------------------------------------------------
// globals.h
//
// Contains global variables and constants.
//
// Author: 12315923
//------------------------------------------------------------------------------
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include "status.h"     // Status

// User input
const int INPUT_BUFFER_SIZE = 256;
const int INPUT_CHUNK_SIZE = 8;

// Commands are in commands.h

// Error Messages
const Status OK = { .code_ = 0, 
  .message_ = "OK", .is_formatted_ = false };
const Status WRONG_NUM_ARGS = { .code_ = 1, 
  .message_ = "Usage: ./a3 <config file>", .is_formatted_ = false };
const Status CANNOT_OPEN_FILE = { .code_ = 2, 
  .message_ = "Error: Cannot open file: %s", .is_formatted_ = true };
const Status INVALID_FILE = { .code_ = 3, 
  .message_ = "Error: Invalid file: %s", .is_formatted_ = true };
const Status OUT_OF_MEMORY = { .code_ = 4, 
  .message_ = "Error: Out of memory", .is_formatted_ = false };
const Status INVALID_CARD_NUMBER = { .code_ = 5, 
  .message_ = "Please enter the number of a card in your hand cards!", .is_formatted_ = false };
const Status INVALID_COMMAND = { .code_ = 6, 
  .message_ = "Please enter a valid command!", .is_formatted_ = false };
const Status INVALID_ARGS = { .code_ = 7, 
  .message_ = "Please enter the correct number of parameters!", .is_formatted_ = false };
const Status INVALID_ROW_NUMBER = { .code_ = 8, 
  .message_ = "Please enter a valid row number!", .is_formatted_ = false };
const Status INVALID_CHOSEN_CARD = { .code_ = 9, 
  .message_ = "Please enter the number of a card in your chosen cards!", .is_formatted_ = false };
const Status CANNOT_EXTEND_ROW = { .code_ = 10, 
  .message_ = "This card cannot extend the chosen row!", .is_formatted_ = false };
const Status RESULTS_NOT_WRITTEN = { .code_ = 0, 
  .message_ = "Warning: Results not written to file!", .is_formatted_ = false };
const Status PARSE_ERROR = { .code_ = 12, 
  .message_ = "Error: Parsing error!", .is_formatted_ = false };
const Status STEAL_USED = { .code_ = 13, 
  .message_ = "Already used steal action!", .is_formatted_ = false };
const Status OPP_HAS_NO_MATCHING_CARD = { .code_ = 14, 
  .message_ = "Opponent does not have the selected card!", .is_formatted_ = false };

#endif // GLOBALS_H
