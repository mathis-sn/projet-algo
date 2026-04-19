#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include "menu.h"

int main(void) {
    if (!al_init()) {
        fprintf(stderr, "Erreur : échec al_init()\n");
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erreur : image addon\n");
        return -1;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Erreur : primitives addon\n");
        return -1;
    }
    if (!al_install_keyboard()) {
        fprintf(stderr, "Erreur : clavier\n");
        return -1;
    }

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);

    /* Plein écran */
    ALLEGRO_DISPLAY_MODE mode;
    al_get_display_mode(0, &mode);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY *display = al_create_display(mode.width, mode.height);
    if (!display) {
        /* Fallback fenêtré */
        al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
        display = al_create_display(800, 600);
        if (!display) {
            fprintf(stderr, "Erreur : affichage non créé\n");
            return -1;
        }
    }

    al_set_window_title(display, "ECE-Type : Shoot'em Up");

    printf("Lancement du menu principal...\n");
    lancer_menu(display);

    al_destroy_display(display);
    return 0;
}
