CC = g++
LD = g++
CFLAGS = -c -g -std=c++11 -pedantic-errors -Wall
LFLAGS = -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

OBJS = Controller.o Game_board.o songinfoparser.o Memory_handler.o main.o Song.o Game.o Mem_game.o React_game.o Utility.o Main_menu.o Light_cont.o Arduino_cont.o
PROG = melodimemori

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -o $(PROG)

Controller.o: Memory_handler.o songinfoparser.o Game_board.o Controller.cpp Controller.h Main_menu.o Utility.o Light_cont.o Arduino_cont.o
	$(LD) $(CFLAGS) Controller.cpp -o Controller.o

Memory_handler.o: Utility.o Memory_handler.cpp Memory_handler.h Game_board.h
	$(LD) $(CFLAGS) Memory_handler.cpp -o Memory_handler.o

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

Main_menu.o: Main_menu.cpp Main_menu.h
	$(LD) $(CFLAGS) Main_menu.cpp -o Main_menu.o

Light_cont.o: Light_cont.cpp Light_cont.h
	$(LD) $(CFLAGS) Light_cont.cpp -o Light_cont.o

Arduino_cont.o: Arduino_cont.cpp Arduino_cont.h
	$(LD) $(CFLAGS) Arduino_cont.cpp -o Arduino_cont.o

clean:
	rm -f *.o
real_clean:
	rm -f $(PROG)
	rm -f *.o
