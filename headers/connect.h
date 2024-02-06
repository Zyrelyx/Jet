#include "person.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef VSPWS23_059_CONNECT_H
#define VSPWS23_059_CONNECT_H

void addGrandParent(Person **persons, int *person_array_size, Person *related_person, char *grandparent_type);

void setPersonParent(Person *person, Person *parent, char *parent_type);

void connect(Person **persons, int *person_array_size, Person *child_person, char *relation, Person *related_person);

bool connectCommandHandler(Person **person, int *person_array_size, int first, char *relation, int second);

#endif
