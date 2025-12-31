
#include "pch.h"
#include "shimai.h"
#include "shimai-data.h"
#include "shimai-msg.h"
#include "LoadModel.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include "jenny-towel.h"
#include <stdio.h>
#include <math.h>
#include <ctime>

using namespace std;

#define GET_SHIMAIWK(tp) ((ShimaiWork*)tp->awp->work.ptr[0])
#define SHIMAIDATA(tp) shimaiData[((ShimaiWork*)tp->awp->work.ptr[0])->sisterID]

#define JENNY_MASK_FRAME(tp) tp->awp->work.ub[10]
#define JENNY_MASK_TIMER(tp) tp->awp->work.ub[11]
#define JENNY_TOWEL_TEX(tp) tp->awp->work.ub[12]

extern NJS_TEXLIST ShimaiTexlist;
extern NJS_OBJECT ShimaiShadow;
extern const HelperFunctions* helperFunctionsGlobal;
extern bool gDebugMode;
int gShimaiTalkCount = 0;
extern HMODULE gLanternEngineHandle;


enum
{
	SHIMAI_MD_INIT,
	SHIMAI_MD_IDLE,
	SHIMAI_MD_TALK
};

const char* shimaiNameStr[] =
{
	"JENNY",
	"DEEJAY",
	"JENNY"
};

const char* shimaiModeStr[] =
{
	"SHIMAI_MD_INIT",
	"SHIMAI_MD_IDLE",
	"SHIMAI_MD_TALK"
};



CCL_INFO colli_info_shimai[1] =
{
	{ 0, CI_FORM_PERSON, CI_PUSH_PO_CMN | CI_PUSH_TH_CMN, 0, 0, { 0.0f, 1.0f, 0.0f}, 3.0f, 3.0f, 0.65f, 0.0f, 0, 0, 0 },
};

static int maskAnimTexID[] =
{
	17,18,19,20
};

static Uint32 maskAnimPtr[4] =
{
	NULL,
	NULL,
	NULL,
	NULL
};

struct ShimaiWork
{
	SHIMAI_ID sisterID;

	SHIMAI_MTN currentAnim;
	SHIMAI_MTN overrideAnim;

	float animFrame;
	float animSpeed;

	int homeAngle;

	ShimaiMessagePool* msgPool;
	NpcMessageMemory msgBuffer;
	int msgCounter;
	int act = 0;
	char mes_status;

};

static void loadShimaiAnimation(ShimaiAnim* animData, NJS_OBJECT* obj)
{

	NJS_MOTION* newMotion = new NJS_MOTION;

	string path;
	path += "system\\";
	path += animData->fileName;
	path += ".saanim";

	newMotion = LoadAnimation(path.c_str());
	animData->mAction->motion = newMotion;
	animData->mAction->object = obj;
}

bool shimaiMaterial(NJS_MATERIAL* material, Uint32 flags)
{
	set_diffuse(2, false);
	set_specular(8, false);

	return true;
}


const NJS_MATERIAL* matArray[] = { nullptr };

static void shimaiFixMaterials(NJS_OBJECT * obj)
{
	//Why wouldn't you tho
	if (!gLanternEngineHandle)
		return;

	if (obj->basicdxmodel != nullptr)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			matArray[0] = &obj->basicdxmodel->mats[q];
			material_register(matArray, 1, &shimaiMaterial);
		}
	}

	if (obj->sibling != nullptr)
	{
		shimaiFixMaterials(obj->sibling);
	}

	if (obj->child != nullptr)
	{
		shimaiFixMaterials(obj->child);
	}
}

static NJS_MATERIAL* jennyMaskMat;

static NJS_MATERIAL* shimaiGetMaskMaterial(NJS_OBJECT* obj, Uint32 texID)
{

	if (obj->basicdxmodel != nullptr)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			PrintDebug(" ATTR_TEXID: %i\n", obj->basicdxmodel->mats[q].attr_texId);

			if ( obj->basicdxmodel->mats[q].attr_texId == texID)
				return &obj->basicdxmodel->mats[q];

			//obj->basicdxmodel->mats[q].attr_texId = 0;
		}
	}

	NJS_MATERIAL* ret = NULL;

	if (obj->sibling != nullptr)
	{
		ret = shimaiGetMaskMaterial(obj->sibling, texID);
	}

	if (obj->child != nullptr)
	{
		ret = shimaiGetMaskMaterial(obj->child, texID);
	}

	if (ret)
		return ret;

	return NULL;
}

static void loadShimaiModel(ShimaiData* data)
{
	LoadPVM(data->shimaiPVMName, data->shimaiTexlist);
	
	
	string path;
	path += "system\\";
	path += data->shimaiModel;
	path += ".sa1mdl";

	data->shimaiObject = LoadModel(path.c_str(), data->shimaiWeightInfo);
	helperFunctionsGlobal->Weights->Init(data->shimaiWeightInfo, data->shimaiObject);


	shimaiFixMaterials(data->shimaiObject);
	jennyMaskMat = shimaiGetMaskMaterial(data->shimaiObject, 17);

	for (int i = 0; i < data->nbAnims; i++)
	{
		loadShimaiAnimation(&data->shimaiAnims[i], data->shimaiObject);
		data->shimaiAnims[i].mAction->object = data->shimaiObject;
	}

}

static void shimaiLoadMessagePool(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);
	shw->msgPool = NULL;

	if (tp->awp->work.ptr[1])
	{
		shw->msgPool = (ShimaiMessagePool*)tp->awp->work.ptr[1];
	}
}

//Animation change
static void shimaiChangeAnimation(task* tp, SHIMAI_MTN newAnim, bool override)
{

	if ((tp->twp->flag & SHIMAI_FLG_LOCKANIM) && !override)
		return;

	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (shw->currentAnim == newAnim)
		return;

	if (SHIMAIDATA(tp).shimaiActions[newAnim].motion == NULL)
		return;

	shw->currentAnim = newAnim;
	shw->animFrame = 0;

	if(override)
		tp->twp->flag |= SHIMAI_FLG_LOCKANIM;
	
}

static void DBG_shimaiMover(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	//scooch your butt into place lol

	PrintDebug("\nGIRL POS %f, %f, %f\n", tp->twp->pos.x, tp->twp->pos.y, tp->twp->pos.z);
	PrintDebug("\nGIRL ANGY: %f\n", NJM_ANG_DEG(tp->twp->ang.y));

	float trnAmnt = 0.1f;// *0.25f;
	float rotAmnt = 1.0f;// *0.25f;


	if (KeyGetPress(PDD_KEYUS_PAD_PLUS))
		tp->twp->pos.y += trnAmnt;

	if (KeyGetPress(PDD_KEYUS_PAD_MINUS))
		tp->twp->pos.y -= trnAmnt;

	if (KeyGetPress(PDD_KEYUS_PAD_8))
		tp->twp->pos.z += trnAmnt;

	if (KeyGetPress(PDD_KEYUS_PAD_2))
		tp->twp->pos.z -= trnAmnt;

	if (KeyGetPress(PDD_KEYUS_PAD_6))
		tp->twp->pos.x += trnAmnt;

	if (KeyGetPress(PDD_KEYUS_PAD_4))
		tp->twp->pos.x -= trnAmnt;

	if (KeyGetPress(PDD_KEYUS_PAD_7))
		tp->twp->ang.y += NJM_DEG_ANG(rotAmnt);

	if (KeyGetPress(PDD_KEYUS_PAD_9))
		tp->twp->ang.y -= NJM_DEG_ANG(rotAmnt);

	shw->homeAngle = tp->twp->ang.y;
}

static void shimaiJennySetup(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	//Load her special butt towel textures
	LoadPVM("JENNY_TOWEL", &JennyTowelTexlist);
	JENNY_TOWEL_TEX(tp) = random(0, 3);

	if(tp->twp->flag & SHIMAI_FLG_SIT)
		shimaiChangeAnimation(tp, SHIMAI_MTN_SIT, true);

	/*
	//Sitting animation
	if (AL_GetStageNumber() == CHAO_STG_EC || 
		ssStageNumber == STAGE_WINDY || 
		ssStageNumber == STAGE_HIGHWAY)
	{
		tp->twp->flag |= SHIMAI_FLG_LOCKROT;

		//Don't sit on a public bench without a towel
		if (ssStageNumber == STAGE_HIGHWAY)
			tp->twp->flag |= SHIMAI_FLG_USETOWEL;

		shimaiChangeAnimation(tp, SHIMAI_MTN_SIT, true);
	}
	

	//She thinks you can't see her, lol
	if (shw->sisterID == SHIMAI_JENNY_MAHOUSHOJO)
	{
		tp->twp->flag |= (SHIMAI_FLG_LOCKROT | SHIMAI_FLG_LOCKANIM);
	}
	*/
}

task* djShower = NULL;

static void shimaiDeejaySetup(task* tp)
{

	if (tp->twp->flag & SHIMAI_FLG_LAYTREE)
		shimaiChangeAnimation(tp, SHIMAI_MTN_LAYTREE, true);

	if (tp->twp->flag & SHIMAI_FLG_SHOWER)
		shimaiChangeAnimation(tp, SHIMAI_MTN_SHOWER, true);

	/*
	ShimaiWork* shw = GET_SHIMAIWK(tp);
	tp->twp->flag |= SHIMAI_FLG_LOCKROT;

	//SHIMAIDATA(tp).anim_idle = &anim_DeejayIdle;
	//SHIMAIDATA(tp).anim_talk = &anim_DeejayIdle;

	if (ssStageNumber == STAGE_CASINO)
	{
		shimaiChangeAnimation(tp, SHIMAI_MTN_SHOWER, true);
	}
	*/
} 

static void DBG_awpViewer(task* tp)
{
	int r = 0;
	int c = 0;

	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			//njPrint(NJM_LOCATION(16 + (c * 8), 16 + (r * 8)), "%x", tp->awp->work.ub[(r * 4 + c)]);
		}
	}

	njPrint(NJM_LOCATION(16, 16), "%x", tp->awp->work.ptr[1]);
}

static void shimaiJennyExec(task* tp)
{
	DBG_shimaiMover(tp);
	//DBG_awpViewer(tp);

}

static void shimaiDeejayExec(task* tp)
{
	//DBG_shimaiMover(tp);

}

static void shimaiDestroy(task* tp)
{
	free(GET_SHIMAIWK(tp));
}

static void shimaiInit(task* tp)
{
	
	ShimaiWork * shw = GET_SHIMAIWK(tp);

	loadShimaiModel(&SHIMAIDATA(tp));
	shw->msgCounter = 0;
	shw->msgPool = NULL;
	shw->animFrame = 0;
	shw->animSpeed = 0.5f;
	shw->currentAnim = SHIMAI_MTN_IDLE;
	shw->homeAngle = tp->twp->ang.y;

	switch (shw->sisterID)
	{
	case SHIMAI_JENNY:
		shimaiJennySetup(tp);
		break;

	case SHIMAI_DEEJAY:
		shimaiDeejaySetup(tp);
		break;

	case SHIMAI_JENNY_MAHOUSHOJO:
		shimaiJennySetup(tp);
		break;
	}

	shimaiLoadMessagePool(tp);
	CCL_Init(tp, colli_info_shimai, 1, CID_OBJECT);

}

static void drawShimaiShadow(task* tp)
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
		njSetTexture(&ShimaiTexlist);
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
		ProcessModelNode_A_WrapperC(&ShimaiShadow, thisa);
		njPopMatrix(1u);
	}
}

//For good girls to keep their butts clean
static void drawGoodGirlTowel(task* tp)
{
	taskwk* twp = tp->twp;

	if (!loop_count)
	{
		ResetMaterial();
		njSetTexture(&JennyTowelTexlist);
		mats_goodGirlTowel[0].attr_texId = JENNY_TOWEL_TEX(tp);
		___dsSetPalette(2);

		SaveControl3D();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
		SetMaterial(0.5f, 1.0f, 1.0f, 1.0f);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);

		ROTATEX(0, 0);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(270.0f));
		ROTATEZ(0, 0);

		njScale(0, 1.0f, 1.0f, 1.0f);

		dsDrawObject(&goodGirlTowel);

		njPopMatrix(1u);
		ResetMaterial();
		LoadControl3D();
		___dsSetPalette(0);

	}
}

static void shimaiDisp(task* tp)
{
	
	taskwk* twp = tp->twp;
	ShimaiWork* shw = GET_SHIMAIWK(tp);


	JENNY_MASK_TIMER(tp)++;

	if (JENNY_MASK_TIMER(tp) > 15)
	{
		JENNY_MASK_FRAME(tp)++;
		JENNY_MASK_TIMER(tp) = 0;
	}

	if (JENNY_MASK_FRAME(tp) > 3)
		JENNY_MASK_FRAME(tp) = 0;
	
	if(jennyMaskMat)
		jennyMaskMat->attr_texId = 17 + JENNY_MASK_FRAME(tp); 

	if (!loop_count)
	{
		ResetMaterial();
		njSetTexture(shimaiData[shw->sisterID].shimaiTexlist);
		//set_diffuse(8, false);
		___dsSetPalette(0);

		SaveControl3D();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
		SetMaterial(0.5f, 1.0f, 1.0f, 1.0f);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);

		ROTATEX(0, 0);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(270.0f));
		ROTATEZ(0, 0);

		njScale(0, 1.0f, 1.0f, 1.0f);

		helperFunctionsGlobal->Weights->Apply(SHIMAIDATA(tp).shimaiWeightInfo, &SHIMAIDATA(tp).shimaiActions[shw->currentAnim], GET_SHIMAIWK(tp)->animFrame);
		dsDrawMotion(SHIMAIDATA(tp).shimaiObject, SHIMAIDATA(tp).shimaiActions[shw->currentAnim].motion, shw->animFrame);


		njPopMatrix(1u);
		ResetMaterial();
		LoadControl3D();
		___dsSetPalette(0);
	}

	if(tp->twp->flag & SHIMAI_FLG_USETOWEL)
		drawGoodGirlTowel(tp);
	else
		drawShimaiShadow(tp);
		
}
static void shimaiDebug(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	//njPrint((NJM_LOCATION(2, 8 + (8 * shw->sisterID))), "%s STATE: %s", shimaiNameStr[shw->sisterID], shimaiModeStr[tp->twp->mode]);
	//njPrint((NJM_LOCATION(2, 9 + (8 * shw->sisterID))), " OBJECT: %x", SHIMAIDATA(tp).shimaiObject);
	//njPrint((NJM_LOCATION(2, 10 + (8 * shw->sisterID))), " ANIM_IDLE: %x", SHIMAIDATA(tp).anim_idle->mAction);

	for (int i = 0; i < 32; i++)
	{
		if (&SHIMAIDATA(tp).shimaiActions[i] != NULL)
		{
			njPrint(NJM_LOCATION((30 * shw->sisterID) + 5, 50 + i), "ACTION %i OFFSET: %x", i, SHIMAIDATA(tp).shimaiActions[i].motion);
		}
	}

}
static void startNPCMessage(task* tp, const char** msg)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	shw->msgBuffer.message_p = msg;
	shw->msgBuffer.flag_index = 0;

	NpcMessageStart(&shw->msgBuffer);
}
//Wait for player to close message.
static bool waitPlayerCloseMsg(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (shw->mes_status == 0)
	{
		SetInputP(0, PL_OP_LETITGO);
		EV_MsgClose();
		return true;
	}

	playerpwp[0]->breathtimer = 0;

	return false;
}
//Check if player talks to us
static bool checkPlayerInteract(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);


	if (!shw->msgPool)
		return false;

	if (!shw->msgPool->msg_Character)
		return false;

	if (!shw->msgPool->msg_Character[0])
		return false;

	float dst = njDistanceP2P(&tp->twp->pos, &playertwp[0]->pos);
	float distThreshold = 10;

	if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma)
		distThreshold = 20;

	if (dst < distThreshold)
	{
		if (perG[0].press & (Buttons_B | Buttons_X))
		{
			SetInputP(0, PL_OP_PLACEON);
			HintRegistStatusPointer(&shw->mes_status);
			//startNPCMessage(tp, msg_Character[PLNO(playertwp[0])][jennywk->msgCounter]);

			startNPCMessage(tp, shw->msgPool->msg_Character[CurrentCharacter][shw->msgCounter]);
			

			if (!shw->msgCounter)
				shw->msgCounter++;

			return true;
		}
	}

	return false;
}

//Check for mode changes
static void shimaiCheckMode(task* tp)
{
	if (!isIngame())
		return;

	ShimaiWork* shw = GET_SHIMAIWK(tp);

	switch (tp->twp->mode)
	{
	case SHIMAI_MD_INIT:
		break;

	case SHIMAI_MD_IDLE:
		if (checkPlayerInteract(tp))
		{
			tp->twp->mode = SHIMAI_MD_TALK;
			//changeJennyAction(tp, &action_Jenny_talk);

			shimaiChangeAnimation(tp, SHIMAI_MTN_TALK, false);

			shw->animSpeed = 0.75f;
			InputHookSet(tp, &tp->twp->pos, &tp->twp->ang.y, 0, 0, 10.0f);
			gShimaiTalkCount++;
		}
		return;

	case SHIMAI_MD_TALK:
		if (waitPlayerCloseMsg(tp))
		{
			tp->twp->mode = SHIMAI_MD_IDLE;
			//changeJennyAction(tp, &action_Jenny_idle);

			shimaiChangeAnimation(tp, SHIMAI_MTN_IDLE, false);
		}
		break;
	}
}

unsigned int ShimaiGetAngleToTarget(NJS_POINT3* ps, NJS_POINT3* pd, float* dist, float* distxz)
{
	long double v5; // st7
	long double v6; // st6
	float v8; // [esp+8h] [ebp+8h]

	v5 = pd->x - ps->x;
	v8 = pd->y - ps->y;
	v6 = pd->z - ps->z;
	if (dist)
	{
		*dist = sqrt(v6 * v6 + v8 * v8 + v5 * v5);
	}
	if (distxz)
	{
		*distxz = sqrt(v6 * v6 + v5 * v5);
	}
	return (atan2(v6, -v5) * 65536.0 * 0.1591549762031479);
}

static void shimaiLerpAngle(task* tp, int targetAngle)
{

	int angle = tp->twp->ang.y;

	angle = lerp(angle, targetAngle, 0.2f);

	tp->twp->ang.y = angle;
}

static float fixAngle(float angle)
{
	while (angle > 360.0f)
		angle -= 360.0f;

	while (angle < 0)
		angle += 360.0f;

	return angle;
}

//Cute idea also used in my Amy fangame
//Was inspired by your home gyroid in Animal Crossing
static void shimaiProximitySpeed(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	float minDist = 10;
	float maxDist = 50;

	float minAnimSpeed = 0.45f;
	float maxAnimSpeed = 1.25f;
	

	float dst = njDistanceP2P(&tp->twp->pos, &playertwp[0]->pos);

	float fac = clampFloat01(remapRange(dst, minDist, maxDist, 0.0f, 1.0f));

	//njPrint(NJM_LOCATION(16, 30 + shw->sisterID), "DIST: %f FAC: %f", dst, fac);

	shw->animSpeed = lerp(maxAnimSpeed, minAnimSpeed, fac);
}
//Main exec
static void shimaiExec(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (shw->act != ssActNumber)
	{
		DestroyTask(tp);
		return;
	}

	switch (tp->twp->mode)
	{
	case SHIMAI_MD_INIT:
		shimaiInit(tp);
		tp->twp->mode++;
		break;

	case SHIMAI_MD_IDLE:

		if (!(tp->twp->flag & SHIMAI_FLG_LOCKROT))
			shimaiLerpAngle(tp, shw->homeAngle);

		shimaiProximitySpeed(tp);

		break;

	case SHIMAI_MD_TALK:
		if (!(tp->twp->flag & SHIMAI_FLG_LOCKROT))
			shimaiLerpAngle(tp, NJM_DEG_ANG(fixAngle(NJM_ANG_DEG(ShimaiGetAngleToTarget(&tp->twp->pos, &playertwp[0]->pos, 0, 0)) - NJM_DEG_ANG(180.0f))));
		break;
	}

	if (shw->sisterID == SHIMAI_JENNY || shw->sisterID == SHIMAI_JENNY_MAHOUSHOJO)
		shimaiJennyExec(tp);

	if (shw->sisterID == SHIMAI_DEEJAY)
		shimaiDeejayExec(tp);

	GET_SHIMAIWK(tp)->animFrame += GET_SHIMAIWK(tp)->animSpeed;

	//if (GET_SHIMAIWK(tp)->animFrame > GET_SHIMAIWK(tp)->currentAnim->mAction->motion->nbFrame)
	//	GET_SHIMAIWK(tp)->animFrame = 0;

	shimaiCheckMode(tp);


	if(gDebugMode)
		shimaiDebug(tp);

	shimaiDisp(tp);
	EntryColliList(tp->twp);
}

static bool shouldCreateSister(char sisterID)
{
	if (sisterID != SHIMAI_JENNY_MAHOUSHOJO)
	{
		if (GetTimeOfDay() == TimesOfDay_Night && ssStageNumber == STAGE_SS_AFT)
			return false;

		if (GetTimeOfDay() == TimesOfDay_Night && ssStageNumber == STAGE_MR)
			return false;
	}
	else
	{

		//No witch hunting on school nights young lady
		//if (getDayOfWeek() < WDAY_KIN)
		//	return false;

		if (GetTimeOfDay() != TimesOfDay_Night && ssStageNumber == STAGE_SS_AFT)
			return false;

		if (GetTimeOfDay() != TimesOfDay_Night && ssStageNumber == STAGE_MR)
			return false;

		if (ssStageNumber == STAGE_MR && ssActNumber == 2 && !getFinalEggVisible())
			return false;

	}



	if (ssStageNumber == STAGE_EC_ST_AB && GetEventFlag((EventFlags)FLAG_KNUCKLES_EC_PALMSWITCH))
		return false;

	if (ssStageNumber == STAGE_BEACH)
	{
		int day = getDayOfWeek();

		//Deejay's line about having school tomorrow won't make sense if it's not a school night.
		if (day == WDAY_KIN || day == WDAY_DO)
			return false;
	}

	return true;
}
//Create Sisters~
static task* createSister(SHIMAI_ID sisterID)
{
	if (!shouldCreateSister(sisterID))
		return NULL;

	task* newSis = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, shimaiExec);
	newSis->awp->work.ptr[0] = new ShimaiWork;

	ShimaiWork* shw = GET_SHIMAIWK(newSis);
	shw->sisterID = sisterID;
	shw->act = ssActNumber;

	newSis->exec = shimaiExec;
	newSis->disp = shimaiDisp;
	newSis->dest = shimaiDestroy;

	return newSis;
}

task* createJenny()
{
	return createSister(SHIMAI_JENNY);
}
task* createDeejay()
{
	return createSister(SHIMAI_DEEJAY);
}
task* createJenny_MahouShojo()
{
	return createSister(SHIMAI_JENNY_MAHOUSHOJO);
}
task* createDeejay_OnTree()
{
	task* deejay = createSister(SHIMAI_DEEJAY);
	return deejay;
}
