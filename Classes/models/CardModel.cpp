#include "CardModel.h"

CardModel::CardModel()
    : _id(0)
    , _face(CFT_NONE)
    , _suit(CST_NONE)
    , _position(cocos2d::Vec2::ZERO)
    , _isFaceUp(true)
    , _isBlocked(false)
    , _zOrder(0)
{
}

CardModel::CardModel(int id, CardFaceType face, CardSuitType suit)
    : _id(id)
    , _face(face)
    , _suit(suit)
    , _position(cocos2d::Vec2::ZERO)
    , _isFaceUp(true)
    , _isBlocked(false)
    , _zOrder(0)
{
}

CardModel::~CardModel()
{
}

bool CardModel::isRed() const
{
    return _suit == CST_HEARTS || _suit == CST_DIAMONDS;
}

int CardModel::getFaceValue() const
{
    if (_face == CFT_ACE) return 1;
    if (_face >= CFT_TWO && _face <= CFT_KING)
        return _face + 1;
    return 0;
}
