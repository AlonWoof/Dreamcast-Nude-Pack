
#include "pch.h"
#include "helper-functions.h"
#include "body-functions.h"
#include "decomp-functions.h"
#include "arousal.h"
#include <UsercallFunctionHandler.h>
#include <FunctionHook.h>

extern bool TailsAlt;
extern float arousalLevel[Characters_MetalSonic];

FunctionHook <void, int, task*> PInitialize_h(0x442750);

const float dripGravity = -0.06f;
const float dropSize = 0.005f;

NJS_TEXNAME cunnyDripTexName[1];
NJS_TEXLIST cunnyDripTexlist = { arrayptrandlengthT(cunnyDripTexName, unsigned int) };

NJS_TEXANIM anim_cunnydrip[3] =
{
  { 10, 10, 5, 5, 0, 0, 255, 255, 0, 0 }
};

NJS_SPRITE sprite_cunnydrip = { { 0.0, 0.0, 0.0 }, dropSize, dropSize, 0, &cunnyDripTexlist, anim_cunnydrip };

struct CunnyDripParticle
{
	NJS_VECTOR pos;
	NJS_VECTOR vel;
	float lifeTime;
};

#define CUNNYDRIPS(tp) ((CunnyDripParticle*)tp->awp->work.ptr[0])
#define CUNNYPNUM(tp) tp->twp->counter.b[0]

NJS_VECTOR calcCrotchPos(playerwk* pwp)
{
	NJS_VECTOR out = lerpVector(pwp->leftfoot_vec, pwp->rightfoot_vec, 0.5f);

	njPrint(NJM_LOCATION(40, 40), "CROTCH X:%f Y%f: Z:%f", out.x, out.y, out.z);

	njAddVector(&out, &playertwp[0]->pos);

	out.y += 4.25f;

	if (PLNO(pwp->ttp->twp) == Characters_Amy)
	{
		PrintDebug("\n\n\nAMY!\n\n\n");
		out.y += 2.0f;
	}

	//DrawCollisionSphere(&out, 0.25f);

	return out;
}

void wetCunnyDropDisp(task* tp)
{
	
	if (!loop_count)
	{

			taskwk* twp = tp->twp;

			CUNNYDRIPS(tp)->pos.y += dripGravity;
			CUNNYDRIPS(tp)->lifeTime--;

			njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
			njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
			njPushMatrix(0);

			njTranslate(0, CUNNYDRIPS(tp)->pos.x, CUNNYDRIPS(tp)->pos.y, CUNNYDRIPS(tp)->pos.z);
			njSetTexture(&cunnyDripTexlist);
			njDrawSprite3D(&sprite_cunnydrip, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_SCALE | NJD_SPRITE_ANGLE);
			njPopMatrix(1);

			if (CUNNYDRIPS(tp)->lifeTime < 0 && random(0, 100) < 10)
			{
				NJS_VECTOR pos = calcCrotchPos(playerpwp[CUNNYPNUM(tp)]);

				CUNNYDRIPS(tp)->pos.x = pos.x + random(-1,1) * 0.02f;
				CUNNYDRIPS(tp)->pos.y = pos.y;
				CUNNYDRIPS(tp)->pos.z = pos.z + random(-1, 1) * 0.02f;
				CUNNYDRIPS(tp)->lifeTime = random(120, 480);
			}
	}
}


//just a little particle effect~
void wetCunnyExec(task* tp)
{
    taskwk* twp = tp->twp;

	if (playertwp[0])
	{
		//twp->pos = playertwp[0]->pos;
	}

	switch (tp->twp->mode)
	{
	case 0:
		tp->awp->work.ptr[0] = new CunnyDripParticle; 
		LoadPVM("DRIPS", &cunnyDripTexlist);
		tp->twp->mode = 1;
		break;

	case 1:
		
		if (arousalLevel[CUNNYPNUM(tp)] > 0.9f)
			mode = 2;
		
		break;
	case 2:
		if (arousalLevel[CUNNYPNUM(tp)] < 0.8f)
			mode = 1;

		wetCunnyDropDisp(tp);
		break;
	}
}

void PInitialize_r(int num, task* tp)
{
	PInitialize_h.Original(num, tp);

	if (PLNO(tp->twp) == Characters_Tails && !TailsAlt)
	{
		task* wet = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, wetCunnyExec);
		wet->exec = wetCunnyExec;
		CUNNYPNUM(wet) = num;
	}

	if (PLNO(tp->twp) == Characters_Amy)
	{
		task* wet = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, wetCunnyExec);
		wet->exec = wetCunnyExec;
		CUNNYPNUM(wet) = num;
	}
}

void hookBodyFunctions()
{
	PInitialize_h.Hook(PInitialize_r);
}