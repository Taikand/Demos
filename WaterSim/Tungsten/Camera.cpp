#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace Tungsten;
Camera::Camera(void)
{
	
	lookAt=XMVectorSet(0.0f,0.0f,1.0f,1.0f);
	position=XMVectorSet(0.0f,0.0f,-1.0f,0.0f);
	up=XMVectorSet(0.0f,1.0f,0.0f,0.0f);
	pitchRoll.x=0.0f;
	pitchRoll.y=0.0f;
	aspectRatio=4.0f/3.0f;
}


Camera::~Camera(void)
{
}

void Camera::SetLookAt(float x,float y,float z)
{
	
	lookAt=XMVectorSet(x,y,z,0.0f);
}

void Camera::SetPosition(float x,float y,float z)
{

	position=XMVectorSet(x,y,z,0.0f);
}

void Camera::SetUp(float x,float y, float z)
{
	up=XMVectorSet(x,y,z,0.0f);
}

DirectX::XMMATRIX* Camera::GetCameraMatrix()
{

	matrix=XMMatrixLookAtLH(position,position+lookAt,up)*XMMatrixPerspectiveFovLH(XM_PI*90.0f/180.0f ,aspectRatio,0.1f,1000.0f);
	return &matrix;
}

void Camera::SetPerspectiveDelta(float x,float y)
{
	/*
	This function receives the rotation of the perspective vector, as radians.
	*/
	pitchRoll.x+=x;
	pitchRoll.x=fmodf(pitchRoll.x,XM_2PI);
	pitchRoll.y+=y;
	if(pitchRoll.y>XM_PIDIV2)	pitchRoll.y=XM_PIDIV2-0.001f;
	if(pitchRoll.y<-XM_PIDIV2)	pitchRoll.y=-XM_PIDIV2+0.001f;

	//Normalise perspective vector;
	/*float norm=perspective.x*perspective.x+perspective.y+perspective.y;
	norm=sqrt(norm);
	perspective.x/=norm;
	perspective.y/=norm;*/
	
	XMMATRIX rotation=XMMatrixRotationRollPitchYaw(pitchRoll.y,pitchRoll.x,0);
	XMVECTOR basePerspective=XMLoadFloat4(&XMFLOAT4(0.0f,0.0f,1.0f,0.0f));
	lookAt=XMVector4Transform(basePerspective,rotation);
}

Vector<3,float> Camera::GetPosition()
{
	Vector<3,float> vector;
	vector.x=XMVectorGetX(position);
	vector.y=XMVectorGetY(position);
	vector.z=XMVectorGetZ(position);
	return vector;
}

void Camera::MoveRelative(float x, float y, float z)
{
	XMMATRIX rotation=XMMatrixRotationRollPitchYaw(pitchRoll.y,pitchRoll.x,0);
	XMVECTOR movement=XMLoadFloat4(&XMFLOAT4(x,y,z,0.0f));
	movement=XMVector4Transform(movement,rotation);
	//Keep perspective bound to gound.
	//movement=XMVectorSetY(movement,0);
	
	position=position+movement;

	
	

}

Vector<4> Camera::GetLookAt()
{
	Vector<4> ret;
	ret.x=XMVectorGetX(lookAt);
	ret.y=XMVectorGetY(lookAt);
	ret.z=XMVectorGetZ(lookAt);
	ret.w=XMVectorGetW(lookAt);
	float norm=ret.x*ret.x;
	norm+=ret.y*ret.y;
	norm+=ret.z*ret.z;
	norm+=ret.w*ret.w;
	norm=sqrt(norm);
	ret.x/=norm;
	ret.y/=norm;
	ret.z/=norm;
	ret.w/=norm;
	return ret;
	//0743 333 086
}

Vector<2> Camera::GetOrientation()
{
	
	return pitchRoll;
}

XMMATRIX Camera::GetProjection()
{
	return XMMatrixPerspectiveFovLH(XM_PI*90.0f/180.0f ,aspectRatio,1.0f,1000.0f);
}

void Camera::SetAspectRatio(float aspectRatio)
{
	this->aspectRatio=aspectRatio;
}

void Camera::MoveAbsolute(Vector<2> absoluteCoords)
{
	position=XMVectorSetX(position,XMVectorGetX(position)+absoluteCoords.x);

	position=XMVectorSetZ(position,XMVectorGetZ(position)+absoluteCoords.y);
}

XMMATRIX Camera::GetView()
{
	return XMMatrixLookAtLH(position,position+lookAt,up);
}