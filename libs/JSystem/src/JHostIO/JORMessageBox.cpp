// Debug-only file. This file is known to have existed for TWW based on the debug maps.
// The contents of this are based on the TP debug build decomp and may or may not match the actual TWW debug build.

#include "JSystem/JSystem.h" // IWYU pragma: keep

#include "JSystem/JHostIO/JORServer.h"

u32 JORMessageBox(const char* message, const char* title, u32 style) {
    u32 status = 0;
    JORMContext* mctx = JORServer::getInstance()->attachMCTX(MCTX_MSG_OPEN_MESSAGE_BOX);
    mctx->openMessageBox(&status, style, message, title);
    JORServer::getInstance()->releaseMCTX(mctx);

    while (status == 0) {
        JOR_MESSAGELOOP();
    }

    return status;
}
