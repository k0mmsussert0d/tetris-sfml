CC=g++
CFLAGS=-std=c++17
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

ODIR=obj

all: tetris

debug: CFLAGS += -DDEBUG -g
debug: tetris

%.o: %.cpp
	$(CC) -c $< -o $(ODIR)/$@ $(CFLAGS)

%.o: %.hpp
	$(CC) -c $< -o $(ODIR)/$@ $(CFLAGS)

tetris: tetris.o block.o blockfactory.o fields.o stats.o window.o
	$(CC) -o tetris $(ODIR)/tetris.o $(ODIR)/block.o $(ODIR)/blockfactory.o $(ODIR)/fields.o $(ODIR)/stats.o $(ODIR)/window.o $(CFLAGS) $(LIBS)

clean:
	@echo "**Removing object files and executable..."
