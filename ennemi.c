#include "ennemi.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>

/* ---- ENNEMIS ---- */

static ALLEGRO_BITMAP *sprite_cache_ennemi   = NULL;
static ALLEGRO_BITMAP *sprite_cache_tourelle = NULL;
static ALLEGRO_BITMAP *sprite_cache_sinus    = NULL;

static ALLEGRO_BITMAP *charger_sprite_ennemi(type_ennemi_e type) {
    const char *fichier;
    ALLEGRO_BITMAP **cache;

    switch (type) {
        case ENNEMI_FIXE:
            fichier = "enemy_turret.png";
            cache   = &sprite_cache_tourelle;
            break;
        case ENNEMI_SINUSOIDE:
            fichier = "enemy_sinus.png";
            cache   = &sprite_cache_sinus;
            break;
        default: /* ENNEMI_VOLANT */
            fichier = "enemy.png";
            cache   = &sprite_cache_ennemi;
            break;
    }

    if (!*cache) {
        *cache = al_load_bitmap(fichier);
        if (!*cache) {
            fprintf(stderr, "Erreur : impossible de charger %s\n", fichier);
            *cache = al_create_bitmap(32, 32);
            al_set_target_bitmap(*cache);
            ALLEGRO_COLOR c = (type == ENNEMI_FIXE)      ? al_map_rgb(200,50,50)
                            : (type == ENNEMI_SINUSOIDE)  ? al_map_rgb(50,200,50)
                                                          : al_map_rgb(255,60,60);
            al_clear_to_color(c);
            al_set_target_backbuffer(al_get_current_display());
        }
    }
    return *cache;
}

void init_ennemis(ennemi_t ennemis[]) {
    for (int i = 0; i < NB_ENNEMIS_MAX; i++) {
        ennemis[i].actif = false;
        ennemis[i].sprite = NULL;
    }
}

ennemi_t creer_ennemi(float x, float y, type_ennemi_e type, int pv, int cadence) {
    ennemi_t e = {0};
    e.x      = x;
    e.y      = y;
    e.base_y = y;
    e.angle  = 0.0f;
    e.pv     = pv;
    e.actif  = true;
    e.type   = type;
    e.cadence_tir = cadence;
    e.timer_tir   = cadence / 2; /* décalage initial */

    switch (type) {
        case ENNEMI_VOLANT:
            e.vx = -3.0f;
            e.vy = 0.0f;
            break;
        case ENNEMI_FIXE:
            e.vx = 0.0f;
            e.vy = 0.0f;
            break;
        case ENNEMI_SINUSOIDE:
            e.vx = -2.5f;
            e.vy = 0.0f;
            break;
    }

    e.sprite = charger_sprite_ennemi(type);
    return e;
}

void maj_ennemis(ennemi_t ennemis[], int nb) {
    for (int i = 0; i < nb; i++) {
        if (!ennemis[i].actif) continue;

        switch (ennemis[i].type) {
            case ENNEMI_VOLANT:
                ennemis[i].x += ennemis[i].vx;
                if (ennemis[i].x < -40) ennemis[i].actif = false;
                break;
            case ENNEMI_FIXE:
                /* reste en place */
                break;
            case ENNEMI_SINUSOIDE:
                ennemis[i].angle += 0.05f;
                ennemis[i].x += ennemis[i].vx;
                ennemis[i].y  = ennemis[i].base_y + sinf(ennemis[i].angle) * 60.0f;
                if (ennemis[i].x < -40) ennemis[i].actif = false;
                break;
        }
    }
}

void dessiner_ennemis(ennemi_t ennemis[], int nb) {
    for (int i = 0; i < nb; i++) {
        if (ennemis[i].actif && ennemis[i].sprite)
            al_draw_bitmap(ennemis[i].sprite, ennemis[i].x, ennemis[i].y, 0);
    }
}

void detruire_ennemis(ennemi_t ennemis[], int nb) {
    /* Les sprites sont partagés (cache), ne pas les détruire ici */
    for (int i = 0; i < nb; i++) {
        ennemis[i].actif  = false;
        ennemis[i].sprite = NULL;
    }
}

void liberer_cache_ennemis(void) {
    if (sprite_cache_ennemi)   { al_destroy_bitmap(sprite_cache_ennemi);   sprite_cache_ennemi   = NULL; }
    if (sprite_cache_tourelle) { al_destroy_bitmap(sprite_cache_tourelle); sprite_cache_tourelle = NULL; }
    if (sprite_cache_sinus)    { al_destroy_bitmap(sprite_cache_sinus);    sprite_cache_sinus    = NULL; }
}

/* ---- BOSS ---- */

boss_t creer_boss(float x, float y) {
    boss_t b = {0};
    b.x      = x;
    b.y      = y;
    b.base_y = y;
    b.pv_max = PV_BOSS_MAX;
    b.pv     = PV_BOSS_MAX;
    b.actif  = true;
    b.apparu = false;
    b.phase  = 0;
    b.cadence_tir = 90;
    b.timer_tir   = 60;
    b.vx = -1.5f;
    b.vy = 0.0f;
    b.angle = 0.0f;

    b.sprite = al_load_bitmap("boss.png");
    if (!b.sprite) {
        fprintf(stderr, "Erreur : impossible de charger boss.png\n");
        b.sprite = al_create_bitmap(80, 80);
        al_set_target_bitmap(b.sprite);
        al_clear_to_color(al_map_rgb(180, 0, 200));
        al_set_target_backbuffer(al_get_current_display());
    }

    b.sprite_endommage = al_load_bitmap("boss_damaged.png");
    if (!b.sprite_endommage) {
        b.sprite_endommage = b.sprite; /* fallback même sprite */
    }

    return b;
}

void maj_boss(boss_t *b) {
    if (!b->actif) return;

    /* Entrée en scène */
    if (!b->apparu) {
        b->x += b->vx;
        if (b->x <= JEU_LARGEUR - 160) {
            b->apparu = true;
            b->vx = 0;
        }
        return;
    }

    /* Oscillation verticale */
    b->angle += 0.03f;
    b->y = b->base_y + sinf(b->angle) * 80.0f;

    /* Changement de phase selon PV */
    if (b->pv <= b->pv_max / 2) {
        b->phase = 1;
        b->cadence_tir = 50; /* tir plus rapide */
    }
    if (b->pv <= b->pv_max / 4) {
        b->phase = 2;
        b->cadence_tir = 30; /* tir frénétique */
    }
}

void dessiner_boss(boss_t *b) {
    if (!b->actif) return;
    ALLEGRO_BITMAP *spr = (b->pv < b->pv_max / 2) ? b->sprite_endommage : b->sprite;
    if (spr) al_draw_bitmap(spr, b->x, b->y, 0);

    /* Barre de vie */
    float ratio = (float)b->pv / (float)b->pv_max;
    al_draw_filled_rectangle(10, 10, 10 + 200, 22, al_map_rgb(80, 0, 0));
    al_draw_filled_rectangle(10, 10, 10 + (int)(200 * ratio), 22,
                             al_map_rgb(220, 40, 40));
    al_draw_rectangle(10, 10, 210, 22, al_map_rgb(255, 255, 255), 1.5f);
}

void detruire_boss(boss_t *b) {
    if (b->sprite) {
        al_destroy_bitmap(b->sprite);
        b->sprite = NULL;
    }
    if (b->sprite_endommage && b->sprite_endommage != b->sprite) {
        al_destroy_bitmap(b->sprite_endommage);
        b->sprite_endommage = NULL;
    }
}
