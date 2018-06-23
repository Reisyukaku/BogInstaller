#include <stdio.h>
#include "menu.h"

int idx = 0, cnt = 0;
int prev_idx = 0;

void waitOnKey(u32 key) {
    while(!(hidKeysDown(CONTROLLER_P1_AUTO) & key)) hidScanInput();
}

void updateMenu(menu_t *menu) {
    // Draw the menu
    printf("\x1b[%dm\x1b[%d;%dH[%s]\n\n\x1b[0m", CYAN, menu->x, menu->y, menu->caption);
    for (cnt = 0; menu->ents[cnt].type != MENT_END; cnt++) {
        switch(menu->ents[cnt].type){
            case MENT_CAPTION:
                printf("\x1b[%dm %s\x1b[0m\n", menu->ents[cnt].color, menu->ents[cnt].caption);
                break;
            default:
                printf("\x1b[%dm %s\x1b[0m\n", cnt == idx ? GREEN : WHITE, menu->ents[cnt].caption);
                break;
        }
        printf(" \n");
    }
    printf("\n");

    // Skip caption or seperator lines selection
    while (menu->ents[idx].type == MENT_CAPTION || menu->ents[idx].type == MENT_CHGLINE) {
        if (prev_idx <= idx || (!idx && prev_idx == cnt - 1)) {             
            idx++;
            if (idx > (cnt - 1)) {
                idx = 0;
                prev_idx = 0;
            }
        } else {
            idx--;
            if (idx < 0) {
                idx = cnt - 1;
                prev_idx = cnt;
            }
        }
    }
    prev_idx = idx;
}

u64 waitForKey() {
    u64 prevKey = hidKeysDown(CONTROLLER_P1_AUTO), currKey = 0;
    while((currKey = hidKeysDown(CONTROLLER_P1_AUTO)) == prevKey) hidScanInput();
    return currKey;
}

void DrawMenu(menu_t *menu) {
    consoleClear();
    
    while(1){
        updateMenu(menu);

        u64 kDown = waitForKey();

        if (kDown & KEY_DDOWN && idx < (cnt - 1))
            idx++;
        else if (kDown & KEY_DDOWN && idx == (cnt - 1))
            idx = 0;
        if (kDown & KEY_DUP && idx > 0)
            idx--;
        else if (kDown & KEY_DUP && idx == 0)
            idx = cnt - 1;
        if (kDown & KEY_A)
        {
            ment_t *ent = &menu->ents[idx];
            idx = 0;
            switch (ent->type)
            {
            case MENT_HANDLER:{
                Result res = ent->handler(ent->data);
                if(res == 0) printf("\n\x1b[%dmDone!\x1b[0m\n", GREEN);
                else printf("\n\x1b[%dmError: %d\x1b[0m\n", RED, res);
                waitOnKey(KEY_B);
                break;
            }
            case MENT_MENU:
                return DrawMenu(ent->menu);
                break;
            case MENT_CHOICE:
                return ent->data;
                break;
            case MENT_BACK:
                return;
                break;
            default:
                break;
            }
            consoleClear();
        }
        if (kDown & KEY_B) return;
    }
}
