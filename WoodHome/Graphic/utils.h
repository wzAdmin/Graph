#pragma once

inline int Float2Int(float value)
{  
	static const float magic_f = (3<<21);
	static const long magic_i = 0x4ac00000;
	value +=magic_f;
	return  (*((int*)&value)-magic_i) >> 1;
}
inline int Double2Int(double value)
{
	static double magicd = 6755399441055744.0;
	value += magicd;
	return *(int*)&value;
}