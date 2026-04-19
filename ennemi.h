#ifndef ENNEMI_H
#define ENNEMI_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "globals.h"

typedef enum {
    ENNEMI_VOLANT,   /* se déplace horizontalement */
    ENNEMI_FIXE,     /* tourelle fixe */
    ENNEMI_SINUSOIDE /* trajectoire ondulante */
} type_ennemi_e;

typedef struct {
    float x, y;
    float vx, vy;
    float base_y;        /* pour le mouvement sinusoïdal */
    float angle;         /* phase sinusoïde */
    int   pv;            /* points de vie */
    bool  actif;
    type_ennemi_e type;
    int   timer_tir;     /* cooldown avant prochain tir */
    int   cadence_tir;   /* frames entre chaque tir */
    ALLEGRO_BITMAP *sprite;
} ennemi_t;

typedef struct {
    float x, y;
    float vx, vy;         /* oscillation verticale */
    float base_y;
    float angle;
    int   pv;
    int   pv_max;
    bool  actif;
    bool  apparu;         /* le boss est entré en jeu */
    int   phase;          /* phases d'attaque */
    int   timer_tir;
    int   cadence_tir;
    ALLEGRO_BITMAP *sprite;
    ALLEGRO_BITMAP *sprite_endommage;
} boss_t;

/* Ennemis */
void init_ennemis(ennemi_t ennemis[]);
ennemi_t creer_ennemi(float x, float y, type_ennemi_e type, int pv, int cadence);
void maj_ennemis(ennemi_t ennemis[], int nb);
void dessiner_ennemis(ennemi_t ennemis[], int nb);
void detruire_ennemis(ennemi_t ennemis[], int nb);

/* Boss */
boss_t  creer_boss(float x, float y);
void    maj_boss(boss_t *b);
void    dessiner_boss(boss_t *b);
void    detruire_boss(boss_t *b);

#endif /* ENNEMI_H */
