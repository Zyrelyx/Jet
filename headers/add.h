#include <stdbool.h>

#include "person.h"

#ifndef VSPWS23_059_ADD_H
#define VSPWS23_059_ADD_H

/**
 * @brief This function adds a new person to the provided persons array.
 *
 * @param persons Pointer to the array of persons.
 * @param id ID of the new person.
 * @param name Name of the new person.
 * @param person_array_size person_array_size Pointer to the size of the persons array. This value will be incremented.
 */
void add(Person **persons, int id, char *name, int *person_array_size);

/**
 * @brief This function handles the add command.
 *
 * @param input String that contains the name of the person to add.
 * @param persons Pointer to the array of persons.
 * @param person_array_size Pointer to the size of the persons array. This value might be updated.
 *
 * @return Returns true if the command is handled successfully.
 */
bool addCommandHandler(char *input, Person **persons, int *person_array_size);

#endif
