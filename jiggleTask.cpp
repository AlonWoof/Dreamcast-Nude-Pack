#include <SADXModLoader.h>
#include "pch.h"
#include "body-functions.h"
#include "helper-functions.h"

NJS_POINT3* copyPointsData(NJS_MODEL_SADX* model)
{
	NJS_POINT3* newArray = new NJS_POINT3[model->nbPoint];
	memcpy(newArray, model->points, sizeof(NJS_POINT3) * model->nbPoint);
	return newArray;
}

void jiggleAnimation(task* tp)
{
	NJS_MODEL_SADX* target = (NJS_MODEL_SADX*)tp->awp->work.ptr[2];
	JiggleWeightInfo* jiggleInfo = (JiggleWeightInfo*)tp->awp->work.ptr[3];
	NJS_POINT3* originalPoints = (NJS_POINT3*)tp->awp->work.ptr[4];
	int infoSize = tp->awp->work.sl[1];


	motionwk2* pmwp = playermwp[0];

	double realTime = (((double)FrameCounter) * 0.0166666f);

	float mag = clampFloat(getVectorMagnitude(tp->mwp->acc), 0.0f, 0.999f);


	float fac_x = sin(realTime * 12);
	float fac_y = sin(realTime * 10);

	fac_x *= 0.15f;
	fac_x *= mag;


	fac_y *= 0.05f;
	fac_y *= mag;

	float limit = 0.02f;

	fac_x = clampFloat(fac_x, -limit, limit);
	fac_y = clampFloat(fac_y, -limit, limit);

	njPrint(NJM_LOCATION(32, 32), "fac x: %f", fac_x);
	njPrint(NJM_LOCATION(32, 33), "fac y: %f", fac_y);

	for (int i = 0; i < target->nbPoint; i++)
	{

		for (int b = 0; b < infoSize; b++)
		{
			if (jiggleInfo[b].vert_number == i)
			{

				float fac2 = jiggleInfo[b].vert_weight;

				target->points[i].x = (originalPoints)[i].x + (fac2 * fac_x) * -(tp->mwp->acc.x);
				target->points[i].y = (originalPoints)[i].y + (fac2 * fac_y) * -(tp->mwp->acc.y);
				target->points[i].z = (originalPoints)[i].z + (fac2 * fac_x) * -(tp->mwp->acc.z);

				//PrintDebug("\n VERT WEIGHT %i: %f", i, (float)tailsBalls[b].vert_weight);
			}
		}
	}
}


void PlayerJiggleProc(task* tp)
{
	NJS_MODEL_SADX* model = (NJS_MODEL_SADX*)tp->awp->work.ptr[2];
	JiggleWeightInfo* jiggleInfo = (JiggleWeightInfo*)tp->awp->work.ptr[3];
	NJS_POINT3* originalPoints = (NJS_POINT3*)tp->awp->work.ptr[4];

	//motionwk* pmwp = ((task*)tp->awp->work.ptr[1])->mwp;

	int pno = tp->twp->mode;

	if (!playermwp[pno])
		return;

	if (!playerpwp[pno])
		return;

	motionwk2* pmwp = playermwp[0];


	//DisplayDebugStringFormatted(NJM_LOCATION(12, 12), "playermwp accel x: %f y: %f z: %f", playerpwp[0]->spd.x, playerpwp[0]->spd.y, playerpwp[0]->spd.z);
	//DisplayDebugStringFormatted(NJM_LOCATION(12, 13), "my accel x: %f y: %f z: %f", tp->mwp->acc.x, tp->mwp->acc.y, tp->mwp->acc.z);

	float lerpFac = 0.02f;

	if (getVectorMagnitude(pmwp->spd) > 0.1f)
	{
		tp->mwp->acc.x = playerpwp[0]->spd.x * 3;
		tp->mwp->acc.y = playermwp[0]->spd.y * 1;
		tp->mwp->acc.z = playerpwp[0]->spd.z * 3;
	}

	//TEST
	tp->mwp->acc.x = lerp(tp->mwp->acc.x, 0, lerpFac * 0.5f);
	tp->mwp->acc.y = lerp(tp->mwp->acc.y, 0, lerpFac * 0.5f);
	tp->mwp->acc.z = lerp(tp->mwp->acc.z, 0, lerpFac * 0.5f);

	//TES2
	//tp->mwp->acc.x = 1.0f;

	//AnimateJigglesFORCED(model, &tp->mwp->acc, originalPoints);

	jiggleAnimation(tp);
}