
#include "pch.h"
#include <ctime>

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

Float njDistanceP2P(NJS_POINT3* p1, NJS_POINT3* p2)
{
	Float y = p1->y - p2->y;
	Float x = p1->x - p2->x;
	Float z = p1->z - p2->z;
	return njSqrt(x * x + y * y + z * z);
}


float getVectorMagnitude(NJS_VECTOR vec)
{

	// Stores the sum of squares
	  // of coordinates of a vector
	float sum = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;

	// Return the magnitude
	return sqrt(sum);
}

NJS_VECTOR getPlayerSidePos(taskwk* twp, double dist, int angle_offset)
{
	double sin; // fp30

	NJS_VECTOR pos;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	if (twp)
	{
		sin = njSin(twp->ang.y + angle_offset);
		pos.x = -(float)((float)((float)njCos(twp->ang.y + angle_offset) * (float)dist) - twp->pos.x);
		pos.y = twp->pos.y;
		pos.z = -(float)((float)((float)sin * (float)dist) - twp->pos.z);
	}

	return pos;
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

NJS_VECTOR lerpVector(NJS_VECTOR a, NJS_VECTOR b, float f)
{
	NJS_VECTOR ret;

	ret.x = lerp(a.x, b.x, f);
	ret.y = lerp(a.y, b.y, f);
	ret.z = lerp(a.z, b.z, f);

	return ret;
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

float remapRange(float from, float fromMin, float fromMax, float toMin, float toMax)
{
	float fromAbs = from - fromMin;
	float fromMaxAbs = fromMax - fromMin;

	float normal = fromAbs / fromMaxAbs;

	float toMaxAbs = toMax - toMin;
	float toAbs = toMaxAbs * normal;

	float to = toAbs + toMin;

	return to;
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

int random(int min, int max) 
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int getTimeSeconds()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	return newtime.tm_sec;
}

int getDayOfWeek()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int wday = newtime.tm_wday;
	return wday;
}

bool getFinalEggVisible()
{
	int result; // eax

	switch (GetPlayerNumber())
	{
	case Characters_Sonic:
		result = seqVars[FLAG_SONIC_MR_APPEAR_FINALEGG];
		break;
	case Characters_Knuckles:
		result = seqVars[FLAG_KNUCKLES_MR_APPEAR_FINALEGG];
		break;
	case Characters_Amy:
		result = seqVars[FLAG_AMY_MR_APPEAR_FINALEGG];
		break;
	case Characters_Gamma:
		result = seqVars[FLAG_E102_MR_APPEAR_FINALEGG];
		break;
	default:
		result = 0;
		break;
	}

	return result;
}
