#pragma once

#include <mutex>
#include <vector>
#include "common/commondef.h"
#include "entity/player.h"
#include <memory>
#include "entity/EntityModule.h"

class GameModule
{
private:
	GameModule() = default;
	~GameModule() = default;
	// 禁止拷贝构造和赋值
	GameModule(const GameModule&) = delete;
	GameModule& operator=(const GameModule&) = delete;

	struct deleter
	{
		void operator()(GameModule* ptr)
		{
			delete ptr;
		}
	};

	static std::unique_ptr<GameModule, deleter> _instance;
	static std::mutex _mtx;

public:
	static GameModule* GetInstance()
	{
		std::lock_guard<std::mutex> lock(_mtx);
		if (!_instance)
		{
			_instance.reset(new GameModule());
		}

		return _instance.get();
	}

public:
	void OnBeginModule();
	void OnEndModule();
	void OnUpdate(double detalTime);
};