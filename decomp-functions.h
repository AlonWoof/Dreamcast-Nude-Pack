#pragma once
#ifndef _DECOMPFUNCTIONS_H_
#define _DECOMPFUNCTIONS_H_

typedef struct NpcMessageMemory
{
    const char** message_p;
    int flag_index;
} NpcMessageMemory;

FunctionPointer(signed int, NpcMessageStart, (const NpcMessageMemory* data_p), 0x4B7A40);
FunctionPointer(void, InputHookSet, (task* hook_task_p, NJS_POINT3* pos_p, int* ang_y_p, int* status_p, int type, double range), 0x49C920);
FunctionPointer(void, HintRegistStatusPointer, (char* status_p), 0x4B7210);

TaskFunc(ObjectCasinoShowerExec, 0x5CF0F0);
FunctionPointer(Bool, CreateMizu1, (NJS_POINT3* pos, NJS_POINT3* spdofs, Float spd, Float reflecty), 0x005E0670);

#endif