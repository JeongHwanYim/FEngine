#pragma once

#include "FObject.h"
#include "FMath.h"
#include <vector>

struct FVertex
{
	FVector pos;
	FVector4 color;
};

struct FTriCorn : public FObject
{
	static const int VERTEX_COUNT = 4;
	std::vector<FVertex> vertex;

	static const int INDEX_COUNT = 12;
	std::vector<DWORD> indices;

	FTriCorn() : FObject(nullptr)
	{
		InitVertexBuffer();
		InitIndexBuffer();
	}

	void InitVertexBuffer()
	{
		vertex.push_back(
		{FVector(3, 0.0f, 0.5f, 0.0f), FVector4(4, 1.0f, 0.0f, 0.0f, 1.0f)}
		);
		vertex.push_back(
		{FVector(3, 0.45f, -0.5f, 0.0f), FVector4(4, 0.0f, 1.0f, 0.0f, 1.0f)
		});
		vertex.push_back(
		{FVector(3, -0.45f, -0.5f, 0.0f), FVector4(4, 0.0f, 0.0f, 1.0f, 1.0f)}
		);
		vertex.push_back(
		{FVector(3, 0.0f, 0.6f, 0.6f), FVector4(4, 0.5f, 0.5f, 0.5f, 1.0f)}
		);
	}

	void InitIndexBuffer()
	{
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(1);

		indices.push_back(3);
		indices.push_back(0);
		indices.push_back(2);

		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);
	}
};