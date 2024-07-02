#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <functional>
#include <mutex>
#include <common/commondef.h>

class Message
{
public:
	virtual ~Message() {};
};


//订阅者
struct Subscriber
{
public:
	virtual ~Subscriber() {}
	virtual void receive(const std::shared_ptr<Message>& message) = 0;
};


//订阅中心
class MessageCenter
{
public:
	struct deleter
	{
		void operator()(MessageCenter* ptr)
		{
			delete ptr;
		}
	};

	static MessageCenter* GetInstance()
	{
		std::lock_guard<std::mutex> lock(instance_mutex_);
		if (!instance_)
		{
			instance_.reset(new MessageCenter());
		}
		return instance_.get();
	}
private:
	static std::unique_ptr<MessageCenter, deleter> instance_;
	static std::mutex instance_mutex_; // static 互斥锁，保证线程安全的创建单例模式，当多个线程同时访问的时候，公用同一个mutex从而达到线程安全的目的
	mutable std::mutex mutex_; // 订阅互斥
	MessageCenter() = default;
	~MessageCenter() = default;
private:
	std::unordered_map<const std::type_info*, std::vector<std::function<void(const std::shared_ptr<Message>&) >>> subscribers_;
public:
	
	template<typename MessageType>
	void subscribe(const std::function<void(const std::shared_ptr<Message>&)>& callback)
	{	
		std::lock_guard<std::mutex> lock(mutex_);
		subscribers_[&typeid(MessageType)].push_back(callback);
	}

	template<typename MessageType>
	void unsubscribe(std::function<void(const std::shared_ptr<Message>&)>& callback)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		auto it = subscribers_.find(&typeid(MessageType));
		if (it != subscribers_.end())
		{
			it->second.erase(std::remove(it->second.begin(), it->second.end(), callback), it->second.end());
		}
	}


	// 推送
	template<typename MessageType>
	void publish(const std::shared_ptr<MessageType>& message)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		auto it = subscribers_.find(&typeid(MessageType));
		if (it != subscribers_.end())
		{
			for (auto callback : it->second)
			{
				callback(std::static_pointer_cast<Message>(message));
			}
		}
	}
};


// 移动消息
class MoveMessage : public Message
{
public:
	Vector2D<int> position;
	MoveMessage() {}
	MoveMessage(const Vector2D<int>& pos) : position(pos) {}
	~MoveMessage() {}
};



