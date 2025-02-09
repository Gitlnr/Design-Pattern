/*
Creational Design Patterns (Responsible for object creation)
✅ Factory Method → Creates objects without specifying the exact class.

The "Factory" Design Pattern is a creational design pattern used to define an interface for creating objects,
but allows subclasses or concrete classes to alter the type of objects that will be created. 

While both Factory Method and Abstract Factory are creational patterns, they differ in their scope:
Factory Method: Creates a single object type (like a button or a text box) based on the specific need.
Abstract Factory: Creates families of related objects (e.g., a whole set of UI components like buttons, text boxes, etc., for different operating systems).
*/


#include <iostream>
#include <string>
using namespace std;

// Step 1: Define interfaces for Button and TextBox
class IButton {
public:
    virtual void OnClickEvent() = 0;
    virtual ~IButton() = default;
};

class ITextBox {
public:
    virtual void ShowTextEvent() = 0;
    virtual ~ITextBox() = default;
};

// Step 2: Define concrete products (Windows, Mac, Linux implementations)
class WinButton : public IButton {
public:
    void OnClickEvent() override {
        cout << "Windows OS Button Click Event" << endl;
    }
};

class MacButton : public IButton {
public:
    void OnClickEvent() override {
        cout << "Mac OS Button Click Event" << endl;
    }
};

class LinuxButton : public IButton {
public:
    void OnClickEvent() override {
        cout << "Linux OS Button Click Event" << endl;
    }
};

class WinTextBox : public ITextBox {
public:
    void ShowTextEvent() override {
        cout << "Windows OS TextBox Event" << endl;
    }
};

class MacTextBox : public ITextBox {
public:
    void ShowTextEvent() override {
        cout << "Mac OS TextBox Event" << endl;
    }
};

class LinuxTextBox : public ITextBox {
public:
    void ShowTextEvent() override {
        cout << "Linux OS TextBox Event" << endl;
    }
};

// Step 3: Define the Factory class with methods for creating both Button and TextBox
class UIFactory {
public:
    static IButton* CreateButton(int osType) {
        switch (osType) {
            case 0: return new WinButton();
            case 1: return new MacButton();
            case 2: return new LinuxButton();
            default:
                cout << "Unknown OS type. Defaulting to Windows." << endl;
                return new WinButton();
        }
    }

    static ITextBox* CreateTextBox(int osType) {
        switch (osType) {
            case 0: return new WinTextBox();
            case 1: return new MacTextBox();
            case 2: return new LinuxTextBox();
            default:
                cout << "Unknown OS type. Defaulting to Windows." << endl;
                return new WinTextBox();
        }
    }
};

// Step 4: Demonstrate usage in main()
int main() {
    cout << "Select OS type (0: Windows, 1: Mac, 2: Linux): ";
    int osType;
    cin >> osType;

    // Use the factory methods to create both Button and TextBox
    IButton* button = UIFactory::CreateButton(osType);
    ITextBox* textBox = UIFactory::CreateTextBox(osType);

    if (button) {
        button->OnClickEvent();    // Call Button functionality
        delete button; // Clean up dynamically allocated objects
    }
    if (textBox) {
        textBox->ShowTextEvent(); // Call TextBox functionality
        delete textBox; // Clean up dynamically allocated objects
    }
    return 0;
}
