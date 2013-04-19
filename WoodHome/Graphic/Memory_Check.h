/*
 * Author: woodhome(wudecs2007@126.com)
 */
#pragma once

//#if defined(_DEBUG) || defined(DEBUG)

extern "C" void* DebugNew(size_t n, const char* file, int line);
extern "C" void* DebugNewArray(size_t n, const char* file, int line);
extern "C" void* DebugDelArray(void* p);
extern "C" void* DebugDel(void* p);
extern "C" void* DbgMalloc(size_t n,const char* file, int line);
extern "C" void  DbgFree(void* p);
// inline void* operator new(size_t n, const char* file, int line)
// {
// 	return DebugNew(n,file,line);
// }
// inline void* operator new[](size_t n, const char* file, int line)
// {
// 	return DebugNewArray(n,file,line);
// }
// inline void operator delete(void* p, const char* file, int line)
// {
// 	DebugDel(p);
// }
// inline void operator delete[](void* p)
// {
// 	DebugDelArray(p);
// }
// 
// inline void operator delete(void* p)
// {
// 	DebugDel(p);
// }

#define NEW_LEAKCHECK new(__FILE__,__LINE__)
#define malloc(n) DebugMalloc(n,__FILE__,__LINE__)
#define free(p) DebugFree(p)
//#endif 

