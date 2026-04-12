#ifndef ENNEMI_H
#define ENNEMI_H
#include <allegro5/allegro.h>

typedef struct {
    float x, y;
    float vx;
    ALLEGRO_BITMAP *sprite;
} ennemi_t;

ennemi_t creer_ennemi(float x, float y);
void maj_ennemi(ennemi_t *e);
void dessiner_ennemi(ennemi_t *e);

#endif
