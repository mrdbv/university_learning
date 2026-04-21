#include <iostream>
#include <vector>
using namespace std;

class Logger {
public:
	virtual void log(string message) {
		cout << " Base log : " << message << endl;
	}
	virtual ~Logger() {}
	};
class FileLogger : public Logger {
public :
	void log(string message) override {
		cout << " File : " << message << endl;
	}

};
class EncryptLogger : public Logger {
public : 
	void log(string message) override {
		cout << "Encrypted log :  " << message << "? ? ? ? ? ? ? ?" << endl;
	}
};
int main() {
	vector<Logger*> loggers;
	loggers.push_back(new Logger());
	loggers.push_back(new FileLogger());
	loggers.push_back(new EncryptLogger());
	for (Logger* loggerPtr : loggers) {
		loggerPtr->log("Text message");
	}
	for (Logger* loggerPtr : loggers) {
		delete loggerPtr;
	}
	loggers.clear();

	return 0;
}
