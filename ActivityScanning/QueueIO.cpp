#include "QueueIO.h"

QueueIO::QueueIO()
{
}

QueueIO::~QueueIO()
{
}

void QueueIO::add_to_queueIO(Process * temp)
{
	DeviceQueue.push(temp);
}

Process* QueueIO::remove_from_queueIO()
{
	Process *p = DeviceQueue.front();
	DeviceQueue.pop();
	return p;
}

void QueueIO::get_from_queueIO()
{
	DeviceQueue.front();
}

