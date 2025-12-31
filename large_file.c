#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char dname[100], path[200], largest[100] = "";
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    long max = 0;

    printf("Enter directory name: ");
    scanf("%s", dname);

    dp = opendir(dname);
    if (dp == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        printf(path, "%s/%s", dname, entry->d_name);

        if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) {
            if (st.st_size > max) {
                max = st.st_size;
                strcpy(largest, entry->d_name);
            }
        }
    }

    closedir(dp);

    if (max > 0) {
        printf("Largest file: %s\n", largest);
        printf("Size: %ld bytes\n", max);
    } else {
        printf("No regular files found\n");
    }

    return 0;
}
