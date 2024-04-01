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


#endif