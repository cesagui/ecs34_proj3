#include <gtest/gtest.h>
#include "DSVReader.h"
#include "StringDataSource.h"
#include "CSVBusSystem.h"

/*
    BusSystem TESTS
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

TEST(CCSVBusSystem, SingleStopTest){
    // Implementation test of CCSVBusSystem OBJECT here
    auto Source = std::make_shared<CStringDataSource>("stop_id,node_id\n22043,2849810514");
    auto stop_reader =std::make_shared<CDSVReader>(Source, ',');

    Source = std::make_shared<CStringDataSource>("route,stop_id\nA,22258");
    auto route_reader =std::make_shared<CDSVReader>(Source, ',');
    
    CCSVBusSystem BusSystem = CCSVBusSystem(stop_reader, route_reader);
    EXPECT_EQ(BusSystem.StopCount(),1);
    EXPECT_EQ(BusSystem.RouteCount(),1);
}

TEST(CCSVBusSystem, EmptySourceTest){
    // Implementation test of CCSVBusSystem OBJECT here
    auto Source = std::make_shared<CStringDataSource>("");
    auto stop_reader =std::make_shared<CDSVReader>(Source, ',');

    Source = std::make_shared<CStringDataSource>("");
    auto route_reader =std::make_shared<CDSVReader>(Source, ',');
    
    CCSVBusSystem BusSystem = CCSVBusSystem(stop_reader, route_reader);
    EXPECT_EQ(BusSystem.StopCount(),0);
    EXPECT_EQ(BusSystem.RouteCount(),0);
}

TEST(CCSVBusSystem, MultiTest){
    // Implementation test of CCSVBusSystem OBJECT here
    auto Source = std::make_shared<CStringDataSource>("stop_id,node_id\n22043,2849810514\n22358,2849805223\n22105,3954294407\n22175,5598639595\n22174,3119663186\n22177,2599137935\n22176,2607436578\n22078,1190339479\n22079,2580285987\n22173,2276473527\n22172,366763830\n22074,2579936805\n22075,2579936421\n22076,2579936417\n22077,2560323391\n22070,5554742310\n22071,4595133310\n22072,2578985048\n22073,1918186801");
    auto stop_reader =std::make_shared<CDSVReader>(Source, ',');

    Source = std::make_shared<CStringDataSource>("route,stop_id\nA,22258\nA,22169\nA,22000\nA,22005\nA,22007\nB,22274\nB,22230\nB,22185\nB,22189");
    auto route_reader =std::make_shared<CDSVReader>(Source, ',');
    
    CCSVBusSystem BusSystem = CCSVBusSystem(stop_reader, route_reader);
    EXPECT_EQ(BusSystem.StopCount(),19);
    EXPECT_EQ(BusSystem.RouteCount(),2);
    EXPECT_EQ(BusSystem.StopByIndex(0)->ID(), 22043); 
    EXPECT_EQ(BusSystem.StopByID(22043)->NodeID(), 2849810514);
    EXPECT_EQ(BusSystem.RouteByIndex(0)->Name(), "A");
}
