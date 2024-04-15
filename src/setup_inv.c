/*
** EPITECH PROJECT, 2023
** B-MUL-200-MAR-2-1-myrpg-yanis.prevost
** File description:
** setup_inv.c
*/

#include "my.h"
#include "rpg.h"
#include "menu.h"
#include "include/inventory.h"

sfSprite *set_weapon(Global_t *m, char *filename, sfVector2f pose, sfVector2f scale)
{
    sfSprite *sprite = sfSprite_create();

    m->perso.stat_w.init.texture = sfTexture_createFromFile(filename, NULL);
    sfSprite_setTexture(sprite, m->perso.stat_w.init.texture, sfFalse);
    sfSprite_setPosition(sprite, pose);
    sfSprite_setScale(sprite, scale);
    return sprite;
}