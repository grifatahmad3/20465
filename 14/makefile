CC = gcc
OBJS = myassm.o essentials.o preassm.o
EXEC = myassm
DEBUG_FLAG = -g
COMP_FLAG = -ansi -Wall -pedantic

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@
myassm.o : myassm.c essentials.h preassm.h
	$(CC) -c $(COMP_FLAG) $*.c
preassm.o : preassm.c preassm.h essentials.h
	$(CC) -c $(COMP_FLAG) $*.c
clean : 
	rm -f $(OBJS) $(EXEC)