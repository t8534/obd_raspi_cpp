#
# simple_makefile.txt
#

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I. -Idiag

# Target executable
TARGET := obd_raspi_cpp.exe

# Source files
# SRCS := main.cpp Alpha.cpp Beta.cpp diag/Gamma.cpp
SRCS := obd_raspi_cpp.cpp CmdManager.cpp

# Object files (replace .cpp with .o)
OBJS := $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule (pattern rule for .cpp -> .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	del /Q $(OBJS) $(TARGET) 2>nul || rm -f $(OBJS) $(TARGET)

# Optional convenience rule to rebuild everything
rebuild: clean all

.PHONY: all clean rebuild