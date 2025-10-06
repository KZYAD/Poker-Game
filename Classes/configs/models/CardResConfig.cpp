#include "CardResConfig.h"

std::string CardResConfig::getCardBackPath()
{
    return "res/card_general.png";
}

std::string CardResConfig::getCardSuitPath(int suit)
{
    static const char* kSuitNames[] = {"club", "diamond", "heart", "spade"};
    if (suit < 0 || suit > 3) return "";

    char path[128];
    sprintf(path, "res/suits/%s.png", kSuitNames[suit]);
    return path;
}

std::string CardResConfig::getCardBigNumberPath(int face, bool isRed)
{
    static const char* kFaceNames[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    if (face < 0 || face > 12) return "";

    const char* color = isRed ? "red" : "black";
    char path[128];
    sprintf(path, "res/number/big_%s_%s.png", color, kFaceNames[face]);
    return path;
}

std::string CardResConfig::getCardSmallNumberPath(int face, bool isRed)
{
    static const char* kFaceNames[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    if (face < 0 || face > 12) return "";

    const char* color = isRed ? "red" : "black";
    char path[128];
    sprintf(path, "res/number/small_%s_%s.png", color, kFaceNames[face]);
    return path;
}
