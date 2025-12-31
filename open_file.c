#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    char fname[50];
    int fd;

    printf("Enter file name:");
    scanf("%s",fname);

    fd=open(fname,O_RDONLY);
    if(fd==-1)
    {
        perror("Error opening file");
        return 1;
    }
    printf("file opened successfully\n");
    printf("file descriptor:%d\n",fd);
    
    close(fd);
    return 0;
}