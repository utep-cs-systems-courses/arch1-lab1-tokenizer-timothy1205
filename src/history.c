#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "tokenizer.h"

List* init_history()
{
  // Initialize list with zeros
  List *list = (List*) calloc(1, sizeof(List));
  if (!list) {
    fprintf(stderr, "init_history: Memory allocation error!");
    exit(EXIT_FAILURE);
  }

  return list;
}

void add_history(List *list, char *str)
{
  // Create a new Item 
  Item *new_item = (Item*) malloc(sizeof(Item));
  if (!new_item) {
    fprintf(stderr, "add_history: Memory allocation error!");
    exit(EXIT_FAILURE);
  }

  // Copy given string into a freshly allocated space
  // using strlen, store pointer into new item
  new_item->str = copy_str(str, strlen(str));

  Item *item = list->root;

  // List id starts at 1
  if (!item) {
    // No root node, create it
    list->root = new_item;
    new_item->id = 1;
    
  } else {
    // Find the last item in our list and 
    // append our new_item to it
    int id = 1;
    Item *prev_item;
    while (item) {
      prev_item = item;
      item = item->next;
      id++;
    }

    // Once item is null and the loop finishes
    // prev_item will be the last valid node
    prev_item->next = new_item; // Update the next pointer
    new_item->id = id; // Update new_item's id to correspond with the 
  }

  list->length++;
}

char *get_history(List *list, int id)
{
  Item* item = list->root;
  while(item) {
    // If id matches, return item string
    if (item->id == id)
      return item->str;
   
    item = item->next;
  }

  // If we go through entire list with no matching ids 
  // return a zero pointer
  return 0;
}

void print_history(List *list)
{
  Item* item = list->root;
  while(item) {
    // For every item print its position (relative to most recent input) 
    // and string on separate line
    // ex: [1] 'test string'
    printf("[%d] '%s'\n", list->length - item->id + 1, item->str); 
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

  // Free linked list and length attribute
  free(list);
}

