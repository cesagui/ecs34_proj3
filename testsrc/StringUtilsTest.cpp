#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    std::string inp = "honeybee";

    // slicing an empty string
    EXPECT_EQ(StringUtils::Slice("", 1, 3), "");

    // standard test cases:
    EXPECT_EQ(StringUtils::Slice(inp, 1, 3), "on");
    EXPECT_EQ(StringUtils::Slice(inp, 2, 5), "ney");

    
    // slicing the entire string
    EXPECT_EQ(StringUtils::Slice(inp, 0, inp.size()), "honeybee");
    EXPECT_EQ(StringUtils::Slice(inp, 0, 100), "honeybee");
    
    // standard case for back-counting start index
    EXPECT_EQ(StringUtils::Slice(inp, -5, inp.size()), "eybee");
    EXPECT_EQ(StringUtils::Slice(inp, -4, inp.size()), "ybee");

    // back-counting start index, positive stop index comes first
    EXPECT_EQ(StringUtils::Slice(inp, -4, 1), "");

    // standard case for back-counting stop index
    EXPECT_EQ(StringUtils::Slice(inp, 0, -5), "hon");
    EXPECT_EQ(StringUtils::Slice(inp, 0, -2), "honeyb");
    
    // back-counting stop index, positive stop index comes last
    EXPECT_EQ(StringUtils::Slice(inp, 6, -5), "");

    // standard behavior back-counting start index, stop index
    EXPECT_EQ(StringUtils::Slice(inp, -7, -5), "on");
    EXPECT_EQ(StringUtils::Slice(inp, -8, -2), "honeyb");
}

TEST(StringUtilsTest, Capitalize){
    EXPECT_EQ(StringUtils::Capitalize(""), "");
    EXPECT_EQ(StringUtils::Capitalize("tHR3W TH3 WIRE"), "Thr3w th3 wire");
    EXPECT_EQ(StringUtils::Capitalize("1234"), "1234");
    EXPECT_EQ(StringUtils::Capitalize("i am peggylover1539"), "I am peggylover1539");
    EXPECT_EQ(StringUtils::Capitalize("."), ".");
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper("12345"), "12345");
    EXPECT_EQ(StringUtils::Upper(""), "");
    EXPECT_EQ(StringUtils::Upper("abracadabra"), "ABRACADABRA");
    EXPECT_EQ(StringUtils::Upper("Kanye To The"), "KANYE TO THE");
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower("12345"), "12345");
    EXPECT_EQ(StringUtils::Lower(""), "");
    EXPECT_EQ(StringUtils::Lower("ABRACADABRA"), "abracadabra");
    EXPECT_EQ(StringUtils::Lower("Kanye To The"), "kanye to the");   
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip(""),"");
    EXPECT_EQ(StringUtils::LStrip("   "),"");
    EXPECT_EQ(StringUtils::LStrip("   sand    wich     "),"sand    wich     ");
    EXPECT_EQ(StringUtils::LStrip("trailing     "),"trailing     ");
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip(""),"");
    EXPECT_EQ(StringUtils::RStrip("   "),"");
    EXPECT_EQ(StringUtils::RStrip("   sand    wich     "),"   sand    wich");
    EXPECT_EQ(StringUtils::RStrip("trailing"),"trailing");
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip(""),"");
    EXPECT_EQ(StringUtils::Strip("   "),"");
    EXPECT_EQ(StringUtils::Strip("trailing      "),"trailing");
    EXPECT_EQ(StringUtils::Strip("      leading"),"leading");
    EXPECT_EQ(StringUtils::Strip("      sand    wich      "),"sand    wich");
    EXPECT_EQ(StringUtils::Strip("   base_case   "),"base_case");
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("base_case", 9 ,' '),"base_case");
    EXPECT_EQ(StringUtils::Center("base_case", 11 ,'X'),"Xbase_caseX");
    EXPECT_EQ(StringUtils::Center("base_case", 12 ,'X'),"Xbase_caseXX");
    EXPECT_EQ(StringUtils::Center("base_case", 0 ,'X'),"base_case");
    EXPECT_EQ(StringUtils::Center("base_case", 17 ,'X'),"XXXXbase_caseXXXX");
}


TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("", 9 ,'X'),"XXXXXXXXX");
    EXPECT_EQ(StringUtils::LJust("base_case", 9 ,' '),"base_case");
    EXPECT_EQ(StringUtils::LJust("base_case", 11 ,'X'),"base_caseXX");
    EXPECT_EQ(StringUtils::LJust("base_case", 12 ,'X'),"base_caseXXX");
    EXPECT_EQ(StringUtils::LJust("base_case", 0 ,'X'),"base_case");
    EXPECT_EQ(StringUtils::LJust("base_case", 17 ,'X'),"base_caseXXXXXXXX");  
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("", 9 ,'X'),"XXXXXXXXX");
    EXPECT_EQ(StringUtils::RJust("base_case", 9 ,' '),"base_case");
    EXPECT_EQ(StringUtils::RJust("base_case", 11 ,'X'),"XXbase_case");
    EXPECT_EQ(StringUtils::RJust("base_case", 12 ,'X'),"XXXbase_case");
    EXPECT_EQ(StringUtils::RJust("base_case", 0 ,'X'),"base_case");
    EXPECT_EQ(StringUtils::RJust("base_case", 17 ,'X'),"XXXXXXXXbase_case");  
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("", "", ""),"");
    EXPECT_EQ(StringUtils::Replace("", "", "banana"),"banana");
    EXPECT_EQ(StringUtils::Replace("awesome sauce", "yes", "no"),"awesome sauce");
    EXPECT_EQ(StringUtils::Replace("yes awesome sauce", "yes", "")," awesome sauce");
    EXPECT_EQ(StringUtils::Replace("yes awesome sauce", "yes", "no"),"no awesome sauce");
    EXPECT_EQ(StringUtils::Replace("yes awesome sauce", "yes", "yes"),"yes awesome sauce");
    EXPECT_EQ(StringUtils::Replace("yes awesome sauce yes", "yes", "no"),"no awesome sauce no");
    EXPECT_EQ(StringUtils::Replace("yesyes awesomeyessauce yes", "yes", "no"),"nono awesomenosauce no");
}

TEST(StringUtilsTest, Split){
    std::string input = "apple,orange,banana,grape";
    std::string rep = ",";

    std::vector<std::string> result = StringUtils::Split(input, rep);

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "apple");
    EXPECT_EQ(result[1], "orange");
    EXPECT_EQ(result[2], "banana");
    EXPECT_EQ(result[3], "grape");

    input = "";
    rep = ",";

    result = StringUtils::Split(input, rep);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "");

    input = "apple";
    rep = ",";

    result = StringUtils::Split(input, rep);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "apple");

    input = "apple-orange-banana-grape";
    rep = ",";

    result = StringUtils::Split(input, rep);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "apple-orange-banana-grape");
}

TEST(StringUtilsTest, Join){
    std::vector<std::string> words = {"apple", "orange", "banana", "grape"};
    std::string addition = ",";

    std::string result = StringUtils::Join(addition, words);

    EXPECT_EQ(result, "apple,orange,banana,grape");

    result = StringUtils::Join(addition, {});

    EXPECT_EQ(result, "");

    words = {"apple"};
    result = StringUtils::Join(addition, words);

    EXPECT_EQ(result, "apple");

    words = {"apple", "orange", "banana", "grape"};
    addition = " | ";

    result = StringUtils::Join(addition, words);

    EXPECT_EQ(result, "apple | orange | banana | grape");
}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(StringUtils::ExpandTabs("\tTest\tCases\t", 16), "                Test            Cases           ");
    EXPECT_EQ(StringUtils::ExpandTabs("Test Cases", 6), "Test Cases");
    EXPECT_EQ(StringUtils::ExpandTabs("\tTest\tCases\t", -3), "");
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(StringUtils::EditDistance("hello", "hello"), 0);
    EXPECT_EQ(StringUtils::EditDistance("hello", "hella"), 1);
    EXPECT_EQ(StringUtils::EditDistance("kitten", "sitting"), 3);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "hello", true), 0);
}
