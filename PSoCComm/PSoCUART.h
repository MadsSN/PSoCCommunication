#pragma once

#include "PSoCComm.h"



class PSoCUART : public PSoCComm {
public:
	PSoCUART();
	~PSoCUART();

private:
	int fd_;
	struct pollfd src[1];
	//Functions
	//Inits
	void initUart();
	void initPolling();
	void openFile();
	void closeFile();
	void setUartSettings();

	//Writes/Read
	void readBytes(int);
	void writeToPSoC(const char [], int);


};
