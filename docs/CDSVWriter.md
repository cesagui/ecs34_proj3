# CDSVWriter
## Description:
The CDSVWriter class is utilized to write data to delimiter-separated value (DSV) files, which are files with data separated by a specific character. This allows you to output structured data (ex: list or table of strings) into a text file with a specified delimiter to separate the data. It also ensures that proper formatting is used so special characters are correctly denoted to follow the guidelines of DSV files.
## Class overview:
### Implementation Details
The class contains an internal structure SImplementation to encapsulate implementation details and maintain abstraction.
```
struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> s_sink;
    char s_delim;
    bool s_quoteall;
    bool first_row = true;

    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : s_sink(sink), s_delim(delimiter), s_quoteall(quoteall) {}
};
```
#### Constructor
The constructor initializes the CDSVWriter object with a data sink, a specified delimiter, and a flag to determine whether to quote all fields.
```
CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : DImplementation(std::make_unique<SImplementation>(sink, delimiter, quoteall)) {
}
```
#### Destructor
The class uses the default destructor.
```
CDSVWriter::~CDSVWriter() = default; // default destruct operator
```
## Member Functions
### WriteRow(const std::vector<<std::string>> &row)
Writes a row of CSV data to the specified data sink. Handles quoting of fields based on specified conditions.
```
bool CDSVWriter::WriteRow(const std::vector<std::string> &row);
```
## Example Usage of Class:
```
std::vector<std::string> row = {"Field1", "Field2", "Field3"};
CDSVWriter csvWriter(dataSink, ',', true);
csvWriter.WriteRow(row);
```
Note: Ensure that the appropriate data sink implementation is provided for CDataSink when using this class.
