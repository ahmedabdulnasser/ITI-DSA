#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
    struct Student *data;
    struct Node *pNext;
    struct Node *pPrev;
};
struct Node *pHead;
struct Node *pTail;
struct Student
{
    int id;
    char name[20];
    int grades[3];
};
// Student Relevant Functions
struct Student *fillStudent();
void printStudent(struct Student student);
// Linked List Relevant Functions
int addNode(struct Student *std);
struct Node *createNode(struct Student *std);
struct Student *searchNodeById(int id);
struct Student *searchNodeByName(char name[20]);
void freeListRecursive(void); // Requried Task - Directly implemented after the main function.
void freeList(void);
void printList(void);
int insertNode(struct Student *std, int loc);
int deleteNode(int loc);
int main()
{
    int isProgramRunning = 1;
    int userInput;
    int loc, id;
    printf("== ITI Student Database == \n");
    printf("1. Add\n");
    printf("2. Insert\n");
    printf("3. Search by ID\n");
    printf("4. Search by Name\n");
    printf("5. Delete\n");
    printf("6. Delete the whole database\n");
    printf("7. Display the database\n");
    printf("8. Exit\n");
    while (isProgramRunning)
    {
        printf("Your choice: ");
        struct Student *stdPtr;
        scanf("%d", &userInput);
        switch (userInput)
        {
        case 1:
            stdPtr = fillStudent();
            addNode(stdPtr);
            break;
        case 2:
            printf("Location to insert: ");
            scanf("%d", &loc);
            stdPtr = fillStudent();
            insertNode(stdPtr, loc);
            break;
        case 3:
            printf("ID: ");
            scanf("%d", &id);
            // TODO: Change it from ptr to normal student then check if it returns anything and based on this decide whether to print or not.
            stdPtr = searchNodeById(id);
            printStudent(*stdPtr);
            break;
        case 4:
            char name[20];
            printf("Name: ");
            scanf("%s", name);
            stdPtr = searchNodeByName(name);
            printStudent(*stdPtr);
            break;
        case 5:
            printf("Location to delete: ");
            scanf("%d", &loc);
            deleteNode(loc);
            break;
        case 6:
            freeList();
            printf("Database has been deleted successfully.\n");
            break;
        case 7:
            printList();
            break;
        case 8:
            isProgramRunning = 0;
            break;
        }
    }
    printList();

    return 0;
}
// Linked List Relevant Function Implementations
void freeListRecursive(void) // Required Task by Eng Mahmoud
{
    if (!pHead)
    {
        pTail = NULL;
    }
    else
    {
        struct Node *ptr;
        ptr = pHead;
        pHead = pHead->pNext;
        free(ptr);
        freeListRecursive();
    }
}
void freeList()
{
    struct Node *ptr;
    while (pHead)
    {
        ptr = pHead;
        pHead = pHead->pNext;
        free(ptr);
    }
    pTail = NULL;
}
struct Node *createNode(struct Student *std)
{
    struct Node *ptr;
    ptr = (struct Node *)malloc(sizeof(struct Node));
    if (ptr)
    {
        ptr->data = std;
        ptr->pNext = NULL;
        ptr->pPrev = NULL;
    }
    return ptr;
}
struct Student *searchNodeById(int id)
{
    struct Node *ptr;
    ptr = pHead;
    while (ptr->data->id != id && ptr)
    {
        ptr = ptr->pNext;
    }
    return ptr->data;
}
struct Student *searchNodeByName(char name[20])
{
    struct Node *ptr;
    ptr = pHead;
    while (strcmp(ptr->data->name, name) != 0 && ptr)
    {
        ptr = ptr->pNext;
    }
    return ptr->data;
}
void printList(void)
{
    struct Node *ptr;
    ptr = pHead;
    while (ptr != NULL)
    {
        printf("%d %s ", ptr->data->id, ptr->data->name);
        for (int i = 0; i < 3; i++)
        {
            printf("%d ", ptr->data->grades[i]);
        }
        printf("\n");
        ptr = ptr->pNext;
    }
}
int addNode(struct Student *std)
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
            ptr->pPrev = pTail;
            pTail = ptr;
        }
    }
    return isSuccessfulAddition;
}
int insertNode(struct Student *std, int loc)
{
    int retVal = 0;
    struct Node *ptr, *tmp;
    ptr = createNode(std);
    if (ptr)
    {
        retVal = 1;
        if (!pHead) // No list
        {
            pHead = pTail = ptr;
        }
        else // List exists
        {
            if (loc == 0)
            {
                pHead->pPrev = ptr;
                ptr->pNext = pHead;
                pHead = ptr;
            }
            else
            {
                tmp = pHead;
                for (int i = 0; i < loc - 1 && tmp; i++)
                {
                    tmp = tmp->pNext;
                }
                if (tmp == pTail || tmp == NULL) // Last node or further
                {
                    pTail->pNext = ptr;
                    ptr->pPrev = pTail;
                    pTail = ptr;
                }
                else // Location is in the mid
                {
                    tmp->pNext->pPrev = ptr;
                    ptr->pNext = tmp->pNext;
                    ptr->pPrev = tmp;
                    tmp->pNext = ptr;
                }
            }
        }
    }
    return retVal;
}
int deleteNode(int loc)
{
    int retVal = 0;
    struct Node *ptr;
    ptr = pHead;
    if (ptr)
    {
        retVal = 1;
        if (loc == 0)
        {
            ptr->pNext->pPrev = NULL;
            pHead = ptr->pNext;
            ptr->pNext = NULL;
            free(ptr);
        }
        else
        {
            for (int i = 0; i < loc && ptr; i++)
            {
                ptr = ptr->pNext;
            }
            if (ptr == pTail || ptr == NULL)
            {
                ptr->pPrev->pNext = NULL;
                pTail = ptr->pPrev;
                ptr->pPrev = NULL;
                free(ptr);
            }
            else
            {
                ptr->pPrev->pNext = ptr->pNext;
                ptr->pNext->pPrev = ptr->pPrev;
                ptr->pNext = ptr->pPrev = NULL;
                free(ptr);
            }
        }
    }
    return retVal;
}
// Student Relevant Function Implementations
struct Student *fillStudent()
{
    struct Student *student;
    student = (struct Student *)malloc(sizeof(struct Student));
    printf("Student Name: ");
    scanf("%s", student->name);

    printf("Student ID: ");
    scanf("%d", &student->id);

    for (int i = 0; i < 3; i++)
    {
        printf("Grade %d: ", i + 1);
        scanf("%d", &student->grades[i]);
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
