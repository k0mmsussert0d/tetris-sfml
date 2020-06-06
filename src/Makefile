CXX=g++
FLAGS=-std=c++17
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

ODIR=obj

all: tetris

debug: FLAGS += -DDEBUG -g
debug: tetris

tetris: tetris.o block.o fields.o blockfactory.o stats.o window.o
	$(CXX) -o tetris $(ODIR)/tetris.o $(ODIR)/block.o $(ODIR)/fields.o $(ODIR)/blockfactory.o $(ODIR)/stats.o $(ODIR)/window.o $(FLAGS) $(LIBS)

tetris.o: block.o fields.o blockfactory.o stats.o window.o
	$(CXX) -c -o $(ODIR)/tetris.o tetris.cpp $(FLAGS)

blockfactory.o: block.o
	$(CXX) -c -o $(ODIR)/blockfactory.o blockfactory.cpp $(FLAGS)

fields.o: block.o
	$(CXX) -c -o $(ODIR)/fields.o fields.cpp $(FLAGS)

block.o:
	$(CXX) -c -o $(ODIR)/block.o block.cpp $(FLAGS)

stats.o:
	$(CXX) -c -o $(ODIR)/stats.o stats.cpp $(FLAGS)

window.o:
	$(CXX) -c -o $(ODIR)/window.o window.cpp $(FLAGS)

clean:
	@echo "**Removing object files and executable..."
