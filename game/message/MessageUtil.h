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


//������
struct Subscriber
{
public:
	virtual ~Subscriber() {}
	virtual void receive(const std::shared_ptr<Message>& message) = 0;
};


//��������
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
	static std::mutex instance_mutex_; // static ����������֤�̰߳�ȫ�Ĵ�������ģʽ��������߳�ͬʱ���ʵ�ʱ�򣬹���ͬһ��mutex�Ӷ��ﵽ�̰߳�ȫ��Ŀ��
	mutable std::mutex mutex_; // ���Ļ���
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


	// ����
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


// �ƶ���Ϣ
class MoveMessage : public Message
{
public:
	Vector2D<int> position;
	MoveMessage() {}
	MoveMessage(const Vector2D<int>& pos) : position(pos) {}
	~MoveMessage() {}
};



