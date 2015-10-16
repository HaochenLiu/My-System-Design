#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace std::chrono;

class TokenBucket {
public:
    TokenBucket(int cap, int tps) {
        capacity = cap;
        tokenps = tps;
        tokens = 0;
        remaider = 0.0;
        beginTime = high_resolution_clock::now();
    }

    bool getToken() {
        high_resolution_clock::time_point now = high_resolution_clock::now();
        int t = duration_cast<milliseconds>(now - beginTime).count() * tokenps;
        beginTime = now;
        int add = (int)((double)t / (double)1000 + remaider);
        tokens += add;
        remaider = (double)t / (double)1000 + remaider - add;
        if(tokens > capacity) {
            tokens = capacity;
        }
        if(tokens < 1) {
            return false;
        }
        tokens--;
        return true;
    }

private:
    int capacity;
    int tokenps;
    int tokens;
    double remaider;
    high_resolution_clock::time_point beginTime;
};

int main() {
    TokenBucket bucket(4, 4);

    Sleep(1000);
    for(int i = 0; i < 5; i++) {
        if(bucket.getToken()) {
            cout << "1" << endl;
        }
        else {
            cout << "0" << endl;
        }
    }

    Sleep(1000);
    for(int i = 0; i < 5; i++) {
        if (bucket.getToken()) {
            cout << "1" << endl;
        }
        else {
            cout << "0" << endl;
        }
    }

    int wait;
    cin >> wait;

    return 0;
}
