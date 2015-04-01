CC = g++
LD = g++
CFLAGS = -c -g -std=c++11 -pedantic-errors -Wall
LFLAGS = -g
LIBS = -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window

OBJS = Controller.o Game_board.o songinfoparser.o memory_handler.o main.o qdsleep.o Song.o Game.o Mem_game.o React_game.o Utility.o
PROG = mem_demo

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -o $(PROG)

Controller.o: memory_handler.o songinfoparser.o Game_board.o qdsleep.o Controller.cpp Controller.h
	$(LD) $(CFLAGS) Controller.cpp -o Controller.o

memory_handler.o: qdsleep.o memory_handler.cpp memory_handler.h Game_board.h
	$(LD) $(CFLAGS) memory_handler.cpp -o memory_handler.o

qdsleep.o: qdsleep.h qdsleep.cpp
	$(LD) $(CFLAGS) qdsleep.cpp -o qdsleep.o

songinfoparser.o: songinfoparser.cpp songinfoparser.h Note.h 
	$(LD) $(CFLAGS) songinfoparser.cpp -o songinfoparser.o

Game_board.o: Game_board.cpp Game_board.h
	$(LD) $(CFLAGS) Game_board.cpp -o Game_board.o
main.o: Controller.cpp Controller.h main.cpp
	$(LD) $(CFLAGS) main.cpp -o main.o

Song.o: Song.cpp Song.h Note.h
	$(LD) $(CFLAGS) Song.cpp -o Song.o
Game.o: Game.cpp Game.h
	$(LD) $(CFLAGS) Game.cpp -o Game.o
Mem_game.o: Mem_game.cpp Mem_game.h
	$(LD) $(CFLAGS) Mem_game.cpp -o Mem_game.o
React_game.o: React_game.cpp React_game.h
	$(LD) $(CFLAGS) React_game.cpp -o React_game.o
Utility.o: Utility.cpp Utility.h
	$(LD) $(CFLAGS) Utility.cpp -o Utility.o

clean:
	rm -f *.o
real_clean:
	rm -f $(PROG)
	rm -f *.o
