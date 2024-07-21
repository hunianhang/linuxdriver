#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


// write: ./file_app /dev/xxx 100ask
//  read: ./file_app  /dev/xxx
int main(int argc, char *argv[]){

    int fd;
    int len;
    int buf[100];

    if(argc < 2){
        printf("Usage:\n");
        printf("%s <dev> [string]\n",argv[0]);
        return -1;
    }

    //open
    fd = open(argv[1],O_RDWR);
    if(fd < 0){
        printf("Can not open file %s\n",argv[0]);
        return -1;
    }

    //write 
    if(argc == 3){
        len = write(fd, argv[2],strlen(argv[2]) + 1);
        printf("Write ret = %d\n", len);
    }else {
        len = read(fd, buf,100);
        buf[99] = '\0';
        printf("read str: %s\n", (char*)buf);
    }

    //close
    close(fd);

    return 0;

}
