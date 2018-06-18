#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <switch.h>
#include <inttypes.h>

#include "menu.h"
#include "dump.h"
#include "install.h"
#include "apprec.h"
#include "utils.h"

int main(int argc, char **argv) {
    
    //Dumping tools menu
    ment_t ment_dump[] = {
        MDEF_BACK(),
        MDEF_HANDLER("Dump card CXI", dump_cxi),
        MDEF_HANDLER("Dump card NCAs", dump_nca),
        MDEF_END()
    };

    menu_t menu_dump = {
        ment_dump,
        "Dumping", 0, 0
    };
    
    //Application records menu
    ment_t ment_apprec[] = {
        MDEF_BACK(),
        MDEF_HANDLER("List record", listAppRec),
        MDEF_HANDLER("Push record", pushAppRec),
        MDEF_HANDLER("Remove record", removeAppRec),
        MDEF_HANDLER("Delete redundant records", deleteRedunAppRec),
        MDEF_END()
    };

    menu_t menu_apprec = {
        ment_apprec,
        "Application Records", 0, 0
    };
    
    //Main menu
    ment_t ment_top[] = {
        MDEF_HANDLER("Install", install),
        MDEF_MENU("Dumping Tools", &menu_dump),
        MDEF_MENU("Application records", &menu_apprec),
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
    
    while(appletMainLoop()) {
        DrawMenu(&menu_top);
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    nsExit();
    gfxExit();
    fsExit();
    return 0;
}

