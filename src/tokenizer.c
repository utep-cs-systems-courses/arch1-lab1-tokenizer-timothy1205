#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c)
{
  switch (c) {
    case ' ':
      return 1;
    case '\t':
      return 1;
    default:
      return 0;
  }

  return 0;
}

int non_space_char(char c)
{
  switch (c) {
    case ' ':
      return 0;
    case '\t':
      return 0;
    case '\0':
      return 0;
    default:
      return 1;
  }

  return 0;
}

char *word_start(char *str)
{
  do {
    if (non_space_char(*str))
      return str;
  } while (*(++str) != '\0');

  return NULL;
}

char *word_terminator(char *word)
{
  while (1) {
    // We are at end of word if we hit a space char or zero-terminator
    if (!non_space_char(*word))
      return word;

    word++;
  }

  return NULL;
}

int count_words(char *str)
{
  int words = 0;
  char inWord = 0;
  
  do {
    if (inWord && space_char(*str)) {
      inWord = 0;
    } else if (!inWord && non_space_char(*str)) {
      inWord = 1;
      words++;
    }
  } while(*(++str) != '\0');

  return words;
}

char *copy_str(char *inStr, short len)
{
  // Add 1 for zero-terminator
  char *outStr = (char*) malloc(sizeof(char) * len + 1);
  if (!outStr) {
    fprintf(stderr, "copy_str: Memory alloation error!");
    exit(EXIT_FAILURE);
  }
 
  char *c = outStr;

  /* 
   * Loop over word for length characters
   * or until we hit a zero-terinator so that we
   * can copy both zero-terminated strings and substrings
   */
  for (short i = 0; i < len; ++i) {
    *c = *inStr;

    // Break to prevent copying potentially unmanaged data
    if (*c == '\0') {
      break;
    }

    c++;
    inStr++;
  }

  // Ensure string is zero-terminated
  *c = '\0';

  return outStr;
}

char **tokenize(char* str)
{
  int words = count_words(str);
  // Add 1 to allow for zero pointer
  char **tokens = malloc(sizeof(char*) * (words + 1));

  if (!tokens) {
    fprintf(stderr, "tokenize: Memory alloation error!");
    exit(EXIT_FAILURE);
  }
  
  str = word_start(str);
  for (int i = 0; i < words; ++i) {
    char* terminator = word_terminator(str);
    tokens[i] = copy_str(str, terminator - str);

    str = word_start(terminator);
  }

  // Point the last pointer to nothing
  char **terminator = tokens + words;
  *terminator = 0;

  return tokens;
}

void print_tokens(char **tokens)
{
  printf("{\n");
  for (char** token = tokens; *token != 0; token++)
    printf("\t[%ld] '%s'\n", token - tokens, *token);
  printf("}\n\n");
}

void free_tokens(char **tokens)
{
  char **token = tokens;
    while(*token != 0) {
      free(*token);
      token++;
    }
  // Free final token
  free(*token);
  // Free array of pointers
  free(tokens);
}
