# Compiler to use
CXX = g++

# Compile flags
CXXFLAGS = -Wall -g

# Source files
SRCS = Callon-Nathan-Program3.cpp Game.cpp Tree.cpp

# Objects
OBJS = $(SRCS:.cpp=.o)

MAIN = test.out

all: $(MAIN)
    @echo Simple compiler named $(MAIN) has been compiled.

$(MAIN): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

# To create the object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# To start over from scratch, type 'make clean'. This removes the executable file, as well as old .o object
# files and *~ backup files:
clean:
    $(RM) $(OBJS) $(MAIN)

# Suffix replacement within a macro:
#   $(name:string1=string2)
#   For each word in 'name' replace 'string1' with 'string2'
# In the target below we are replacing the suffix .cpp of all words in the macro SRCS
# with the .o suffix