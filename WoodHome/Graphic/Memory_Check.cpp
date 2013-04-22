#include <memory>
#include <assert.h>
#include <stdlib.h>
#include "GraphicType.h"
#include "Trace.h"
#if defined(_DEBUG) || defined(DEBUG)
typedef struct _MemoryRecord {
	void* startadress;
	int Memsize;
	const char* file;
	int line;
	const char* type;
	struct _MemoryRecord* next;
} MemoryRecord;

class Hash_MemoryRecord
{
public:
	int MemCurUsed;
	int MemMaxUsed;
	const static int sHash_INDEX_SIZE = 0x10000;

	//if n = 2^k,then m%n = m&(n-1).
	const static int sMask  = sHash_INDEX_SIZE - 1;
public:
	Hash_MemoryRecord()
	{
		memset(mHashIndex,0,sizeof(MemoryRecord*)*sHash_INDEX_SIZE);
	}
	~Hash_MemoryRecord()
	{
		Printmem();
	}

	void Insert(MemoryRecord* record)
	{
		//if n = 2^k,then m%n = m&(n-1).
		int index = int(record->startadress) & sMask;

		record->next = mHashIndex[index];
		mHashIndex[index] = record;
		MemCurUsed += record->Memsize;
		MemMaxUsed = MemMaxUsed < MemCurUsed ? MemCurUsed : MemMaxUsed;
	}
	const MemoryRecord* FindRecord(void* p)
	{
		int index = int(p) & sMask;
		MemoryRecord* r = mHashIndex[index];
		while (r && p!=r->startadress)
		{
			r =r->next;
		}
		return r;
	}
	void RemoveRecord(const MemoryRecord* record)
	{
		MemCurUsed -= record->Memsize;
		int index = int(record->startadress) & sMask;
		MemoryRecord* r = mHashIndex[index];
		if(r == record)
		{
			mHashIndex[index] = mHashIndex[index]->next;
			::delete record;
			return ;
		}
		while (r)
		{
			if(r->next == record)
			{
				r->next = record->next;
				::delete record;
				return;
			}
			r = r->next;
		}
		assert(false);
	}
	MemoryRecord* mHashIndex[sHash_INDEX_SIZE];
};

static Hash_MemoryRecord sMemRecords;

GRAPHIC_API void*  DebugNew(size_t n, const char* file, int line)
{
	void* p = ::malloc(n);
	MemoryRecord* record = ::new MemoryRecord;
	record->file =file;
	record->line = line;
	record->Memsize = n;
	record->startadress = p;
	record->type = "new";
	sMemRecords.Insert(record);
	return p;
}
GRAPHIC_API void* DebugNewArray(size_t n, const char* file, int line)
{
	void* p = ::malloc(n);
	MemoryRecord* record = ::new MemoryRecord;
	record->file =file;
	record->line = line;
	record->Memsize = n;
	record->startadress = p;
	record->type = "new[]";
	sMemRecords.Insert(record);
	return p;
}

GRAPHIC_API void  DebugDel(void* p)
{
	if(!p)
		return ;
	const MemoryRecord* record = sMemRecords.FindRecord(p);
	assert( record && record->type == "new" );
	sMemRecords.RemoveRecord(record);
}
GRAPHIC_API void  DebugDelArray(void* p)
{
	if(!p)
		return ;
	const MemoryRecord* record = sMemRecords.FindRecord(p);

	//If p is an array of class object and the class have a destructor explicitly(
	//include destructor of base class and member's),
	//the compiler will malloc more 4(it is different in different compiler, gcc and vc++ is 4) 
	//bytes to save the number of the objects,so that it can call the destructor correctly when delete
	//the array.
	if(!record)
		record = sMemRecords.FindRecord((char*)p-4);

	assert( record && record->type == "new[]" );
	sMemRecords.RemoveRecord(record);
}

GRAPHIC_API void*  DbgMalloc(size_t n, const char* file, int line)
{
	void* p = ::malloc(n);
	MemoryRecord* record = ::new MemoryRecord;
	record->file =file;
	record->line = line;
	record->Memsize = n;
	record->startadress = p;
	record->type = "malloc";
	sMemRecords.Insert(record);
	return p;
}
GRAPHIC_API void  DbgFree(void* p)
{
	if(!p)
		return ;
	const MemoryRecord* record = sMemRecords.FindRecord(p);
	assert( record && record->type == "malloc" );
	sMemRecords.RemoveRecord(record);
	::free(p);
}

GRAPHIC_API void Printmem() 
{
	DebugTrace(Trace_Error,"MemMaxUsed not include external libs %d bytes\n",sMemRecords.MemMaxUsed);
	DebugTrace(Trace_Error,"MemLeak not include external libs %d bytes\n",sMemRecords.MemCurUsed);
	if(sMemRecords.MemCurUsed)
	{
		for (int i = 0 ;  i < Hash_MemoryRecord::sHash_INDEX_SIZE ; i++)
		{
			MemoryRecord* r = sMemRecords.mHashIndex[i];
			while (r)
			{
				DebugTrace(Trace_Error,"File %s line %d leak %d bytes\n",r->file,r->line,r->Memsize);
				r = r->next;
			}

		}
	}
}
#endif