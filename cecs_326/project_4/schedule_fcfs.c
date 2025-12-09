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
    // reverses and traverses the list
    head = reverse(head);
    traverse(head, 0);
}