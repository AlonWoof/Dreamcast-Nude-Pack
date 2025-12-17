
#include "pch.h"

NJS_MATERIAL matlist_DJSHADOW[] = {
	{ { 0xB0FFFFFF }, { 0x00000000 }, 0, 8, NJD_D_100 | NJD_FLAG_CLAMP_V | NJD_FLAG_CLAMP_U | NJD_FLAG_USE_ALPHA | NJD_FLAG_USE_TEXTURE | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_DJSHADOW[] = {
	0, 1, 3,
	0, 3, 2
};

NJS_TEX uv_DJSHADOW[] = {
	{ 7, 247 },
	{ 7, 7 },
	{ 247, 7 },
	{ 7, 247 },
	{ 247, 7 },
	{ 247, 247 }
};

NJS_MESHSET_SADX meshlist_DJSHADOW[] = {
	{ NJD_MESHSET_3 | 0, 2, poly_DJSHADOW, NULL, NULL, NULL, uv_DJSHADOW, NULL }
};

NJS_VECTOR vertex_DJSHADOW[] = {
	{ -5, 0, -5 },
	{ -5, 0, 5 },
	{ 5, 0, -5 },
	{ 5, 0, 5 }
};

NJS_VECTOR normal_DJSHADOW[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_DJSHADOW = { vertex_DJSHADOW, normal_DJSHADOW, LengthOfArray<Sint32>(vertex_DJSHADOW), meshlist_DJSHADOW, matlist_DJSHADOW, LengthOfArray<Uint16>(meshlist_DJSHADOW), LengthOfArray<Uint16>(matlist_DJSHADOW), { 0 }, 7.071068f, NULL };

NJS_OBJECT DeeJay_Shadow = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_DJSHADOW, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };
