#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "headers/add.h"

void add(Person **persons, int id, char *name, int *person_array_size) {
  Person new_person = (Person) {.id_ = id};
  strncpy(new_person.name_, name, sizeof(new_person.name_));
  (*person_array_size)++;
  Person *temp = realloc(*persons, (*person_array_size) * sizeof(Person));
  if (!temp) {
    printf("Memory problem");
    return;
  }
  *persons = temp;
  (*persons)[(*person_array_size) - 1] = new_person;
}

bool addCommandHandler(char *input, Person **persons, int *person_array_size) {
  int id = *persons == NULL ? 0 : getHighestId(*persons, person_array_size) + 1;
  add(persons, id, input, person_array_size);
  return true;
}
