#ifndef JOUEUR_H
#define JOUEUR_H
#include <allegro5/allegro.h>

typedef struct {
    float x, y;
    float vx, vy;
    ALLEGRO_BITMAP *sprite;
} joueur_t;

joueur_t creer_joueur();
void maj_joueur(joueur_t *j);
void dessiner_joueur(joueur_t *j);

#endif
