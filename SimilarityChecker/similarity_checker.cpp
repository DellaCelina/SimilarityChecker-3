#include "similarity_checker.h"

#include <stdexcept>
#include <bitset>

SimilarityChecker::SimilarityChecker(const std::string& targetStr) : targetStr(targetStr) {}

static void checkStrValid(const std::string& str) {
    for (char c : str) if (c < 'A' || c > 'Z') throw std::invalid_argument("String should be uppercase");
    if (str.size() == 0) throw std::invalid_argument("String can't be empty");
}

static int calculateLengthScore(int targetStrSize, int checkStrSize) {
    static constexpr int LENGTH_SCORE_MAX = 60;

    int shortSize = std::min(targetStrSize, checkStrSize);
    int sizeGap = std::min(
        std::abs(targetStrSize - checkStrSize),
        shortSize);

    return LENGTH_SCORE_MAX - LENGTH_SCORE_MAX * sizeGap / shortSize;
}

int SimilarityChecker::getLengthSimilarityScore(const std::string& checkStr) const {
    checkStrValid(targetStr);
    checkStrValid(checkStr);
    return calculateLengthScore(targetStr.size(), checkStr.size());
}

int SimilarityChecker::getAlphabetSimilarityScore(const std::string& checkStr) const {
    std::bitset<26> targetAlphabetExist;
    std::bitset<26> checkAlphabetExist;

    for (char c : targetStr) targetAlphabetExist[c - 'A'] = true;
    for (char c : checkStr) checkAlphabetExist[c - 'A'] = true;

    std::bitset<26> totalAlphabetExist = targetAlphabetExist | checkAlphabetExist;
    std::bitset<26> sameAlphabetExist = targetAlphabetExist & checkAlphabetExist;

    return 40 * sameAlphabetExist.count() / totalAlphabetExist.count();
}

int SimilarityChecker::getScore(const std::string& checkStr) const {
    return 0;
}