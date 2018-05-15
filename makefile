.DEFAULT_GOAL := all

######## VARIABLES #######
# Use gcc compiler
CC = g++

# Folders
SRC = src
INCL = include

# Basic compiler flags
CFLAGS = -std=c++11 -g -Wall
CFOLD =  -I$(INCL) -I$(SRC)

# Optimization level. 0 for no optimization. 3 for highest.
OPT = -O0

# Add your targets here for what files should be compiled.
SMARTCACHETEST = main

# Files to run overhead tests
OVERHEAD = cpu_overhead

# Platform Utilities
PLAT_UTIL = platform_util

# General Includes
GEN_UTIL = general_util

# Output name will be same as cpp file
SCT_OUT = $(SMARTCACHETEST)
OH_OUT = $(OVERHEAD)

# Append our folder values
SCT_FOLD := $(addprefix $(SRC)/, $(SMARTCACHETEST))
OH_FOLD := $(addprefix $(SRC)/, $(OVERHEAD))
GEN_UTIL := $(addprefix $(SRC)/, $(GEN_UTIL))


# Execution Extensions
ifeq ($(OS), Windows_NT)
EEXT = .exe
PLAT_UTIL_OUT = $(SRC)/win32/$(PLAT_UTIL)
else
EEXT =
PLAT_UTIL_OUT = $(SRC)/posix/$(PLAT_UTIL)
$(warning Smart Caching Test supports only Windows OS for now.)
endif


####### COMPILING COMMANDS ########

# Compiling for overhead files.
# The :=.cpp is to append cpp extensions for ease of use.
oh: $(OH_FOLD:=.cpp)
	$(CC) $(CFLAGS) $(CFOLD) $(OPT) -o $(OH_OUT) $(OH_FOLD:=.cpp) $(GEN_UTIL:=.cpp) $(PLAT_UTIL_OUT:=.cpp)

# Compiling for the smart cache test
sct: $(SCT_FOLD:=.cpp)
	$(CC) $(CFLAGS) $(CFOLD) $(OPT) -o $(SCT_OUT) $(SCT_FOLD:=.cpp) $(GEN_UTIL:=.cpp) $(PLAT_UTIL_OUT:=.cpp)

# Compiling for the memory overhead files
memory: memory.o
	$(CC) memory.o -o memory

memory.o: memory.cpp memory.hpp
	$(CC) $(CFLAGS) -c memory.cpp memory.hpp

# Compile everything
all: oh sct memory





####### RUN COMMANDS ########
# Run all overhead tests. aohr => all over head run
aohr: oh
	./$(OH_OUT:=$(EEXT))

# Run cache test
sctr: sct
	./$(SCT_OUT:=$(EEXT))

# Run everything
run: aohr sctr


####### CLEAN COMMANDS #######

# Remove everything
clean:
	$(RM) $(OH_OUT:=$(EEXT)) $(SCT_OUT:=$(EEXT)) memory.o memory *.gch
