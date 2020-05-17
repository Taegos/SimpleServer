#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

class ExitSemaphore {
public:
	ExitSemaphore();
	void up();
	void down();
	void wait();
private:
	std::mutex mx;
	std::condition_variable cnd;
	int count;
};