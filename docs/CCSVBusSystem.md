# BusStop Struct Documentation

## Description
The `BusStop` struct represents a bus stop in a bus system. It inherits from the `CBusSystem::SStop` struct and adds additional functionality and data members.

## Dependencies
- `CSVBusSystem.h`
- `iostream`

## Member Functions
### Constructor

#### BusStop(CBusSystem::TStopID ts_id, CStreetMap::TNodeID node_id);
##### Description:
Constructs a BusStop object with the given stop ID and node ID.
##### Parameters:
    ts_id: A CBusSystem::TStopID representing the stop ID.
    node_id: A CStreetMap::TNodeID representing the node ID.
### Destructor
#### ~BusStop();
##### Description:
Default destructor. No additional cleanup needed.

### ID
#### CBusSystem::TStopID ID() const noexcept;



##### Description:
    Returns the stop ID of the bus stop.
    Return: A CBusSystem::TStopID representing the stop ID.

### NodeID
#### CStreetMap::TNodeID NodeID() const noexcept;

##### Description:
    Returns the node ID of the bus stop.
    Return: A CStreetMap::TNodeID representing the node ID.

## Example Usage
##### Description:
```
// Example usage of BusStop struct
CBusSystem::TStopID stopID = 123;
CStreetMap::TNodeID nodeID = 456;
BusStop busStop(stopID, nodeID);

// Accessing member functions
CBusSystem::TStopID retrievedID = busStop.ID();
CStreetMap::TNodeID retrievedNodeID = busStop.NodeID();
```
# BusRoute Struct Documentation

## Description
The `BusRoute` struct represents a bus route in a bus system. It inherits from the `CBusSystem::SRoute` struct and adds additional functionality and data members.

## Dependencies
- `CSVBusSystem.h`
- `iostream`
- `vector`

## Member Functions
### Constructor
```
BusRoute(std::string n);
```
#### Description:
Constructs a BusRoute object with the given name.
#### Parameters:
n: A std::string representing the name of the bus route.
### Destructor
```
~BusRoute();
```
#### Description:
Default destructor. No additional cleanup needed.

### StopCount()
```
std::size_t StopCount() const noexcept;
```
#### Description:
Returns the number of stops in the bus route.
#### Return:
A std::size_t representing the number of stops.
### GetStopID()

```
CBusSystem::TStopID GetStopID(std::size_t index) const noexcept;
```
#### Description:
Returns the stop ID at the specified index in the bus route.
#### Parameters:
    index: A std::size_t representing the index of the stop.
    Return: A CBusSystem::TStopID representing the stop ID at the specified index, or CBusSystem::InvalidStopID if the index is out of range.

### Name()
```
std::string Name() const noexcept;
```
#### Description:
Returns the name of the bus route.
#### Return:
A std::string representing the name of the bus route.

### append_stop()
```
void append_stop(CStreetMap::TNodeID stop);
```
#### Description:
Appends a stop to the bus route.
#### Parameters:
stop: A CStreetMap::TNodeID representing the stop to be appended.

## Example Usage

```// Example usage of BusRoute struct
std::string routeName = "Route A";
BusRoute busRoute(routeName);

// Adding stops to the route
CStreetMap::TNodeID stop1 = 123;
busRoute.append_stop(stop1);
CStreetMap::TNodeID stop2 = 456;
busRoute.append_stop(stop2);

// Accessing member functions
std::size_t stopCount = busRoute.StopCount();
CBusSystem::TStopID retrievedStopID = busRoute.GetStopID(0);
std::string routeName = busRoute.Name();
```

# CCSVBusSystem::SImplementation Struct Documentation

## Description
The `CCSVBusSystem::SImplementation` struct encapsulates the details and methods for managing bus stops and routes within the `CCSVBusSystem` class.

## Dependencies
- `CSVBusSystem.h`
- `iostream`
- `vector`
- `memory`
- `string`

## Member Functions
### Constructor
```
SImplementation(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc);
```
#### Description:
Constructs an SImplementation object by initializing bus stops and routes from CSV data sources.
#### Parameters:
stopsrc: A std::shared_ptr< CDSVReader > representing the CSV data source for bus stops.
routesrc: A std::shared_ptr< CDSVReader > representing the CSV data source for bus routes.

#### Destructor

```~SImplementation();
```

##### Description:
Default destructor. No additional cleanup needed.

### StopCount()

```
std::size_t StopCount();
```
#### Description:
Returns the number of bus stops.
#### Return:
A std::size_t representing the number of bus stops.
