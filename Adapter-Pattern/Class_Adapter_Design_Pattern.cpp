/*
Type:
Class Adapter
Implementation:
Uses multiple inheritance (inherits from both adaptee and target interface)	No need for explicit delegation, 
Pros:
simpler implementation	
Cons:
Less flexible, cannot wrap multiple adaptees
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
    DataAnalyticsTool() {} // Default constructor for inheritance
    virtual void AnalyseData() {
        cout << "Analysing JSON data: " << jsonData << endl;
    }
};

class Adapter : public DataAnalyticsTool, public XMLData {
    // Class Adapter: Inherits from both DataAnalyticsTool and XMLData
  public:
    Adapter(string xml) : XMLData(xml) {
        // Convert XML data to JSON format
        jsonData = "Converted JSON from: " + getXmlData();
    }

    void AnalyseData() override {
        cout << "Converting XML Data: " << getXmlData() << " to JSON format..." << endl;
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
    auto tool = make_shared<Adapter>("Sample XML Data");
    auto client = make_shared<Client>();

    client->ProcessingData(tool);

    return 0;
}
