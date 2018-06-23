#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <switch.h>
#include <inttypes.h>

#include "menu.h"
#include "dump.h"
#include "install.h"
#include "apps.h"
#include "utils.h"

int main(int argc, char **argv) {
    
    //Install menu
    ment_t ment_install[] = {
        MDEF_BACK(),
        MDEF_HANDLER("From NSP", installNsp),
        MDEF_HANDLER("From CDN", installShop),
        MDEF_END()
    };

    menu_t menu_install = {
        ment_install,
        "Install Title", 0, 0
    };
    
    //Dumping tools menu
    ment_t ment_dump[] = {
        MDEF_BACK(),
        MDEF_HANDLER("Dump card XCI", dump_xci),
        MDEF_HANDLER("Dump card NCAs", dump_nca),
        MDEF_END()
    };

    menu_t menu_dump = {
        ment_dump,
        "Dumping", 0, 0
    };
    
    //Application records menu
    ment_t ment_app[] = {
        MDEF_BACK(),
        MDEF_HANDLER("List Applications", listApps),
        MDEF_HANDLER("List record", listAppRec),
        MDEF_HANDLER("Push record", pushAppRec),
        MDEF_HANDLER("Remove record", removeAppRec),
        MDEF_HANDLER("Delete redundant records", deleteRedunAppRec),
        MDEF_END()
    };

    menu_t menu_app = {
        ment_app,
        "Applications", 0, 0
    };
    
    //Main menu
    ment_t ment_top[] = {
        MDEF_MENU("Install Title", &menu_install),
        MDEF_MENU("Dumping Tools", &menu_dump),
        MDEF_MENU("Application Tools", &menu_app),
        MDEF_CAPTION("----------", YELLOW),
        MDEF_HANDLER("Quit", NULL),
        MDEF_END()
    };
    
    menu_t menu_top = {
        ment_top,
        "BogInstaller - v0.1", 0, 0
    };
    
    gfxInitDefault();
    consoleInit(NULL);
    nsInitialize();
    fsInitialize();
    ncmInitialize();
    
    while(appletMainLoop()) {
        DrawMenu(&menu_top);
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    nsExit();
    ncmExit();
    gfxExit();
    fsExit();
    return 0;
}