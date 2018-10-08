#pragma once
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <poll.h>
#include <pthread.h>

#define statusRapportLength 2
#define commandLength 4
class PSoCComm {
public:
	PSoCComm();
	virtual ~PSoCComm();
	void sendCommand();
	const char* getStatus();
	void setBytes(int first, int second, int third);

protected:
	char dataToSend[commandLength];
	const char getStatusByte[1] = {(char)195};
	char lastGottenStatus_[statusRapportLength];

private:
	void requestStatusRapport();
	void setFirstByte(int first);
	void setSecondByte(int second);
	void setThirdByte(int third);
	virtual void readBytes(int) = 0;
	virtual void writeToPSoC(const char [], int) = 0;

};
