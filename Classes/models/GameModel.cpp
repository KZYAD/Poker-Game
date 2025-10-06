#include "GameModel.h"
#include <algorithm>

GameModel::GameModel()
    : _trayCard(nullptr)
{
}

GameModel::~GameModel()
{
    clear();
}

CardModel* GameModel::findCardById(int cardId) const
{
    auto it = _cardMap.find(cardId);
    if (it != _cardMap.end())
    {
        return it->second;
    }
    return nullptr;
}

bool GameModel::removePlayfieldCard(CardModel* card)
{
    if (!card) return false;

    auto it = std::find(_playfieldCards.begin(), _playfieldCards.end(), card);
    if (it != _playfieldCards.end())
    {
        _playfieldCards.erase(it);
        // 注意：不从cardMap中删除，因为卡牌对象仍然存在（会移到底牌区）
        return true;
    }
    return false;
}

bool GameModel::removeStackCard(CardModel* card)
{
    if (!card) return false;

    auto it = std::find(_stackCards.begin(), _stackCards.end(), card);
    if (it != _stackCards.end())
    {
        _stackCards.erase(it);
        // 注意：不从cardMap中删除，因为卡牌对象仍然存在（会移到底牌区）
        return true;
    }
    return false;
}

void GameModel::addPlayfieldCard(CardModel* card)
{
    if (!card) return;

    _playfieldCards.push_back(card);
    // cardMap应该已经包含这张卡牌，但为了安全起见仍然设置
    _cardMap[card->getId()] = card;
}

void GameModel::addStackCard(CardModel* card)
{
    if (!card) return;

    _stackCards.push_back(card);
    // cardMap应该已经包含这张卡牌，但为了安全起见仍然设置
    _cardMap[card->getId()] = card;
}

void GameModel::clear()
{
    // 删除所有卡牌对象
    for (auto card : _playfieldCards)
    {
        delete card;
    }
    _playfieldCards.clear();

    for (auto card : _stackCards)
    {
        delete card;
    }
    _stackCards.clear();

    if (_trayCard)
    {
        delete _trayCard;
        _trayCard = nullptr;
    }

    _cardMap.clear();
}
