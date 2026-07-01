#include "similarity_checker.h"

#include <stdexcept>

static constexpr int LENGTH_SCORE_MAX = 60;

SimilarityChecker::SimilarityChecker(const std::string& targetStr) : targetStr(targetStr) {}

int SimilarityChecker::getLengthSimilarityScore(const std::string& checkStr) const {
    for (char c : targetStr) if (c < 'A' || c > 'Z') throw std::invalid_argument("String should be uppercase");
    for (char c : checkStr) if (c < 'A' || c > 'Z') throw std::invalid_argument("String should be uppercase");

    int targetStrSize = targetStr.size();
    if (targetStrSize == 0) throw std::invalid_argument("String can't be empty");

    int checkStrSize = checkStr.size();
    if (checkStrSize == 0) throw std::invalid_argument("String can't be empty");

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