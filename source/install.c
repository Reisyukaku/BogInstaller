#include <stdio.h>
#include "types.h"
#include "install.h"

void install() {
	u64 tid = 0x0100B7D0022EE000;
	
	printf("Installing hardcoded tid: %" PRIx64 "\n", tid);
	u32 ret = nsBeginInstallApplication(tid, 0, FsStorageId_SdCard);
	printf("nsBeginInstallApplication() : "); ResultStr(ret);
}