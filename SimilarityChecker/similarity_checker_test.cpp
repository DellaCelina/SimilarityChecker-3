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
            .target = "",
            .check = "AEFJLSI",
        },
        SimilarityCheckerParam{
            .target = "FAWEFAE",
            .check = "",
        },
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

struct SimilarityCheckerAlphabetTester : public SimilarityCheckerTester {};

TEST_P(SimilarityCheckerAlphabetTester, AlphabetTest) {
    auto&& p = GetParam();
    SimilarityChecker checker(p.target);
    EXPECT_EQ(checker.getAlphabetSimilarityScore(p.check), p.expected);
}

INSTANTIATE_TEST_SUITE_P(
    SimilarityCheckerAlphabetTest,
    SimilarityCheckerAlphabetTester,
    Values(
        SimilarityCheckerParam{
            .target = "ASD",
            .check = "DSA",
            .expected = 40,
        },
        SimilarityCheckerParam{
            .target = "A",
            .check = "BB",
            .expected = 0,
        },
        SimilarityCheckerParam{
            .target = "AAABBAAAA",
            .check = "BA",
            .expected = 40,
        },
        SimilarityCheckerParam{
            .target = "AA",
            .check = "AAE",
            .expected = 20,
        },
        SimilarityCheckerParam{
            .target = "ABCDEFGHIJKLMN",
            .check = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            .expected = 40 * 14 / 26,
        }
    )
);

struct SimilarityCheckerAlphabetInvalidArgumentTester : public SimilarityCheckerTester {};

TEST_P(SimilarityCheckerAlphabetInvalidArgumentTester, AlphabetScoreInvalidArgumentTest) {
    auto&& p = GetParam();
    SimilarityChecker checker(p.target);
    EXPECT_THROW(checker.getAlphabetSimilarityScore(p.check), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    SimilarityCheckerAlphabetInvalidArgumentTest,
    SimilarityCheckerAlphabetInvalidArgumentTester,
    Values(
        SimilarityCheckerParam{
            .target = "",
            .check = "AEFJLSI",
        },
        SimilarityCheckerParam{
            .target = "FAWEFAE",
            .check = "",
        },
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

