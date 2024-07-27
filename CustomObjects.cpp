#include "pch.h"
#include "helper-functions.h"
#include "world-location.h"
#include "CustomObjects.h"
#include "JennyNPC.h"


CustomStageObject customObjects[] =
{
	{STAGE_ACT(STAGE_SS_AFT, 4), {-437.797302f, 0.000000f, 1838.036865f}, {0,NJM_DEG_ANG(90.0f),0}, CreateJennyNPC, NULL}
};



void setupAllCustomObjects()
{
	for (CustomStageObject obj : customObjects)
	{
		obj.instance = NULL;
		
		if (ssStageNumber == GET_STAGE(obj.levelAct))
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

void deleteAllCustomObjects()
{
	for (CustomStageObject obj : customObjects)
	{
		if (obj.instance)
		{
			DestroyTask(obj.instance);
			obj.instance = NULL;
		}
	}
}
