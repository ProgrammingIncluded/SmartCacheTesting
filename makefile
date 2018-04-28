######## VARIABLES #######
# Use gcc compiler
CC = g++

# Basic compiler flags
CFLAGS = -g -Wall

# Optimization level. 0 for no optimization. 3 for highest.
OPT = -O0

# Add your targets here for what files should be compiled.
SMARTCACHETEST = main

# Files to run overhead tests
OVERHEAD = cpu_overhead

# Execution Extensions
ifeq ($(OS), Windows_NT)
EEXT = .exe
else
EEXT = 
$(warning Smart Caching Test supports only Windows OS for now.)
endif


####### COMPILING COMMANDS ########

# Compiling for overhead files. 
# The :=.cpp is to append cpp extensions for ease of use.
oh: $(OVERHEAD:=.cpp)
	$(CC) $(CFLAGS) $(OPT) -o $(OVERHEAD) $(OVERHEAD:=.cpp)

# Compiling for the smart cache test
sct: $(SMARTCACHETEST:=.cpp)
	$(CC) $(CFLAGS) $(OPT) -o $(SMARTCACHETEST) $(SMARTCACHETEST:=.cpp)

# Compile everything
all: oh sct


####### RUN COMMANDS ########
# Run all overhead tests. aohr => all over head run
aohr: oh
	$(OVERHEAD:=$(EEXT))

# Run cache test
sctr: sct
	$(SMARTCACHETEST:=$(EEXT))

# Run everything
run: aohr sctr


####### CLEAN COMMANDS #######

# Remove everything
clean:
	$(RM) $(TARGET) $(OVERHEAD)