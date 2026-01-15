CC= gcc
SOURCE= set.c hashtable.c pagedir.c url.c curl.c bag.c crawler.c
OBJ = $(SOURCE:.c=.o)
HEADER= $(SOURCE:.c=.h)
FLAGS =-Wall -Wextra -Wpedantic -gdwarf-4
LFLAGS = -lcurl

crawler: ${OBJ} ${HEADER}
	$(CC) $(FLAGS) $(OBJ) $(LFLAGS) -o crawler

%.o: %.c $(HEADER)	
	$(CC) $(FLAGS) $< -c 

clean:
	rm -rf crawler
	rm -rf *.o
