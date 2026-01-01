
#include "pch.h"
#include "shimai-data.h"

NJS_TEXNAME ShimaiTexName[16];
NJS_TEXLIST ShimaiTexlist = { arrayptrandlengthT(ShimaiTexName, unsigned int) };


#pragma region JennyData

NJS_OBJECT* JennyObject;
WeightInfo* JennyWeights;

NJS_ACTION jenny_actions[32];

ShimaiAnim jenny_anims[] =
{
	{"jenny_idle", &jenny_actions[SHIMAI_MTN_IDLE]},
	{"jenny_talk", &jenny_actions[SHIMAI_MTN_TALK]},
	{"jenny_sit", &jenny_actions[SHIMAI_MTN_SIT]},
	{"jenny_poolchair", &jenny_actions[SHIMAI_MTN_POOLCHAIR]}
	
};


#pragma endregion

#pragma region DeejayData

NJS_OBJECT* DeejayObject;
WeightInfo* DeejayWeights;

NJS_ACTION deejay_actions[32];

ShimaiAnim deejay_anims[] =
{
	{"deejay_idle", &deejay_actions[SHIMAI_MTN_IDLE]},
	{"deejay_shower", &deejay_actions[SHIMAI_MTN_SHOWER]},
	{"deejay_laytree", &deejay_actions[SHIMAI_MTN_LAYTREE]},
	{"deejay_poolchair", &deejay_actions[SHIMAI_MTN_POOLCHAIR]}
};


#pragma endregion

ShimaiData shimaiData[] =
{
	{"jenny", JennyObject, JennyWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, jenny_actions, jenny_anims, LengthOfArray(jenny_anims)},
	{"deejay", DeejayObject, DeejayWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, deejay_actions, deejay_anims, LengthOfArray(deejay_anims)},
	{"jenny_mahoushojo", JennyObject, JennyWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, jenny_actions, jenny_anims, LengthOfArray(jenny_anims)}
};
