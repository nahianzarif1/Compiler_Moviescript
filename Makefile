all:
	bison -d moviescript.y
	flex moviescript.l
	cc -Wall -Wextra -std=c11 -o moviescript \
	main.c ast.c semantic.c symbol_table.c ir.c interpreter.c moviescript.tab.c lex.yy.c

run:
	./moviescript < demo.ms

demo:
	./moviescript < demo.ms

clean:
	rm -f moviescript lex.yy.c moviescript.tab.c moviescript.tab.h