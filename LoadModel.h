#pragma once
#ifndef _LOADMODEL_H_
#define _LOADMODEL_H_

#include <SADXModLoader.h>
#include <ModelInfo.h>

NJS_OBJECT* LoadModel(const char* ModelName, WeightInfo*& weightInfo);
NJS_MOTION* LoadAnimation(const char* AnimationName);

#endif
