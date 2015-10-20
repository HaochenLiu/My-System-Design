#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton& GetInstance() {
        cout<<"Get instance"<<endl;
        static Singleton m_Instance;
        return m_Instance;
    }

    int GetTest() {
        return m_Test++;
    }
private:
    Singleton() {
        m_Test = 10;
    }
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    int m_Test;
};

int main() {
    Singleton& a = Singleton::GetInstance();
    cout<<"a.GetTest() "<<a.GetTest()<<endl;
    Singleton& b = Singleton::GetInstance();
    cout<<"b.GetTest() "<<b.GetTest()<<endl;
    Singleton& c = Singleton::GetInstance();
    cout<<"c.GetTest() "<<c.GetTest()<<endl;

    int wait = 0;
    cin>>wait;

    return 0;
}
