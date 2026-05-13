#include "z_bg_haka_ship.h"

void fast_boat(z64_actor_t* thisx) {
    BgHakaShip* this = (BgHakaShip*)thisx;
    if (Actor_FindNearby(&z64_game, &this->dyna.actor, 0x0002, ACTORTYPE_ENEMY, 800.0) == NULL &&
        Actor_FindNearby(&z64_game, &this->dyna.actor, 0x0000, ACTORTYPE_PLAYER, 450.0) != NULL) {
        this->dyna.actor.xz_speed = 25.0f;
    } else if (this->dyna.actor.xz_speed > 4.0f) {
        this->dyna.actor.xz_speed = 4.0f;
    }
}