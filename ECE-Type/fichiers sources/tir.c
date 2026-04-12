#include "tir.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

void init_tirs(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        tirs[i].actif = false;

        // Chargement du sprite du tir
        tirs[i].sprite = al_load_bitmap("bullet.png");
        if (!tirs[i].sprite) {
            fprintf(stderr, "Erreur : impossible de charger bullet.png\n");

            // Fallback : petit rectangle jaune si image manquante
            tirs[i].sprite = al_create_bitmap(10, 3);
            al_set_target_bitmap(tirs[i].sprite);
            al_clear_to_color(al_map_rgb(255, 255, 0));
            al_set_target_backbuffer(al_get_current_display());
        }
    }
}

void tirer(tir_t tirs[], float x, float y) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        if (!tirs[i].actif) {
            tirs[i].x = x + 40;
            tirs[i].y = y + 8;
            tirs[i].actif = true;
            break;
        }
    }
}

void maj_tirs(tir_t tirs[]) {
    for (int i = 0; i < NB_TIRS_MAX; i++) {
        if (tirs[i].actif) {
            tirs[i].x += 10;
            if (tirs[i].x > 800)
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
        if (tirs[i].sprite)
            al_destroy_bitmap(tirs[i].sprite);
    }
}
