#include <graphics.h>
#include <iostream>
#include <string>
#include "game/entity/player.h"
#include "game/GameModule.h"
#include <chrono>

const int TARGET_FPS = 30; // Ŀ��֡��
const double TARGET_FRAME_TIME = 1000.0 / TARGET_FPS; // ÿ֡��Ŀ��ʱ�䣨���룩

void GetInput(const Player& player,double deltaTime)
{
	bool isUP = false;
	bool isDown = false;
	bool isLeft = false;
	bool isRight = false;

	// ������״̬
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		isUP = true;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		isDown = true;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		isLeft = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		isRight = true;
	}

	Vector2D<float> target = player.GetPlayerPoint();
	if (isUP) target.y -= 2;
	if (isDown) target.y += 2;
	if (isLeft) target.x -= 2;
	if (isRight) target.x += 2;
	if (!isRight && !isUP && !isLeft && !isDown)
	{
		return;
	}

	// ����EntityModule��OnMove�������ƶ����
	EntityModule::GetInstance()->OnMove(player.GetEntityId(), target, deltaTime);
}

int main()
{
	initgraph(1280, 720);

	bool bRunning = true;
	IMAGE img_bg;
	loadimage(&img_bg, _T("img/background.png"));
	BeginBatchDraw();
	GameModule::GetInstance()->OnBeginModule();

	auto lastTime = std::chrono::high_resolution_clock::now();
	auto fpsTimer = std::chrono::high_resolution_clock::now();
	int frameCount = 0;
	double currentFPS = 0.0;

	while (bRunning)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> frameTime = currentTime - lastTime;
		double deltaTime = frameTime.count();
		lastTime = currentTime; // ����lastTime�Լ�¼��֡����ʱ��ʱ��

		// ���������Ʊ���
		cleardevice();
		putimage(0, 0, &img_bg);

		// �������벢������Ϸ�߼�
		GetInput(EntityModule::GetInstance()->GetPlayer(1), deltaTime);
		GameModule::GetInstance()->OnUpdate(deltaTime);

		// ֡����
		frameCount++;

		// ���㲢��ʾ֡��
		auto currentFPSTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> fpsDuration = currentFPSTime - fpsTimer;
		if (fpsDuration.count() >= 1.0)
		{
			currentFPS = frameCount / fpsDuration.count();
			frameCount = 0;
			fpsTimer = currentFPSTime;
		}

		// ��ʾ��ǰ֡��
		settextstyle(20, 0, _T("Arial"));
		settextcolor(WHITE); // ȷ���ı���ɫΪ��ɫ
		TCHAR fpsText[50];
		_stprintf_s(fpsText, _T("FPS: %.2f"), currentFPS);
		outtextxy(10, 10, fpsText); // ������ͼ�����֮������ı�

		// ����һ֡
		FlushBatchDraw();

		// ������Ҫ��˯��ʱ���Կ���֡��
		double sleepTime = TARGET_FRAME_TIME - deltaTime;
		if (sleepTime > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime)));
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); // ȷ��������ȫռ��CPU
		}
	}

	GameModule::GetInstance()->OnEndModule();
}

