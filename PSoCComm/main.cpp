

#include "PSoCUART.h"
#include "PSoCComm.h"


int main(){
  PSoCUART UART;
  PSoCComm * comm = &UART;

  const char * buffer;

  printf("Program starts:\n");
  while(true){
  comm->sendCommand();

  buffer = comm->getStatus();
  printf("Prints buffer \n");
  puts(buffer);
  sleep(1);
  }

  return 0;
}
