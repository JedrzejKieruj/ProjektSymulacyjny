#include "CPU.h"



CPU::CPU()
{
	process_cpu = nullptr;
	workingTime = 0;
	serviceStart = -1;
	serviceEnd = -1;	
}

CPU::~CPU()
{
}



Process * CPU::get_process_cpu()
{
	return process_cpu;
}

void CPU::assign_process_to_cpu(Process * _p, long time)
{
	if (process_cpu == nullptr) {
		process_cpu = _p;
		if (_p->get_IOT() > 0) {
			serviceEnd = time + fmin(_p->get_IOT(), _p->get_CET());
		} else {
			serviceEnd = time + _p->get_CET();
			serviceStart = time;
		}

		workingTime = serviceEnd - time;
	}

	
}

long CPU::getWorkingTime() {
	return workingTime;
}

void CPU::take_out_process_from_CPU()
{
	if (process_cpu != nullptr) {
		process_cpu->uptade_CET_ICT();
		process_cpu = nullptr;
		serviceEnd = -1;
		serviceStart = -1;
	}

}

long CPU::getServiceEnd()
{
	return serviceEnd;
}

long CPU::getServiceStart()
{
	return serviceStart;
}





