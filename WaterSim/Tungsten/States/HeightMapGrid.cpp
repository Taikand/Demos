#include "pch.h"
#include "HeightMapGrid.h"
#include <math.h>

using namespace Tungsten;

HeightMapGrid::HeightMapGrid(int meshWidth, int meshHeight, int mapWidth, int mapHeight, int textureStep)
{
	geometry=new MapVertex[meshWidth*meshHeight];
	vertexCount = meshWidth*meshHeight;
	for(int i=0;i<meshHeight;i++)
	{
		for(int y=0;y<meshWidth;y++)
		{
			geometry[i*meshWidth+y].geometry.x=(float)y/*-meshWidth/2*/;
			geometry[i*meshWidth+y].geometry.y=(float)(i/*-meshHeight/2*/);
			
			geometry[i*meshWidth+y].heightCoord.x=y*(float)mapWidth/meshWidth;
			geometry[i*meshWidth+y].heightCoord.y=i*(float)mapHeight/meshHeight;

			geometry[i*meshWidth+y].texCoord.x=(float)y/textureStep;
			geometry[i*meshWidth+y].texCoord.y=(float)i/textureStep;

		}
	}
	/*
	Assume following grid
	 0- 1- 2- 3
	 4- 5- 6- 7
	 8- 9-10-11
	12-13-14-15
	Indices for Line1:
	3  7  2  6  1  5  0  4  4
	Indices for Line2
	4  8  5  9  6 10  7 11  11
	Z is reversed!!	
	*/
	index=new UINT32[ (meshWidth*2+1) * (meshHeight-1)  ];
	indexCount = (meshWidth * 2 + 1) * (meshHeight - 1);
	for(int i=0;i<meshHeight-1;i++)
	{
		UINT32* indexLine=index+i*(meshWidth*2+1);
		//Go back
		if(!(i%2))
		{
			for(int y=0;y<meshWidth;y++)
			{
				indexLine[y*2+0]=i*meshWidth+y;
				indexLine[y*2+1]=(i+1)*meshWidth+y;
			}
			indexLine[meshWidth*2]=(i+1)*meshWidth+meshWidth-1;
			
		}
		else
		{
			for(int y=0;y<meshWidth;y++)
			{
				indexLine[y*2+0]=i*meshWidth+meshWidth-1-y;
				indexLine[y*2+1]=(i+1)*meshWidth+meshWidth-1-y;
			}
			indexLine[meshWidth*2]=(i+1)*meshWidth;
			
		}
		
	}
	
}


HeightMapGrid::~HeightMapGrid(void)
{
	delete[] index;
	delete[] geometry;
}

Tungsten::MemoryBlock HeightMapGrid::GetGeometry()
{
	return Tungsten::MemoryBlock(geometry, vertexCount*sizeof(MapVertex));
}

Tungsten::MemoryBlock HeightMapGrid::GetIndex()
{
	return Tungsten::MemoryBlock(index, indexCount*sizeof(UINT32));
}

