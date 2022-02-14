Project 1: Tokenizer
====================

## Compiling & Running
- `make` or `make all` will compile the `tokenizer` executable.
- `make run` will compile and run the `tokenizer` executable.
- `make test` will compile and run the `tokenizer-test` executable.
- `make clean` will remove all object files and both the `tokenizer` and `tokenizer-test` executables if they exist.

## Usage
- Upon running the program you will be greeted with a shell-style ui.
- Entering a non-command (see below) input will cause it to be printed back to you and continue
  accepting input.
- All commands are prefixed with a `!`.
  - `!` or `!0` will print your input history (excluding commands).
    - **NOTE:** The numbers printed next to the inputs correspond to the order they were entered and
      do not match the below command.
  - `!N` where N is a positive number corresponding to the Nth most recent input will cause that input to be tokenized and printed.
  - `!q` will terminate the program.
