# CXMLWriter
## Description:
The CXMLWriter class is utilized to write data to eXtensible Markup Language (XML) files, XML being a popular format for storing and transporting structured data. This allows you to create XML documents and format them based on the structure guidelines of XML. By properly generating XML elements, this class streamlines the process of working with XML data and writing data that adheres to its formatting.
## Class overview:
### Implementation Details
This class contains an internal structure "SImplementation" which is utilized to encapsualte implementation details and maintain abstraction.
```
struct CXMLWriter::SImplementation {
    std::shared_ptr<CDataSink> s_sink;
    std::string pendingData;

    SImplementation(std::shared_ptr<CDataSink> sink) : s_sink(std::move(sink)) {}

    bool WriteString(const std::string &str) {
        std::vector<char> buf(str.begin(), str.end());
        return s_sink->Write(buf);
    }
};
```
#### Constructor
The constructor initializes the CXMLWriter object with a data sink which directs the XML output.
```
CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink)
    : DImplementation(std::make_unique<SImplementation>(std::move(sink))) {}
```
#### Destructor
This class uses the default destructor to clean up resources.
```
CXMLWriter::~CXMLWriter() = default;
```
## Member Functions

### Flush()
Makes sure that all pending XML data is written to the data sink.
```
bool CXMLWriter::Flush();
```
### WriteEntity(const SXMLEntity &entity)
Writes an XML entity to the document while handling elements, attributes, and character data.
```
bool CXMLWriter::WriteEntity(const SXMLEntity &entity);
```
#### Example Usage of Class:
```
// Create an instance of the class and specify a data sink where XML data will be written
std::shared_ptr<CDataSink> dataSink = std::make_shared<CStringDataSink>();
CXMLWriter xmlWriter(dataSink);

SXMLEntity startElement = {SXMLEntity::EType::StartElement, "root"};
SXMLEntity endElement = {SXMLEntity::EType::EndElement, "root"};
SXMLEntity charData = {SXMLEntity::EType::CharData, "example text"};

// Written using "WriteEntity" method and "Flush" to ensure data is written to the sink.
xmlWriter.WriteEntity(startElement);
xmlWriter.WriteEntity(charData);
xmlWriter.WriteEntity(endElement);
xmlWriter.Flush();
```
Note: Ensure a suitable implementation for "CDataSink" is provided when utilizing this class so the XML data is directed to the indended output medium.