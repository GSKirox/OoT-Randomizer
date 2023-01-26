#include "z64.h"
#include "gfx.h"
#include "text.h"
#include "rainbow.h"
#include "hud_colors.h"

void manage_traps();
void draw_traps_effects(z64_disp_buf_t *db);
void reverse_trap(uint32_t totalTimeOfTrap);
void speed_trap(uint32_t totalTimeOfTrap, float speed);
void no_z_trap(uint32_t totalTimeOfTrap);
void no_b_trap(uint32_t totalTimeOfTrap);
void c_button_trap();
void shock_trap();
void bonk_trap();
void textbox_trap();
void sound_trap(uint32_t totalTimeOfTrap);
void rainbow_trap(uint32_t totalTimeOfTrap);
void interface_trap(uint32_t totalTimeOfTrap);
void earthquake_trap(uint32_t totalTimeOfTrap);
void draw_countdown(z64_disp_buf_t *db, int offsetCountdownX, int countdown);

#define BLOCK_EFFECT (0x00000001 | \
                    0x00000002 | \
                    0x00000080 | \
                    0x00000400 | \
                    0x10000000 | \
                    0x20000000)

#define CAN_DRAW_OR_APPLY_EFFECT   (((z64_link.state_flags_1 & BLOCK_EFFECT ) == 0) && \
                            ((uint32_t)z64_ctxt.state_dtor==z64_state_ovl_tab[3].vram_dtor) && \
                            (z64_file.game_mode == 0) && \
                            ((z64_event_state_1 & 0x20) == 0) && \
                            z64_game.pause_ctxt.state != 6)
