OPENING_CREDITS
SCREENPLAY

// A complete movie report, using checked values and reusable functions.
CHARACTER @director <- "Ava"
SCENE @premiere <- "Opening night"
DIALOGUE @title <- "The Last Reel"
RATING @audience <- 4.5
RATING @critics <- 4
BUDGET @budget <- 5000000
STATUS @release <- SUCCESS
SIGNAL @ready <- TRUE
GENRE @favorite <- "Drama"
WHOLE @reviewCount <- 0
GENRE_COLLECTION @genres <- {"Drama", "Adventure"}
ADD_TO @genres "Mystery"

FUNCTION @average(RATING @a, RATING @b) RETURNS RATING FRAME
    RATING @mean <- (@a + @b) / 2
    RETURN @mean
ENDFRAME ENDFUNCTION

FUNCTION @verdict(RATING @score) RETURNS DIALOGUE FRAME
    SCENE_IF (@score GREATER_EQUAL 4) FRAME
        RETURN "Audience favorite"
    ENDFRAME OTHERWISE FRAME
        RETURN "Room to improve"
    ENDFRAME
ENDFRAME ENDFUNCTION

RATING @score <- @average(@audience, @critics)
PRINT "Movie: " + @title
PRINT "Directed by: " + @director
ANALYZE @premiere
ANALYZE @budget
ANALYZE @release
PRINT @score
PRINT @verdict(@score)
PRINT COUNT(@genres)

FOR_EACH_SCENE @genre IN @genres REEL
    PRINT "Genre: " + @genre
    @reviewCount <- @reviewCount + 1
ENDREEL
ASSERT (@reviewCount IS 3, "Every genre must be reviewed")
ASSERT (CONTAINS(@genres, @favorite), "Favorite genre must be present")

SCENE_IF (@ready AND @release IS SUCCESS AND @score GREATER_EQUAL 4) FRAME
    AWARD "Festival selection"
ENDFRAME

WHOLE @countdown <- 2
WHILE (@countdown GREATER_THAN 0) TAKE
    BUILD_SUSPENSE
    @countdown <- @countdown - 1
ENDTAKE
ENTER_STAGE

ENDSCREENPLAY
FINAL_CREDITS
