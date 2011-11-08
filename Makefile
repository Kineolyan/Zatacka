#Zatacka Makefile
#Copyright by Mage 2006

SRC = .
OBJ = $(SRC)/obj
rm = $(SRC)/bin/rm -f
ln = $(SRC)/bin/ln -s
CC = g++ 
DEFS =  
INCLUDES =  -I $(SRC)

# Temporary
OS = unix
MODE = debug

ifeq ($(OS), windows)
PROGNAME = zatacka.exe
LIBS = `sdl-config --libs` -lSDL_image -lSDL_ttf
BIN = /usr/bin
DEST = /usr/local/games/zatac
else
ifeq ($(OS), unix)
PROGNAME = zatacka
LIBS = `sdl-config --libs` -lSDL_image -lSDL_ttf
BIN = /usr/bin
DEST = /usr/local/games/zatacka
endif
endif


DEBUG = -ggdb
DEFINES = $(INCLUDES) $(DEFS) -DSYS_UNIX=1 $(DEBUG)
CFLAGS = $(DEFINES) `sdl-config --cflags` -Wall

OBJS = $(OBJ)/main.o $(OBJ)/jeu.o $(OBJ)/texte.o

$(OBJ)/SDL_prim.o: $(SRC)/SDL_lib/SDL_prim.c
	$(CC) $(CFLAGS) -c $(SRC)/SDL_lib/SDL_prim.c
	mv $*.o $(OBJ)

$(OBJ)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $*.cpp
	mv $*.o $(OBJ)
	
$(OBJ)/%.o: $(SRC)/jeu/%.cpp
	$(CC) $(CFLAGS) -c $(SRC)/jeu/$*.cpp
	mv $*.o $(OBJ)

$(OBJ)/%.o: $(SRC)/serpent/%.cpp
	$(CC) $(CFLAGS) -c $(SRC)/serpent/$*.cpp
	mv $*.o $(OBJ)

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

prepare:
	-if  ! [ -d $(OBJ) ]; then mkdir $(OBJ); fi

clean:
	rm -f $(OBJ)/*.o

install: prepare all

