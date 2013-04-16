#pragma once
#include <assert.h>
#include <math.h>
#include "utils_mem.h"
template<int N>
class vectorf
{
public:
	vectorf(){Zero();}
	~vectorf(){}
public:
	vectorf<N>& Zero()
	{
		float zero = 0.0f;
		mem_set(mValues ,N ,&zero , 1);
		return *this;
	}
	float& operator[](unsigned int index) 
	{
		assert(index < N);
		return mValues[index];
	}	
	const float& operator[](unsigned int index) const
	{
		assert(index < N);
		return mValues[index];
	}
	void SetValue(float* values ,int len)
	{
		assert(len == N);
		memcpy(mValues , values ,sizeof(float)*N);
	}
	vectorf(const vectorf<N>& other)
	{
		*this = other;
	}
	vectorf<N>& operator = (const vectorf<N>& other)
	{
		assert(this != &other);
		memcpy(mValues , other.mValues ,sizeof(float)*N);
		return *this;
	}
	vectorf<N> operator + (const vectorf<N>& other) const
	{
		vectorf<N> result;
		for (int i = 0;i < N ;i++)
		{
			result[i] = mValues[i] + other[i];
		}
		return result;
	}
	vectorf<N>& operator += (const vectorf<N>& other) 
	{
		for (int i = 0;i < N ;i++)
		{
			mValues[i] += other[i];
		}
		return *this;
	}
	vectorf<N> operator * (float f)
	{
		vectorf<N> result;
		for (int i = 0; i < N ;i++ )
		{
			result[i] = mValues[i]*f;
		}
		return result;
	}
	vectorf<N>& operator *= (float f)
	{
		for (int i = 0;i < N ; i++)
		{
			mValues[i] *= f;
		}
		return *this;
	}
	bool operator == (const vectorf<N>& other) const
	{
		for(int i=0; i < N ;i++)
		{
			if(mValues[i] != other.mValues[i])
				return false;
		}
		return true;
	}
	float operator * (const vectorf<N>& other) const
	{
		float result = 0.0f;
		for (int i = 0 ;i < N ;i++)
		{
			result += mValues[i] * other.mValues[i];
		}
		return result;
	}

	float Length() const
	{
		return sqrt((*this)*(*this));
	}
	vectorf<N>& Normalize()
	{
		float len = Length();
		if(0.0f == len)
			return *this;
		for (int i = 0; i < N ; i++)
		{
			mValues[i] /= len;
		}
		return *this;
	}
	float adot_2(const vectorf<2>& other) const;
	vectorf<3> adot_3(const vectorf<3> other) const;
private:
	float mValues[N];
};

template<>
inline float vectorf<2>::adot_2(const vectorf<2>& other) const
{
	return mValues[0]*other.mValues[1] - mValues[1]*other.mValues[0];
}

template<>
inline vectorf<3> vectorf<3>::adot_3(const vectorf<3> other) const
{
	vectorf<3> result;
	result[0] = mValues[1] * other.mValues[2] - mValues[2] * other.mValues[1];
	result[1] = mValues[2] * other.mValues[0] - mValues[0] * other.mValues[2];
	result[2] = mValues[0] * other.mValues[1] - mValues[1] * other.mValues[0];
	return result;
}