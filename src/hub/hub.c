/*
** EPITECH PROJECT, 2024
** B-MUL-200-MAR-2-1-myrpg-yanis.prevost
** File description:
** hub.c
*/
#include "../rpg.h"
#include "../include/perso.h"
#include "../include/menu.h"
#include "../include/worlds.h"

static void init_hub2(Global_t *m, hub_t *h)
{
    char *link_dia_b = "assets/perso/dialogue/dia_board.png";

    m->hub.cadre = sfSprite_create();
    m->hub.Cadre = sfTexture_createFromFile(link_dia_b, NULL);
    m->dialogue.pro_dia = sfText_create();
    m->dialogue = readDialogueFromFile(m, "dialogue/prologue.txt");
    sfSprite_setTexture(m->hub.cadre, m->hub.Cadre, sfFalse);
    sfSprite_setTexture(h->bulle, h->Bulle, sfFalse);
    sfSprite_setScale(h->bulle, (sfVector2f){0.07, 0.07});
    sfSprite_setScale(h->pouilleux, (sfVector2f){0.8, 0.8});
    sfSprite_setTexture(h->pouilleux, h->Pouilleux, sfFalse);
    sfSprite_setTexture(h->sprite_hub, h->texture_hub, sfFalse);
    sfSprite_setTextureRect(h->sprite_perso, h->rect);
    sfSprite_setPosition(h->sprite_perso, (sfVector2f){694, 380});
    sfSprite_setScale(h->sprite_perso, (sfVector2f){0.7, 0.7});
}

void init_hub(hub_t *h, Global_t *m)
{
    char *link_pou = "assets/perso/dialogue/npc/pouilleux.png";
    char *link_bull = "assets/perso/dialogue/bulle.png";

    h->view = sfView_createFromRect((sfFloatRect){0, 0, 1408, 800});
    h->rect = (sfIntRect){0, 512 + 65 * 2, 65, 65};
    h->sprite_perso = sfSprite_create();
    h->texture_hub = sfTexture_createFromFile("maps/map.png", NULL);
    h->sprite_hub = sfSprite_create();
    h->normal_view = sfView_createFromRect((sfFloatRect){0, 0, 1920, 1080});
    h->movement = (sfVector2f){0, 0};
    h->hitbox = sfImage_createFromFile("maps/map_d.png");
    h->pouilleux = sfSprite_create();
    h->Pouilleux = sfTexture_createFromFile(link_pou, NULL);
    h->bulle = sfSprite_create();
    h->Bulle = sfTexture_createFromFile(link_bull, NULL);
    init_hub2(m, h);
}

void vision(Global_t *m, hub_t *h)
{
    if (m->perso->is_visible) {
        if (get_size(h->view).x < 1920 || get_size(h->view).y < 1080)
            sfView_zoom(h->view, 1.05f);
        sfRenderWindow_setView(m->window, h->normal_view);
    }
    if (!m->perso->is_visible) {
        if (get_size(h->view).x > 860 || get_size(h->view).y > 800)
            sfView_zoom(h->view, 0.95f);
        sfRenderWindow_setView(m->window, h->view);
    }
}

void draw_hub(Global_t *m, hub_t *h)
{
    char *perso = NULL;

    if (m->current == 12) { /* temporaire normalement m->current == 0*/
        perso = m->perso[m->perso->current_perso].texture_battle;
        vision(m, h);
        if (h->texture_perso != NULL) {
            sfTexture_destroy(h->texture_perso);
            h->texture_perso = NULL;
        }
        h->texture_perso = sfTexture_createFromFile(perso, NULL);
        sfSprite_setTexture(h->sprite_perso, h->texture_perso, sfTrue);
        sfRenderWindow_drawSprite(m->window, h->sprite_hub, NULL);
        if (!m->perso->is_visible)
            movecharacter(m, h);
        h->pos_sprite = sfSprite_getPosition(h->sprite_perso);
        h->color = sfImage_getPixel(h->hitbox, (h->pos_sprite.x +
        h->movement.x + 20), (h->pos_sprite.y + h->movement.y + 37));
    }
}

void destroy_hub(hub_t *h)
{
    sfImage_destroy(h->hitbox);
    sfSprite_destroy(h->sprite_hub);
    sfSprite_destroy(h->sprite_perso);
    sfTexture_destroy(h->texture_hub);
    sfTexture_destroy(h->texture_perso);
    sfSprite_destroy(h->pouilleux);
    sfTexture_destroy(h->Pouilleux);
    sfSprite_destroy(h->bulle);
    sfTexture_destroy(h->Bulle);
}
