#include <stdio.h>

#include "list.h"

int main() {
  printf("Tests for linked list implementation\n");

  list_t * list = list_alloc();

  // Building a Linked list [1.7.3.4.8.0]

  list_add_to_back(0);
  
  return 0;

}
