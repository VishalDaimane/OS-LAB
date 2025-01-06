#include <stdio.h>
#include <stdlib.h>

// Declare semaphores and variables
int mutex = 1, full = 0, empty = 3, x = 0;

// Function declarations
void producer();
void consumer();
int wait(int);
int signal(int);

int main() {
    int n;
    printf("\n1. PRODUCER\n2. CONSUMER\n3. EXIT\n");
    
    while (1) {
        printf("\nENTER YOUR CHOICE: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                // Producer operation
                if ((mutex == 1) && (empty != 0)) {
                    producer();
                } else {
                    printf("BUFFER IS FULL\n");
                }
                break;

            case 2:
                // Consumer operation
                if ((mutex == 1) && (full != 0)) {
                    consumer();
                } else {
                    printf("BUFFER IS EMPTY\n");
                }
                break;

            case 3:
                // Exit program
                exit(0);

            default:
                printf("INVALID CHOICE\n");
        }
    }
    return 0;
}

// Semaphore wait operation
int wait(int s) {
    return (--s);
}

// Semaphore signal operation
int signal(int s) {
    return (++s);
}

// Producer function
void producer() {
    mutex = wait(mutex);   // Lock critical section
    full = signal(full);   // Increment full buffer count
    empty = wait(empty);   // Decrement empty buffer count
    x++;                   // Increment item count
    printf("\nPRODUCER PRODUCES THE ITEM %d\n", x);
    mutex = signal(mutex); // Unlock critical section
}

// Consumer function
void consumer() {
    mutex = wait(mutex);   // Lock critical section
    full = wait(full);     // Decrement full buffer count
    empty = signal(empty); // Increment empty buffer count
    printf("\nCONSUMER CONSUMES ITEM %d\n", x);
    x--;                   // Decrement item count
    mutex = signal(mutex); // Unlock critical section
}
