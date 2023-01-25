#pragma once
#include <SADXModLoader.h>

typedef struct
{
	Sint32 vert_number;
	float vert_weight;

}JiggleWeightInfo;

enum BodyState
{
	E_Body_Normal,
	E_Body_Aroused,
	E_Body_Cold
};

typedef struct BodyModel
{
	NJS_MODEL_SADX * body_Normal;
	JiggleWeightInfo * body_Normal_JiggleInfo;
	int bodyJiggleSize;

	NJS_MODEL_SADX * body_Aroused;

	NJS_MODEL_SADX * body_Cold;
};

