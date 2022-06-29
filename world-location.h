#pragma once

#include <SADXModLoader.h>

typedef struct
{
	LevelIDs levelID;
	int act;
	NJS_VECTOR position;
	float range;

} WorldLocation;

bool isInLocation(WorldLocation* wl);
