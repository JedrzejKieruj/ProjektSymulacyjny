#include "IO.h"
#include "Process.h"

void IOdevice::take_out_process_from_IO()
{
	process_io->updateIOToccupation(getProcessingTime());
	process_io = nullptr;
	serviceEnd = -1;
	serviceStart = -1;

}

void IOdevice::assign_process_to_IO(Process * _p, long time)
{
	if (process_io == nullptr) {
		process_io = _p;
		serviceEnd = _p->get_ioExecTime() + time;
		serviceStart = time;
	}
}

long IOdevice::getServiceEnd()
{
	return serviceEnd;
}

long IOdevice::getProcessingTime()
{
	return serviceEnd - serviceStart;
}

IOdevice::IOdevice()
{
	process_io = nullptr;
	serviceEnd = -1;
}

IOdevice::~IOdevice()
{
}

Process* IOdevice::get_process_io()
{
	return process_io;
}
