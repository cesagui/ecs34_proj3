#include "XMLWriter.h"
#include "XMLEntity.h"
#include "DataSink.h"
#include "StringDataSink.h"
#include <memory>
#include <expat.h>

// The CXMLWriter implementation details are hidden from users, the "SImplementation" internal structure encapsualtes the details

struct CXMLWriter::SImplementation {
    
    // Output data sink, holds a shared pointer so CXMLWriter can write to various data sink types
    std::shared_ptr<CDataSink> s_sink;
    // initializes where pending data is to be written on
    std::string pendingData; 

    // Constructor to initialize the data sink
    SImplementation(std::shared_ptr<CDataSink>sink) : s_sink(std::move(sink)) {}

    // Writes a string to the data sink, converts to std::vector<char> because CDataSink::Write expects a vector 
    bool WriteString(const std::string &str) {
        std::vector<char> buf(str.begin(), str.end());
        return s_sink->Write(buf);
    }
};

// Constructor for CXMLWriter which initailizes the DImplementation unique pointer with the SImplementation instance to hide details
CXMLWriter::CXMLWriter(std::shared_ptr<CDataSink> sink)
    : DImplementation(std::make_unique<SImplementation>(std::move(sink))) {}

// Destructor for CXMLWriter, relies on automatic resource management to perform any clean ups
CXMLWriter::~CXMLWriter() = default;

// Flush any pending data to the data sink, calls WriteString if data needs to be written, makes sure that buffered data is written out
bool CXMLWriter::Flush() {
    
    if (!DImplementation->pendingData.empty()) {   
        return DImplementation->WriteString(DImplementation->pendingData);
    }

    return true;
}

// Writes an XML entity to the data sink depending on the specific type of XML entity 
bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {

    std::string tag;

    // Determines the type of entity and results in the construction of the appropriate XML tag

    switch (entity.DType) {
        case SXMLEntity::EType::StartElement: {

            tag = "<" + entity.DNameData;

            for(const auto &attribute : entity.DAttributes) {
                tag += " " + attribute.first + "=\"" + attribute.second + "\"";
            }

            // Handles self-closing elements
            if (entity.DNameData.find("selfClose:") == 0) {
                std::string tagName = entity.DNameData.substr(10);
                tag = "<" + tagName + "/>";
            }

            else {
                tag += ">";
            }

            break;
        }
    
        // Handles typical end elements
        case SXMLEntity::EType::EndElement: {
            if (entity.DNameData.find("selfClose:") != 0) {
                tag = "</" + entity.DNameData + ">";
            }

            break;
        }
    
        // Handles character data
        case SXMLEntity::EType::CharData: {
            tag = entity.DNameData;
            break;
        }

        default:

            break;    
    }

    // Appends the previously generaetd tag to the pending data
    DImplementation->pendingData += tag;

    // Checks if the pending data length is greater than the threshold and therefore flushes if necessary
    if (DImplementation->pendingData.length() >= 1024) {
        return Flush();
    }

    return true;

}