#include "GameModelGenerator.h"
#include "../configs/models/LevelConfig.h"
#include "../models/GameModel.h"
#include "../models/CardModel.h"

int GameModelGenerator::s_nextCardId = 1;

GameModel* GameModelGenerator::generateFromLevelConfig(const LevelConfig* levelConfig)
{
    if (!levelConfig) return nullptr;

    GameModel* gameModel = new GameModel();

    // 生成主牌区卡牌
    const auto& playfieldCards = levelConfig->getPlayfieldCards();
    for (const auto& cardData : playfieldCards)
    {
        CardModel* card = new CardModel(
            generateCardId(),
            static_cast<CardFaceType>(cardData.cardFace),
            static_cast<CardSuitType>(cardData.cardSuit)
        );
        card->setPosition(cardData.position);
        gameModel->addPlayfieldCard(card);
    }

    // 生成备用牌堆卡牌
    const auto& stackCards = levelConfig->getStackCards();
    for (const auto& cardData : stackCards)
    {
        CardModel* card = new CardModel(
            generateCardId(),
            static_cast<CardFaceType>(cardData.cardFace),
            static_cast<CardSuitType>(cardData.cardSuit)
        );
        card->setPosition(cardData.position);
        gameModel->addStackCard(card);
    }

    // 初始底牌为备用牌堆的第一张
    if (!gameModel->getStackCards().empty())
    {
        CardModel* firstStackCard = gameModel->getStackCards().front();
        gameModel->removeStackCard(firstStackCard);
        gameModel->setTrayCard(firstStackCard);
    }

    return gameModel;
}

int GameModelGenerator::generateCardId()
{
    return s_nextCardId++;
}
