#include <gtest/gtest.h>
#include "XMLReader.h"
#include "StringDataSource.h"
#include "OpenStreetMap.h"

// the following test was pasted from piazza Project 3 Example/Start Google Tests (with slight alteration)

TEST(OpenStreetMap, SimpleExampleTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
                                                        "</osm>");
    
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
    
    EXPECT_EQ(StreetMap.NodeCount(), 1);
    
    auto node = StreetMap.NodeByIndex(0);
    
    ASSERT_NE(node, nullptr); 
    EXPECT_EQ(node->ID(), 1);  
    EXPECT_EQ(node->Location(), std::make_pair(1.0, -1.0));  
}

TEST(OpenStreetMap, ManyNodesTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"           
                                                        "<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>"
                                                        "<node id=\"62209104\" lat=\"38.535052\" lon=\"-212.7408606\"/>"
                                                        "</osm>");

    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 2);                                                                                    
}

TEST(OpenSTreetMap, TagNodesTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"           
                                                        "<node id=\"62224365\" lat=\"38.5278374\" lon=\"-121.7588672\"/>"
                                                        "<tag k=\"highway\" v=\"motorway_junction\"/>"
                                                        "<tag k=\"ref\" v=\"71\"/>"
                                                        "</node>"                                                         
                                                        "</osm>");
    
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 1);

    auto node = StreetMap.NodeByIndex(0);
    
    ASSERT_NE(node, nullptr);
    
    EXPECT_TRUE(node->HasAttribute("highway"));
    EXPECT_EQ(node->GetAttribute("highway"), "motorway_junction");

    EXPECT_TRUE(node->HasAttribute("ref"));
    EXPECT_EQ(node->GetAttribute("ref"), "71");
}

TEST(OpenStreetMap, ManyWaysAndNodesTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"   
                                                        "<node id=\"62224286\" lat=\"38.5302841\" lon=\"-121.7689756\"/>"
                                                        "<node id=\"62224288\" lat=\"38.5288995\" lon=\"-121.7691145\"/>"
                                                        "<way id=\"10746713\">"
                                                        "<nd ref=\"62224286\"/>"
                                                        "<nd ref=\"62224288\"/>"
                                                        "/way>"
                                                        "</osm>");

    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 2);
    EXPECT_EQ(StreetMap.WayCount(), 1);

    auto way = StreetMap.WayByIndex(0);
    
    ASSERT_NE(way, nullptr);
    
    EXPECT_EQ(way->ID(), 10746713);
    EXPECT_EQ(way->NodeCount(), 2);                                                        
}

TEST(OpenStreetMap, WaysWithManyNodeReferencesTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<node id=\"62224365\" lat=\"38.5278374\" lon=\"-121.7588672\"/>"
                                                        "<node id=\"62224369\" lat=\"38.5284058\" lon=\"-121.7577639\"/>"
                                                        "<way id=\"10746725\">"
                                                        "<nd ref=\"62224365\"/>"
                                                        "<nd ref=\"62224369\"/>"
                                                        "<tag k=\"highway\" v=\"residential\"/>"
                                                        "<tag k=\"name\" v=\"El Macero Drive\"/>"
                                                        "</way>"
                                                        "</osm>");

    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 2);
    EXPECT_EQ(StreetMap.WayCount(), 1);

    auto way = StreetMap.WayByIndex(0);
    
    ASSERT_NE(way, nullptr);
    
    EXPECT_EQ(way->ID(), 10746725);
    
    EXPECT_EQ(way->NodeCount(), 2);

    EXPECT_EQ(way->GetNodeID(0), 62224365);
    
    EXPECT_EQ(way->GetNodeID(1), 62224369);

    EXPECT_TRUE(way->HasAttribute("highway"));
    
    EXPECT_EQ(way->GetAttribute("highway"), "residential");

    EXPECT_TRUE(way->HasAttribute("name"));
    
    EXPECT_EQ(way->GetAttribute("name"), "El Macero Drive");
}