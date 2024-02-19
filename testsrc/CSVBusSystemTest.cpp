#include <gtest/gtest.h>
#include "DSVReader.h"
#include "StringDataSource.h"
#include "CSVBusSystem.h"

/*
The CCSVBusSystem class you will be developing will implement the CBusSystem abstract
interface. There are two struct abstract interfaces that are part of the CBusSystem, that will need
to be implemented as well (SStop and SRoute). The bus system is a collection of stops, and
routes. Each route is a set of stops that specifies the locations where the bus stops on the route.

SStop: stop_id : int, node_id: int
SRoute: collection SStop's reported by stop_id 
*/

TEST(CCSVBusSystem, TestEmptyStops){
    auto Source = std::make_shared<CStringDataSource>("stop_id,node_id\n");
    auto stop_reader =std::make_shared<CDSVReader>(Source, ',');

    Source = std::make_shared<CStringDataSource>("route,stop_id\n");
    auto route_reader =std::make_shared<CDSVReader>(Source, ',');
    
    CCSVBusSystem BusSystem = CCSVBusSystem(stop_reader, route_reader);
    EXPECT_EQ(BusSystem.StopCount(),0);
    EXPECT_EQ(BusSystem.RouteCount(),0);
}
/*
TEST(CCSVBusSystem, SingleStopTest){
    // Implementation test of CCSVBusSystem OBJECT here
    auto stop_source = std::make_shared<CStringDataSource>("stop_id,node_id
22043,2849810514");
    CDSVReader stop_reader(stop_source, ',');
    auto route_source = std::make_shared<CStringDataSource>("route,stop_id
A,22258");
    CDSVReader route_reader(route_source, ',');
    
    CCSVBusSystem BusSystem(stop_source, route_source);
    EXPECT_EQ(BusSystem.StopCount(),1);
    EXPECT_EQ(BusSystem.RouteCount(),1);      
}


TEST(CCSVBusSystem, SeveralStopsAndRoutesTest){
    // Implementation test of CCSVBusSystem OBJECT here
    auto stop_source = std::make_shared<CStringDataSource>("stop_id,node_id
22043,2849810514
22358,2849805223
22105,3954294407
22175,5598639595
22174,3119663186
22177,2599137935
22176,2607436578
22078,1190339479
22079,2580285987
22173,2276473527
22172,366763830
22074,2579936805
22075,2579936421
22076,2579936417
22077,2560323391
22070,5554742310
22071,4595133310
22072,2578985048
22073,1918186801");
    CDSVReader stop_reader(stop_source, ',');
    auto route_source = std::make_shared<CStringDataSource>("route,stop_id
A,22258
A,22169
A,22000
A,22005
A,22007
A,22011
A,22031
A,22033
A,22076
A,22075
A,22073
A,22073
A,22234
A,22237
A,22070
A,22300
A,22067
A,22235
A,22066
A,22243
A,22061
A,22062
B,22274
B,22230
B,22185
B,22189
B,22188
B,22186
B,22191
B,22193
B,22194
B,22195
B,22192
B,22187
B,22190
B,22292
B,22179
B,22167");
    CDSVReader route_reader(route_source, ',');
    
    CCSVBusSystem BusSystem(stop_source, route_source);
    EXPECT_EQ(BusSystem.StopCount(),19);
    EXPECT_EQ(BusSystem.RouteCount(),2);      
}
*/
