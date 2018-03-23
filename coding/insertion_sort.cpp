#include <iostream>

using namespace std;

static const int arraySize = 8;
static int array[arraySize] = {0};

void display()
{
    cout << "numbers: ";
    for(int i=0; i < arraySize; ++i)
        cout << array[i] << " ";
    cout << endl;
}

void Init()
{
    cout << "set 8 number:" << endl;
    for(int i=0; i < arraySize; ++i)
    {
        cin >> array[i];
    }
    display();
}

void InsertionSort()
{
    for(int i=1; i < arraySize; ++i)
    {
        int temp = array[i];
        int j = i - 1;
        if(temp < array[j])
        {
            while(j>=0 && temp < array[j])
            {
                array[j+1] = array[j];
                --j;
            }
            array[j+1] = temp;
        }
    }

    display();
}

int main()
{
    bool quit = false;
    int choice = -1;
    while(!quit)
    {
        cout << "**********************" << endl;
        cout << "option 1: set array" << endl;
        cout << "option 2: quit" << endl;
        cout << "**********************" << endl;
        cin >> choice;
        switch(choice)
        {
            case 1:
                Init();
                InsertionSort();
                break;
            case 2:
            default:
                cout << "quting..." << endl;
                quit = true;
        }
    }

    return 0;
}
