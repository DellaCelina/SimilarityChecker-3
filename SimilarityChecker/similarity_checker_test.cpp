#include <string>

#include "gmock/gmock.h"

using namespace testing;

struct SimilarityCheckerParam {
    std::string target;
    std::string check;
    int score;
};
struct SimilarityCheckerTester : public TestWithParam<SimilarityCheckerParam> {
};
