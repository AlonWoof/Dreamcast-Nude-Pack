#pragma once
#ifndef ALONWOOF_SHIMAI_MSG_H_
#define ALONWOOF_SHIMAI_MSG_H_

struct ShimaiMessagePool
{
	const char*** msg_Character[Characters_MetalSonic];
};

extern ShimaiMessagePool JennyPoolsideMessages;
extern ShimaiMessagePool DeeJayPoolsideMessages;
extern ShimaiMessagePool JennyMysticRuinsMessages;
extern ShimaiMessagePool JennyEggCarrierPoolMessages;

extern ShimaiMessagePool* msgPool_ADVSS06[];
extern ShimaiMessagePool* msgPool_ADVMR00[];
extern ShimaiMessagePool* msgPool_ADVEC05[];
extern ShimaiMessagePool* msgPool_S01A02[];
extern ShimaiMessagePool* msgPool_S09A00[];

#endif