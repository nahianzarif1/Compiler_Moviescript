# MovieScript Compiler

MovieScript is a small compiler/interpreter project built with Flex and Bison.

## Architecture

MovieScript Source Code
↓
Lexical Analyzer (Flex)
↓
Parser (Bison)
↓
Abstract Syntax Tree
↓
Semantic Analyzer
↓
Symbol Table
↓
Intermediate Code Generation
↓
Control Flow Graph
↓
Interpreter
↓
Program Output

## Features

- Lexer with line-aware errors
- Parser with syntax error messages
- AST with readable printing
- Duplicate variable detection
- Undefined variable detection
- Type checking for assignments
- Constant folding for arithmetic expressions like `5 + 3`
- Dead-code warning for impossible `RATING > 10` checks
- Three-address style IR output
- CFG printing for control-flow constructs

## Build

Use the provided `Makefile`.

## Demo files

- `demo.ms` — full feature demo
- `presentation_demo.ms` — compact presentation demo

## Presentation idea

Show the compiler stages in this order:

1. Source program
2. AST
3. Semantic analysis messages
4. IR
5. CFG
6. Interpreter output