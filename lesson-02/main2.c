// Copyright Cristiano 2022
//
// Created by Cristiano Sellitto
// Created in December 2022
// A file for the "Space Aliens" game

#include <gb/gb.h>
#include <stdio.h>

#include "MetaSprites.c"
#include "SpaceAliens.c"

void main() {
    // Load sprite data (16 sprites) into pos 0
    set_sprite_data(0, 16, SpaceAliens);
    // Load meta sprites 0-4
    set_meta_sprite_tile(0, 1, 2, 3, 4);
    // Move meta sprite ID 0 to point (76, 120)
    move_meta_sprite(0, 76, 120);

    SHOW_SPRITES;
    DISPLAY_ON;
}
