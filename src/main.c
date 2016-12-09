#include "main.h"

void _start() {
	asm(
		"lis %r1, 0x1ab5 ;"
 		"ori %r1, %r1, 0xd138 ;"
	);
	
	InitLibs();
	
	int fd = GLOBAL_VARIABLES->IM_Open();
	void* mem = GLOBAL_VARIABLES->OSAllocFromSystem(0x100, 64);
	GLOBAL_VARIABLES->memset(mem, 0, 0x100);
	GLOBAL_VARIABLES->IM_SetDeviceState(fd, mem, 3, 0, 0);
	GLOBAL_VARIABLES->IM_Close(fd);
	GLOBAL_VARIABLES->OSFreeToSystem(mem);
	
	unsigned int t1 = 0x1FFFFFFF;
	while(t1--) ;
	
	GLOBAL_VARIABLES->ACInitialize();
	unsigned int ac_startup_id;
	GLOBAL_VARIABLES->ACGetStartupId(&ac_startup_id);
	GLOBAL_VARIABLES->ACConnectWithConfigId(ac_startup_id);
	
	GLOBAL_VARIABLES->OSScreenInit();
	
	int buf0 = GLOBAL_VARIABLES->OSScreenGetBufferSizeEx(0);
	int buf1 = GLOBAL_VARIABLES->OSScreenGetBufferSizeEx(1);
	
	GLOBAL_VARIABLES->OSScreenSetBufferEx(0, (void*)0xF4000000);
	GLOBAL_VARIABLES->OSScreenSetBufferEx(1, (void*)0xF4000000 + buf0);
	
	GLOBAL_VARIABLES->OSScreenPutFontEx(0, 0, 0, "hello");
	GLOBAL_VARIABLES->OSScreenPutFontEx(1, 0, 0, "hello");
	
	GLOBAL_VARIABLES->DCFlushRange((void*)0xF4000000, buf0 + buf1);

	GLOBAL_VARIABLES->OSScreenFlipBuffersEx(0);
	GLOBAL_VARIABLES->OSScreenFlipBuffersEx(1);
	
	
	
	t1 = 0x1FFFFFFF;
	while(t1--) ;
	GLOBAL_VARIABLES->_Exit();
}

void InitLibs() {
	unsigned int coreinit_handle, nn_ac_handle, nsysnet_handle;
	OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);
	OSDynLoad_Acquire("nn_ac.rpl", &nn_ac_handle);
	OSDynLoad_Acquire("nsysnet.rpl", &nsysnet_handle);
	
	OSDynLoad_FindExport(coreinit_handle, 0, "IM_Open", &(GLOBAL_VARIABLES->IM_Open));
	OSDynLoad_FindExport(coreinit_handle, 0, "IM_Close", &(GLOBAL_VARIABLES->IM_Close));
	OSDynLoad_FindExport(coreinit_handle, 0, "IM_SetDeviceState", &(GLOBAL_VARIABLES->IM_SetDeviceState));
	OSDynLoad_FindExport(coreinit_handle, 0, "_Exit", &(GLOBAL_VARIABLES->_Exit));
	OSDynLoad_FindExport(coreinit_handle, 0, "OSAllocFromSystem", &(GLOBAL_VARIABLES->OSAllocFromSystem));
	OSDynLoad_FindExport(coreinit_handle, 0, "OSFreeToSystem", &(GLOBAL_VARIABLES->OSFreeToSystem));
	OSDynLoad_FindExport(coreinit_handle, 0, "memset", &(GLOBAL_VARIABLES->memset));
	
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenInit", &(GLOBAL_VARIABLES->OSScreenInit));
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenGetBufferSizeEx", &(GLOBAL_VARIABLES->OSScreenGetBufferSizeEx));
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenSetBufferEx", &(GLOBAL_VARIABLES->OSScreenSetBufferEx));
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenPutFontEx", &(GLOBAL_VARIABLES->OSScreenPutFontEx));
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenFlipBuffersEx", &(GLOBAL_VARIABLES->OSScreenFlipBuffersEx));
	
	OSDynLoad_FindExport(coreinit_handle, 0, "DCFlushRange", &(GLOBAL_VARIABLES->DCFlushRange));
	
	OSDynLoad_FindExport(nn_ac_handle, 0, "ACInitialize", &(GLOBAL_VARIABLES->ACInitialize));
	OSDynLoad_FindExport(nn_ac_handle, 0, "ACConnectWithConfigId", &(GLOBAL_VARIABLES->ACConnectWithConfigId));
	OSDynLoad_FindExport(nn_ac_handle, 0, "ACGetStartupId", &(GLOBAL_VARIABLES->ACGetStartupId));
	
	OSDynLoad_FindExport(nsysnet_handle, 0, "socket_lib_init", &(GLOBAL_VARIABLES->socket_lib_init));
}
