## Member Functions
### SStop Struct

#### Description:
Defines the interface for a bus stop.
#### Virtual Functions:
##### ID():
Returns the ID of the bus stop.
##### NodeID():
Returns the node ID associated with the bus stop.

### SRoute Struct

#### Description:
Defines the interface for a bus route.
#### Virtual Functions:
##### Name():
Returns the name of the bus route.
##### StopCount():
Returns the number of stops in the bus route.##### GetStopID(std::size_t index):
Returns the ID of the stop at the specified index in the bus route.

### CBusSystem Class

#### Description:
Defines the abstract interface for managing bus stops and routes.
#### Virtual Functions:
##### StopCount():
Returns the total number of bus stops in the system.
##### RouteCount():
Returns the total number of bus routes in the system.
##### StopByIndex(std::size_t index):
Returns a shared pointer to the bus stop at the specified index.
##### StopByID(TStopID id):
Returns a shared pointer to the bus stop with the specified ID.
##### RouteByIndex(std::size_t index):
Returns a shared pointer to the bus route at the specified index.
##### RouteByName(const std::string &name):
Returns a shared pointer to the bus route with the specified name.

# Notes

    This class provides an abstract interface and should be subclassed to provide concrete implementations.