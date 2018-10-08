

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

void PSoCComm::setBytes(int first, int second, int third){
 setFirstByte(first);
 setSecondByte(second);
 setThirdByte(third);
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
