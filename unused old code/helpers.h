//------------------------------------------------------------------------------
// helpers.h
//
// Defines little helper functions.
// Contains forward declarations for helper.impl.c
// This file is copied from my implementation of Assignment 2.
//
// Group: Elias Komar
//
// Author: 12315923
//------------------------------------------------------------------------------
//

#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>     // malloc, free
#include <stdint.h>     // integer range
#include <ctype.h>      // character manipulation
#include <stdbool.h>    // bool type
#include <string.h>     // string manipulation
#include <stdio.h>      // printf
#include "status.h"     // status codes

char* openAndGetString(const char* path, StatusBuffer* status_buffer, MemoryAllocator* memory_allocator);
char* getFileAsString(FILE* file, StatusBuffer* status_buffer, MemoryAllocator* memory_allocator);
char* getUserInput(StatusBuffer* status_buffer, MemoryAllocator* memory_allocator);
bool strEqualsInsensitive(const char* str1, const char* str2);
size_t strLength(const char* str);
size_t strLineLength(const char* str);
void strToUpper(const char* source, char* destination);
void removeNL(char* str);
bool betweenIncl(const int x, const int lower, const int upper);
size_t to1DIndex(size_t row, size_t col, size_t num_cols);
void resetCharArray(char* array, size_t size);
int numDigits(int n);
bool isEndOfLine(char c);
void resetCharArray(char* array, size_t size);
int compareInts(const void* a, const void* b);
int compareStatus(const void* a, const void* b);
void clearScanBuffer(void);

//------------------------------------------------------------------------------
///
/// Opens a file and returns its content as a string.
///
/// @param path the path to the file
///
/// @return the file as a string on heap if opening and reading was successful,
///         else NULL
//
char* openAndGetString(const char* path, StatusBuffer* status_buffer, MemoryAllocator* memory_allocator)
{
  FILE* file = fopen(path, "r");
  if (file == NULL) 
  {
    addStatusFormatted(status_buffer, memory_allocator, CANNOT_OPEN_FILE, path);

    return NULL;
  }

  char* file_content = getFileAsString(file, status_buffer, memory_allocator);
  fclose(file);

  return file_content;
}

//------------------------------------------------------------------------------
///
/// Reads a file into a string (doesn't close the file).
///
/// @param file the file to read
///
/// @return the file as a string on heap
//
char* getFileAsString(FILE* file, StatusBuffer* status_buffer, MemoryAllocator* memory_allocator) 
{
  char* buffer = 0;
  long length;

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);

  buffer = myMalloc(length + 1, memory_allocator);//, NULL);
  if (buffer == NULL)
  {
    addStatus(status_buffer, OUT_OF_MEMORY);
    return NULL;
  }

  fread(buffer, 1, length, file);

  return buffer;
}

char* getUserInput(StatusBuffer* status_buffer, MemoryAllocator* memory_allocator)
{
  char* input = (char*) myMalloc(INPUT_BUFFER_SIZE * sizeof(char), memory_allocator);
  if (input == NULL)
  {
    addStatus(status_buffer, OUT_OF_MEMORY);
    return NULL;
  }

  bool buffer_large_enough = false;
  int size = 0;
  int current_max_size = INPUT_BUFFER_SIZE;
  while (!buffer_large_enough)
  {
    char current_char = getchar();
    if (current_char == '\n' || current_char == '\0')
    {
      // end of string
      input[size] = '\0';
      buffer_large_enough = true;
      break;
    }

    if (size >= current_max_size)
    {
      // buffer too small
      current_max_size += INPUT_CHUNK_SIZE;
      input = (char*) realloc(input, current_max_size * sizeof(char));
      if (input == NULL)
      {
        addStatus(status_buffer, OUT_OF_MEMORY);
        return NULL;
      }
    }

    input[size] = current_char;
    size++;
  }

  return input;
}

//------------------------------------------------------------------------------
///
/// Checks if two strings are equal *without* case sensitivity.
///
/// @param str1 first string
/// @param str2 second string
///
/// @return true if the string are equal
//
bool strEqualsInsensitive(const char* str1, const char* str2)
{
  size_t length1 = strLineLength(str1);
  size_t length2 = strLineLength(str2);

  if (length1 != length2)
  {
    return false;
  }

  bool equals = true;

  for (size_t i = 0; i < length1; i++)
  {
    equals &= tolower(str1[i]) == tolower(str2[i]);
  }

  return equals;
}

//------------------------------------------------------------------------------
///
/// Counts the number of character in a string.
///
/// @param str string used for counting
///
/// @return the length of str.
//
size_t strLength(const char* str)
{
  size_t length = 0;

  while(str[length] != '\0')
  {
    length++;
  }

  return length;
}

//------------------------------------------------------------------------------
///
/// Counts the number of character in the first line of a string.
/// The first line means it counts until '\n' or '\0'.
///
/// @param str string used for counting
///
/// @return the length of str in a line.
//
size_t strLineLength(const char* str)
{
  size_t length = 0;

  while(str[length] != '\0' && str[length] != '\n')
  {
    length++;
  }

  return length;
}

//------------------------------------------------------------------------------
///
/// Copies the charactesr of source to destination 
/// and makes each letter uppercase.
///
/// @param source source string
/// @param destination the destination string
//
void strToUpper(const char* source, char* destination)
{
  size_t index = 0;

  while(source[index] != '\0')
  {
    destination[index] = toupper(source[index]);
    index++;
  }
}

//------------------------------------------------------------------------------
///
/// Removes the last character of a string if it is '\n'.
///
/// @param str source string
//
void removeNL(char* str)
{
  if(str[strLength(str)-1] == '\n')
  {
    str[strLength(str)-1] = '\0';
  }
}

//------------------------------------------------------------------------------
///
/// Checks if a number is inbetween certain bounds, including those bounds.
/// For example 2 would be inbetween 2 and 4 in this function.
///
/// @param x number to check
/// @param lower lower bound
/// @param upper upper bound
///
/// @return true if x is inbetween lower and upper
//
bool betweenIncl(const int x, const int lower, const int upper)
{
  return lower <= x && x <= upper;
}

//------------------------------------------------------------------------------
///
/// Converts a 2D Array index in (row, col) format to a onedimensional index.
///
/// @param row row of 2D Array
/// @param col col of 2D Array
/// @param num_cols number of columns in the 2D Array
///
/// @return the onedimensional equivalent
//
size_t to1DIndex(size_t row, size_t col, size_t num_cols)
{
  return row * num_cols + col;
}

//------------------------------------------------------------------------------
///
/// Sets all characters in an array to '\0'.
/// 'size' should be the size of the array.
///
/// @param array array to be cleared
/// @param size size of the array
//
void resetCharArray(char* array, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    array[i] = '\0';
  }
}

//------------------------------------------------------------------------------
///
/// Finds the number of digits for the given number.
/// This code was found here: 
/// https://stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c
///
/// @param number given number
///
/// @return number of digits of 'number'
//
int numDigits(int number)
{
  int num_digits = 1;

  if (number < 0) 
  {
    number = -number;
  }

  while (number > 9) 
  {
      number /= 10;
      num_digits++;
  }

  return num_digits;
}

//------------------------------------------------------------------------------
///
/// Checks if a character is the end of a line.
/// End-Of-Line also means string-terminator.
///
/// @param c character to be checked
///
/// @return true if character is end of a line or string.
//
bool isEndOfLine(char c)
{
  return c == '\0' || c == '\n';
}

//------------------------------------------------------------------------------
///
/// Comparator for two integers, NULL first.
///
/// @param a number 1
/// @param b number 2
///
/// @return 1 if a is larger then b
///         0 if a is equal to b
///         -1 if a is smaller then b
//
int compareInts(const void* a, const void* b)
{
  if (a == NULL && b != NULL)
  {
    return -1;
  }
  
  if (a != NULL && b == NULL)
  {
    return 1;
  }

  if (a == b)
  {
    return 0;
  }

  const int int_a = * ((int*) a);
  const int int_b = * ((int*) b);

  if (int_a == int_b) 
  {
    return 0;
  }

  if (int_a < int_b) 
  {
    return -1;
  }

  return 1;
}

//------------------------------------------------------------------------------
///
/// Comparator for two status codes, nulls last.
///
/// @param a status code 1
/// @param b status code 2
///
/// @return 1 if a is larger then b
///         0 if a is equal to b
///         -1 if a is smaller then b
//
int compareStatus(const void* a, const void* b)
{
  const Status* status_A = (const Status*)a;
  const Status* status_B = (const Status*)b;

  if (status_A == NULL && status_B != NULL)
  {
    return 1;
  }
  
  if (status_A != NULL && status_B == NULL)
  {
    return -1;
  }

  if (status_A == NULL && status_B == NULL)
  {
    return 0;
  }

  return (-1) * compareInts(&status_A->code_, &status_B->code_);
}

//------------------------------------------------------------------------------
///
/// Clears the scan buffer of stdin.
///
//
void clearScanBuffer(void)
{
  int clear_buffer_temporary;
  while ((clear_buffer_temporary = getchar()) != '\n' && clear_buffer_temporary != EOF)
  { 
    ;
  }
}

#endif // HELPERS_H
