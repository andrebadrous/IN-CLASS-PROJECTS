/*
 * Priority scheduling
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

    // gets and runs each task based on priority
    while (head != NULL)
    {
        temp = traverse(head, 1);
        printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, temp->task->burst);
        usleep(temp->task->burst * 1000);
        delete(&head, temp->task);
    }
}
