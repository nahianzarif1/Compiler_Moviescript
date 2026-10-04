CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -Wpedantic -std=c11
LDLIBS ?= -lm
BISON ?= bison
FLEX ?= flex
PYTHON ?= python3
SANITIZER_CC ?= clang

SOURCES = main.c ast.c diagnostic.c value.c semantic.c symbol_table.c ir.c interpreter.c
HEADERS = ast.h diagnostic.h value.h semantic.h symbol_table.h ir.h interpreter.h limits.h
GENERATED = moviescript.tab.c moviescript.tab.h lex.yy.c

.PHONY: all run demo test sanitize clean
all: moviescript

moviescript: $(SOURCES) $(HEADERS) $(GENERATED)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) moviescript.tab.c lex.yy.c $(LDLIBS)

moviescript.tab.c: moviescript.y
	$(BISON) -d -o $@ $<

moviescript.tab.h: moviescript.tab.c
	@test -f $@ || $(BISON) -d -o moviescript.tab.c moviescript.y

lex.yy.c: moviescript.l moviescript.tab.h
	$(FLEX) -o $@ $<

run: moviescript
	./moviescript examples/showcase.ms

demo: moviescript
	./moviescript --trace examples/showcase.ms

test: moviescript
	$(PYTHON) tests/test_moviescript.py ./moviescript

moviescript-sanitize: $(SOURCES) $(HEADERS) $(GENERATED)
	$(SANITIZER_CC) -g -O1 -Wall -Wextra -Wpedantic -std=c11 -fsanitize=address,undefined -fno-omit-frame-pointer -o $@ $(SOURCES) moviescript.tab.c lex.yy.c $(LDLIBS)

sanitize: moviescript-sanitize
	$(PYTHON) tests/test_moviescript.py ./moviescript-sanitize

clean:
	$(RM) moviescript moviescript-sanitize $(GENERATED)
