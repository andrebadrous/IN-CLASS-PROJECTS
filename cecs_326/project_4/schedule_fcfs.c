/**
 * FCFS scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// Your code and design here
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
    head = reverse(head);
    traverse(head, 0);
}