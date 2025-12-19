
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
ShimaiAnim anim_JennyTalk = { "jenny_talk", &action_JennyTalk };

#pragma endregion

#pragma region DeeJayData

NJS_OBJECT* DeeJayObject;
WeightInfo* DeeJayWeights;

NJS_ACTION action_DeeJayIdle;
NJS_ACTION action_DeeJayTalk;
NJS_ACTION action_DeeJayShower;

ShimaiAnim anim_DeeJayIdle = { "deejay_idle", &action_DeeJayIdle };
ShimaiAnim anim_DeeJayTalk = { "deejay_talk", &action_DeeJayTalk };
ShimaiAnim anim_DeeJayShower = {"deejay_shower", &action_DeeJayShower };

#pragma endregion

ShimaiData shimaiData[] =
{
	{"jenny", JennyObject, JennyWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, &anim_JennyIdle, &anim_JennyTalk},
	{"deejay", DeeJayObject, DeeJayWeights,"SHIMAI", ShimaiTexName, &ShimaiTexlist, &anim_DeeJayIdle, &anim_DeeJayIdle}
};
