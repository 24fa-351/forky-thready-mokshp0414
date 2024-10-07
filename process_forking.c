#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void pattern1(int n);
void pattern2(int n);
void pattern3(int n, int current);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <number_of_things> <pattern_number>\n", argv[0]);
        return 1;
    }

    int numThings = atoi(argv[1]);
    int patternNum = atoi(argv[2]);

    if (numThings < 1 || numThings > 256 || (patternNum < 1 || patternNum > 3))
    {
        fprintf(stderr, "Error: Number of things must be between 1 and 256, and pattern number must be 1, 2, or 3.\n");
        return 1;
    }

    srand(time(NULL)); // Seed for random number generation

    switch (patternNum)
    {
    case 1:
        pattern1(numThings);
        break;
    case 2:
        pattern2(numThings);
        break;
    case 3:
        pattern3(numThings, 1); // Start with process number 1
        break;
    default:
        fprintf(stderr, "Invalid pattern number.\n");
        return 1;
    }

    return 0;
}

void pattern1(int n)
{
    printf("Starting pattern 1 with %d processes...\n", n);
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            int sleep_time = rand() % 8 + 1; // Sleep for 1-8 seconds
            printf("Process %d (PID: %d) beginning\n", i + 1, getpid());
            sleep(sleep_time);
            printf("Process %d (PID: %d) exiting after %d seconds\n", i + 1, getpid(), sleep_time);
            exit(0);
        }
        printf("Parent: created child %d (PID: %d)\n", i + 1, pid);
    }

    for (int i = 0; i < n; i++)
    {
        wait(NULL); // Wait for all child processes to finish
    }

    printf("All processes have completed.\n");
}

void pattern2(int n)
{
    printf("Starting pattern 2 with %d processes...\n", n);
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            int sleep_time = rand() % 8 + 1; // Sleep for 1-8 seconds
            printf("Process %d (PID: %d) beginning\n", i + 1, getpid());
            sleep(sleep_time);
            printf("Process %d (PID: %d) exiting after %d seconds\n", i + 1, getpid(), sleep_time);
            exit(0);
        }
        else
        {
            // Parent process
            printf("Parent: created child %d (PID: %d)\n", i + 1, pid);
            wait(NULL); // Wait for the child to finish
        }
    }

    printf("All children have exited.\n");
}

void pattern3(int n, int current)
{
    if (current > n)
        return; // Stop if current exceeds the number of things

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        int sleep_time = rand() % 8 + 1; // Sleep for 1-8 seconds
        printf("Process %d (PID: %d) beginning\n", current, getpid());
        sleep(sleep_time);

        // Logic for creating further processes based on the fork tree structure
        if (current == 1)
        {
            // Create child process 2
            printf("Process %d (PID: %d) creating Process 2\n", current, getpid());
            pattern3(n, 2); // Call for the next process in the pattern (2)
        }
        if (current == 2)
        {
            // Create child processes 4 and 5
            printf("Process %d (PID: %d) creating Process 4\n", current, getpid());
            pattern3(n, 4);
            printf("Process %d (PID: %d) creating Process 5\n", current, getpid());
            pattern3(n, 5);
        }
        if (current == 3)
        {
            // Create child processes 6 and 7
            printf("Process %d (PID: %d) creating Process 6\n", current, getpid());
            pattern3(n, 6);
            printf("Process %d (PID: %d) creating Process 7\n", current, getpid());
            pattern3(n, 7);
        }

        printf("Process %d (PID: %d) exiting after %d seconds\n", current, getpid(), sleep_time);
        exit(0);
    }
    else
    {
        // Parent process waits for the child to finish
        wait(NULL);
    }
}
