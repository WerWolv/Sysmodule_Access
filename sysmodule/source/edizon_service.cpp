#include <switch.h>
#include <stratosphere.hpp>
#include "edizon_service.hpp"

Result EdiZonService::dispatch(IpcParsedCommand &r, IpcCommand &out_c, u64 cmd_id, u8 *pointer_buffer, size_t pointer_buffer_size) {
    Result rc = 0xF601;
                
    switch (cmd_id) {
        case 0:
			rc = WrapIpcCommandImpl<&EdiZonService::getTest>(this, r, out_c, pointer_buffer, pointer_buffer_size);
			break;
        default:
            break;
    }
    return rc;
}

std::tuple<Result, u64> EdiZonService::getTest(u64 num) {
	return { 0x00, num * 2 };
}