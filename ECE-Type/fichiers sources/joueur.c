#include "joueur.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdio.h>  

joueur_t creer_joueur() {
    joueur_t j = {100, 300, 0, 0, NULL};

    j.sprite = al_load_bitmap("player.png");
    if (!j.sprite) {
        fprintf(stderr, "Erreur : impossible de charger player.png\n");
        // fallback : carré bleu
        j.sprite = al_create_bitmap(40, 20);
        al_set_target_bitmap(j.sprite);
        al_clear_to_color(al_map_rgb(0, 150, 255));
        al_set_target_backbuffer(al_get_current_display());
    }

    return j;
}


void maj_joueur(joueur_t *j) {
    ALLEGRO_KEYBOARD_STATE ks;
    al_get_keyboard_state(&ks);

    if (al_key_down(&ks, ALLEGRO_KEY_UP)) j->y -= 5;
    if (al_key_down(&ks, ALLEGRO_KEY_DOWN)) j->y += 5;
    if (al_key_down(&ks, ALLEGRO_KEY_LEFT)) j->x -= 5;
    if (al_key_down(&ks, ALLEGRO_KEY_RIGHT)) j->x += 5;

    if (j->y < 0) j->y = 0;
    if (j->y > 580) j->y = 580;
}

void dessiner_joueur(joueur_t *j) {
    al_draw_bitmap(j->sprite, j->x, j->y, 0);
}
