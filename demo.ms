OPENING_CREDITS
SCREENPLAY

CHARACTER @hero <- "Ava"
SCENE @intro <- "Opening scene"
SCENE @scene <- "Premiere"
DIALOGUE @line <- "Welcome"

FUNCTION @scoreMovie(RATING @rating) RETURNS RATING FRAME
RETURN @rating + 1
ENDFRAME ENDFUNCTION

RATING @rating <- @scoreMovie(2 + 1)
BUDGET @budget <- 5000000

GENRE_COLLECTION @genres <- {"Action","Drama"}

ADD_TO @genres "Comedy"

SCENE_IF (@rating GREATER_THAN 3.0) FRAME
AWARD "Excellent Film"
ENDFRAME
OTHERWISE FRAME
REVIEW "Needs Improvement"
ENDFRAME

FOR_EACH_SCENE IN @genres REEL
ANALYZE @scene
PRINT "Scene analyzed"
ENDREEL

WHILE (@rating GREATER_THAN 3) TAKE
BUILD_SUSPENSE
@rating <- 3
ENDTAKE

ENDSCREENPLAY
FINAL_CREDITS
