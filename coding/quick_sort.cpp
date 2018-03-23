#include <iostream>

using namespace std;

int Partition(int * array, int p, int r);
void QuickSort(int * array, int i, int j)
{
    if(i < j)
    {
        int p = Partition(array, i, j);
        QuickSort(array, i, p-1);
        QuickSort(array, p+1, j);
    }
}

int Partition(int * array, int p, int r)
{
    int x = array[r];
    int i = p;
    int j = p;
    while(j < r)
    {
        if(array[j] < x)
        {
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            ++i;
        }
        ++j;
    }
    array[r] = array[i];
    array[i] = x;
    return i;
}

int main()
{
    int array[8] = {3, 2, 4, 1, 8, 5, 7, 6};
    QuickSort(array, 0, 7);

    for(int i=0; i < 8; ++i)
        cout << array[i] << " ";
    cout << endl;
    return 0;
}
