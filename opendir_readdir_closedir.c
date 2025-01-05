#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // For directory operations

int main() {
    char dirname[256];
    struct dirent *dptr; // Struct to hold directory entry information
    DIR *dir; // Pointer to directory

    // Step 4: Get the directory name
    printf("ENTER DIRECTORY NAME: ");
    scanf("%s", dirname);

    // Step 5: Open the directory
    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1; // Exit with error
    }

    // Step 6: Read the contents of the directory and print them
    printf("Contents of the directory '%s':\n", dirname);
    while ((dptr = readdir(dir)) != NULL) {
        printf("%s\n", dptr->d_name); // Print the name of each entry
    }

    // Step 7: Close the directory
    closedir(dir);
    return 0; // Successful execution
}
