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

# Memory Characterization
LATENCY = latency
MEMORYBW = memory_bw
PAGEFAULT = page_fault

# Output name will be same as cpp file
SCT_OUT = $(SMARTCACHETEST)
OH_OUT = $(OVERHEAD)
LATENCY_OUT = $(LATENCY)
MEMORYBW_OUT = $(MEMORYBW)
PAGEFAULT_OUT = $(PAGEFAULT)

# Append our folder values
SCT_FOLD := $(addprefix $(SRC)/, $(SMARTCACHETEST))
OH_FOLD := $(addprefix $(SRC)/, $(OVERHEAD))
GEN_UTIL := $(addprefix $(SRC)/, $(GEN_UTIL))
LATENCY_FOLD := $(addprefix $(SRC)/, $(LATENCY))
MEMORYBW_FOLD := $(addprefix $(SRC)/, $(MEMORYBW))
PAGEFAULT_FOLD := $(addprefix $(SRC)/, $(PAGEFAULT))

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

latency: $(LATENCY_FOLD:=.cpp)
	$(CC) $(CFLAGS) $(CFOLD) $(OPT) -o $(LATENCY_OUT) $(LATENCY_FOLD:=.cpp) $(GEN_UTIL:=.cpp) $(PLAT_UTIL_OUT:=.cpp)

memorybw: $(MEMORYBW_FOLD:=.cpp)
	$(CC) $(CFLAGS) $(CFOLD) $(OPT) -o $(MEMORYBW_OUT) $(MEMORYBW_FOLD:=.cpp) $(GEN_UTIL:=.cpp) $(PLAT_UTIL_OUT:=.cpp)

pagefault: $(PAGEFAULT_FOLD:=.cpp)
	$(CC) $(CFLAGS) $(CFOLD) $(OPT) -o $(PAGEFAULT_OUT) $(PAGEFAULT_FOLD:=.cpp) $(GEN_UTIL:=.cpp) $(PLAT_UTIL_OUT:=.cpp)

# Compile everything
all: oh sct latency memorybw pagefault

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
	$(RM) $(OH_OUT:=$(EEXT)) $(SCT_OUT:=$(EEXT)) $(LATENCY_OUT:=$(EEXT)) $(MEMORYBW_OUT:=$(EEXT)) $(PAGEFAULT_OUT:=$(EEXT))
