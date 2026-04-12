#ifndef TIR_H
#define TIR_H
#include <allegro5/allegro.h>
#include <stdbool.h>

#define NB_TIRS_MAX 20

typedef struct {
    float x, y;
    bool actif;
    ALLEGRO_BITMAP *sprite;
} tir_t;

void init_tirs(tir_t tirs[]);
void tirer(tir_t tirs[], float x, float y);
void maj_tirs(tir_t tirs[]);
void dessiner_tirs(tir_t tirs[]);
void detruire_tirs(tir_t tirs[]);

#endif
