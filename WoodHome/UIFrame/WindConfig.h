#pragma once
#include "resource_image.h"
#include "window_Style.h"
#include <map>
typedef struct _WindowConfig
{
	int x;
	int y;
	int width;
	int height;
	SourceID startScene;
}WindowConfig;
class CWindConfig
{
public:
	CWindConfig(void);
	~CWindConfig(void);
public:
	void Init(SourceID config);
	const WindowConfig* GetConfig(Style_Window style) const;
private:
	std::map<Style_Window,WindowConfig> mWindowStyles;
};

