CC = gcc
OBJS = my_suffix.o
EXEC = my_suffix
DEBUG_FLAG = -g
COMP_FLAG = -ansi -Wall -pedantic

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@
my_suffix.o : my_suffix.c
	$(CC) -c $(COMP_FLAG) $*.c
clean : 
	rm -f $(OBJS) $(EXEC)
