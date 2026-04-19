#include "ressources.h"
#include <stdio.h>

sons_t charger_ressources(void) {
    sons_t s = {0};

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);

    s.tir       = al_load_sample("snd_tir.wav");
    s.explosion = al_load_sample("snd_explosion.wav");
    s.hit       = al_load_sample("snd_hit.wav");
    s.boss_mort = al_load_sample("snd_boss.wav");
    s.menu      = al_load_sample("snd_menu.wav");

    if (!s.tir)       printf("Avertissement : snd_tir.wav manquant\n");
    if (!s.explosion) printf("Avertissement : snd_explosion.wav manquant\n");
    if (!s.hit)       printf("Avertissement : snd_hit.wav manquant\n");
    if (!s.boss_mort) printf("Avertissement : snd_boss.wav manquant\n");
    if (!s.menu)      printf("Avertissement : snd_menu.wav manquant\n");

    return s;
}

void liberer_ressources(sons_t *s) {
    if (s->tir)       { al_destroy_sample(s->tir);       s->tir       = NULL; }
    if (s->explosion) { al_destroy_sample(s->explosion); s->explosion = NULL; }
    if (s->hit)       { al_destroy_sample(s->hit);       s->hit       = NULL; }
    if (s->boss_mort) { al_destroy_sample(s->boss_mort); s->boss_mort = NULL; }
    if (s->menu)      { al_destroy_sample(s->menu);      s->menu      = NULL; }
}
