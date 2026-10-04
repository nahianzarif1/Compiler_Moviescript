OPENING_CREDITS
SCREENPLAY

// Nested calls, local variables, string returns, and recursion.
FUNCTION @factorial(WHOLE @n) RETURNS WHOLE FRAME
    SCENE_IF (@n LESS_EQUAL 1) FRAME
        RETURN 1
    ENDFRAME OTHERWISE FRAME
        RETURN @n * @factorial(@n - 1)
    ENDFRAME
ENDFRAME ENDFUNCTION

FUNCTION @greet(CHARACTER @name) RETURNS DIALOGUE FRAME
    DIALOGUE @message <- "Welcome, " + @name
    PRINT "Preparing greeting"
    RETURN @message
ENDFRAME ENDFUNCTION

PRINT @greet("Ava")
PRINT @factorial(5)
PRINT CLAMP(6, 0, 5)
PRINT LENGTH("MovieScript")

ENDSCREENPLAY
FINAL_CREDITS
