CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2
LDFLAGS = -lallegro -lallegro_image -lallegro_font -lallegro_primitives \
          -lallegro_ttf -lallegro_acodec -lallegro_audio -lm

SRC = main.c menu.c niveau.c joueur.c ennemi.c tir.c collision.c \
      explosion.c ressources.c

OBJ = $(SRC:.c=.o)

TARGET = ShootEmUp

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: clean
