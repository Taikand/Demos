#pragma once
#include "pch.h"
#include "DataContainers.h"

#include <DirectXMath.h>

struct CameraBuffer
{
	DirectX::XMMATRIX view;
};
class Camera
{
private:
	Tungsten::Vector<2,float> pitchRoll;
	
	__declspec(align(16))	DirectX::XMVECTOR lookAt;
	__declspec(align(16))	DirectX::XMVECTOR position;
	__declspec(align(16))	DirectX::XMVECTOR up;
	__declspec(align(16))	DirectX::XMMATRIX matrix;
	float aspectRatio;
public:
	Camera(void);
	~Camera(void);
	DirectX::
	XMMATRIX*		GetCameraMatrix		();
	DirectX::
	XMMATRIX		GetProjection		();
	Tungsten::
	Vector<4>		GetLookAt			();
	void			SetLookAt			(float x,float y,float z);
	void			SetPosition			(float x,float y,float z);
	void			SetUp				(float x,float y,float z);
	//Pass relative Deltas
	void			SetPerspectiveDelta	(float x,float y);
	void			MoveRelative		(float x,float y,float z);	
	Tungsten::
	Vector<3>		GetPosition			();	
	Tungsten::
	Vector<2>		GetOrientation		();
	void			SetAspectRatio		(float aspectRatio);
	void			MoveAbsolute		(Tungsten::Vector<2> absoluteCoords);
	DirectX::
	XMMATRIX		GetView				();
	
};
