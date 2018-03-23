#include <iostream>

using namespace std;

void CountingSort(int *a, int *b, int k)
{
    int *c = new int[k]();
    int i = 0;
    for(i = 0; i < 8; ++i)
        ++c[a[i]];
    for(i = 1; i <= k; ++i)
        c[i] = c[i] + c[i-1];
    for(i = 7; i >= 0; --i)
    {
        b[c[a[i]]-1] = a[i];
        --c[a[i]];
    }

    delete c;
    c = NULL;
}

int main()
{
    int array[8] = {3, 2, 4, 2, 8, 5, 5, 6};
    int result[8] = {0};
    CountingSort(array, result, 8);

    for(int i=0; i < 8; ++i)
        cout << result[i] << " ";
    cout << endl;
    return 0;
}

