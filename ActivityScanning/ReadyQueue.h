
#pragma once
#include <vector>
class Process;

class ReadyQueue {
public:
	ReadyQueue();
	Process* getNextProcess();
	void pushProcess(Process* p);
	int getLength() { return ReadyQ.size(); };
	void clear() { ReadyQ.clear(); };
	~ReadyQueue();
	bool isEmpty();
private:
	std::vector<Process*> ReadyQ; //kolejka ready


};