#pragma once

#include <string>

class SimilarityChecker {
public:
    SimilarityChecker(const std::string& targetStr);

    int getLengthSimilarityScore(const std::string& checkStr) const;
    int getAlphabetSimilarityScore(const std::string& checkStr) const;
    int getScore(const std::string& checkStr) const;
private:
    std::string targetStr;
};
