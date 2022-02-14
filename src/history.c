#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "tokenizer.h"

List* init_history()
{
  List *list = (List*) calloc(1, sizeof(List));
  if (!list) {
    fprintf(stderr, "init_history: Memory allocation error!");
    exit(EXIT_FAILURE);
  }

  return list;
}

void add_history(List *list, char *str)
{
  Item *new_item = (Item*) malloc(sizeof(Item));
  if (!new_item) {
    fprintf(stderr, "add_history: Memory allocation error!");
    exit(EXIT_FAILURE);
  }

  new_item->str = copy_str(str, strlen(str));

  Item *item = list->root;

  // List id starts at 1
  if (!item) {
    // Create root node
    list->root = new_item;
    new_item->id = 1;
    
  } else {
    // Get last item in list
    int id = 1;
    Item *prev_item;
    while (item) {
      prev_item = item;
      item = item->next;
      id++;
    }

    prev_item->next = new_item;
    new_item->id = id;
  }
}

char *get_history(List *list, int id)
{
  Item* item = list->root;
  while(item) {
    if (item->id == id)
      return item->str;
   
    item = item->next;
  }

  return 0;
}

void print_history(List *list)
{
  Item* item = list->root;
  while(item) {
    printf("[%d] '%s'\n", item->id, item->str); 
    item = item->next;
  }
}

void free_history(List *list)
{
  Item *item = list->root;
  Item *prev_item;
  while (item) {
    prev_item = item;
    item = item->next;

    // Free malloc string and node
    free(prev_item->str);
    free(prev_item);
  }

  // Free linked list
  free(list);
}

