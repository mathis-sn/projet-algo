#include "niveau.h"
#include "collision.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>

/* ------------------------------------------------------------------ */
/*  Structures de vagues par niveau                                     */
/* ------------------------------------------------------------------ */

typedef struct {
    float x, y;
    type_ennemi_e type;
    int pv;
    int cadence;
} def_ennemi_t;

/* Niveau 1 : 6 vagues */
static def_ennemi_t vagues_n1[][4] = {
    /* vague 0 */
    {{820, 150, ENNEMI_VOLANT, 1, 180}, {820, 300, ENNEMI_VOLANT, 1, 180},
     {820, 450, ENNEMI_VOLANT, 1, 180}, {0}},
    /* vague 1 */
    {{820, 200, ENNEMI_SINUSOIDE, 1, 240}, {820, 400, ENNEMI_SINUSOIDE, 1, 240},
     {0},{0}},
    /* vague 2 */
    {{820, 100, ENNEMI_VOLANT, 2, 150}, {820, 250, ENNEMI_VOLANT, 2, 150},
     {820, 400, ENNEMI_VOLANT, 2, 150}, {0}},
    /* vague 3 */
    {{750, 150, ENNEMI_FIXE, 2, 120}, {750, 350, ENNEMI_FIXE, 2, 120},
     {0},{0}},
    /* vague 4 */
    {{820, 80,  ENNEMI_SINUSOIDE, 1, 200}, {820, 200, ENNEMI_SINUSOIDE, 1, 200},
     {820, 320, ENNEMI_SINUSOIDE, 1, 200}, {820, 440, ENNEMI_SINUSOIDE, 1, 200}},
    /* vague 5 */
    {{820, 300, ENNEMI_VOLANT, 3, 100}, {0},{0},{0}},
};
#define NB_VAGUES_N1 6
#define DUREE_VAGUE_N1 600  /* frames entre vagues */

/* Niveau 2 : ennemis plus coriaces */
static def_ennemi_t vagues_n2[][4] = {
    {{820, 100, ENNEMI_SINUSOIDE, 2, 100}, {820, 300, ENNEMI_VOLANT, 2, 100},
     {820, 500, ENNEMI_SINUSOIDE, 2, 100}, {0}},
    {{820, 200, ENNEMI_VOLANT, 3, 80},  {820, 400, ENNEMI_VOLANT, 3, 80},
     {700, 200, ENNEMI_FIXE, 3, 80}, {700, 400, ENNEMI_FIXE, 3, 80}},
    {{820, 150, ENNEMI_SINUSOIDE, 2, 90}, {820, 350, ENNEMI_SINUSOIDE, 2, 90},
     {0},{0}},
    {{820, 80,  ENNEMI_VOLANT, 4, 60},  {820, 240, ENNEMI_VOLANT, 4, 60},
     {820, 400, ENNEMI_VOLANT, 4, 60},  {820, 520, ENNEMI_VOLANT, 4, 60}},
    {{750, 250, ENNEMI_FIXE, 4, 70},    {0},{0},{0}},
    {{820, 200, ENNEMI_SINUSOIDE, 3, 80}, {820, 400, ENNEMI_SINUSOIDE, 3, 80},
     {0},{0}},
};
#define NB_VAGUES_N2 6
#define DUREE_VAGUE_N2 480

/* Niveau 3 : difficile */
static def_ennemi_t vagues_n3[][4] = {
    {{820, 100, ENNEMI_SINUSOIDE, 3, 60}, {820, 200, ENNEMI_VOLANT, 3, 60},
     {820, 350, ENNEMI_VOLANT, 3, 60},  {820, 500, ENNEMI_SINUSOIDE, 3, 60}},
    {{820, 150, ENNEMI_VOLANT, 4, 50},  {820, 300, ENNEMI_VOLANT, 4, 50},
     {820, 450, ENNEMI_VOLANT, 4, 50},  {0}},
    {{750, 100, ENNEMI_FIXE, 5, 45},    {750, 300, ENNEMI_FIXE, 5, 45},
     {750, 500, ENNEMI_FIXE, 5, 45},    {0}},
    {{820, 200, ENNEMI_SINUSOIDE, 4, 40}, {820, 400, ENNEMI_SINUSOIDE, 4, 40},
     {0},{0}},
    {{820, 100, ENNEMI_VOLANT, 5, 35},  {820, 200, ENNEMI_VOLANT, 5, 35},
     {820, 350, ENNEMI_VOLANT, 5, 35},  {820, 500, ENNEMI_VOLANT, 5, 35}},
    {{820, 300, ENNEMI_SINUSOIDE, 6, 30}, {0},{0},{0}},
};
#define NB_VAGUES_N3 6
#define DUREE_VAGUE_N3 360

/* ------------------------------------------------------------------ */

static void spawner_vague(niveau_t *niv, def_ennemi_t defs[], int nb_def_par_vague) {
    int spawne = 0;
    for (int i = 0; i < nb_def_par_vague && spawne < 4; i++) {
        def_ennemi_t *d = &defs[i];
        if (d->x == 0 && d->y == 0) break;
        /* Trouver un slot libre */
        for (int s = 0; s < NB_ENNEMIS_MAX; s++) {
            if (!niv->ennemis[s].actif) {
                niv->ennemis[s] = creer_ennemi(d->x, d->y, d->type, d->pv, d->cadence);
                spawne++;
                break;
            }
        }
    }
}

static void dessiner_hud(joueur_t *j, ALLEGRO_FONT *font) {
    /* Vies */
    char buf[64];
    snprintf(buf, sizeof(buf), "VIES: %d", j->vies);
    al_draw_text(font, al_map_rgb(255,255,255), 10, JEU_HAUTEUR - 30, 0, buf);

    /* Score */
    snprintf(buf, sizeof(buf), "SCORE: %06d", j->score);
    al_draw_text(font, al_map_rgb(255,220,0), JEU_LARGEUR/2, JEU_HAUTEUR - 30,
                 ALLEGRO_ALIGN_CENTRE, buf);
}

static bool tous_ennemis_morts(niveau_t *niv) {
    for (int i = 0; i < NB_ENNEMIS_MAX; i++) {
        if (niv->ennemis[i].actif) return false;
    }
    return true;
}

/* ------------------------------------------------------------------ */
/*  Point d'entrée principal                                            */
/* ------------------------------------------------------------------ */

resultat_niveau_e lancer_niveau(ALLEGRO_DISPLAY *display, int numero, joueur_t *joueur) {
    printf("Lancement niveau %d\n", numero);

    /* ---- Init addons (idempotent) ---- */
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();

    /* ---- Timer & Queue ---- */
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER       *timer = al_create_timer(1.0 / 60.0);
    if (!queue || !timer) { printf("Erreur timer/queue\n"); return NIVEAU_MENU; }

    /* ---- Police ---- */
    ALLEGRO_FONT *font = al_load_ttf_font("font.ttf", 20, 0);
    if (!font) font = al_create_builtin_font();

    /* ---- Fond ---- */
    const char *bg_file[] = {"background.png", "background2.png", "background3.png"};
    ALLEGRO_BITMAP *background = al_load_bitmap(bg_file[numero - 1]);
    if (!background) {
        background = al_create_bitmap(JEU_LARGEUR, JEU_HAUTEUR);
        al_set_target_bitmap(background);
        ALLEGRO_COLOR col = (numero == 1) ? al_map_rgb(5,5,30)
                          : (numero == 2) ? al_map_rgb(10,0,20)
                                          : al_map_rgb(0,10,5);
        al_clear_to_color(col);
        al_set_target_backbuffer(display);
    }

    /* ---- Niveau ---- */
    niveau_t niv = {0};
    niv.numero   = numero;
    niv.vit_scroll = (numero == 1) ? VIT_SCROLL_N1
                   : (numero == 2) ? VIT_SCROLL_N2 : VIT_SCROLL_N3;
    niv.background  = background;
    niv.bg_x        = 0;
    niv.phase_boss  = false;
    niv.timer_spawn = 60; /* petit délai avant 1ère vague */
    niv.vague       = 0;
    niv.nb_ennemis  = NB_ENNEMIS_MAX;

    for (int i = 0; i < NB_ENNEMIS_MAX; i++) niv.ennemis[i].actif = false;

    /* Boss créé hors écran, activé plus tard */
    niv.boss = creer_boss(JEU_LARGEUR + 100, JEU_HAUTEUR / 2 - 40);

    /* ---- Tirs ---- */
    tir_t tirs_j[NB_TIRS_MAX];
    tir_t tirs_e[NB_TIRS_ENNEMIS];
    init_tirs(tirs_j);
    init_tirs_ennemis(tirs_e);

    /* ---- Explosions ---- */
    explosion_t exps[NB_EXPLOSIONS_MAX];
    init_explosions(exps);

    /* ---- Paramètres de vague selon niveau ---- */
    int nb_vagues       = (numero == 1) ? NB_VAGUES_N1 : (numero == 2) ? NB_VAGUES_N2 : NB_VAGUES_N3;
    int duree_vague     = (numero == 1) ? DUREE_VAGUE_N1 : (numero == 2) ? DUREE_VAGUE_N2 : DUREE_VAGUE_N3;
    void *vagues        = (numero == 1) ? (void*)vagues_n1 : (numero == 2) ? (void*)vagues_n2 : (void*)vagues_n3;
    (void)vagues; /* utilisé via macro ci-dessous */

#define SPAWNER_VAGUE_NIVEAU(NB) \
    if (numero == 1 && niv.vague < NB_VAGUES_N1) spawner_vague(&niv, vagues_n1[niv.vague], 4); \
    else if (numero == 2 && niv.vague < NB_VAGUES_N2) spawner_vague(&niv, vagues_n2[niv.vague], 4); \
    else if (numero == 3 && niv.vague < NB_VAGUES_N3) spawner_vague(&niv, vagues_n3[niv.vague], 4);

    /* ---- Events ---- */
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    bool fini   = false;
    bool redraw = true;
    bool pause  = false;
    bool delai_tir_ready = false;
    int  cooldown_tir = 0;
    resultat_niveau_e resultat = NIVEAU_VICTOIRE;

    /* Texte niveau */
    char titre_niv[32];
    snprintf(titre_niv, sizeof(titre_niv), "NIVEAU %d", numero);
    int  afficher_titre = 120; /* frames d'affichage du titre */

    while (!fini) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            resultat = NIVEAU_MENU;
            fini = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                resultat = NIVEAU_MENU;
                fini = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_P) {
                pause = !pause;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE && !pause) {
                if (cooldown_tir <= 0) {
                    tirer(tirs_j, joueur->x, joueur->y);
                    cooldown_tir = 8;
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER && !pause) {

            if (afficher_titre > 0) afficher_titre--;

            /* ---- Tir automatique maintenu ---- */
            ALLEGRO_KEYBOARD_STATE ks;
            al_get_keyboard_state(&ks);
            if (al_key_down(&ks, ALLEGRO_KEY_SPACE)) {
                if (cooldown_tir <= 0) {
                    tirer(tirs_j, joueur->x, joueur->y);
                    cooldown_tir = 8;
                }
            }
            if (cooldown_tir > 0) cooldown_tir--;

            /* ---- Scroll & spawn vagues ---- */
            if (!niv.phase_boss) {
                niv.bg_x -= niv.vit_scroll;
                if (niv.bg_x <= -JEU_LARGEUR) niv.bg_x = 0;

                niv.timer_spawn--;
                if (niv.timer_spawn <= 0) {
                    if (niv.vague < nb_vagues) {
                        SPAWNER_VAGUE_NIVEAU(4)
                        niv.vague++;
                    }
                    /* Déclenchement boss après toutes les vagues */
                    if (niv.vague >= nb_vagues && tous_ennemis_morts(&niv)) {
                        niv.phase_boss = true;
                        printf("Phase boss!\n");
                    }
                    niv.timer_spawn = duree_vague;
                }
            }

            /* ---- Tirs ennemis ---- */
            for (int i = 0; i < NB_ENNEMIS_MAX; i++) {
                if (!niv.ennemis[i].actif) continue;
                niv.ennemis[i].timer_tir--;
                if (niv.ennemis[i].timer_tir <= 0) {
                    /* Tir vers la gauche, avec légère visée */
                    float dx = joueur->x - niv.ennemis[i].x;
                    float dy = joueur->y - niv.ennemis[i].y;
                    float d  = sqrtf(dx*dx + dy*dy);
                    if (d > 0) { dx /= d; dy /= d; }
                    float spd = 5.0f;
                    tirer_ennemi(tirs_e, niv.ennemis[i].x, niv.ennemis[i].y + 12,
                                 dx * spd, dy * spd);
                    niv.ennemis[i].timer_tir = niv.ennemis[i].cadence_tir;
                }
            }

            /* Tirs boss */
            if (niv.phase_boss && niv.boss.actif && niv.boss.apparu) {
                niv.boss.timer_tir--;
                if (niv.boss.timer_tir <= 0) {
                    /* Salve selon phase */
                    int nb_tirs = (niv.boss.phase == 0) ? 1 : (niv.boss.phase == 1) ? 3 : 5;
                    for (int k = 0; k < nb_tirs; k++) {
                        float angle = (float)k * (6.283f / nb_tirs);
                        tirer_ennemi(tirs_e, niv.boss.x + 40, niv.boss.y + 40,
                                     cosf(angle) * -5.0f, sinf(angle) * 3.0f);
                    }
                    niv.boss.timer_tir = niv.boss.cadence_tir;
                }
            }

            /* ---- Mises à jour ---- */
            maj_joueur(joueur);
            maj_ennemis(niv.ennemis, NB_ENNEMIS_MAX);
            if (niv.phase_boss) maj_boss(&niv.boss);
            maj_tirs(tirs_j);
            maj_tirs_ennemis(tirs_e);
            maj_explosions(exps);

            /* ---- Collisions ---- */
            gerer_collisions_tirs_ennemis(tirs_j, niv.ennemis, NB_ENNEMIS_MAX, exps, joueur);
            if (niv.phase_boss)
                gerer_collisions_tirs_boss(tirs_j, &niv.boss, exps, joueur);
            gerer_collisions_tirs_ennemis_joueur(tirs_e, joueur, exps);
            gerer_collisions_joueur_ennemis(joueur, niv.ennemis, NB_ENNEMIS_MAX, exps);
            if (niv.phase_boss)
                gerer_collision_joueur_boss(joueur, &niv.boss, exps);

            /* ---- Mort du joueur ---- */
            if (!joueur->vivant) {
                if (joueur->vies > 0) {
                    respawn_joueur(joueur);
                } else {
                    resultat = NIVEAU_GAME_OVER;
                    fini = true;
                }
            }

            /* ---- Victoire ---- */
            if (niv.phase_boss && !niv.boss.actif) {
                /* Petite pause avant de passer */
                al_rest(1.5);
                resultat = NIVEAU_VICTOIRE;
                fini = true;
            }

            redraw = true;
        }

        /* ---- Rendu ---- */
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));

            /* Fond défilant */
            al_draw_bitmap(niv.background, niv.bg_x, 0, 0);
            al_draw_bitmap(niv.background, niv.bg_x + JEU_LARGEUR, 0, 0);

            /* Entités */
            dessiner_ennemis(niv.ennemis, NB_ENNEMIS_MAX);
            if (niv.phase_boss) dessiner_boss(&niv.boss);
            dessiner_tirs(tirs_j);
            dessiner_tirs_ennemis(tirs_e);
            dessiner_joueur(joueur);
            dessiner_explosions(exps);

            /* HUD */
            dessiner_hud(joueur, font);

            /* Titre de niveau */
            if (afficher_titre > 0) {
                float alpha = (afficher_titre > 30) ? 1.0f : afficher_titre / 30.0f;
                al_draw_text(font,
                             al_map_rgba_f(1,1,0, alpha),
                             JEU_LARGEUR/2, JEU_HAUTEUR/2 - 20,
                             ALLEGRO_ALIGN_CENTRE, titre_niv);
            }

            /* Pause */
            if (pause) {
                al_draw_filled_rectangle(0, 0, JEU_LARGEUR, JEU_HAUTEUR,
                                         al_map_rgba(0,0,0,140));
                al_draw_text(font, al_map_rgb(255,255,255),
                             JEU_LARGEUR/2, JEU_HAUTEUR/2 - 15,
                             ALLEGRO_ALIGN_CENTRE, "PAUSE - Appuyez sur P pour reprendre");
            }

            al_flip_display();
        }
    }

    /* ---- Nettoyage ---- */
    detruire_tirs(tirs_j);
    detruire_tirs_ennemis(tirs_e);
    detruire_explosions(exps);
    detruire_boss(&niv.boss);
    al_destroy_bitmap(background);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    if (font) al_destroy_font(font);

    return resultat;
}
