/*
** EPITECH PROJECT, 2024
** B-MUL-200-MAR-2-1-myrpg-yanis.prevost
** File description:
** main.c
*/
#include "rpg.h"
#include "include/perso.h"
#include "include/menu.h"

void event_click(sfEvent event, Global_t *m)
{
    if (event.type == sfEvtClosed || m->current == -1)
        sfRenderWindow_close(m->window);
    if (m->current == 12)
        inventory(m, event);
    if (m->current == 13)
        event_setting(event, m);
}

void clock(Global_t *m)
{
    sfTime time = sfClock_getElapsedTime(m->clock);
    float seconds;

    seconds = time.microseconds / 1000000.0;
    if (seconds > 0.1) {
        sfClock_restart(m->clock);
    }
}

void rpg(Global_t *m, hub_t *h)
{
    sfEvent event;

    m->show_mouse = true;
    m->mouse = sfMouse_getPositionRenderWindow(m->window);
    sfRenderWindow_clear(m->window, sfBlack);
    while (sfRenderWindow_pollEvent(m->window, &event))
        event_click(event, m);
    draw_menu(m);
    draw_select_perso(m);
    draw_setting(m);
    draw_hub(m, h);
    draw_inventaire(m);
    draw_mouse(m);
    draw_shop(m);
    loading_screen(m);
    sfRenderWindow_display(m->window);
}

int main(int argc, char **argv)
{
    Global_t m = {0};
    hub_t h = {0};
    sfVideoMode mode = {1920, 1080, 32};

    if (argc != 1)
        return 84;
    m.perso->is_visible == false;
    m.window = sfRenderWindow_create(mode, "My Rpg", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(m.window, 60);
    import_weapons_stats(&m);
    setup_stat(&m);
    init_menu(&m);
    init_inventaire(&m);
    init_pose(&m);
    init_loading(&m);
    init_hub(&h, &m);
    init_shop(&m);
    init_select_perso(&m);
    while (sfRenderWindow_isOpen(m.window))
        rpg(&m, &h);
    destroy_hub(&h);
    destroy_inventaire(&m);
    destroy_menu(&m);
    destroy_shop(&m);
    destroy_select_perso(&m);
    destroy_loading(&m);
    sfClock_destroy(m.clock);
    sfSprite_destroy(m.menu.cursor);
    sfRenderWindow_destroy(m.window);
    return 0;
}
