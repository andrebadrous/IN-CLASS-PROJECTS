/**
 * Various list operations
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "task.h"

// add a new task to the list of tasks
void insert(struct node **head, Task *newTask)
{
    // add the new task to the list
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

struct node *reverse(struct node *head)
{
    struct node *curr;
    struct node *prev;
    struct node *next;
    curr = head;
    prev = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }

    return prev;
}

// delete the selected task from the list
void delete(struct node **head, Task *task)
{
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name, temp->task->name) == 0)
    {
        *head = (*head)->next;
    }
    else
    {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name, temp->task->name) != 0)
        {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
struct node *traverse(struct node *head, int type)
{
    // type=0 returns last node;
    // type=1 returns
    struct node *temp;
    temp = head;

    if (type == 0)
    {
        while (temp != NULL)
        {
            printf("Process [%s] With priority [%d] ran for [%d] ms.\n", temp->task->name, temp->task->priority, temp->task->burst);
            usleep(temp->task->burst * 1000);
            temp = temp->next;
        }
        return temp;
    }
    else
    {
        struct node *turn;
        turn = head;

        while (temp != NULL)
        {

            if (temp->task->priority > turn->task->priority)
            {
                turn = temp;
            }
            temp = temp->next;
        }
        return turn;
    }
}
