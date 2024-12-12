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
// Queue
struct Student arr[100];
struct Student dequeue(void);
int enqueue(struct Student std);
int loc = 0, front = 0;
int main()
{

    return 0;
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
int enqueue(struct Student std)
{
    int isEnqueued = 0;
    if (loc < sizeof(arr) / sizeof(struct Student))
    {
        arr[loc] = std;
        loc++;
        isEnqueued = 1;
    }
    return isEnqueued;
}
struct Student dequeue(void)
{
    struct Student std;
    if (front < loc)
    {
        std = arr[front];
        front++;
        loc--;
    }

    return std;
}
