#include <stdio.h>

#ifndef HELP_H
#define HELP_H

//---------------------------------------------------------------------------------------------------------------------
///
/// This function just prints the help manual.
///
//
void help(void) {
  printf("  Available commands:\n- help: Display this help message.\n- add <person name>\n");
  printf("  Add a new person to the program\n- list\n");
  printf("  Print all individuals that have been added (or initially imported)\n- connect <id> <relation> <id>\n");
  printf("  Connect a person to another person and specify their relationship\n- rename <id> <new name>\n");
  printf("  Rename an existing person\n- delete <id>\n  Remove an existing person from the family tree\n");
  printf("- draw-all <filename>\n  Write all relationships to the terminal or a DOT file. <filename> is optional\n");
  printf("- draw <id> <filename>\n");
  printf("  Write all ancestors of a person to the terminal or a DOT file. <filename> is optional\n");
  printf("- relationship <id1> <id2>\n  Find out whether a family relationship exists between two indivduals\n");
  printf("- prune\n  Remove unkown leaf nodes from tree(s)\n- quit\n  End the program\n\n");
}

#endif // HELP_H
