#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

int main() 
{
    char dname[100], fname[100];
    DIR *dp;
    struct dirent *entry;
    char fullpath[PATH_MAX];

    printf("Enter directory name: ");
    scanf("%s", dname);

    printf("Enter file name: ");
    scanf("%s", fname);

    dp = opendir(dname);
    if (dp == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, fname) == 0) {
            realpath(dname, fullpath);
            printf("File found at: %s/%s\n", fullpath, fname);
            closedir(dp);
            return 0;
        }
    }

    printf("File not found\n");
    closedir(dp);
    return 0;
}
