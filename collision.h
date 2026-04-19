#ifndef COLLISION_H
#define COLLISION_H

#include "joueur.h"
#include "ennemi.h"
#include "tir.h"
#include "explosion.h"
#include <stdbool.h>

/* Renvoie true si collision AABB entre deux rectangles */
bool collision_rect(float ax, float ay, float aw, float ah,
                    float bx, float by, float bw, float bh);

/* Tirs joueur vs ennemis */
void gerer_collisions_tirs_ennemis(tir_t tirs_j[], ennemi_t ennemis[], int nb_ennemis,
                                    explosion_t exps[], joueur_t *j);

/* Tirs joueur vs boss */
void gerer_collisions_tirs_boss(tir_t tirs_j[], boss_t *boss,
                                 explosion_t exps[], joueur_t *j);

/* Tirs ennemis vs joueur */
void gerer_collisions_tirs_ennemis_joueur(tir_t tirs_e[], joueur_t *j,
                                           explosion_t exps[]);

/* Joueur vs ennemis */
void gerer_collisions_joueur_ennemis(joueur_t *j, ennemi_t ennemis[], int nb_ennemis,
                                      explosion_t exps[]);

/* Joueur vs boss (contact) */
void gerer_collision_joueur_boss(joueur_t *j, boss_t *b, explosion_t exps[]);

#endif /* COLLISION_H */
