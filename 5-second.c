#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
if (argc != 2) {
printf("Incorrect args\n");
return 0;
}

int fd;
char *fifo = argv[1];

fd = open(fifo, O_RDONLY);
char buffer[100];
read(fd, buffer, sizeof(buffer));
printf("Received from process #1: %s\n", buffer);
if(close(fd) < 0){
printf("Writer: Can\'t close FIFO\n");
exit(-1);
}

fd = open(fifo, O_WRONLY);
char *message = "Hello from process #2!";
write(fd, message, strlen(message) + 1);
if(close(fd) < 0){
printf("Writer: Can\'t close FIFO\n");
exit(-1);
}

return 0;
}
