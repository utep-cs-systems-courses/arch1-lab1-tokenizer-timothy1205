#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "tokenizer.h"

List* init_history()
{
  List *list = (List*) calloc(1, sizeof(List));

  return list;
}

void add_history(List *list, char *str)
{
  Item *newItem = (Item*) malloc(sizeof(Item));
  newItem->str = copy_str(str, sizeof(str));

  Item *item = list->root;

  // List id starts at 1
  if (!item) {
    // Create root node
    list->root = newItem;
    newItem->id = 1;
    
  } else {
    // Get last item in list
    int id = 1;
    Item *prevItem;
    while (item) {
      prevItem = item;
      item = item->next;
      id++;
    }

    prevItem->next = newItem;
    newItem->id = id;
  }
}

char *get_history(List *list, int id) {
  Item* item = list->root;
  while(item) {
    if (item->id == id)
      return item->str;
   
    item = item->next;
  }

  return 0;
}

void free_history(List *list) {
  Item *item = list->root;
  Item *prevItem;
    while (item) {
      prevItem = item;
      item = item->next;

      // Free malloc string and node
      free(prevItem->str);
      free(prevItem);
    }

    // Free linked list
    free(list);
}

