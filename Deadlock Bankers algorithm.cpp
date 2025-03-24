#include <iostream>
#define MAX 20
using namespace std;
//This is still some what WIP and some notes are incomplete

class bankers
{
private: // setup all the variables (Do i need to say what these are? Delete when read)
    int al[MAX][MAX], m[MAX][MAX], n[MAX][MAX], avail[MAX];
    int nop, nor, k, result[MAX], pnum, work[MAX], finish[MAX];
    /* al = allocated resource | m = max resource demanded | n = needed resoures to complete the task | avail = available resources in the system */
    /* nop = number of processes | nor = number of resource types | k = tracks the current process number for safe sequence | results = safe sequence | 
       pnum = checks if the current process number can be executed or not | work = freed up resources that is added to available | finish = track if a process has finished execution*/
public:
    bankers();
    void input();
    void method();
    int search(int);
    void display();
};

bankers::bankers()
{ //Initialize all the variables to zero to prevent it from reading garbage data
    k = 0;
    for (int i = 0;i < MAX;i++)
    {
        for (int j = 0;j < MAX;j++)
        {
            al[i][j] = 0;
            m[i][j] = 0;
            n[i][j] = 0;
        }
        avail[i] = 0;
        result[i] = 0; 
        finish[i] = 0;
    }
}

void bankers::input()
{
    int i, j;
    //This part is for processes ie number of processes P1 P2 P3 P4 P5 like that
    cout << "Enter the number of processes:";
    cin >> nop;
    //This is the needed resources like memory and ram and other idk so resource types will be Resource A B C
    cout << "Enter the number of resources:";
    cin >> nor;
    /*This allocates resource for each block ie P1 has 3 resource tyes needed A B C so Resource A has 1 B has 0 and C has 1 allocated to it so this will be subtracted later */
    cout << "Enter the allocated resources for each process: " << endl;
    for (i = 0;i < nop;i++)
    {
        cout << "\nProcess " << i;
        for (j = 0;j < nor;j++)
        {
            cout << "\nResource " << j << ":";
            cin >> al[i][j];
        }
    }
    // This is the needed resources like memory and ram and other idk so 
    cout << "Enter the maximum resources that are needed for each process: " << endl;
    for (i = 0;i < nop;i++)
    {
        cout << "\nProcess " << i;
        for (j = 0;j < nor;j++)
        {
            cout << "\nResouce " << j << ":";
            cin >> m[i][j];
            n[i][j] = m[i][j] - al[i][j];
        }
    }
    //This is the available amount of resource types that is currently in the system for example 2 for A 3 for B and 1 for C
    cout << "Enter the currently available resources in the system: ";
    for (j = 0;j < nor;j++)
    {
        cout << "Resource " << j << ":";
        cin >> avail[j];
        work[j] = -1;
    }
    for (i = 0;i < nop;i++)
        finish[i] = 0;
}

void bankers::method()
{ // This is the main system to find a safe sequence
    int i = 0, j, flag;
    while (1)
    {
        if (finish[i] == 0) // checks if the process is done if not redo it
        {
            pnum = search(i);
            if (pnum != -1)
            {
                result[k++] = i;
                finish[i] = 1;
                for (j = 0;j < nor;j++)
                {
                    avail[j] = avail[j] + al[i][j];
                }
            }
        }
        i++;
        if (i == nop)
        {
            flag = 0;
            for (j = 0;j < nor;j++)
                if (avail[j] != work[j])

                    flag = 1;
            for (j = 0;j < nor;j++)
                work[j] = avail[j];

            if (flag == 0)
                break;
            else
                i = 0;
        }
    }
}

int bankers::search(int i)
{
    int j;
    for (j = 0;j < nor;j++) 
        if (n[i][j] > avail[j]) // check if the needed resource is greater that the available resource
            return -1; 
    return 0;
}

void bankers::display()
{
    //Output all the results into matrixes in their respetive tables 
    int i, j;
    cout << endl << "OUTPUT:";
    cout << endl << "========";
    cout << endl << "PROCESS\t     ALLOTED\t     MAXIMUM\t     NEED";
    for (i = 0;i < nop;i++)
    {
        cout << "\nP" << i + 1 << "\t     ";
        for (j = 0;j < nor;j++)
        {
            cout << al[i][j] << "  ";
        }
        cout << "\t     ";
        for (j = 0;j < nor;j++)
        {
            cout << m[i][j] << "  ";
        }
        cout << "\t     ";
        for (j = 0;j < nor;j++)
        {
            cout << n[i][j] << "  ";
        }
    }
    //This is the safe process sequence it means that the system will not encounter a deadlock scenario
    cout << "\nThe sequence of the safe processes are: \n";
    for (i = 0;i < k;i++)
    {
        int temp = result[i] + 1;
        cout << "P" << temp << " ";
    }// Opposite of the top this is the unsafe sequence which might result in a deadlock
    cout << "\nThe sequence of unsafe processes are: \n";
    int flg = 0;
    for (i = 0;i < nop;i++)
    {
        if (finish[i] == 0)
        {
            flg = 1;
        }
        cout << "P" << i << " ";
    }
    cout << endl << "RESULT:";
    cout << endl << "=======";
    if (flg == 1) { // check if the best possible route is safe or not
        cout << endl << "The system is not in safe state and deadlock may occur!!";
        cout << endl;
        cout << endl;
    }
    else{
        cout << endl << "The system is in safe state and deadlock will not occur!!";
        cout << endl;
        cout << endl;
    }
}

int main()
{
    cout << " DEADLOCK BANKER’S ALGORITHM " << endl;
    bankers B;
    //calls all the previous methods
    B.input();
    B.method();
    B.display();
}
