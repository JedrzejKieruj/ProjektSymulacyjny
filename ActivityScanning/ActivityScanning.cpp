
#include <iostream>
#include "CPUscheduler.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>

int main()
{

	/*
	int n = 100000;
	std::vector<int> uniformHistogram, ExpHistogram;
	uniformHistogram.resize(10, 0);
	ExpHistogram.resize(10, 0);
	Kernels * k = new Kernels();
	k->ReadKernels("kernels.txt");
	RNG * rng = new RNG();
	rng->Initialize(k, 0, 0.57);
	ofstream outputFile, expFile;
	outputFile.open("UniformTimeHist.txt", std::ios::out);
	expFile.open("ExpTimeHist.txt", std::ios::out);
	for (int i = 1; i <= n; i++)
	{
		int val = min(((int)(rng->tpd->Rand(0, 10))), 9);
		uniformHistogram[val]++;
		val = min(((int)(rng->tpg->Rand())), 9);
		ExpHistogram[val]++;
	}
	for (int i = 0; i < uniformHistogram.size(); i++)
	{
		outputFile << uniformHistogram[i] << "  ";
		expFile << ExpHistogram[i] << "  ";
	}
	outputFile << std::endl;
	outputFile.close();
	expFile << std::endl;
	expFile.close();
	*/

	
	int numbOfSimulations;
	int simIndex = 1;
	int programModeNumb;
	int maxProcesses;
	int steadyStateProcesses = 0;
	//double lambdaParameter = 0;


	printf("_____WELCOME TO ACTIVITY SCANNING SIMULATION_____ \n __________How many simulations?__________\n");
	scanf_s("%d", &numbOfSimulations);
	printf("_____Enter 0 for CONTINUOUS MODE or 1 for STEP-BY-STEP mode_____ \n");
	scanf_s("%d", &programModeNumb);
	printf("Processes to generate: \n");
	scanf_s("%d", &maxProcesses);
	printf("Initial phase process number: \n");
	scanf_s("%d", &steadyStateProcesses);
	//printf("Lambda: \n");
	//scanf_s("%f", &lambdaParameter);
	RNG* rng = new RNG;	
	Kernels* k = new Kernels();
	

	//k->GenerateKernels("kernels.txt");
	k->ReadKernels("kernels.txt");

	for (simIndex; simIndex <= numbOfSimulations; simIndex++)
	{	 
		Process::resetId();
		rng->Initialize(k, simIndex, 0.092);
		CPUscheduler* model = new CPUscheduler(rng, programModeNumb, simIndex, maxProcesses, steadyStateProcesses);
		model->Simulate();
	}	
		
		system("pause");
			return 0;
}



// opis generatorów, co tutaj zawrzeæ
// histogramy dla generatorów, sprawdzenie poprawnoœci ich implementacji(dodanie generowania seedsów dla wiêkszej iloœci symulacji)
// result display nie dzia³a poprawnie
// czy average turnaround time ma byæ dla uœredniony dla jednej symulacji czy ma to byc wektor turnaround time'ów uœredniany po X symulacjach
// na podstawie ready q wyznaczamy initial phase,  turnaround time ma byæ równie¿ wektorem dla pojedynczych (wykorzystujemy go ECDF)
// sprawdzanie initial phase, dodanie i zastosowanie omijania fazy inicjalizacyjnej
//  List of events/processes (from Assignment 1) ~ co rozumiemy przez "listê procesów"

//Empirical cumulative distribution function chart of turnaround time samples from ten simulations ~ co przez to rozumiemy
//matlab ma t¹ funkcje, wstawiamy tam potem wektor turnaround timów






//dodanie zmiennej: (average waiting time in the ready queue)

