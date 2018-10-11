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

#define statusRapportLength 6
#define commandLength 4


class PSoCComm {
public:
	PSoCComm();
	virtual ~PSoCComm();
	void sendCommand();
	const char* getStatus();
	void setSecondAxisAngle(int first);
	void setThirdAxisAngle(int second);
	void turnRightMovement();
	void turnLeftMovement();
	void stopTurn();
	void tiltDownMovement();
	void tiltUpMovement();
	void stopTilt();
	void rotateRightMovement();
	void rotateLeftMovement();
	void stopRotate();
	void openHandMovement();
	void closeHandMovement();
	void stopHand();
protected:
	char dataToSend[commandLength] = {255};
	const char getStatusByte[1] = {254};
	char lastGottenStatus_[statusRapportLength] = {0};

private:
	void requestStatusRapport();

	virtual void readBytes(int) = 0;
	virtual void writeToPSoC(const char [], int) = 0;

};
