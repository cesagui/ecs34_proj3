# COpenStreetMap
## Description: 
The COpenStreetMap class is used to parse and represent OpenStreetMap (OSM) XML data and covers the extracting and usage of information data from OSM which allows access to specific nodes, ways, and corresponding attributes.
## Class overview:
### Implementation Details:
This class contains an SImplementation internal structure which is used to encapsualte implementation details and maintains abstraction.
```
It inherits from CStreetMap to abstract the OSM data struct and use CXMLReader to parse the data.
```
#### Important Components:
This represents a node in OSM, holding the ID, location, and corresponding attributes
struct OSMNode : public CStreetMap::SNode {
    ...
    CStreetMap::TNodeID ID() const noexcept override {}
    CStreetMap::TLocation Location() const noexcept override {}
    std::size_t AttributeCount() const noexcept override {}
    std::string GetAttributeKey(std::size_t index) const noexcept override {}
    bool HasAttribute(const std::string &key) const noexcept override {}
    std::string GetAttribute(const std::string &key) const noexcept override {}
};

This represents a way in OSM, holding an ID, collection of node IDs related that creates the way, and corresponding attributes

struct OSMWay : public CStreetMap::SWay {
    ...
    CStreetMap::TWayID ID() const noexcept override {}
    std::size_t NodeCount() const noexcept override {}
    CStreetMap::TNodeID GetNodeID(std::size_t index) const noexcept override {}
    std::size_t AttributeCount() const noexcept override {}
    std::string GetAttributeKey(std::size_t index) const noexcept override {}
    bool HasAttribute(const std::string &key) const noexcept override {}
    std::string GetAttribute(const std::string &key) const noexcept override {}
};
```
#### Example Usage
