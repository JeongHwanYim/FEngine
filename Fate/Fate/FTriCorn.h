#pragma once

#include "FMath.h"
#include <vector>

struct FVertex
{
	FVector pos;
	FVector4 color;
};

struct FTriCorn
{
	static const int VERTEX_COUNT = 4;
	FVertex vertex[VERTEX_COUNT];

	static const int INDEX_COUNT = 12;
	std::vector<DWORD> indices;

	FTriCorn()
	{
	//		{ 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
	//		{ 0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
	//		{ -0.45f, -0.5f, 0.0f, 

		vertex[0].pos = FVector(3, 0.0f, 0.5f, 0.0f);
		vertex[0].color = FVector4(4, 1.0f, 0.0f, 0.0f, 1.0f);

		vertex[1].pos = FVector(3, 0.45f, -0.5f, 0.0f);
		vertex[1].color = FVector4(4, 0.0f, 1.0f, 0.0f, 1.0f);

		vertex[2].pos = FVector(3, -0.45f, -0.5f, 0.0f);
		vertex[2].color = FVector4(4, 0.0f, 0.0f, 1.0f, 1.0f);

		vertex[3].pos = FVector(3, 0.0f, 0.6f, 0.6f);
		vertex[3].color = FVector4(4, 0.5f, 0.5f, 0.5f, 1.0f);

		indices.resize(INDEX_COUNT);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 3;
		indices[5] = 1;
		indices[6] = 3;
		indices[7] = 0;
		indices[8] = 2;
		indices[9] = 3;
		indices[10] = 2;
		indices[11] = 1;
	}
};