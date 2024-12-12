#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    struct Student *data;
    struct Node *pNext;
};
struct Node *pHead;
struct Node *pTail;
struct Student
{
    int id;
    char name[20];
    int grades[3];
};
struct Student fillStudent();
void printStudent(struct Student student);
int addNode(struct Student std);
struct Node *createNode(struct Student std);
int push(struct Student std);
struct Student pop();

int main()
{
    int isAppRunning = 1;
    int userInput = 0;
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Pop All & Print Elements\n");
    printf("4. Exit\n");
    struct Student std;
    while (isAppRunning)
    {
        printf("Your choice: ");
        scanf("%d", &userInput);
        switch (userInput)
        {
        case 1:
            std = fillStudent();
            push(std);
            break;
        case 2:
            if (pHead)
            {
                std = pop();
                printStudent(std);
            }
            else
                printf("Empty stack\n");
            break;
        case 3:
            if (pHead)
            {

                while (pHead != NULL)
                {
                    struct Student poppedStudent = pop();
                    printStudent(poppedStudent);
                    printf("\n");
                }
            }
            else
            {
                printf("Empty stack\n");
            }
            break;
        case 4:
            isAppRunning = 0;
            break;
        }
    }

    return 0;
}
struct Node *createNode(struct Student std)
{
    struct Node *ptr;
    ptr = (struct Node *)malloc(sizeof(struct Node));
    if (ptr)
    {
        ptr->data = (struct Student *)malloc(sizeof(struct Student));
        if (ptr->data)
        {
            *(ptr->data) = std;
            ptr->pNext = NULL;
        }
        else
        {
            free(ptr);
            ptr = NULL;
        }
    }
    return ptr;
}
int addNode(struct Student std)
{
    int isSuccessfulAddition = 0;
    struct Node *ptr;
    ptr = createNode(std);
    if (ptr)
    {
        isSuccessfulAddition = 1;
        if (!pHead)
        {
            pHead = pTail = ptr;
        }
        else
        {
            pTail->pNext = ptr;
            pTail = ptr;
        }
    }
    return isSuccessfulAddition;
}
// Student Relevant Function Implementations
struct Student fillStudent()
{
    struct Student student;
    printf("Student Name: ");
    scanf("%s", student.name);

    printf("Student ID: ");
    scanf("%d", &student.id);

    for (int i = 0; i < 3; i++)
    {
        printf("Grade %d: ", i + 1);
        scanf("%d", &student.grades[i]);
    }
    return student;
}
void printStudent(struct Student student)
{
    printf("Student Name: %s\n", student.name);
    printf("Student ID: %d\n", student.id);
    printf("Student Grades: \n");
    for (int i = 0; i < 3; i++)
    {
        printf("Grade %d: %d\n", i + 1, student.grades[i]);
    }
}
int push(struct Student std)
{
    int isPushed = 0;
    struct Node *ptr;
    ptr = createNode(std);
    if (ptr)
    {
        isPushed = 1;
        if (!pHead)
        {
            pHead = pTail = ptr;
        }
        else
        {
            ptr->pNext = pHead;
            pHead = ptr;
        }
    }

    return isPushed;
}
struct Student pop()
{
    struct Node *ptr;
    struct Student std;
    if (pHead)
    {
        ptr = pHead;
        pHead = ptr->pNext;
        std = *(ptr->data);
        free(ptr->data);
        free(ptr);
    }
    return std;
}