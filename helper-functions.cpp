
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

float getVectorMagnitude(NJS_VECTOR vec)
{

	// Stores the sum of squares
	  // of coordinates of a vector
	float sum = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;

	// Return the magnitude
	return sqrt(sum);
}

bool isIngame()
{

	if (ssGameMode != MD_GAME_MAIN && ssGameMode != MD_GAME_PAUSE
		&& ssGameMode != MD_GAME_FADEOUT_CHANGE
		&& ssGameMode != MD_GAME_FADEOUT_CHANGE2
		&& ssGameMode != MD_GAME_FADEOUT_CLEAR
		&& ssGameMode != MD_GAME_FADEOUT_MISS
		&& ssGameMode != MD_GAME_FADEOUT_MISS_RESTART
		&& ssGameMode != MD_GAME_FADEOUT_RESTART
		)
		return false;

	if (!playertp[0])
		return false;

	if (!playermwp[0])
		return false;

	if (EV_CheckCansel())
		return false;



	return true;
}

float lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

float clamp(float tg, float min, float max)
{
	if (tg < min)
		return min;

	if (tg > max)
		return max;

	return tg;
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