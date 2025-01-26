/*
### Definition of Abstract Factory Pattern:
The Abstract Factory Pattern provides an interface for creating families of related or dependent 
objects without specifying their concrete classes.

### When Is It Used?
1. When the system needs to create objects that are related or dependent on each other.
2. When you want to ensure that objects from a specific "family" are used together 
(e.g., GUI components for the same OS).
3. When the exact types of objects to be created need to be determined at runtime.

### Use Cases for Abstract Factory Pattern:
1. Cross-Platform Applications: Creating GUI components (buttons, textboxes, etc.) 
   specific to an operating system (Windows, Mac, Linux).
2. Database Access Layers: Switching between different database providers (e.g., MySQL, PostgreSQL) 
   without changing the core logic.
3. Game Development: Creating different enemy types, weapons, or environments based on the game's theme or level.
4. UI Themes: Building components for light mode, dark mode, or other UI themes dynamically.
5. Device Drivers: Abstracting device-specific implementations like printers, scanners, or input devices. 

*/

#include <iostream>
#include <string>
#include <memory> //for smart pointers
using namespace std;

class IButton{
    public:
    virtual void OnClickEvent() =0;
    virtual ~IButton() = default;
};
class WinButton : public IButton{
    public:
    void OnClickEvent() override{
        cout<<"Windows OS Button Click Event"<<endl;
    }
};
class MacButton : public IButton{
    public:
    void OnClickEvent() override{
        cout<<"MAC OS Button Click Event"<<endl;
    }
};
class LinuxButton : public IButton{
    public:
    void OnClickEvent() override{
        cout<<"Linux OS Button Click Event"<<endl;
    }
};

class ITextBox{
    public:
    virtual void ShowTextEvent() =0;
    virtual ~ITextBox() = default;
};
class WinTextBox : public ITextBox{
    public:
    void ShowTextEvent() override{
        cout<<"Windows OS Text Box Event"<<endl;
    }
};
class MacTextBox : public ITextBox{
    public:
    void ShowTextEvent() override{
        cout<<"MAC OS Text Box Event"<<endl;
    }
};
class LinuxTextBox : public ITextBox{
    public: 
    void ShowTextEvent()override{
        cout<<"Linux OS Text Box Event"<<endl;
    }
};

class IFactory {
   public:
   virtual IButton* CreateButton()=0;
   //virutal unique_ptr<IButton> CreateButton()=0; //using smart pointer
   virtual ITextBox* CreateTextBox()=0;
   //virtual unique_ptr<ITextBox> CreateTextBox() = 0;
   virtual ~IFactory()= default;
};

class WinFactory : public IFactory{
    public:
    IButton* CreateButton() override{
    //unique_ptr<IButton>CreateButton() override
       return new WinButton();
      //return make_unique<WinButton>(); //new = make_unique
    }
    ITextBox* CreateTextBox() override{
       return new WinTextBox();
    }
    /* unique_ptr<ITextBox> CreateTextBox() override {
        return make_unique<WinTextBox>();
    }*/
};

class MacFactory : public IFactory{
    public:
    IButton* CreateButton() override{
       return new MacButton();
    }
    ITextBox* CreateTextBox() override{
       return new MacTextBox();
    }
    /*    unique_ptr<IButton> CreateButton() override {
        return make_unique<MacButton>();
    }
    unique_ptr<ITextBox> CreateTextBox() override {
        return make_unique<MacTextBox>();
    }*/
};
class LinuxFactory : public IFactory{
    public:
    IButton* CreateButton() override{
       return new LinuxButton();
    }
    ITextBox* CreateTextBox() override{
       return new LinuxTextBox();
    }
    /*    unique_ptr<IButton> CreateButton() override {
        return make_unique<LinuxButton>();
    }
    unique_ptr<ITextBox> CreateTextBox() override {
        return make_unique<LinuxTextBox>();
    }*/
};


class GUIAbstractFactory {
    enum  {Windows, Mac ,Linux};
    public:
    //Im using static becasue there is only one function
    static IFactory* CreateOSFactory(int osType){
        switch(osType){
            case Windows : return new WinFactory();
            case Mac : return new MacFactory();
            case Linux: return new LinuxFactory();
            default : 
                cout << "Unknown OS type. Defaulting to Windows." << endl;
                return new WinFactory();
        }
        /* when osType is string 
        if(osType == "Windows"){
            return new WinFactory();
        }else if(osType == "Mac"){
            return new MacFactory();
        }else if(osType == "Linux"){
            return new LinuxFactory();
        }else{
            return new WinFactory();
        }*/
    }
};

int main()
{
   
    cout<< "Please select the OS Type from the list below"<<endl;
    cout<< "0 : Windows  1: MAC  2: Linux"<<endl;
    int osType;
    cin>>osType;
    
    //Static methods belong to the class, not to any object instance.
    //If you accidentally try to call it using an object instance, the compiler will give an error or warning.
    //Since the method is static, you must call it using the scope resolution operator (::) with the class name
   
   //If I don’t use static
   //GUIAbstractFactory factory;
    //IFactory* fact = factory.CreateOSFactory(osType);
   
    IFactory* fact = GUIAbstractFactory::CreateOSFactory(osType); //create a os type
    
    if(!fact){
        cout <<"Failed to create a OS factory"<<endl;
        return -1;
    }
    
    IButton* button = fact->CreateButton(); //first create a button of os type 
    if(button){
        button->OnClickEvent(); //then call a function 
        delete button ;// dellocate the memory fro button
    }
    
    
    ITextBox* textBox = fact->CreateTextBox(); //first create a textbox of os type 
    if(textBox){
      textBox->ShowTextEvent(); //then call a function
      delete textBox;
    }
    
    delete fact;
    
    /*  no need to delete manually
    auto factory = GUIAbstractFactory::CreateOSFactory(osType);

    auto button = factory->CreateButton();
    button->OnClickEvent();

    auto textBox = factory->CreateTextBox();
    textBox->ShowTextEvent();
    */
    
    return 0;
}
