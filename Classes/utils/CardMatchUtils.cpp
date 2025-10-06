#include "CardMatchUtils.h"
#include "../models/CardModel.h"
#include <cmath>

bool CardMatchUtils::canMatch(const CardModel* card1, const CardModel* card2)
{
    if (!card1 || !card2) return false;

    int face1 = card1->getFaceValue();
    int face2 = card2->getFaceValue();

    int diff = getFaceDifference(face1, face2);
    return diff == 1;
}

bool CardMatchUtils::canMatchWithTray(const CardModel* card, const CardModel* trayCard)
{
    return canMatch(card, trayCard);
}

int CardMatchUtils::getFaceDifference(int face1, int face2)
{
    // 计算普通差值
    int normalDiff = std::abs(face1 - face2);

    // 考虑A(1)和K(13)的循环情况
    // A可以和2或K匹配，K可以和Q或A匹配
    int circularDiff = 13 - normalDiff;

    // 返回较小的差值
    return std::min(normalDiff, circularDiff);
}
