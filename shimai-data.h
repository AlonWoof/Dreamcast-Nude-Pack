#pragma once
#ifndef ALONWOOF_SHIMAI_DATA_H_
#define ALONWOOF_SHIMAI_DATA_H_

struct ShimaiAnim
{
	const char* fileName;
	NJS_ACTION* mAction;
};

struct ShimaiData
{
	const char* shimaiModel;
	NJS_OBJECT* shimaiObject;
	WeightInfo* shimaiWeightInfo;

	const char* shimaiPVMName;
	NJS_TEXNAME* shimaiTexName;
	NJS_TEXLIST* shimaiTexlist;

	NJS_ACTION* shimaiActions;
	ShimaiAnim* shimaiAnims;
	int nbAnims;
};

enum SHIMAI_ID
{
	SHIMAI_JENNY,
	SHIMAI_DEEJAY,
	SHIMAI_JENNY_MAHOUSHOJO
};

enum SHIMAI_MTN
{
	SHIMAI_MTN_IDLE,
	SHIMAI_MTN_TALK,
	SHIMAI_MTN_SHOWERING
};

ShimaiData shimaiData[];

extern ShimaiAnim anim_DeeJayIdle;
extern ShimaiAnim anim_DeeJayTalk;
extern ShimaiAnim anim_DeeJayShower;

#endif