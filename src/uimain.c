#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"
#define BUFFER_SIZE 500

int main(int argc, char** argv)
{
  puts("Program ready...");

  char buffer[BUFFER_SIZE];
  List *history = init_history();
  int historyLength = 0;
  
  while (1) {
    printf("$ ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Remove new line from input
    char *newLine = strchr(buffer, '\n');
    if (newLine) {
      *newLine = '\0'; // Terminate string early
    }

    // Ignore whitespace only strings
    if (!word_start(buffer))
      continue;

    if (buffer[0] == '!') {
      // Command input
      if (buffer[1] == '\0' || buffer[1] == ' ' || buffer[1] == '0') {
        // '!0' or just '!''
        printf("\nHISTORY:\n");
        print_history(history);
      } else {
        int id = atoi(&buffer[1]);
        if (id > 0) {
          char *str = get_history(history, historyLength - id + 1);
          if (str) {
            char **tokens = tokenize(str);
            print_tokens(tokens);
            free_tokens(tokens);
          }
        } else {
          printf("[ERROR] Invalid command!\n");
        }
      }
    } else {
      puts(buffer);
      add_history(history, buffer);
      historyLength++;
    }
  }
}
