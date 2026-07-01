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

constexpr size_t ALPHABET_COUNT = 'Z' - 'A' + 1;
using ExistAlphabet = std::bitset<ALPHABET_COUNT>;
ExistAlphabet makeExistAlphabet(const std::string& str) {
    ExistAlphabet exists;
    for (char c : str) exists[c - 'A'] = true;
    return exists;
}

int SimilarityChecker::getAlphabetSimilarityScore(const std::string& checkStr) const {
    static constexpr int ALPHABET_SCORE_MAX = 40;

    auto targetAlphabetExist = makeExistAlphabet(targetStr);
    auto checkAlphabetExist = makeExistAlphabet(checkStr);

    size_t sameCount = (targetAlphabetExist & checkAlphabetExist).count();
    size_t totalCount = (targetAlphabetExist | checkAlphabetExist).count();

    return ALPHABET_SCORE_MAX * sameCount / totalCount;
}

int SimilarityChecker::getScore(const std::string& checkStr) const {
    return 0;
}