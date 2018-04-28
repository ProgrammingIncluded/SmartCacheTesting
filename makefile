# Use gcc compiler
CC = g++

# Basic compiler flags
CFLAGS = -g -Wall

# Optimization level. 0 for no optimization. 3 for highest.
OPT = -O0

# Add your targets here for what files should be compiled.
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(OPT) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)