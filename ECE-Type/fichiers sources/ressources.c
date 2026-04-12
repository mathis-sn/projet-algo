#include "ressources.h"
#include <stdio.h>

sons_t charger_ressources() {
    sons_t s = {0};

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);

    s.tir = al_load_sample("assets/tir.wav");
    s.explosion = al_load_sample("assets/explosion.wav");

    if (!s.tir || !s.explosion)
        printf("⚠️  Sons non trouvés (assets/tir.wav, assets/explosion.wav)\n");

    return s;
}

void liberer_ressources(sons_t *s) {
    if (s->tir) al_destroy_sample(s->tir);
    if (s->explosion) al_destroy_sample(s->explosion);
}
