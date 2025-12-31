
#include "pch.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include "deejay-shower.h"

static Sint32 SAL_casinoshowerfallspeed = 40;
static Float SAL_casinoshowermizuspdofs = 1.3f;
static Float SAL_casinoshowermizuspd = 0.4f;
static Float SAL_casinoshowermizurad = 0.8f;
static Float SAL_casinoshowermudsub = 0.002f;
static Sint32 SAL_casinoshowermizunum = 2;
static Sint32 SAL_casinoshowerstartframe = 60;
static Sint32 SAL_casinoshowerendframe = 500;


static void deejayShowerExec(task* tp)
{
	taskwk* twp = tp->twp;

    float dst = njDistanceP2P(&twp->pos, &camera_twp->pos);

    if (dst < 180)
    {
        dsPlay_timer(SE_CA_SHOWER, (Sint32)twp, 1, 0, 10);

        NJS_VECTOR spdofs = { 0.125f, 22.5f, -6.55f };
        NJS_VECTOR pos = { 0.125f, 22.5f, -6.55f };
        njUnitVector(&spdofs);
        spdofs.x *= -SAL_casinoshowermizuspdofs;
        spdofs.y *= -SAL_casinoshowermizuspdofs;
        spdofs.z *= -SAL_casinoshowermizuspdofs;
        Angle r1 = NJM_DEG_ANG(njRandom() * 1520.0f);
        Angle r2 = (Angle)(njRandom() * 90.0f);
        Float mizurad = njSin(r2) * SAL_casinoshowermizurad * 0.3f + SAL_casinoshowermizurad * 0.7f;
        pos.x = njCos(r1) * mizurad + pos.x;
        pos.z = njSin(r1) * mizurad + pos.z;
        njPushMatrix(_nj_unit_matrix_);
        njTranslateV(0, &twp->pos);
        ROTATEY(0, twp->ang.y);
        njCalcVector(0, &spdofs, &spdofs);
        njCalcPoint(0, &pos, &pos);
        njPopMatrix(1);

        if (playerpwp[0])
        {
            for (Sint32 i = 0; i < SAL_casinoshowermizunum; ++i)
            {
                CreateMizu1(&pos, &spdofs, SAL_casinoshowermizuspd, playerpwp[0]->shadow.y_bottom);
            }
        }
    }

    if (ssActNumber)
        return;
}

task* createDeejayShower()
{
    task* shower = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, deejayShowerExec);
    shower->exec = deejayShowerExec;

    return shower;
}