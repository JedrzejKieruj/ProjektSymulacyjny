#include "CPUscheduler.h"
#include <vector>


vector<Process*> allProcesses = vector<Process*>();

void CPUscheduler::UpdateSimTime()
{
	
	long min_time = next_process_time;
	for (int i = 0; i < cpuNumb; i++)
	{
		long cpuTime = cpus[i]->getServiceEnd();
		if (cpuTime >= 0) {
			min_time = min(min_time, cpuTime);
		}
	}
	for (int i = 0; i < ioNumb; i++)
	{
		long ioTime = devices[i]->getServiceEnd();
		if (ioTime >= 0) {
			min_time = min(min_time, ioTime);
		}
	}
	sim_time = min_time;
}


QueueIO* CPUscheduler::get_devices_queues(int i)
{
	return devices_queues[i];
}


CPU* CPUscheduler::get_cpus(int i)
{
	return cpus[i];
}

vector<IOdevice*> CPUscheduler::get_devices()
{
	return devices;
}

void CPUscheduler::generateProcess()
{
	Process* p = new Process(sim_time, rng);
	CPUqueue.pushProcess(p);
	p->set_ReadyQTime(sim_time);
	allProcesses.push_back(p);
	next_process_time = sim_time + rng->tpg->Rand();							//generator wyk³adniczy;
	if (programModeNumb != 0) {
		printf("__________________________*|*__________________________ \n Time: %d - Process %d has been generated \n", sim_time, p->get_ID());
		program_mode(programModeNumb);
	}
}

void CPUscheduler::checkEndCPUProcessing(StatisticsHolder* statistics)
{
	for (int i = 0; i < cpuNumb; i++)
	{
		if (sim_time == cpus[i]->getServiceEnd())
		{
			Process* p = cpus[i]->get_process_cpu();
			if (sim_time > steady_state) {
			statistics->setNewUtilization(i, cpus[i]->getWorkingTime());		
			}
				

			cpus[i]->take_out_process_from_CPU();

			if (p->get_CET() <= 0)
			{
				//zbieranie wyników
				
				processCounter++;
				if (processCounter >= steady_state) {
					//turnaroundVector[i] = p->getTurnaroundTime;
					
					statistics->setNewProcessesCompleted();
					statistics->setNewTurnaroundTime(p->getProcessingTime(sim_time));
					statistics->setTotalReadyQTime(p->get_totalQTime(), sim_time, p->get_ID());

					//int testowyTurnaround = p->getProcessingTime(sim_time);
					statistics->setTurnaroundVector(processCounter-1,p->getProcessingTime(sim_time));
				}
				//p->setCompletedTime(sim_time);
				if (programModeNumb != 0) {
					printf("__________________________*|*__________________________ \n Time: %d - Process %d has been deleted and removed from CPU %d \n", sim_time, p->get_ID(), i);
					program_mode(programModeNumb);					
				}
				delete p;
			}
			else {
				//dodaj do io
				int IO_id = p->get_IOD();				
				int IOexec_time = p->get_ioExecTime();
				devices_queues[IO_id]->add_to_queueIO(p);	
				if (programModeNumb != 0) {
					printf("__________________________*|*__________________________ \n Time: %d - Process %d ends work on CPU %d \n", sim_time, p->get_ID(), i);
					program_mode(programModeNumb);
				}
			}
		}
	}
	
}

void CPUscheduler::checkEndIOProcessing()
{
	for (int i = 0; i < ioNumb; i++)
	{
		if (sim_time == devices[i]->getServiceEnd())
		{
			Process* p = devices[i]->get_process_io();
			int CET_time = p->get_CET();
			int IOstart = (CET_time >1) ? ((int) (rng->tpio->Rand()*CET_time)) % (CET_time) : 0;	//IOstart z zakresu (0,CET_time)

			int n = 100000;
			std::vector<int> uniformHistogram;
			int IOdev = ((int) (rng->tpio->Rand()*ioNumb)) % ioNumb; //0->IOdevices
			int IOT_occupation= ((int) (rng->tpio->Rand()*10)) % 10 + 1; 
			p->set_IOT(IOstart);
			p->set_ReadyQTime(sim_time);

			CPUqueue.pushProcess(p);
			devices[i]->take_out_process_from_IO();
			if (programModeNumb != 0) {
				printf("__________________________*|*__________________________ \n Time: %d - Process %d ends work on IO %d \n", sim_time, p->get_ID(), i);
				program_mode(programModeNumb);
			}



			
		}
	}
}

bool CPUscheduler::checkStartCPUProcessing()
{
	bool res = false;
	if (CPUqueue.getLength())
	{
		for (int i = 0; i < cpuNumb; i++)
		{
			if (!cpus[i]->cpuStatus())
			{
				Process *p = CPUqueue.getNextProcess();
				cpus[i]->assign_process_to_cpu(p,sim_time);
				p->update_totalQTime(sim_time);
				res = true;
				if (programModeNumb != 0) {
					printf("__________________________*|*__________________________ \n Time: %d - Process %d start working on CPU %d \n", sim_time, p->get_ID(), i);
					program_mode(programModeNumb);
				}
				break;
			}
			
		}
	}
	return res;
}


bool CPUscheduler::checkStartIOProcessing()
{
	bool res = false;
	for (int i = 0; i < ioNumb; i++)
	{
			if ((!devices[i]->IO_status())&&(devices_queues[i]->status()))
			{
				Process *p = devices_queues[i]->remove_from_queueIO();
				devices[i]->assign_process_to_IO(p, sim_time);
				res = true;
				if (programModeNumb != 0) {
					printf("__________________________*|*__________________________ \n Time: %d - Process %d start working on IO %d \n", sim_time, p->get_ID(), i);
					program_mode(programModeNumb);
				}
			}
	}
	return res;
}

void CPUscheduler::program_mode(int mode)
{
	if (mode >= 1) {
		getchar();
	}
}

CPUscheduler::CPUscheduler(RNG * g, int mode, int id, int maxP, int steady): programModeNumb(mode), maxProcesses(maxP), steady_state(steady)
{
	processCounter = 0;
	rng = g;
	devices_queues.resize(4);
	CPUqueue.clear();
	devices.resize(4);
	cpus.resize(3);
	for (int i = 0; i < 4; i++)
	{
		devices_queues[i] = new QueueIO();
		devices[i] = new IOdevice();
	}
	for (int i = 0; i < 3; i++) {
		CPU* cpu = new CPU();
		cpus[i] = cpu;
	}
	sim_time = 0;
	next_process_time = rng->tpg->Rand(); 	//exp generator
	simId = id;
	}


CPUscheduler::~CPUscheduler()
{
	rng = nullptr;
}


void CPUscheduler::Simulate()
{
	StatisticsHolder* statistics = new StatisticsHolder(simId);
	total_time = 30000;
	
	long steadyStateTime = -1;
	//(sim_time < total_time)&&	
	while (processCounter < maxProcesses)
	{
		if (sim_time == next_process_time)
		{
			generateProcess();
			}
		checkEndCPUProcessing(statistics);
		checkEndIOProcessing();

		
		bool trigger = false;
		do {
			trigger = false;
			//sprawdziæ czy rozpoczêcie na CPU
			trigger |= checkStartCPUProcessing();

			//sprawdziæ czy rozpoczêcie na IO
			trigger |= checkStartIOProcessing();
		} while (trigger);
		if (processCounter >= steady_state) {
			if (steadyStateTime < 0) steadyStateTime = sim_time;
			statistics->setReadyQSize(CPUqueue.getLength(), sim_time);
		}
		UpdateSimTime();				//aktualizacja sim_time	
	}

	
	statistics ->saveToFiles(sim_time - steadyStateTime);
	statistics->resultDisplay(sim_time - steadyStateTime);
}
