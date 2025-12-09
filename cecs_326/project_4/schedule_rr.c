/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

/*
 * Your code and design here:
 */

struct node *head;

void add(char *name, int priority, int burst)
{
    // creates task
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    //adds task
    insert(&head, task);
}

void schedule()
{
    struct node *temp;
    head = reverse(head);
    int num = 1;

    // runs until all tasks are complete
    while (head != NULL)
    {
        printf("\nROUND %d\n", num);
        temp = head;
        // traverses the whole list 
        while (temp != NULL)
        {
            // if there are only 10 ms left runs and deletes task
            if (temp->task->burst == 10)
            {
                printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, 10);
                temp->task->burst -= 10;
                usleep(10 * 1000);
                delete(&head, temp->task);
            }
            // if more then 10 ms just runs for some time
            else if (temp->task->burst > 10)
            {
                printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, 10);
                temp->task->burst -= 10;
                usleep(10 * 1000);
            }
            // if less than 10 ms runs and deletes task
            else
            {
                printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, temp->task->burst);
                usleep(temp->task->burst * 1000);
                temp->task->burst = 0;
                delete(&head, temp->task);
            }
            // moves to next task
            temp = temp->next;
        }
        num += 1;
    }
}