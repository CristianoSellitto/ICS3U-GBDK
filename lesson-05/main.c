// Copyright Cristiano 2022
//
// Created by Cristiano Sellitto
// Created in December 2022
// A file for the "Space Aliens" game

#include <gb/gb.h>
#include <stdio.h>

#include "GBDK_Constants.h"
#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "Background.c"

void main() {
    // Sprite Pos Variables
    const int FIXED_Y_POSITION_OF_SHIP = 144;
    int shipXPosition = 76;
    int shipYPosition = FIXED_Y_POSITION_OF_SHIP;

    // Load sprite data (16 sprites) into pos 0
    set_sprite_data(0, 16, SpaceAliens);
    // Load meta sprites 0-4
    set_meta_sprite_tile(0, 1, 2, 3, 4);
    // Move meta sprite ID 0 to point (76, 120)
    move_meta_sprite(0, shipXPosition, shipYPosition);

    // Set background tile sheet 0 to the same tile sheet
    set_bkg_data(0, 16, SpaceAliens);
    // Load tiles from (0, 0) to (20, 36) from the tile sheet called Background
    set_bkg_tiles(0, 0, 20, 36, Background);

    SHOW_BKG; // Turn BG on
    SHOW_SPRITES; // Show sprites
    DISPLAY_ON; // Turn on display

    // Game loop
    while (1) {
        // Get D-Pad input
        switch (joypad()) {
            case J_LEFT:
                // Move sprite id 0 by (x, y), (-1, 0)
                scroll_meta_sprite(0, -1, 0);
                shipXPosition -= 1;
                if (shipXPosition < 8) {
                    shipXPosition = 8;
                    move_meta_sprite(0, 8, FIXED_Y_POSITION_OF_SHIP);
                }
                break;
            case J_RIGHT:
                // Move sprite id 0 by (x, y), (1, 0)
                scroll_meta_sprite(0, 1, 0);
                shipXPosition += 1;
                if (shipXPosition > SCREEN_WIDTH - 8) {
                    shipXPosition > SCREEN_WIDTH - 8;
                    move_meta_sprite(0, (uint8_t)(SCREEN_WIDTH - 8), FIXED_Y_POSITION_OF_SHIP);
                }
                break;
            default:
                break;
        }

        // Scroll BG 0 in the x and -1 in the y
        scroll_bkg(0, -1);

        // Wait until the end of the frame (1/60 of a second)
        wait_vbl_done();
    }
}
