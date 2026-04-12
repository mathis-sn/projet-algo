#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "jeu.h"

int main(void) {
    if (!al_init()) {
        printf("Erreur : échec al_init()\n");
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    if (!display) {
        printf("Erreur : affichage non créé\n");
        return -1;
    }

    printf("💡 Lancement du jeu...\n");
    lancer_jeu(display);   // 👈 c’est ici que tout le jeu tourne

    printf("✅ Fin du programme principale\n");
    al_destroy_display(display);
    return 0;
}
