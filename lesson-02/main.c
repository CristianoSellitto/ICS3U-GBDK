// Copyright Cristiano 2022
//
// Created by Cristiano Sellitto
// Created in December 2022
// A file for the "Space Aliens" game

#include <gb/gb.h>
#include <stdio.h>

#include "SpaceAliens.c"

void main() {
    // Load sprite data (16 sprites) into pos 0
    set_sprite_data(0, 16, SpaceAliens);
    // Load sprite index 15 to sprite ID 0
    set_sprite_tile(0, 15);
    // Move sprite ID 0 to point (88, 78)
    move_sprite(0, 88, 78);


    set_sprite_tile(1, 5);
    set_sprite_tile(2, 10);
    move_sprite(1, 8, 144);
    move_sprite(2, 64, 64);

    SHOW_SPRITES;
}
