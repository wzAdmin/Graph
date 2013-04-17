#pragma once
#ifdef _DLL
#define GRAPHIC_API _declspec(dllexport)
#else
#define GRAPHIC_API
#endif

#ifndef _MSC_VER
typedef long long int64;
typedef unsigned long long uint64;
#define ns_hash __gnu_cxx
#define HASH_MAP <ext/hash_map>
 #else
typedef __int64 int64;
typedef unsigned __int64 uint64;
#define ns_hash std
#define HASH_MAP <hash_map>
#endif

#define MATH_PI  3.1415926f
#define ABS(a) ((a) < 0 ? (-(a)) : (a))
#ifndef MAX
#define MAX(a,b) ((a)>(b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#endif
enum COLORFORMAT
{
	RGB_565,
	RGB_888
};
enum ALIGN
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	LEFTTOP,
	RIGHTTOP,
	LEFTBOTTOM,
	RIGHTBOTTOM,
	CENTER
};
typedef unsigned int COLORARGB;
#define ARGB(a , r , g , b) ( (a<<24) | (r <<16) | (g << 8) | b)
#define CRGB(r , g , b) ( (r <<16) | (g << 8) | b)
#ifndef NULL 
#define NULL 0
#endif
typedef struct _Font 
{
	int width;
	int height;
	COLORARGB color;
}Font;

inline unsigned int RGB565ToRGB888(unsigned short color)
{
	unsigned int r = 0, g = 0, b = 0;
	r = (color & 0xF800) >> 8;
	g = (color & 0x07E0) >> 2;
	b = (color & 0x001F) << 3;
	return CRGB(r,g,b);
}

inline unsigned short RGB888ToRGB565(unsigned int color)
{
	unsigned short r = 0, g = 0, b = 0;
	r = (color & 0xFF00000) >> 19;
	g = (color & 0xFF00) >> 10;
	b = (color & 0xFF) >> 3;
	return ( (r<<11) | (g<<5) | b );
}
inline void Alpha(unsigned short& dest , unsigned short src ,unsigned char alpha)
{	
 	unsigned int srcColor = src ;
 	srcColor = ((srcColor <<16) | srcColor ) & 0x07E0F81F;
 	unsigned int destColor = dest;
 	destColor = ((destColor <<16) | destColor ) & 0x07E0F81F;
 	destColor +=(((srcColor - destColor) * alpha )>> 5);
	destColor &=0x07E0F81F;
 	dest = ((destColor >>16) | destColor);
}

inline void Alpha(unsigned short& dest , unsigned int srcColor ,unsigned char alpha)
{	
	unsigned int destColor = dest;
	destColor = ((destColor <<16) | destColor ) & 0x07E0F81F;
	destColor +=(((srcColor - destColor) * alpha )>>5);
	destColor &=0x07E0F81F;
	dest = ((destColor >>16) | destColor);
}

inline void Alpha(unsigned char& dest , unsigned char src ,unsigned char alpha)
{
	dest += (int(src-dest)*alpha )>> 5;
}
inline unsigned short ConstructRGB(unsigned  char r,unsigned char g,unsigned char b)
{
	r>>=3;
	g>>=2;
	b>>=3;
	return ((unsigned short)r << 11) | ((unsigned short)g << 5) | (unsigned short)b ;
}


