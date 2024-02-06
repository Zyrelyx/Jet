#include <stddef.h>

#ifndef PERSON_H
#define PERSON_H

typedef struct _Person_ {
  int id_;
  char name_[100];
  struct _Person_ *parent1_;
  struct _Person_ *parent2_;
} Person;

Person *getPersonById(Person **persons, int id, int *person_array_size);

int getHighestId(Person *person, int *person_array_size);

#endif // PERSON_H
