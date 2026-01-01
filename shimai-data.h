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
	SHIMAI_MTN_SIT,
	SHIMAI_MTN_SHOWER,
	SHIMAI_MTN_LAYTREE,
	SHIMAI_MTN_POOLCHAIR
};

ShimaiData shimaiData[];

extern ShimaiAnim anim_DeejayIdle;
extern ShimaiAnim anim_DeejayTalk;
extern ShimaiAnim anim_DeejayShower;

#endif