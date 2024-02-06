//------------------------------------------------------------------------------
// commands.h
//
// Implements functionality for commands.
//
// Group: Elias Komar
//
// Author: 12315923
//------------------------------------------------------------------------------
//

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>        // printf
#include <string.h>       // strcmp

typedef struct _Context_
{
  // TODO: zB Lebensbaum Array
} Context;

typedef struct _Command_ 
{
  char* command_;              // The command to be executed
  int expected_args_;          // The number of arguments expected
  void* (*handler_)(Command* command, Context* context);  // The handler, should return NULL if error
  char** args_;                // The args passed to the handler for each obj
} Command;

//Example
void* handleAdd(Command* command, Context* context);

void* handleAdd(Command* command, Context* context)
{
  printf("Add command!\n");
  return context;
}

#endif // COMMANDS_H
