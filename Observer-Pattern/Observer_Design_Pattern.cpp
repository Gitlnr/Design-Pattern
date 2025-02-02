#include <iostream>
#include <list>
#include <memory>

using namespace std;

enum {
    User1 = 1,
    User2,
    User3,
};

// Interface or abstract for Subscriber
class ISubscribe {
public:
    virtual void notification(const string& msg) = 0;
    virtual ~ISubscribe() = default; // Ensure proper destruction in derived classes
};

// Concrete User class implementing the Subscriber interface
//derived class becomes concrete if it fully implements all pure virtual functions of an abstract class.
class User : public ISubscribe {
private:
    int userID;
public:
    User(int userID) : userID(userID) {} // Constructor initializer list

    void notification(const string& msg) override {
        cout << "User " << userID << " received message: " << msg << endl;
    }
};

// Publisher (Group class)
class Group {
private:
    list<shared_ptr<ISubscribe>> users; // List of subscribers

public:
    void SubscribeUser(shared_ptr<ISubscribe> user) { //ISubscriber* user
        users.push_back(user);
    }

    void UnsubscribeUser(shared_ptr<ISubscribe> user) {
        users.remove(user);
    }

    void notification(const string& msg) {
        for (const auto& user : users) {
            user->notification(msg);
        }
    }
};

int main() {
    // Create a group using smart pointer
    auto group = make_shared<Group>(); //Group* group = new Group(); delete group

    // Create users using smart pointers
    auto user1 = make_shared<User>(User1);
    auto user2 = make_shared<User>(User2);
    auto user3 = make_shared<User>(User3);

    // Subscribe users to the group
    group->SubscribeUser(user1);
    group->SubscribeUser(user2);
    group->SubscribeUser(user3);

    // Send a notification to all users
    group->notification("Welcome to the Group!");

    // Unsubscribe user1
    group->UnsubscribeUser(user1);
    
    // Send another notification
    group->notification("User1 has left the Group.");

    return 0; // No need to delete objects; smart pointers handle memory management
}
