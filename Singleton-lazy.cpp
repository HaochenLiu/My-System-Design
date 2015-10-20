#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton* GetInstance() {
        cout<<"Get instance"<<endl;
        if (m_Instance == NULL) {
            cout<<"Create instance"<<endl;
            m_Instance = new Singleton();
        }
        return m_Instance;
    }

    static void DestoryInstance() {
        cout<<"Destroy time"<<endl;
        if(m_Instance != NULL ) {
            cout<<"Delete time"<<endl;
            delete m_Instance;
            m_Instance = NULL;
        }
    }

    int GetTest() {
        return m_Test++;
    }
private:
    Singleton() {
        m_Test = 10;
    }
    static Singleton* m_Instance;
    int m_Test;
};

Singleton* Singleton::m_Instance = NULL;

int main() {
    Singleton* a = Singleton::GetInstance();
    cout<<"a->GetTest() "<<a->GetTest()<<endl;
    Singleton* b = Singleton::GetInstance();
    cout<<"b->GetTest() "<<b->GetTest()<<endl;
    Singleton* c = Singleton::GetInstance();
    cout<<"c->GetTest() "<<c->GetTest()<<endl;
    Singleton::DestoryInstance();

    int wait = 0;
    cin>>wait;

    return 0;
}
