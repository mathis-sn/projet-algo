#ifndef RESSOURCES_H
#define RESSOURCES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct {
    ALLEGRO_SAMPLE *tir;
    ALLEGRO_SAMPLE *explosion;
    ALLEGRO_SAMPLE *hit;
    ALLEGRO_SAMPLE *boss_mort;
    ALLEGRO_SAMPLE *menu;
} sons_t;

sons_t charger_ressources(void);
void   liberer_ressources(sons_t *s);

#endif /* RESSOURCES_H */
