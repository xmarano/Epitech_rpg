/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** inventory.h
*/
#include "../my.h"
#include "../rpg.h"
#include "weapons.h"
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Config.h>

#ifndef INVENTORY_H
    #define INVENTORY_H

typedef struct inv2_sprite {
    sfSprite *inventory;
    sfTexture *Inventory;
    sfSprite *inventory2;
    sfTexture *Inventory2;
    sfSprite *cursor;
    sfTexture *Cursor;
    sfVector2f pos_cursor;
    sfVector2f pos_hooved;
    sfRectangleShape *rect_inv;
    sfRectangleShape *hooved_weapon;
}inv2_sprite_t;

typedef struct inventaire {
    char *item1;
    char *item2;
    char *item3;
    char *item4;
    char *item5;
    inv2_sprite_t inv_sprite;
} inv_t;

typedef struct stats_char {
    int level;
    int xp;
    int current_hp;
    int max_hp;
    int lck;
    int skl;
    int def;
    int res;
    int str;
    int spd;
    int mov;
} stchar_t;

typedef struct Perso {
    char *name_perso; // nom du perso
    char *type; // type du perso
    Weapons_t current_weapon[20]; //arme actuelle
    stchar_t stat_p; //stat du perso
    inv_t inv; //inventaire du perso
    bool is_visible;
    bool is_visible2;
    char texture_dialogue[100]; //texture dialogue
    char texture_battle[100]; // texture combat
    sfSprite *dialogue_sprite;
    sfTexture *dialogue_texture;
}Perso_t;

#endif
