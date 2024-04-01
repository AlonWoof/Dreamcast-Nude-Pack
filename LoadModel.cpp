#include "pch.h"

extern const HelperFunctions* helperFunctionsGlobal;

// Hope you don't mind if I nab this bit of code, PkR
// Removes material colors from a model
void RemoveMaterialColors(NJS_OBJECT* obj)
{
	if (obj == nullptr)
		return;
	if (obj->basicdxmodel != nullptr)
	{
		for (int k = 0; k < obj->basicdxmodel->nbMat; ++k)
		{
			obj->basicdxmodel->mats[k].diffuse.argb.r = 0xFF;
			obj->basicdxmodel->mats[k].diffuse.argb.g = 0xFF;
			obj->basicdxmodel->mats[k].diffuse.argb.b = 0xFF;
		}
	}
	if (obj->child != nullptr)
		RemoveMaterialColors(obj->child);
	if (obj->sibling != nullptr)
		RemoveMaterialColors(obj->sibling);
}

NJS_OBJECT* LoadModel(const char* ModelName, WeightInfo*& weightInfo)
{
	//if (ModConfig::DebugVerbose >= DebugVerboseConfig::Models)
	PrintDebug("Loading model: %s: ", helperFunctionsGlobal->GetReplaceablePath(ModelName));
	ModelInfo* info = new ModelInfo(helperFunctionsGlobal->GetReplaceablePath(ModelName));

	weightInfo = info->getweightinfo();
	NJS_OBJECT* object = info->getmodel();

	//RemoveMaterialColors(object);

	//ProcessMaterials_Object(object);
	//if (ModConfig::DebugVerbose >= DebugVerboseConfig::Models)
	PrintDebug("OK\n");
	return object;
}

NJS_MOTION* LoadAnimation(const char* AnimationName)
{
	//if (ModConfig::DebugVerbose >= DebugVerboseConfig::Models)
	PrintDebug("Loading animation: %s: ", helperFunctionsGlobal->GetReplaceablePath(AnimationName));
	AnimationFile* animfile = new AnimationFile(helperFunctionsGlobal->GetReplaceablePath(AnimationName));
	NJS_MOTION* motion = animfile->getmotion();
	//if (ModConfig::DebugVerbose >= DebugVerboseConfig::Models)
	PrintDebug("OK\n");
	return motion;

}
