#pragma once

#include <switch.h>

#define MENT_END     0
#define MENT_HANDLER 1
#define MENT_MENU    2
#define MENT_CHOICE  3
#define MENT_BACK    4
#define MENT_CAPTION 5
#define MENT_CHGLINE 6

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

typedef struct _ment_t
{
    u32 type;
    const char *caption;
    u32 color;
    void *data;
    union
    {
        Result(*handler)(void *);
        struct _menu_t *menu;
    };
} ment_t;

typedef struct _menu_t
{
    ment_t *ents;
    const char *caption;
    u32 x;
    u32 y;
} menu_t;

#define MDEF_END() {MENT_END}
#define MDEF_HANDLER(caption, _handler) { MENT_HANDLER, caption, 0, NULL, { .handler = _handler } }
#define MDEF_HANDLER_EX(caption, data, _handler) { MENT_HANDLER, caption, 0, data, { .handler = _handler } }
#define MDEF_MENU(caption, _menu) { MENT_MENU, caption, 0, NULL, { .menu = _menu } }
#define MDEF_BACK() { MENT_BACK, "Back" }
#define MDEF_CAPTION(caption, color) { MENT_CAPTION, caption, color }
#define MDEF_CHGLINE() {MENT_CHGLINE}

void DrawMenu(menu_t *menu);