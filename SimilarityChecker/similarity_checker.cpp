#include "similarity_checker.h"

#include <stdexcept>

static constexpr int LENGTH_SCORE_MAX = 60;

SimilarityChecker::SimilarityChecker(const std::string& targetStr) : targetStr(targetStr) {}

static void checkStrValid(const std::string& str) {
    for (char c : str) if (c < 'A' || c > 'Z') throw std::invalid_argument("String should be uppercase");
    if (str.size() == 0) throw std::invalid_argument("String can't be empty");
}

int SimilarityChecker::getLengthSimilarityScore(const std::string& checkStr) const {
    checkStrValid(targetStr);
    checkStrValid(checkStr);

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