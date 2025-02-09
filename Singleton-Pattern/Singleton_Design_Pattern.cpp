/*
Creational Design Patterns (Responsible for object creation)
✅ Singleton → Ensures only one instance of a class exists and provides a global access point.

The Singleton pattern ensures that only one instance of a class exists and provides a global access point to that instance.
Key Points to Consider:
✅ Only One Instance → The class should allow only one object to be created.
✅ Private Constructor → Prevents instantiation from outside the class.
✅ Deleted Copy Constructor & Assignment Operator → Prevents duplication.
✅ Static Method for Access → Provides a controlled way to get the single instance.
✅ Thread Safety → Ensure the instance is created safely in a multi-threaded environment.
✅ Proper Cleanup → Manage memory (e.g., atexit() or unique_ptr) to avoid memory leaks.
✅ Destructor Consideration → Prevent clients from manually deleting the instance (delete this; is unsafe).
*/

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

class Logger {
  private:
    static int count;
    static unique_ptr<Logger> loggerInstance;//static Logger* loggerInstance;
    static mutex mtx; // For thread-safe lock

    // For singleton design, always keep the constructor (all types) private to prevent multiple instances
    // Type1: Default constructor
    Logger() {
        cout << "New instance created " << count++ << endl;
    }
    
    // Type2: Copy constructor (deleted to prevent copying)
    Logger(const Logger&) = delete;
    
    // Type3: Assignment operator (deleted to prevent assignment)
    Logger& operator=(const Logger&) = delete;

  public:
    void Log(string msg) {
        cout << msg << endl;
    }

    // Static method to get the singleton instance with thread safety
    static Logger* getLogger() {
        if (loggerInstance == nullptr) { // First check (fast path)
            lock_guard<mutex> lock(mtx); // Auto-lock and unlock (RAII principle)
            if (loggerInstance == nullptr) { // Second check (safe path)
            //C++98
                //loggerInstance = new Logger();
                //atexit(deleteLogger); // Register cleanup function using atexit
                //In the Singleton pattern, we cannot make the destructor delete the instance
                loggerInstance.reset(new Logger()); //C++11 onwards
            }
        }
        return loggerInstance.get();
    }
    
    /*C++98 standard
    void deleteLogger(){
        delete loggerInstance;
        loggerInstance= null;
    }*/
};

// Define static variables outside the class
int Logger::count = 1;
mutex Logger::mtx;
unique_ptr<Logger> Logger::loggerInstance=nullptr;//Logger* Logger::loggerInstance = nullptr;

// Simulated user logging functions
void user1Log(void) {
    auto user1 = Logger::getLogger();
    user1->Log("User1 logged");
}

void user2Log(void) {
    auto user2 = Logger::getLogger();
    user2->Log("User2 logged");
}

int main() {
    // Non-singleton approach (commented out for understanding)
    /* auto user1 = make_shared<Logger>();
    user1->Log("User1 logged");
    auto user2 = make_shared<Logger>();
    user2->Log("User2 logged"); */

    // Singleton approach (direct calls)
    /* auto user1 = Logger::getLogger();
    user1->Log("User1 logged");
    auto user2 = Logger::getLogger();
    user2->Log("User2 logged"); */

    // Thread-safe singleton test
    thread t1(user1Log);
    thread t2(user2Log);

  // Pass arguments to the thread function
  //void userLog(int userId, string message)
  //  thread t1(userLog, id, msg); 

    t1.join();
    t2.join();

    return 0;
}
