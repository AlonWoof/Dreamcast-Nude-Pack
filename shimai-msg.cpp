#include "pch.h"
#include "shimai-msg.h"

#pragma region JennyPoolside

const char* m_ADVSS06_JSI[] =
{
	"It's the fast boyo himself!\nHow's it going, Sonic?",
	"I've been a fan of your games \n since I was 10 years old!",
	NULL
};

const char* m_ADVSS06_JSM[] =
{
	"\aかこいい～！",
	NULL
};

const char** msg_ADVSS06_JS[] =
{
	m_ADVSS06_JSI,
	m_ADVSS06_JSM
};

const char* m_ADVSS06_JTI[] =
{
	"Wow, it's Tails!", "Such a cute fox! And so smart!",
	NULL
};

const char* m_ADVSS06_JTM[] =
{
	"\aI can practically see the \n\aintelligence in your eyes.",
	"\aYou have a bright future\n\aahead of you, young man!",
	NULL
};

const char** msg_ADVSS06_JT[] =
{
	m_ADVSS06_JTI,
	m_ADVSS06_JTM
};

const char* m_ADVSS06_JAI[] =
{
	"Amy? Amy Rose, in the flesh?",
	"\aWow, you look so soft!\nCan I pet you?",
	NULL
};

const char* m_ADVSS06_JAM[] =
{
	"You're a nudist, too?",
	"\aはは、そうはかわいいね。\n今日の天気は気持ちいい、ね？",
	NULL
};

const char** msg_ADVSS06_JA[] =
{
	m_ADVSS06_JAI,
	m_ADVSS06_JAM
};

const char* m_ADVSS06_JKI[] =
{
	"Knock knock, it's Knuckles!",
	"\aI don't care what anyone says.\a\nI think the treasure hunting segments are fun!",
	NULL
};

const char* m_ADVSS06_JKM[] =
{
	"Seen Rouge lately?",
	"\aShe doesn't hate you at all, you know.\n Quite the opposite.",
	"\aBoys are adorably oblivious sometimes...",
	NULL
};

const char** msg_ADVSS06_JK[] =
{
	m_ADVSS06_JKI,
	m_ADVSS06_JKM
};

const char* m_ADVSS06_JBI[] =
{
	"Woah, Big the Cat!",
	"\aI've always loved your chill demeanor.\nWe should totally go fishing together sometime.",
	NULL
};

const char* m_ADVSS06_JBM[] =
{
	"Thanks for always protecting Cream and Amy.",
	"\aYou're such a good nii-chan~",
	NULL
};

const char** msg_ADVSS06_JB[] =
{
	m_ADVSS06_JBI,
	m_ADVSS06_JBM
};

const char* m_ADVSS06_JEI[] =
{
	"E-102 Gamma...",
	"\aPlease take care of yourself, dear...\nThere's a pure soul inside this machine.",
	NULL
};

const char* m_ADVSS06_JEM[] =
{
	"I... I'm sorry...",
	"\aI need a moment...",
	NULL
};

const char** msg_ADVSS06_JE[] =
{
	m_ADVSS06_JEI,
	m_ADVSS06_JEM
};

const char* m_JDEF[] =
{
	"This is a default message.",
	"\aBecause crashing the game is no fun.",
	NULL
};

const char** msg_ADVSS06_Def[] =
{
	m_JDEF,
	m_JDEF
};


ShimaiMessagePool JennyPoolsideMessages = 
{
	msg_ADVSS06_JS,		//Sonic
	msg_ADVSS06_Def,	//Eggman
	msg_ADVSS06_JT,		//Tails
	msg_ADVSS06_JK,		//Knux
	msg_ADVSS06_Def,	//Tikal
	msg_ADVSS06_JA,		//Amy
	msg_ADVSS06_JE,		//Gamma
	msg_ADVSS06_JB		//Big
};

#pragma endregion

#pragma region DeejayPoolside

const char* m_ADVSS06_DSI[] =
{
	"\aOnee-chan took me to\n\athe hotel pool today! So happy~",
	NULL
};

const char* m_ADVSS06_DSM[] =
{
	"\aSwimming is fun!\n\aEspecially nakie swimming~",
	NULL
};

const char** msg_ADVSS06_DS[] =
{
	m_ADVSS06_DSI,
	m_ADVSS06_DSM
};

const char* m_ADVSS06_DTI[] =
{
	"EEEEEEEEEEEEEEEEEEEEEEEEEE!", 
	"TAILS, YOU'RE MY FAVORITE!",
	NULL
};

const char* m_ADVSS06_DTM[] =
{
	"\aCan I go to your workshop? Please?",
	"\aI'm sure onee-chan\nwould like to go, too!",
	NULL
};

const char** msg_ADVSS06_DT[] =
{
	m_ADVSS06_DTI,
	m_ADVSS06_DTM
};

const char* m_ADVSS06_DAI[] =
{
	"Amy! You're so cute and pink!",
	"\aAnd you got a big hammer!\nYou're really strong, huh?",
	NULL
};

const char* m_ADVSS06_DAM[] =
{
	"Wanna swim nakie with me?",
	NULL
};

const char** msg_ADVSS06_DA[] =
{
	m_ADVSS06_DAI,
	m_ADVSS06_DAM
};

const char* m_ADVSS06_DEI[] =
{
	"\aWoah, what a huge robot!",
	"\aDid Eggman make you?\nI can tell you're actually nice, though!",
	NULL
};

const char* m_ADVSS06_DEM[] =
{
	"\aFuck Eggman!",
	NULL
};

const char** msg_ADVSS06_DE[] =
{
	m_ADVSS06_DEI,
	m_ADVSS06_DEM
};

const char* m_DDEF[] =
{
	"This is a default message.",
	"\aBecause crashing the game is no fun.",
	NULL
};


ShimaiMessagePool DeejayPoolsideMessages =
{
	msg_ADVSS06_DS,		//Sonic
	msg_ADVSS06_Def,	//Eggman
	msg_ADVSS06_DT,		//Tails
	msg_ADVSS06_DS,		//Knux
	msg_ADVSS06_Def,	//Tikal
	msg_ADVSS06_DA,		//Amy
	msg_ADVSS06_DE,		//Gamma
	msg_ADVSS06_DS		//Big
};

const char* m_ADVSS06_DChairI[] =
{
	"Onee-chan... I love you~",
	NULL
};

const char* m_ADVSS06_DChairM[] =
{
	"Awawawawa... so soft...",
	NULL
};

const char** msg_ADVSS06_DChair[] =
{
	m_ADVSS06_DChairI,
	m_ADVSS06_DChairM
};

ShimaiMessagePool DeejayPoolChairMessages =
{
	msg_ADVSS06_DChair,		//Sonic
	msg_ADVSS06_DChair,	//Eggman
	msg_ADVSS06_DChair,		//Tails
	msg_ADVSS06_DChair,		//Knux
	msg_ADVSS06_DChair,	//Tikal
	msg_ADVSS06_DChair,		//Amy
	msg_ADVSS06_DChair,		//Gamma
	msg_ADVSS06_DChair		//Big
};



const char* m_ADVSS03_JSI[] =
{
	"...Where'd the witch go...",
	NULL
};

const char* m_ADVSS03_JSF[] =
{
	"I need to protect the people of this city.",
	"\aI need to protect Deejay...",
	NULL
};

const char** msg_ADVSS03_JS[] =
{
	m_ADVSS03_JSI,
	m_ADVSS03_JSF
};


ShimaiMessagePool JennyMSSewerMessages =
{
	msg_ADVSS03_JS,		//Sonic
	msg_ADVSS03_JS,	//Eggman
	msg_ADVSS03_JS,		//Tails
	msg_ADVSS03_JS,		//Knux
	msg_ADVSS03_JS,	//Tikal
	msg_ADVSS03_JS,		//Amy
	msg_ADVSS03_JS,		//Gamma
	msg_ADVSS03_JS		//Big
};

#pragma endregion

#pragma region JennyMysticRuins
const char* m_ADVMR00_JSI[] =
{
	"\aThe breeze here feels good on my skin~",
	"\aI wonder if it's really OK \nfor me to be nude here?",
	NULL
};

const char* m_ADVMR00_JSM[] =
{
	"\aI mean, the researchers don't mind...\n\aOne ojisan even called me \"cute\"!",
	NULL
};

const char** msg_ADVMR00_JS[] =
{
	m_ADVMR00_JSI,
	m_ADVMR00_JSM
};

const char* m_ADVMR00_JTI[] =
{
	"Wow, it's Tails!", "Such a cute fox! And so smart!",
	NULL
};

const char* m_ADVMR00_JTM[] =
{
	"\aI can practically see the \n\aintelligence in your eyes.",
	"\aYou have a bright future\n\aahead of you, young man!",
	NULL
};

const char** msg_ADVMR00_JT[] =
{
	m_ADVMR00_JTI,
	m_ADVMR00_JTM
};

const char* m_ADVMR00_JAI[] =
{
	"Amy? Amy Rose, in the flesh?",
	"\aWow, you look so soft!\nCan I pet you?",
	NULL
};

const char* m_ADVMR00_JAM[] =
{
	"You're a nudist, too?",
	"\aはは、そうはかわいいね。\n今日の天気は気持ちいい、ね？",
	NULL
};

const char** msg_ADVMR00_JA[] =
{
	m_ADVMR00_JAI,
	m_ADVMR00_JAM
};

const char* m_ADVMR00_JKI[] =
{
	"Knock knock, it's Knuckles!",
	"\aI don't care what anyone says.\a\nI think the treasure hunting segments are fun!",
	NULL
};

const char* m_ADVMR00_JKM[] =
{
	"Seen Rouge lately?",
	"\aShe doesn't hate you at all, you know.\n Quite the opposite.",
	"\aBoys are adorably oblivious sometimes...",
	NULL
};

const char** msg_ADVMR00_JK[] =
{
	m_ADVMR00_JKI,
	m_ADVMR00_JKM
};

const char* m_ADVMR00_JBI[] =
{
	"Woah, Big the Cat!",
	"\aI've always loved your chill demeanor.\nWe should totally go fishing together sometime.",
	NULL
};

const char* m_ADVMR00_JBM[] =
{
	"Thanks for always protecting Cream and Amy.",
	"\aYou're such a good nii-chan~",
	NULL
};

const char** msg_ADVMR00_JB[] =
{
	m_ADVMR00_JBI,
	m_ADVMR00_JBM
};

const char* m_ADVMR00_JEI[] =
{
	"E-102 Gamma...",
	"\aPlease take care of yourself, dear...\nThere's a pure soul inside this machine.",
	NULL
};

const char* m_ADVMR00_JEM[] =
{
	"I... I'm sorry...",
	"\aI need a moment...",
	NULL
};

const char** msg_ADVMR00_JE[] =
{
	m_ADVMR00_JEI,
	m_ADVMR00_JEM
};


ShimaiMessagePool JennyMysticRuinsMessages =
{
	msg_ADVMR00_JS,		//Sonic
	msg_ADVSS06_Def,	//Eggman
	msg_ADVMR00_JS,		//Tails
	msg_ADVMR00_JK,		//Knux
	msg_ADVSS06_Def,	//Tikal
	msg_ADVMR00_JA,		//Amy
	msg_ADVMR00_JE,		//Gamma
	msg_ADVMR00_JB		//Big
};


const char* m_ADVMR01_JSI[] =
{
	"\aWhat a garish construction...",
	"\aAnd he plastered his face all\nover it as per usual for him.",
	NULL
};

const char* m_ADVMR01_JSM[] =
{
	"\aI hope Sonic blows it up.",
	NULL
};

const char** msg_ADVMR01_JS[] =
{
	m_ADVMR01_JSI,
	m_ADVMR01_JSM
};

ShimaiMessagePool JennyMSJungleMessages =
{
	msg_ADVMR01_JS,		//Sonic
	msg_ADVSS06_Def,	//Eggman
	msg_ADVMR01_JS,		//Tails
	msg_ADVMR01_JS,		//Knux
	msg_ADVSS06_Def,	//Tikal
	msg_ADVMR01_JS,		//Amy
	msg_ADVMR01_JS,		//Gamma
	msg_ADVMR01_JS		//Big
};

#pragma endregion

#pragma region JennyEggCarrierPool
const char* m_ADVEC05_JSI[] =
{
	"Deejay, get out of the pool!\nWe're gonna get caught!",
	"Eggman's gonna be pissed we \nsnuck on to his ship!",
	NULL
};

const char* m_ADVEC05_JSM[] =
{
	"Like, what are the chances it took\noff right as we were checking it out?",
	"My little sis has no sense \nof danger, I swear...",
	NULL
};

const char** msg_ADVEC05_JS[] =
{
	m_ADVEC05_JSI,
	m_ADVEC05_JSM
};

const char* m_ADVEC05_DSI[] =
{
	"Fuck Eggman!",
	NULL
};


const char** msg_ADVEC05_DS[] =
{
	m_ADVEC05_DSI,
	m_ADVEC05_DSI
};


ShimaiMessagePool JennyEggCarrierPoolMessages =
{
	msg_ADVEC05_JS,		//Sonic
	msg_ADVEC05_JS,		//Eggman
	msg_ADVEC05_JS,		//Tails
	msg_ADVEC05_JS,		//Knux
	msg_ADVEC05_JS,		//Tikal
	msg_ADVEC05_JS,		//Amy
	msg_ADVEC05_JS,		//Gamma
	msg_ADVEC05_JS		//Big
};

#pragma endregion

#pragma region EmeraldCoastAct3

const char* m_S01A02_JSI[] =
{
	"We found a rather nice little\ncove to relax in.",
	"Look at all these beautiful fish!\nNature is amazing~",
	NULL
};

const char* m_S01A02_JSM[] =
{
	"Glad my little sis is happy, too!",
	NULL
};

const char** msg_S01A02_JS[] =
{
	m_S01A02_JSI,
	m_S01A02_JSM
};

ShimaiMessagePool JennyEmeraldCoastMessages =
{
	msg_S01A02_JS,		//Sonic
	msg_S01A02_JS,	    //Eggman
	msg_S01A02_JS,		//Tails
	msg_S01A02_JS,		//Knux
	msg_S01A02_JS,	    //Tikal
	msg_S01A02_JS,		//Amy
	msg_S01A02_JS,		//Gamma
	msg_S01A02_JS		//Big
};

const char* m_S01A02_DSI[] =
{
	"Wow, look at the colorful fishies!\nCan I have one as a pet?",
	NULL
};

const char* m_S01A02_DSM[] =
{
	"I wanna stay here all day!\nBut I got school tomorrow, huh...",
	NULL
};

const char** msg_S01A02_DS[] =
{
	m_S01A02_DSI,
	m_S01A02_DSM
};

ShimaiMessagePool DeejayEmeraldCoastMessages =
{
	msg_S01A02_DS,		//Sonic
	msg_S01A02_DS,		//Eggman
	msg_S01A02_DS,		//Tails
	msg_S01A02_DS,		//Knux
	msg_S01A02_DS,		//Tikal
	msg_S01A02_DS,		//Amy
	msg_S01A02_DS,		//Gamma
	msg_S01A02_DS		//Big
};

#pragma endregion

#pragma region CasinoAct1

const char* m_S09A00_JSI[] =
{
	"Deejay showers with her glasses on.\nShe's so silly!",
	NULL
};

const char* m_S09A00_JSM[] =
{
	"I'm surprised they let us into this casino.\nI'm not even old enough to drive...",
	"They let us enter completely naked, too!",
	NULL
};

const char** msg_S09A00_JS[] =
{
	m_S09A00_JSI,
	m_S09A00_JSM
};

ShimaiMessagePool JennyCasinoMessages =
{
	msg_S09A00_JS,		//Sonic
	msg_S09A00_JS,	    //Eggman
	msg_S09A00_JS,		//Tails
	msg_S09A00_JS,		//Knux
	msg_S09A00_JS,	    //Tikal
	msg_S09A00_JS,		//Amy
	msg_S09A00_JS,		//Gamma
	msg_S09A00_JS		//Big
};

const char* m_S09A00_DSI[] =
{
	"Warm... waaaterrr...",
	"Feels goooood....",
	NULL
};

const char* m_S09A00_DSM[] =
{
	"Awawawawawawa...",
	NULL
};

const char** msg_S09A00_DS[] =
{
	m_S09A00_DSI,
	m_S09A00_DSM
};

ShimaiMessagePool DeejayCasinoMessages =
{
	msg_S09A00_DS,		//Sonic
	msg_S09A00_DS,		//Eggman
	msg_S09A00_DS,		//Tails
	msg_S09A00_DS,		//Knux
	msg_S09A00_DS,		//Tikal
	msg_S09A00_DS,		//Amy
	msg_S09A00_DS,		//Gamma
	msg_S09A00_DS		//Big
};

#pragma endregion

#pragma region FinalEgg

const char* m_S10A02_JSI[] =
{
	"That familiar...\nWhere'd it run off to?",
	"It was here yesterday...",
	NULL
};

const char* m_S10A02_JSM[] =
{
	"It kinda looked like a duck...?",
	NULL
};

const char** msg_S10A02_JS[] =
{
	m_S10A02_JSI,
	m_S10A02_JSM
};

ShimaiMessagePool JennyFinalEggMessages =
{
	msg_S10A02_JS,		//Sonic
	msg_S10A02_JS,	    //Eggman
	msg_S10A02_JS,		//Tails
	msg_S10A02_JS,		//Knux
	msg_S10A02_JS,	    //Tikal
	msg_S10A02_JS,		//Amy
	msg_S10A02_JS,		//Gamma
	msg_S10A02_JS		//Big
};

#pragma endregion

#pragma region DestinyIslands

const char* m_DI_JSI[] =
{
	"Aah, the breeze feels great!\nEspecially on my bare skin~",
	NULL
};

const char* m_DI_JSM[] =
{
	"This place is so nice... \nAnd the chao are so cute!",
	"Now, if only we had some sea-salt icecream...",
	NULL
};

const char** msg_DI_JS[] =
{
	m_DI_JSI,
	m_DI_JSM
};

const char* m_DI_DSI[] =
{
	"The sun is sooo hot,\nbut the water is sooo cold!",
	"Onee-chan should swim with me!",
	NULL
};

const char* m_DI_DSM[] =
{
	"Maybe we could get ice cream after!",
	"What kind do you like?",
	NULL
};


const char** msg_DI_DS[] =
{
	m_DI_DSI,
	m_DI_DSM
};

ShimaiMessagePool JennyDestinyIslandsMessages =
{
	msg_DI_JS,		//Sonic
	msg_DI_JS,	    //Eggman
	msg_DI_JS,		//Tails
	msg_DI_JS,		//Knux
	msg_DI_JS,	    //Tikal
	msg_DI_JS,		//Amy
	msg_DI_JS,		//Gamma
	msg_DI_JS		//Big
};

ShimaiMessagePool DeejayDestinyIslandsMessages =
{
	msg_DI_DS,		//Sonic
	msg_DI_DS,	    //Eggman
	msg_DI_DS,		//Tails
	msg_DI_DS,		//Knux
	msg_DI_DS,	    //Tikal
	msg_DI_DS,		//Amy
	msg_DI_DS,		//Gamma
	msg_DI_DS		//Big
};

const char* m_DI_JSI_Tree[] =
{
	"She tried to climb the tree.\nThen she got tired halfway up.",
	NULL
};

const char* m_DI_JSM_Tree[] =
{
	"I've heard legends about that fruit.",
	"I think I wanna try it myself~",
	NULL
};

const char** msg_DI_JS_Tree[] =
{
	m_DI_JSI_Tree,
	m_DI_JSM_Tree
};

const char* m_DI_DSI_Tree[] =
{
	"Star-shaped fruit...\nSo kawaii...",
	"...Must... get...",
	NULL
};

const char* m_DI_DSM_Tree[] =
{
	"I give up for now.\nSwimming drained my energies.",
	NULL
};


const char** msg_DI_DS_Tree[] =
{
	m_DI_DSI_Tree,
	m_DI_DSM_Tree
};

ShimaiMessagePool JennyDestinyIslandsMessages_Tree =
{
	msg_DI_JS_Tree,		//Sonic
	msg_DI_JS_Tree,	    //Eggman
	msg_DI_JS_Tree,		//Tails
	msg_DI_JS_Tree,		//Knux
	msg_DI_JS_Tree,	    //Tikal
	msg_DI_JS_Tree,		//Amy
	msg_DI_JS_Tree,		//Gamma
	msg_DI_JS_Tree		//Big
};

ShimaiMessagePool DeejayDestinyIslandsMessages_Tree =
{
	msg_DI_DS_Tree,		//Sonic
	msg_DI_DS_Tree,	    //Eggman
	msg_DI_DS_Tree,		//Tails
	msg_DI_DS_Tree,		//Knux
	msg_DI_DS_Tree,	    //Tikal
	msg_DI_DS_Tree,		//Amy
	msg_DI_DS_Tree,		//Gamma
	msg_DI_DS_Tree		//Big
};

#pragma endregion
