/*
Structural Design Patterns (Deals with class composition & object relationships)
✅ Adapter → Converts one interface into another that a client expects.

Definition:
The Adapter Design Pattern is a structural pattern that allows incompatible interfaces to work together by acting as a bridge between them. 
It converts an interface of a class into another interface that clients expect, enabling seamless integration without modifying existing code.

Type:Object Adapter	
Implementation:Uses composition (an adapter class has a pointer/reference to the adaptee(XMLData* xmlData))	
Pros :More flexible, can wrap multiple adaptees	
Cons :Requires more delegation
*/

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class XMLData {
    // Client data is originally in XML format
  private:
    string xmlData;
  public:
    XMLData(string pxmlData) : xmlData(pxmlData) {}

    string getXmlData() {
        return xmlData;
    }
};

class DataAnalyticsTool {
    // This class only processes JSON data
  protected:
    string jsonData;
  public: 
    DataAnalyticsTool(string pjsonData) : jsonData(pjsonData) {}

    virtual void AnalyseData() {
        cout << "Analysing JSON data: " << jsonData << endl; //note this wont dispaly in output
    }
};

class Adapter : public DataAnalyticsTool {
    // Adapter converts XML data to JSON format
  private:
    shared_ptr<XMLData> xmlData; //XMLData* xmlData; //Multiple owners so am gonna use shared_ptr (shared ownership).
  public: 
    Adapter(shared_ptr<XMLData> pxmlData) 
        : DataAnalyticsTool("Converted JSON Data"), xmlData(pxmlData) {}

    void AnalyseData() override {
        cout << "Converting XML Data: " << xmlData->getXmlData() << " to JSON format..." << endl;
        cout << "Analysing the converted JSON data." << endl;
    }
};

class Client {
    // Client processes the data using a DataAnalyticsTool
  public:
    void ProcessingData(shared_ptr<DataAnalyticsTool> tool) {
        tool->AnalyseData();
    }
};

int main() {
    auto xmlData = make_shared<XMLData>("Sample XML Data"); //XMLData* xmlData = new XMLData("Sample XML Data");
    auto tool = make_shared<Adapter>(xmlData);
    auto client = make_shared<Client>();

    client->ProcessingData(tool);

    return 0;
}
//output
//Converting XML Data: Sample XML Data to JSON format...
//Analysing the converted JSON data.
