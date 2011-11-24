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
LIBS = `sdl-config --libs` -lSDL_ttf
BIN = /usr/bin
DEST = /usr/local/games/zatac
else
	ifeq ($(OS), unix)
	PROGNAME = zatacka
	LIBS = `sdl-config --libs` -lSDL_ttf
	BIN = /usr/bin
	DEST = /usr/local/games/zatacka
	endif
endif


DEBUG = -ggdb
DEFINES = $(INCLUDES) $(DEFS) -DSYS_UNIX=1 $(DEBUG)
CFLAGS = $(DEFINES) `sdl-config --cflags` -Wall

OBJS = $(OBJ)/exception.o \
	$(OBJ)/itemEcran.o \
	$(OBJ)/ecran.o \
	$(OBJ)/texte.o \
	$(OBJ)/option.o \
	$(OBJ)/serpent.o \
	$(OBJ)/jeu.o \
	$(OBJ)/zatacka.o \
	$(OBJ)/main.o

$(OBJ)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $*.cpp
	mv $*.o $(OBJ)
	
$(OBJ)/%.o: $(SRC)/jeu/%.cpp
	$(CC) $(CFLAGS) -c $(SRC)/jeu/$*.cpp
	mv $*.o $(OBJ)

$(OBJ)/%.o: $(SRC)/serpent/%.cpp
	$(CC) $(CFLAGS) -c $(SRC)/serpent/$*.cpp
	mv $*.o $(OBJ)

$(OBJ)/%.o: $(SRC)/util/%.cpp
	$(CC) $(CFLAGS) -c $(SRC)/util/$*.cpp
	mv $*.o $(OBJ)
	
# Règles de dépendance
#$(OBJ)/main.o : $(SRC)/jeu/jeu.h 
#$(OBJ)/jeu.o : $(SRC)/jeu/jeu.* $(OBJ)/jeu/texte.h \
#	$(SRC)/jeu/option.h $(SRC)/exception.h
#$(OBJ)/texte.o : $(SRC)/jeu/texte.h
#$(OBJ)/option.o : $(SRC)/jeu/option.h $(SRC)/jeu/texte.h
#$(OBJ)/exception.o : $(SRC)/exceptions/exception.h

# Commandes executables

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

prepare:
	-if  ! [ -d $(OBJ) ]; then mkdir $(OBJ); fi

clean:
	rm -f $(OBJ)/*.o
	rm -f $(PROGNAME)

install: prepare all

reset: clean all

