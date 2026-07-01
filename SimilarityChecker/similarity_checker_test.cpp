#include <string>

#include "gmock/gmock.h"

#include "similarity_checker.h"

using namespace testing;

struct SimilarityCheckerParam {
    std::string target;
    std::string check;
    int expected = 0;
};
struct SimilarityCheckerTester : public TestWithParam<SimilarityCheckerParam> {};

struct SimilarityCheckerLengthTester : public SimilarityCheckerTester {};

TEST_P(SimilarityCheckerLengthTester, LengthScoreTest) {
    auto&& p = GetParam();
    SimilarityChecker checker(p.target);
    EXPECT_EQ(checker.getLengthSimilarityScore(p.check), p.expected);
}

INSTANTIATE_TEST_SUITE_P(
    SimilarityCheckerLengthTest,
    SimilarityCheckerLengthTester,
    Values(
        SimilarityCheckerParam{
            .target = "ASD",
            .check = "DSA",
            .expected = 60,
        },
        SimilarityCheckerParam{
            .target = "A",
            .check = "BB",
            .expected = 0,
        },
        SimilarityCheckerParam{
            .target = "AAABB",
            .check = "BAA",
            .expected = 20,
        },
        SimilarityCheckerParam{
            .target = "AA",
            .check = "AAE",
            .expected = 30,
        },
        SimilarityCheckerParam{
            .target = "AAAAAAAAAAA",
            .check = "AAAAAAAAA",
            .expected = 47
        },
        SimilarityCheckerParam{
            .target = "ABCDFEAFESFASEFASEF",
            .check = "A",
            .expected = 0,
        },
        SimilarityCheckerParam{
            .target = "ADF",
            .check = "AFAEWFAEFAEFAE",
            .expected = 0,
        }
    )
);

struct SimilarityCheckerLengthInvalidArgumentTester : public SimilarityCheckerTester {};

TEST_P(SimilarityCheckerLengthInvalidArgumentTester, LengthScoreInvalidArgumentTest) {
    auto&& p = GetParam();
    SimilarityChecker checker(p.target);
    EXPECT_THROW(checker.getLengthSimilarityScore(p.check), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    SimilarityCheckerLengthInvalidArgumentTest,
    SimilarityCheckerLengthInvalidArgumentTester,
    Values(
        SimilarityCheckerParam{
            .target = "adbfelk",
            .check = "AEFJLSI",
        },
        SimilarityCheckerParam{
            .target = "AFELKFJSE",
            .check = "faliejflase",
        },
        SimilarityCheckerParam{
            .target = "232n432",
            .check = "ADKLFJEK",
        },
        SimilarityCheckerParam{
            .target = "ASLFAJES",
            .check = "flskfjlakse",
        }
    )
);
