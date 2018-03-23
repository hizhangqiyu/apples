#include <iostream>

using namespace std;

class MaxHeap
{
public:
    void display()
    {
        cout << "numbers: ";
        for(int i=0; i < m_Size; ++i)
            cout << m_Array[i] << " ";
        cout << endl;
    }

    void Init(int size)
    {
        m_Size = size;
        m_Array = new int[m_Size];
        cout << "set " << m_Size << " numbers: ";
        for(int i = 0; i < m_Size; ++i)
            cin >> m_Array[i];
        cout << endl;
        BuildMaxHeap();
        display();
    }

    void HeapSort()
    {
        int temp = 0;
        int size = m_Size;
        for(int i=m_Size-1; i > 0; --i)
        {
            temp = m_Array[i];
            m_Array[i] = m_Array[0];
            m_Array[0] = temp;
            MaxHeapify(0, --size);
        }
        
        display();
    }

private:
    void MaxHeapify(int i, int size)
    {
        int next = i;
        if(Left(i) < size && m_Array[Left(i)] > m_Array[i])
            next = Left(i);
        if(Right(i) < size && m_Array[Right(i)] > m_Array[next])
            next = Right(i);
        if(next != i)
        {
            int temp = m_Array[i];
            m_Array[i] = m_Array[next];
            m_Array[next] = temp;
            MaxHeapify(next, size);
        }
    }

    int Parent(int i)
    {
        return i/2;
    }

    int Left(int i)
    {
        return 2 * i;
    }

    int Right(int i)
    {
        return 2 * i + 1;
    }

    void BuildMaxHeap()
    {
        for(int i = m_Size-1; i >= 0; --i)
        {
            MaxHeapify(i, m_Size);
        }
    }

    int * m_Array;
    int m_Size;
};

int main()
{
    MaxHeap heap;
    bool quit = false;
    int choice = -1;
    int size = 0;
    while(!quit)
    {
        cout << "**********************" << endl;
        cout << "option 1: init array" << endl;
        cout << "option 2: sort array" << endl;
        cout << "option 3: quit" << endl;
        cout << "**********************" << endl;
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout << "heap size: ";
                cin >> size;
                heap.Init(size);
                break;
            case 2:
                heap.HeapSort();
                break;
            case 3:
            default:
                cout << "quting..." << endl;
                quit = true;
                break;
        }
    }

    return 0;
}
