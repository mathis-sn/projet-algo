#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "globals.h"

#define EXPLOSION_FRAMES 8
#define EXPLOSION_DUREE  40  /* frames totales */

typedef struct {
    float x, y;
    bool  actif;
    int   timer;
    int   frame;
    ALLEGRO_BITMAP *sprite; /* spritesheet ou bitmap unique */
} explosion_t;

void init_explosions(explosion_t exps[]);
void creer_explosion(explosion_t exps[], float x, float y);
void maj_explosions(explosion_t exps[]);
void dessiner_explosions(explosion_t exps[]);
void detruire_explosions(explosion_t exps[]);

#endif /* EXPLOSION_H */
