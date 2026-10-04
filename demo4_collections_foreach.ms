OPENING_CREDITS
SCREENPLAY

SCENE @scene <- "Premiere"
GENRE_COLLECTION @genres <- {"Action","Drama"}
ADD_TO @genres "Comedy"

FOR_EACH_SCENE IN @genres REEL
ANALYZE @scene
PRINT "Scene analyzed"
ENDREEL

ENDSCREENPLAY
FINAL_CREDITS
