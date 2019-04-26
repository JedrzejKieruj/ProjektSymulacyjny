#ifndef statistics_holder_h
#define statistics_holder_h

#include <map>
#include <vector>

class StatisticsHolder {
    
    
public:
    
    StatisticsHolder(int id);
    ~StatisticsHolder();
    
    void saveToFiles(long time);
	
	void setTotalReadyQTime(long value, long time, int id);
	void setReadyQSize(int value, long time);
    void setNewProcessesCompleted();
    void setNewTurnaroundTime(long value);
    void setNewUtilization(int cpu, long value);
	void resultDisplay(long time);
	void setTurnaroundVector(int idx, int value);

private:
	int simID;
	long completedProcesses;
	long waitingTimeInReadyQueue;
	long sum_Turnaroundtime;
	std::vector<long> cpuUtilization;
	std::vector<int> turnaroundHistogram;
	std::vector<int> turnaroundVector;
	std::vector<std::pair<long, int>> ReadyQSize;
	std::vector<std::pair<long, double>> ReadyQTime;
	std::vector<std::pair<int, long>> ReadyQProcess;
	long totalReadyQTime;

	const double step = 1;				//krok symulacji
};

#endif /* statistics_holder_h */
