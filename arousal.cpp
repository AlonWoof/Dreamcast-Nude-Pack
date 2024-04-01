
#include <cmath>

#include "pch.h"
#include "arousal.h"
#include "helper-functions.h"
#include "world-location.h"


float arousalLevel[Characters_MetalSonic];

WorldLocation CasinoShowersLocation = { LevelIDs_Casinopolis, 0, {-246.0f, -199.0f, -548.0f}, 200.0f };
WorldLocation TailsWorkshopLocation = { LevelIDs_MysticRuins, 0, {1476.0f, 200.0f, 772.0f}, 500.0f };

extern BodyState playerBodyStates[Characters_MetalSonic];

//Practically on top of each other... hoo boy.... 
const float rubbingDistance = 50.0f;

const float gHornyMultiplier[]
{
	0.45f, //Characters_Sonic
	0.0f,
	0.35f, //Characters_Tails
	0.1f,  //Characters_Knuckles
	0.0f,
	1.0f, //Characters_Amy
	0.0f,
	0.05f,  //Characters_Big
	0.0f
};

const float gArousalDecay[]
{
	0.0019f, //Characters_Sonic
	0.0f,
	0.0026f, //Characters_Tails
	0.014f,  //Characters_Knuckles
	0.0f,
	0.0015f, //Characters_Amy
	0.0f,	 
	0.003f,  //Characters_Big
	0.0f
};

/*
* 	Characters_Sonic,
	Characters_Eggman,
	Characters_Tails,
	Characters_Knuckles,
	Characters_Tikal,
	Characters_Amy,
	Characters_Gamma,
	Characters_Big,
	Characters_MetalSonic
*/

WorldLocation coldPlaces[] =
{
	{LevelIDs_MysticRuins,1,{-1428.0f,68.2f,358.20f},700.0f}
};

WorldLocation privatePlaces[] =
{
	{LevelIDs_MysticRuins,2,{0.0f,0.0f,0.0f},80000.0f},
	{LevelIDs_MysticRuins,1,{0.0f,0.0f,0.0f},80000.0f},
	{LevelIDs_MysticRuins,0,{0.0f,0.0f,0.0f},80000.0f},

	//Behind the walls at town hall.
	{LevelIDs_StationSquare,0,{393.0f, 0.0f, 448.0f},80.0f},
	{LevelIDs_StationSquare,0,{160.0f, 0.0f, 448.0f},80.0f},

	//Behind the Twinkle Park entrance
	{LevelIDs_StationSquare,3,{690.0f, 0.0f, 1598.0f},100.0f},

	//Tails Jet Anklet location
	{LevelIDs_StationSquare,3,{662.0f, 56.0f, 1270.0f},60.0f},

	//Alley by Casinopolis
	{LevelIDs_StationSquare,1,{-701.0f, 0.0f, 1330.0f},200.0f},

	{LevelIDs_SSGarden, 0, {0.0f, 0.0f, 0.0f}, 10000.0f},
	{LevelIDs_MRGarden, 0, {0.0f, 0.0f, 0.0f}, 10000.0f},
	{LevelIDs_ECGarden, 0, {0.0f, 0.0f, 0.0f}, 10000.0f},

	//Tails workshop
	{ LevelIDs_MysticRuins, 0, {1476.0f, 200.0f, 772.0f}, 200.0f },

	//Casinopolis showers
	CasinoShowersLocation
};

WorldLocation repulsivePlaces[] =
{
	//Casinopolis trash zone
	{ LevelIDs_Casinopolis, 1, {0.0f, 0.0f, 0.0f}, 2000000.0f },

	//Station Square sewers
	{ LevelIDs_StationSquare, 2, {0.0f, 0.0f, 0.0f}, 2000000.0f }
};



void initializeTheHorny()
{
	for (int i = 0; i < Characters_MetalSonic; i++)
	{
		arousalLevel[i] = 0.0f;
	}
}

	bool isRepulsivePlace()
	{
		//Ew gross
		for (WorldLocation wl : repulsivePlaces)
		{
			if (isInLocation(&wl))
				return true;
		}

		return false;
	}

	bool isColdPlace()
	{
		//And they say it gets colder, you're bundled up now wait til you get older
		if (CurrentLevel == LevelIDs_IceCap || CurrentLevel == LevelIDs_SkyDeck)
			return true;

		if (CurrentLevel == LevelIDs_EggCarrierOutside && !IsEggCarrierSunk() && CurrentAct != 3 && CurrentAct != 5 && CurrentAct != 4)
			return true;

	
		for(WorldLocation wl : coldPlaces)
		{
			if (isInLocation(&wl))
				return true;
		}

		return false;
	}

	bool isCrowdedPlace()
	{
		if (CurrentLevel == LevelIDs_StationSquare)
			return true;

		return false;
	}

	bool isSecludedPlace()
	{
		//Secluded places are good.

		for (WorldLocation wl : privatePlaces)
		{
			if (isInLocation(&wl))
			{
				return true;
			}
		}

		if (CurrentLevel == LevelIDs_StationSquare && CurrentAct != 2 && CurrentAct != 5)
			return false;

		return false;
	}

float getAttractionMultiplier(char playerID, char partnerID)
{
	//Shipping tiiiimmmeeeee

	if (playerID == Characters_Sonic)
	{
		//Little buddy <3
		if (partnerID == Characters_Tails)
			return 0.85f;

		//Knuckles is kinda hot too
		if (partnerID == Characters_Knuckles)
			return 0.2f;

		//Amy is... well, OK, she's kinda cute.
		if (partnerID == Characters_Amy)
			return 0.3f;
	}

	if (playerID == Characters_Tails)
	{
		//ソニックはちょっとセクシーだな…
		if (partnerID == Characters_Sonic)
			return 1.0f;

		//I totally ship it.
		if (partnerID == Characters_Amy)
			return 0.76f;

		//That thing is at eye level....
		if (partnerID == Characters_Big)
			return 0.1f;
	}

	if (playerID == Characters_Knuckles)
	{
		//I bet he's really tsundere about it
		if (partnerID == Characters_Sonic)
			return 0.214f;

		//A-a girl.... *sweats*
		if (partnerID == Characters_Amy)
			return 1.25f;
	}

	if (playerID == Characters_Amy)
	{
		//I mean, duh. 
		if (partnerID == Characters_Sonic)
			return 2.0f;

		//2nd fave ship~
		if (partnerID == Characters_Tails)
			return 0.85f;

		//That thing is at eye level....
		if (partnerID == Characters_Big)
			return 0.185f;

	}

	return 0.005f;
}

void updatePartnerDistance()
{
	if (!playertwp[0])
		return;

	if (!playertwp[1])
		return;

	if (!playermwp[1])
		return;

	float dist = GetPlayerDistance((EntityData1*)playertwp[1],0);

	//Oh boy things are touching... >///>
	if (dist < rubbingDistance)
	{
		float arousalAdded = (0.0352 * getAttractionMultiplier(playertwp[0]->counter.b[1], playertwp[1]->counter.b[1]));
		arousalLevel[playertwp[0]->counter.b[1]] += arousalAdded * gHornyMultiplier[playertwp[0]->counter.b[1]] * getDeltaTime();

		arousalAdded = (0.0340 * getAttractionMultiplier(playertwp[1]->counter.b[1], playertwp[0]->counter.b[1]));
		arousalLevel[playertwp[1]->counter.b[1]] += arousalAdded * gHornyMultiplier[playertwp[1]->counter.b[1]] * getDeltaTime();

		//DisplayDebugStringFormatted(NJM_LOCATION(8, 10), "Standing close...");
	}

}

void DBG_ShowArousalLevels()
{

	DisplayDebugStringFormatted(NJM_LOCATION(2, 18), "Sonic Arousal: %f ", arousalLevel[Characters_Sonic]);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 19), "Tails Arousal: %f ", arousalLevel[Characters_Tails]);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 20), "Knuckles Arousal: %f ", arousalLevel[Characters_Knuckles]);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 21), "Amy Arousal: %f ", arousalLevel[Characters_Amy]);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 22), "Big Arousal: %f ", arousalLevel[Characters_Big]);

}

void calculateIncidentalArousal()
{

	for (int i = 0; i < Characters_MetalSonic; i++)
	{
		int chance = 100;

		switch (i)
		{
		
		//Sonic is only 8% horny
		case Characters_Sonic:
			chance = 8;
			break;
		
		//Tails is 5% horny
		case Characters_Tails:
			chance = 5;
			break;
		
		//Knux is super serious so even less for him.
		case Characters_Knuckles:
			chance = 2;
			break;

		//Amy has 10% because she horny as heck
		case Characters_Amy:
			chance = 10;
			break;

		//The elusive catboner
		case Characters_Big:
			chance = 1;
			break;

		}

		int rng = random(0, 100);

		if (rng <= chance)
		{
			arousalLevel[i] = 1.0f;
		}
		else
		{
			arousalLevel[i] = 0.0f;
		}

	}
}

void ArousalLogic_Common()
{

	if (ChkPause())
		return;

	for (int i = 0; i < 8; i++)
	{
		if (playertwp[i])
		{
			int plnum = playertwp[i]->counter.b[1];

			if (isColdPlace())
				arousalLevel[plnum] -= (0.0015f * getDeltaTime());

			if (isRepulsivePlace())
				arousalLevel[plnum] = -1.0f;

			if (ssStageNumber == STAGE_AL_GARDEN00_SS ||
				ssStageNumber == STAGE_AL_GARDEN01_EC ||
				ssStageNumber == STAGE_AL_GARDEN02_MR)
			{
				//Do not the chao. Please.
				arousalLevel[plnum] = -1.0f;
			}

			if (isCrowdedPlace() && !isSecludedPlace() && plnum != Characters_Amy)
			{
				if (arousalLevel[plnum] > 0.0f)
					arousalLevel[plnum] -= (gArousalDecay[plnum] * getDeltaTime());
			}
			
		}
	}

	for (int i = 0; i < Characters_MetalSonic; i++)
	{
		
		#ifdef DEBUG
				njPrint(NJM_LOCATION(5, 8 + i), "Character %i arousal level: %f", i, arousalLevel[i]);
		#endif // DEBUG
	}



}

void ArousalLogic_Sonic()
{

}

void ArousalLogic_Tails()
{

}

void ArousalLogic_Amy()
{

	if (!playertp[0])
		return;

	float total = 0;

	/*
	if (CurrentCharacter == Characters_Amy)
	{

			if(isColdPlace())
				total -= (0.0015f * getDeltaTime());

			//The wind feels nice down there~
			if (((playerwk*)playermwp[0]->work.l)->mj.action == 29)
			{
				total += (0.003142f * getDeltaTime());
				njPrint(NJM_LOCATION(8, 10), "KIMOCHIIIII");
			}

			//She's happy to be in good company
			if (playertwp[1])
			{
				total += ((0.01253f * getAttractionMultiplier(Characters_Amy, playertwp[1]->counter.b[1])) * getDeltaTime());
			}
	}
	*/

	if (EV_CheckCansel())
	{
		if (EVENT_ID == 18 || EVENT_ID == 98 || EVENT_ID == 99)
		{
			total += 0.25f;
		}
	}

	//if (isCrowdedPlace() && !isSecludedPlace())
	//	total += 0.01f;

	if(total > 0.0f)
		arousalLevel[Characters_Amy] += ((gHornyMultiplier[Characters_Amy] * total) * getDeltaTime());


}

void updateBodyStates()
{
	ArousalLogic_Common();
	//ArousalLogic_Sonic();
	//ArousalLogic_Tails();
	//ArousalLogic_Amy();

	updatePartnerDistance();

	for (int i = 0; i < Characters_MetalSonic; i++)
	{

		arousalLevel[i] = clampFloat(arousalLevel[i], -1.0f, 1.0f);

		if (arousalLevel[i] > 0.75f)
			playerBodyStates[i] = E_Body_Aroused;
		else
			playerBodyStates[i] = E_Body_Normal;


		if(isColdPlace())
			playerBodyStates[i] = E_Body_Cold;
	}


	//Debug
	if (Controllers[0].HeldButtons & Buttons_Up)
	{
		//arousalLevel[CurrentCharacter] += (0.3342f * getDeltaTime());
	}

	if (Controllers[0].HeldButtons & Buttons_Down)
	{
		//arousalLevel[CurrentCharacter] -= (0.3342f * getDeltaTime());
	}

	if (playertwp[0] && playermwp[0])
	{
#ifdef DEBUG

		if (((playerwk*)playermwp[0]->work.l) != NULL)
			njPrint(NJM_LOCATION(5, 10), "Player Action: %i", ((playerwk*)playermwp[0]->work.l)->mj.action);
#endif // DEBUG

	}

	if (playertwp[1] && playermwp[1])
	{
#ifdef DEBUG

		if (((playerwk*)playermwp[1]->work.l) != NULL)
			njPrint(NJM_LOCATION(5, 11), "Partner Action: %i", ((playerwk*)playermwp[1]->work.l)->mj.action);
#endif // DEBUG

	}

}