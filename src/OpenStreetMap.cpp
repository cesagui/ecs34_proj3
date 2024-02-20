#include "OpenStreetMap.h"
#include "StreetMap.h"
#include "XMLReader.h"
#include <memory>
#include <vector>
#include <iostream>
#include <cstddef>
#include <unordered_map>


// Define OSMNode struct that inherits publicly all methods from CStreetMap::SNode
// (certain simple comments are taken from the Project 3 description)

struct OSMNode : public CStreetMap::SNode {
    
    CStreetMap::TNodeID tnode_id;
    
    CStreetMap::TLocation tlocation;
    
    std::unordered_map<std::string, std::string> attributes; // store attributes as key-value pair

    OSMNode(CStreetMap::TNodeID id, CStreetMap::TLocation location) : tnode_id(id), tlocation(location) {}

    ~OSMNode() = default; // utilizes default destructor

    // Returns id of the SNode
    CStreetMap::TNodeID ID() const noexcept override {
        return tnode_id;
    }

    // Returns the lat/lon location of the SNode
    CStreetMap::TLocation Location() const noexcept override {
        return tlocation;
    }

    // Returns number of attributes attached to the SNode
    std::size_t AttributeCount() const noexcept override {
        return attributes.size();
    }

    // Returns key of the attribute at index
    std::string GetAttributeKey(std::size_t index) const noexcept override {
        
        // Returns empty string if index is greater than or equal to AttributeCount()
        if (index >= attributes.size()) {
            return "";
        }

        else {

            // initialize counter
            std::size_t currentPos = 0;

            // iterate over unordered_map and checks if the current position matches the needed index, returns the key of the current attribute if so
            for (const auto& pair : attributes) {
                if (currentPos == index) {
                    return pair.first;
                }

                currentPos += 1;
            }
            
        }

        // return empty string if index not found (shouldn't occur but used to avoid compiler problems)
        return "";

    }

    // Returns whether the value is attached to SNode or not
    bool HasAttribute(const std::string &key) const noexcept override {
        bool hasKey = false;

        // determines whether key is found and changes the bool value to reflect the result
        if (attributes.count(key) > 0) {
            hasKey = true;
        }

        return hasKey;
    }

    // Returns value of the attribute specificed by key 
    std::string GetAttribute(const std::string &key) const noexcept override {
        
        // Returns empty string if the key doesn't exist
        if (attributes.count(key) == 0) {
            return "";
        }

        // Returns the paired value of the key if the key exists
        else {
            return attributes.at(key);
        }

    }

};

// Define OSMNode struct that inherits publicly all methods from CStreetMap::SRoute

struct OSMWay : public CStreetMap::SWay {
    
}

