#ifndef ITEM_EFFECTS_H
#define ITEM_EFFECTS_H

#include "z64.h"
#include "icetrap.h"
#include "triforce.h"
#include "traps.h"
#include "refill.h"
#include "rng.h"

void no_effect(z64_file_t *save, int16_t arg1, int16_t arg2);
void full_heal(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_triforce_piece(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_tycoon_wallet(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_biggoron_sword(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_bottle(z64_file_t *save, int16_t bottle_item_id, int16_t arg2);
void give_dungeon_item(z64_file_t *save, int16_t mask, int16_t dungeon_id);
void give_small_key(z64_file_t *save, int16_t dungeon_id, int16_t arg2);
void give_small_key_ring(z64_file_t *save, int16_t dungeon_id, int16_t arg2);
void give_defense(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_magic(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_double_magic(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_fairy_ocarina(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_song(z64_file_t *save, int16_t quest_bit, int16_t arg2);
void ice_trap_effect(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_bean_pack(z64_file_t *save, int16_t arg1, int16_t arg2);
void fill_wallet_upgrade(z64_file_t *save, int16_t arg1, int16_t arg2);
void clear_excess_hearts(z64_file_t *save, int16_t arg1, int16_t arg2);
void open_mask_shop(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_bombchus(z64_file_t *save, int16_t arg1, int16_t arg2);
void trade_quest_upgrade(z64_file_t *save, int16_t item_id, int16_t arg2);
uint8_t get_random_duration(uint8_t minDuration, uint8_t maxDuration);
void give_reverse_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_healing_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_speed_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_no_z_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_no_b_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void rotate_c_buttons(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_shock_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_bonk_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_sound_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_textbox_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_rainbow_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_interface_trap(z64_file_t *save, int16_t arg1, int16_t arg2);
void give_earthquake_trap(z64_file_t *save, int16_t arg1, int16_t arg2);

enum dungeon {
    DEKU_ID    = 0,
    DODONGO_ID = 1,
    JABU_ID    = 2,
    FOREST_ID  = 3,
    FIRE_ID    = 4,
    WATER_ID   = 5,
    SPIRIT_ID  = 6,
    SHADOW_ID  = 7,
    BOTW_ID    = 8,
    ICE_ID     = 9,
    TOWER_ID   = 10,
    GTG_ID     = 11,
    FORT_ID    = 12,
    CASTLE_ID  = 13,
};

#endif
