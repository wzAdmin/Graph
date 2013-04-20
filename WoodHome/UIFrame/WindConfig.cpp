#include "WindConfig.h"
#include "FileSystem.h"
#include "SlimXml.h"
#include "Trace.h"

CWindConfig::CWindConfig(void)
{
}


CWindConfig::~CWindConfig(void)
{
}

void CWindConfig::Init( SourceID config )
{
	Sourceitem item = sFilesystem.GetSource(config);
	char* data = new char[item.length];
	sFilesystem.LoadSource(item,data);
	slim::XmlDocument doc;
	doc.loadFromMemory(data,item.length);
	delete[] data;
	slim::NodeIterator it;
	slim::XmlNode* root = doc.getFirstChild(it);
	slim::XmlNode* child = root->getFirstChild(it);
	while (child)
	{
		WindowConfig conf;
		conf.x = child->readAttributeAsInt("x");
		conf.y = child->readAttributeAsInt("y");
		conf.width = child->readAttributeAsInt("width");
		conf.height = child->readAttributeAsInt("height");
		conf.startScene = SourceID(child->readAttributeAsInt("startscene"));
		mWindowStyles.insert(std::pair<Style_Window,WindowConfig>
			(Style_Window(child->readAttributeAsInt("id")),conf));
		child = root->getNextChild(it);
	}
}

const WindowConfig* CWindConfig::GetConfig( Style_Window style ) const
{
	std::map<Style_Window,WindowConfig>::const_iterator it = mWindowStyles.find(style);
	if(mWindowStyles.end() != it)
		return &it->second;
	else
	{
		DebugTrace("CWindConfig::GetConfig Con not find %d\n",style);
		return NULL;
	}
}
