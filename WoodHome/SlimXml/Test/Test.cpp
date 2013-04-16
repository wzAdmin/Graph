#include <stdio.h>
#include <tchar.h>

#ifdef UNICODE
	#include "test_utf8.h"
	const wchar_t* INPUT_FILE = L"test_utf8.xml";
	const wchar_t* SAVE_TEST_FILE = L"savetest_utf8.xml";
	const wchar_t* SCHEMA_TEST_FILE = L"schematest_utf8.xml";
#else
	#include "test_gb2312.h"
	const char* INPUT_FILE = "test_gb2312.xml";
	const char* SAVE_TEST_FILE = "savetest_gb2312.xml";
	const char* SCHEMA_TEST_FILE = "schematest_gb2312.xml";
#endif

using namespace slim;

int _tmain(int argc, _TCHAR* argv[])
{
	XmlDocument readingDoc;
	readingDoc.loadFromFile( INPUT_FILE );

	//testing parsing and writing
	readingDoc.save( SAVE_TEST_FILE );

	//testing generated reading/writing code
#ifdef UNICODE
	test_utf8::Model model;
#else
	test_gb2312::Model model;
#endif
	XmlNode* readingNode = readingDoc.findChild( T("Model") );
	if ( readingNode != NULL )
	{
		model.read( readingNode );
	}

	XmlDocument writingDoc;
	XmlNode* writingNode = writingDoc.addChild( T("Model") );
	model.write( writingNode );

	writingDoc.save( SCHEMA_TEST_FILE );

	return 0;
}
