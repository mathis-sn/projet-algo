CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lallegro -lallegro_image -lallegro_font -lallegro_primitives -lallegro_ttf -lallegro_acodec -lallegro_audio

SRC = main.c jeu.c joueur.c ennemi.c tir.c collision.c ressources.c
OBJ = $(SRC:.c=.o)

ShootEmUp: $(OBJ)
	$(CC) $(OBJ) -o ShootEmUp $(LDFLAGS)

clean:
	rm -f *.o ShootEmUp
