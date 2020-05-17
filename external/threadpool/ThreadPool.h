#pragma once
#include "Semaphore.h"
#include "ExitSemaphore.h"
#include <condition_variable>
#include <functional>
#include <queue>

class ThreadPool {

	using TASK = std::function<void()>;

public:
	ThreadPool(int);
	~ThreadPool();
	void enqueue(TASK);

private:

	ExitSemaphore exitSema;

	std::mutex queueMut;
	Semaphore queueSema;
	std::queue<TASK> queue;

	void runTasks();
};