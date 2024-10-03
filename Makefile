.PHONY: all
CFLAGS = -std=c2x -Wall -pedantic -I./include -Wno-newline-eof

# Headers.
HEADERS = ./include/*.h

HEADERS = ./include/Base/*.h
HEADERS = ./include/Vector/*.h

# Executables.
TESTS = $(subst src/,executables/,$(subst .c,.out,$(shell find src -name "Test_*.c")))

# Objects.
T_OBJECTS = $(subst src/,objects/,$(subst .c,.o,$(shell find src -name "Test_*")))
OBJECTS = $(subst src/,objects/,$(subst .c,.o,$(shell find src -name "*.c" -not -name "Test_*")))

# Directories.
DIRECTORIES = ./output ./objects ./executables

# All.
all: $(DIRECTORIES) $(TESTS)
	@echo "Compiled everything!"

# Tests.
$(TESTS): executables/Test_%.out: objects/Test_%.o $(OBJECTS) 
	@echo "Linking to $@"
	@$(CC) $^ -o $@

# Objects.
$(T_OBJECTS): objects/%.o: src/%.c $(HEADERS)
	@echo "Compiling $< using $(CC) with: $(CFLAGS)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS): objects/%.o: src/%.c $(HEADERS)
	@echo "Compiling $< using $(CC) with: $(CFLAGS)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Directories.
$(DIRECTORIES):
	@mkdir -p $(DIRECTORIES)

# Clean.
distclean:
	@echo "Cleaning the repo."
	@$(RM) -r $(DIRECTORIES)