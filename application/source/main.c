#include <string.h>
#include <stdio.h>

#include <switch.h>

static Service g_edizonService;

Result getEdiZon(u64 num, u64 *num_out) {
    IpcCommand c;
    ipcInitialize(&c);
    
    struct {
        u64 magic;
        u64 cmd_id;
        u64 num;
    } *raw;

    raw = ipcPrepareHeader(&c, sizeof(*raw));

    raw->magic = SFCI_MAGIC;
    raw->cmd_id = 0;
    raw->num = num;

    Result rc = serviceIpcDispatch(&g_edizonService);

    if (R_SUCCEEDED(rc)) {
        IpcParsedCommand r;
        ipcParse(&r);

        struct {
            u64 magic;
            u64 result;
			u64 num;
        } *resp = r.Raw;

        rc = resp->result;
		*num_out = resp->num;
    }

    return rc;
}

int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(NULL);
	
	printf("Init\n");
	
	if(R_FAILED(smGetService(&g_edizonService, "edz:tst")))
		printf("Failed getting Service!\n");

    // Main loop
	
	u64 i;
	
	getEdiZon(64, &i);
	printf("%lu\n", i);
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        // Your code goes here

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}

