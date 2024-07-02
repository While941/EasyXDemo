#include "MessageUtil.h"

std::unique_ptr<MessageCenter, MessageCenter::deleter> MessageCenter::instance_ = nullptr;
std::mutex MessageCenter::instance_mutex_;