#pragma once

#include <string>

class SimilarityChecker {
public:
    SimilarityChecker(const std::string& targetStr);

    int getLengthSimilarityScore() const;
    int getAlphabetSimilarityScore() const;
    int getScore() const;
private:
};
