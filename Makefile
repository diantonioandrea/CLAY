.PHONY: all distclean

ifeq ($(shell uname),Darwin)
CFLAGS = -std=c2x
else
CFLAGS = -std=c23
endif

CFLAGS += -Wall -pedantic -I./include -Wno-newline-eof

# Headers.
HEADERS = ./include/*.h

HEADERS = ./include/Base/*.h
HEADERS = ./include/Vector/*.h
HEADERS = ./include/Matrix/*.h

# Executables.
TESTS = $(subst src/,executables/,$(subst .c,.out,$(shell find src -name "Test_*.c")))
BENCHMARKS = $(subst src/,executables/,$(subst .c,.out,$(shell find src -name "Bench_*.c")))

# Objects.
T_OBJECTS = $(subst src/,objects/,$(subst .c,.o,$(shell find src -name "Test_*")))
B_OBJECTS = $(subst src/,objects/,$(subst .c,.o,$(shell find src -name "Bench_*")))
OBJECTS = $(subst src/,objects/,$(subst .c,.o,$(shell find src -name "Clay_*")))

# Directories.
DIRECTORIES = ./output ./objects ./executables

# All.
all: $(DIRECTORIES) $(TESTS) $(BENCHMARKS)
	@echo "Compiled everything!"

# Tests and benchmarks.
$(TESTS): executables/Test_%.out: objects/Test_%.o $(OBJECTS) 
	@echo "Linking to $@"
	@$(CC) $^ -o $@

$(BENCHMARKS): executables/Bench_%.out: objects/Bench_%.o $(OBJECTS) 
	@echo "Linking to $@"
	@$(CC) $^ -o $@

# Objects.
$(T_OBJECTS): objects/%.o: src/%.c $(HEADERS)
	@echo "Compiling $< using $(CC) with: $(CFLAGS)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJECTS): objects/%.o: src/%.c $(HEADERS)
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