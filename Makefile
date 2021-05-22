COMP = gcc -std=c99 -g3 -shared -Wall -Werror -Wextra -pedantic -fPIC
SRC = src/*.c
OBJS = *.o

shared : $(OBJS)
	$(COMP) $(OBJS) -o libjstring.so
	rm $(OBJS)

$(OBJS) : $(SRC)
	$(COMP) -c $(SRC) -o $(OBJS)

install :
	sudo cp ./libjstring.so /usr/local/lib/libjstring.so
	sudo cp src/headers/jstring.h /usr/local/include/jstring.h
	LIBRARY_PATH=/usr/local/lib
	export LIBRARY_PATH

static :
	gcc -g3 -std=c99 -c $(SRC) -o $(OBJS)
	ar rcs libjstring.a $(OBJS)
	ranlib libjstring.a
	rm $(OBJS)

test : tests/*.c
	make static
	gcc -std=c99 -g3 -o test tests/main.c -L. -ljstring
	./test
clean :
	rm $(OBJS) libjstring.so libjstring.a debug test
