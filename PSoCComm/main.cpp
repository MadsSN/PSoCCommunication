

#include "PSoCUART.h"
#include "PSoCComm.h"

int state(PSoCComm*& comm){
  const char * buffer;
  buffer = comm->getStatus();
  printf("Prints buffer \n");
  for(int x = 0;x<statusRapportLength;x++){
    printf("%d ",buffer[x]);
  }
  printf("\n");
}

int main(){
  PSoCUART UART;
  PSoCComm * comm = &UART;



  printf("Program starts:\n");
  //while(true){
  comm->sendCommand();
  sleep(5);
  printf("Expect:\n");
  state(comm);
  sleep(5);
  comm->setSecondAxisAngle(150);
  comm->closeHandMovement();
  comm->tiltUpMovement();
  comm->rotateLeftMovement();
  comm->turnLeftMovement();
  comm->sendCommand();
  sleep(5);
  printf("Expect +25:\n");
  state(comm);
  comm->tiltDownMovement();
  comm->setSecondAxisAngle(200);
  comm->rotateRightMovement();
  comm->turnRightMovement();
  comm->openHandMovement();
  comm->sendCommand();
  sleep(2);
  printf("Expect -10:\n");
  state(comm);
  comm->stopHand();
  comm->stopTilt();
  comm->stopTurn();
  comm->stopRotate();
  comm->sendCommand();
  sleep(2);
  printf("Expect same:\n");
  state(comm);
  return 0;
}
