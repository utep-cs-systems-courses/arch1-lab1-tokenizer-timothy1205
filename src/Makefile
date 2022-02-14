OBJS = tokenizer.o history.o
OBJS_MAIN = $(OBJS) uimain.o
OBJS_TEST = $(OBJS) tester.o

CFLAGS =-g -O3

tokenizer.o uimain.o: tokenizer.h
history.o uimain.o: history.h

tokenizer: $(OBJS_MAIN)
	cc -o tokenizer $(CFLAGS) $(OBJS_MAIN)

tokenizer-test: $(OBJS_TEST)
	cc -o tokenizer-test $(CFLAGS) $(OBJS_TEST)

all: tokenizer

clean:
	rm -f *.o tokenizer tokenizer-test

run: tokenizer
	./tokenizer

test: tokenizer-test
	./tokenizer-test
