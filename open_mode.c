#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char fname[50], mode[5];
    int fd, flags = 0;

    printf("Enter file name: ");
    scanf("%s", fname);

    printf("Enter mode (R / W / RW / A): ");
    scanf("%s", mode);

    if (strcmp(mode, "R") == 0)
        flags = O_RDONLY;
    else if (strcmp(mode, "W") == 0)
        flags = O_WRONLY | O_CREAT;
    else if (strcmp(mode, "RW") == 0)
        flags = O_RDWR | O_CREAT;
    else if (strcmp(mode, "A") == 0)
        flags = O_APPEND | O_CREAT | O_WRONLY;
    else
    {
        printf("Invalid mode\n");
        return 1;
    }

    fd = open(fname, flags, 0777);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    printf("File opened successfully\n");
    printf("File Descriptor: %d\n", fd);

    close(fd);
    return 0;
}