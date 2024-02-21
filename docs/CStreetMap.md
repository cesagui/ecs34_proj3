# CStreetMap
## Description: 
The CStreetMap is used as an abstract base class that represents street maps, which is done so by defining a common interface to access location-relevant data in the form of nodes and ways
### Implemenetation Details
Note that CStreetMap doesn't implement parsing or data storage but is used as an interface for COpenStreetMap
```
#### Important Components:
   
This returns the total number of nodes in the map and used to determine the size of the map data
    `std::size_t NodeCount() const noexcept`

This returns the total number of ways in the map where the ways represents paths/roads within the map data
    `std::size_t WayCount() const noexcept`

This gives access to a node using its index within an internal collection, but if the index is out of bounds, then a null pointer is returned instead
    `std::shared_ptr<SNode> NodeByIndex(std::size_t index) const noexcept`

This gives a node utilizing its unique identifier (ID), but if no nodes match the given ID, then a null pointer is returned instead
    `std::shared_ptr<SNode> NodeByID(TNodeID id) const noexcept`

This gives access to a way using its index, but if the index is outside the map's current range, a null pointer is returned instead
    `std::shared_ptr<SWay> WayByIndex(std::size_t index) const noexcept`

This gives a way utilizing its unique identifier (ID), but if no ways match the given ID, then a null pointer is returned instead
    `std::shared_ptr<SWay> WayByID(TWayID id) const noexcept`