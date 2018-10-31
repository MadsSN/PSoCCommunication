#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>

unsigned bitcount(char* dataArray, char size)
{
	unsigned count = 0;
  char temp = dataArray[0];
	for (int x = 0; x<size; x++) {
    temp = dataArray[x];
		while (temp) {
			count += (temp & 1);
			temp >>= 1;
		}
	}
	return count;
}

int main(){
    int fd;
    char buffer[8] = "Hello";
    char readbuffer[8] = {0};
    fd = open("/dev/i2c-1", O_RDWR);
    if(fd == -1)
        printf("File not open");
    int ret;
    ret = ioctl(fd, 0x0703, 0x8); // i2cdev sys call (0x0703) to set I2C addr
    if(ret<0)
        printf("could not find i2c device");
    int readNr;
    int count = 0;
    while(true){
        //sprintf(buffer,"%d",count++);
        for(int x = 0;x<7;x++){


        readNr = read(fd, readbuffer, 7);
        if(readNr == -1)
            printf("read no success");

        printf("Reading:");
        for(int x = 0;x<7;x++){
          printf("%d:%d ",x,readbuffer[x]);
        }
        printf("\n");
        sleep(1);
        }
        for(int x = 0;x<6;x++){
          buffer[x] = rand()%180;
        }
        buffer[6] = bitcount(buffer,6);
        readNr = write(fd, buffer, strlen(buffer));
        if(readNr == -1)
            printf("read no success");

        printf("Writing:");
        for(int x = 0;x<7;x++){
          printf("%d:%d ",x,buffer[x]);
        }
        printf("\n");
        sleep(1);
        }
    close(fd);

}
