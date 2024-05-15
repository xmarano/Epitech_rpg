/*
** EPITECH PROJECT, 2023
** B-MUL-200-MAR-2-1-myrpg-yanis.prevost
** File description:
** setup_sp_dialogue.c
*/

#include "../rpg.h"
#include "../include/perso.h"
#include "../include/menu.h"
#include "../include/worlds.h"

sfVector2f swap_pou_pose2(sfVector2f pose, int word)
{
    if (word == 5) {
        pose.x += 110;
        pose.y -= 60;
    }
    if (word == 6) {
        pose.x -= 550;
        pose.y -= 120;
    }
    if (word == 7) {
        pose.x -= 550;
        pose.y -= 80;
    }
    if (word == 8) {
        pose.x -= 415;
        pose.y += 110;
    }
    return (pose);
}

sfVector2f swap_pou_pose(sfVector2f pose, int word)
{
    if (word == 0) {
        pose.x -= 240;
        pose.y -= 50;
    }
    if (word == 1) {
        pose.x -= 300;
        pose.y -= 50;
    }
    if (word == 2) {
        pose.x -= 240;
        pose.y += 160;
    }
    if (word == 3) {
        pose.x -= 230;
        pose.y -= 120;
    }
    if (word == 4) {
        pose.x -= 80;
        pose.y -= 300;
    }
    return swap_pou_pose2(pose, word);
}

static void anime_mouse(Global_t *m, int offset, int max_value)
{
    if (m->hub.rect_dia.left < max_value - offset) {
        if (m->hub.rect_dia.top == 96) {
            m->hub.rect_dia.top = 80;
            m->hub.rect_dia.left += 32;
            return;
        }
        if (m->hub.rect_dia.top == 80) {
            m->hub.rect_dia.top += 16;
        }
    } else {
        m->hub.rect_dia.left = 0;
        m->hub.rect_dia.top = 80;
    }
}

static void move_rect(Global_t *m, int offset, int max_value)
{
    sfTime time = sfClock_getElapsedTime(m->hub.clock);
    float seconds = time.microseconds / 1000000.0;

    if (seconds >= 0.2) {
        sfClock_restart(m->hub.clock);
        anime_mouse(m, offset, max_value);
    }
}

void draw_pouill_dia(Global_t *m, int word, sfVector2f pose)
{
    sfIntRect base = {0, 0, 91, 80};
    sfVector2f animated_rect_pos;

    pose = swap_pou_pose(pose, word);
    sfSprite_setPosition(m->hub.dia_pouill, pose);
    pose.x -= 50;
    pose.y += 150;
    sfSprite_setPosition(m->hub.cadre, pose);
    sfSprite_setTextureRect(m->hub.dia_pouill, base);
    sfRenderWindow_drawSprite(m->window, m->hub.dia_pouill, NULL);
    move_rect(m, 32, 96);
    animated_rect_pos = sfSprite_getPosition(m->hub.dia_pouill);
    animated_rect_pos.x += 72.5;
    animated_rect_pos.y += 109.5;
    sfSprite_setPosition(m->hub.dia_pouill, animated_rect_pos);
    sfSprite_setTextureRect(m->hub.dia_pouill, m->hub.rect_dia);
    sfRenderWindow_drawSprite(m->window, m->hub.dia_pouill, NULL);
    sfRenderWindow_drawSprite(m->window, m->hub.cadre, NULL);
    what_dialogue(m, word);
}

void destroy_dialoque(Global_t *m)
{
    sfSprite_destroy(m->hub.dia_pouill);
    sfTexture_destroy(m->hub.Dia_pouill);
    sfSprite_destroy(m->hub.cadre);
    sfTexture_destroy(m->hub.Cadre);
    sfClock_destroy(m->hub.clock);
}

void init_pouill_dialog(Global_t *m)
{
    char *link_pou = "assets/perso/dialogue/npc/pouilleux_dialogue.png";

    m->hub.dia_pouill = sfSprite_create();
    m->hub.Dia_pouill = sfTexture_createFromFile(link_pou, NULL);
    sfSprite_setTexture(m->hub.dia_pouill, m->hub.Dia_pouill, sfFalse);
    sfSprite_setScale(m->hub.dia_pouill, (sfVector2f){2.3, 2.3});
    m->hub.rect_dia.top = 80;
    m->hub.rect_dia.left = 0;
    m->hub.rect_dia.width = 32;
    m->hub.rect_dia.height = 16;
    m->hub.clock = sfClock_create();
}