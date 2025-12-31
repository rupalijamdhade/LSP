#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char ch;
    off_t size;

    if (argc != 2)
    {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    size = lseek(fd, 0, SEEK_END);

    for (off_t i = size - 1; i >= 0; i--)
    {
        lseek(fd, i, SEEK_SET);
        read(fd, &ch, 1);
        write(1, &ch, 1);   // stdout
    }

    close(fd);
    return 0;
}
