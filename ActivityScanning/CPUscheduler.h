#pragma once
//#include "generator.h"
#include <vector>
#include <queue>
#include "Process.h"
#include "CPU.h"
#include "queueIO.h"
#include "IO.h"
#include "ReadyQueue.h"
#include "generator.h"
#include	"kernels.h"
#include "rng.h"
#include "statistics_holder.h"

using namespace std;

class CPUscheduler
{
public:
	QueueIO* get_devices_queues(int);			 //wektor kolejek do IOs
	CPU* get_cpus(int);							// wektor procesor�w
	vector<IOdevice*> get_devices();			//wektor urz�dze�
	void generateProcess();
	void checkEndCPUProcessing(StatisticsHolder* statistics);
	void checkEndIOProcessing();
	bool checkStartCPUProcessing();
	bool checkStartIOProcessing();

	void program_mode(int i);	//jedynka lub wiecej to tryb pojedynczych wy�wietle�
	

	CPUscheduler(RNG * g, int mode, int id, int maxP, int steady);
	~CPUscheduler();
	void Simulate();
	
private:
	RNG * rng;
	int simId;
	int processCounter;
	long sim_time;
	int maxProcesses;
	long total_time;
	int programModeNumb;
	vector<QueueIO*> devices_queues;	//wektor kolejek do IOs
	ReadyQueue CPUqueue;			 // wektor jednej kolejki ready queue
	vector<CPU*> cpus;					// wektor procesor�w
	vector<IOdevice*> devices;			 //wektor urz�dze� IO
	const int cpuNumb = 3;
	const int ioNumb = 4;
	int steady_state;
	long next_process_time;
	void UpdateSimTime();
	vector<int> turnaroundVector;
};

























/*metody testowania symulacji
independent replications
method of bath means
regenerative method

zmniejszanie wariancji:
control variables
antithetic variates (przeciwstawne zmienianie)

analiza wariancji
regresja liniowa

monte carlo simulation - symulacja gdzie zmiennych jest bardzo duzo i bardzo ciezko utworzyc symulacje
polega na wypunktowaniu wszystkich mozliwych wynik�w, okre�leniu prawdopodobie�stwa ka�dego wyniku, okre�leniu 
powi�zania miedzy randowowymi zmiennymi z tabeli a wynikami, wybraniu randomowych wartosci z tabeli i przeprowadzenie 
eksperymentu, powt�rzenie procesu i zbieranie danych, obliczanie statystyk i wniosk�w.*/