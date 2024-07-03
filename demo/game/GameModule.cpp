#include "GameModule.h"

std::unique_ptr<GameModule, GameModule::deleter> GameModule::_instance = nullptr;
std::mutex GameModule::_mtx;


void GameModule::OnBeginModule()
{
	EntityModule::GetInstance()->OnBeginModule();
}

void GameModule::OnEndModule()
{
	EntityModule::GetInstance()->OnEndModule();
}

void GameModule::OnUpdate(double detalTime)
{
	EntityModule::GetInstance()->OnUpdate(detalTime);
}