#include <iostream>
#include <fstream>
#include <cstring>
#define MaxSize 50

using namespace std;

// Store male and female dancer information
typedef struct
{
    char name[20]; // Name
    char sex[10];  // Gender
} Dancer;

typedef struct
{
    Dancer d[MaxSize];
    int front;  // Front of the queue
    int rear;   // Rear of the queue
    int count;  // Number of elements in the queue
} SqQueue;

// Initialize the queue
void initqueue(SqQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// Check if the queue is empty, return 1 if empty, otherwise return 0
int queueempty(SqQueue *q)
{
    if (q->count == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Enqueue function, add d to the queue
void enqueue(SqQueue *q, Dancer d)
{
    q->count++;
    q->d[q->rear] = d;
    q->rear = (q->rear + 1) % MaxSize;
}

// Dequeue function, remove the front element
void dequeue(SqQueue *q)
{
    q->count--;
    q->front = (q->front + 1) % MaxSize;
}

// Access the front element of the queue
Dancer queuefront(SqQueue *q)
{
    return q->d[q->front];
}

int main()
{
    char name[20]; // Name
    char sex[10];  // Gender

    Dancer d[MaxSize]; // Array to store all dancer information
    ifstream r("./dancer.txt"); // Read from txt file

    if (!r.is_open())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    int i = 0;
    // Store the read information into the array
    while (r >> name >> sex)
    {
        strcpy(d[i].name, name);
        strcpy(d[i].sex, sex);
        i++;
    } // i represents the total number of participants

    cout << "Total participants: " << i << endl;

    // Create two queues to store male and female dancers
    SqQueue Mq, Fq; // Mq stores males, Fq stores females

    initqueue(&Mq);
    initqueue(&Fq); // Initialize both queues

    // Enqueue data from the array
    int j = 0;
    char s[10] = "Man";
    char s1[10] = "Woman";
    for (j = 0; j < i; j++)
    {
        if (strcmp(d[j].sex, s) == 0)
        {
            enqueue(&Mq, d[j]);
        }
        else if (strcmp(d[j].sex, s1) == 0)
        {
            enqueue(&Fq, d[j]);
        }
    }

    // Pairing
    int d1 = 0;
    Dancer m[MaxSize], fm[MaxSize];
    while ((queueempty(&Mq) == 1) && (queueempty(&Fq) == 1))
    {
        // First dequeue from the shorter queue
        m[d1] = queuefront(&Mq);
        fm[d1] = queuefront(&Fq);
        int dd = d1 + 1;

        cout << "Dance pair " << dd << " members" << endl;
        cout << "Male: " << m[d1].name << endl;
        cout << "Female: " << fm[d1].name << endl;

        // Remove from the queue
        dequeue(&Mq);
        dequeue(&Fq);
        d1++; // Number of people in the shorter queue
    }

    // Re-enqueue the previous queue members for the second round of dancing
    int l = 0;
    while (l < d1)
    {
        // Re-enqueue all members after the shorter queue is fully dequeued
        enqueue(&Mq, m[l]);
        enqueue(&Fq, fm[l]);
        l++;
    }

    while ((queueempty(&Mq) == 1) && (queueempty(&Fq) == 1))
    {
        // Second dequeue from the shorter queue
        Dancer m, fm;
        m = queuefront(&Mq);
        fm = queuefront(&Fq);

        d1++;
        cout << "Dance pair " << d1 << " members" << endl;
        cout << "Male: " << m.name << endl;
        cout << "Female: " << fm.name << endl;

        // Remove from the queue
        dequeue(&Mq);
        dequeue(&Fq);
    }

    cout << "Total dance pairs in this round: " << d1 << endl; // Output the total number of dance pairs

    int d2 = 0;
    while (queueempty(&Mq) == 1)
    {
        d2++;
        Dancer m1 = queuefront(&Mq);
        cout << "\nNext round pairing person " << d2 << " information:" << endl;
        cout << "Name: " << m1.name << ", Gender: " << m1.sex << endl;

        dequeue(&Mq);
    }

    while (queueempty(&Fq) == 1)
    {
        d2++;
        Dancer m1 = queuefront(&Fq);
        cout << "Next round pairing person " << d2 << " information:" << endl;
        cout << "Name: " << m1.name << ", Gender: " << m1.sex << endl;

        dequeue(&Fq);
    }

    return 0;
}
