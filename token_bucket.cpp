#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

class TokenBucket {
public:
	TokenBucket(int cap, int tps) {
		capacity = cap;
		tokenps = tps;
		tokens = 0;
		beginTime = time(0);
	}

	bool getToken() {
		time_t now = time(0);
		tokens += (int)((now - beginTime) * tokenps);
		if (tokens > capacity) {
			tokens = capacity;
		}
		beginTime = now;
		if (tokens < 1) {
			return false;
		}
		tokens--;
		return true;
	}

private:
	int capacity;
	int tokenps;
	int tokens;
	time_t beginTime;
};

int main() {
	TokenBucket bucket(4, 4);

	Sleep(1000);
	for(int i = 0; i < 6; i++) {
		if(bucket.getToken()) {
			cout << "1" << endl;
		}
		else {
			cout << "0" << endl;
		}
	}

	Sleep(1000);
	for(int i = 0; i < 6; i++) {
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
