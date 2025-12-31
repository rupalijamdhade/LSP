#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    char fname[100];
    struct stat st;

    printf("Enter file name: ");
    scanf("%s", fname);

    if (stat(fname, &st) == -1) {
        perror("stat failed");
        return 1;
    }

    printf("\nFile Information:\n");
    printf("Size: %ld bytes\n", st.st_size);
    printf("Inode: %ld\n", st.st_ino);
    printf("Permissions: %o\n", st.st_mode & 0777);
    printf("Hard Links: %ld\n", st.st_nlink);
    printf("Owner UID: %d\n", st.st_uid);
    printf("Group GID: %d\n", st.st_gid);
    printf("Last Access: %s", ctime(&st.st_atime));
    printf("Last Modify: %s", ctime(&st.st_mtime));

    return 0;
}
