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

	ShimaiAnim* anim_idle;
	ShimaiAnim* anim_talk;

};

enum
{
	SHIMAI_JENNY,
	SHIMAI_DEEJAY
};

ShimaiData shimaiData[];

extern ShimaiAnim anim_DeeJayIdle;
extern ShimaiAnim anim_DeeJayTalk;
extern ShimaiAnim anim_DeeJayShower;

#endif