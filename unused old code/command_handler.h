//------------------------------------------------------------------------------
// command_handler.h
//
// Implementations of the command handler and command structs.
//
// Group: Elias Komar
//
// Author: 12315923
//------------------------------------------------------------------------------
//

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdio.h>              // printf
#include <stdlib.h>             // malloc
#include <string.h>             // strcmp
#include "memory_allocator.h"   // MemoryAllocator
#include "status.h"             // Status
#include "commands.h"           // Command
#include "helpers.h"            // helpers
#include "globals.h"            // globals

#define MAX_CMD_CHAR_SIZE 100      // The max of chars in a arg of a command
#define EXPECTED_NUM_ARGS_MAX 50  // The max number of arguments
#define INITIAL_CMD_ARRAY_SIZE 10  // The initial size of the command array
#define CMD_ARRAY_CHUNK_SIZE 5     // The chunk size to increase the array by

typedef struct _CommandHandler_ 
{
  Command* commands_;          // The list of commands, on heap
  int num_cmds_;               // The number of commands in the list
  int size_;                   // The maximum size of the list
} CommandHandler;

Command* findCommand(CommandHandler* handler, StatusBuffer* status_buffer, 
  MemoryAllocator* allocator, char command_context[]);
void* executeCommand(Command* command, Context* context);
Command* findAndExecCommand(CommandHandler* handler, Context* context,
  StatusBuffer* status_buffer, MemoryAllocator* allocator, char command_context[]);
CommandHandler* createCommandHandler(StatusBuffer* status_buffer, MemoryAllocator* allocator);
void* addCommand(CommandHandler* handler, StatusBuffer* status_buffer, Command command);

//------------------------------------------------------------------------------
///
/// Searches for a command in the command handler.
/// If the command was found, it returns the command.
/// If the number of parameters is invalid, it adds an INVALID_ARGS status to
/// the status buffer.
///
/// @param handler the command handler
/// @param status_buffer the status buffer
/// @param command_context the user input
///
/// @return NULL if memory error, else the command
//
Command* findCommand(CommandHandler* handler, StatusBuffer* status_buffer, 
  MemoryAllocator* allocator, char command_context[])
{
  char command_strcpy[strlen(command_context) + 1];
  strcpy(command_strcpy, command_context);

  char* command = strtok(command_strcpy, " ");

  char* args[EXPECTED_NUM_ARGS_MAX]; 
  int num_args = 0;

  while (command != NULL)
  {
    args[num_args] = command;
    num_args++;
    command = strtok(NULL, " ");
  }

  Command* found_cmd = NULL;
  bool found = false;
  for (int i = 0; i < handler->num_cmds_; i++)
  {
    if (!strEqualsInsensitive(handler->commands_[i].command_, args[0])) 
    {
      // Not the command we are looking for
      continue;
    }

    found = true;
    found_cmd = &handler->commands_[i];
    // Check if the number of arguments is correct, the command itself counts to num_args
    if (num_args - 1 != handler->commands_[i].expected_args_) 
    {
      addStatus(status_buffer, INVALID_ARGS);
      break;
    }

    char** arr = (char**) myMalloc(sizeof(char*) * found_cmd->expected_args_, allocator);
    if (arr == NULL) 
    {
      addStatus(status_buffer, OUT_OF_MEMORY);
      return NULL;
    }

    for(int i = 0; i < found_cmd->expected_args_; i++) 
    {
      arr[i] = (char*) myMalloc(MAX_CMD_CHAR_SIZE * sizeof(char), allocator);
      if (arr[i] == NULL) 
      {
        addStatus(status_buffer, OUT_OF_MEMORY);
        return NULL;
      }

      strcpy(arr[i], args[i + 1]);
    }
    found_cmd->args_ = arr;

    break;
  }

  if (!found) 
  {
    addStatus(status_buffer, INVALID_COMMAND);
    return NULL;
  }

  return found_cmd;
}

//------------------------------------------------------------------------------
///
/// LEGACY!
/// Searches for a command in the command handler.
/// If the command was found, it executes the matching handler and returns 
/// the command with args_ set to the current args.
/// If the number of parameters is invalid, it adds an INVALID_ARGS status to
/// the status buffer.
///
/// @param handler the command handler
/// @param status_buffer the status buffer
/// @param command_context the command context
/// 
/// @return NULL if memory error, else the command with args
//
Command* findAndExecCommand(CommandHandler* handler, Context* context,
  StatusBuffer* status_buffer, MemoryAllocator* allocator, char command_context[])
{
  Command* found_cmd = findCommand(handler, status_buffer, allocator, command_context);
  
  if (found_cmd == NULL || isBufferError(status_buffer))
  {
    return NULL;  // Status already added
  }

  executeCommand(found_cmd, context);

  return found_cmd;
}

//------------------------------------------------------------------------------
///
/// Executes a command.
///
/// @param command the command to execute
///
/// @return NULL if error, else the return value of the handler
//
void* executeCommand(Command* command, Context* context)
{
  return command->handler_(command, context);
}

//------------------------------------------------------------------------------
///
/// Creates a new command handler.
///
/// @param status_buffer the status buffer
/// @param allocator the memory allocator
///
/// @return NULL if memory error, else the command handler
//
CommandHandler* createCommandHandler(StatusBuffer* status_buffer, MemoryAllocator* allocator)
{
  CommandHandler* handler = (CommandHandler*) myMalloc(sizeof(CommandHandler), allocator);
  if (handler == NULL)
  {
    addStatus(status_buffer, OUT_OF_MEMORY);
    return NULL;
  }

  handler->commands_ = (Command*) myMalloc(sizeof(Command) * INITIAL_CMD_ARRAY_SIZE, allocator);
  if (handler->commands_ == NULL)
  {
    addStatus(status_buffer, OUT_OF_MEMORY);
    return NULL;
  }

  handler->num_cmds_ = 0;
  handler->size_ = INITIAL_CMD_ARRAY_SIZE;
  return handler;
}

//------------------------------------------------------------------------------
///
/// Adds a command to the command handler.
///
/// @param handler the command handler
/// @param status_buffer the status buffer
/// @param command the command to add
///
/// @return NULL if memory error, else the command handler
//
void* addCommand(CommandHandler* handler, StatusBuffer* status_buffer, Command command)
{
  if (handler->num_cmds_ == handler->size_)
  {
    Command* commands = (Command*) realloc(handler->commands_, 
      sizeof(Command) * (handler->size_ + CMD_ARRAY_CHUNK_SIZE));

    if (commands == NULL)
    {
      addStatus(status_buffer, OUT_OF_MEMORY);
      return NULL;
    }

    handler->commands_ = commands;
    handler->size_ += CMD_ARRAY_CHUNK_SIZE;
  }

  handler->commands_[handler->num_cmds_] = command;
  handler->num_cmds_++;

  return handler;
}

#endif // COMMAND_HANDLER_H
