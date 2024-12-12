#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student
{
    int id;
    char name[20];
    int grades[3];
};
struct Student fillStudent();
void printStudent(struct Student student);
int binarySearchByID(struct Student arr[], int size, int LB, int UB, int id);
void mergeSort(struct Student arr[], int LB, int UB);
void merge(struct Student arr[], int LB, int mid, int UB);

int main()
{
    int isAppRunning = 1;
    int userInput = 0;
    int id, isDBSorted = 0, size = 0;
    struct Student *studentDB = NULL;
    printf("1. Fill the database\n");
    printf("2. Sort the database\n");
    printf("3. Search the database\n");
    printf("4. Display the database\n");
    printf("5. Exit\n");

    while (isAppRunning)
    {
        printf("Your choice: ");
        scanf("%d", &userInput);
        switch (userInput)
        {
        case 1:
            printf("Number of students: ");
            scanf("%d", &size);
            studentDB = (struct Student *)malloc(sizeof(struct Student) * size);
            for (int i = 0; i < size; i++)
            {
                studentDB[i] = fillStudent();
            }
            isDBSorted = 0;
            break;
        case 2:
            if (size)
            {
                mergeSort(studentDB, 0, size - 1);
                printf("Sorted Successfully.\n");
                isDBSorted = 1;
            }
            else
            {
                printf("You must fill the database first.\n");
            }
            break;
        case 3:
            if (size)
            {
                if (isDBSorted)
                {
                    scanf("%d", &id);
                    int studentLoc = binarySearchByID(studentDB, size, 0, size - 1, id);
                    if (studentLoc >= 0)
                    {
                        printStudent(studentDB[studentLoc]);
                    }
                    else
                    {
                        printf("No student found.\n");
                    }
                }
                else
                {
                    printf("You must sort the DB first to search.\n");
                }
            }
            else
            {
                printf("You must fill the database first.\n");
            }
            break;
        case 4:
            if (size)
            {
                for (int j = 0; j < size; j++)
                {
                    printStudent(studentDB[j]);
                }
            }
            else
            {
                printf("You must fill the database first.\n");
            }
            break;

        case 5:
            isAppRunning = 0;
            break;
        }
    }
    return 0;
}
void mergeSort(struct Student arr[], int LB, int UB)
{
    int mid;
    if (LB < UB)
    {
        mid = (UB + LB) / 2;
        mergeSort(arr, LB, mid);
        mergeSort(arr, mid + 1, UB);
        merge(arr, LB, mid, UB);
    }
}
void merge(struct Student arr[], int LB, int mid, int UB)
{

    int list1Idx, list2Idx, i;
    list1Idx = LB;
    list2Idx = mid + 1;
    i = LB;
    struct Student *temp = (struct Student *)malloc((UB - LB + 1) * sizeof(struct Student));
    if (temp)
    {
        while (list1Idx <= mid && list2Idx <= UB)
        {
            if (arr[list1Idx].id < arr[list2Idx].id)
            {
                temp[i - LB] = arr[list1Idx];
                list1Idx++;
                i++;
            }
            else
            {
                temp[i - LB] = arr[list2Idx];
                list2Idx++;
                i++;
            }
        }
        // Leftovers
        while (list1Idx <= mid)
        {
            temp[i - LB] = arr[list1Idx];
            list1Idx++;
            i++;
        }
        while (list2Idx <= UB)
        {
            temp[i - LB] = arr[list2Idx];
            list2Idx++;
            i++;
        }
        for (int j = LB; j <= UB; j++)
        {
            arr[j] = temp[j - LB];
        }
        free(temp);
    }
}

// Student functions
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
int binarySearchByID(struct Student arr[], int size, int LB, int UB, int id)
{
    int mid, loc = -1;
    while (loc == -1 && LB <= UB)
    {
        mid = (LB + UB) / 2;
        if (id == arr[mid].id)
        {
            loc = mid;
        }
        else if (id > arr[mid].id)
        {
            LB = mid + 1;
        }
        else
        {
            UB = mid - 1;
        }
    }

    return loc;
}
