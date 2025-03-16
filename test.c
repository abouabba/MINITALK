#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum) {
    printf("Received signal %d\n", signum);
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handler; // Set the handler function
    sigemptyset(&sa.sa_mask); // Do not block any signals during handler execution
    sa.sa_flags = 0; // No special flags

    // Register the handler for SIGINT (Ctrl+C)
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Waiting for SIGINT...\n");
    // while (1) {
    //     pause(); // Wait for a signal
    // }

    return 0;
}
