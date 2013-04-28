#include "FontConfig.h"
#include <assert.h>
#include "Trace.h"
#include "SlimXml.h"
#include "FileSystem.h"

// the font config is like this
//<Fonts Count = "4">
//<Font ID = "1" Name = "Black1616" Width = "16" Height = "16" Color = "000000"/>
//	<Font ID = "2" Name = "White1616" Width = "16" Height = "16" Color = "ffffff"/>
//	<Font ID = "3" Name = "Green1616" Width = "16" Height = "16" Color = "00ff00"/>
//	<Font ID = "4" Name = "Bule1616" Width = "16" Height = "16" Color = "0000ff"/>
//</Font>

CFontConfig::CFontConfig(void):mFonts(NULL),mFontCount(0)
{
}


CFontConfig::~CFontConfig(void)
{
	Destroy();
}

void CFontConfig::Load(SourceID id)
{
	slim::XmlDocument doc;
	Sourceitem item = sFilesystem.GetSource(id);

	char* data = NEW_LEAKCHECK char[item.length];
	sFilesystem.LoadSource(item,data);
	doc.loadFromMemory(data,item.length);
	DELETEARR_LEAKCHECK(data);

	slim::NodeIterator nodeit;
	slim::XmlNode* root = doc.getFirstChild(nodeit);
	mFontCount = root->readAttributeAsInt("Count");
	mFonts = NEW_LEAKCHECK Font[mFontCount];
	slim::XmlNode* child = root->getFirstChild(nodeit);
	while (child)
	{
		int id = child->readAttributeAsInt("ID");
		assert((id <= mFontCount && id > 0) || DebugTrace(Trace_Error,"id out of range in CFontConfig::Load"));
		const char * color = child->readAttributeAsString("Color");
		mFonts[id-1].color = strtol(color,NULL,16);
		mFonts[id-1].height = child->readAttributeAsInt("Height");
		mFonts[id-1].width = child->readAttributeAsInt("Width");
		child = root->getNextChild(nodeit);
	}
}

 const Font* CFontConfig::GetFont( int id )
{
	assert(mFonts|| DebugTrace(Trace_Error,"mFonts is null in CFontConfig::GetFont"));
	assert((id <= mFontCount && id > 0) || DebugTrace(Trace_Error,"id out of range in CFontConfig::GetFont"));
	return mFonts + id - 1;
}

CFontConfig& CFontConfig::Instance()
{
	static CFontConfig ftconf;
	return ftconf;
}

void CFontConfig::Destroy()
{
	if(mFonts)
	{
		DELETEARR_LEAKCHECK(mFonts);
		mFonts = NULL;
	}
}
