#include "UndoModel.h"

UndoModel::UndoModel()
    : _actionType(UAT_NONE)
    , _cardId(0)
    , _previousTrayCardId(0)
    , _originalPosition(cocos2d::Vec2::ZERO)
{
}

UndoModel::UndoModel(UndoActionType type, int cardId, int previousTrayCardId, const cocos2d::Vec2& originalPos)
    : _actionType(type)
    , _cardId(cardId)
    , _previousTrayCardId(previousTrayCardId)
    , _originalPosition(originalPos)
{
}

UndoModel::~UndoModel()
{
}
