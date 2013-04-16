#pragma once
#include <memory>
#include <stdlib.h>
// |----srcmem----|
//copy to destmem
// |----srcmem--------srcmem--------srcmem--------srcmem----|
template<typename T>
int mem_set(T* pDest ,int destlen ,const T* pSrc,int srclen)
{
	if(destlen < 1 || srclen < 1)
		return 0;
	srclen = destlen < srclen ? destlen : srclen;
	memcpy(pDest,pSrc,sizeof(T)*srclen);
	destlen -= srclen;
	pSrc = pDest;
	pDest += srclen;
	while(destlen > 0)
	{
		srclen = destlen < srclen ? destlen : srclen;
		memcpy(pDest,pSrc,sizeof(T)*srclen);
		pDest += srclen;
		destlen -= srclen;
		srclen *= 2;
	}
	return destlen;
}