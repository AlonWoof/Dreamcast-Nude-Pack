
#include <SADXModLoader.h>
#include "pch.h"
#include "helper-functions.h"
#include <UsercallFunctionHandler.h>

#include "a_sowewr0.h"
#include "a_sowewr1.h"
#include "a_sowewr2.h"

NJS_ACTION action_a_sowewr0 { AMY_OBJECTS[0], &motion_a_sowewr0 };
NJS_ACTION action_a_sowewr1 { AMY_OBJECTS[0], &motion_a_sowewr1 };
NJS_ACTION action_a_sowewr2 { AMY_OBJECTS[0], &motion_a_sowewr2 };

FunctionPointer(void, AmyChangeWaitingMotion, (taskwk* twp, playerwk* pwp), 0x484520);


PL_ACTION amy_sowewr0{ &action_a_sowewr0, 73, MD_MTN_NEXT, 39, 0.25f, 0.25f };
PL_ACTION amy_sowewr1{ &action_a_sowewr1, 73, MD_MTN_LOOP, 39, 0.25f, 0.25f };
PL_ACTION amy_sowewr2{ &action_a_sowewr2, 73, MD_MTN_NEXT, 0, 0.25f, 0.50f };

PL_ACTION amy_action38{ NULL, 0, 0, 0, 0, 0 };
PL_ACTION amy_action39{ NULL, 0, 0, 0, 0, 0 };
PL_ACTION amy_action40{ NULL, 0, 0, 0, 0, 0 };

bool isInShower = false;

UsercallFunc(int, AmyCheckInput, (playerwk* pwp, motionwk2* mwp, taskwk* twp), (pwp, mwp, twp), 0x00487810, rEAX, rECX, rEDI, rESI);

int AmyCheckInput_r(playerwk* pwp, motionwk2* mwp, taskwk* twp)
{
	if (twp->ewp->move.mode)
	{
		//KnucklesCheckAutoPilot(twp, pwp);
		return FALSE;
	}

	

	if (twp->ewp->path.list)
	{
		twp->mode = MD_AMY_EVENT;
		twp->flag &= ~(PL_FLAG_PATH | PL_FLAG_ATTACK | PL_FLAG_BALL);
		return TRUE;
	}

	if (!(twp->flag & PL_FLAG_INPUT))
	{
		return FALSE;
	}

	switch (twp->smode)
	{
	case PL_OP_STARTSHOWER:
		twp->mode = MD_AMY_PLON;
		pwp->mj.reqaction = 38;
		//EV_SetAction(playertp[0], &action_a_sowewr0, NULL, 0.25f, 0, 0);
		twp->ang.z = 0;
		twp->ang.x = 0;
		PClearSpeed(mwp, pwp);
		twp->flag &= 0xDAFFu;
		return TRUE;

	case PL_OP_STOPSHOWER:
		twp->mode = MD_AMY_PLON;
		pwp->mj.reqaction = 39;
		return TRUE;

	case PL_OP_SHAKEMUDOUT:
		return TRUE;

		twp->mode = MD_AMY_PLON;
		pwp->mj.reqaction = 40;
		twp->ang.z = 0;
		twp->ang.x = 0;
		PClearSpeed(mwp, pwp);
		twp->flag &= 0xDAFFu;
		return TRUE;
	}

	return AmyCheckInput.Original(pwp, mwp, twp);
}



void copyAction(PL_ACTION* original, PL_ACTION * copy)
{
	copy->actptr = original->actptr;
	copy->frame = original->frame;
	copy->mtnmode = original->mtnmode;
	copy->next = original->next;
	copy->objnum = original->objnum;
	copy->racio = original->racio;
}

void checkIfShowerTime(int pnum)
{
	int pno = PLNO(playertwp[pnum]);

	if (pno != Characters_Amy)
		return;

	if (amy_action38.actptr == NULL)
	{
		copyAction(&amy_action[38], &amy_action38);
		copyAction(&amy_action[39], &amy_action39);
		copyAction(&amy_action[40], &amy_action40);

		amy_sowewr0.actptr->object = amy_action[0].actptr->object;
		amy_sowewr1.actptr->object = amy_action[0].actptr->object;
		amy_sowewr2.actptr->object = amy_action[0].actptr->object;

		
		AmyCheckInput.Hook(AmyCheckInput_r);
	}

	if (playertwp[pnum]->smode == PL_OP_STARTSHOWER ||
		playertwp[pnum]->smode == PL_OP_STOPSHOWER ||
		playertwp[pnum]->smode == PL_OP_SHAKEMUDOUT)
	{
		if (!isInShower)
		{
			//Do a little replacing.
			amy_action[38] = amy_sowewr0;
			amy_action[39] = amy_sowewr1;
			amy_action[40] = amy_sowewr2;
			isInShower = true;
		}
	}
	else
	{
		if (isInShower)
		{
			amy_action[38] = amy_action38;
			amy_action[39] = amy_action39;
			amy_action[40] = amy_action40;
			isInShower = false;
		}
	}

}

