
#include "headers/draw.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void draw(Person **persons, int id, char *filename, int *array_size) {
  if (filename) {
    FILE *dot_file;
    dot_file = fopen(filename, "w");
    // TODO: error Handling
    if (dot_file == NULL) {
      return;
    }

    fprintf(dot_file, "diagraph FamilyTree\n{\n");
    Person *current = getPersonById(persons, id, array_size);

    while (current != NULL) {
      if (current->parent1_ != NULL) {
        fprintf(dot_file, "\"%s [%d]\" -> \"%s [%d]\";\n", current->name_, current->id_,
                current->parent1_->name_, current->parent1_->id_);
      }

      if (current->parent2_ != NULL) {
        fprintf(dot_file, "\"%s [%d]\" -> \"%s [%d]\";\n", current->name_, current->id_,
                current->parent2_->name_, current->parent2_->id_);
      }

      if (current->parent1_ != NULL) {
        current = current->parent1_;
      } else if (current->parent2_ != NULL) {
        current = current->parent2_;
      } else {
        current = NULL;
      }
    }

    fprintf(dot_file, "}\n");
    fclose(dot_file);
    return;
  }
  Person *current = getPersonById(persons, id, array_size);
  while (current != NULL) {
    if (current->parent1_ != NULL) {
      printf("\"%s [%d]\" -> \"%s [%d]\";\n", current->name_, current->id_,
             current->parent1_->name_, current->parent1_->id_);
    }

    if (current->parent2_ != NULL) {
      printf("\"%s [%d]\" -> \"%s [%d]\";\n", current->name_, current->id_,
             current->parent2_->name_, current->parent2_->id_);
    }

    if (current->parent1_ != NULL) {
      current = current->parent1_;
    } else if (current->parent2_ != NULL) {
      current = current->parent2_;
    } else {
      current = NULL;
    }
  }
}

void drawAll(void) {
  return;
}


char **splitStringToArray(char *input, char *delimiter) {
  char *temp = strtok(input, delimiter);
  char **result = NULL;
  int i = 0;
  while (temp != NULL) {
    result = realloc(result, sizeof(char *) * (i + 1));
    if (result == NULL)
      return NULL;
    result[i] = malloc(sizeof(char) * (strlen(temp) + 1));
    if (result[i] == NULL)
      return NULL;
    strcpy(result[i], temp);
    temp = strtok(NULL, delimiter);
    i++;
  }

  return result;
}

int isInteger(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isdigit(str[i]))
      return 0;
  }
  return 1;
}
// TODO: when person is leaf node

void drawCommandHandler(char *input, Person **persons, int *array_size) {
  char **input_;
  input_ = splitStringToArray(input, " ");

  char *test = malloc(100);
  strcpy(test, input_[1]);

  if (isInteger(input_[1])) {
    draw(persons, atoi(input_[1]), NULL, array_size);
  } else {
    drawAll();
  }

  free(input_);
  free(test);
}
