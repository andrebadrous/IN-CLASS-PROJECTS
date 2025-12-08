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
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    insert(&head, task);
}

void schedule()
{
    struct node *temp;
    head = reverse(head);
    int num = 1;

    while (head != NULL)
    {
        printf("\nROUND %d\n", num);
        temp = head;
        while (temp != NULL)
        {
            if (temp->task->burst == 10)
            {
                printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, 10);
                temp->task->burst -= 10;
                usleep(10 * 1000);
                delete(&head, temp->task);
            }
            else if (temp->task->burst > 10)
            {
                printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, 10);
                temp->task->burst -= 10;
                usleep(10 * 1000);
            }
            else
            {
                printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, temp->task->burst);
                usleep(temp->task->burst * 1000);
                temp->task->burst = 0;
                delete(&head, temp->task);
            }
            temp = temp->next;
        }
        num += 1;
    }
}