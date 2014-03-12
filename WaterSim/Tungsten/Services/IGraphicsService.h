#pragma once
#include "pch.h"
#include "../DataContainers.h"

#include <d3d11.h>

namespace Tungsten
{
	
class D3D11CommonState;

class IGraphicsService
{
private:
	D3D11CommonState* currentState;
	friend D3D11CommonState;
protected:
	IGraphicsService(Vector<2>& ref) :resolution(ref){};
public:
	const Vector<2>&	resolution;
//	virtual Texture		LoadTexture(WCHAR* )=0;	
	virtual void		Refresh()=0;
	virtual void		Present()=0;
	virtual void		ClearContext()=0;
	virtual Vector<2>	GetResolution()=0;
	D3D11CommonState*	GetCurrentState(){ return currentState; }
};


}