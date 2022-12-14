//  
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

list_t *list_alloc() 
    { 
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->head = NULL;
    return list;
    }


void list_free(list_t *l)
     {
    free(l);
    }

void list_print(list_t *l) {

      node_t *curr_node;
  curr_node = l->head;
  
  if (curr_node == NULL){
    printf("list is empty\n");
  }
  
  while (curr_node != NULL){
    printf("%d -> ", curr_node->value);
    curr_node = curr_node->next;
  }
    
}
int list_length(list_t *l) 
{ 

  node_t* curr_node = l->head;
  int length = 0;
  while (curr_node != NULL) { // the while loop will iterate through the linked list until it is NULL.
    length++;
    curr_node = curr_node->next;
  }
  return length;

 } 

void list_add_to_back(list_t *l, elem value) {
  node_t *curr_node;
  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  
  new_node->value = value;
  new_node->next = NULL;
  
  if(l->head == NULL){
    l->head = new_node;
  }
  else
  {
    curr_node = l->head;
    while(curr_node->next != NULL){
      curr_node = curr_node->next;
    }
    curr_node->next = new_node;
  }     }


void list_add_to_front(list_t *l, elem value) {

    if(!l)
    {
        printf("The list you entered does NOT exist, please try agian");
    } // Just a condition to ensure proper list is entered.

    list_t *n  = list_alloc(value);
    node_t *t  = l -> head;
    
    n -> head -> next = t;
    l -> head = n -> head;

}

void list_add_at_index(list_t *l, elem value, int index) {

    node_t* curr = l->head;
    node_t* newNode = (node_t*) malloc(sizeof(node_t));
    node_t* temp = (node_t*) malloc(sizeof(node_t));
    int count = 0;

    if (curr == NULL) 
        { 
            list_add_to_front(l, v);
         }

    while (count < index-1)
             {
            curr = curr->next;
            count++; 
             }

    if (count == index-1) 
        {
        holder = curr->next;
        curr->next = newNode;
        newNode->next = holder;
        newNode->value = v;
        }
}

elem list_remove_from_back(list_t *l) { 

  node_t* curr = l->head;
  if (curr == NULL)
    {
    return -1;
    }

  while (curr->next->next != NULL) 
    { 
        curr = curr->next;
     }

  free(curr->next);
  curr->next = NULL;
  return 0;

 }
elem list_remove_from_front(list_t *l) { return -1; }
elem list_remove_at_index(list_t *l, int index) { return -1; }

bool list_is_in(list_t *l, elem value) { return false; }
elem list_get_elem_at(list_t *l, int index) { return -1; }
int list_get_index_of(list_t *l, elem value) { return -1; }

