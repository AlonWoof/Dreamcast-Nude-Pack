#pragma once
#ifndef ALONWOOF_SHIMAI_H_
#define ALONWOOF_SHIMAI_H_

#define GET_SHIMAIWK(tp) ((ShimaiWork*)tp->awp->work.ptr[0])
#define SHIMAIDATA(tp) shimaiData[((ShimaiWork*)tp->awp->work.ptr[0])->sisterID]

task* createJenny();
task* createDeejay();
task* createJenny_MahouShojo();

enum SHIMAI_FLG
{
	SHIMAI_FLG_LOCKANIM = 0x1,
	SHIMAI_FLG_LOCKROT = 0x2,
	SHIMAI_FLG_USETOWEL = 0x4,
	SHIMAI_FLG_SIT = 0x8,
	SHIMAI_FLG_LAYTREE = 0x10,
	SHIMAI_FLG_SHOWER = 0x20
};



#endif