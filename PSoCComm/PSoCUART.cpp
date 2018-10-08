//Credits goes to example found and modified from: https://raspberrypi.stackexchange.com/questions/57906/uart-interrupt-in-raspberry-pi-with-c-or-c
#include "PSoCUART.h"



PSoCUART::PSoCUART() : PSoCComm() {
	initUart();
}

PSoCUART::~PSoCUART(){
	closeFile();
}


void PSoCUART::writeToPSoC(const char data[], int length){
	//printf("writeToPsoc starts:\n");
	write(fd_, data, length);
}

void PSoCUART::readBytes(int amountToRead){
	int currentCountOfReadBytes = 0;
	int check = 0;
	//Bytes can happen to be read in batches. Meaning that bytes might come in pairs
	//Or tens, or random amount, so to ensure the correct amount is read, while.
	//Not blocking other processes.
	while(currentCountOfReadBytes<amountToRead){
		//Wait until bytes is available to read.
		check = poll(src, 1, -1);
		if(check == 1){
				 currentCountOfReadBytes += read(fd_, lastGottenStatus_ + currentCountOfReadBytes,
	 				 amountToRead - currentCountOfReadBytes);
		}
	}
}


void PSoCUART::initUart() {
	openFile();
	setUartSettings();
	initPolling();
}

void PSoCUART::openFile(){
	fd_ = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
	printf("File is: %d\n",fd_);
	if (fd_ == -1) {
		fprintf(stderr, "file error is %s (errno=%d)\n", strerror(errno), errno);
		_exit(errno);
	}
}

void PSoCUART::closeFile(){

	close(fd_);
}

void PSoCUART::setUartSettings(){

	struct termios serialSet;
	memset(&serialSet, 0, sizeof(serialSet));
	serialSet.c_iflag = IGNBRK;
	serialSet.c_cflag = CS8 | CREAD | CLOCAL;
	memset(serialSet.c_cc, _POSIX_VDISABLE, NCCS);
	serialSet.c_cc[VMIN] = 0;
	serialSet.c_cc[VTIME] = 0;

	//Set speed
	speed_t baudRate = B115200;
	cfsetispeed(&serialSet, baudRate);
	cfsetospeed(&serialSet, baudRate);

	//Apply settings

	if (tcsetattr(fd_, TCSANOW, &serialSet) == -1) {
		fprintf(stderr, "set Error is %s (errno=%d)\n", strerror(errno), errno);
		_exit(errno);
	}

}

void PSoCUART::initPolling(){
	src[0].fd = fd_;
	src[0].events = POLLIN;
	src[0].revents = 0;
}
