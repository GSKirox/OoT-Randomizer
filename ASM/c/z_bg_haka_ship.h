#ifndef BG_HAKA_SHIP
#define BG_HAKA_SHIP
#include "z64.h"

struct BgHakaShip;

z64_actor_t* Actor_FindNearby(z64_game_t* play, z64_actor_t* refActor, int16_t actorId, uint8_t actorCategory, float range);

typedef struct BgHakaShip {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0154 */ void* actionFunc;
    /* 0x0158 */ uint8_t counter;
    /* 0x0159 */ uint8_t switchFlag;
    /* 0x015A */ int16_t yOffset;
    /* 0x015C */ z64_xyzf_t bellSfxPos;
} BgHakaShip; // size = 0x0168

#endif