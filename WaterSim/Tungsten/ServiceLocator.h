#pragma once
#include "pch.h"
#include "Services\IGraphicsService.h"
#include "Services\IConfigurationService.h"
#include "Services\ISpriteTextService.h"
#include "Services\InputService.h"
#include "Services\IImporterService.h"
namespace Tungsten
{

	
class ServiceLocator
{
private:
	IGraphicsService* graphics;
	IConfigurationService* config;
	ISpriteTextService* spriteText;
	InputService* input;
	IImporterService* importer;
public:



	void SetGraphics(IGraphicsService*);
	void SetConfig(IConfigurationService*);
	void SetSpriteText(ISpriteTextService*);
	void SetInput(InputService*);
	void SetImporter(IImporterService*);
	IGraphicsService* Graphics();
	IConfigurationService* Config();
	ISpriteTextService* SpriteText();
	InputService* Input();
	IImporterService* Import();
	//Refresh is called in order to update Input and other services for a new frame
	void Refresh();
	ServiceLocator(void);
	~ServiceLocator(void);
};
extern ServiceLocator Services;

typedef unsigned int Pixels;
//Converts pixels to vertical UV coordinates
inline float vpx(Pixels val)
{
	return val / Services.Graphics()->resolution.y;
}
//Converts pixels to horizontal UV coordinates
inline float hpx(Pixels val)
{
	return val / Services.Graphics()->resolution.x;
}
//Point in Pixel coordinates
typedef Vector<2, Pixels> PPoint;
//Point in PixelCoordinate to Point in UV coordinates
inline Point px(PPoint val)
{
	return{ hpx(val.x), vpx(val.y) };
}
typedef Vector<4, Pixels> PRectangle;
inline Rectangle px(PRectangle val)
{
	return{ px(val.upperLeft), px(val.lowerRight) };

}

}
