#include "ennemi.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

ennemi_t creer_ennemi(float x, float y) {
    ennemi_t e = {x, y, -3, NULL};

    e.sprite = al_load_bitmap("enemy.png");
    if (!e.sprite) {
        fprintf(stderr, "Erreur : impossible de charger assets/enemy.png\n");
        // fallback rouge
        e.sprite = al_create_bitmap(30, 30);
        al_set_target_bitmap(e.sprite);
        al_clear_to_color(al_map_rgb(255, 60, 60));
        al_set_target_backbuffer(al_get_current_display());
    }

    return e;
}


void maj_ennemi(ennemi_t *e) {
    e->x += e->vx;
    if (e->x < -30) e->x = 850; // Recyclage des ennemis
}

void dessiner_ennemi(ennemi_t *e) {
    al_draw_bitmap(e->sprite, e->x, e->y, 0);
}
