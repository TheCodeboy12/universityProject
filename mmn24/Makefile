# Variables
CC = /usr/bin/gcc
CFLAGS = -fdiagnostics-color=always -g -Wall -ansi -pedantic 
SOURCES = main.c \
          preAssembler/preAssembler2.c \
          preAssembler/macroArray.c \
          globals/helperFuncs.c \
          globals/globalConstants.c \
          globals/hashFunction.c \
          globals/bitField.c \
          firstRun/firstRun.c \
          firstRun/firstRunConstants.c \
          firstRun/helperFunctions.c \
          firstRun/lineAnalyzer.c \
          firstRun/hashTable.c \
          firstRun/token.c \
          firstRun/lineStruct.c \
          secondRun/intLinkedList.c \
          secondRun/codingFunctions.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = main

# Targets
all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)
