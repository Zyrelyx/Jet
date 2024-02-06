#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef USERINPUT_H
#define USERINPUT_H

#define COMMAND_LINE "vsp> "
#define NEW_LINE "\n"

//---------------------------------------------------------------------------------------------------------------------
///
/// This function gets user input for the command. In case the input is "ENTER" (or "\n") the command line asks again.
///
/// @param user_input the string were the input should be saved
/// @param size the size of the given string
///
//
void getUserInput(char* user_input, int size)
{
  do
  {
    printf(COMMAND_LINE);
    fgets(user_input, size, stdin);
  } while (strcmp(user_input, NEW_LINE) == 0);

  user_input[strcspn(user_input, NEW_LINE)] = '\0';
}

#endif // USERINPUT_H
