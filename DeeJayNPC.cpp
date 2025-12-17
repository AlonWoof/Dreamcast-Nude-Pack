#include <SADXModLoader.h>
#include "pch.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include "world-location.h"

#include "LoadModel.h"

extern const HelperFunctions* helperFunctionsGlobal;

CCL_INFO colli_info_DJ[3] =
{
	{ 0, CI_FORM_PERSON, CI_PUSH_PO_CMN | CI_PUSH_TH_CMN, 0, 0, { 0.0f, 1.0f, 0.0f}, 4.0f, 4.0f, 0.65f, 0.0f, 0, 0, 0 },
};

NJS_OBJECT* DeeJayObject;
WeightInfo* DeeJayWeights;
//extern NJS_OBJECT DeeJay_Shadow;

NJS_TEXNAME DeeJayTexName[8];
NJS_TEXLIST DeeJayTexlist = { arrayptrandlengthT(DeeJayTexName, unsigned int) };

NJS_MOTION* motion_DeeJay_idle;
NJS_ACTION action_DeeJay_idle;

#define DJ_FRAME(tp) tp->awp->work.f[0]

enum
{
	DEEJAY_MD_INIT,
	DEEJAY_MD_IDLE
};

void LoadDeeJayFiles()
{
	LoadPVM("DEEJAY", &DeeJayTexlist);

	DeeJayObject = LoadModel("system\\DeeJay.sa1mdl", DeeJayWeights);
	helperFunctionsGlobal->Weights->Init(DeeJayWeights, DeeJayObject);

	motion_DeeJay_idle = LoadAnimation("system\\deejay_idle.saanim");
	action_DeeJay_idle.object = DeeJayObject;
	action_DeeJay_idle.motion = motion_DeeJay_idle;

}
/*
void drawDeeJayShadow(task* tp)
{
	taskwk* twp = tp->twp;

	NJS_POINT3 a2;
	Angle3 a4;

	float y_off = twp->pos.y + 0.5f;

	float v6 = GetShadowPos(twp->pos.x, y_off, twp->pos.z, &a4) + 0.2f;
	if (v6 < y_off)
	{
		a2.y = v6;
		float v7 = y_off - v6;
		float v8 = twp->pos.z;
		a2.x = twp->pos.x;
		a2.z = v8;
		float thisa = 0.58f / (fabs(v7 + 1.0) * 0.05 + 1.0);
		njSetTexture(&DeeJayTexlist);
		njPushMatrix(0);
		njTranslateV(0, &a2);
		if (a4.z)
		{
			njRotateZ(0, LOWORD(a4.z));
		}
		if (a4.x)
		{
			njRotateX(0, LOWORD(a4.x));
		}
		njScale(0, thisa, thisa, thisa);
		ProcessModelNode_A_WrapperC(&DeeJay_Shadow, thisa);
		njPopMatrix(1u);
	}
}
*/

void DeeJayInit(task* tp)
{
	LoadDeeJayFiles();
	CCL_Init(tp, colli_info_DJ, 1, CID_OBJECT);

}

void DeeJayDisp(task* tp)
{
	taskwk* twp = tp->twp;

	if (!loop_count)
	{
		ResetMaterial();
		njSetTexture(&DeeJayTexlist);
		___dsSetPalette(2);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		//ROTATEZ(0, twp->ang.z);
		//ROTATEX(0, twp->ang.x);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(270.0f));

		njScale(0, 1.0f, 1.0f, 1.0f);

		helperFunctionsGlobal->Weights->Apply(DeeJayWeights, &action_DeeJay_idle, DJ_FRAME(tp));
		dsDrawMotion(DeeJayObject, action_DeeJay_idle.motion, DJ_FRAME(tp));
		//dsDrawObject(JennyObject);

		njPopMatrix(1u);
		___dsSetPalette(0);
		//drawDeeJayShadow(tp);
	}

}

void DeeJayNPC(task* tp)
{
	switch (tp->twp->mode)
	{
	case DEEJAY_MD_INIT:
		DeeJayInit(tp);
		tp->twp->mode++;
		return;

	case DEEJAY_MD_IDLE:
		//changeJennyAction(tp,&action_Jenny_idle);
		break;

	}

	DJ_FRAME(tp) += 0.5f;

	if (DJ_FRAME(tp) > action_DeeJay_idle.motion->nbFrame)
		DJ_FRAME(tp) = 0.0f;

	DeeJayDisp(tp);
	EntryColliList(tp->twp);
}

task* CreateDeeJayNPC()
{

	//return NULL;

	task* dj = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, DeeJayNPC);

	dj->exec = DeeJayNPC;
	dj->disp = DeeJayDisp;
	//jenny->dest = DeeJayDestructor;

	return dj;
}