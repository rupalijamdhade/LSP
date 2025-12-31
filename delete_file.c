#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    char dname[100], path[200];
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    int count = 0;

    printf("Enter directory name: ");
    scanf("%s", dname);

    dp = opendir(dname);
    if (dp == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dname, entry->d_name);

        if (stat(path, &st) == 0 && S_ISREG(st.st_mode) && st.st_size == 0) {
            unlink(path);
            printf("Deleted: %s\n", entry->d_name);
            count++;
        }
    }

    closedir(dp);
    printf("Total deleted files: %d\n", count);
    return 0;
}
