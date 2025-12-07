/**
 * Various list operations
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        while (temp->next != NULL)
        {
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
