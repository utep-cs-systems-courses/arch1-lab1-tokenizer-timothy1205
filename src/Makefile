OBJS= tokenizer.o history.o uimain.o
CFLAGS=-g -O3

tokenizer.o uimain.o: tokenizer.h
history.o uimain.o: history.h

tokenizer: $(OBJS) 
	cc -o tokenizer $(CFLAGS) $(OBJS)

all: tokenizer

clean:
	rm -f *.o tokenizer

run: tokenizer
	./tokenizer
