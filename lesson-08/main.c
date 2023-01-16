// Copyright Cristiano 2022
//
// Created by Cristiano Sellitto
// Created in December 2022
// A file for the "Space Aliens" game

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "GBDK_Constants.h"
#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "SpaceAliensData.c"
#include "SpaceAliensMap.c"
#include "Background.c"

typedef enum { // Define scenes
    SPLASH,
    START,
    GAME,
    GAME_OVER
} screen_t;

screen_t splash() {
    // User inputs
    uint8_t joypadData;
    screen_t next_screen = START;

    // Time variable
    unsigned int timeCounter = 0;

    printf("\n\n\n\n\n");
    printf("   MT Game Studios");
    printf("        Presents");
    printf("\n\n\n\n\n\n");
    printf("    Space Aliens");

    DISPLAY_ON; // Turn display on

    // Game loop
    while (1) {
        // Get controls
        joypadData = joypad();

        // Start Button
        if (joypadData & J_START) {
            return next_screen;
        }

        // Go to next scene after two seconds of no input
        timeCounter++;
        if (timeCounter > (3 * 60)) {
            return next_screen;
        }

        // Wait until the end of the frame (1/60 of a second)
        wait_vbl_done();
    }
}

screen_t start() {
    screen_t next_screen = GAME;

    set_bkg_data(0, 215, space_aliens_data);
    set_bkg_tiles(0, 0, 20, 18, space_aliens_map);

    SHOW_BKG;
    DISPLAY_ON;

    // Wait for start button input
    waitpad(J_START);
    return next_screen;
}

screen_t game() {
    // Get controls
    uint8_t joypadData;

    // Sprite Pos Variables
    const int FIXED_Y_POSITION_OF_SHIP = 144;
    int shipXPosition = 76;
    int shipYPosition = FIXED_Y_POSITION_OF_SHIP;

    // A Button Bools

    bool aButtonJustPressed = false;
    bool aButtonStillPressed = false;

    // Sound Settings | MUST BE IN THIS ORDER
    NR52_REG = 0X80; // Selects which channels to use (0x80 is all of them)
    NR50_REG = 0X77; // Turns on sound
    NR51_REG = 0XFF; // Sets left and right channels to the max (0x77)

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
        // Get controls
        joypadData = joypad();

        // Left D-Pad
        if (joypadData & J_LEFT) {
            // Move sprite id 0 by (x, y), (-1, 0)
            scroll_meta_sprite(0, -1, 0);
            shipXPosition -= 1;
            if (shipXPosition < 8) {
                shipXPosition = 8;
                move_meta_sprite(0, 8, FIXED_Y_POSITION_OF_SHIP);
            }
        }

        // Right D-Pad
        if (joypadData & J_RIGHT) {
            // Move sprite id 0 by (x, y), (1, 0)
            scroll_meta_sprite(0, 1, 0);
            shipXPosition += 1;
            if (shipXPosition > SCREEN_WIDTH - 8) {
                shipXPosition > SCREEN_WIDTH - 8;
                move_meta_sprite(0, (uint8_t)(SCREEN_WIDTH - 8), FIXED_Y_POSITION_OF_SHIP);
            }
        }

        // A Button
        if (joypadData & J_A) {
            if (aButtonJustPressed == true) {
                aButtonStillPressed = true;
            } else {
                aButtonJustPressed = true;
                // Play a sound:
                NR10_REG = 0x16;
                NR11_REG = 0x82;
                NR12_REG = 0X69;
                NR13_REG = 0X59;
                NR14_REG = 0XC6;
            }
        } else {
            aButtonJustPressed = false;
            aButtonStillPressed = false;
        }

        // Scroll BG 0 in the x and -1 in the y
        scroll_bkg(0, -1);

        // Wait until the end of the frame (1/60 of a second)
        wait_vbl_done();
    }
}

void main() {
    // Current screen, default is TITLE
    screen_t current_screen = SPLASH;

    // Sound Settings | MUST BE IN THIS ORDER
    NR52_REG = 0X80; // Selects which channels to use (0x80 is all of them)
    NR50_REG = 0X77; // Turns on sound
    NR51_REG = 0XFF; // Sets left and right channels to the max (0x77)

    while(1) {
        if (current_screen == SPLASH) {
            current_screen = splash();
        } else if (current_screen == START) {
            current_screen = start();
        } else if (current_screen == GAME) {
            current_screen = game();
        } else if (current_screen == GAME_OVER) {
            printf("game_over");
            // current_screen = game_over();
        }
    }
}