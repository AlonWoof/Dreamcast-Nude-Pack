#include "pch.h"
#include "helper-functions.h"
#include "world-location.h"
#include "CustomObjects.h"
#include "shimai.h"
#include "deejay-shower.h"


CustomStageObject customObjects[] =
{
	{-1, {0, 0, 0}, {0,NJM_DEG_ANG(90.0f),0}, NULL, NULL},
	{STAGE_ACT(STAGE_SS_AFT, 4), {-437.797302f, 0.000000f, 1838.036865f}, {0,NJM_DEG_ANG(90.0f),0}, createJenny, NULL },
	{STAGE_ACT(STAGE_SS_AFT, 4), {-381.0f, -10.0f, 1911.0f}, {0,NJM_DEG_ANG(315.0f),0}, createDeeJay, NULL },

	{STAGE_ACT(STAGE_MR, 0), {448.604706f, -33.080769f, 631.368164f}, {0,NJM_DEG_ANG(120.0f),0}, createJenny, NULL },

	{STAGE_ACT(STAGE_EC_ST_AB, 5), {139.954666f, 13.0f, -101.342484f}, {0,NJM_DEG_ANG(90.0f),0}, createJenny, NULL },
	{STAGE_ACT(STAGE_EC_ST_AB, 5), {103.93f, -8.0f, -5.37f}, {0,NJM_DEG_ANG(270.0f),0}, createDeeJay, NULL },

	{STAGE_ACT(STAGE_BEACH, 2), {6112.229980f, -116.5f, 2357.009766f}, {0,NJM_DEG_ANG(150.0f),0}, createDeeJay, NULL },
	{STAGE_ACT(STAGE_BEACH, 2), {6141.962402f, -96.993195f, 2374.986084f}, {0,NJM_DEG_ANG(140.0f),0}, createJenny, NULL },

	{STAGE_ACT(STAGE_CASINO, 0), {-196.404449f, -199.699997f, -530.090515f}, {0,NJM_DEG_ANG(290.0f),0}, createJenny, NULL },
	{STAGE_ACT(STAGE_CASINO, 0), {-171.651657f, -198.890411f, -514.052979f}, {0,NJM_DEG_ANG(110.0f),0}, createDeeJay, NULL },
	{STAGE_ACT(STAGE_CASINO, 0), {-171.6f, -199.1f, -513.92f}, {0, NJM_DEG_ANG(200.0f), 0}, createDeeJayShower, NULL }

};

void checkCustomObjects()
{
	for (CustomStageObject obj : customObjects)
	{

		if (ssStageNumber != GET_STAGE(obj.levelAct) || ssActNumber != GET_ACT(obj.levelAct))
		{
		
			if (obj.instance)
			{
				DestroyTask(obj.instance);
				obj.instance = NULL;
			}

		}
	}
}


void setupAllCustomObjects()
{
	for (CustomStageObject obj : customObjects)
	{
		obj.instance = NULL;
		

		if (ssStageNumber == GET_STAGE(obj.levelAct) && ssActNumber == GET_ACT(obj.levelAct))
		{
			//Create the thingy
			obj.instance = obj.taskFunc();

			if (obj.instance)
			{
				obj.instance->twp->pos = obj.position;
				obj.instance->twp->ang.x = obj.rotation[0];
				obj.instance->twp->ang.y = obj.rotation[1];
				obj.instance->twp->ang.z = obj.rotation[2];
			}
		}
	}

}


