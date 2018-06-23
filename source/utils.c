#include "utils.h"

void ResultStr(int code) {
    switch(code){
        case 0:
            printf("\x1B[32mOk!\n\x1B[0m");
            break;
        default:
            printf("\x1B[31m0x%04X\n\x1B[0m", code);
    }
}

void printHex(u8 *buf, u32 size) {
    for(u32 i=0;i<size;i++){
        printf("%02X ", buf[i]);
        if(i != 0 && (i % 0x10 == 0xF))
            printf("\n");
    }
    printf("\n");
}