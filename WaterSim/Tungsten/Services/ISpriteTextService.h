#pragma once
#include "pch.h"
#include "IImporterService.h"

namespace Tungsten
{


class ISpriteTextService
{
private:

	
public:
	virtual void Write(char* text)=0;
	virtual void Clear() = 0;
};


}