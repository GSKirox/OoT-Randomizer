#include "traps.h"

extern float SPEED_MULTIPLIER;

const int trap_text_width = 10;
const int trap_text_height = 10;

// Unused trap, puts a black fog
//typedef void(*adjustlights_t)(z64_game_t *game, float arg1, float arg2, float arg3, float arg4);
//#define z64_adjustlights   ((adjustlights_t)      0x800631D8)
//z64_adjustlights(&z64_game, 1.0f, 0.0f, 0.1f, 0.0f);


struct traps_ctxt_t {
    float             speed_multiplier;
    uint8_t           speed_multiplier_seconds;
    uint8_t           traps_c_buttons;
    uint8_t           no_z;
    uint8_t           no_z_seconds;
    uint8_t           no_b;
    uint8_t           no_b_seconds;
    uint8_t           reverse_controls;
    uint8_t           reverse_controls_seconds;
    uint8_t           sound;
    uint8_t           sound_seconds;
    uint8_t           interface;
    uint8_t           interface_seconds;
    uint8_t           shock;
    uint8_t           bonk;
    uint8_t           textbox;
    uint8_t           rainbow;
    uint8_t           rainbow_seconds;
    uint8_t           earthquake;
    uint8_t           earthquake_seconds;
} traps_ctxt = { 
    .speed_multiplier = 1.0
};

static uint32_t framesReverse = 0;
static uint32_t framesNoZ = 0;
static uint32_t framesNoB = 0;
static uint32_t framesSpeed = 0;
static uint32_t framesSound = 0;
static uint32_t framesInterface = 0;
static uint32_t framesShock = 0;
static uint32_t framesBonk = 0;
static uint32_t messageOn = 0;
static uint32_t framesRainbow = 0;
static uint32_t framesEarthquake = 0;
static uint32_t rainbowMagicDirection = 1;
static uint16_t previousSceneIndex = 0;
void manage_traps() {
    /* C button trap */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.traps_c_buttons != 0) {
        int8_t oldCLeft = z64_file.c_button_slots[0];
        int8_t oldCDown = z64_file.c_button_slots[1];
        int8_t oldCRight = z64_file.c_button_slots[2];
        int8_t oldCLeftItem = z64_file.button_items[1];
        int8_t oldCDownItem = z64_file.button_items[2];
        int8_t oldCRightItem = z64_file.button_items[3];

        z64_file.c_button_slots[0] = oldCRight;
        z64_file.button_items[1] = oldCRightItem;
        z64_UpdateItemButton(&z64_game, 1);
        z64_file.c_button_slots[1] = oldCLeft;
        z64_file.button_items[2] = oldCLeftItem;
        z64_UpdateItemButton(&z64_game, 2);
        z64_file.c_button_slots[2] = oldCDown;
        z64_file.button_items[3] = oldCDownItem;
        z64_UpdateItemButton(&z64_game, 3);

        if (traps_ctxt.traps_c_buttons == 1)
            traps_ctxt.traps_c_buttons = 0;
    }

    /* Shocking trap */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.shock != 0) {

        // Thunder and Laughing Phantom Ganon sound 1 sec later
        if (framesShock == 0) {
            z64_Audio_PlaySoundGeneral(0x282E, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
        }
        if (framesShock / 20 == 1) {
            z64_Audio_PlaySoundGeneral(0x38B0, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
        }

        if (framesShock == 0) {
            z64_LinkDamage(&z64_game, &z64_link, 0x04, 0, 0, 0x14);
        }
        // Another shock 5 secs later
        if (framesShock == 100) {
            // Thunder
            z64_Audio_PlaySoundGeneral(0x282E, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);

            z64_LinkDamage(&z64_game, &z64_link, 0x04, 0, 0, 0x14);
        }
        // Another shock 5 secs later
         if (framesShock == 200) {
            // Thunder
            z64_Audio_PlaySoundGeneral(0x282E, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);

            z64_LinkDamage(&z64_game, &z64_link, 0x04, 0, 0, 0x14);
            framesShock = 0;
            traps_ctxt.shock = 0;
        }

        framesShock++;
    }

    /* Bonk trap */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.bonk != 0) {

        if (framesBonk == 0) {
            // Hammer bonk
            z64_Audio_PlaySoundGeneral(0x180A, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
            z64_LinkDamage(&z64_game, &z64_link, 0x01, 0, 0, 0x14);
        }

        // Another bonk 5 secs later
        if (framesBonk == 100) {
            // Hammer bonk
            z64_Audio_PlaySoundGeneral(0x180A, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);

            z64_LinkDamage(&z64_game, &z64_link, 0x01, 0, 0, 0x14);
        }
        // Another bonk 5 secs later
        if (framesBonk == 200) {
            // Hammer bonk
            z64_Audio_PlaySoundGeneral(0x180A, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);

            z64_LinkDamage(&z64_game, &z64_link, 0x01, 0, 0, 0x14);
            framesBonk = 0;
            traps_ctxt.bonk = 0;
        }
        framesBonk++;
    }

    /* Speed Multiplier */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.speed_multiplier_seconds > 0 && traps_ctxt.speed_multiplier) {
        if (traps_ctxt.speed_multiplier > 1.0) {
            if (framesSpeed == 0 || z64_game.scene_index != previousSceneIndex) {
                z64_ModifyTempo(1.18921f, 30);
                previousSceneIndex = z64_game.scene_index;
            }
        }
        if (traps_ctxt.speed_multiplier < 1.0) {
            if (framesSpeed == 0 || z64_game.scene_index != previousSceneIndex) {
                z64_ModifyTempo(0.840896f, 30);
                previousSceneIndex = z64_game.scene_index;
            }
        }

        if (framesSpeed / 20 < traps_ctxt.speed_multiplier_seconds) {
            SPEED_MULTIPLIER = traps_ctxt.speed_multiplier;
            framesSpeed++;
        }
        else {
            traps_ctxt.speed_multiplier_seconds = 0;
            framesSpeed = 0;
            SPEED_MULTIPLIER = traps_ctxt.speed_multiplier = 1.0;
            z64_ModifyTempo(1.0f, 30);
        }
    }

    /* No Z */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.no_z_seconds > 0 && traps_ctxt.no_z) {
        if (framesNoZ < traps_ctxt.no_z_seconds * 20) {
            z64_game.common.input[0].raw.pad.z = 0;
            z64_game.common.input[0].pad_pressed.z = 0;

            framesNoZ++;
        }
        else {
            traps_ctxt.no_z_seconds = 0;
            framesNoZ = 0;
            traps_ctxt.no_z = 0;
        }
    }

    /* No B */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.no_b_seconds > 0 && traps_ctxt.no_b) {
        if (framesNoB < traps_ctxt.no_b_seconds * 20) {
            z64_game.common.input[0].raw.pad.b = 0;
            z64_game.common.input[0].pad_pressed.b = 0;

            framesNoB++;
        }
        else {
            traps_ctxt.no_b_seconds = 0;
            framesNoB = 0;
            traps_ctxt.no_b = 0;
        }
    }

    /* Reverse Controls */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.reverse_controls_seconds > 0 && traps_ctxt.reverse_controls) {
        if (framesReverse < traps_ctxt.reverse_controls_seconds * 20) {
            z64_game.common.input[0].raw.x = -z64_game.common.input[0].raw.x;
            z64_game.common.input[0].raw.y = -z64_game.common.input[0].raw.y;
            z64_game.common.input[0].x_diff = -z64_game.common.input[0].x_diff;
            z64_game.common.input[0].y_diff = -z64_game.common.input[0].y_diff;
            z64_game.common.input[0].adjusted_x = -z64_game.common.input[0].adjusted_x;
            z64_game.common.input[0].adjusted_y = -z64_game.common.input[0].adjusted_y;

            framesReverse++;
        }
        else {
            traps_ctxt.reverse_controls_seconds = 0;
            framesReverse = 0;
            traps_ctxt.reverse_controls = 0;
        }
    }

    /* Sound trap : play a sound every 10 frames */
    if (traps_ctxt.sound_seconds > 0 && traps_ctxt.sound) {
        if (framesSound < traps_ctxt.sound_seconds * 20) {
            framesSound++;
            if (framesSound % 10 == 0) {
                // MWEEP
                z64_Audio_PlaySoundGeneral(0x687A, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
            }
        }
        else {
            traps_ctxt.sound_seconds = 0;
            framesSound = 0;
            traps_ctxt.sound = 0;
        }
    }

    // Message trap
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.textbox > 0) {
        if (messageOn == 0) {
            z64_DisplayTextbox(&z64_game, 0x045C, 0);
        }
        if (z64_MessageGetState(((uint8_t *)(&z64_game)) + 0x20D8) == 0) {
            traps_ctxt.textbox = 0;
            messageOn = 0;
        } else {
            z64_link.common.frozen = 10;
            messageOn = 1;
        }
    }

    // Rainbow trap
    if (traps_ctxt.rainbow_seconds > 0 && traps_ctxt.rainbow) {
        if (framesRainbow < traps_ctxt.rainbow_seconds * 20) {

            colorRGB8_t rainbow = get_rainbow_color(framesRainbow, 3);
            z64_file.gameinfo->a_button_r = rainbow.r;
            z64_file.gameinfo->a_button_g = rainbow.g;
            z64_file.gameinfo->a_button_b = rainbow.b;
            z64_file.gameinfo->b_button_r = rainbow.r;
            z64_file.gameinfo->b_button_g = rainbow.g;
            z64_file.gameinfo->b_button_b = rainbow.b;
            z64_file.gameinfo->c_button_r = rainbow.r;
            z64_file.gameinfo->c_button_g = rainbow.g;
            z64_file.gameinfo->c_button_b = rainbow.b;
            z64_file.gameinfo->magic_fill_r = rainbow.r;
            z64_file.gameinfo->magic_fill_g = rainbow.g;
            z64_file.gameinfo->magic_fill_b = rainbow.b;

            colorRGB16_t* beating_no_dd    = (colorRGB16_t*)0x801D8B92;
            colorRGB16_2_t* normal_no_dd   = (colorRGB16_2_t*)0x801D8B9E;
            colorRGB16_t* beating_dd       = (colorRGB16_t*)0x8011BD38;
            colorRGB16_t* normal_dd        = (colorRGB16_t*)0x8011BD50;
            beating_no_dd->r   = rainbow.r;
            beating_no_dd->g   = rainbow.g;
            beating_no_dd->b   = rainbow.b;
            normal_no_dd->r1 = rainbow.r;
            normal_no_dd->g1 = rainbow.g;
            normal_no_dd->b1 = rainbow.b;
            beating_dd->r = rainbow.r;
            beating_dd->g = rainbow.g;
            beating_dd->b = rainbow.b;
            normal_dd->r  = rainbow.r;
            normal_dd->r  = rainbow.g;
            normal_dd->r  = rainbow.b;

            use_default_rupee_color(0);
            set_rupee_color_extern(rainbow);

            if (framesRainbow % 3 == 0) {
                z64_file.magic_meter_size += (framesRainbow % 0x30) * rainbowMagicDirection;
                if (z64_file.magic_meter_size > 0x60) {
                    z64_file.magic_meter_size = 0x60;
                    rainbowMagicDirection = -1;
                }
                if (z64_file.magic_meter_size < 0x30) {
                    z64_file.magic_meter_size = 0x30;
                    rainbowMagicDirection = 1;
                }
            }

            framesRainbow++;
        }
        else {
            traps_ctxt.rainbow_seconds = 0;
            framesRainbow = 0;
            traps_ctxt.rainbow = 0;
            use_default_rupee_color(1);
            if (z64_file.magic_capacity_set == 1) {
                z64_file.magic_meter_size = 0x30;
            }
            if (z64_file.magic_capacity_set == 2) {
                z64_file.magic_meter_size = 0x60;
            }
        }
    }

    // UI trap
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.interface_seconds > 0 && traps_ctxt.interface) {
         if (framesInterface < traps_ctxt.interface_seconds * 20) {

            z64_file.nextHudVisibilityMode = z64_file.hudVisibilityMode = 1;
            framesInterface++;
         }
         else {
            framesInterface = 0;
            traps_ctxt.interface = 0;
            traps_ctxt.interface_seconds = 0;
            z64_file.nextHudVisibilityMode = z64_file.hudVisibilityMode = 50;
         }
    }

    // Earthquake trap
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.earthquake_seconds > 0 && traps_ctxt.earthquake) {
        if (framesEarthquake < traps_ctxt.earthquake_seconds * 20) {
            if (framesEarthquake == 0 || z64_game.scene_index != previousSceneIndex) {
                void* Camera = z64_game.mainCamera;
                z64_Camera_RequestQuake(&Camera, 0, 2, traps_ctxt.earthquake_seconds*20 - framesEarthquake);
            }
            // Play earthquake sound every 5sec
             if (framesEarthquake % 100 == 0) {
                z64_Audio_PlaySoundGeneral(0x1845, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
            }
            framesEarthquake++;
        }
        else {
            framesEarthquake = 0;
            traps_ctxt.earthquake = 0;
            traps_ctxt.earthquake_seconds = 0;
         }
    }  
}

void draw_traps_effects(z64_disp_buf_t *db) {

    // Call setup display list
    gSPDisplayList(db->p++, &setup_db);
    gDPPipeSync(db->p++);
    gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(db->p++, 0, 0, 0xDA, 0xD3, 0x0B, 0xFF);

    /* Reverse Controls */
    int offsetX = 0;
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.reverse_controls_seconds > 0 && traps_ctxt.reverse_controls) {
        if (framesReverse / 20 < traps_ctxt.reverse_controls_seconds) {  
            draw_countdown(db, 0, traps_ctxt.reverse_controls_seconds - framesReverse / 20);
            offsetX++;
        }
    }
    /* Speed multiplier */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.speed_multiplier_seconds > 0 && traps_ctxt.speed_multiplier) {
        if (framesSpeed / 20 < traps_ctxt.speed_multiplier_seconds) {
            draw_countdown(db, offsetX, traps_ctxt.speed_multiplier_seconds - framesSpeed / 20);
            offsetX++;
        }
    }
    /* No Z */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.no_z_seconds > 0 && traps_ctxt.no_z) {
        if (framesNoZ / 20 < traps_ctxt.no_z_seconds) {
            draw_countdown(db, offsetX, traps_ctxt.no_z_seconds - framesNoZ / 20);
            offsetX++;
        }
    }
    /* No B */
    if (CAN_DRAW_OR_APPLY_EFFECT && traps_ctxt.no_b_seconds > 0 && traps_ctxt.no_b) {
        if (framesNoB / 20 < traps_ctxt.no_b_seconds) {
            draw_countdown(db, offsetX, traps_ctxt.no_b_seconds - framesNoB / 20);
            offsetX++;
        }
    }
    text_flush_size(db, trap_text_width, trap_text_height, 0, 0);

    gDPFullSync(db->p++);
    gSPEndDisplayList(db->p++);
}

void reverse_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.reverse_controls = 1;
    traps_ctxt.reverse_controls_seconds = totalTimeOfTrap;
    // Refresh timer
    framesReverse = 0;

    // Laughing Phantom Ganon sound
    z64_Audio_PlaySoundGeneral(0x38B0, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
}

void speed_trap(uint32_t totalTimeOfTrap, float speed) {
    traps_ctxt.speed_multiplier = speed;
    traps_ctxt.speed_multiplier_seconds = totalTimeOfTrap;
    // Refresh timer
    framesSpeed = 0;

    if (speed < 1.0) {
        // Iron boots sound
        z64_Audio_PlaySoundGeneral(0x080D, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
    }
    else {
        // Epona sound
        //z64_Audio_PlaySoundGeneral(0x2805, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
    }
}

void c_button_trap() {
    traps_ctxt.traps_c_buttons = 1;

    // Ganondorf tennis sound
    z64_Audio_PlaySoundGeneral(0x39CA, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
}

void shock_trap() {
    traps_ctxt.shock = 1;
}

void bonk_trap() {
    traps_ctxt.bonk = 1;
}

void textbox_trap() {
    traps_ctxt.textbox = 1;
}

void no_z_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.no_z = 1;
    traps_ctxt.no_z_seconds = totalTimeOfTrap;
    // Refresh timer
    framesNoZ = 0;

    // Zelda gasp sound
    z64_Audio_PlaySoundGeneral(0x6879, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
}

void no_b_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.no_b = 1;
    traps_ctxt.no_b_seconds = totalTimeOfTrap;
    // Refresh timer
    framesNoB = 0;

    // Zelda gasp sound
    z64_Audio_PlaySoundGeneral(0x6879, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
}

void sound_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.sound = 1;
    traps_ctxt.sound_seconds = totalTimeOfTrap;
    // Refresh timer
    framesSound = 0;
}

void rainbow_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.rainbow = 1;
    traps_ctxt.rainbow_seconds = totalTimeOfTrap;
    // Refresh timer
    framesRainbow = 0;
}

void earthquake_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.earthquake = 1;
    traps_ctxt.earthquake_seconds = totalTimeOfTrap;
    // Refresh timer
    framesEarthquake = 0;
}

void interface_trap(uint32_t totalTimeOfTrap) {
    traps_ctxt.interface = 1;
    traps_ctxt.interface_seconds = totalTimeOfTrap;
    // Refresh timer
    framesInterface = 0;

     // Talon wtf
    z64_Audio_PlaySoundGeneral(0x6853, (void *)0x80104394, 0x04, (float*)0x801043A0, (float*)0x801043A0, (uint8_t *)0x801043A8);
}

void draw_countdown(z64_disp_buf_t *db, int offsetCountdownX, int countdown) {

    int countdown_digits = 0;
    int countdown_copy = countdown;
    while (countdown_copy >= 1) {
        countdown_digits++;
        countdown_copy /= 10;
    }
    int str_len = countdown_digits;
    char text[str_len + 1];
    text[str_len] = 0;
    countdown_copy = countdown;
    for (int i = countdown_digits - 1; i >= 0; i--) {
        text[i] = (countdown_copy % 10) + '0';
        countdown_copy /= 10;
    }

    int offsetX = 3*offsetCountdownX * font_sprite.tile_w;
    int height = font_sprite.tile_h * 2.5;
    if (z64_file.magic_capacity_set > 0)
        height += font_sprite.tile_h * 0.8;
    if (z64_file.energy_capacity > 10 * 0x10)
        height += font_sprite.tile_h * 0.8;
    text_print_size(text, Z64_SCREEN_WIDTH / 12 + offsetX, height, trap_text_height);
}
