#include "statistics_holder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>



StatisticsHolder::StatisticsHolder(int id) {
	simID = id;
	completedProcesses = 0;
	sum_Turnaroundtime = 0;
	waitingTimeInReadyQueue = 0;
	cpuUtilization.resize(3,0);
	turnaroundHistogram.resize(200,0);
	ReadyQSize.clear();
	ReadyQTime.clear();
	ReadyQProcess.clear();
}

StatisticsHolder::~StatisticsHolder() {
    
    
}



void StatisticsHolder::saveToFiles(long time) {


	char b[50];
	int n = sprintf_s(b,"./Results/results_sim%d.txt", simID);
	std::string fname = b;
	std::ofstream outputFile(fname, std::ios::out);
	outputFile << " ---------- START OF SIM RUN ---------" << std::endl;
	outputFile << "Throughput : " << ((double)completedProcesses) / ((double)time) << std::endl;
	//outputFile.open("avgTurnaroundTime.txt", std::ios::app);
	outputFile << "Average turnaround time: " << ((double) sum_Turnaroundtime)/((double) completedProcesses) << std::endl;
	//outputFile.open("TurnaroundTimeHist.txt", std::ios::app);
	outputFile << "Turnaround time histogram: " << std::endl;
	double sum = 0;
	for (int i = 0; i < turnaroundHistogram.size(); i++)
		sum += ((double)turnaroundHistogram[i]);
	for (int i=0;i<turnaroundHistogram.size();i++)
		outputFile <<  ((double) turnaroundHistogram[i])/sum << "  ";
	outputFile << std::endl;

	outputFile << "Turnaround time vector: " << std::endl;
	for (int i = 0; i < turnaroundVector.size(); i++)
		outputFile << turnaroundVector[i] << " ";
	outputFile << std::endl;

	//outputFile.open("CPU_Utilization.txt", std::ios::app);
	outputFile << "CPU utilization: " << std::endl;

	for (int i = 0; i < cpuUtilization.size(); i++)
		outputFile << ((double) cpuUtilization[i])/((double) time) << "  ";
	outputFile << std::endl;
//	outputFile.close();
	//outputFile.open("ReadyQTime.txt", std::ios::app);
	outputFile << "Ready Queue waiting time: " << ((double) totalReadyQTime) / ((double) completedProcesses) << std::endl;
	outputFile << "--------- END OF SIM RUN --------" << std::endl;
	outputFile.close();

	outputFile.open("./Results/ReadyQSize.txt", std::ios::app);
	outputFile << "-------New SIM --------" << std::endl;
	for (int i = 0; i < ReadyQSize.size(); i++)
		outputFile << ReadyQSize[i].first << "  " << ReadyQSize[i].second << std::endl;
	outputFile.close();
	outputFile.open("./Results/ReadyQTime.txt", std::ios::app);
	outputFile << "-------New SIM --------" << std::endl;
	for (int i = 0; i < ReadyQTime.size(); i++)
		outputFile << ReadyQTime[i].first << "  " << ReadyQTime[i].second << std::endl;
	outputFile.close();
	n = sprintf_s(b, "./Results/ReadyQProcess_sim%d.txt", simID);
	fname = b;
	outputFile.open(fname, std::ios::out);
	outputFile << "-------New SIM" << std::endl;
	std::sort(ReadyQProcess.begin(), ReadyQProcess.end());
	for (int i = 0; i < ReadyQProcess.size(); i++)
		outputFile << ReadyQProcess[i].first << "  " << ReadyQProcess[i].second << std::endl;
	outputFile.close();
}

void StatisticsHolder::setReadyQSize(int value, long time)
{
	ReadyQSize.push_back(std::pair<long, int>(time, value));
}


void StatisticsHolder::setTotalReadyQTime(long value, long time, int id)
{
	totalReadyQTime += value;
	ReadyQTime.push_back(std::pair<long, double>(time, ((double)totalReadyQTime) / ((double)completedProcesses)));
	ReadyQProcess.push_back(std::pair<int, long>(id, value));
}

void StatisticsHolder::setNewProcessesCompleted() {
	completedProcesses++;
}

void StatisticsHolder::setNewTurnaroundTime(long value) {
	sum_Turnaroundtime += value;
	int idx = (value >= step*200) ? 199 : floor(value / step);
	turnaroundHistogram[idx]++;
}

void StatisticsHolder::setNewUtilization(int cpu, long value) {
    cpuUtilization[cpu] += value;
}

void StatisticsHolder::setTurnaroundVector(int idx, int value)
{	
		turnaroundVector.push_back(value);
}


void StatisticsHolder::resultDisplay(long time)
{	
	double throughput = (((double)completedProcesses) / ((double)time));
	double avgTurnaroundTime = (((double)sum_Turnaroundtime) / ((double)completedProcesses));
	printf("throughput: %f \n",throughput);
	printf("Average turnaround time: %f \n",avgTurnaroundTime);
	printf("Average waiting time in Ready Queue: %f \n", (((double)totalReadyQTime) / ((double)completedProcesses)));

	for (int i = 0; i < cpuUtilization.size(); i++) {
		printf("CPU %d utilization: %f \n", i, (((double)cpuUtilization[i]) / ((double)time)));
	}
	printf("#################################################### \n" );
}








