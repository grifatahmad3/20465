CC = gcc
OBJS = myassm.o preasm.o essentials.o firstpass.o
EXEC = myassm
DEBUG_FLAG = -g
COMP_FLAG = -ansi -Wall -pedantic
ASSM_OUTPUT = *.o *.am *.ob *.ent *.ext
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@
myassm.o : myassm.c preasm.h essentials.h firstpass.h
	$(CC) -c $(COMP_FLAG) $*.c
preasm.o : preasm.c preasm.h essentials.h
	$(CC) -c $(COMP_FLAG) $*.c
essentials.o : essentials.c essentials.h
	$(CC) -c $(COMP_FLAG) $*.c
firstpass.o : firstpass.c firstpass.h essentials.h
	$(CC) -c $(COMP_FLAG) $*.c
clean : 
	rm -f $(EXEC) $(ASSM_OUTPUT)
val:
	valgrind $(VALGRIND_FLAGS) ./$(EXEC)