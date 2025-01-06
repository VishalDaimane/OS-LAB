#include <stdio.h>

void main() {
    int fragment[20], b[20], p[20], i, j, nb, np, temp, lowest = 9999;
    static int barray[20], parray[20]; // Allocation flags for blocks and processes

    printf("\n\t\t\tMemory Management Scheme - Best Fit");
    
    // Input the number of blocks
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &np);

    // Input the size of each block
    printf("\nEnter the size of the blocks:\n");
    for (i = 1; i <= nb; i++) {
        printf("Block no.%d: ", i);
        scanf("%d", &b[i]);
    }

    // Input the size of each process
    printf("\nEnter the size of the processes:\n");
    for (i = 1; i <= np; i++) {
        printf("Process no.%d: ", i);
        scanf("%d", &p[i]);
    }

    // Best Fit Allocation
    for (i = 1; i <= np; i++) { // Loop through processes
        lowest = 9999; // Reset lowest for each process
        for (j = 1; j <= nb; j++) { // Loop through blocks
            if (barray[j] != 1) { // If block is not yet allocated
                temp = b[j] - p[i]; // Calculate remaining space in block
                if (temp >= 0 && temp < lowest) { // Find the best-fitting block
                    parray[i] = j;
                    lowest = temp;
                }
            }
        }
        fragment[i] = lowest; // Store the fragment size
        if (parray[i] != 0) { // If a block was allocated
            barray[parray[i]] = 1; // Mark the block as allocated
        }
    }

    // Display the results
    printf("\nProcess_no\tProcess_size\tBlock_no\tBlock_size\tFragment");
    for (i = 1; i <= np; i++) {
        if (parray[i] != 0) { // Process allocated to a block
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, p[i], parray[i], b[parray[i]], fragment[i]);
        } else { // Process not allocated
            printf("\n%d\t\t%d\t\tNot Allocated", i, p[i]);
        }
    }
}
