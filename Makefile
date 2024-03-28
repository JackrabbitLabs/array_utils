# arrayutils Makefile
CC=gcc
CFLAGS= -g3 -O0 -Wall -Wextra
INCLUDE_DIR=/usr/local/include/
LIB_DIR=/usr/local/lib
INCLUDE_PATH=-I $(INCLUDE_DIR) 
LIB_PATH=-L $(LIB_DIR)
LIBS=

all: testbench libarrayutils.a

testbench: testbench.c arrayutils.o
	$(CC) $^ $(CFLAGS) $(INCLUDE_PATH) $(LIB_PATH) $(LIBS) -o $@ 

libarrayutils.a: arrayutils.o
	ar rcs $@ $^

arrayutils.o: arrayutils.c arrayutils.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATH) -o $@ 

clean:
	rm -rf ./*.o ./*.a testbench

install: libarrayutils.a 
	sudo cp libarrayutils.a $(LIB_DIR)
	sudo cp arrayutils.h $(INCLUDE_DIR)

.PHONY: all clean install

# Variables 
# $^ 	Will expand to be all the sensitivity list
# $< 	Will expand to be the frist file in sensitivity list
# $@	Will expand to be the target name (the left side of the ":" )
# -c 	gcc will compile but not try and link 
