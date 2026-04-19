#include "joueur.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

joueur_t creer_joueur(void) {
    joueur_t j = {0};
    j.x     = 100.0f;
    j.y     = 300.0f;
    j.vies  = PV_JOUEUR_MAX;
    j.score = 0;
    j.vivant = true;
    j.invincible = false;
    j.timer_invincible = 0;

    j.sprite = al_load_bitmap("player.png");
    if (!j.sprite) {
        fprintf(stderr, "Erreur : impossible de charger player.png\n");
        j.sprite = al_create_bitmap(40, 20);
        al_set_target_bitmap(j.sprite);
        al_clear_to_color(al_map_rgb(0, 150, 255));
        al_set_target_backbuffer(al_get_current_display());
    }
    return j;
}

void respawn_joueur(joueur_t *j) {
    j->x = 100.0f;
    j->y = 300.0f;
    j->vivant = true;
    j->invincible = true;
    j->timer_invincible = 180; /* 3 secondes à 60fps */
}

void maj_joueur(joueur_t *j) {
    if (!j->vivant) return;

    ALLEGRO_KEYBOARD_STATE ks;
    al_get_keyboard_state(&ks);

    float speed = 5.0f;

    if (al_key_down(&ks, ALLEGRO_KEY_UP)    || al_key_down(&ks, ALLEGRO_KEY_Z)) j->y -= speed;
    if (al_key_down(&ks, ALLEGRO_KEY_DOWN)  || al_key_down(&ks, ALLEGRO_KEY_S)) j->y += speed;
    if (al_key_down(&ks, ALLEGRO_KEY_LEFT)  || al_key_down(&ks, ALLEGRO_KEY_Q)) j->x -= speed;
    if (al_key_down(&ks, ALLEGRO_KEY_RIGHT) || al_key_down(&ks, ALLEGRO_KEY_D)) j->x += speed;

    /* Bornes écran */
    if (j->x < 0)           j->x = 0;
    if (j->x > JEU_LARGEUR - 40) j->x = JEU_LARGEUR - 40;
    if (j->y < 0)           j->y = 0;
    if (j->y > JEU_HAUTEUR - 20) j->y = JEU_HAUTEUR - 20;

    /* Invincibilité temporaire */
    if (j->invincible) {
        j->timer_invincible--;
        if (j->timer_invincible <= 0) {
            j->invincible = false;
        }
    }
}

void dessiner_joueur(joueur_t *j) {
    if (!j->vivant) return;
    /* Clignotement pendant invincibilité */
    if (j->invincible && (j->timer_invincible / 5) % 2 == 0) return;
    al_draw_bitmap(j->sprite, j->x, j->y, 0);
}

void detruire_joueur(joueur_t *j) {
    if (j->sprite) {
        al_destroy_bitmap(j->sprite);
        j->sprite = NULL;
    }
}
