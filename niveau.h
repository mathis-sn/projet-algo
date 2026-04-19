#ifndef NIVEAU_H
#define NIVEAU_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "globals.h"
#include "joueur.h"
#include "ennemi.h"
#include "tir.h"
#include "explosion.h"

/* Résultat retourné par lancer_niveau */
typedef enum {
    NIVEAU_VICTOIRE,  /* niveau terminé, passer au suivant */
    NIVEAU_GAME_OVER, /* plus de vies */
    NIVEAU_MENU       /* Échap pressé */
} resultat_niveau_e;

typedef struct {
    int            numero;      /* 1, 2 ou 3 */
    float          vit_scroll;
    ALLEGRO_BITMAP *background;
    ennemi_t       ennemis[NB_ENNEMIS_MAX];
    int            nb_ennemis;
    boss_t         boss;
    bool           phase_boss;  /* scrolling arrêté, combat boss */
    float          bg_x;
    int            timer_spawn; /* compteur pour spawner des vagues */
    int            vague;       /* indice de vague courante */
} niveau_t;

resultat_niveau_e lancer_niveau(ALLEGRO_DISPLAY *display, int numero, joueur_t *joueur);

#endif /* NIVEAU_H */
