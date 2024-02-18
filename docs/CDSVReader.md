# CDSVReader
## Description:
The CDSVReader class is utilized to read and parse (interpret and break down the data of a file) delimiter-separated value (DSV) files, which are files with data separated by a specific character. This allows you to effectively extract and interpret structured data based on the specified delimiter so you can work with systemized data formats.
## Class overview:
### Implementation Details
This class contains an internal structure "SImplementation" used in order to encapsulate implementation details and maintain abstraction. 
```
struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> s_source;
    char s_delim;

    SImplementation(std::shared_ptr<CDataSource> src, char delimiter)
    : s_source(src), s_delim(delimiter) {}
};
```
#### Constructor
The constructor initializes the CDSVReader object with a data source and a specified delimiter.
```
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delimiter)
    : DImplementation(std::make_unique<SImplementation>(src, delimiter)) {}
```
#### Destructor
This class uses the default destructor.
```
CDSVReader::~CDSVReader() = default;
```
## Member Functions

### End()
Checks if the end of the data source is reached.
```
bool CDSVReader::End() const;
```
### ReadRow(std::vector<<std::string>> &row)
Reads a row from the CSV data, handling quoted fields and the specified delimiter.
```
bool CDSVReader::ReadRow(std::vector<std::string> &row);
```
#### Example Usage:
````
std::vector<std::string> row;
while (CDSVReader::ReadRow(row)) {
    // Process each row as needed
}
````
## Example Usage of Class:
```
// Example instantiation of CDSVReader
std::shared_ptr<CDataSource> dataSource = std::make_shared<CStringDataSource>();
CDSVReader csvReader(dataSource, ',');

// Example reading rows
std::vector<std::string> row;
while (csvReader.ReadRow(row)) {
    // Process each row as needed
}
```