#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"
#define BUFFER_SIZE 500

static void process_command(char *buffer, List *history, int history_length) {
  // Command input
  if (buffer[1] == '\0' || buffer[1] == ' ' || buffer[1] == '0') {
    // '!0' or just '!''
    printf("\nHISTORY:\n");
    print_history(history);
  } else {
    if (buffer[1] == 'q') {
      puts("[SYSTEM] Termination command received! Exiting...");
      free_history(history);
      exit(EXIT_SUCCESS);
    }

    int id = atoi(&buffer[1]);
    if (id > 0) {
      char *str = get_history(history, history_length - id + 1);
      if (!str) {
        puts("[ERROR] No history found!");
        return;
      }

      char **tokens = tokenize(str);
      print_tokens(tokens);
      free_tokens(tokens);
    } else {
      puts("[ERROR] Invalid command!");
    }
  }
}

int main(int argc, char** argv)
{
  puts("[SYSTEM] Program ready...");

  char buffer[BUFFER_SIZE];
  List *history = init_history();
  int history_length = 0;
  
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
      process_command(buffer, history, history_length);
   } else {
      puts(buffer);
      add_history(history, buffer);
      history_length++;
    }
  }
}
