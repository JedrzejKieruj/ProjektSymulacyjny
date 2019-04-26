#pragma once

#include <math.h>
#include "Process.h"


class CPU
{
public:
	//bool cpuBusy;
	bool cpuStatus() {
		return process_cpu != nullptr;
	};
	Process* get_process_cpu();
	void assign_process_to_cpu(Process*, long time);
	void take_out_process_from_CPU();
	long getServiceEnd();
	long getServiceStart();
	long getWorkingTime();
	CPU();
	~CPU();
private:
	Process* process_cpu;		//zmienna typu Process przechowuj¹ca proces
	long serviceEnd, serviceStart;		//pytanie czy zrobic serviceEnd i Start dla IO
	long workingTime;
};

