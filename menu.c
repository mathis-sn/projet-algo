#include "menu.h"
#include "niveau.h"
#include "joueur.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* ------------------------------------------------------------------ */
/*  Utilitaires dessin                                                  */
/* ------------------------------------------------------------------ */

static void dessiner_fond_menu(ALLEGRO_BITMAP *bg, float *bg_x) {
    *bg_x -= 1.0f;
    if (*bg_x <= -JEU_LARGEUR) *bg_x = 0;
    al_draw_bitmap(bg, *bg_x, 0, 0);
    al_draw_bitmap(bg, *bg_x + JEU_LARGEUR, 0, 0);
    /* Overlay sombre */
    al_draw_filled_rectangle(0, 0, JEU_LARGEUR, JEU_HAUTEUR, al_map_rgba(0,0,0,160));
}

static void dessiner_bouton(ALLEGRO_FONT *font, const char *texte,
                             float cx, float cy, bool selectionne, float anim) {
    float w = 320, h = 48;
    float x = cx - w/2, y = cy - h/2;

    if (selectionne) {
        float pulse = 0.7f + 0.3f * sinf(anim * 0.1f);
        al_draw_filled_rounded_rectangle(x, y, x+w, y+h, 8, 8,
                                          al_map_rgba_f(0.0f, 0.4f * pulse, 0.8f * pulse, 0.85f));
        al_draw_rounded_rectangle(x, y, x+w, y+h, 8, 8,
                                   al_map_rgba_f(0.4f, 0.8f, 1.0f, pulse), 2.5f);
        al_draw_text(font, al_map_rgb(255, 255, 255), cx, cy - 13,
                     ALLEGRO_ALIGN_CENTRE, texte);
    } else {
        al_draw_filled_rounded_rectangle(x, y, x+w, y+h, 8, 8,
                                          al_map_rgba(20, 20, 40, 180));
        al_draw_rounded_rectangle(x, y, x+w, y+h, 8, 8,
                                   al_map_rgb(80, 80, 120), 1.5f);
        al_draw_text(font, al_map_rgb(180, 180, 210), cx, cy - 13,
                     ALLEGRO_ALIGN_CENTRE, texte);
    }
}

/* ------------------------------------------------------------------ */
/*  Écran Game Over                                                     */
/* ------------------------------------------------------------------ */

static void ecran_game_over(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font,
                             ALLEGRO_FONT *font_big, int score) {
    ALLEGRO_EVENT_QUEUE *q = al_create_event_queue();
    ALLEGRO_TIMER *t = al_create_timer(1.0 / 60.0);
    al_register_event_source(q, al_get_display_event_source(display));
    al_register_event_source(q, al_get_timer_event_source(t));
    al_register_event_source(q, al_get_keyboard_event_source());
    al_start_timer(t);

    bool fin = false;
    int  frame = 0;

    while (!fin) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(q, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            frame++;
            if (frame > 60*5) fin = true; /* auto après 5s */
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_filled_rectangle(0,0,JEU_LARGEUR,JEU_HAUTEUR, al_map_rgba(10,0,0,220));
            al_draw_text(font_big, al_map_rgb(220,30,30),
                         JEU_LARGEUR/2, 180, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
            char buf[64];
            snprintf(buf, sizeof(buf), "Score final : %06d", score);
            al_draw_text(font, al_map_rgb(200,200,200),
                         JEU_LARGEUR/2, 280, ALLEGRO_ALIGN_CENTRE, buf);
            al_draw_text(font, al_map_rgb(160,160,160),
                         JEU_LARGEUR/2, 340, ALLEGRO_ALIGN_CENTRE,
                         "Appuyez sur ENTREE pour revenir au menu");
            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
                ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) fin = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) fin = true;
    }
    al_destroy_event_queue(q);
    al_destroy_timer(t);
}

/* ------------------------------------------------------------------ */
/*  Écran Victoire                                                      */
/* ------------------------------------------------------------------ */

static void ecran_victoire(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font,
                            ALLEGRO_FONT *font_big, int score) {
    ALLEGRO_EVENT_QUEUE *q = al_create_event_queue();
    ALLEGRO_TIMER *t = al_create_timer(1.0 / 60.0);
    al_register_event_source(q, al_get_display_event_source(display));
    al_register_event_source(q, al_get_timer_event_source(t));
    al_register_event_source(q, al_get_keyboard_event_source());
    al_start_timer(t);

    bool fin = false;
    int  frame = 0;

    while (!fin) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(q, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            frame++;
            if (frame > 60*8) fin = true;
            float pulse = 0.6f + 0.4f * sinf(frame * 0.05f);
            al_clear_to_color(al_map_rgb(0,0,15));
            al_draw_filled_rectangle(0,0,JEU_LARGEUR,JEU_HAUTEUR,
                                     al_map_rgba(0,0,30,180));
            al_draw_text(font_big,
                         al_map_rgba_f(pulse, 1.0f, pulse * 0.5f, 1.0f),
                         JEU_LARGEUR/2, 160, ALLEGRO_ALIGN_CENTRE,
                         "VICTOIRE !");
            al_draw_text(font, al_map_rgb(200,220,255),
                         JEU_LARGEUR/2, 260, ALLEGRO_ALIGN_CENTRE,
                         "L'Empire Bydo est vaincu !");
            char buf[64];
            snprintf(buf, sizeof(buf), "Score final : %06d", score);
            al_draw_text(font, al_map_rgb(255,220,50),
                         JEU_LARGEUR/2, 310, ALLEGRO_ALIGN_CENTRE, buf);
            al_draw_text(font, al_map_rgb(140,140,180),
                         JEU_LARGEUR/2, 380, ALLEGRO_ALIGN_CENTRE,
                         "Appuyez sur ENTREE pour revenir au menu");
            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
                ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) fin = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) fin = true;
    }
    al_destroy_event_queue(q);
    al_destroy_timer(t);
}

/* ------------------------------------------------------------------ */
/*  Menu principal                                                      */
/* ------------------------------------------------------------------ */

void lancer_menu(ALLEGRO_DISPLAY *display) {

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER       *timer = al_create_timer(1.0 / 60.0);
    if (!queue || !timer) { printf("Erreur menu\n"); return; }

    /* Polices */
    ALLEGRO_FONT *font_big = al_load_ttf_font("font.ttf", 52, 0);
    ALLEGRO_FONT *font     = al_load_ttf_font("font.ttf", 22, 0);
    ALLEGRO_FONT *font_sm  = al_load_ttf_font("font.ttf", 16, 0);
    if (!font_big) font_big = al_create_builtin_font();
    if (!font)     font     = al_create_builtin_font();
    if (!font_sm)  font_sm  = al_create_builtin_font();

    /* Fond menu = fond niveau 1 */
    ALLEGRO_BITMAP *bg = al_load_bitmap("background.png");
    if (!bg) {
        bg = al_create_bitmap(JEU_LARGEUR, JEU_HAUTEUR);
        al_set_target_bitmap(bg);
        al_clear_to_color(al_map_rgb(5,5,30));
        al_set_target_backbuffer(display);
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    /* Options du menu :
       0 = Nouvelle Partie
       1 = Niveau 1
       2 = Niveau 2
       3 = Niveau 3 (boss direct)
       4 = Quitter
    */
    const char *labels[] = {
        "Nouvelle partie",
        "Acces direct - Niveau 1",
        "Acces direct - Niveau 2",
        "Acces direct - Niveau 3 (Boss)",
        "Quitter"
    };
    const int NB_OPTIONS = 5;
    int selection = 0;
    float anim    = 0;
    float bg_x    = 0;
    bool  quitter = false;

    while (!quitter) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { quitter = true; break; }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    selection = (selection - 1 + NB_OPTIONS) % NB_OPTIONS; break;
                case ALLEGRO_KEY_DOWN:
                    selection = (selection + 1) % NB_OPTIONS; break;
                case ALLEGRO_KEY_ENTER:
                case ALLEGRO_KEY_SPACE: {
                    /* Lancer l'action */
                    if (selection == 4) { quitter = true; break; }

                    int niveau_depart = (selection == 0) ? 1 : selection;
                    /* Crée un joueur frais */
                    joueur_t joueur = creer_joueur();

                    resultat_niveau_e res = NIVEAU_VICTOIRE;
                    for (int n = niveau_depart; n <= NB_NIVEAUX && res == NIVEAU_VICTOIRE; n++) {
                        res = lancer_niveau(display, n, &joueur);
                        /* Réinit display target après niveau */
                        al_set_target_backbuffer(display);
                    }

                    al_set_target_backbuffer(display);

                    if (res == NIVEAU_GAME_OVER)
                        ecran_game_over(display, font, font_big, joueur.score);
                    else if (res == NIVEAU_VICTOIRE)
                        ecran_victoire(display, font, font_big, joueur.score);

                    detruire_joueur(&joueur);
                    al_set_target_backbuffer(display);
                    break;
                }
                case ALLEGRO_KEY_ESCAPE:
                    quitter = true; break;
                default: break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER) {
            anim += 1.0f;

            al_clear_to_color(al_map_rgb(0,0,0));
            dessiner_fond_menu(bg, &bg_x);

            /* Titre */
            float titre_y = 80.0f + sinf(anim * 0.03f) * 6.0f;
            al_draw_text(font_big, al_map_rgb(50, 180, 255),
                         JEU_LARGEUR/2 + 2, titre_y + 2, ALLEGRO_ALIGN_CENTRE, "ECE-TYPE");
            al_draw_text(font_big, al_map_rgb(255, 255, 255),
                         JEU_LARGEUR/2, titre_y, ALLEGRO_ALIGN_CENTRE, "ECE-TYPE");

            al_draw_text(font_sm, al_map_rgb(150, 150, 200),
                         JEU_LARGEUR/2, titre_y + 58, ALLEGRO_ALIGN_CENTRE,
                         "Shoot'em Up  -  ING1 Projet Allegro 5");

            /* Boutons */
            float start_y = 210.0f;
            float step_y  = 70.0f;
            for (int i = 0; i < NB_OPTIONS; i++) {
                dessiner_bouton(font, labels[i],
                                JEU_LARGEUR/2, start_y + i * step_y,
                                (i == selection), anim);
            }

            /* Aide touches */
            al_draw_text(font_sm, al_map_rgb(100, 100, 140),
                         JEU_LARGEUR/2, JEU_HAUTEUR - 30, ALLEGRO_ALIGN_CENTRE,
                         "Fleches : naviguer    ENTREE : valider    ECHAP : quitter");

            al_flip_display();
        }
    }

    al_destroy_bitmap(bg);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    if (font_big) al_destroy_font(font_big);
    if (font)     al_destroy_font(font);
    if (font_sm)  al_destroy_font(font_sm);
}
