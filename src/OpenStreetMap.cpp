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
    
    // store attributes as key-value pair
    std::unordered_map<std::string, std::string> attributes; 

    OSMNode(CStreetMap::TNodeID id, CStreetMap::TLocation location) : tnode_id(id), tlocation(location) {}

    // utilizes default destructor
    ~OSMNode() = default; 

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
            std::size_t current_pos = 0;

            // iterate over unordered_map and checks if the current position matches the needed index, returns the key of the current attribute if so
            for (const auto& pair : attributes) {
                if (current_pos == index) {
                    return pair.first;
                }

                current_pos += 1;
            }
            
        }

        // return empty string if index not found (shouldn't occur but used to avoid compiler problems)
        return "";

    }

    // Returns whether the value is attached to SNode or not
    bool HasAttribute(const std::string &key) const noexcept override {
        bool has_key = false;

        // determines whether key is found and changes the bool value to reflect the result
        if (attributes.count(key) > 0) {
            has_key = true;
        }

        return has_key;
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

// Define OSMWay struct that inherits publicly all methods from CStreetMap::SWay
// (certain simple comments are taken from the Project 3 description)

struct OSMWay : public CStreetMap::SWay {
    
    CStreetMap::TWayID tway_id;

    std::vector<CStreetMap::TNodeID> node_id;

    // store attributes as key-value pair
    std::unordered_map<std::string, std::string> attributes; 

    OSMWay(CStreetMap::TWay id) : tway_id(id) {}

    // utilizes default destructor
    ~OSMWay() = default; 

    // Returns the id of the SWay
    CStreetMap::TWayID ID() const noexcept override {
        return tway_id;
    }

    // Returns the number of nodes in the way
    std::size_t NodeCount() const noexcept override {
        return node_id.size();
    }

    // Returns the node id of the node at the index
    TNodeID GetNodeID(std::size_t index) const noexcept override {
        
        // Returns InvalidNodeID if the index is greater than or equal to NodeCount()
        if (index >= node_id.size()) {
            return InvalidNodeID;
        }

        // Else the node id of the node at the index is returned
        else {
            return node_id[index];
        }
    }

    // Returns the number of attributes attached to SWay
    std::size_t AttributeCount() const noexcept override {
        return attributes.size();
    }

    // Returns the key of the attribute at the index
    std::string GetAttributeKey(std::size_t index) const noexcept override {
        
        // Returns empty string if index is greater than or equal to AttributeCount()
        if (index >= attributes.size()) {
            return "";
        }

        // Else returns the key of the attribute at the index
        else {
            
            // initialize counter
            std::size_t current_pos = 0;

            // iterate over unordered_map and checks if the current position matches the needed index, returns the key of the current attribute if so
            for (const auto& pair : attributes) {
                if (current_pos == index) {
                    return pair.first;
                }

                current_pos += 1;
            }
            
        }

        // return empty string if index not found (shouldn't occur but used to avoid compiler problems)
        return "";

    }

    // Returns whether the value is attached to SWay or not
    bool HasAttribute(const std::string &key) const noexcept override {
        bool has_key = false;

        // determines whether key is found and changes the bool value to reflect the result
        if (attributes.count(key) > 0) {
            has_key = true;
        }

        return has_key;
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

// SImplementation struct defined here, details and methods are encapsulated and hidden from users
struct COpenStreetMap::SImplementation {
    
    std::vector<std::shared_ptr<OSMNode>> osm_nodes;
    
    std::vector<std::shared_ptr<OSMWay>> osm_ways;

    std::unordered_map<TNodeID, std::shared_ptr<OSMNode>> node_id_map;

    std::unordered_map<TWayID, std::shared_ptr<OSMWay>> way_id_map;

    // Constructor that initializes the implementation by parsing the XML source
    explicit SImplementation(std::shared_ptr<CXMLReader> src) {
        ParseXML(src);
    }

    // Function that parses OSM XML data
    void ParseXML(std::shared_ptr<CXMLReader> src) {
    
    }

    // Default destructor operation
    ~SImplementation() {} 

    // Returns the number of nodes in the map
    std::size_t NodeCount() const noexcept {
        return osm_nodes.size();
    }

    // Returns the number of ways in the map
    std::size_t WayCount() const noexcept {
        return osm_ways.size();
    }

    // Returns SNode associated with index
    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept {

        // Return a null pointer if index is greater than or equal to NodeCount()
        if (index >= osm_nodes.size()) {
            return nullptr;
        }

        // Else return the SNode associated with the index
        else {
            return osm_nodes[index];

        }

    }

    // Returns the SNode with the id of id
    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept {
        
        // Returns a null pointer if the id doesn't exist
        if (node_id_map.count(id) == 0) {
            return nullptr;
        }

        // Returns SNode with the id of id
        else {
            return node_id_map.at(id);
        }

    }

    // Returns the SWay associated with index
    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept {
        
        // Returns a null pointer if the index is greater than or equal to WayCount()
        if (index >= osm_ways.size()) {
            return nullptr;
        }

        // Else return the SWay associated with index
        else {
            return osm_ways[index];
        }

    }

    // Returns the SWay with the id of id
    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept {

        // Returns a null pointer if the id doesn't exist
        if (way_id_map.count(id) == 0) {
            return nullptr;
        }

        // Else returns SWay with the id of id
        else {
            return way_id_map.at(id);
        }
    
    }

};

// Constructor for Open Street Map
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) {

}

// Default destructor operation
COpenStreetMap::~COpenStreetMap() {}



 
std::size_t NodeCount() const noexcept override {

}

std::size_t WayCount() const noexcept override {

}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept override {

}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept override {

}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept override {

}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept override {

}