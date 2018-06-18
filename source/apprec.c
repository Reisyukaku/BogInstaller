#include <stdio.h>
#include <malloc.h>
#include "types.h"
#include "utils.h"
#include "apprec.h"

void deleteRedunAppRec() {
    
    u32 ret = 0;
    bool b = true;
    
    ret = nsIsAnyApplicationEntityRedundant(&b);
    printf("nsDeleteRedundantApplicationEntity() : "); ResultStr(ret);
    
    if(b) {
        ret = nsDeleteRedundantApplicationEntity();
        printf("nsDeleteRedundantApplicationEntity() : "); ResultStr(ret);
    }else{
        printf("no redundancy found!\n");
    }
}

void pushAppRec() {
    u32 ret = 0;
    AppRecord *apprec = calloc(1, sizeof(AppRecord));
    apprec->tid = 0x0100B7D0022EE000;
    apprec->type = 3;
    apprec->unk1 = 2;
    
    printf("Pushing record for hardcoded tid: %" PRIx64 "\n", apprec->tid);
    ret = nsPushApplicationRecord(apprec->tid, 2, apprec);
    printf("nsPushApplicationRecord() : "); ResultStr(ret);
    
    free(apprec);
}

void listAppRec() {
    
    AppRecord *apprec = calloc(1, sizeof(AppRecord));
    u32 ret = nsListApplicationRecord(apprec, sizeof(AppRecord));
    printf("nsListApplicationRecord() : "); ResultStr(ret);
    printf("TitleID: %" PRIx64 "\n", apprec->tid);
}

void removeAppRec() {
    u32 cnt=0;
    u64 tid = 0x0100B7D0022EE000;
    
    printf("Deleting record for hardcoded tid: %" PRIx64 "\n", tid);
    u32 ret = nsDeleteApplicationRecord(tid);
    printf("nsDeleteApplicationRecord() : "); ResultStr(ret);
    
    ret = nsGenerateApplicationRecordCount(&cnt);
    printf("nsGenerateApplicationRecordCount() : "); ResultStr(ret);
    printf("cnt=%d\n", cnt);
}