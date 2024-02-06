#include <stdio.h>
#include <stdlib.h>

#include "person.h"

#ifndef FREE_H
#define FREE_H

//---------------------------------------------------------------------------------------------------------------------
///
/// This function frees an "Person**"-Array. The old pointers get set to NULL.
///
/// @param person the person-array
/// @param array_size the size of the array
///
//
void freePersonArray(Person** person, int array_size)
{
  for (int i = 0; i < array_size; i++)
  {
    free(person[i]);
    person[i] = NULL;
  }
  free(person);
  person = NULL;
}

#endif //FREE_H
