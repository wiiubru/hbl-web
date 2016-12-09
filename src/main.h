//A better name would be everything.h

#define OSDynLoad_Acquire ((void (*)(char* rpl, unsigned int *handle))0x0102A3B4)
#define OSDynLoad_FindExport ((void (*)(unsigned int handle, int isdata, char *symbol, void *address))0x0102B828)
#define OSFatal ((void (*)(char* msg))0x01031618)
#define __os_snprintf ((int(*)(char* s, int n, const char * format, ... ))0x0102F160)

void InitLibs();

#define AF_INET		2
#define SOCK_STREAM	1
#define IPPROTO_TCP	6

typedef struct {
    unsigned int s_addr;
} in_addr;

typedef struct {
    unsigned short sin_family;
    unsigned short sin_port;
    in_addr sin_addr;
    char sin_zero[8];
} sockaddr_in;

typedef struct _GlobalVariables {
	void (*_Exit)();
	
	void* (*memset)(void* dest, unsigned int value, unsigned int bytes);
	void* (*OSAllocFromSystem)(unsigned int size, int align);
	void (*OSFreeToSystem)(void* ptr);
	
	int (*IM_Open)();
	int (*IM_Close)(int fd);
	int (*IM_SetDeviceState)(int fd, void* mem, int state, int a, int b);
	
	int (*ACInitialize)(void);
	int (*ACGetStartupId)(unsigned int* id);
	int (*ACConnectWithConfigId)(unsigned int id);
	int (*socket_lib_init)(void);
	int (*curl_global_init)(int opts);
	void* (*curl_easy_init)(void);
	void (*curl_easy_cleanup)(void* handle);

	void (*OSScreenInit)();
	unsigned int (*OSScreenGetBufferSizeEx)(int buffer);
	void (*OSScreenSetBufferEx)(int buffer, void* addr);
	void (*OSScreenPutFontEx)(int buffer, int x, int y, char* text);
	void (*OSScreenFlipBuffersEx)(int buffer);
	void (*OSScreenClearBufferEx)(int buffer, unsigned int colour);

	void (*DCFlushRange)(void* addr, int len);
} GlobalVariables;

#define GLOBAL_VARIABLES ((GlobalVariables*)0xE0001000)
