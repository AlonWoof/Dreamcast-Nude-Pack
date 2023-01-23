#pragma once

#include "body-model.h"
#include "body-functions.h"



DataPointer(int, EVENT_ID, 0x03B2C570);

void initializeTheHorny();
void updateBodyStates();
float getAttractionMultiplier();

void ArousalLogic_Common(int pno);
void ArousalLogic_Sonic(int pno);
void ArousalLogic_Tails(int pno);
void ArousalLogic_Amy(int pno);
