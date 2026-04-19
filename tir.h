#ifndef TIR_H
#define TIR_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "globals.h"

typedef struct {
    float x, y;
    float vx, vy;
    bool  actif;
    ALLEGRO_BITMAP *sprite;
} tir_t;

/* Tirs joueur */
void init_tirs(tir_t tirs[]);
void tirer(tir_t tirs[], float x, float y);
void maj_tirs(tir_t tirs[]);
void dessiner_tirs(tir_t tirs[]);
void detruire_tirs(tir_t tirs[]);

/* Tirs ennemis */
void init_tirs_ennemis(tir_t tirs[]);
void tirer_ennemi(tir_t tirs[], float x, float y, float vx, float vy);
void maj_tirs_ennemis(tir_t tirs[]);
void dessiner_tirs_ennemis(tir_t tirs[]);
void detruire_tirs_ennemis(tir_t tirs[]);

#endif /* TIR_H */
