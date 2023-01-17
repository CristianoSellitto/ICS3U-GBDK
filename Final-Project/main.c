// Copyright Cristiano 2023
//
// Created by Cristiano Sellitto
// Created in January 2023
// A file for the final project game

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "TestImage.c"
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
    unsigned int timeCounter = 0;

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
        timeCounter++;
        if (timeCounter > (3 * 60)) {
            return next_screen;
        }

        // Wait until the end of the frame (1/60 of a second)
        wait_vbl_done();
    }
}

screen_t game() {
    // Get controls
    uint8_t joypadData;

    // Time variables
    unsigned int time = 0;
    int buttonWaitTime = 0;

    // Position Variables
    int playerXPos = 8;
    int playerYPos = 16;

    // Sound Settings | MUST BE IN THIS ORDER
    NR52_REG = 0X80; // Selects which channels to use (0x80 is all of them)
    NR50_REG = 0X77; // Turns on sound
    NR51_REG = 0XFF; // Sets left and right channels to the max (0x77)

    // Load sprite data (16 sprites) into pos 0
    set_sprite_data(0, 16, TestImage);
    // Load meta sprites 0-4
    set_meta_sprite_tile(0, 1, 2, 3, 4);
    // Move meta sprite ID 0 to a point (x, y)
    move_meta_sprite(0, playerXPos, playerYPos);

    //SHOW_BKG; // Turn BG on
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game loop
    while (1) {
        // Get controls
        joypadData = joypad();

        time++;

        // Up Button
        if (joypadData & J_UP) {
            if (buttonWaitTime > time) {
                playerYPos -= 8;
                move_meta_sprite(0, playerXPos, playerYPos);
            } else {
                buttonWaitTime = time + (3 * 60);
            }
        }

        // Down Button
        if (joypadData & J_DOWN) {
            if (buttonWaitTime > time) {
                playerYPos += 8;
                move_meta_sprite(0, playerXPos, playerYPos);
            } else {
                buttonWaitTime = time + (3 * 60);
            }
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
