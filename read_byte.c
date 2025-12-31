#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char fname[100], buffer[1024];
    int fd, n, bytes;

    printf("Enter file name: ");
    scanf("%s", fname);

    printf("Enter number of bytes: ");
    scanf("%d", &n);

    fd = open(fname, O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    bytes = read(fd, buffer, n);
    if (bytes == -1) {
        perror("Read failed");
        close(fd);
        return 1;
    }

    write(1, buffer, bytes);
    printf("\nBytes read: %d\n", bytes);

    close(fd);
    return 0;
}
