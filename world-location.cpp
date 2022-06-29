
#include "pch.h"
#include "world-location.h"

bool isInLocation(WorldLocation* wl)
{
	if (CurrentLevel == wl->levelID && CurrentAct == wl->act)
	{

		DrawCollisionSphere(&wl->position, wl->range);

		if (IsPlayerInsideSphere(&wl->position, wl->range))
		{
			return true;
		}

	}

	return false;
}