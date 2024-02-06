//---------------------------------------------------------------------------------------------------------------------
// assignment.c
//
// This is a familytree-tool for creating and/or working on an already existing familytree saved in a ".dot" file.
// The file can modified in several diffrent ways such as add new members, deleting members, pruning the family tree,
// saving/drawing it into the ".dot"-file, get the relationship status between two members and connecting two members as
// parent and child.
//
// Group: 59
//
// Author: 12311195, <Steini>, <Paul>
//---------------------------------------------------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "headers/person.h"
#include "headers/readfromdotfile.h"
#include "headers/help.h"
#include "headers/userinput.h"
#include "headers/free.h"
#include "headers/commandhandling.h"
#include "headers/rename.h"
#include "headers/draw.h"

#define INVALID_FILE_MESSAGE "Error: Invalid input file content.\n"
#define OUT_OF_MEMORY_MESSAGE "Error: Out of memory.\n"
#define WRONG_CMDLINE_MESSAGE "Usage: ./assignment [optional-input-file]\n"
#define CANNOT_OPEN_FILE_MESSAGE "Error: Cannot open file.\n"

#define WELCOME_MESSAGE "Welcome to the VSP Family Tree!\n\n"

enum _ReturnValues_ {
  SUCCESSFUL,
  WRONG_CMDLINE,
  OUT_OF_MEMORY,
  CANNOT_OPEN_FILE,
  INVALID_FILE
};

int doCommand(Person **person, int *array_size) {
  char command_input[BUFFER_SIZE];
  Command_index command_index = NOTHING;

  while (1) {
    getUserInput(command_input, BUFFER_SIZE);
    command_index = getCommandIndex(command_input);

    switch (command_index) {
      case QUIT:return QUIT;

      case HELP:help();
        break;

      case RENAME:renamePerson(command_input, person, *array_size);
        break;

      case NOTHING:break;

      case DRAW: drawCommandHandler(command_input, person, array_size);
        break;
    }
  }
}

int main(int argc, char *argv[]) {
  Person **person = NULL;
  int person_array_size = 0;

  if (argc > 2) {
    printf(WRONG_CMDLINE_MESSAGE);
    return WRONG_CMDLINE;
  }

  FILE *dot_file = NULL;
  if (argc == 2) {
    dot_file = fopen(argv[1], "r");
    if (dot_file == NULL) {
      printf(CANNOT_OPEN_FILE_MESSAGE);
      return CANNOT_OPEN_FILE;
    }
    if (checkMagicNumber(dot_file) == false) {
      printf(INVALID_FILE_MESSAGE);
      return INVALID_FILE;
    }
    person = readPersonsFromDotFile(dot_file, &person_array_size);
    if (person == NULL) {
      printf(OUT_OF_MEMORY_MESSAGE);
      freePersonArray(person, person_array_size);
      return OUT_OF_MEMORY;
    }
    bool relations_return_value = getRelationsFromDotFile(dot_file, person, person_array_size);
    if (relations_return_value == false) {
      freePersonArray(person, person_array_size);
      printf(INVALID_FILE_MESSAGE);
      return INVALID_FILE;
    }
  }

  printf(WELCOME_MESSAGE);
  int command_return_value = doCommand(person, &person_array_size);
  if (command_return_value == QUIT) {
    freePersonArray(person, person_array_size);
    fclose(dot_file);
    return SUCCESSFUL;
  }
}
