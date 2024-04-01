
#include <SADXModLoader.h>
#include "pch.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include "world-location.h"

#include "LoadModel.h"



CCL_INFO colli_info_9[3] =
{
	{ 0, CI_FORM_PERSON, CI_PUSH_PO_CMN | CI_PUSH_TH_CMN, 0, 0, { 0.0f, 1.0f, 0.0f}, 4.0f, 4.0f, 0.65f, 0.0f, 0, 0, 0 },
};

extern const HelperFunctions* helperFunctionsGlobal;


NJS_OBJECT* JennyObject;
WeightInfo* JennyWeights;
extern NJS_OBJECT Jenny_Shadow;

NJS_TEXNAME JennyTexName[10];
NJS_TEXLIST JennyTexlist = { arrayptrandlengthT(JennyTexName, unsigned int) };

NJS_MOTION* motion_Jenny_idle;
NJS_MOTION* motion_Jenny_walk;
NJS_MOTION* motion_Jenny_talk;

NJS_ACTION action_Jenny_idle;
NJS_ACTION action_Jenny_walk;
NJS_ACTION action_Jenny_talk;

NpcMessageMemory jennyNPCMessageBuffer;
extern const char*** msg_Character[];

enum
{
	JENNY_MD_INIT,
	JENNY_MD_IDLE,
	JENNY_MD_WALK,
	JENNY_MD_TALK
};

struct JennyNPCWork
{
	float animSpd;
	NJS_ACTION* lastAction;
	NJS_ACTION* currAction;
	NJS_ACTION* nextAction;

	float lastAnimFrame;
	float currAnimFrame;
	float blendRatio;

	int msgCounter;
};


void LoadJennyFiles()
{
	LoadPVM("JENNY", &JennyTexlist);

	JennyObject = LoadModel("system\\Jenny.sa1mdl", JennyWeights);
	helperFunctionsGlobal->Weights->Init(JennyWeights, JennyObject);

	motion_Jenny_idle = LoadAnimation("system\\jenny_idle.saanim");
	action_Jenny_idle.object = JennyObject;
	action_Jenny_idle.motion = motion_Jenny_idle;

	motion_Jenny_walk = LoadAnimation("system\\jenny_walk.saanim");
	action_Jenny_walk.object = JennyObject;
	action_Jenny_walk.motion = motion_Jenny_walk;

	motion_Jenny_talk = LoadAnimation("system\\jenny_talk.saanim");
	action_Jenny_talk.object = JennyObject;
	action_Jenny_talk.motion = motion_Jenny_talk;
}

void changeJennyAction(task* tp, NJS_ACTION* newAction)
{
	JennyNPCWork* jennywk = ((JennyNPCWork*)tp->awp->work.ptr[0]);

	jennywk->lastAction = jennywk->currAction;
	jennywk->currAction = newAction;
}

void JennyInit(task* tp)
{
	LoadJennyFiles();
	CCL_Init(tp, colli_info_9, 1, CID_OBJECT);
	tp->awp->work.ptr[0] = new JennyNPCWork;

	JennyNPCWork* jennywk = ((JennyNPCWork*)tp->awp->work.ptr[0]);

	jennywk->currAction = &action_Jenny_idle;
	jennywk->animSpd = 0.5f;
	jennywk->currAnimFrame = 0.0f;
	jennywk->lastAnimFrame = 0.0f;
	jennywk->msgCounter = 0;

	changeJennyAction(tp, &action_Jenny_idle);

}

void drawJennyShadow(task* tp)
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
		njSetTexture(&JennyTexlist);
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
		ProcessModelNode_A_WrapperC(&Jenny_Shadow, thisa);
		njPopMatrix(1u);
	}
}

void JennyDisp(task* tp)
{
	taskwk* twp = tp->twp;
	JennyNPCWork* jennywk = ((JennyNPCWork*)tp->awp->work.ptr[0]);

	if (!loop_count)
	{
		//ResetMaterial();
		njSetTexture(&JennyTexlist);
		___dsSetPalette(2);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		ROTATEZ(0, twp->ang.z);
		ROTATEX(0, twp->ang.x);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(270.0f));

		njScale(0, 1.0f, 1.0f, 1.0f);

		helperFunctionsGlobal->Weights->Apply(JennyWeights, jennywk->currAction, jennywk->currAnimFrame);
		dsDrawMotion(JennyObject, jennywk->currAction->motion, jennywk->currAnimFrame);

		njPopMatrix(1u);
		___dsSetPalette(0);
		drawJennyShadow(tp);
	}
}

void startNPCMessage(const char** msg)
{
	jennyNPCMessageBuffer.message_p = msg;
	jennyNPCMessageBuffer.flag_index = 0;

	NpcMessageStart(&jennyNPCMessageBuffer);
}

bool checkPlayerInteract(task* tp)
{
	JennyNPCWork* jennywk = ((JennyNPCWork*)tp->awp->work.ptr[0]);
	float dst = njDistanceP2P(&tp->twp->pos, &playertwp[0]->pos);

	if (dst < 10)
	{

		if (perG[0].press & Buttons_B)
		{
			//SetInputP(0, PL_OP_PLACEON);

			startNPCMessage(msg_Character[PLNO(playertwp[0])][jennywk->msgCounter]);

			if (!jennywk->msgCounter)
				jennywk->msgCounter++;


			return true;
		}
	}

	return false;
}

bool waitPlayerCloseMsg(task* tp)
{
	if (perG[0].press & Buttons_B)
	{
		//SetInputP(0, PL_OP_LETITGO);
		//EV_MsgClose();
		//return true;
	}

	return false;
}

void JennyDestructor(task* tp)
{
	JennyNPCWork* jennywk = ((JennyNPCWork*)tp->awp->work.ptr[0]);
	free(jennywk);
}

void checkJennyMode(task* tp)
{
	if (!isIngame())
		return;

	switch (tp->twp->mode)
	{
	case JENNY_MD_IDLE:
		if (checkPlayerInteract(tp))
		{
			tp->twp->mode = JENNY_MD_TALK;
			changeJennyAction(tp, &action_Jenny_talk);
			InputHookSet(tp, &tp->twp->pos, &tp->twp->ang.y, 0, 0, 10.0f);
		}
		return;
	case JENNY_MD_WALK:
		return;
	case JENNY_MD_TALK:
		if (waitPlayerCloseMsg(tp))
		{
			tp->twp->mode = JENNY_MD_IDLE;
			changeJennyAction(tp, &action_Jenny_idle);
		}

		return;
	}
}


void JennyNPC(task* tp)
{


	switch (tp->twp->mode)
	{
	case JENNY_MD_INIT:
		JennyInit(tp);
		tp->twp->mode++;
		return;

	case JENNY_MD_IDLE:
		//changeJennyAction(tp,&action_Jenny_idle);

		break;

	case JENNY_MD_WALK:
		//changeJennyAction(tp, &action_Jenny_walk);
		break;

	case JENNY_MD_TALK:
		//changeJennyAction(tp, &action_Jenny_talk);
		break;
	}

	checkJennyMode(tp);

	JennyNPCWork* jennywk = ((JennyNPCWork*)tp->awp->work.ptr[0]);

	float animSpd = jennywk->animSpd;

	if (EV_CheckCansel())
		animSpd *= 2.0f;

	jennywk->currAnimFrame += animSpd;
	jennywk->lastAnimFrame += animSpd;

	if (jennywk->currAnimFrame > jennywk->currAction->motion->nbFrame)
		jennywk->currAnimFrame = 0.0f;

	if (jennywk->lastAnimFrame > jennywk->lastAction->motion->nbFrame)
		jennywk->lastAnimFrame = 0.0f;

	JennyDisp(tp);
	EntryColliList(tp->twp);


}

task* CreateJennyNPC()
{
	task* jenny = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, JennyNPC);

	jenny->exec = JennyNPC;
	jenny->disp = JennyDisp;
	jenny->dest = JennyDestructor;

	return jenny;
}
