

#include "PSoCComm.h"


PSoCComm::PSoCComm(){
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

void PSoCComm::setSecondAxisAngle(int first) {
  if(first<0 || first>180){
    dataToSend[1] = 192;
  }else{
    dataToSend[1] = first;
  }

}
void PSoCComm::setThirdAxisAngle(int second) {
  if(second<0 || second>180){
    dataToSend[2] = 192;
  }else{
    dataToSend[2] = second;
  }
}

void PSoCComm::turnRightMovement() {
  dataToSend[3] = dataToSend[3] & ~0b11000000;
  dataToSend[3] = dataToSend[3] | 0b10000000;
}

void PSoCComm::turnLeftMovement() {
  dataToSend[3] = dataToSend[3] & ~0b11000000;
  dataToSend[3] = dataToSend[3] | 0b01000000;
}

void PSoCComm::stopTurn() {
  dataToSend[3] = dataToSend[3] & ~0b11000000;
}


void PSoCComm::tiltDownMovement() {
	dataToSend[3] = dataToSend[3] & ~0b00110000;
	dataToSend[3] = dataToSend[3] | 0b00100000;
}

void PSoCComm::tiltUpMovement() {
	dataToSend[3] = dataToSend[3] & ~0b00110000;
	dataToSend[3] = dataToSend[3] | 0b00010000;
}

void PSoCComm::stopTilt() {
	dataToSend[3] = dataToSend[3] & ~0b00110000;
}

void PSoCComm::rotateRightMovement() {
	dataToSend[3] = dataToSend[3] & ~0b00001100;
	dataToSend[3] = dataToSend[3] | 0b00001000;
}

void PSoCComm::rotateLeftMovement() {
	dataToSend[3] = dataToSend[3] & ~0b00001100;
	dataToSend[3] = dataToSend[3] | 0b00000100;
}

void PSoCComm::stopRotate() {
	dataToSend[3] = dataToSend[3] & ~0b00001100;
}

void PSoCComm::openHandMovement() {
	dataToSend[3] = dataToSend[3] & ~0b00000011;
	dataToSend[3] = dataToSend[3] | 0b00000010;
}

void PSoCComm::closeHandMovement() {
	dataToSend[3] = dataToSend[3] & ~0b00000011;
	dataToSend[3] = dataToSend[3] | 0b00000001;
}

void PSoCComm::stopHand() {
	dataToSend[3] = dataToSend[3] & ~0b00000011;
}
