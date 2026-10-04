"""End-to-end regressions: observable output, diagnostics, and process status."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

BINARY = str(Path(sys.argv.pop(1) if len(sys.argv) > 1 else "./moviescript").resolve())
ROOT = Path(__file__).resolve().parents[1]


def program(body):
    return f"OPENING_CREDITS\nSCREENPLAY\n{body}\nENDSCREENPLAY\nFINAL_CREDITS\n"


class MovieScriptTests(unittest.TestCase):
    def run_script(self, body, *options, wrapped=True):
        return subprocess.run([BINARY, *options], input=program(body) if wrapped else body,
                              text=True, capture_output=True, timeout=15)

    def accepts(self, body, output=None, *options):
        result = self.run_script(body, *options)
        self.assertEqual(result.returncode, 0, result.stderr)
        if output is not None:
            self.assertEqual(result.stdout, output)
        self.assertNotIn("Error", result.stderr)
        return result

    def rejects(self, body, diagnostic, *options):
        result = self.run_script(body, *options)
        self.assertEqual(result.returncode, 1, result.stderr)
        self.assertIn(diagnostic, result.stderr)
        self.assertNotIn("AddressSanitizer", result.stderr)
        self.assertNotIn("UndefinedBehaviorSanitizer", result.stderr)
        self.assertNotIn("runtime error:", result.stderr)
        return result

    def test_rating_boundaries(self):
        self.accepts('RATING @a <- 0 RATING @b <- 5 RATING @c <- 4.75 PRINT @a PRINT @b PRINT @c', '0\n5\n4.75\n')
        for value in ('5.00001', '6', '10', '-0.01', '-1', '2 * 3'):
            with self.subTest(value=value):
                self.rejects(f'RATING @r <- {value}', 'must be between 0 and 5')

    def test_rating_assignments(self):
        self.rejects('RATING @r <- 4 @r <- 6', 'must be between 0 and 5')
        result = self.rejects('RATING @r <- 4 WHOLE @delta <- 2 @r <- @r + @delta PRINT "after"', 'must be between 0 and 5')
        self.assertIn('Runtime Error', result.stderr)
        self.assertEqual(result.stdout, '')
        self.accepts('RATING @r <- 5 @r <- @r - 1 PRINT @r', '4\n')

    def test_rating_function_arguments_and_returns(self):
        fn = 'FUNCTION @echo(RATING @r) RETURNS RATING FRAME RETURN @r ENDFRAME ENDFUNCTION '
        self.rejects(fn + 'PRINT @echo(6)', 'must be between 0 and 5')
        self.rejects(fn + 'WHOLE @n <- 6 PRINT @echo(@n)', 'must be between 0 and 5')
        self.rejects('FUNCTION @f(RATING @r) RETURNS RATING FRAME RETURN @r + 1 ENDFRAME ENDFUNCTION PRINT @f(5)', 'must be between 0 and 5')
        self.accepts(fn + 'PRINT @echo(5)', '5\n')

    def test_budget_and_whole_ranges(self):
        self.accepts('BUDGET @b <- 1e12 WHOLE @lo <- -2147483648 WHOLE @hi <- 2147483647 PRINT @b PRINT @lo PRINT @hi', '1000000000000\n-2147483648\n2147483647\n')
        for value in ('-1', '1000000000001'):
            self.rejects(f'BUDGET @b <- {value}', 'BUDGET @b must be between')
        for value in ('2.5', '-2147483649', '2147483648', '3 / 2'):
            self.rejects(f'WHOLE @n <- {value}', 'must be an integer')
        self.rejects('WHOLE @n <- 2147483647 @n <- @n + 1', 'must be an integer')
        self.rejects('BUDGET @b <- 0 @b <- @b - 1', 'BUDGET @b must be between')

    def test_all_text_boundaries_and_no_truncation(self):
        for typ, limit in [('CHARACTER', 100), ('SCENE', 200), ('GENRE', 50), ('DIALOGUE', 2000)]:
            with self.subTest(type=typ):
                self.accepts(f'{typ} @v <- "' + 'x' * limit + '" PRINT @v', 'x' * limit + '\n')
                self.rejects(f'{typ} @v <- "' + 'x' * (limit + 1) + '"', f'exceeds {limit} bytes')
                self.rejects(f'DIALOGUE @long <- "' + 'x' * (limit + 1) + f'" {typ} @short <- @long', f'exceeds {limit} bytes')
        self.rejects('PRINT "' + 'x' * 2001 + '"', 'string exceeds 2000 bytes')
        self.accepts('DIALOGUE @v <- "' + 'x' * 500 + '" @v <- @v + "y" PRINT LENGTH(@v)', '501\n')
        self.rejects('DIALOGUE @v <- "' + 'x' * 1500 + '" PRINT @v + @v', 'concatenated text exceeds')

    def test_utf8_limits_are_bytes(self):
        self.accepts('CHARACTER @v <- "' + 'é' * 50 + '" PRINT LENGTH(@v)', '100\n')
        self.rejects('CHARACTER @v <- "' + 'é' * 51 + '"', 'exceeds 100 bytes')

    def test_identifier_boundaries(self):
        name = '@' + 'x' * 62
        self.accepts(f'WHOLE {name} <- 1 PRINT {name}', '1\n')
        self.rejects('WHOLE @' + 'x' * 63 + ' <- 1', 'identifier exceeds 63 bytes')

    def test_type_checks(self):
        for body in ('RATING @v <- "bad"', 'CHARACTER @v <- 5', 'SIGNAL @v <- 1', 'STATUS @v <- "SUCCESS"', 'WHOLE @v <- TRUE'):
            with self.subTest(body=body):
                self.rejects(body, 'requires')
        self.accepts('STATUS @v <- SUCCESS @v <- BLOCKBUSTER SIGNAL @b <- TRUE PRINT @v PRINT @b', 'BLOCKBUSTER\nTRUE\n')
        for status in ('SUCCESS', 'FAILURE', 'BLOCKBUSTER', 'FLOP', 'AVERAGE'):
            self.accepts(f'STATUS @v <- {status} PRINT @v', status + '\n')
        self.rejects('RATING @v <- 1 @v <- "bad"', 'requires RATING')
        self.rejects('PRINT "a" + 1', 'does not accept')
        self.rejects('SCENE_IF (2) FRAME ENDFRAME', 'condition requires SIGNAL')
        self.rejects('AWARD 2', 'requires DIALOGUE')

    def test_undefined_duplicate_and_uninitialized(self):
        self.rejects('PRINT @missing', 'undefined variable')
        self.rejects('WHOLE @x <- @missing', 'undefined variable')
        self.rejects('@missing <- 1', 'undefined variable')
        self.rejects('WHOLE @x WHOLE @x', 'duplicate variable')
        self.rejects('WHOLE @x PRINT @x', 'may be uninitialized')
        self.rejects('WHOLE @x <- @x', 'may be uninitialized')
        self.accepts('WHOLE @x @x <- 1 PRINT @x', '1\n')
        self.rejects('ANALYZE @missing', 'undefined variable')
        self.rejects('RETURN 1', 'only valid inside a function')

    def test_scope_and_definite_initialization(self):
        self.accepts('WHOLE @x SCENE_IF (TRUE) FRAME @x <- 2 ENDFRAME PRINT @x', '2\n')
        self.accepts('WHOLE @x SCENE_IF (FALSE) FRAME ENDFRAME OTHERWISE FRAME @x <- 3 ENDFRAME PRINT @x', '3\n')
        self.accepts('WHOLE @x <- 1 SCENE_IF (TRUE) FRAME WHOLE @x <- 2 PRINT @x ENDFRAME PRINT @x', '2\n1\n')
        self.rejects('SCENE_IF (TRUE) FRAME WHOLE @x <- 1 ENDFRAME PRINT @x', 'undefined variable')
        self.accepts('WHOLE @x SIGNAL @yes <- TRUE SCENE_IF (@yes) FRAME @x <- 1 ENDFRAME OTHERWISE FRAME @x <- 2 ENDFRAME PRINT @x', '1\n')
        self.rejects('WHOLE @x SIGNAL @yes <- FALSE SCENE_IF (@yes) FRAME @x <- 1 ENDFRAME PRINT @x', 'may be uninitialized')
        self.rejects('WHOLE @x WHILE (FALSE) TAKE @x <- 1 ENDTAKE PRINT @x', 'may be uninitialized')

    def test_comparisons_and_logic(self):
        self.accepts('PRINT 1 < 2 PRINT 1 <= 1 PRINT 2 > 1 PRINT 2 >= 2 PRINT 1 == 1 PRINT 1 != 2 PRINT NOT FALSE PRINT TRUE AND FALSE PRINT TRUE OR FALSE PRINT "a" IS "a" PRINT SUCCESS IS_NOT FAILURE', 'TRUE\n' * 7 + 'FALSE\nTRUE\nTRUE\nTRUE\n')
        self.accepts('PRINT 1 LESS_THAN 2 PRINT 1 LESS_EQUAL 1 PRINT 2 GREATER_THAN 1 PRINT 2 GREATER_EQUAL 2', 'TRUE\n' * 4)
        self.accepts('PRINT NOT 1 IS 2 PRINT TRUE OR FALSE AND FALSE', 'TRUE\nTRUE\n')
        self.rejects('PRINT 1 AND TRUE', 'does not accept')
        self.rejects('PRINT "a" < "b"', 'does not accept')

    def test_short_circuit(self):
        self.accepts('WHOLE @zero <- 0 PRINT FALSE AND 1 / @zero > 0 PRINT TRUE OR 1 / @zero > 0', 'FALSE\nTRUE\n')
        body = 'FUNCTION @side() RETURNS SIGNAL FRAME PRINT "side" RETURN TRUE ENDFRAME ENDFUNCTION PRINT FALSE AND @side() PRINT TRUE OR @side()'
        self.accepts(body, 'FALSE\nTRUE\n')

    def test_arithmetic_errors(self):
        self.accepts('PRINT -2 * 3 + 10 PRINT 7 % 3 PRINT 5 / 2', '4\n1\n2.5\n')
        for body in ('PRINT 1 / 0', 'PRINT 1 % 0', 'WHOLE @n <- 2 PRINT @n / 0'):
            self.rejects(body, 'division by zero')
        self.rejects('WHOLE @z <- 0 PRINT 1 / @z', 'division by zero')
        self.rejects('PRINT 1e309', 'finite number range')
        self.rejects('PRINT 1e308 * 1e308', 'finite number range')
        self.rejects('BUDGET @x <- 1e12 PRINT @x * 1e308', 'finite number range')
        self.rejects('PRINT ' + '9' * 129, 'numeric literal exceeds')

    def test_functions_execute_full_body(self):
        body = 'FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME WHOLE @local <- @n + 1 PRINT @local @local <- @local + 1 RETURN @local PRINT "unreachable" ENDFRAME ENDFUNCTION PRINT @f(3)'
        result = self.accepts(body, '4\n5\n')
        self.assertIn('unreachable statement', result.stderr)
        self.accepts('FUNCTION @f(DIALOGUE @s) RETURNS DIALOGUE FRAME RETURN @s ENDFRAME ENDFUNCTION PRINT @f("hello")', 'hello\n')
        self.accepts('FUNCTION @f(SIGNAL @s) RETURNS SIGNAL FRAME RETURN NOT @s ENDFRAME ENDFUNCTION PRINT @f(FALSE)', 'TRUE\n')

    def test_nested_calls_and_recursion(self):
        body = 'FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME RETURN @n + 1 ENDFRAME ENDFUNCTION PRINT @f(@f(2))'
        self.accepts(body, '4\n')
        body = 'FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME SCENE_IF (@n <= 1) FRAME RETURN 1 ENDFRAME OTHERWISE FRAME RETURN @n * @f(@n - 1) ENDFRAME ENDFRAME ENDFUNCTION PRINT @f(5)'
        self.accepts(body, '120\n')
        body = 'FUNCTION @pick(WHOLE @a, WHOLE @b) RETURNS WHOLE FRAME RETURN @b ENDFRAME ENDFUNCTION WHOLE @a <- 7 PRINT @pick(1, @a)'
        self.accepts(body, '7\n')
        self.accepts('PRINT @later(2) FUNCTION @later(WHOLE @n) RETURNS WHOLE FRAME RETURN @n ENDFRAME ENDFUNCTION', '2\n')

    def test_function_validation(self):
        fn = 'FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME RETURN @n ENDFRAME ENDFUNCTION '
        self.rejects(fn + 'PRINT @f()', 'expects 1 arguments')
        self.rejects(fn + 'PRINT @f(1, 2)', 'expects 1 arguments')
        self.rejects(fn + 'PRINT @f("bad")', 'requires WHOLE')
        self.rejects('PRINT @missing()', 'undefined function')
        self.rejects(fn + fn, 'duplicate function')
        self.rejects('FUNCTION @f(WHOLE @n, WHOLE @n) RETURNS WHOLE FRAME RETURN @n ENDFRAME ENDFUNCTION', 'duplicate variable')
        self.rejects('FUNCTION @f() RETURNS WHOLE FRAME PRINT 1 ENDFRAME ENDFUNCTION', 'RETURN on every path')
        self.rejects('FUNCTION @f() RETURNS WHOLE FRAME RETURN "bad" ENDFRAME ENDFUNCTION', 'requires WHOLE')
        self.rejects('SCENE_IF (TRUE) FRAME FUNCTION @f() RETURNS WHOLE FRAME RETURN 1 ENDFRAME ENDFUNCTION ENDFRAME', 'screenplay level')
        self.rejects(fn + 'PRINT @f', 'call it with parentheses')
        params = ', '.join(f'WHOLE @p{i}' for i in range(33))
        self.rejects(f'FUNCTION @f({params}) RETURNS WHOLE FRAME RETURN 1 ENDFRAME ENDFUNCTION', 'exceeds 32 parameters')
        self.rejects('FUNCTION @f() RETURNS WHOLE FRAME RETURN @f() ENDFRAME ENDFUNCTION PRINT @f()', 'call depth exceeds')

    def test_function_local_scopes(self):
        self.accepts('WHOLE @n <- 7 FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME @n <- @n + 1 RETURN @n ENDFRAME ENDFUNCTION PRINT @f(2) PRINT @n', '3\n7\n')
        self.rejects('FUNCTION @f() RETURNS WHOLE FRAME WHOLE @x <- 2 RETURN @x ENDFRAME ENDFUNCTION PRINT @x', 'undefined variable')
        body = 'WHOLE @x FUNCTION @f() RETURNS WHOLE FRAME RETURN @x ENDFRAME ENDFUNCTION PRINT @f()'
        self.rejects(body, 'is uninitialized')
        self.accepts('WHOLE @x <- 3 FUNCTION @g() RETURNS WHOLE FRAME RETURN @x ENDFRAME ENDFUNCTION FUNCTION @f() RETURNS WHOLE FRAME WHOLE @x <- 7 RETURN @g() ENDFRAME ENDFUNCTION PRINT @f()', '3\n')

    def test_returns_inside_control_flow(self):
        body = 'FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME WHILE (@n > 0) TAKE RETURN @n ENDTAKE RETURN 0 ENDFRAME ENDFUNCTION PRINT @f(3) PRINT @f(0)'
        self.accepts(body, '3\n0\n')
        body = 'GENRE_COLLECTION @items <- {"a", "b"} FUNCTION @first() RETURNS GENRE FRAME FOR_EACH_SCENE @item IN @items REEL RETURN @item ENDREEL RETURN "empty" ENDFRAME ENDFUNCTION PRINT @first()'
        self.accepts(body, 'a\n')

    def test_collections_and_iteration(self):
        self.accepts('GENRE_COLLECTION @c <- {"a", "b"} ADD_TO @c "c" PRINT COUNT(@c) FOR_EACH_SCENE @item IN @c REEL PRINT @item ENDREEL PRINT CONTAINS(@c, "b")', '3\na\nb\nc\nTRUE\n')
        self.accepts('GENRE_COLLECTION @c <- {} FOR_EACH_SCENE IN @c REEL PRINT "bad" ENDREEL PRINT COUNT(@c)', '0\n')
        self.accepts('GENRE_COLLECTION @c <- {"a", "b"} WHOLE @count <- 0 FOR_EACH_SCENE IN @c REEL @count <- @count + 1 ENDREEL PRINT @count', '2\n')
        self.accepts('GENRE_COLLECTION @c <- {"a", "b"} FOR_EACH_SCENE @item IN @c REEL ADD_TO @c "c" PRINT @item ENDREEL PRINT COUNT(@c)', 'a\nb\n4\n')
        self.rejects('GENRE_COLLECTION @c <- {"a"} FOR_EACH_SCENE @item IN @c REEL ENDREEL PRINT @item', 'undefined variable')
        self.rejects('WHOLE @n <- 1 FOR_EACH_SCENE IN @n REEL ENDREEL', 'requires GENRE_COLLECTION')
        self.rejects('ADD_TO @missing "a"', 'undefined variable')
        self.rejects('WHOLE @n <- 1 ADD_TO @n "a"', 'requires GENRE_COLLECTION')
        self.rejects('GENRE_COLLECTION @c <- {} ADD_TO @c 1', 'requires GENRE')
        self.rejects('GENRE_COLLECTION @c <- {"' + 'x' * 51 + '"}', 'exceeds 50 bytes')
        self.rejects('GENRE_COLLECTION @c <- {} DIALOGUE @v <- "' + 'x' * 51 + '" ADD_TO @c @v', 'exceeds 50 bytes')

    def test_collection_output_and_copy(self):
        self.accepts('GENRE_COLLECTION @c <- {"a\\n", "b\\\""} PRINT @c', '{"a\\n", "b\\\""}\n')
        self.accepts('GENRE_COLLECTION @a <- {"one"} GENRE_COLLECTION @b <- {} @b <- @a ADD_TO @a "two" PRINT COUNT(@a) PRINT COUNT(@b)', '2\n1\n')

    def test_collection_capacity(self):
        items = ','.join('"a"' for _ in range(1000))
        self.accepts('GENRE_COLLECTION @c <- {' + items + '} PRINT COUNT(@c)', '1000\n')
        self.rejects('GENRE_COLLECTION @c <- {' + items + ',"b"}', 'exceeds 1000 items')
        self.rejects('GENRE_COLLECTION @c <- {' + items + '} ADD_TO @c "b"', 'exceeds 1000 items')

    def test_builtins_and_assertions(self):
        self.accepts('PRINT CLAMP(6, 0, 5) PRINT LENGTH("hello") GENRE_COLLECTION @c <- {"a"} ASSERT (CONTAINS(@c, "a"), "present")', '5\n5\n')
        self.rejects('PRINT CLAMP(3, 5, 0)', 'minimum cannot exceed maximum')
        for body in ('PRINT COUNT(1)', 'PRINT LENGTH(2)', 'PRINT CONTAINS("a", "b")', 'PRINT CLAMP(1, 2)'):
            self.rejects(body, 'invalid arguments')
        self.rejects('ASSERT (FALSE, "failure message") PRINT "after"', 'assertion failed: failure message')
        self.rejects('ASSERT (1, "bad condition")', 'requires SIGNAL')

    def test_comments_and_escapes(self):
        self.accepts('# first\n/* block\ncomment */\nPRINT "Hello\\nWorld\\t\\\"quoted\\\"\\\\" // final', 'Hello\nWorld\t"quoted"\\\n')
        self.rejects('PRINT "bad\\q"', 'unsupported string escape')
        self.rejects('PRINT "unterminated', 'unterminated string')
        self.rejects('/* unterminated', 'unterminated block comment')

    def test_syntax_and_lexical_errors_never_execute(self):
        for source in ('', 'OPENING_CREDITS SCREENPLAY PRINT 1', 'OPENING_CREDITS SCREENPLAY PRINT 1 ENDSCREENPLAY FINAL_CREDITS $'):
            result = self.run_script(source, wrapped=False)
            self.assertEqual(result.returncode, 1, result.stderr)
            self.assertEqual(result.stdout, '')
        self.rejects('PRINT $', 'Lexical Error')
        self.rejects('GENRE_COLLECTION @c <- {,"a"}', 'Syntax Error')
        self.rejects('FUNCTION @f(,WHOLE @n) RETURNS WHOLE FRAME RETURN @n ENDFRAME ENDFUNCTION', 'Syntax Error')
        self.accepts('', '')

    def test_error_line_numbers(self):
        result = self.rejects('\n\nRATING @score <- 6', '<stdin>:5: Semantic Error')
        self.assertEqual(result.stdout, '')
        self.rejects('/* line3\nline4 */\nPRINT $', '<stdin>:5: Lexical Error')

    def test_step_limit_and_rising(self):
        self.rejects('WHILE (TRUE) TAKE ENDTAKE', 'execution step limit (30)', '--max-steps', '30')
        self.rejects('RATING @r <- 1 WHILE (@r RISING) TAKE ENDTAKE', 'execution step limit', '--max-steps', '30')
        self.accepts('WHOLE @n <- 3 WHILE (@n RISING) TAKE PRINT @n @n <- @n - 1 ENDTAKE', '3\n2\n1\n')

    def test_check_mode_and_compiler_stages(self):
        self.accepts('PRINT "must not execute"', 'Check passed (0 warnings).\n', '--check')
        body = 'WHOLE @x <- 2 FUNCTION @f(WHOLE @n) RETURNS WHOLE FRAME RETURN @n + 1 ENDFRAME ENDFUNCTION PRINT @f(@x * 3)'
        result = self.accepts(body, None, '--trace')
        for stage in ('Abstract syntax tree', 'Intermediate code', 'Control-flow graph', 'Function index', 'Global symbols', 'Program output'):
            self.assertIn(stage, result.stdout)
        self.assertIn('CHECK_STORE @x', result.stdout)
        self.assertIn('CALL @f, 1', result.stdout)
        self.assertIn('WHOLE @n', result.stdout)
        self.assertIn('7\n', result.stdout)
        self.accepts('PRINT (2 + 3) * -2', '-10\n', '--no-optimize')

    def test_ir_uses_real_operators_and_arguments(self):
        result = self.accepts('WHOLE @x <- 2 SCENE_IF (@x <= 3) FRAME PRINT @x + 1 ENDFRAME', None, '--ir', '--check')
        self.assertIn('@x <= 3', result.stdout)
        self.assertIn('@x + 1', result.stdout)
        self.assertIn('PRINT t', result.stdout)
        result = self.accepts('SIGNAL @yes <- TRUE PRINT @yes OR FALSE', None, '--ir', '--check')
        self.assertIn('== TRUE GOTO', result.stdout)

    def test_cli_and_file_input(self):
        for options in (['--bogus'], ['--max-steps'], ['--max-steps', '0'], ['--max-steps', '-1'], ['--max-steps', 'abc'], ['--max-steps', '9x'], ['a.ms', 'b.ms']):
            result = subprocess.run([BINARY, *options], capture_output=True, text=True)
            self.assertEqual(result.returncode, 2, result.stderr)
        for option in ('--help', '--version'):
            result = subprocess.run([BINARY, option], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0)
            self.assertIn('MovieScript', result.stdout)
        result = subprocess.run([BINARY, '/nonexistent/moviescript.ms'], capture_output=True, text=True)
        self.assertEqual(result.returncode, 2)
        with tempfile.TemporaryDirectory() as directory:
            file = Path(directory) / 'movie.ms'
            file.write_text(program('PRINT 5'))
            result = subprocess.run([BINARY, str(file)], capture_output=True, text=True)
            self.assertEqual((result.returncode, result.stdout), (0, '5\n'))
            file.write_text(program('RATING @v <- 6'))
            result = subprocess.run([BINARY, str(file)], capture_output=True, text=True)
            self.assertIn(str(file) + ':3: Semantic Error', result.stderr)
        self.accepts('PRINT 5', '5\n', '-')

    def test_input_resource_limits(self):
        result = self.run_script('x' * (1024 * 1024 + 1), wrapped=False)
        self.assertEqual(result.returncode, 1)
        self.assertIn('source exceeds 1 MiB', result.stderr)
        self.rejects('PRINT "a\0b"', 'NUL byte')
        self.rejects('PRINT ' + '- ' * 150 + '1', 'nesting levels')
        self.rejects('PRINT 1\n' * 10001, 'AST nodes')

    def test_working_legacy_demos(self):
        files = ['demo.ms', 'demo1_basic.ms', 'demo2_functions.ms',
                 'demo4_collections_foreach.ms', 'full_demo.ms', 'presentation_demo.ms']
        for name in files:
            result = subprocess.run([BINARY, str(ROOT / name)], capture_output=True, text=True, timeout=15)
            with self.subTest(demo=name):
                self.assertEqual(result.returncode, 0, result.stderr)

    def test_examples(self):
        for file in sorted((ROOT / 'examples').glob('*.ms')):
            result = subprocess.run([BINARY, str(file)], capture_output=True, text=True, timeout=15)
            with self.subTest(example=file.name):
                if file.name == 'validation_errors.ms':
                    self.assertEqual(result.returncode, 1)
                    self.assertEqual(result.stdout, '')
                else:
                    self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == '__main__':
    unittest.main(verbosity=2)
