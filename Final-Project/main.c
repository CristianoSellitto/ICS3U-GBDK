// Copyright Cristiano 2023
//
// Created by Cristiano Sellitto
// Created in January 2023
// A file for the final project game

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "boxWorldGBSprites.c"
#include "MetaSprites.c"

typedef enum { // Define scenes
    SPLASH,
    GAME
} screen_t;

screen_t splash() {
    // User inputs
    uint8_t joypadData;
    screen_t next_screen = GAME;

    // Time variable
    unsigned int time = 0;

    printf("Test");

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
        time++;
        if (time > (3 * 60)) {
            return next_screen;
        }

        // Wait until the end of the frame (1/60 of a second)
        wait_vbl_done();
    }
}

screen_t game() {
    // Get controls
    uint8_t joypadData;

    // Level Variable
    int currentLvl = 1;

    // Time variables
    // unsigned int time = 0;
    // int buttonWaitTime = 0;

    // Position Variables
    const int playerSpawnXPos = 8;
    const int playerSpawnYPos = 24;
    int playerXPos = 8;
    int playerYPos = 24;

    // Box variables
    int boxGroupLvlOne[3][3] = {
        {0, 1, 1},
        {0, 2, 2},
        {0, 3, 3},
    }; // Box ID, Box X Pos, Box Y Pos | Unit formula is 8 + 16 * Pos
    int boxXs[100];
    int boxYs[100];
    int boxGroupLvlIDs = 1 * 4;

    // A Button Bools
    bool aButtonJustPressed = false;
    bool aButtonStillPressed = false;

    // Sound Settings | MUST BE IN THIS ORDER
    NR52_REG = 0X80; // Selects which channels to use (0x80 is all of them)
    NR50_REG = 0X77; // Turns on sound
    NR51_REG = 0XFF; // Sets left and right channels to the max (0x77)

    // Load sprite data (35 sprites) into pos 0
    set_sprite_data(0, 35, boxWorldGBSprites);

    if (currentLvl == 1) {
        // Load boxes for Level 1
        boxGroupLvlIDs = 3 * 4;
        int boxNumber = 0;
        for (int counter = 4; counter <= boxGroupLvlIDs; counter += 4) {
            if (boxGroupLvlOne[boxNumber][0] == 0) {
                set_meta_sprite_tile(counter, 8, 10, 9, 11);
                move_meta_sprite(counter,
                                 8 + 16 * boxGroupLvlOne[boxNumber][1],
                                 8 + 16 * boxGroupLvlOne[boxNumber][2]);
                printf("\nBox type 0 generated");
            } else {
                printf("\nBox type invalid");
            }
            boxNumber++;
        }
        for (int boxNumber = 0; boxNumber <= 3; boxNumber++) {
            // Player reposition values
            int plrXRepos = -4;
            int plrYRepos = 15;

            // Min/max box variables
            int minBoxX = (8 + 16 * boxGroupLvlOne[boxNumber][1]) + plrXRepos;
            int maxBoxX = minBoxX + plrYRepos;
            int minBoxY = (8 + 16 * boxGroupLvlOne[boxNumber][2]) + plrXRepos;
            int maxBoxY = minBoxY + plrYRepos;
            for (boxNumber = 0; boxNumber > 3; boxNumber++) {
                for (int validXPos = minBoxX; validXPos <= maxBoxX; validXPos++) {
                    boxXs[boxNumber] = validXPos;
                    printf("\nBox X %d set", validXPos);
                }
                for (int validYPos = minBoxY; validYPos <= maxBoxY; validYPos++) {
                    boxYs[boxNumber] = validYPos;
                    printf("\nBox Y %d set", validYPos);
                }
            }
        }
    } else {
        printf("\nNot a valid level ID");
    }
        // Load player
        set_meta_sprite_tile(0, 0, 2, 1, 3); // Load meta sprites 0-3 to meta sprite IDs 0-3
        move_meta_sprite(0, playerXPos, playerYPos); // Move meta sprite ID 0 to a point (x, y)
        printf("\nPlayer generated");

    //SHOW_BKG; // Turn BG on
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game loop
    while (1) {
        // Get controls
        joypadData = joypad();

        // Add up time
        //time++;

        // Up Button | Move player up
        if (joypadData & J_UP) {
            if (playerYPos <= 20) {
                playerYPos = 20;
            } else {
                playerYPos -= 1;
            }
            move_meta_sprite(0, playerXPos, playerYPos);
        }

        // Down Button | Move player down
        if (joypadData & J_DOWN) {
            if (playerYPos >= 156) {
                playerYPos = 156;
            } else {
                playerYPos += 1;
            }
            move_meta_sprite(0, playerXPos, playerYPos);
        }

        // Left Button | Move player let
        if (joypadData & J_LEFT) {
            if (playerXPos <= 4) {
                playerXPos = 4;
            } else {
                playerXPos -= 1;
            }
            move_meta_sprite(0, playerXPos, playerYPos);
        }

        // Right Button | Move player right
        if (joypadData & J_RIGHT) {
            if (playerXPos >= 156) {
                playerXPos = 156;
            } else {
                playerXPos += 1;
            }
            move_meta_sprite(0, playerXPos, playerYPos);
        }

        // A Button | Check if the player is moving and is collided with a box
        // joypadData & J_RIGHT || joypadData & J_LEFT || joypadData & J_UP || joypadData & J_DOWN
        // if (joypadData & J_A) {
        //     for (int boxNumber = 0; boxNumber <= 3; boxNumber++) {
        //         // Player reposition values
        //         int plrXRepos = -4;
        //         int plrYRepos = 15;

        //         // Min/max box variables
        //         int minBoxX = (8 + 16 * boxGroupLvlOne[boxNumber][1]) + plrXRepos;
        //         int maxBoxX = minBoxX + plrYRepos;
        //         int minBoxY = (8 + 16 * boxGroupLvlOne[boxNumber][2]) + plrXRepos;
        //         int maxBoxY = minBoxY + plrYRepos;
        //         for (int validXPos = minBoxX; validXPos <= maxBoxX; validXPos++) {
        //             for (int validYPos = minBoxY; validYPos <= maxBoxY; validYPos++) {
        //                 if (playerXPos == validXPos && playerYPos == validYPos) {
        //                     playerXPos = playerSpawnXPos;
        //                     playerYPos = playerSpawnYPos;
        //                     move_meta_sprite(0, playerXPos, playerYPos);
        //                     break;
        //                 }
        //             }
        //         }
        //     }
        // }

        // B Button | Player position check
        if (joypadData & J_B) {
            //printf("\nPlayer Pos: (%d,", playerXPos);
            //printf("%d)", playerYPos);
            printf("Box X: %d", boxXs);
        }

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

    while(1) { // Set scenes
        if (current_screen == SPLASH) {
            current_screen = splash();
        } else if (current_screen == GAME) {
            current_screen = game();
        }
    }
}
