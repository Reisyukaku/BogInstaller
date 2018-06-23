#include <stdio.h>
#include <malloc.h>
#include <inttypes.h>
#include "types.h"
#include "utils.h"
#include "apps.h"

Result deleteRedunAppRec() {
    Result ret = 0;
    bool b = true;
    
    ret = nsIsAnyApplicationEntityRedundant(&b);
    printf("nsDeleteRedundantApplicationEntity() : "); ResultStr(ret);
    
    if(b) {
        ret = nsDeleteRedundantApplicationEntity();
        printf("nsDeleteRedundantApplicationEntity() : "); ResultStr(ret);
    }else{
        printf("no redundancy found!\n");
    }
    
    return ret;
}

Result pushAppRec() {
    Result ret = 0;
    AppRecord *apprec = calloc(1, sizeof(AppRecord));
    apprec->tid = 0x0100B7D0022EE000;
    apprec->type = 3;
    apprec->unk1 = 2;
    
    printf("Pushing record for hardcoded tid: %" PRIx64 "\n", apprec->tid);
    ret = nsPushApplicationRecord(apprec->tid, 2, apprec);
    printf("nsPushApplicationRecord() : "); ResultStr(ret);
    
    free(apprec);
    
    return ret;
}

Result listAppRec() {
    Result ret = 0;
    
    AppRecord *apprec = calloc(1, sizeof(AppRecord));
    ret = nsListApplicationRecord(apprec, sizeof(AppRecord));
    printf("nsListApplicationRecord() : "); ResultStr(ret);
    printf("TitleID: %" PRIx64 "\n", apprec->tid);
    
    return ret;
}

Result removeAppRec() {
    Result ret = 0;
    u32 cnt=0;
    u64 tid = 0x0100B7D0022EE000;
    
    printf("Deleting record for hardcoded tid: %" PRIx64 "\n", tid);
    ret = nsDeleteApplicationRecord(tid);
    printf("nsDeleteApplicationRecord() : "); ResultStr(ret);
    
    ret = nsGenerateApplicationRecordCount(&cnt);
    printf("nsGenerateApplicationRecordCount() : "); ResultStr(ret);
    printf("cnt=%d\n", cnt);
    
    return ret;
}

Result listApps() {
    Result ret = 0;
    NCMContentStorage out;
    AppContMeta *contmeta = calloc(1,sizeof(AppContMeta));
    ret = ncmOpenContentMetaStorage(FsStorageId_NandUser, &out);
    printf("ncmOpenContentMetaStorage() : "); ResultStr(ret);
    
    ret = ncmListApplication(&out, &contmeta, 1);
    printf("ncmListApplication() : "); ResultStr(ret);
    
    printHex(&contmeta, 0x24);
    free(contmeta);
    return ret;
}