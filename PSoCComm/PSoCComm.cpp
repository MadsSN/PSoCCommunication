

#include "PSoCComm.h"


PSoCComm::PSoCComm(){
  	lastGottenStatus_[0] = 0;
    lastGottenStatus_[1] = 0;
    lastGottenStatus_[2] = 0;
    lastGottenStatus_[3] = 0;

  	dataToSend[0] = 255;
  	dataToSend[1] = 48;
  	dataToSend[2] = 49;
  	dataToSend[3] = 50;
}

PSoCComm::~PSoCComm(){

}

void PSoCComm::sendCommand() {
  writeToPSoC(dataToSend,commandLength);
}

const char * PSoCComm::getStatus() {
	//Write to PSoC to return data.
	requestStatusRapport();

  //Read X bytes.
	readBytes(statusRapportLength);

	//Return a pointer to the status. Const pointer to avoid writes.
	//ALternative pass in pointer, but slightly violates in/out principle.
	return lastGottenStatus_;
}

void PSoCComm::requestStatusRapport(){
  //printf("requestStatus starts:\n");
	writeToPSoC(getStatusByte, 1);
}

void PSoCComm::setFirstByte(int first) {
  dataToSend[1] = first;
}
void PSoCComm::setSecondByte(int second) {
  dataToSend[2] = second;
}
void PSoCComm::setThirdByte(int third) {
  dataToSend[3] = third;
}

void PSoCComm::turnRightMovement() {
  dataToSend[3] = dataToSend[3] & ~0b11000000;
  dataToSend[3] = dataToSend[3] | 0b10000000;
}

void PSoCComm::turnLeftMovement() {
  dataToSend[3] = dataToSend[3] & ~0b11000000;
  dataToSend[3] = dataToSend[3] | 0b01000000;
}

void PSoCComm::stopRotate() {
  dataToSend[3] = dataToSend[3] & ~0b11000000;
}
