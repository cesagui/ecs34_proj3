#include "DSVWriter.h"
#include "DataSink.h"
#include "StringUtils.h"


// The SImplementation construct is going to contain implementation details of the 
// class, which we want to keep hidden from users. Examples of what we would have in
// here are any private datatypes, any memory we want to allocate/deallocate


struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> s_sink;
    char s_delim;
    // NOTE: question to ask on Piazza: If I pass it a string containing the delimiter, and set 
    bool s_quoteall;
    bool first_row = true;

    // the following is a constructor for SImplementation, with three parameters
    // these are used to initialize the variables of the SImplementation struct
    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : s_sink(sink), s_delim(delimiter), s_quoteall(quoteall) {}
    
};

// Constructor for CDSVWriter:
// the parameters are passed in to create a new pointer to a SImplementation struct
// with these parameters

// explanation of ternary operator: s used to check if the delimiter is a double-quote
// (") character. If it is, it replaces it with a comma (,), otherwise, it uses the
// original delimiter.

CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : DImplementation(std::make_unique<SImplementation>(sink, (delimiter == '\"') ? ',' : delimiter, quoteall)) {
}


CDSVWriter::~CDSVWriter() = default; // default destruct operator

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    

    // we want quoteall to be true (to set double quotes __\"__ around the entire string) under three conditions
    // 1. that we see the delimiter in any of the strings
    // 2. that we see a double quote anywhere (revisit this in the main loop)
    // 3. that we see a newline character
    // if any of these hold, set quoteall to true; we find out if this is true by looping through the whole loop

    // iterate through every string of the row vector
    if (DImplementation->first_row){
        DImplementation->first_row = false;
    } else {
        DImplementation->s_sink->Put('\n');
    } 

    for (const std::string &field : row){
        // use find to find the first occurence of a character within a string
        
        // delimiter check
        size_t find = field.find(DImplementation->s_delim);
        if (find != std::string::npos) DImplementation->s_quoteall = true;

        // double quote check
        find = field.find("\"");
        if (find != std::string::npos) DImplementation->s_quoteall = true;
        
        // newline check
        find = field.find("\n");
        if (find != std::string::npos) DImplementation->s_quoteall = true;
    }    

    
    // get the last vector from the start    
    std::string last_row = row[row.size() - 1];

    // iterate through every element of the row vector
    for (const std::string &field : row){
        
        std::string iter = StringUtils::Replace(field, "\"", "\"\"");
        
        if(DImplementation->s_quoteall){
            DImplementation->s_sink->Put('\"');
        }

        // iterate through every single character in the current element
        for (char curr_character : iter) {
            DImplementation->s_sink->Put(curr_character);
        }
        
        if(DImplementation->s_quoteall){
            DImplementation->s_sink->Put('\"');
        }

        // add the delimiter if it's on any row other than the last one
        if (field != last_row)
            DImplementation->s_sink->Put(DImplementation->s_delim);
    }
    return true;
}