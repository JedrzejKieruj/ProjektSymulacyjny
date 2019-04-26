//#include "pch.h"
#include "Process.h"
#include "generator.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int Process::ID = 0;

int Process::get_PGT()
{
	return PGT;
}

int Process::get_CET()
{
	return CET;
}

int Process::get_IOT()
{
	return IOT;
}

int Process::get_IOD()
{
	return IOD;
}

long Process::get_totalQTime()
{
	return totalQTime;
}

void Process::set_ReadyQTime(long t)
{
	ReadyQTime = t;
}

int Process::getTurnaroundTime()
{
	return turnaroundTime;
}

void Process::update_totalQTime(long t)
{
	if (ReadyQTime > 0)
		totalQTime += t - ReadyQTime;
		ReadyQTime = -1;

}

int Process::get_ioExecTime()
{
	return IOT_occupation;
}

int Process::get_ID()
{
	return processID;
}

int Process::get_numbOfExecutedProcesses()
{
	return numbOfExecutedProcesses;
}

void Process::uptade_CET_ICT()
{
	if (IOT > 0)
	{
		CET -= IOT;
	}
	else
	{
		CET = 0;
	}
	IOT = -1;

}

void Process::updateIOToccupation(long time)
{
	total_ioExecTime += time;
}

long Process::getProcessingTime(long time) {
	return time - this->bornTime;
}
void Process::resetId()
{
	ID = 0;
}
Process::Process(long bornTime, RNG * g)
{	
	processID = ID++;
	PGT = ((int) g->tpg->Rand());
	CET = ((int) (g->tpw->Rand()*50.0)) % 50 + 1;
	IOT_occupation = ((int) (g->tpo->Rand()*10)) % 10 +1;
	IOT = (CET-1 > 0) ? ((int) (g->tpio->Rand()*CET)) % (CET) : 0;
	IOD = ((int) (g->tpd->Rand()*4)) %  4;
	this->bornTime = bornTime;
	ReadyQTime = -1;
	totalQTime = 0;
	turnaroundTime = 0;
}
Process::~Process()
{
	//gen = NULL;
}

