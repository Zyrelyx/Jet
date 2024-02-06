
#include "headers/connect.h"

void addGrandParent(Person **persons, int *person_array_size, Person *related_person, char *grandparent_type) {
  (*person_array_size)++;
  Person *temp = realloc(*persons, (*person_array_size) * sizeof(Person));

  if (!temp) {
    //TODO Malloc error
    printf("Malloc error");
    return;
  }

  *persons = temp;

  (*persons)[*person_array_size - 1] = (Person) {
      .id_ = getHighestId(*persons, person_array_size - 1),
      .parent1_ = strcmp(grandparent_type, "gp1") == 0 ? related_person : NULL,
      .parent2_ = strcmp(grandparent_type, "gp2") == 0 ? related_person : NULL
  };

  (*persons)[*person_array_size - 1].name_[0] = '?';
  (*persons)[*person_array_size - 1].name_[1] = '\0';
}

void setPersonParent(Person *person, Person *parent, char *parent_type) {
  if (strcmp(parent_type, "parent1") == 0)
    person->parent1_ = parent;
  else if (strcmp(parent_type, "parent2") == 0)
    person->parent2_ = parent;
}

void connect(Person **person, int *person_array_size, Person *child_person, char *relation, Person *related_person) {
  char *delimiter = strchr(relation, ':');
  if (!delimiter) {
    setPersonParent(child_person, related_person, relation);
    return;
  }

  size_t len = strlen(relation);
  if (len < 11)
    return;
  printf("[%c]", *delimiter);
  *delimiter = '\0';

  char *parent_type = relation;
  char *grandparent_type = delimiter + 1;

  if (strcmp(grandparent_type, "gp1") == 0 || strcmp(grandparent_type, "gp2") == 0) {
    setPersonParent(child_person, NULL, parent_type);
    addGrandParent(person, person_array_size, related_person, grandparent_type);
    return;
  }
  // TODO error wenn nicht enthalten
}

bool connectCommandHandler(Person **persons, int *person_array_size, int first, char *relation, int second) {
  Person *first_person = getPersonById(*persons, first, person_array_size);
  Person *second_person = getPersonById(*persons, second, person_array_size);
  if (!first_person || !second_person) {
    // TODO ERRORHANDLING
    return false;
  }

  connect(persons, person_array_size, first_person, relation, second_person);

  return true;
}
