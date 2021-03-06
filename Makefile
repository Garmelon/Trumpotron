CC = g++ -std=c++14
#CFLAGS = -g -O0 -Wall --pedantic
CFLAGS = -O2 -march=native -Wall --pedantic
LFLAGS =

RM = rm -f

SRCDIR = src
TMPDIR = build
TARGET = trumpotron
FILES = main Markov MarkovMatrix SimpleMarkov

#SOURCES = $(patsubst %,$(SRCDIR)/%.cpp,$(FILES))
OBJECTS = $(patsubst %,$(TMPDIR)/%.o,$(FILES))
DEPS    = $(patsubst %,$(TMPDIR)/%.d,$(FILES))

.PHONY: clean run remake

all: $(TARGET)

# run the target
run: $(TARGET)
	./$<

# clean up the build directory
clean:
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)
	$(RM) $(DEPS)

# clean up and make again
remake: clean $(TARGET)

# link the final target
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $@

# compiling to .o file
$(TMPDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# generating .d dependency files
$(TMPDIR)/%.d: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -MM  $< -MT $(TMPDIR)/$*.o -MF $(TMPDIR)/$*.d

# using dependency files
-include $(DEPS)
