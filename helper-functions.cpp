
#include "pch.h"

int lastFrame = 0;

float deltaTime = 0.0f;
float totalTime = 0.0f;

void updateTime()
{
	totalTime = (float(FrameCounter) * 0.016666666f);

	deltaTime = ((float)(FrameCounter - lastFrame)) * 0.01666666f;

	lastFrame = FrameCounter;

#ifdef DEBUG
	njPrint(NJM_LOCATION(5, 5), "Delta: %f", deltaTime);
#endif // DEBUG

	
}

float getDeltaTime()
{
	return deltaTime;
}

float clampFloat(float target, float min, float max)
{
	if (target > max)
		return max;

	if (target < min)
		return min;

	return target;
}

float clampFloat01(float target)
{
	return clampFloat(target, 0, 1.0f);
}

void fixPartnerCollisions()
{
	if (!playertwp[0])
		return;

	if (!playertwp[1])
		return;

	if (!playertwp[1]->cwp)
		return;

	char playerCharID = playertwp[0]->counter.b[1];
	char partnerCharID = playertwp[1]->counter.b[1];

	if (playerCharID == Characters_Sonic)
	{
		//if(partnerCharID != Characters_Tails)
		//	playertwp[1]->cwp->info[0].form = 5;
	}
	else
	{
		//playertwp[1]->cwp->info[0].form = 5;
	}
}