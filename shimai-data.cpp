
#include "pch.h"
#include "shimai-data.h"

NJS_TEXNAME ShimaiTexName[16];
NJS_TEXLIST ShimaiTexlist = { arrayptrandlengthT(ShimaiTexName, unsigned int) };

#pragma region JennyData

NJS_OBJECT* JennyObject;
WeightInfo* JennyWeights;

NJS_ACTION action_JennyIdle;
NJS_ACTION action_JennyTalk;

ShimaiAnim anim_JennyIdle = {"jenny_idle", &action_JennyIdle};
ShimaiAnim anim_JennyTalk = {"jenny_talk", &action_JennyTalk};



NJS_ACTION jenny_actions[32];

ShimaiAnim jenny_anims[] =
{
	{"jenny_idle", &jenny_actions[SHIMAI_MTN_IDLE]},
	{"jenny_talk", &jenny_actions[SHIMAI_MTN_TALK]}
};


#pragma endregion

#pragma region DeeJayData

NJS_OBJECT* DeeJayObject;
WeightInfo* DeeJayWeights;


NJS_ACTION deejay_actions[32];

ShimaiAnim deejay_anims[] =
{
	{"deejay_idle", &deejay_actions[SHIMAI_MTN_IDLE]},
	{"deejay_idle", &deejay_actions[SHIMAI_MTN_TALK]},
	{"deejay_shower", &deejay_actions[SHIMAI_MTN_SHOWERING]}
};


#pragma endregion

ShimaiData shimaiData[] =
{
	{"jenny", JennyObject, JennyWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, jenny_actions, jenny_anims, LengthOfArray(jenny_anims)},
	{"deejay", DeeJayObject, DeeJayWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, deejay_actions, deejay_anims, LengthOfArray(deejay_anims)},
	{"jenny_mahoushojo", JennyObject, JennyWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, jenny_actions, jenny_anims, LengthOfArray(jenny_anims)}
};
