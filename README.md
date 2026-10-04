# MovieScript

A movie-themed language built with **C11, Flex, and Bison**. MovieScript parses a screenplay, validates its types and values, optionally prints compiler stages, and executes the program with scoped variables and checked function calls.

## Quick start

Requirements: a C compiler, Make, Flex, and Bison. Python 3 is needed only for tests; Clang is needed for the sanitizer target. No Python packages are required.

```sh
make
./moviescript examples/showcase.ms
./moviescript --check examples/showcase.ms
make demo       # AST, IR, CFG, functions, output, and symbols
make test       # end-to-end regression tests
make sanitize   # same tests with AddressSanitizer and UndefinedBehaviorSanitizer
```

Standard input remains supported:

```sh
./moviescript < demo1_basic.ms
```

## A small screenplay

```text
OPENING_CREDITS
SCREENPLAY

CHARACTER @director <- "Ava"
RATING @score <- 4.5
GENRE_COLLECTION @genres <- {"Drama", "Mystery"}

PRINT "Directed by " + @director
SCENE_IF (@score GREATER_EQUAL 4) FRAME
    AWARD "Audience favorite"
ENDFRAME OTHERWISE FRAME
    REVIEW "Room to improve"
ENDFRAME

FOR_EACH_SCENE @genre IN @genres REEL
    PRINT @genre
ENDREEL
PRINT COUNT(@genres)
ASSERT (@score LESS_EQUAL 5, "Rating must be valid")

ENDSCREENPLAY
FINAL_CREDITS
```

## Types and limits

All boundaries are inclusive. Text limits count **UTF-8 bytes**, excluding the terminating NUL. Empty text is allowed. Limits live in `limits.h` so the language contract is defined in one place.

| Type | Allowed values |
| --- | --- |
| `RATING` | Finite numbers from **0 to 5**, including decimals |
| `BUDGET` | Finite numbers from **0 to 1,000,000,000,000**, including decimals |
| `WHOLE` | Integers from **−2,147,483,648 to 2,147,483,647** |
| `CHARACTER` | Text up to **100 bytes** |
| `SCENE` | Text up to **200 bytes** |
| `DIALOGUE` | Text up to **2,000 bytes** |
| `GENRE` | Text up to **50 bytes** |
| `STATUS` | `SUCCESS`, `FAILURE`, `BLOCKBUSTER`, `FLOP`, or `AVERAGE` |
| `SIGNAL` | `TRUE` or `FALSE` |
| `GENRE_COLLECTION` | Up to **1,000** genre strings, each up to **50 bytes** |

Identifiers start with `@` followed by an ASCII letter; remaining characters may be letters, digits, or underscores. The maximum is **63 bytes including `@`**. Names and keywords are case-sensitive. Numeric tokens may contain a decimal fraction and exponent, such as `4.5` or `1e6`; each numeric token is limited to 128 bytes. All arithmetic uses finite double-precision numbers; `WHOLE` additionally enforces its integer range on storage.

These checks apply to **declarations, reassignment, function arguments, and function returns**. Numeric types can be used together in arithmetic, but every destination keeps its own range. Text types share text expressions, but each destination keeps its own length limit. Text is never silently truncated. `STATUS` uses unquoted enum values; `"SUCCESS"` is ordinary text and cannot be stored in a `STATUS` variable. Conditions require `SIGNAL`.

```text
RATING @score <- 6
```

is rejected with a filename and line number:

```text
movie.ms:3: Semantic Error: RATING @score must be between 0 and 5 (got 6)
```

The compiler checks constant values before execution. Values computed from variables or calls are checked again at runtime. `--check` performs static analysis without executing functions or loops; it cannot prove every runtime value. For example, `RATING @score <- @oldScore + 1` can pass static checking and still fail at runtime if the result exceeds 5. Invalid assignments never change the destination; runtime errors stop the program immediately. Output produced before a runtime error remains visible.

## Language features

### Variables, arithmetic, and text

Every scalar type supports both initialized and uninitialized declarations. An uninitialized variable must be assigned before reading it. Duplicate names in the same scope and references to undeclared names are errors.

```text
WHOLE @count
@count <- 2
DIALOGUE @message <- "Take " + "two"
PRINT -2 * (3 + 1)
PRINT 7 % 3
```

Arithmetic operators are `+`, `-`, `*`, `/`, and `%`; unary minus and parentheses are supported. Division produces a number, so assigning `3 / 2` to `WHOLE` is an error. `+` also joins two text values. Division by zero, unsupported mixed types, non-finite literals, and arithmetic overflow produce errors.

Strings support `\n`, `\t`, `\r`, `\"`, and `\\`. Unsupported escapes and unterminated strings are errors. Comments use `//`, `#`, or `/* ... */`; block comments do not nest.

### Conditions and loops

| Word operator | Symbol equivalent |
| --- | --- |
| `GREATER_THAN` | `>` |
| `GREATER_EQUAL` | `>=` |
| `LESS_THAN` | `<` |
| `LESS_EQUAL` | `<=` |
| `IS` | `==` |
| `IS_NOT` | `!=` |

Ordered comparisons require numbers. Equality also supports text, status, and signal values of the same kind. Collections cannot be compared for equality. `NOT`, `AND`, and `OR` operate on signals; `AND` and `OR` short-circuit at runtime. From lowest to highest precedence: `OR`, `AND`, `NOT`, comparisons, `+`/`-`, `*`/`/`/`%`, unary minus. Chained comparisons must be written using `AND`.

`SCENE_IF` supports an optional `OTHERWISE` block. `WHILE` uses `TAKE ... ENDTAKE`:

```text
WHOLE @remaining <- 3
WHILE (@remaining GREATER_THAN 0) TAKE
    PRINT @remaining
    @remaining <- @remaining - 1
ENDTAKE
```

The legacy `@remaining RISING` condition means `@remaining GREATER_THAN 0`. Its value is reevaluated each iteration.

Blocks create lexical scopes. They can shadow outer variables, and local declarations disappear when the block ends. Assigning an existing outer variable updates that variable. Static analysis tracks definite initialization across branches and assumes loops may execute zero times. Impossible checks such as a rating greater than 5 produce warnings.

### Collections

```text
GENRE_COLLECTION @genres <- {}
ADD_TO @genres "Drama"
ADD_TO @genres "Mystery"

FOR_EACH_SCENE @genre IN @genres REEL
    PRINT @genre
ENDREEL
```

The optional iterator is a local `GENRE` variable. The original `FOR_EACH_SCENE IN @genres REEL ... ENDREEL` syntax also executes once per item. Empty collections execute zero times. A loop snapshots the collection at entry: additions in the loop body are retained in the collection but are not visited by that iteration. Duplicate entries are allowed and count as separate items. Assignment between declared collections makes an independent copy.

### Functions

```text
FUNCTION @average(RATING @a, RATING @b) RETURNS RATING FRAME
    RATING @mean <- (@a + @b) / 2
    PRINT "Calculated score"
    RETURN @mean
ENDFRAME ENDFUNCTION

RATING @score <- @average(4, 5)
```

Functions execute their complete bodies, support local declarations, typed parameters, nested calls, recursion, and returns from inside loops or branches. All scalar types may be parameters or return types. A call may also be used as a statement when its result is unnecessary.

Functions are declared at screenplay level, and may be called before their declaration. Argument values are evaluated in the caller before any parameters are bound. Each call can see its own local variables and globals, with its parameters shadowing globals. It cannot see another caller's local variables. Globals must exist and be initialized when read at runtime.

A function must have a provable return on every path: a direct `RETURN` or an `SCENE_IF` whose two branches return. Loops alone do not establish a guaranteed return. Duplicate functions or parameters, wrong argument counts, wrong types, missing returns, and `RETURN` outside a function are errors.

### Built-ins and actions

| Operation | Result or behavior |
| --- | --- |
| `COUNT(@genres)` | Number of collection entries |
| `LENGTH("text")` | Text length in UTF-8 bytes |
| `CONTAINS(@genres, "Drama")` | `TRUE` if an exact, case-sensitive entry exists |
| `CLAMP(value, minimum, maximum)` | Number bounded to the supplied range; minimum must not exceed maximum |
| `PRINT expression` | Print a value, without surrounding quotes for text |
| `ANALYZE @variable` | Print its identifier, declared type, and current value |
| `AWARD expression` / `REVIEW expression` | Print a labeled text message |
| `ASSERT (condition, "message")` | Stop with a diagnostic if the condition is false |
| `BUILD_SUSPENSE` / `ENTER_STAGE` | Print their movie-themed stage actions |

`CLAMP` is an explicit operation. Ratings exceeding 5 are rejected unless the program deliberately clamps them before storing them.

## Command-line tools

```sh
./moviescript --help
./moviescript --check movie.ms
./moviescript --trace movie.ms
./moviescript --check --ir --cfg movie.ms
./moviescript --symbols movie.ms
./moviescript --max-steps 50000 movie.ms
./moviescript --no-optimize movie.ms
```

`--ast`, `--ir`, `--cfg`, `--functions`, and `--symbols` can be combined. `--trace` enables all of them. Stage flags execute the program unless `--check` is also present. The symbol view shows final global values after execution; in check-only mode, initialized values are marked as not evaluated. Numeric constant folding is enabled by default and happens after successful semantic validation.

Ordinary runs print only the program's output to stdout. Errors and warnings go to stderr as `file:line:category:message`; syntax errors also include the column. Exit status is **0** on success, **1** for language or runtime errors, and **2** for command-line or file access errors. Warnings alone do not fail a program.

Programs are limited to 1 MiB of source, 20,000 AST nodes, 128 AST nesting levels, 32 parameters per function, and 128 active function calls. NUL bytes in source are rejected. Execution has a default budget of 100,000 steps; each evaluated expression, statement, and collection iteration counts toward the budget. `--max-steps` changes this budget. These limits prevent accidental infinite loops and runaway recursion from hanging the interpreter.

## Architecture

```text
Source → Flex lexer → Bison parser → AST → semantic validation
                                           ↓
                                   constant folding
                                           ↓
                              optional AST / IR / CFG views
                                           ↓
                                  checked interpreter
```

- `moviescript.l` / `moviescript.y`: tokenization, source locations, and grammar.
- `ast.c`: AST construction, input complexity checks, printing, and cleanup.
- `value.c` / `limits.h`: shared types, value limits, checked operations, and built-ins.
- `semantic.c`: function indexing, scope checks, type checks, definite initialization, and constant validation.
- `symbol_table.c`: lexical scopes and owned, dynamically allocated values.
- `interpreter.c`: execution, checked storage, function frames, and bounded loops.
- `ir.c`: three-address IR with expression temporaries and short-circuit branches, plus CFG and function views.
- `diagnostic.c`: consistent diagnostics and error counts.

IR and CFG are educational views of the parsed program. The interpreter executes the validated AST; there is no machine-code backend.

## Examples and regression coverage

- `examples/showcase.ms`: a complete movie report using every scalar type.
- `examples/functions.ms`: local variables, string returns, recursion, and built-ins.
- `examples/collections.ms`: empty collections, membership, and both iterator forms.
- `examples/validation_errors.ms`: intentional static errors, suitable for `--check`.
- `demo1_basic.ms`, `demo2_functions.ms`, `demo4_collections_foreach.ms`, `demo.ms`, `full_demo.ms`, and `presentation_demo.ms`: working introductory demos on the 0–5 rating scale.

The preexisting local edits in `demo3_control.ms` and `demo5_full_features.ms` are preserved. Their invalid ratings and undeclared variables are now rejected. Use `examples/showcase.ms` for a valid full-feature presentation.

The regression suite checks numeric and text boundaries, UTF-8 lengths, runtime assignments, function arguments and returns, scopes and initialization, collections and capacity, recursion, nested control flow, comments and escapes, arithmetic errors, CLI behavior, source locations, compiler views, and execution limits. `make sanitize` runs the same cases under memory and undefined-behavior instrumentation.
