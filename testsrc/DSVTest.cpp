// TODO: add skeleton functions / header setup here.
#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

// Values that have either the delimiter, double quote character ‘"’, or newline must be quoted
// with double quotes.
// Double quote character in the cell must be replace with two double quotes.
// An empty line is a valid row where there are not values.
// A double quote specified as a delimiter is interpreted as a comma ‘,’


// the following test was pasted from Figure 1.

TEST(DSVTest, ExampleWriter){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");

    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source,'&');

    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Hello");
    EXPECT_EQ(output[1],"World!");
}

TEST(DSVTest, Multi){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"Name", "ID"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Name&ID");
    input = {"Cesar", "100"};
    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Name&ID\nCesar&100");
    
    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source,'&');

    std::vector<std::string> output;

    
    // Suppose the dataSource contains the string Name&ID\nPEGGY&100, with & as the delimiter
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);

    EXPECT_EQ(output[0],"Name");
    EXPECT_EQ(output[1],"ID");
    
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Cesar");
    EXPECT_EQ(output[1],"100");
}
TEST(DSVTest, WriteDoubleQuotationsWithDelimiter){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"delimiter:&","mystring", "mysecondstring"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"\"delimiter:&\"&\"mystring\"&\"mysecondstring\"");

    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source,'&');

    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),3);

    EXPECT_EQ(output[0],"delimiter:&");
    EXPECT_EQ(output[1],"mystring");
    EXPECT_EQ(output[2],"mysecondstring");
}

TEST(DSVTest, WriteDoubleQuotationsWithDoubleQuotation){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"\"a"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"\"\"\"a\"");

    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source,'&');

    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),1);

    EXPECT_EQ(output[0],"\"a");
}

TEST(DSVTest, WriteDoubleQuotationsWithNewLine){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"\n"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"\"\n\"");

    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source,'&');

    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),1);

    EXPECT_EQ(output[0],"\n");
}

TEST(DSVTest, WriteDoubleQuotationsWithAllThree){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"new line: \n", "DQ: \"","Delim: &","all three: \n\"&", "this contains none of them."};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"\"new line: \n\"&\"DQ: \"\"\"&\"Delim: &\"&\"all three: \n\"\"&\"&\"this contains none of them.\"");
}

// the following test was pasted from Figure 1.

TEST(DSVTest, ExampleReader){
    auto Source = std::make_shared<CStringDataSource>("Hello&World!");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Hello");
    EXPECT_EQ(output[1],"World!");
}

// test cases for edgecases provided on Piazza

TEST(DSVTest, ReadingEmptyEntries2){
    auto Source = std::make_shared<CStringDataSource>("a&b&c\n\n&\n\n1&2&3");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),3);
    EXPECT_EQ(output[0],"a");
    EXPECT_EQ(output[1],"b");
    EXPECT_EQ(output[2],"c");
    
    output = {};
    
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),1);
    EXPECT_EQ(output[0],"");

    output = {};
    
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"");
    EXPECT_EQ(output[1],"");

    output = {};
    
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),1);
    EXPECT_EQ(output[0],"");

    output = {};
    
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),3);
    EXPECT_EQ(output[0],"1");
    EXPECT_EQ(output[1],"2");
    EXPECT_EQ(output[2],"3");
}

TEST(DSVTest, ReadingEmptyEntries){
    auto Source = std::make_shared<CStringDataSource>("&a&&\n&");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),4);
    EXPECT_EQ(output[0],"");
    EXPECT_EQ(output[1],"a");
    EXPECT_EQ(output[2],"");
    EXPECT_EQ(output[3],"");
    
    output = {};
    
    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"");
    EXPECT_EQ(output[1],"");
}

TEST(DSVTest, DoubleQuotesDoNotEndColumn){
    auto Source = std::make_shared<CStringDataSource>("\"\"abc\"\" hi&12&83");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),3);
    EXPECT_EQ(output[0],"abc hi");
    EXPECT_EQ(output[1],"12");
    EXPECT_EQ(output[2],"83");
}

TEST(DSVTest, DoubleQuoteAsComma){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'\"');
    std::vector<std::string> input = {"Hello", "World!"};
    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello,World!");

    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source,'\"');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Hello");
    EXPECT_EQ(output[1],"World!");
}