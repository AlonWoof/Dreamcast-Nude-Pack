
#include "pch.h"
#include "sex.h"


#include "anim-Amy-Masturbate.h"


#define SEX_INIT 0
#define SEX_LOOP 1
#define SEX_ORGASM 2
#define SEX_END 3

extern float arousalLevel[Characters_MetalSonic];
NJS_ACTION AmyMasturbateAction = { AMY_OBJECTS[0], &AmyFapping };
extern NJS_MODEL_SADX amy_face_sex_attach;

NJS_MODEL_SADX* AMY_ORIGINAL_HEADS[2];

bool checkInterruptSex(int pno)
{
	if (!CheckPadReadModeP(pno))
		return false;

	if (abs(ControllersRaw[pno].LeftStickX) > 3 || abs(ControllersRaw[pno].LeftStickY) > 3)
		return true;

	if (GameState != 15)
		return true;

	return false;
}

void setAmyFaceSex()
{
	AMY_ORIGINAL_HEADS[0] = AMY_MODELS[0];
	AMY_ORIGINAL_HEADS[1] = AMY_MODELS[1];
	AMY_ORIGINAL_HEADS[2] = AMY_MODELS[2];

	AMY_MODELS[0] = &amy_face_sex_attach;
	AMY_MODELS[1] = &amy_face_sex_attach;
	AMY_MODELS[2] = &amy_face_sex_attach;
}

void Sex_AmyMasturbate(task* tp)
{
	
	switch (tp->twp->mode)
	{
		case SEX_INIT:

			//Save the position to prevent movement
			tp->twp->ang = playertwp[tp->twp->value.b[0]]->ang;
			tp->twp->pos = playertwp[tp->twp->value.b[0]]->pos;

			//Start the animation
			EV_SetAction(playertp[tp->twp->value.b[0]], &AmyMasturbateAction, &AMY_TEXLIST, 0.85f, 1, 0);
			setAmyFaceSex();

			//The cum timer lol
			tp->twp->value.w[1] = 1800;

			//Next mode
			tp->twp->mode++;

			break;

		case SEX_LOOP:

			playertwp[tp->twp->value.b[0]]->ang = tp->twp->ang;
			playertwp[tp->twp->value.b[0]]->pos = tp->twp->pos;

			PrintDebug(" time left is %i \n", tp->twp->value.w[1]);

			arousalLevel[Characters_Amy] = 1.0f;

			if (checkInterruptSex(tp->twp->value.b[0]))
				tp->twp->mode = SEX_END;

			tp->twp->value.w[1]--;

			if(tp->twp->value.w[1] == 0)
				tp->twp->mode = SEX_ORGASM;

			break;

		case SEX_ORGASM:

			arousalLevel[Characters_Amy] *= 0.5365421f;

			if(arousalLevel[Characters_Amy] < 0.1f)
				tp->twp->mode = SEX_END;

			break;

		case SEX_END:

			EV_ClrAction(playertp[tp->twp->value.b[0]]);
			DestroyTask(tp);
			break;
	}

}

void dbg_amyFap(int pno)
{
	if (!playertwp[pno])
		return;

	if (playertwp[pno]->counter.b[1] != Characters_Amy)
		return;

	task* amyFap = CreateElementalTask(2, 0, Sex_AmyMasturbate);

	amyFap->twp->value.b[0] = pno;

}