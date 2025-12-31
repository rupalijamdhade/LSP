#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char fname[100], str[200];
    int fd, bytes;

    printf("Enter file name: ");
    scanf("%s", fname);

    printf("Enter string: ");
    scanf(" %[^\n]", str);

    fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    bytes = write(fd, str, strlen(str));
    printf("Bytes written: %d\n", bytes);

    close(fd);
    return 0;
}
rupali