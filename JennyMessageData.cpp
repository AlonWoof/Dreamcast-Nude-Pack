#include <SADXModLoader.h>
#include "pch.h"

const char* msg_SonicIntro[] =
{
	"It's the fast boyo himself!\nHow's it going, Sonic?", 
	"I've been a fan of your games \n since I was 10 years old!", 
	NULL
};

const char* msg_SonicMain[] =
{
	"\aかこいい～！", 
	NULL
};

const char** msg_Sonic[] =
{
	msg_SonicIntro,
	msg_SonicMain
};


const char* msg_TailsIntro[] =
{
	"Wow, it's Tails!", "Such a cute fox! And so smart!", 
	NULL
};

const char* msg_TailsMain[] =
{
	"\aI can practically see the \n\aintelligence in your eyes.", 
	"\aYou have a bright future\n\aahead of you, young man!", 
	NULL
};

const char** msg_Tails[] =
{
	msg_TailsIntro,
	msg_TailsMain
};


const char* msg_AmyIntro[] =
{
	"Amy? Amy Rose, in the flesh?", 
	"\aWow, you look so soft!\nCan I pet you?", 
	NULL
};

const char* msg_AmyMain[] =
{
	"You're a nudist, too?", 
	"\aはは、そうはかわいいね。\n今日の天気は気持ちいい、ね？", 
	NULL
};

const char** msg_Amy[] =
{
	msg_AmyIntro,
	msg_AmyMain
};

const char* msg_DefaultMsg[] =
{
	"This is a default message.",
	"\aBecause crashing the game is no fun.",
	NULL
};

const char** msg_Default[] =
{
	msg_DefaultMsg,
	msg_DefaultMsg
};

const char*** msg_Character[] =
{
	msg_Sonic,
	msg_Default,
	msg_Tails,
	msg_Default,
	msg_Default,
	msg_Amy,
	msg_Default,
	msg_Default
};


