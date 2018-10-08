
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
char buffer[] = "Hello World";
void * readFunction(void * arg) {
	int amountOfReads = 0;
	char bufs[20];
	int check = 0;
	int fd = *(int *)arg;
	struct pollfd src[1];
	src[0].fd = fd;
	src[0].events = POLLIN;
	src[0].revents = 0;
	int readnr = 0;
	while (true) {
		readnr = 0;
		printf("Goes into waiting for stuff to read\n");
		check = poll(src, 1, -1);
		if (check == 1) {
			printf("Reads actually stuff %d\n", amountOfReads++);
			while (readnr != strlen(buffer)) {
				printf("How often is read in parts of %d?\n", readnr);
				readnr += read(fd, bufs + readnr, strlen(buffer) - readnr);
			}
			if (readnr) {
				printf("The char is %s and read is %d\n", bufs, readnr);
			}
			else {
				printf("Nothing new \n");
			}
		}


	}
}

int main() {
	int serial_fd;
	//Open value

	serial_fd = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
	//serial_fd = open("/dev/serial0", O_RDWR | O_NOCTTY);
	if (serial_fd == -1) {
		fprintf(stderr, "ttyS0 Error is %s (errno=%d)\n", strerror(errno), errno);
		return errno;
	}


	struct termios serialSet;
	memset(&serialSet, 0, sizeof(serialSet));
	serialSet.c_iflag = IGNBRK;
	serialSet.c_cflag = CS8 | CREAD | CLOCAL;
	memset(serialSet.c_cc, _POSIX_VDISABLE, NCCS);
	serialSet.c_cc[VMIN] = 0;
	serialSet.c_cc[VTIME] = 0;

	speed_t baudRate = B115200;
	cfsetispeed(&serialSet, baudRate);
	cfsetospeed(&serialSet, baudRate);

	if (tcsetattr(serial_fd, TCSANOW, &serialSet) == -1) {
		fprintf(stderr, "set Error is %s (errno=%d)\n", strerror(errno), errno);
		return errno;
	}


	pthread_t readThread;
	pthread_create(&readThread, NULL, &readFunction, &serial_fd);
	printf("File is %d\n",serial_fd);

	while (true) {

		printf("Write stuff, expect same return\n");
		write(serial_fd, buffer, strlen(buffer));
		sleep(1);
	}
	close(serial_fd);

}
