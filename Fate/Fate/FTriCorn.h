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
	enum { VERTEX_COUNT = 4 };
	std::vector<FVertex> vertex;

	enum { INDEX_COUNT = 12 };
	std::vector<DWORD> indices;

	FTriCorn() : FObject(nullptr)
	{
		InitVertexBuffer();
		InitIndexBuffer();
	}

	void InitVertexBuffer()
	{
		//vertex.push_back(
		//{FVector(3, 100.f, 150.f, 100.f), FVector4(4, 1.0f, 0.0f, 0.0f, 1.0f)}
		//);
		//vertex.push_back(
		//{FVector(3, 145.f, 50.f, 100.f), FVector4(4, 0.0f, 1.0f, 0.0f, 1.0f)
		//});
		//vertex.push_back(
		//{FVector(3, 55.f, 50.f, 100.f), FVector4(4, 0.0f, 0.0f, 1.0f, 1.0f)}
		//);
		//vertex.push_back(
		//{FVector(3, 100.f, 160.f, 160.f), FVector4(4, 0.5f, 0.5f, 0.5f, 1.0f)}
		//);

		vertex.push_back(
		{ FVector(3, 0.f, 0.5f, 0.f), FVector4(4, 1.0f, 0.0f, 0.0f, 1.0f) }
		);
		vertex.push_back(
		{ FVector(3, 0.45f, -0.5f, 0.f), FVector4(4, 0.0f, 1.0f, 0.0f, 1.0f)
		});
		vertex.push_back(
		{ FVector(3, -0.45f, -0.5f, 0.f), FVector4(4, 0.0f, 0.0f, 1.0f, 1.0f) }
		);
		vertex.push_back(
		{ FVector(3, 0.f, 0.6f, 0.6f), FVector4(4, 0.5f, 0.5f, 0.5f, 1.0f) }
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