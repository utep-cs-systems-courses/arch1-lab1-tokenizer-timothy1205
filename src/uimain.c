#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"
#define BUFFER_SIZE 500

static void process_command(char *buffer, List *history) {
  // Command input
  if (buffer[1] == '\0' || buffer[1] == ' ' || buffer[1] == '0') {
    // '!0' or just '!''
    printf("\nHISTORY:\n");
    print_history(history);
  } else {
    if (buffer[1] == 'q') {
      // Quit program
      puts("[SYSTEM] Termination command received! Exiting...");
      free_history(history);
      exit(EXIT_SUCCESS);
    }

    int id = atoi(&buffer[1]);
    if (id > 0) {
      // If specified id is valid attempt to get history
      char *str = get_history(history, history->length - id + 1);
      if (!str) {
        puts("[ERROR] No history found!");
        return;
      }

      char **tokens = tokenize(str);
      print_tokens(tokens);
      free_tokens(tokens);
    } else {
      // Unrecognized command
      puts("[ERROR] Invalid command!");
    }
  }
}

int main(int argc, char** argv)
{
  puts("[SYSTEM] Program ready...");

  char buffer[BUFFER_SIZE];
  List *history = init_history();
  
  while (1) {
    printf("$ ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Remove new line from input
    char *new_line = strchr(buffer, '\n');
    if (new_line) {
      *new_line = '\0'; // Terminate string early
    }

    // Ignore whitespace only strings
    if (!word_start(buffer))
      continue;

    if (buffer[0] == '!') {
      process_command(buffer, history);
   } else {
      puts(buffer);
      add_history(history, buffer);
    }
  }
}
