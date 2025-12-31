#pragma once
#ifndef _CUSTOMOBJECTS_H_
#define _CUSTOMOBJECTS_H_

#include <SADXModLoader.h>
#include "world-location.h"

typedef struct CustomStageObject
{
	short levelAct;
	NJS_VECTOR position;
	Angle rotation[3];
	task* (*taskFunc)();
	__int16 flags;
	void* ptr;
};


void setupAllCustomObjects();
void checkCustomObjects();
void setupChaoGardenGirls();

#endif