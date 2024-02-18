# CXMLReader
## Description:
The CXMLReader class is utilized to read and parse (interpret and break down the data of a file) eXtensible Markup Language (XML) files, XML being a popular format for storing and transporting structured data. This allows you to effectively extract and interpret information contained in XML files to optimize working with the formatting of XML. It helps nvagiate through XML and handling the data included. 
## Class overview:
### Implementation Details
This class contains an internal structure "SImplementation" which is utilized to encapsualte implementation details and maintain abstraction.
```
struct CXMLReader::SImplementation {
    std::shared_ptr<CDataSource> s_src;
    
    XML_Parser parser;
    
    bool isEnd;
    
    SXMLEntity currentEntity;

    static void XMLCALL HandleStartElement(void *userData, const XML_Char *name, const XML_Char **attributes) {// function code}

    static void XMLCALL HandleEndElement(void *userData, const XML_Char *name) {// function code}

    static void XMLCALL HandleCharData(void *userData, const XML_Char *s, int len) {// function code}

    SImplementation(std::shared_ptr<CDataSource> src) : s_src(std::move(src)), isEnd(false) {// function code}

    ~SImplementation() {
        XML_ParserFree(parser);
    }
};
```
#### Constructor
The constructor initializes the "CXMLReader" object with a data source tailored for XML content.
```
CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src)
    : DImplementation(std::make_unique<SImplementation>(src)) {}
```
#### Destructor
This class uses the default destructor to clean up resources.
```
CXMLReader::~CXMLReader() = default;
```
## Member Functions

### End()
Checks if the end of the XML data source has been reached.
```
bool CXMLReader::End() const;
```
### ReadEntity(SXMLEntity &entity, bool skipcdata = false)
Reads an XML entity from the data source and stores the parsed entity in the "entity" parameter.
```
bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata = false);
```
#### Example Usage of Class:
```
// Ex: Instantiation of CXMLReader
std::shared_ptr<CDataSource> dataSource = std::make_shared<CStringDataSource>();
CXMLReader xmlReader(dataSource);

// Ex: Read XML entities
SXMLEntity entity;
while (xmlReader.ReadEntity(entity)) {
    // Process parsed XML entity as needed
}