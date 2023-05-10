#pragma once

#include "body-model.h"


NJS_MODEL_SADX* getNudeBody(BodyModel* model, BodyState state);
JiggleWeightInfo** getBodyJiggleInfo(BodyModel* model, BodyState state);

void initBodySystem(const HelperFunctions& helperFunctions, const char* path);
void setPlayerBodyModels();
void setOtherNudeModels();

void addJigglePhysics(BodyModel* model, int pno);
void createJiggleTasksForPlayer(int pnum);
