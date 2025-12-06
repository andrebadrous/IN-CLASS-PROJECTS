#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void pickup_forks(int i);
void return_forks(int i);
void *routine(void *arg);
void test(int i);
float random_time();
pthread_mutex_t mutexchopstick[5];
pthread_cond_t self[5];
enum
{
    THINKING,
    HUNGRY,
    EATING
} state[5];

int main()
{
    // initialize states to thinking
    for (int i = 0; i < 5; i++)
    {
        state[i] = THINKING;
    }
    srand(time(NULL));

    // initialize threads, mutexes, and condition variables
    pthread_t phil[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_init(&mutexchopstick[i], NULL);
        pthread_cond_init(&self[i], NULL);
    }

    // creates the threads and calls the routine function
    for (int i = 0; i < 5; i++)
    {
        // variable for the philosopher number
        int *j = malloc(sizeof(int));
        *j = i;
        if (pthread_create(&phil[i], NULL, &routine, j) != 0)
        {
            perror("An error occured when creating the thread");
            return 1;
        }
    }
    // joins the threads (not needed for this project)
    for (int i = 0; i < 5; i++)
    {
        if (pthread_join(phil[i], NULL) != 0)
        {
            printf("An error occured when joining the thread");
            return 2;
        }
    }
    // destroys mutex and condition variable (not needed for this project)
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_destroy(&mutexchopstick[i]);
        pthread_cond_destroy(&self[i]);
    }

    return 0;
}

void *routine(void *arg)
{
    int i = *(int *)arg;
    while (1)
    {
        float think_time = random_time();
        printf("Philosopher %d has started thinking\n", i);
        usleep((int)(think_time * 1000000));
        printf("Philosopher %d thought for %.2f seconds\n", i, think_time);
        pickup_forks(i);
    }
}

void pickup_forks(int i)
{
    state[i] = HUNGRY;
    // locks mutexes
    pthread_mutex_lock(&mutexchopstick[(i + 1) % 5]);
    pthread_mutex_lock(&mutexchopstick[i]);
    // tests if both are free
    test(i);
    while (state[i] != EATING)
    {
        // waits for signal that chopsticks are free
        pthread_cond_wait(&self[(i + 1) % 5], &mutexchopstick[(i + 1) % 5]);
        pthread_cond_wait(&self[i], &mutexchopstick[i]);
    }
    // pick up chopsticks when free
    printf("Philosopher %d has chopstick %d\n", i, ((i + 1) % 5));
    usleep((int)(random_time()*500000));
    printf("Philosopher %d has chopstick %d\n", i, i);
    printf("Philosopher %d has started eating\n", i);

    float eat_time = random_time();
    usleep((int)(eat_time * 1000000));
    printf("Philosopher %d ate for %.2f seconds\n", i, eat_time);
    // return chopsticks
    return_forks(i);
}

void return_forks(int i)
{
    state[i] = THINKING;
    printf("Philosopher %d has returned their chopsticks\n", i);
    //unlocks chopsticks
    pthread_mutex_unlock(&mutexchopstick[(i + 1) % 5]);
    pthread_mutex_unlock(&mutexchopstick[i]);
    // signal chopsticks are free
    pthread_cond_signal(&self[(i + 1) % 5]);
    pthread_cond_signal(&self[i]);
}

void test(int i)
{
    if ((state[(i + 4) % 5] != EATING) && (state[i] == HUNGRY) && (state[(i + 1) % 5] != EATING))
    {
        state[i] = EATING;
    }
}

float random_time()
{
    // random number / max random number will give a range between 0 and 1
    // multiply by 2 and the range will be between 0 and 2
    // add 1 and the range will be between 1 and 3
    float random = (((float)rand() / (float)RAND_MAX)) * 2 + 1.0;
    return random;
}