// Copyright Cristiano 2022
//
// Created by Cristiano Sellitto
// Created in December 2022
// A file for the "Space Aliens" game

#include <gb/gb.h>
#include <stdio.h>

#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "Background.c"

void main() {
    // Get user input
    uint8_t joypadData;

    // Load sprite data (16 sprites) into pos 0
    set_sprite_data(0, 16, SpaceAliens);
    // Load meta sprites 0-4
    set_meta_sprite_tile(0, 1, 2, 3, 4);
    // Move meta sprite ID 0 to point (76, 120)
    move_meta_sprite(0, 76, 120);

    // Set background tile sheet 0 to the same tile sheet
    set_bkg_data(0, 16, SpaceAliens);
    // Load tiles from (0, 0) to (20, 36) from the tile sheet called Background
    set_bkg_tiles(0, 0, 20, 36, Background);

    SHOW_BKG; // Turn BG on
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game loop
    while (1) {
        // Get D-Pad input
        joypadData = joypad();

        // Joypad inputs
        if (joypadData & J_LEFT) {
            // Move sprite 0 -1 in x and 0 in y
            scroll_meta_sprite(0, -1, 0);
        }
        if (joypadData & J_RIGHT) {
            // Move sprite 0 1 in x and 0 in y
            scroll_meta_sprite(0, 1, 0);
        }
        if (joypadData & J_UP) {
            // Move sprite 0 0 in x and -1 in y
            scroll_meta_sprite(0, 0, -1);
        }
        if (joypadData & J_DOWN) {
            // Move sprite 0 0 in x and 1 in y
            scroll_meta_sprite(0, 0, 1);
        }

        // Scroll BG 0 in the x and -1 in the y
        scroll_bkg(0, -1);

        // Wait until the end of the frame (1/60 of a second)
        wait_vbl_done();
    }
}
