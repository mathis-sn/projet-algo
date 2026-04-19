#include "tir.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

/* ---- TIRS JOUEUR ---- */

void init_tirs(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        tirs[i].actif = false;
        tirs[i].sprite = al_load_bitmap("bullet.png");
        if (!tirs[i].sprite) {
            fprintf(stderr, "Erreur : impossible de charger bullet.png\n");
            tirs[i].sprite = al_create_bitmap(12, 4);
            al_set_target_bitmap(tirs[i].sprite);
            al_clear_to_color(al_map_rgb(255, 220, 50));
            al_set_target_backbuffer(al_get_current_display());
        }
    }
}

void tirer(tir_t tirs[], float x, float y) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        if (!tirs[i].actif) {
            tirs[i].x   = x + 42;
            tirs[i].y   = y + 8;
            tirs[i].vx  = 14.0f;
            tirs[i].vy  = 0.0f;
            tirs[i].actif = true;
            break;
        }
    }
}

void maj_tirs(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        if (tirs[i].actif) {
            tirs[i].x += tirs[i].vx;
            if (tirs[i].x > JEU_LARGEUR + 20)
                tirs[i].actif = false;
        }
    }
}

void dessiner_tirs(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        if (tirs[i].actif)
            al_draw_bitmap(tirs[i].sprite, tirs[i].x, tirs[i].y, 0);
    }
}

void detruire_tirs(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        if (tirs[i].sprite) {
            al_destroy_bitmap(tirs[i].sprite);
            tirs[i].sprite = NULL;
        }
    }
}

/* ---- TIRS ENNEMIS ---- */

void init_tirs_ennemis(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_ENNEMIS; i++) {
        tirs[i].actif = false;
        tirs[i].sprite = al_load_bitmap("enemy_bullet.png");
        if (!tirs[i].sprite) {
            tirs[i].sprite = al_create_bitmap(10, 4);
            al_set_target_bitmap(tirs[i].sprite);
            al_clear_to_color(al_map_rgb(255, 60, 60));
            al_set_target_backbuffer(al_get_current_display());
        }
    }
}

void tirer_ennemi(tir_t tirs[], float x, float y, float vx, float vy) {
    for (int i = 0; i < NB_TIRS_ENNEMIS; i++) {
        if (!tirs[i].actif) {
            tirs[i].x  = x;
            tirs[i].y  = y;
            tirs[i].vx = vx;
            tirs[i].vy = vy;
            tirs[i].actif = true;
            break;
        }
    }
}

void maj_tirs_ennemis(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_ENNEMIS; i++) {
        if (tirs[i].actif) {
            tirs[i].x += tirs[i].vx;
            tirs[i].y += tirs[i].vy;
            if (tirs[i].x < -20 || tirs[i].x > JEU_LARGEUR + 20 ||
                tirs[i].y < -20 || tirs[i].y > JEU_HAUTEUR + 20)
                tirs[i].actif = false;
        }
    }
}

void dessiner_tirs_ennemis(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_ENNEMIS; i++) {
        if (tirs[i].actif)
            al_draw_bitmap(tirs[i].sprite, tirs[i].x, tirs[i].y, 0);
    }
}

void detruire_tirs_ennemis(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_ENNEMIS; i++) {
        if (tirs[i].sprite) {
            al_destroy_bitmap(tirs[i].sprite);
            tirs[i].sprite = NULL;
        }
    }
}
