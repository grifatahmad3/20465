CC = gcc
OBJS = my_add.o
EXEC = my_add
DEBUG_FLAG = -g
COMP_FLAG = -ansi -Wall -pedantic

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@
my_add.o : my_add.c
	$(CC) -c $(COMP_FLAG) $*.c
clean : 
	rm -f $(OBJS) $(EXEC)
