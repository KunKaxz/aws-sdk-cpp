/*
  * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  * 
  * Licensed under the Apache License, Version 2.0 (the "License").
  * You may not use this file except in compliance with the License.
  * A copy of the License is located at
  * 
  *  http://aws.amazon.com/apache2.0
  * 
  * or in the "license" file accompanying this file. This file is distributed
  * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
  * express or implied. See the License for the specific language governing
  * permissions and limitations under the License.
  */


#include <aws/external/gtest.h>
#include <aws/testing/MemoryTesting.h>

#include <aws/core/utils/StringUtils.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <climits>

using namespace Aws::Utils;


TEST(StringUtilsTest, TestSplitHappyPath)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toSplit = "test1,test2,test3,test4";
    Aws::Vector<Aws::String> splits = StringUtils::Split(toSplit, ',');

    ASSERT_EQ(4uL, splits.size());
    EXPECT_STREQ("test1", splits[0].c_str());
    EXPECT_STREQ("test2", splits[1].c_str());
    EXPECT_STREQ("test3", splits[2].c_str());
    EXPECT_STREQ("test4", splits[3].c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestSplitOnLineHappyPath)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::StringStream ss;
    ss << "test1" << std::endl << "test2" << std::endl << "test3" << std::endl << "test4";
    Aws::String toSplit = ss.str();

    Aws::Vector<Aws::String> splits = StringUtils::SplitOnLine(toSplit);

    ASSERT_EQ(4uL, splits.size());
    EXPECT_STREQ("test1", splits[0].c_str());
    EXPECT_STREQ("test2", splits[1].c_str());
    EXPECT_STREQ("test3", splits[2].c_str());
    EXPECT_STREQ("test4", splits[3].c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestSplitWithDelimiterOnTheFrontAndBack)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toSplit = ",test1,test2,test3,test4,";

    Aws::Vector<Aws::String> splits = StringUtils::Split(toSplit, ',');

    ASSERT_EQ(4uL, splits.size());
    EXPECT_STREQ("test1", splits[0].c_str());
    EXPECT_STREQ("test2", splits[1].c_str());
    EXPECT_STREQ("test3", splits[2].c_str());
    EXPECT_STREQ("test4", splits[3].c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestSplitWithEmptyString)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toSplit = "";

    Aws::Vector<Aws::String> splits = StringUtils::Split(toSplit, ',');

    ASSERT_EQ(0uL, splits.size());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestSplitDelimiterNotFound)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toSplit = "BlahBlahBlah";

    Aws::Vector<Aws::String> splits = StringUtils::Split(toSplit, ',');

    ASSERT_EQ(1uL, splits.size());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestToLower)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toMakeLower = "Make Me Lower Case";
    Aws::String lowered = StringUtils::ToLower(toMakeLower.c_str());

    EXPECT_STREQ("make me lower case", lowered.c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestToUpper)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toMakeUpper = "Make Me Upper Case";
    Aws::String uppered = StringUtils::ToUpper(toMakeUpper.c_str());

    EXPECT_STREQ("MAKE ME UPPER CASE", uppered.c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestCaselessComparison)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    static const char* upperCase = "WE ARE the Same";
    static const char* lowerCase = "we are the same";
    static const char* bad = "We Are Not the same";

    EXPECT_TRUE(StringUtils::CaselessCompare(upperCase, lowerCase));
    EXPECT_FALSE(StringUtils::CaselessCompare(lowerCase, bad));

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestTrim)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toTrim = " \n\t Trim me\n\t ";

    ASSERT_STREQ("Trim me\n\t ", StringUtils::LTrim(toTrim.c_str()).c_str());
    ASSERT_STREQ(" \n\t Trim me", StringUtils::RTrim(toTrim.c_str()).c_str());
    EXPECT_STREQ("Trim me", StringUtils::Trim(toTrim.c_str()).c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestURLEncodeAndDecode)
{
    AWS_BEGIN_MEMORY_TEST(16, 10)

    Aws::String toEncode = "/Test Path/value=reserved%";

    //test the encoding happened and was deterministic
    Aws::String encoded = StringUtils::URLEncode(toEncode.c_str());
    ASSERT_STREQ("%2FTest%20Path%2Fvalue%3Dreserved%25", encoded.c_str());

    //test that encode and decode are inverse operations.
    Aws::String decoded = StringUtils::URLDecode(encoded.c_str());

    ASSERT_STREQ(toEncode.c_str(), decoded.c_str());

    //test that a string that doesn't need encoding is not altered.
    Aws::String shouldBeTheSameAsEncoded = StringUtils::URLEncode("IShouldNotChange");
    ASSERT_STREQ("IShouldNotChange", shouldBeTheSameAsEncoded.c_str());

    AWS_END_MEMORY_TEST
}

TEST(StringUtilsTest, TestInt64Conversion)
{
    long long bigIntValue = LLONG_MAX - 1;
    std::stringstream ss;
    ss << bigIntValue;
    ASSERT_EQ(0, StringUtils::ConvertToInt64(NULL));
    ASSERT_EQ(0, StringUtils::ConvertToInt64(""));
    ASSERT_EQ(bigIntValue, StringUtils::ConvertToInt64(ss.str().c_str()));
}

TEST(StringUtilsTest, TestInt32Conversion)
{
    long long intValue = LONG_MAX - 1;
    std::stringstream ss;
    ss << intValue;
    ASSERT_EQ(0, StringUtils::ConvertToInt32(NULL));
    ASSERT_EQ(0, StringUtils::ConvertToInt32(""));
    ASSERT_EQ(intValue, StringUtils::ConvertToInt32(ss.str().c_str()));
}

TEST(StringUtilsTest, TestBoolConversion)
{
    ASSERT_FALSE(StringUtils::ConvertToBool(NULL));
    ASSERT_FALSE(StringUtils::ConvertToBool(""));
    ASSERT_FALSE(StringUtils::ConvertToBool("false"));
    ASSERT_FALSE(StringUtils::ConvertToBool("False"));
    ASSERT_FALSE(StringUtils::ConvertToBool("0"));
    ASSERT_TRUE(StringUtils::ConvertToBool("1"));
    ASSERT_TRUE(StringUtils::ConvertToBool("True"));
    ASSERT_TRUE(StringUtils::ConvertToBool("true"));
}

TEST(StringUtilsTest, TestDoubleConversion)
{
    double doubleValue = DBL_MAX - 0.0001;
    ASSERT_DOUBLE_EQ(0.0, StringUtils::ConvertToDouble(NULL));
    ASSERT_DOUBLE_EQ(0.0, StringUtils::ConvertToDouble(""));

    std::stringstream ss;
    ss << std::setprecision(20) << doubleValue;
    ASSERT_DOUBLE_EQ(doubleValue, StringUtils::ConvertToDouble(ss.str().c_str()));
}






