/*
** EPITECH PROJECT, 2023
** B-MUL-200-MAR-2-1-myrpg-yanis.prevost
** File description:
** player_interface.c
*/

#include "../rpg.h"
#include "../include/perso.h"
#include "../include/menu.h"
#include "../include/worlds.h"
#include "../include/npc.h"

void dest_p_interface(Global_t *m)
{
    sfSprite_destroy(m->univ.interface.fond_interf);
    sfTexture_destroy(m->univ.interface.Fond_interf);
    sfSprite_destroy(m->univ.interface.cursor);
    sfTexture_destroy(m->univ.interface.Cursor);
    sfClock_destroy(m->univ.interface.curs_clock);
}

void init_player_interface(Global_t *m)
{
    m->univ.interface.fond_interf = sfSprite_create();
    m->univ.interface.Fond_interf = sfTexture_createFromFile("assets/fight/fond_interface.png", NULL);
    m->univ.interface.cursor = sfSprite_create();
    m->univ.interface.Cursor =sfTexture_createFromFile("assets/inv/cursor.png", NULL);
    sfSprite_setTexture(m->univ.interface.fond_interf, m->univ.interface.Fond_interf, sfFalse);
    sfSprite_setTexture(m->univ.interface.cursor, m->univ.interface.Cursor, sfFalse);
    sfSprite_setScale(m->univ.interface.cursor, (sfVector2f){0.2, 0.2});
    m->univ.interface.curs_clock = sfClock_create();
}

void place_interface(Global_t *m)
{
    sfVector2f pose_sp;

    if (m->univ.interface.who == 0)
        pose_sp = sfSprite_getPosition(m->univ.spr_roy);
    if (m->univ.interface.who == 1)
        pose_sp = sfSprite_getPosition(m->univ.spr_infe);
    if (m->univ.interface.who == 2)
        pose_sp = sfSprite_getPosition(m->univ.spr_pate);
    if (m->univ.interface.who == 3)
        pose_sp = sfSprite_getPosition(m->univ.spr_xmara);
    if (m->univ.interface.who == 4)
        pose_sp = sfSprite_getPosition(m->univ.spr_raca);
    pose_sp.x += 50;
    pose_sp.y -= 90;
    sfSprite_setPosition(m->univ.interface.fond_interf, pose_sp);
    sfRenderWindow_drawSprite(m->window, m->univ.interface.fond_interf, NULL);
}

void moove_cursor(Global_t *m)
{

}

void gest_cursor(Global_t *m)
{
    sfVector2f pose_curs;
    static int cursor_position = 0;
    const int max_position = 2;
    const float y_increment = 48.0f;
    const float initial_y = 48.0f;
    sfTime time = sfClock_getElapsedTime(m->univ.interface.curs_clock);
    float elapsed_seconds = sfTime_asSeconds(time);

    pose_curs = sfSprite_getPosition(m->univ.interface.fond_interf);
    pose_curs.x += 18;
    pose_curs.y += initial_y + (cursor_position * y_increment);
    if (elapsed_seconds > 0.2f) {
        if (sfKeyboard_isKeyPressed(sfKeyS)) {
            cursor_position++;
            m->univ.interface.where++;
            if (cursor_position > max_position) {
                cursor_position = 0;
                m->univ.interface.where = 0;
            }
            sfClock_restart(m->univ.interface.curs_clock);
        } else if (sfKeyboard_isKeyPressed(sfKeyZ)) {
            cursor_position--;
            m->univ.interface.where++;
            if (cursor_position < 0) {
                cursor_position = max_position;
            }
            sfClock_restart(m->univ.interface.curs_clock);
        }
    }
    sfSprite_setPosition(m->univ.interface.cursor, pose_curs);
    sfRenderWindow_drawSprite(m->window, m->univ.interface.cursor, NULL);
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        m->univ.interface.select_inteface = false;
        m->perso->case_visble = 0;
    }
}

void draw_player_interface(Global_t *m)
{
    if (m->univ.interface.select_inteface && m->current >= 1 && m->current <= 8) {
        place_interface(m);
        gest_cursor(m);
    }
}
