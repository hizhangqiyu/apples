#include <iostream>
#include <string>

using namespace std;

class Singleton
{
    public:
        static void CreateInstance()
        {
            if(!m_Instance)
            {
                m_Instance = new Singleton();
            }
        }

        static Singleton *GetInstance()
        {
            return m_Instance;
        }

        void Destory()
        {
            delete m_Instance;
            m_Instance = NULL;
        }

        void Func()
        {
            cout << m_Str << endl;
        }

    private:
        Singleton(){m_Str = "hello world!";}
        ~Singleton(){};
        string m_Str;
        static Singleton *m_Instance;
};

Singleton* Singleton::m_Instance = NULL;

int main()
{
    Singleton::CreateInstance();

    Singleton::GetInstance()->Func();

    Singleton::GetInstance()->Destory();

    return 0;
}