#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef COMMANDHANDLING_H
#define COMMANDHANDLING_H

#define DIFFRENCE_ASCII_LOWER_UPPER 32
#define ASCII_LOWER_CASE_A 97
#define ASCII_LOWER_CASE_Z 122

#define COMMAND_BUFFER_SIZE 100

#define MAX_COMMAND_COUNT 10 //temporary

#define WRONG_PARAMETER_COUNT_MESSAGE "Error: Wrong parameter count.\n"

#define QUIT_STRING "QUIT"
#define HELP_STRING "HELP"
#define RENAME_STRING "RENAME"

const char *COMMAND_STRINGS[COMMAND_BUFFER_SIZE] = {QUIT_STRING, HELP_STRING, RENAME_STRING};

enum _CommandParameterCount_ {
  QUIT_PARAMETER_COUNT = 1,
  HELP_PARAMETER_COUNT = 1,
  RENAME_PARAMETER_COUNT = 3 //Minimum
};

const int COMMAND_PARAMETER_COUNTS[] = {QUIT_PARAMETER_COUNT, HELP_PARAMETER_COUNT, RENAME_PARAMETER_COUNT};

typedef enum _CommandIndex_ {
  NOTHING = -1,
  QUIT,
  HELP,
  RENAME,
  DRAW
} Command_index;

//---------------------------------------------------------------------------------------------------------------------
///
/// This function get the parameter count of a command.
///
/// @param command_input the command line that was input by the user
///
/// @return parameter count
//
int getParameterCount(char *command_input) {
  char command[COMMAND_BUFFER_SIZE];
  int parameter_counter = 1;
  strcpy(command, command_input);
  strtok(command, " ");

  while (strtok(NULL, " ") != NULL) {
    parameter_counter++;
  }
  return parameter_counter;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function checks the current parameter count of a command line and compares it to the value that the user did
/// pass to the function. It returns either true (1) or false (0).
///
/// @param command_input the command line that was input by the user
/// @param correct_parameter_count the value to compare with
///
/// @return TRUE/FALSE
//
bool checkParameterCount(char *command_input, int correct_parameter_count) {
  int parameter_count = getParameterCount(command_input);

  if (parameter_count == correct_parameter_count) {
    return true;
  } else {
    return false;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function converts a string to uppercase.
///
/// @param string this is the string to be checked
/// @param string_length the length of the current string
//
void convertUpperCase(char *string, int string_length) {
  for (int i = 0; i < string_length; i++) {
    if (string[i] <= ASCII_LOWER_CASE_Z && string[i] >= ASCII_LOWER_CASE_A) {
      string[i] -= DIFFRENCE_ASCII_LOWER_UPPER;
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function compares the first parameter (or first command) to the command_template passed to the function.
/// After the process true (1) or false (0) gets returned.
///
/// @param command_input the command line that was input by the user
/// @param command_template the command template to compare with.
///
/// @return TRUE/FALSE
//
bool compareCommandFirstParameter(char *command_input, const char *command_template) {
  char command[COMMAND_BUFFER_SIZE];
  strcpy(command, command_input);
  char *first_parameter = strtok(command, " ");
  convertUpperCase(first_parameter, strlen(first_parameter));

  if (strcmp(first_parameter, command_template) == 0) {
    return true;
  } else {
    return false;
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function uses helper functions to determine which function is input by the user and checks for validity.
/// The return values are the indices to the command (Example: 0 = QUIT, 1 = HELP etc.). In particular if the input
/// is not a valid command, the function returns -1 = NOTHING
///
/// @param command_input the command line that was input by the user
///
/// @return command index
//
Command_index getCommandIndex(char command_input[COMMAND_BUFFER_SIZE]) {
  int current_defined_parameter_count = 0;
  char current_defined_command_string[COMMAND_BUFFER_SIZE];
  Command_index command_index = NOTHING;

  for (Command_index command_counter = QUIT; command_counter < MAX_COMMAND_COUNT; command_counter++) {
//    current_defined_parameter_count = COMMAND_PARAMETER_COUNTS[command_counter];
//    strcpy(current_defined_command_string, COMMAND_STRINGS[command_counter]);

    if (command_counter == RENAME) {
      if (compareCommandFirstParameter(command_input, current_defined_command_string) == true &&
          getParameterCount(command_input) >= current_defined_parameter_count) {
        command_index = command_counter;
        break;
      }
    }

    if (command_counter == DRAW) {
      if (compareCommandFirstParameter(command_input, "DRAW") == true && getParameterCount(command_input) >= 2 &&
          getParameterCount(command_input) <= 3) {
        command_index = command_counter;
        break;
      }
    }
    if (checkParameterCount(command_input, current_defined_parameter_count) == true &&
        compareCommandFirstParameter(command_input, current_defined_command_string) == true) {
      command_index = command_counter;
      break;
    } else if (checkParameterCount(command_input, current_defined_parameter_count) == false &&
               compareCommandFirstParameter(command_input, current_defined_command_string) == true) {
      printf(WRONG_PARAMETER_COUNT_MESSAGE);
      break;
    }
  }
  return command_index;
}

#endif //COMMANDHANDLING_H
