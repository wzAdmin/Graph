#pragma once
#include "vectorf.h"

template<int N>
class matrixf
{
public:
	matrixf(){Normalize();}
	~matrixf(){}
public:
	matrixf<N>& Zero()
	{
		for (int i =0; i < N ;i++ )
		{
			mValues[i].Zero();
		}
		return *this;
	}
	matrixf<N>& Normalize()
	{
		Zero();
		for(int i = 0 ; i < N ;i++)
			mValues[i][i] = 1.0f;
		return *this;
	}
	const vectorf<N>& operator [] (unsigned int index) const
	{
		assert(index < N);
		return mValues[index];
	}
	vectorf<N>& operator [] (unsigned int index) 
	{
		assert(index < N);
		return mValues[index];
	}
	matrixf<N>& operator *= (float f)
	{
		for (int i = 0 ; i < N ;i ++)
		{
			mValues[i] *= f;
		}
		return *this;
	}
	matrixf<N> operator * (float f) const
	{
		matrixf<N> result;
		for (int i = 0 ; i < N ;i ++)
		{
			result[i] = mValues[i] * f;
		}
		return result;
	}
	matrixf<N> operator * (const matrixf<N>& other) const
	{
		matrixf<N> result;
		result.Zero();
		for (int i = 0 ; i < N; i++ )
		{
			for (int j = 0;j < N ; j++)
			{
				for (int k = 0; k < N ;k++)
				{
					result[i][j] += mValues[i][k] * other[k][j];
				}
			}
		}
		return result;
	}
	matrixf<N>& operator *=(const matrixf<N>& other)
	{
		matrixf<N> result = (*this) * other;
		*this = result;
		return *this;
	}
	vectorf<N> operator * (const vectorf<N>& vec) const
	{
		vectorf<N> result;
		result.Zero();
		for (int i = 0; i < N ;i++)
		{
			for (int j =0; j < N ;j ++)
			{
				result[i] += vec[j] * mValues[j][i]; 
			}
		}
		return result;
	}
private:
	vectorf<N> mValues[N];
};