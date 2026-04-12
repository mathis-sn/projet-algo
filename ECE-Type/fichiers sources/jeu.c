#include "jeu.h"
#include "joueur.h"
#include "ennemi.h"
#include "tir.h"
#include "collision.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <stdio.h>
#include <stdbool.h>

void lancer_jeu(ALLEGRO_DISPLAY *display) {
    printf("➡️ lancement de lancer_jeu()\n");

    if (!al_install_keyboard()) {
        printf("clavier non initialisé\n");
        return;
    }
    if (!al_init_image_addon()) {
        printf("image add-on non initialisé\n");
        return;
    }
    if (!al_init_primitives_addon()) {
        printf("primitives non initialisées\n");
        return;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    if (!queue || !timer) {
        printf("échec création timer ou queue\n");
        return;
    }

    ALLEGRO_BITMAP *background = al_load_bitmap("background.png");
    if (!background) {
        printf("background.png non trouvé, création fond noir\n");
        background = al_create_bitmap(800, 600);
        al_set_target_bitmap(background);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_set_target_backbuffer(al_get_current_display());
    }

    joueur_t joueur = creer_joueur();
    ennemi_t ennemi = creer_ennemi(900, 300);
    tir_t tirs[NB_TIRS_MAX];
    init_tirs(tirs);

    bool fini = false;
    bool redraw = true;
    float bg_x = 0;

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    printf("initialisation OK, entrée dans la boucle principale (Échap pour quitter)\n");

    while (!fini) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fini = true;
        } else if (ev.type == ALLEGRO_EVENT_TIMER) {
            maj_joueur(&joueur);
            maj_ennemi(&ennemi);
            maj_tirs(tirs);
            gerer_collisions(&joueur, &ennemi);

            bg_x -= 2;
            if (bg_x <= -800) bg_x = 0;
            redraw = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                fini = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                tirer(tirs, joueur.x, joueur.y);
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Défilement du fond
            al_draw_bitmap(background, bg_x, 0, 0);
            al_draw_bitmap(background, bg_x + 800, 0, 0);

            // Entités
            dessiner_joueur(&joueur);
            dessiner_ennemi(&ennemi);
            dessiner_tirs(tirs);

            al_flip_display();
        }
    }

    printf("sortie propre de la boucle de jeu\n");

    detruire_tirs(tirs);
    al_destroy_bitmap(background);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}
