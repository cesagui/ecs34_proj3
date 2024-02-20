#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include "StringDataSink.h"
#include "StringDataSource.h"
#include <memory>
#include <expat.h>

// the following test was pasted from figure 1

TEST(XMLReaderTest, ReadCompleteElement) {
    auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}
 
TEST(XMLReaderTest, ReadNestedElement) {
    auto InputStream = std::make_shared<CStringDataSource>("<parent><child></child></parent>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "parent");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "child");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(E.DNameData, "child");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(E.DNameData, "parent");
}

TEST(XMLReaderTest, ReadEmptyDoc) {
    auto InputStream = std::make_shared<CStringDataSource>("");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_FALSE(Reader.ReadEntity(E));
    EXPECT_TRUE(Reader.End());
}

TEST(XMLReaderTest, ReadOneEmptyElement) {
    auto InputStream = std::make_shared<CStringDataSource>("<empty></empty>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "empty");
    EXPECT_FALSE(E.AttributeExists("attr"));

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(E.DNameData, "empty");

    EXPECT_TRUE(Reader.End()); 
}

// the following test was pasted from Figure 1.

TEST(XMLWriterTest, WriteCompleteElement) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}}));

    EXPECT_TRUE(Writer.Flush());

    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");
}

TEST(XMLWriterTest, WriteNestedElement) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "parent", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "child", {}}));
    
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "child", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "parent", {}}));

    EXPECT_TRUE(Writer.Flush());
    EXPECT_EQ(OutputStream->String(), "<parent><child></child></parent>");
}

TEST(XMLWriterTest, WriteEmptyElement) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "empty", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "empty", {}}));

    EXPECT_TRUE(Writer.Flush());
    EXPECT_EQ(OutputStream->String(), "<empty></empty>");
}

TEST(XMLWriterTest, WriteMultipleAttributesElement) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "person", {{"name", "John"}, {"age", "20"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "person", {}}));
    EXPECT_TRUE(Writer.Flush());
    EXPECT_EQ(OutputStream->String(), "<person name=\"John\" age=\"20\"></person>");
}

TEST(XMLWriterTest, WriteCharData) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Hello World", {}}));
    EXPECT_TRUE(Writer.Flush());
    EXPECT_EQ(OutputStream->String(), "Hello World");
}

TEST(XMLWriterTest, WriteCData) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "<![CDATA[example CDATA]]>", {}}));

    EXPECT_TRUE(Writer.Flush());
    EXPECT_EQ(OutputStream->String(), "<![CDATA[example CDATA]]>");
}

TEST(XMLWriterTest, WriteSelfClosingElement) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "selfClose:break", {}}));
    EXPECT_TRUE(Writer.Flush());
    EXPECT_EQ(OutputStream->String(), "<break/>");
}