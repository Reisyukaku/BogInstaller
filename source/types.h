#include <inttypes.h>
#include <switch.h>

typedef struct{
	u64 tid;
	u8 type;
	u8 unk1;
	u8 zeroes[6];
	u8 unk2;
	u8 zeroes2[7];
} AppRecord;