//------------------------------------------------------------------------------
// status.h
//
// Defines the Status struct and status buffer.
// 
// Group: Elias Komar
//
// Author: 12315923
//------------------------------------------------------------------------------
//

#ifndef STATUS_H
#define STATUS_H

#include <stdarg.h>             // variable arguments
#include <stdio.h>              // printf, vprintf
#include <stdbool.h>            // bool type
#include <stdlib.h>             // qsort

#define MAX_MESSAGE_LENGTH 100
#define MAX_PATH_LENGTH 4096
#define MAX_STATUS_BUFFER_SIZE 10

typedef struct _Status_ 
{
  bool is_init_;                        // whether the status is initialized
  int code_;                            // return code
  char message_[MAX_MESSAGE_LENGTH];    // message
  bool is_formatted_;                   // whether the message contains format string (e.g. %s)
  char* formatted_msg_;                 // formatted message
} Status;

// Here for import safety
#include "memory_allocator.h"  // MemoryAllocator

// Just a shorthand for a status array
typedef struct _StatusBuffer_
{
  Status buffer_[MAX_STATUS_BUFFER_SIZE];   // buffer of x status codes
  int num_elements_;                        // number of elements in the buffer
} StatusBuffer;

StatusBuffer* createStatusBuffer(MemoryAllocator* memory_allocator);
StatusBuffer* addStatus(StatusBuffer* buffer, Status status);
StatusBuffer* addStatusFormatted(StatusBuffer* buffer, MemoryAllocator* memory_allocator, Status status, ...);
void printStatusBuffer(StatusBuffer* buffer);
void sortBuffer(StatusBuffer* buffer);
int showStatusBuffer(StatusBuffer* buffer);
int showStatus(const Status* status);
void resetStatusBuffer(StatusBuffer* buffer);
bool isFull(StatusBuffer* buffer);
bool isError(Status* status);
bool isBufferError(StatusBuffer* buffer);
void freeStatusBuffer(void** buffer);
int compareInts(const void* a, const void* b);
int compareStatus(const void* a, const void* b);

// Here, because of import order issues
#include "memory_allocator.h"   // MemoryAllocator, myAlloc
#include "string.h"             // strcpy, strlen

//------------------------------------------------------------------------------
///
/// Creates a status buffer on the heap.
///
/// @return empty Statusbuffer if successful,
///         else NULL
//
StatusBuffer* createStatusBuffer(MemoryAllocator* memory_allocator)
{
  StatusBuffer* buffer = (StatusBuffer*) 
    myMalloc(sizeof(StatusBuffer), memory_allocator);//, freeStatusBuffer);

  if (buffer == NULL)
  {
    return NULL;
  }

  resetStatusBuffer(buffer);

  return buffer;
}

//------------------------------------------------------------------------------
///
/// Adds a status to the buffer.
/// If the buffer is full, all but the highest status will be removed.
///
/// @param buffer the buffer to add the status to
/// @param status the status to add
///
/// @return the buffer if successful,
///         else NULL
//
StatusBuffer* addStatus(StatusBuffer* buffer, Status status)
{
  return addStatusFormatted(buffer, NULL, status);
}

//------------------------------------------------------------------------------
///
/// Adds a status to the buffer.
/// If the buffer is full, all but the highest status will be removed.
/// Creates some memory usage errors...
///
/// @param buffer the buffer to add the status to
/// @param memory_allocator pointer to the memory allocator
/// @param status the status to add
///
/// @return the buffer if successful,
///         else NULL
//
StatusBuffer* addStatusFormatted(StatusBuffer* buffer, MemoryAllocator* memory_allocator, Status status, ...)
{
  if (buffer == NULL)
  {
    return NULL;
  }

  // "Conditional jump or move depends on uninitialised value(s)"
  // habe aber keine Ahnung wieso.
  if (isFull(buffer))
  {
    Status tmp_highest_status = buffer->buffer_[0];
    resetStatusBuffer(buffer);
    buffer->buffer_[0] = tmp_highest_status;
  }

  for (int i = 0; i < MAX_STATUS_BUFFER_SIZE; i++)
  {
    if (!buffer->buffer_[i].is_init_)
    {
      buffer->buffer_[i] = status;
      buffer->buffer_[i].is_init_ = true;

      if (memory_allocator == NULL)
      {
        break;
      }

      // format message with args and store the formatted str on the heap
      va_list args;
      va_start(args, status);
      char arg_buffer[MAX_MESSAGE_LENGTH + MAX_PATH_LENGTH];
      vsprintf(arg_buffer, status.message_, args);
      va_end(args);

      buffer->buffer_[i].formatted_msg_ = (char*) myMalloc(strlen(arg_buffer) + 1, memory_allocator);
      if (buffer->buffer_[i].formatted_msg_ == NULL)
      {
        return NULL;
      }
      strcpy(buffer->buffer_[i].formatted_msg_, arg_buffer);

      break;
    }
  }

  sortBuffer(buffer);
  buffer->num_elements_++;

  return buffer;
}

void printStatusBuffer(StatusBuffer* buffer)
{
  for (int i = 0; i < MAX_STATUS_BUFFER_SIZE; i++)
  {
    if (!buffer->buffer_[i].is_init_)
    {
      printf("NULL\n");
      continue;
    }

    printf("%d: %d - %s\n", i, buffer->buffer_[i].code_, buffer->buffer_[i].message_);
  }
}

//------------------------------------------------------------------------------
///
/// Sorts the buffer by status code.
///
/// @param buffer the buffer to sort
//
void sortBuffer(StatusBuffer* buffer)
{
  qsort(buffer->buffer_, MAX_STATUS_BUFFER_SIZE, sizeof(Status), compareStatus);
}

//------------------------------------------------------------------------------
///
/// prints the status message and returns the status code of the first element
/// in the buffer, which is the one with the highest status code.
///
/// @param status the status to print
///
/// @return the status code
//
int showStatusBuffer(StatusBuffer* buffer)
{
  //printf("buffer args val: %X\n", *buffer->buffer_[0].args_);
  return showStatus(&buffer->buffer_[0]);
}

//------------------------------------------------------------------------------
///
/// prints the status message and returns the status code.
///
/// @param status the status to print
///
/// @return the status code
//
int showStatus(const Status* status)
{
  if (status->is_formatted_)
  {
    printf("%s\n", status->formatted_msg_);
  } else {
    printf("%s\n", status->message_);
  }

  return status->code_;
}

//------------------------------------------------------------------------------
///
/// Resets the status.
///
/// @param status the status to reset
//
void resetStatus(Status* status)
{
  status->is_init_ = false;
  status->code_ = 0;
  status->message_[0] = '\0';
  status->is_formatted_ = false;
  status->formatted_msg_ = NULL;
}

//------------------------------------------------------------------------------
///
/// Resets the status buffer.
///
/// @param buffer the buffer to reset
//
void resetStatusBuffer(StatusBuffer* buffer)
{
  for (int i = 0; i < MAX_STATUS_BUFFER_SIZE; i++)
  {
    resetStatus(&buffer->buffer_[i]);
  }
}

//------------------------------------------------------------------------------
///
/// Checks if the buffer is full.
///
/// @param buffer the buffer to check
///
/// @return true if the buffer is full, else false
//
bool isFull(StatusBuffer* buffer)
{
  if (buffer == NULL)
  {
    return false;
  }

  return buffer->num_elements_ == MAX_STATUS_BUFFER_SIZE;
}

//------------------------------------------------------------------------------
///
/// Checks if the status contains an error.
///
/// @param status the status to check
///
/// @return true if the status contains an error, else false
//
bool isError(Status* status)
{
  return status->code_ != 0;
}

//------------------------------------------------------------------------------
///
/// Checks if the buffer contains an error.
///
/// @param buffer the buffer to check
///
/// @return true if the buffer contains an error, else false
//
bool isBufferError(StatusBuffer* buffer)
{
  return isError(&buffer->buffer_[0]);
}

//------------------------------------------------------------------------------
///
/// Frees a status buffer from heap and sets it to NULL.
///
/// @param buffer the buffer to free
//
void freeStatusBuffer(void** buffer)
{
  // The "garbage collector" will free the formatted_msg_ strings

  free(*buffer);
  *buffer = NULL;
}

#endif // STATUS_H
