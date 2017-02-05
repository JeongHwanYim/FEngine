#pragma once

#include <functional>
#include <cmath>

struct FVector
{
	enum { NUM_ELEMENT = 3 };

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

	FVector operator +()
	{
		return FVector(3, this->V[0], this->V[1], this->V[2]);
	}

	FVector operator +(const FVector& other)
	{
		return FVector(3, this->V[0] + other.V[0], this->V[1] + other.V[1], this->V[2] + other.V[2]);
	}

	FVector& operator +=(const FVector& other)
	{
		*this = *this + other;
		return (*this);
	}

	FVector operator -()
	{
		return FVector(3, -this->V[0], -this->V[1], -this->V[2]);
	}

	FVector operator -(const FVector& other)
	{
		return FVector(3, this->V[0] - other.V[0], this->V[1] - other.V[1], this->V[2] - other.V[2]);
	}
};


struct FVector4
{
	enum { NUM_ELEMENT = 4 };

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

	static FVector4 transVector4(const FVector& origin)
	{
		FVector4 vRes;
		for (int i = 0; i < origin.NUM_ELEMENT; ++i)
		{
			vRes.V[i] = origin.V[i];
		}
		vRes.V[origin.NUM_ELEMENT] = 1;

		return vRes;
	}

	FVector4 operator +(const FVector4& other)
	{
		return FVector4(4, this->V[0] + other.V[0], this->V[1] + other.V[1], this->V[2] + other.V[2], this->V[3], other.V[3]);
	}

	FVector4& operator +=(const FVector4& other)
	{
		*this = *this + other;
		return (*this);
	}

	FVector4 operator -()
	{
		return FVector4(4, -this->V[0], -this->V[1], -this->V[2], -this->V[3]);
	}

	float SumElem()
	{
		return V[0] + V[1] + V[2] +V[3];
	}
};

struct FRotator
{
	enum { NUM_ELEMENT = 3 };

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
	enum { NUM_ELEMENT = 4 };

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

		// TODO : 풀어서 연산하기?
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
			this->M[i][i] *= scale.V[i];
		}

		return *this;
	}

	FMatrix& SetRotation(const FRotator& rotation)
	{
		FMatrix RotMatrix;

		float SinX = ::std::sinf(rotation.V[0] * acos(-1) / 180);
		float CosX = ::std::cosf(rotation.V[0] * acos(-1) / 180);

		float SinY = ::std::sinf(rotation.V[1] * acos(-1) / 180);
		float CosY = ::std::cosf(rotation.V[1] * acos(-1) / 180);

		float SinZ = ::std::sinf(rotation.V[2] * acos(-1) / 180);
		float CosZ = ::std::cosf(rotation.V[2] * acos(-1) / 180);

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

	FMatrix GetTranspose()
	{
		FMatrix mat;

		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			for (int j = 0; j < NUM_ELEMENT; ++j)
			{
				mat.M[i][j] = this->M[j][i];
			}
		}

		return mat;
	}

	inline FVector4 multiply(const FVector4& vec)
	{
		FVector4 res(4, 0.0f, 0.0f, 0.0f, 0.0f);
		for (int i = 0; i < vec.NUM_ELEMENT; ++i)
		{
			for (int j = 0; j < vec.NUM_ELEMENT; ++j)
			{
				res.V[i] += vec.V[j] * this->M[j][i];
			}
		}

		return res;
	}

	void Set(int nPos, const FVector4& rhs)
	{
		for (int i = 0; i < NUM_ELEMENT; ++i)
		{
			M[nPos][i] = rhs.V[i];
		}
	}
};

inline FVector4 DotProduct(const FVector4& A, const FVector4& B)
{
	float X = A.V[0] * B.V[0];
	float Y = A.V[1] * B.V[1];
	float Z = A.V[2] * B.V[2];

	return FVector4(4, X, Y, Z, 0.0f);
}

inline float DotProductScalar(const FVector4& A, const FVector4& B)
{
	float X = A.V[0] * B.V[0];
	float Y = A.V[1] * B.V[1];
	float Z = A.V[2] * B.V[2];

	return X + Y + Z;
}

inline FVector4 CrossProduct(const FVector4& A, const FVector4& B)
{
	float X = A.V[1] * B.V[2] - A.V[2] * B.V[1];
	float Y = A.V[2] * B.V[0] - A.V[0] * B.V[2];
	float Z = A.V[0] * B.V[1] - A.V[1] * B.V[0];

	return FVector4(4, X, Y, Z, 0.0f);
}

inline void Normalize(FVector4& Point)
{
	float x = Point.V[0];
	float y = Point.V[1];
	float z = Point.V[2];

	float SquareDist = x*x + y*y + z*z;
	float Dist = std::sqrt(SquareDist);

	Point.V[0] = x / Dist;
	Point.V[1] = y / Dist;
	Point.V[2] = z / Dist;
}