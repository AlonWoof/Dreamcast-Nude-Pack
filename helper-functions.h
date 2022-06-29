#pragma once

#include <SADXModLoader.h>



void updateTime();
float getDeltaTime();

float clampFloat(float target, float min, float max);
float clampFloat01(float target);
void fixPartnerCollisions();
