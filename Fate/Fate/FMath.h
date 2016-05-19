#pragma once

#include <functional>
#include <cmath>

struct FVector
{
	static const int NUM_ELEMENT = 3;

	float V[NUM_ELEMENT];

	FVector()
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			V[i] = 0;
		}
	}
	template<typename F>
	FVector(int nDepth, F&& f)
	{
		V[NUM_ELEMENT - nDepth] = f;
	}

	template<typename F, typename... Args>
	FVector(int nDepth, F&& f, Args&&... args)
		: FVector(nDepth - 1, std::forward<Args>(args)...)
	{
		V[NUM_ELEMENT - nDepth] = f;
	}

	FVector(const FVector& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}
	}

	FVector& operator =(const FVector& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}

		return *this;
	}

	FVector operator -()
	{
		return FVector(3, -this->V[0], -this->V[1], -this->V[2]);
	}
};


struct FVector4
{
	static const int NUM_ELEMENT = 4;

	float V[NUM_ELEMENT];

	FVector4()
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			V[i] = 0;
		}
	}

	template<typename F>
	FVector4(int nDepth, F&& f)
	{
		V[NUM_ELEMENT - nDepth] = f;
	}

	template<typename F, typename... Args>
	FVector4(int nDepth, F&& f, Args&&... args)
		: FVector4(nDepth - 1, std::forward<Args>(args)...)
	{
		V[NUM_ELEMENT - nDepth] = f;
	}

	FVector4(const FVector& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}
	}

	FVector4(const FVector4& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}
	}

	FVector4& operator =(const FVector4& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}

		return *this;
	}
};

struct FRotator
{
	static const int NUM_ELEMENT = 3;

	float V[NUM_ELEMENT];

	FRotator()
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			V[i] = 0;
		}
	}
	template<typename F>
	FRotator(int nDepth, F&& f)
	{
		V[NUM_ELEMENT - nDepth] = f;
	}

	template<typename F, typename... Args>
	FRotator(int nDepth, F&& f, Args&&... args)
		: FRotator(nDepth - 1, std::forward<Args>(args)...)
	{
		V[NUM_ELEMENT - nDepth] = f;
	}

	FRotator(const FRotator& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}
	}

	FRotator& operator =(const FRotator& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			this->V[i] = other.V[i];
		}

		return *this;
	}

	FRotator operator -()
	{
		return FRotator(3, -this->V[0], -this->V[1], -this->V[2]);
	}
};


struct FMatrix
{
	static const int NUM_ELEMENT = 4;

	float M[NUM_ELEMENT][NUM_ELEMENT];

	FMatrix()
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			for (int j = 0; j < NUM_ELEMENT; ++j)
			{
				this->M[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	}

	FMatrix(const FMatrix& other)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			for (int j = 0; j < NUM_ELEMENT; ++j)
			{
				this->M[i][j] = other.M[i][j];
			}
		}
	}
	
	FMatrix& operator *=(const FMatrix& other)
	{
		return *this * other;
	}

	FMatrix& operator *(const FMatrix& other)
	{
		FMatrix RHS(*this);

		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			for (int j = 0; j < NUM_ELEMENT; ++j)
			{
				M[i][j] = 0;
				for (int k = 0; k < NUM_ELEMENT; ++k)
				{
					M[i][j] += RHS.M[i][k] * other.M[k][j];
				}
			}
		}

		return *this;
	}

	FMatrix& SetScale(const FVector& scale)
	{
		for (int i = 0; i < scale.NUM_ELEMENT; ++i)
		{
			this->M[NUM_ELEMENT][i] *= scale.V[i];
		}

		return *this;
	}

	FMatrix& SetTranslation(const FVector& translation)
	{
		for (int i = 0; i < translation.NUM_ELEMENT; ++i)
		{
			this->M[NUM_ELEMENT][i] += translation.V[i];
		}

		return *this;
	}

	FMatrix& SetRotation(const FRotator& rotation)
	{
		FMatrix RotMatrix;

		float SinX = ::std::sinf(rotation.V[0]);
		float CosX = ::std::cosf(rotation.V[0]);

		float SinY = ::std::sinf(rotation.V[1]);
		float CosY = ::std::cosf(rotation.V[1]);

		float SinZ = ::std::sinf(rotation.V[2]);
		float CosZ = ::std::cosf(rotation.V[2]);

		RotMatrix.M[0][0] = CosY * CosZ;
		RotMatrix.M[0][1] = SinZ;
		RotMatrix.M[0][2] = -SinY;
		
		RotMatrix.M[1][0] = -SinZ;
		RotMatrix.M[1][1] = CosX * CosZ;
		RotMatrix.M[1][2] = SinX;

		RotMatrix.M[2][0] = SinY;
		RotMatrix.M[2][1] = -SinX;
		RotMatrix.M[2][2] = CosX * CosY;

		return (*this)*RotMatrix;
	}
};