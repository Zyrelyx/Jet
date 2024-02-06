#include "headers/person.h"

Person *getPersonById(Person **persons, int id, int *person_array_size) {
  for (int i = 0; i < *person_array_size; i++) {
    if (persons[i]->id_ == id)
      return persons[i];
  }
  return NULL;
}

int getHighestId(Person *persons, int *person_array_size) {
  int max_id = 0;
  for (int index = 0; index < *person_array_size; index++) {
    if (persons[index].id_ > max_id)
      max_id = persons[index].id_;
  }
  return max_id;
}

//void sortArray() {
//
//}
