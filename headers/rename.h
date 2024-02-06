#include <stdio.h>
#include <string.h>
#include "readfromdotfile.h"
#include "person.h"

#ifndef RENAME_H
#define RENAME_H

#define ID_NOT_FOUND_MESSAGE "Error: ID [%d] does not exist. Use 'list' to find all available persons.\n"
#define RENAME_SUCCESSFUL_MESSAGE "Renaming %s [%d] to %s [%d] was successful!\n"

//---------------------------------------------------------------------------------------------------------------------
///
/// This function is for renaming a person. The person is that has to be changed is searched via ID.
///
/// @param command_input the command line that was input by the user
/// @param person the person-array
/// @param array_size the size of the array
///
//
void renamePerson(char command_input[BUFFER_SIZE], Person** person, int array_size)
{
  char* new_name = NULL;
  char old_name[BUFFER_SIZE];
  char* id_as_string = NULL;
  int id = 0;
  int person_array_index = 0;

  strtok(command_input, " ");
  id_as_string = strtok(NULL, " ");
  id = atoi(id_as_string);
  new_name = strtok(NULL,"\0");

  person_array_index = getIndexWithId(person, id, array_size);
  if (person_array_index == NOT_FOUND)
  {
    printf(ID_NOT_FOUND_MESSAGE, id);
    return;
  }

  strcpy(old_name, person[person_array_index]->name_);
  strcpy(person[person_array_index]->name_, new_name);
  printf(RENAME_SUCCESSFUL_MESSAGE, old_name, id, new_name, id);
}

#endif // RENAME_H
