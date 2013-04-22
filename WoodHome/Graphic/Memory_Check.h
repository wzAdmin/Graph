/*
 * Author: woodhome(wudecs2007@126.com)
 */
#pragma once

#if defined(_DEBUG) || defined(DEBUG)

_declspec(dllexport) void* DebugNew(size_t n, const char* file, int line);
_declspec(dllexport) void* DebugNewArray(size_t n, const char* file, int line);
_declspec(dllexport) void DebugDelArray(void* p);
_declspec(dllexport) void DebugDel(void* p);
_declspec(dllexport) void* DbgMalloc(size_t n,const char* file, int line);
_declspec(dllexport) void  DbgFree(void* p);
_declspec(dllexport) void Printmem() ;
 inline void* operator new(size_t n, const char* file, int line)
 {
 	return DebugNew(n,file,line);
 }
 inline void* operator new[](size_t n, const char* file, int line)
 {
 	return DebugNewArray(n,file,line);
 }
 inline void operator delete(void* p, const char* file, int line)
 {
 	DebugDel(p);
 }
 inline void operator delete[](void* p, const char* file, int line)
 {
	 DebugDel(p);
 }

#define NEW_LEAKCHECK new(__FILE__,__LINE__)
#define DELETE_LEAKCHECK(p){ delete(p);DebugDel(p);}
#define DELETEARR_LEAKCHECK(p) delete[](p);DebugDelArray(p)
#define MALLOC_LEAKCHECK(s) DbgMalloc(s,__FILE__, __LINE__)
#define FREE_LEAKCHECK(p) DbgFree(p)
#else
#define NEW_LEAKCHECK new
#define DELETE_LEAKCHECK(p)delete(p)
#define DELETEARR_LEAKCHECK(p) delete[](p)
#define MALLOC_LEAKCHECK(s) malloc(s)
#define FREE_LEAKCHECK(p) free(p)
#define Printmem() 
#endif 

