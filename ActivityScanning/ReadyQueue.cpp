#include "ReadyQueue.h"
#include "Process.h"

ReadyQueue::ReadyQueue()
{
	ReadyQ.clear();
}

Process * ReadyQueue::getNextProcess()
{
	int id = rand()%ReadyQ.size();	//wartoœ z gen równomiernego
	Process* p = ReadyQ[id];
	ReadyQ.erase(ReadyQ.begin() + id);
	return p;
}

void ReadyQueue::pushProcess(Process* p)
{
	ReadyQ.push_back(p);
}

ReadyQueue::~ReadyQueue()
{
	ReadyQ.clear();
}

bool ReadyQueue::isEmpty()
{
	if(ReadyQ.size() == 0)
	return true;
}
