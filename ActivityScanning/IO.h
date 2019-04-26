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
	Process* process_io; //zmienna przechowuj�ca proces w urz�dzeniu
	long serviceEnd;
	long serviceStart;
	long getProcessingTime();


};
