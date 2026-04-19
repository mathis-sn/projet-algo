#include "explosion.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

static ALLEGRO_BITMAP *sprite_cache_explosion = NULL;

static ALLEGRO_BITMAP *get_sprite_explosion(void) {
    if (!sprite_cache_explosion) {
        sprite_cache_explosion = al_load_bitmap("explosion.png");
        if (!sprite_cache_explosion) {
            /* Fallback : simple cercle orange */
            sprite_cache_explosion = al_create_bitmap(64, 64);
            al_set_target_bitmap(sprite_cache_explosion);
            al_clear_to_color(al_map_rgba(0, 0, 0, 0));
            al_draw_filled_circle(32, 32, 30, al_map_rgb(255, 140, 0));
            al_draw_filled_circle(32, 32, 18, al_map_rgb(255, 220, 0));
            al_draw_filled_circle(32, 32, 8,  al_map_rgb(255, 255, 255));
            al_set_target_backbuffer(al_get_current_display());
        }
    }
    return sprite_cache_explosion;
}

void init_explosions(explosion_t exps[]) {
    for (int i = 0; i < NB_EXPLOSIONS_MAX; i++) {
        exps[i].actif  = false;
        exps[i].sprite = NULL;
        exps[i].timer  = 0;
        exps[i].frame  = 0;
    }
}

void creer_explosion(explosion_t exps[], float x, float y) {
    for (int i = 0; i < NB_EXPLOSIONS_MAX; i++) {
        if (!exps[i].actif) {
            exps[i].x      = x;
            exps[i].y      = y;
            exps[i].actif  = true;
            exps[i].timer  = EXPLOSION_DUREE;
            exps[i].frame  = 0;
            exps[i].sprite = get_sprite_explosion();
            break;
        }
    }
}

void maj_explosions(explosion_t exps[]) {
    for (int i = 0; i < NB_EXPLOSIONS_MAX; i++) {
        if (exps[i].actif) {
            exps[i].timer--;
            exps[i].frame = (EXPLOSION_DUREE - exps[i].timer) * EXPLOSION_FRAMES / EXPLOSION_DUREE;
            if (exps[i].timer <= 0)
                exps[i].actif = false;
        }
    }
}

void dessiner_explosions(explosion_t exps[]) {
    for (int i = 0; i < NB_EXPLOSIONS_MAX; i++) {
        if (!exps[i].actif || !exps[i].sprite) continue;

        /* Agrandissement et atténuation progressifs */
        float ratio  = 1.0f - (float)exps[i].timer / (float)EXPLOSION_DUREE;
        float scale  = 0.5f + ratio * 1.5f;
        int   alpha  = (int)(255 * exps[i].timer / (float)EXPLOSION_DUREE);

        int w = al_get_bitmap_width(exps[i].sprite);
        int h = al_get_bitmap_height(exps[i].sprite);

        al_draw_tinted_scaled_bitmap(
            exps[i].sprite,
            al_map_rgba(255, 255, 255, alpha),
            0, 0, w, h,
            exps[i].x - (w * scale) / 2.0f,
            exps[i].y - (h * scale) / 2.0f,
            w * scale, h * scale,
            0
        );
    }
}

void detruire_explosions(explosion_t exps[]) {
    /* sprite_cache_explosion est partagé, ne pas le détruire ici */
    for (int i = 0; i < NB_EXPLOSIONS_MAX; i++) {
        exps[i].actif  = false;
        exps[i].sprite = NULL;
    }
}

void liberer_cache_explosion(void) {
    if (sprite_cache_explosion) {
        al_destroy_bitmap(sprite_cache_explosion);
        sprite_cache_explosion = NULL;
    }
}
