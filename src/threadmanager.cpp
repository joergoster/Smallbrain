#include <thread>

#include "threadmanager.h"


void ThreadManager::begin(int depth, Time time, int threadCount) {
	if (is_searching()) {
		stop();
	}
	stopped = false;
	threads = std::thread(&Search::iterative_deepening, searcher_class, depth, time, 0, threadCount);
}
void ThreadManager::stop() {
	stopped = true;
	if (threads.joinable()) {
		threads.join();
	}
}
bool ThreadManager::is_searching() {
	return threads.joinable();
}