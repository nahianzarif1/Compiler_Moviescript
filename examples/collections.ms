OPENING_CREDITS
SCREENPLAY

GENRE_COLLECTION @genres <- {}
ADD_TO @genres "Action"
ADD_TO @genres "Drama"
PRINT @genres
PRINT COUNT(@genres)
PRINT CONTAINS(@genres, "Drama")

FOR_EACH_SCENE @genre IN @genres REEL
    PRINT @genre
ENDREEL

// The original iterator-free syntax also runs once per item.
WHOLE @count <- 0
FOR_EACH_SCENE IN @genres REEL
    @count <- @count + 1
ENDREEL
PRINT @count

ENDSCREENPLAY
FINAL_CREDITS
