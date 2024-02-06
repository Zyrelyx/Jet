
#include "person.h"

#ifndef VSPWS23_059_DRAW_H
#define VSPWS23_059_DRAW_H

void draw(Person **persons, int id, char *filename, int *array_size);

void drawAll(void);

char **splitStringToArray(char *input, char *delimiter);

void drawCommandHandler(char *input, Person **persons, int *array_size);

#endif //VSPWS23_059_DRAW_H
