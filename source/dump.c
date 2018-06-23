#include <stdio.h>
#include <malloc.h>
#include "menu.h"
#include "utils.h"
#include "types.h"
#include "dump.h"

Result dump_xci() {
    printf("\x1b[%dmStubbed feature!\x1b[0m\n", RED);
    return -1;
}

Result dump_nca() {
    FsDeviceOperator devop;
    Result ret = 0;
    
    ret = fsOpenDeviceOperator(&devop);
    printf("fsOpenDeviceOperator() : "); ResultStr(ret);
    
    bool b;
    ret = fsIsGameCardInserted(&devop, &b);
    if(b){
        u32 gc = 0;
        ret = fsGetGameCardHandle(&devop, &gc);
        printf("fsGetGameCardHandle() : "); ResultStr(ret);
        
        FsFileSystem ifs;
        ret = fsMountGameCardFileSystem(&ifs, gc, 2);
        printf("fsMountGameCardFileSystem() : "); ResultStr(ret);
        if(R_SUCCEEDED(ret)) {
            fsdevMountSdmc();
            
            FsDir dir;
            ret = fsFsOpenDirectory(&ifs, "/", 3, &dir);
            printf("fsFsOpenDirectory() : "); ResultStr(ret);
            
            u64 entryCnt = 0;
            ret = fsDirGetEntryCount(&dir, &entryCnt);
            printf("fsDirGetEntryCount() : "); ResultStr(ret);
            printf("Entry count = %" PRId64 "\n", entryCnt);
            
            FsDirectoryEntry *entryBuf = malloc(sizeof(FsDirectoryEntry) * entryCnt);
            ret = fsDirRead(&dir, 0, NULL, entryCnt, entryBuf);
            printf("fsDirRead() : "); ResultStr(ret);
            
            printf("\nListing directory:\n");
            for(int i = 0; i < entryCnt; i++) {
                printf("<%s> %s\n", entryBuf[i].type == 1 ? "file" : "folder", entryBuf[i].name);
            }
            
            printf("\nDumping!\n");
            for(int i = 0; i < entryCnt; i++) {
                if(entryBuf[i].type == 1){
                    printf("%s\n", entryBuf[i].name);
                    FILE *fp;
                    FsFile fs;
                    fp = fopen(entryBuf[i].name, "wb");
                    fsFsOpenFile(&ifs, entryBuf[i].name, FS_OPEN_READ, &fs);
                    size_t size = entryBuf[i].fileSize;
                    u8 *buf;
                    for(int j = 0; j < size / 0x80000; j++) {
                        if(j%16==0) printf("\x1B[33m:\x1B[0m");
                        size_t writeSize = (size > 0x80000 ? 0x80000 : size);
                        buf = calloc(1, writeSize);
                        fsFileRead(&fs, (j*0x80000), buf, writeSize, NULL);
                        fwrite(buf, 1, writeSize, fp);
                        free(buf);
                        hidScanInput();
                        if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B){
                            printf("\x1B[31mCanceled!\x1B[0m\n");
                            break;
                        }
                    }
                    fsFileClose(&fs);
                    fclose(fp);
                    printf("\n\n");
                }
            }
            fsdevUnmountAll();
            free(entryBuf);
            fsDirClose(&dir);
            fsFsClose(&ifs);
        }
        
    } else {
        printf("Card not inserted!\n");
    }
    return ret;
}