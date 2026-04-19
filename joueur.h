#ifndef JOUEUR_H
#define JOUEUR_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "globals.h"

typedef struct {
    float x, y;
    float vx, vy;
    int   vies;
    int   score;
    bool  invincible;       /* clignotement après respawn */
    int   timer_invincible; /* frames restantes */
    bool  vivant;
    ALLEGRO_BITMAP *sprite;
} joueur_t;

joueur_t creer_joueur(void);
void     maj_joueur(joueur_t *j);
void     dessiner_joueur(joueur_t *j);
void     detruire_joueur(joueur_t *j);
void     respawn_joueur(joueur_t *j);

#endif /* JOUEUR_H */
