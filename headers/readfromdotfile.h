#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "person.h"

#ifndef READFROMDOTFILE_H
#define READFROMDOTFILE_H

#define FIRST_READABLE_LINE 21
#define BUFFER_SIZE 100

#define NOT_FOUND -1

#define MAGIC_NUMBER "digraph FamilyTree\n"

#define CURVED_BRACKET_CLOSED "}"
#define SQUARED_BRACKET_OPEN "["
#define SQUARED_BRACKET_CLOSED "]"
#define QUOTATION_MARK "\""
#define SPACE ' '
#define NULL_BYTE '\0'

//---------------------------------------------------------------------------------------------------------------------
///
/// This function takes a string and terminates the last character (in the case it is a space character) and sets it to
/// to zero. The buffer of string has to be 100.
///
/// @param string the string to be formated
///
/// @return formated string
//
char* terminateSpaceCharacter(char string[BUFFER_SIZE])
{
  int i = 0;
  while (string[i] != SPACE || string[i + 1] != NULL_BYTE)
  {
    i++;
  }
  string[i] = NULL_BYTE;
  return string;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function checks if a given person via ID does already exist in the person-array. The return values are TRUE (1)
/// and FALSE (0).
///
/// @param person the person-array
/// @param array_size the size of the array
/// @param current_id the id of the searched player
///
/// @return TRUE/FALSE
//
int checkIfPersonExists(Person** person, int array_size, int current_id)
{
  for (int i = 0; i < array_size; i++)
  {
    if (person[i]->id_ == current_id)
      return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function gets the two persons from the current line/string and saves them into a dynamical created array. It
/// uses several helper functions to get the formated strings and also checks if the given person already exists.
///
/// @param person the person-array
/// @param line the current line
/// @param array_size the size of the array (per reference so it updates when new members get initialized)
///
/// @return new person-array or NULL in case of a memory-error
//
Person** getPersonsFromLine(Person** person, FILE* dot_file, char line[BUFFER_SIZE], int* array_size)
{
  char person_name[BUFFER_SIZE];
  char person_id_as_string[BUFFER_SIZE];
  int person_id = 0;

  for (int i = 0; i < 2; i++)
  {
    if (i == 0)
    {
      strtok(line, QUOTATION_MARK);
    }
    else
    {
      strtok(NULL, QUOTATION_MARK);
    }
    strcpy(person_name, strtok(NULL, SQUARED_BRACKET_OPEN));
    terminateSpaceCharacter(person_name);
    strcpy(person_id_as_string, strtok(NULL, QUOTATION_MARK));
    person_id = atoi(person_id_as_string);

    if (checkIfPersonExists(person, *array_size, person_id) == false)
    {
      *array_size = *array_size + 1;
      person = realloc(person, sizeof(Person*) * *array_size);
      if (person == NULL)
      {
        return NULL;
      }
      person[*array_size - 1] = malloc(sizeof(Person));
      if (person[*array_size - 1] == NULL)
      {
        return NULL;
      }

      person[*array_size - 1]->id_ = person_id;
      strcpy(person[*array_size - 1]->name_, person_name);
      person[*array_size - 1]->parent1_ = NULL;
      person[*array_size - 1]->parent2_ = NULL;
    }
  }
  return person;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function saves all persons from a ".dot"-file into the a dynamical array.
///
/// @param dot_file the file in the ".dot"-format
/// @param array_size the size of the array (per reference so it updates when new members get initialized)
///
/// @return person-array or NULL in case of a memory-error
//
Person** readPersonsFromDotFile(FILE* dot_file, int* array_size)
{
  char current_line[BUFFER_SIZE];
  fseek(dot_file, FIRST_READABLE_LINE, SEEK_SET);
  Person** person = NULL;

  while (1)
  {
    fgets(current_line, BUFFER_SIZE, dot_file);
    if (strncmp(current_line, CURVED_BRACKET_CLOSED, 1) == 0)
    {
      break;
    }
    person = getPersonsFromLine(person, dot_file, current_line, array_size);
    if (person == NULL)
    {
      return NULL;
    }
  }
  return person;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function checks of the currently defined magic-number (here in particular "FamilyTree") is existing at the
/// beginning of the ".dot"-file. The functions return either TRUE (1) or FALSE (0).
///
/// @param dot_file the file in the ".dot"-format
///
/// @return TRUE/FALSE
//
int checkMagicNumber(FILE* dot_file)
{
  char line[BUFFER_SIZE];
  fgets(line, BUFFER_SIZE, dot_file);
  if (strcmp(MAGIC_NUMBER, line) == 0)
  {
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function gets the index of a person in the array via the ID.
///
/// @param person the person-array
/// @param id the ID of the searched person
/// @param array_size the size of the array
///
/// @return the index in the array
//
int getIndexWithId(Person** person, int id, int array_size)
{
  int index = 0;
  while (index < array_size)
  {
    if (person[index]->id_ == id)
    {
      return index;
    }
    index++;
  }
  return NOT_FOUND;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function gets the amount of parents a person can have. The Maximum is two.
///
/// @param person the person-array
/// @param id the ID of the person
/// @param array_size the size of the array
///
/// @return amount of parents
//
int getAmountofParents(Person** person, int id, int array_size)
{
  int index = getIndexWithId(person, id, array_size);

  if (person[index]->parent1_ == NULL && person[index]->parent2_ == NULL)
    return 0;
  if (person[index]->parent1_ != NULL && person[index]->parent2_ == NULL)
    return 1;
  else
    return 2;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function reads the relation of two people in a line/string and connects them via the struct.
/// (parent1 and parent2)
///
/// @param person the person-array
/// @param line currently checked line
/// @param array_size the size of the array
///
/// @return TRUE/FALSE
//
int getPersonsRelated(Person** person, char line[BUFFER_SIZE], int array_size)
{
  char child_id_as_string[BUFFER_SIZE];
  char parent_id_as_string[BUFFER_SIZE];

  strtok(line, SQUARED_BRACKET_OPEN);
  strcpy(child_id_as_string, strtok(NULL, SQUARED_BRACKET_CLOSED));
  strtok(NULL, SQUARED_BRACKET_OPEN);
  strcpy(parent_id_as_string, strtok(NULL, SQUARED_BRACKET_CLOSED));
  int child_id = atoi(child_id_as_string);
  int parent_id = atoi(parent_id_as_string);

  int amount_of_parents = getAmountofParents(person, child_id, array_size);
  switch (amount_of_parents)
  {
    case 0:
      person[getIndexWithId(person, child_id, array_size)]->parent1_ =
      person[getIndexWithId(person, parent_id, array_size)];
      break;

    case 1:
      person[getIndexWithId(person, child_id, array_size)]->parent2_ =
      person[getIndexWithId(person, parent_id, array_size)];
      break;

    default:
      return false;
  }
  return true;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// This function function reads all relations/connections from a ".dot"-file and saves them in the array
/// via the struct.
/// if a person has more than two parents the function return FALSE (0) else it returns TRUE (1).
///
/// @param dot_file the file in the ".dot"-format
/// @param person the person-array
/// @param array_size the size of the array
///
/// @return TRUE/FALSE
//
int getRelationsFromDotFile(FILE* dot_file, Person** person, int array_size)
{
  char current_line[BUFFER_SIZE];
  fseek(dot_file, FIRST_READABLE_LINE, SEEK_SET);

   while (1)
  {
    fgets(current_line, BUFFER_SIZE, dot_file);
    if (strncmp(current_line, CURVED_BRACKET_CLOSED, 1) == 0)
    {
      break;
    }
    int return_value = getPersonsRelated(person, current_line, array_size);
    if (return_value == false)
    {
      return false;
    }
  }
  return true;
}

#endif //READFROMDOTFILE_H
