CC=gcc
CFLAGS=-I -c -fmessage-length=0 -D_SDL_main_h -lSDL -lSDL_ttf -lSDL_gfx -lSDL_image
DEPS = game.h field.h cell.h allocate_field.h GUI.h
OBJ = game.o field.o allocate_field.o GUI.o 
OUTPUT = game



all: $(OBJ)
	@echo Programma aanmaken
	gcc -o $@ $^ $(CFLAGS)
	
	
game.o : game.c field.h GUI.h cell.h
	@echo Bezig met game.o te compileren
	$(CC) -c -o game.o game.c

field.o : field.c allocate_field.h cell.h
	@echo Bezig met field.o te compileren
	$(CC) -c -o field.o field.c

allocate_field.o : allocate_field.c field.h cell.h
	@echo Bezig met allocate_field.o te compileren
	$(CC) -c -o allocate_field.o allocate_field.c

GUI.o : GUI.c field.h cell.h game.h
	@echo Bezig met GUI.o te compileren
	$(CC) -L/home/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf -lSDL_gfx -c -o GUI.o GUI.c


.PHONY : clean	
clean:
	@echo Cleaning... Object files verwijderen	
	rm -f *.o
	rm -f $(OUTPUT)