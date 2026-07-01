#include "similarity_checker.h"

static constexpr int LENGTH_SCORE_MAX = 60;

SimilarityChecker::SimilarityChecker(const std::string& targetStr) : targetStr(targetStr) {}

int SimilarityChecker::getLengthSimilarityScore(const std::string& checkStr) const {
    int targetStrSize = targetStr.size();
    int checkStrSize = checkStr.size();

    int shortSize = std::min(targetStrSize, checkStrSize);

    int sizeGap = std::abs(targetStrSize - checkStrSize);
    sizeGap = std::min(sizeGap, shortSize);

    return LENGTH_SCORE_MAX - LENGTH_SCORE_MAX * sizeGap / shortSize;
}

int SimilarityChecker::getAlphabetSimilarityScore(const std::string& checkStr) const {
    return 0;
}

int SimilarityChecker::getScore(const std::string& checkStr) const {
    return 0;
}