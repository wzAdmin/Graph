#include <memory>
#include <assert.h>
#include <stdlib.h>
#include "GraphicType.h"
#include "Trace.h"
#if defined(_DEBUG) || defined(DEBUG)
#define MEMORY_RECORD_INDEX_SIZE 0x10000
#define MEMORY_RECORD_INDEX_MASK 0xFFFF
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
	Hash_MemoryRecord()
	{
		memset(mHashIndex,0,sizeof(MemoryRecord*)*MEMORY_RECORD_INDEX_SIZE);
	}
	~Hash_MemoryRecord()
	{
		Printmem();
	}

	void Insert(MemoryRecord* record)
	{
		int index = int(record->startadress) & MEMORY_RECORD_INDEX_MASK;
		record->next = mHashIndex[index];
		mHashIndex[index] = record;
		MemCurUsed += record->Memsize;
		MemMaxUsed = MemMaxUsed < MemCurUsed ? MemCurUsed : MemMaxUsed;
	}
	const MemoryRecord* FindRecord(void* p)
	{
		int index = int(p) & MEMORY_RECORD_INDEX_MASK;
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
		int index = int(record->startadress) & MEMORY_RECORD_INDEX_MASK;
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
	MemoryRecord* mHashIndex[MEMORY_RECORD_INDEX_SIZE];
public:
	int MemCurUsed;
	int MemMaxUsed;
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
		for (int i = 0 ;  i < MEMORY_RECORD_INDEX_SIZE ; i++)
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