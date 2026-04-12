#include "collision.h"
#include <math.h>

void gerer_collisions(joueur_t *j, ennemi_t *e) {
    float dx = (j->x + 20) - (e->x + 15);
    float dy = (j->y + 10) - (e->y + 15);
    float dist = sqrt(dx * dx + dy * dy);
    if (dist < 25) {
        j->x = 100;
        j->y = 300; // Reset position (collision)
    }
}
