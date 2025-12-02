#pragma once
#ifndef _AMY_SHOWER_H_
#define _AMY_SHOWER_H_

#include <SADXModLoader.h>

extern NJS_MOTION amy_shower_start;
extern NJS_MOTION amy_shower_loop;
extern NJS_MOTION amy_shower_end;

extern NJS_ACTION action_amy_shower_start;
extern NJS_ACTION action_amy_shower_loop;
extern NJS_ACTION action_amy_shower_end;

void checkIfShowerTime(int pnum);

#endif // !_AMY_SHOWER_H_
