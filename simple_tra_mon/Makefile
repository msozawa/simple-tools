###############################################
#
# M A K E F I L E
#
#
###############################################

PROGRAM = simple_tra_mon
OBJS = main.o init.o window.o if.o
CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -lncurses -lm
RM = /bin/rm -f

# suffix rule definition
.SUFFIXES: .c .o

# target
$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(LDFLAGS) $^

# suffix rule
.c.o:
	$(CC) $(CFLAGS) -c $<

# clean
.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)



