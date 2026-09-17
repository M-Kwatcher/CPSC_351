# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target Executable & Sources
TARGET = run_me
SRCS = main.cpp processes.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = processes.h

# Default target: build executable
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and execute target
run: $(TARGET)
	./$(TARGET)

# Remove build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean