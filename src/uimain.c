#include <stdio.h>
#define BUFFER_SIZE 500

int main(int argc, char** argv)
{
  puts("Program ready...");

  char buffer[BUFFER_SIZE];
  while (1) {
    printf("$ ");
    fgets(buffer, BUFFER_SIZE, stdin);

    puts(buffer);
  }
}
