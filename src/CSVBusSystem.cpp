#include <CSVBusSystem.h>
#include <iostream>

/*
    Define a BusStop struct; this inherits publicly all of the methods from
    CBusSystem::SStop
*/

struct BusStop: public CBusSystem::SStop{
    CBusSystem::TStopID tstop_id;
    CStreetMap::TNodeID n_id;

    BusStop(CBusSystem::TStopID ts_id, CStreetMap::TNodeID node_id){
        tstop_id = ts_id;
        n_id = node_id;
    }
    
    ~BusStop(){} // use default destructor

    CBusSystem::TStopID ID() const noexcept{
        return tstop_id;
    }

    CStreetMap::TNodeID NodeID() const noexcept{
        return n_id;
    }
};

/*
    Define a BusRoute struct; this inherits publicly all of the methods
    of the CBusSystem::SRoute
*/

struct BusRoute: public CBusSystem::SRoute {
    std::vector<CStreetMap::TNodeID> bus_stops;
    std::string name;

    BusRoute(std::string n){
        name = n;
    }

    ~BusRoute(){} // use default destructor

    std::size_t StopCount() const noexcept {
        return bus_stops.size();
    }
    
    CBusSystem::TStopID GetStopID(std::size_t index) const noexcept{
        if (index >= 0 && index < StopCount())
            return bus_stops[index];
        return CBusSystem::InvalidStopID;
    }
    
    std::string Name() const noexcept{
        return name;
    }
    
    void append_stop(CStreetMap::TNodeID stop){
        bus_stops.push_back(stop);
    }
};

/*
    Define our Simplementation Struct, whose details and methods are encapsulated

*/
struct CCSVBusSystem::SImplementation{
    std::vector<std::shared_ptr<BusStop>> bus_stops;
    std::vector<std::shared_ptr<BusRoute>> bus_routes;
    

    SImplementation(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc){
        std::vector<std::string> curr_row;

        while (!stopsrc->End()){
            if (stopsrc->ReadRow(curr_row)){
                if (curr_row[0] != "stop_id"){
                    std::shared_ptr <BusStop> new_stop (new BusStop((CBusSystem::TStopID)std::stol(curr_row[0]), (CBusSystem::TStopID)std::stol(curr_row[1])));
                    bus_stops.push_back(new_stop);
                }
            }  
        }
        /*
        TODO: HANDLE ROUTE CREATION

        //see if name of route already exists
            std::shared_ptr<Route> route = std::dynamic_pointer_cast<Route>(RouteByName(row[0]));
            if(route == nullptr){
                route = std::make_shared<Route>(row[0]);
                routes.push_back(route);

            }
            //add to route specific list of stops
            route->addStop((CBusSystem::TStopID)std::stol(row[1]));
        */
        while (!routesrc->End()){
            if (routesrc->ReadRow(curr_row)){
                if (curr_row[0] != "route"){
                    std::shared_ptr<BusRoute> route = std::dynamic_pointer_cast<BusRoute>(RouteByName(curr_row[0]));
                    if (route == nullptr) {
                        // If the route doesn't exist, create a new one
                        route = std::make_shared<BusRoute>(curr_row[0]);
                        bus_routes.push_back(route);
                    }
                    // Now, route points to a valid BusRoute object
                    route->append_stop((CBusSystem::TStopID)std::stol(curr_row[1]));  
                }
            }
        }
    }

    ~SImplementation(){} // default destructor operation

    std::size_t StopCount() {
        return bus_stops.size();
    }

    std::size_t RouteCount() {
        return bus_routes.size();
    }
        
    std::shared_ptr<SStop> StopByIndex(std::size_t index) {
        if (index >= 0 && index < bus_stops.size()) {
            return bus_stops[index];
        } else {
            return nullptr;
        }
    }
    
    std::shared_ptr<SStop> StopByID(TStopID id){
        for (auto &stop : bus_stops) {
            if (stop->ID() == id) {
                return stop;
            }
        }
        return nullptr;
    }

    std::shared_ptr<CBusSystem::SRoute> RouteByIndex(std::size_t index){
        if (index >= 0 && index < bus_routes.size()) {
            return bus_routes[index];
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<CBusSystem::SRoute> RouteByName(const std::string &name){
        for (const auto& r : bus_routes) {
            if (r->Name() == name) {
                return r;
            }
        }
        return nullptr;
    }
};

CCSVBusSystem::CCSVBusSystem(std::shared_ptr< CDSVReader > stopsrc, std::shared_ptr< CDSVReader > routesrc){
    DImplementation = std::make_unique<SImplementation>(stopsrc, routesrc);
}

CCSVBusSystem::~CCSVBusSystem(){}

std::size_t CCSVBusSystem::StopCount() const noexcept{
    return DImplementation->StopCount();
}

std::size_t CCSVBusSystem::RouteCount() const noexcept{
    return DImplementation->RouteCount();
}


std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept{
    return DImplementation->StopByIndex(index);
}

std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept{
    return DImplementation->StopByID(id);
}

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept{
    return DImplementation->RouteByIndex(index);
}

std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept{
    return DImplementation->RouteByName(name);
}

