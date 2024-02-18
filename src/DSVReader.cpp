#include "DSVReader.h"
#include "DataSource.h"
#include "StringUtils.h"
#include <iostream>
#include <cstdio>

// The SImplementation construct is going to contain implementation details of the 
// class, which we want to keep hidden from users. Examples of what we would have in
// here are any private datatypes, any memory we want to allocate/deallocate

struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> s_source;
    char s_delim;

    // the following is a constructor for SImplementation, with three parameters
    // these are used to initialize the variables of the SImplementation struct
    SImplementation(std::shared_ptr<CDataSource> src, char delimiter)
    : s_source(src), s_delim(delimiter){}
};

// Constructor for CDSVReader:
// the parameters are passed in to create a new pointer to a SImplementation struct
// with these parameters

// explanation of ternary operator: s used to check if the delimiter is a double-quote
// (") character. If it is, it replaces it with a comma (,), otherwise, it uses the
// original delimiter.
CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter)
    : DImplementation(std::make_unique<SImplementation>(src, (delimiter == '\"') ? ',' : delimiter)){
}

// use default destruct operator
CDSVReader::CDSVReader::~CDSVReader() = default;

bool CDSVReader::End() const{
    bool src_end = DImplementation->s_source->End();
    bool end_of = false;
    char peek;
    DImplementation->s_source->Peek(peek);
    if (peek == EOF){
        end_of = true;
    }
    return (end_of || src_end);
}

bool CDSVReader::ReadRow(std::vector<std::string> &row) { 
    row.clear();
    std::string working = "";
    char temp, peek;
    bool isquoted = false;
    
    // iterate through the entire reader file
    while (!(CDSVReader::End())){
        DImplementation->s_source->Get(temp);
        DImplementation->s_source->Peek(peek);
        // four possibilities to account for
        if(temp == '\"'){
            if (!isquoted)
                isquoted = !isquoted;
            else if (isquoted){
                if (peek == '\"' && !CDSVReader::End()) {
                    DImplementation->s_source->Get(temp);
                    working += temp;
                } else {
                    isquoted = !isquoted;
                }
            }
        } else if (temp == DImplementation->s_delim){
            if (isquoted) {
                working += temp;
            }
            else if (!isquoted) {
                row.push_back(working);
                working = "";
            }
        } else if (temp == '\n') {
            if (isquoted){
                working += temp;
            } else if (!isquoted){
                row.push_back(working);
                working = "";
                break;
            }
        } else {
            working += temp;
        }
    }

    if (CDSVReader::End())
        row.push_back(working);

    for (const std::string& str : row) {
        std::cout << str << std::endl;
    }
    
    return true;
}