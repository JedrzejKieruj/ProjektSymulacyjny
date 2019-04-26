#pragma once

class Process;

class IOdevice
{
public:
	void take_out_process_from_IO();
	void assign_process_to_IO(Process*, long time); 
	long getServiceEnd();
	IOdevice();
	~IOdevice();
	Process* get_process_io();
	bool IO_status(){return process_io != nullptr;}

private:
	Process* process_io; //zmienna przechowuj¹ca proces w urz¹dzeniu
	long serviceEnd;
	long serviceStart;
	long getProcessingTime();


};
