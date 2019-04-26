#pragma once

#include "rng.h"

class Process
{
public:
	
	int get_PGT();
	int get_CET();
	int get_IOT();
	int get_IOD();
	long get_totalQTime();
	void set_ReadyQTime(long t);
	int getTurnaroundTime();
	void update_totalQTime(long t);
	int get_ioExecTime();
	int get_ID();
	int get_numbOfExecutedProcesses();
	void uptade_CET_ICT();
	void updateIOToccupation(long time);
	void set_IOT(int time) { IOT = time; };
	long getProcessingTime(long time);
	static void resetId();
	//Process(UniformGenerator* g, long time);

	Process(long bornTime, RNG * g);
	~Process();
private:

	//UniformGenerator* gen;
	int turnaroundTime;			//ca³kowity czas ¿ycia procesu od generacji do ukoñczenia(suma czasów przesiedzenia w procesorze, kolejkach, IO);
	int PGT;
	int CET;
	int IOT_occupation;			//Random variable with uniform distribution between <1, 10>[ms]
	int IOT;					//time between getting an access to the CPU and an I/O call. Random variable with uniform distribution between <0, CET - 1>[ms](natural number).In case of 0, there is no I / O call.
	int IOD;					//number of IO_device
	int total_ioExecTime;		//zmienna przechowuj¹ca ca³kowity czas obs³ugiwania przez Urz¹dzeniaIO - najprawdopodobniej nie potrzebna
	int ioExecTime;				//zmienna przechowuj¹ca wartoœæ ile czasu proces przesiedzia³ w procesorze 
	int processID;
	long ReadyQTime;
	long totalQTime;
	static int ID;
	int numbOfExecutedProcesses;
	long bornTime;
};

