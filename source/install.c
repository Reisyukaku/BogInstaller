#include <stdio.h>
#include "types.h"
#include "install.h"

Result installShop() {
    Result ret = 0;
	u64 tid = 0x0100B7D0022EE000;
	
	printf("Installing hardcoded tid: %" PRIx64 "\n", tid);
	ret = nsBeginInstallApplication(tid, 0, FsStorageId_SdCard);
	printf("nsBeginInstallApplication() : "); ResultStr(ret);
    
    return ret;
}

Result installNsp() {
    //TODO
    return 0;
}