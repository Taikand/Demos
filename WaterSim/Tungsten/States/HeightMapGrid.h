#pragma once
#include "Tungsten\DataContainers.h"

struct MapVertex
{
	
	Tungsten::Vector<2,float>	heightCoord;
	Tungsten::Vector<2,float>	geometry;
	Tungsten::Vector<2,float>	texCoord;
};
struct	GridVertex
{
	Tungsten::Vector<2> geometry;
};
class HeightMapGrid
{
private:
	MapVertex* geometry;
	UINT32* index;
	int indexCount;
	int vertexCount;
public:
	HeightMapGrid(int meshWidth, int meshHeight, int mapWidth, int mapHeight, int textureStep = 1);
	Tungsten::MemoryBlock	GetGeometry();
	Tungsten::MemoryBlock	GetIndex();

	
	~HeightMapGrid(void);
};

