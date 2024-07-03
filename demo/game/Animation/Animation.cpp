#include "Animation.h"

Animation::Animation(LPCTSTR path,double timeValue) : timeInternal(timeValue),aniIndex(0),timer(0)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < StructSize::MAX_ANIM_COUNT;++i)
	{
		img.push_back(std::make_unique<IMAGE>());
		_stprintf_s(path_file, path, i);
		loadimage(img[i].get(), path_file);
	}
}

Animation::~Animation()
{

}

void Animation::PlayAnimation(float x,float y,double deltaTime)
{
	timer += deltaTime;
	if (timer >= timeInternal)
	{
		aniIndex = (aniIndex + 1) % img.size();
		timer = 0;
	}

	putimage_alpha(x, y, img[aniIndex].get());
}
