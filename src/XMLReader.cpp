#include "XMLReader.h"
#include "XMLEntity.h"
#include "DataSource.h"
#include "StringDataSource.h"
#include <memory>
#include <expat.h>
#include <string>
#include <vector>

// The CXMLReader implementation details are hidden from users, the "SImplementation" internal structure encapsualtes the details
struct CXMLReader::SImplementation {
    
    // Establishes the input data source by declaring a smart pointer
    std::shared_ptr<CDataSource> s_src;
    
    // Establishes an instance of Expat XML parser which is used throughout this class to parse data accordingly
    XML_Parser parser;
    
    // Utilized to track the end of processing (either starting or ending an element, or reading character data)
    bool isEnd;
    
    // Establishes the current XML entity that is being read and holds information about it, including the entity type, name of the element, and any associated attributes
    SXMLEntity currentEntity;

    // Expat callback function to proeprly handle the start of an XML element
    static void XMLCALL HandleStartElement(void *userData, const XML_Char *name, const XML_Char **attributes) {
        auto *implementation = static_cast<SImplementation*>(userData);
        
        // Sets the entity type to StartElement and stores the name of the element
        implementation->currentEntity.DType = SXMLEntity::EType::StartElement;
        implementation->currentEntity.DNameData = name;
        implementation->currentEntity.DAttributes.clear();
        
        // Parses and stores attributes for the current element
        for (int i = 0; attributes[i]; i += 2) {
            implementation->currentEntity.DAttributes.emplace_back(attributes[i], attributes[i + 1]);
        }
        
        // Marks that the start element has been found
        implementation->isEnd = true;
    }
    
    // Expat callback function to proeprly handle the end of an XML element
    static void XMLCALL HandleEndElement(void *userData, const XML_Char *name) {
        auto *implementation = static_cast<SImplementation*>(userData);
        
        // Sets the entity type to Endelement and stores the name of the element
        implementation->currentEntity.DType = SXMLEntity::EType::EndElement;
        implementation->currentEntity.DNameData = name;
        
        // Marks that the end element has been found
        implementation->isEnd = true;
    }

    // Expat callback function to proeprly handle the character data that is in the elements
    static void XMLCALL HandleCharData(void *userData, const XML_Char *s, int len) {
        auto *implementation = static_cast<SImplementation*>(userData);

        // Checks if the entity type is character data or a start element
        if (implementation->currentEntity.DType == SXMLEntity::EType::CharData ||
            
            // Sets the entity type to CharData and appends the character data
            implementation->currentEntity.DType == SXMLEntity::EType::StartElement) {
            implementation->currentEntity.DType = SXMLEntity::EType::CharData;
            implementation->currentEntity.DNameData.append(s, len);
            
            // Marks that the character data has been found 
            implementation->isEnd = true;
        }
    }

    // Constructor for SImplementation to initialize with a data source
    SImplementation(std::shared_ptr<CDataSource> src) : s_src(std::move(src)), isEnd(false) {

        // Constructs an Expat XML parser
        parser = XML_ParserCreate(NULL);
        
        // Sets uesr data to this implementation
        XML_SetUserData(parser, this);
        
        // Sets the callback functions for the element and the characcter data handling
        XML_SetElementHandler(parser, HandleStartElement, HandleEndElement);
        XML_SetCharacterDataHandler(parser, HandleCharData);
    }

    // Destructor for SImplementation and frees the parser resources
    ~SImplementation() {
        XML_ParserFree(parser);
    }
};

// Constructor for CXMLReader to create a new instance with a data source
CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) : DImplementation(std::make_unique<SImplementation>(src)) {
}

// Destructor for CXMLReader which uses automatic resource managemenet for any clean ups
CXMLReader::~CXMLReader() = default;

// Checks if the XML parsing reached the end due to parser completing the process or because the data source no longer has data to read
bool CXMLReader::End() const {
    return DImplementation->isEnd || DImplementation->s_src->End();
}

// Reads the next XML entity from the data source and parses it into the given SXMLEntity object -> Gets characters from the data source, parses through Expat and populates entity with details of the XML entity.
bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    entity.DType = SXMLEntity::EType::CharData;
    entity.DNameData.clear();
    entity.DAttributes.clear();

    while (!DImplementation->isEnd) {
        char buffer[1024];
        
        int bytesRead = 0;
        
        char temp;

        // Retrieves the next character from the data source
        if (!DImplementation->s_src->Get(temp)) {
            DImplementation->isEnd = true;
            return false;
        }

        // Parses the character using XML parser
        if (XML_Parse(DImplementation->parser, &temp, 1, 0) == XML_STATUS_ERROR) {
            return false;
        }

        // Checks if an XML entity was encountered
        if (DImplementation->isEnd) {
            entity = DImplementation->currentEntity;
            DImplementation->isEnd = false;
            return true;
        }

        // Checks for a selfclosing element that is in the start element
        if (entity.DType == SXMLEntity::EType::StartElement && temp == '/') {
            entity.DType = SXMLEntity::EType::EndElement;
            entity.DNameData = DImplementation->currentEntity.DNameData;
            return true;
        }
    }

    return false;
}
