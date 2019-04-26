#pragma once
#include <queue>
class Process;
class QueueIO
{
public:
	QueueIO();
	~QueueIO();
	//bool getStatusIO;
	void add_to_queueIO(Process*);
	Process* remove_from_queueIO();
	void get_from_queueIO();
	bool status() { return (DeviceQueue.size() > 0) ? true : false; };
private:
	std::queue<Process*> DeviceQueue; //wektor jednej kolejki
};

