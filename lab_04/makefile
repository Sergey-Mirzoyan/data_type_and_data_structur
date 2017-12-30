CC := gcc
CFLAGS := -std=c99
OBJS := rand_comp.o

ifeq ($(mode), debug)
	CFLAGS += -g3 -Wall -Werror -pedantic
endif

all : mas.exe list.exe

mas.exe : $(OBJS) pp_mas.o stat_mas.o
	$(CC) $^ -o $@

list.exe : $(OBJS) pp_list.o list.o
	$(CC) $^ -o $@

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm *.o *.exe
