#include "collision.h"

bool collision_rect(float ax, float ay, float aw, float ah,
                    float bx, float by, float bw, float bh) {
    return (ax < bx + bw) && (ax + aw > bx) &&
           (ay < by + bh) && (ay + ah > by);
}

void gerer_collisions_tirs_ennemis(tir_t tirs_j[], ennemi_t ennemis[], int nb_ennemis,
                                    explosion_t exps[], joueur_t *j) {
    for (int t = 0; t < NB_TIRS_MAX; t++) {
        if (!tirs_j[t].actif) continue;
        for (int e = 0; e < nb_ennemis; e++) {
            if (!ennemis[e].actif) continue;
            if (collision_rect(tirs_j[t].x, tirs_j[t].y, 12, 4,
                               ennemis[e].x, ennemis[e].y, 32, 32)) {
                tirs_j[t].actif = false;
                ennemis[e].pv--;
                if (ennemis[e].pv <= 0) {
                    creer_explosion(exps, ennemis[e].x + 16, ennemis[e].y + 16);
                    ennemis[e].actif = false;
                    j->score += 100;
                }
                break;
            }
        }
    }
}

void gerer_collisions_tirs_boss(tir_t tirs_j[], boss_t *boss,
                                 explosion_t exps[], joueur_t *j) {
    if (!boss->actif) return;
    for (int t = 0; t < NB_TIRS_MAX; t++) {
        if (!tirs_j[t].actif) continue;
        if (collision_rect(tirs_j[t].x, tirs_j[t].y, 12, 4,
                           boss->x, boss->y, 80, 80)) {
            tirs_j[t].actif = false;
            boss->pv--;
            creer_explosion(exps, tirs_j[t].x, tirs_j[t].y);
            if (boss->pv <= 0) {
                creer_explosion(exps, boss->x + 40, boss->y + 40);
                boss->actif = false;
                j->score += 1000;
            }
            j->score += 10;
        }
    }
}

void gerer_collisions_tirs_ennemis_joueur(tir_t tirs_e[], joueur_t *j,
                                           explosion_t exps[]) {
    if (!j->vivant || j->invincible) return;
    for (int t = 0; t < NB_TIRS_ENNEMIS; t++) {
        if (!tirs_e[t].actif) continue;
        if (collision_rect(tirs_e[t].x, tirs_e[t].y, 10, 4,
                           j->x + 4, j->y + 2, 32, 16)) {
            tirs_e[t].actif = false;
            creer_explosion(exps, j->x + 20, j->y + 10);
            j->vivant = false;
            j->vies--;
        }
    }
}

void gerer_collisions_joueur_ennemis(joueur_t *j, ennemi_t ennemis[], int nb_ennemis,
                                      explosion_t exps[]) {
    if (!j->vivant || j->invincible) return;
    for (int e = 0; e < nb_ennemis; e++) {
        if (!ennemis[e].actif) continue;
        if (collision_rect(j->x + 4, j->y + 2, 32, 16,
                           ennemis[e].x, ennemis[e].y, 32, 32)) {
            creer_explosion(exps, j->x + 20, j->y + 10);
            creer_explosion(exps, ennemis[e].x + 16, ennemis[e].y + 16);
            ennemis[e].actif = false;
            j->vivant = false;
            j->vies--;
        }
    }
}

void gerer_collision_joueur_boss(joueur_t *j, boss_t *b, explosion_t exps[]) {
    if (!j->vivant || j->invincible || !b->actif || !b->apparu) return;
    if (collision_rect(j->x + 4, j->y + 2, 32, 16,
                       b->x, b->y, 80, 80)) {
        creer_explosion(exps, j->x + 20, j->y + 10);
        j->vivant = false;
        j->vies--;
    }
}
