#pragma once

#include <vector>
#include <memory>
#include <graphics.h>
#include "common/commondef.h"
#include <string>
#include <iostream>

#pragma comment(lib, "MSIMG32.LIB")
class Animation
{
public:
	Animation(LPCTSTR path,double timeInternal);
	~Animation();
public:
	void PlayAnimation(float x,float y,double deltaTime);
private:
	inline void putimage_alpha(int x, int y, IMAGE* img)
	{
		int w = img->getwidth();
		int h = img->getheight();
		AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	}
private:
	std::vector<std::unique_ptr<IMAGE>> img;
	double timer;
	double timeInternal;
	int aniIndex;
};