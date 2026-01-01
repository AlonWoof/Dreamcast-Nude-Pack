#include "pch.h"
#include "helper-functions.h"
#include "world-location.h"
#include "CustomObjects.h"
#include "shimai.h"
#include "shimai-msg.h"
#include "deejay-shower.h"

extern HMODULE gDestinyIslandsHandle;

CustomStageObject customObjects[] =
{
	{-1, {0, 0, 0}, {0,NJM_DEG_ANG(90.0f),0}, NULL, NULL},
	//{STAGE_ACT(STAGE_SS_AFT, 4), {-437.797302f, 0.000000f, 1838.036865f}, {0,NJM_DEG_ANG(90.0f),0}, createJenny, NULL, &JennyPoolsideMessages },
	//{STAGE_ACT(STAGE_SS_AFT, 4), {-381.0f, -10.0f, 1911.0f}, {0,NJM_DEG_ANG(315.0f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &DeejayPoolsideMessages},

	{STAGE_ACT(STAGE_SS_AFT, 4), {-231.099991f, 0.0f, 1968.139893f}, {0,NJM_DEG_ANG(-29.970703f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT | SHIMAI_FLG_POOLCHAIR), &DeejayPoolChairMessages},
	{STAGE_ACT(STAGE_SS_AFT, 4), {-231.099991f, 0.0f, 1968.139893f}, {0,NJM_DEG_ANG(-29.970703f),0}, createJenny, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT | SHIMAI_FLG_POOLCHAIR), NULL},

	{STAGE_ACT(STAGE_MR, 0), {448.604706f, -33.080769f, 631.368164f}, {0,NJM_DEG_ANG(120.0f),0}, createJenny, NULL, &JennyMysticRuinsMessages},

	{STAGE_ACT(STAGE_EC_ST_AB, 5), {139.954666f, 13.0f, -101.342484f}, {0,NJM_DEG_ANG(90.0f),0}, createJenny, NULL, &JennyEggCarrierPoolMessages},
	{STAGE_ACT(STAGE_EC_ST_AB, 5), {103.93f, -8.0f, -5.37f}, {0,NJM_DEG_ANG(270.0f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), NULL},

	{STAGE_ACT(STAGE_BEACH, 2), {6141.962402f, -96.993195f, 2374.986084f}, {0,NJM_DEG_ANG(140.0f),0}, createJenny, NULL, &JennyEmeraldCoastMessages},
	{STAGE_ACT(STAGE_BEACH, 2), {6112.229980f, -116.5f, 2357.009766f}, {0,NJM_DEG_ANG(150.0f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &DeejayEmeraldCoastMessages},


	{STAGE_ACT(STAGE_WINDY, 2), {705.093506f, -1078.559937f, -303.454315f}, {0,NJM_DEG_ANG(342.0f),0}, createJenny_MahouShojo, (SHIMAI_FLG_SIT | SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), NULL},

	{STAGE_ACT(STAGE_TWINKLEPARK, 1), {547.397766f, -23.0f,  -724.703003f}, {0,NJM_DEG_ANG(90.0f),0}, createDeejay,  (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), NULL},
	{STAGE_ACT(STAGE_TWINKLEPARK, 1), {650.323608f, 3.000000f, -619.796326f}, {0,NJM_DEG_ANG(300.0f),0}, createJenny, NULL, NULL},

	
	{STAGE_ACT(STAGE_HIGHWAY, 2), {-553.43f, 5.0f, -1713.81f}, {0,NJM_DEG_ANG(90.0f),0}, createJenny_MahouShojo, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT | SHIMAI_FLG_SIT | SHIMAI_FLG_USETOWEL), NULL},
	{STAGE_ACT(STAGE_MOUNTAIN, 1), {-410.49f, 1039.52f, 3190.60f}, {0,NJM_DEG_ANG(121.0f),0}, createJenny_MahouShojo, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT ), NULL},

	{STAGE_ACT(STAGE_CASINO, 0), {-196.404449f, -199.699997f, -530.090515f}, {0,NJM_DEG_ANG(290.0f),0}, createJenny, NULL, &JennyCasinoMessages},
	{STAGE_ACT(STAGE_CASINO, 0), {-171.651657f, -198.890411f, -514.052979f}, {0,NJM_DEG_ANG(110.0f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_SHOWER | SHIMAI_FLG_LOCKROT), &DeejayCasinoMessages},
	{STAGE_ACT(STAGE_CASINO, 0), {-171.6f, -199.1f, -513.92f}, {0, NJM_DEG_ANG(200.0f), 0}, createDeejayShower, NULL, NULL},

	{STAGE_ACT(STAGE_FINAL, 2), {1787.829956f, -201.319992f, -1294.439941f}, {0,NJM_DEG_ANG(-44.961548f),0}, createJenny_MahouShojo, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &JennyFinalEggMessages},


	{STAGE_ACT(STAGE_SS_AFT, 3), {526.24f, -16.678f, 1318.33f}, {0,NJM_DEG_ANG(103.0f),0}, createJenny_MahouShojo,  (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &JennyMSSewerMessages},

	{STAGE_ACT(STAGE_MR, 1), {34.65f, -303.16f, 3181.29f}, {0,NJM_DEG_ANG(90.0f),0}, createJenny_MahouShojo,  (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), NULL},
	{STAGE_ACT(STAGE_MR, 2), {-472.555634f, 155.000000f, -1282.017212f}, {0,NJM_DEG_ANG(237.0f),0}, createJenny_MahouShojo, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &JennyMSJungleMessages},

};


//Destiny Islands only
CustomStageObject Jenny_DI[] =
{
	{ STAGE_ACT(STAGE_AL_GARDEN01_EC, 0), {70.910759f, 27.241463f, -125.562256f}, {0,NJM_DEG_ANG(325.0f),0}, createJenny, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_SIT | SHIMAI_FLG_LOCKROT) , &JennyDestinyIslandsMessages},
	{ STAGE_ACT(STAGE_AL_GARDEN01_EC, 0), {-298.0f, 37.33f, -10.55f}, {0,NJM_DEG_ANG(453.96f),0}, createJenny, NULL, &JennyDestinyIslandsMessages_Tree},
	{ STAGE_ACT(STAGE_AL_GARDEN01_EC, 0), {-240.210007f, 58.759998f, 62.709972f}, {0,NJM_DEG_ANG(241.018066f),0}, createJenny, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_SIT | SHIMAI_FLG_LOCKROT) , &JennyDestinyIslandsMessages}
};

CustomStageObject Deejay_DI[] =
{
	{STAGE_ACT(STAGE_AL_GARDEN01_EC, 0), {-89.713493f, -0.471137f, -218.357544f}, {0,NJM_DEG_ANG(141.0f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &DeejayDestinyIslandsMessages},
	{STAGE_ACT(STAGE_AL_GARDEN01_EC, 0), {-296.824677f, 53.574753f, -36.124981f}, {0,NJM_DEG_ANG(199.500732f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT | SHIMAI_FLG_LAYTREE), &DeejayDestinyIslandsMessages_Tree},
	{STAGE_ACT(STAGE_AL_GARDEN01_EC, 0), {-194.990250f, -0.471137f, -75.570190f}, {0,NJM_DEG_ANG(72.015381f),0}, createDeejay, (SHIMAI_FLG_LOCKANIM | SHIMAI_FLG_LOCKROT), &DeejayDestinyIslandsMessages}
};

task* createCustomObject(CustomStageObject* obj)
{
	task* tp = obj->taskFunc();

	if (tp)
	{
		tp->twp->pos = obj->position;
		tp->twp->ang.x = obj->rotation[0];
		tp->twp->ang.y = obj->rotation[1];
		tp->twp->ang.z = obj->rotation[2];
		tp->twp->flag = obj->flags;

		if (obj->ptr != NULL)
			tp->awp->work.ptr[1] = obj->ptr;
	}

	return tp;
}

void setupChaoGardenGirls()
{
	if (AL_GetStageNumber() != CHAO_STG_EC)
		return;

	if (!gDestinyIslandsHandle)
		return;

	int variant = random(0, 2);

	//Create the jenny
	createCustomObject(&Jenny_DI[variant]);

	//Create the deejay
	createCustomObject(&Deejay_DI[variant]);

}

void checkCustomObjects()
{

	for (CustomStageObject obj : customObjects)
	{

		if (ssStageNumber != GET_STAGE(obj.levelAct) || ssActNumber != GET_ACT(obj.levelAct))
		{
		
			//if (obj.instance)
			//{
			//	DestroyTask(obj.instance);
			//	obj.instance = NULL;
			//}

		}
	}
}


void setupAllCustomObjects()
{
	for (CustomStageObject obj : customObjects)
	{

		if (ssStageNumber == GET_STAGE(obj.levelAct) && ssActNumber == GET_ACT(obj.levelAct))
		{
			createCustomObject(&obj);
		}
	}

	//setupChaoGardenGirls();
}


