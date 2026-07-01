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

static const auto invalidArgumentCases = Values(
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
    );

namespace length_test {

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
    invalidArgumentCases
);

}  // namespace length_test

namespace alphabet_test {

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
    invalidArgumentCases
);

}  // namespace alphabet_test

namespace total_test {

struct SimilarityCheckerTotalScoreTester : public SimilarityCheckerTester {};

TEST_P(SimilarityCheckerTotalScoreTester, TotalScoreTest) {
    auto&& p = GetParam();
    SimilarityChecker checker(p.target);
    EXPECT_EQ(checker.getScore(p.check), p.expected);
}

INSTANTIATE_TEST_SUITE_P(
    SimilarityCheckerTotalScoreTest,
    SimilarityCheckerTotalScoreTester,
    Values(
        SimilarityCheckerParam{
            .target = "ASD",
            .check = "DSA",
            .expected = 60 + 40,
        },
        SimilarityCheckerParam{
            .target = "A",
            .check = "BB",
            .expected = 0 + 0,
        },
        SimilarityCheckerParam{
            .target = "AAABB",
            .check = "BAA",
            .expected = 20 + 40,
        },
        SimilarityCheckerParam{
            .target = "AA",
            .check = "AAE",
            .expected = 30 + 20,
        },
        SimilarityCheckerParam{
            .target = "AAAAAAAAAAA",
            .check = "AAAAAAAAA",
            .expected = 47 + 40,
        },
        SimilarityCheckerParam{
            .target = "ABCDFE",
            .check = "A",
            .expected = 0 + 6,
        },
        SimilarityCheckerParam{
            .target = "A",
            .check = "ABCDFE",
            .expected = 0 + 6,
        }
        )
);

struct SimilarityCheckerTotalInvalidArgumentTester : public SimilarityCheckerTester {};

TEST_P(SimilarityCheckerTotalInvalidArgumentTester, AlphabetScoreInvalidArgumentTest) {
    auto&& p = GetParam();
    SimilarityChecker checker(p.target);
    EXPECT_THROW(checker.getScore(p.check), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    SimilarityCheckerTotalInvalidArgumentTest,
    SimilarityCheckerTotalInvalidArgumentTester,
    invalidArgumentCases
);

}  // namespace total
