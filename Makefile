#Zatacka Makefile
#Copyright by Mage 2006

SRC = .
OBJ = $(SRC)/obj

rm = $(SRC)/bin/rm -f
ln = $(SRC)/bin/ln -s

CC = g++
DEFS =
INCLUDES =  -I $(SRC)
OPTIONS =


OS = unix
ifeq ($(OS), windows)
	PROGNAME = zatacka.exe
	LIBS = `sdl-config --libs` -lSDL_ttf -lSDL_mixer
else
	ifeq ($(OS), unix)
		PROGNAME = zatacka
		LIBS = `sdl-config --libs` -lSDL_ttf -lSDL_mixer
	endif
endif

RELEASE = 0
ifeq ($(RELEASE), 1)
	OPTIONS += -O3
else
	DEFS += -DDEBUG_ACTIVE=1
	OPTIONS += -ggdb
endif

DEFINES = $(INCLUDES) $(DEFS) $(OPTIONS)
CFLAGS = $(DEFINES) `sdl-config --cflags` -Wall

OBJS = $(OBJ)/exception.o \
	$(OBJ)/itemEcran.o \
	$(OBJ)/ecran.o \
	$(OBJ)/texte.o \
	$(OBJ)/option.o \
	$(OBJ)/serpent.o \
	$(OBJ)/audio.o \
	$(OBJ)/jeu.o \
	$(OBJ)/zatacka.o \
	$(OBJ)/regle.o \
	$(OBJ)/reglecollision.o \
	$(OBJ)/regleinitialisation.o \
	$(OBJ)/reglepoints.o \
	$(OBJ)/gestionnaire.o \
	$(OBJ)/main.o

$(OBJ)/%.o: %.cpp

	@$(CC) $(CFLAGS) -c $*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/jeu/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/jeu/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/serpent/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/serpent/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/regle/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/regle/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

$(OBJ)/%.o: $(SRC)/audio/%.cpp
	$(CC) $(CFLAGS) -c $(SRC)/audio/$*.cpp
	mv $*.o $(OBJ)

$(OBJ)/%.o: $(SRC)/util/%.cpp
	@$(CC) $(CFLAGS) -c $(SRC)/util/$*.cpp
	@mv $*.o $(OBJ)
	@echo -- $*.o done

# Règles de dépendance
#$(OBJ)/main.o : $(SRC)/jeu/jeu.h
#$(OBJ)/jeu.o : $(SRC)/jeu/jeu.* $(OBJ)/jeu/texte.h \
#	$(SRC)/jeu/option.h $(SRC)/exception.h
#$(OBJ)/texte.o : $(SRC)/jeu/texte.h
#$(OBJ)/option.o : $(SRC)/jeu/option.h $(SRC)/jeu/texte.h
#$(OBJ)/exception.o : $(SRC)/exceptions/exception.h

# Commandes executables

all: $(OBJS)
	@$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)
	@echo -- program created as: $(PROGNAME) --

prepare:
	@if test ! -d $(OBJ); then mkdir $(OBJ); echo -- obj/ created --; fi

clean:
	@rm -f $(OBJ)/*.o
	@rm -f $(PROGNAME)
	@echo -- .o and program erased --

install: prepare all

reset: clean all
