#include "similarity_checker.h"

SimilarityChecker::SimilarityChecker(const std::string& targetStr) : targetStr(targetStr) {}

int SimilarityChecker::getLengthSimilarityScore(const std::string& checkStr) const {
    int targetStrLength = targetStr.size();
    int checkStrLength = checkStr.size();

    int strGap = std::abs(targetStrLength - checkStrLength);
    int shortSize = std::min(targetStrLength, checkStrLength);

    int gap = targetStr.size() - checkStr.size();
    return 60 - 60 * strGap / shortSize;
}

int SimilarityChecker::getAlphabetSimilarityScore(const std::string& checkStr) const {
    return 0;
}

int SimilarityChecker::getScore(const std::string& checkStr) const {
    return 0;
}