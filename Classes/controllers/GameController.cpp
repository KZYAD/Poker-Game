#include "GameController.h"
#include "../models/GameModel.h"
#include "../models/CardModel.h"
#include "../models/UndoModel.h"
#include "../views/GameView.h"
#include "../views/CardView.h"
#include "../configs/models/LevelConfig.h"
#include "../configs/loaders/LevelConfigLoader.h"
#include "../services/GameModelGenerator.h"
#include "../managers/UndoManager.h"
#include "../utils/CardMatchUtils.h"

USING_NS_CC;

GameController::GameController()
    : _gameModel(nullptr)
    , _gameView(nullptr)
    , _undoManager(nullptr)
{
}

GameController::~GameController()
{
    if (_gameModel)
    {
        delete _gameModel;
        _gameModel = nullptr;
    }

    if (_undoManager)
    {
        delete _undoManager;
        _undoManager = nullptr;
    }
}

bool GameController::startGame(int levelId, Node* parentNode)
{
    // 加载关卡配置
    LevelConfig* levelConfig = LevelConfigLoader::loadLevelConfig(levelId);
    if (!levelConfig)
    {
        CCLOG("Failed to load level config: %d", levelId);
        return false;
    }

    // 初始化游戏数据
    if (!initGameData(levelConfig))
    {
        delete levelConfig;
        return false;
    }

    delete levelConfig;

    // 初始化撤销管理器
    _undoManager = new UndoManager();

    // 初始化游戏视图
    initGameView(parentNode);

    return true;
}

bool GameController::initGameData(const LevelConfig* levelConfig)
{
    // 使用服务层生成游戏数据模型
    _gameModel = GameModelGenerator::generateFromLevelConfig(levelConfig);
    if (!_gameModel)
    {
        CCLOG("Failed to generate game model");
        return false;
    }

    return true;
}

void GameController::initGameView(Node* parentNode)
{
    // 创建游戏视图，传入回调函数
    auto playfieldCallback = [this](int cardId) {
        this->handlePlayfieldCardClick(cardId);
    };

    auto stackCallback = [this](int cardId) {
        this->handleStackCardClick(cardId);
    };

    auto undoCallback = [this]() {
        this->handleUndoClick();
    };

    _gameView = GameView::create(_gameModel, playfieldCallback, stackCallback, undoCallback);
    if (_gameView)
    {
        parentNode->addChild(_gameView);
    }
}

void GameController::handlePlayfieldCardClick(int cardId)
{
    if (!_gameModel || !_gameView) return;

    // 获取点击的卡牌和底牌
    CardModel* clickedCard = _gameModel->findCardById(cardId);
    CardModel* trayCard = _gameModel->getTrayCard();

    if (!clickedCard || !trayCard)
    {
        CCLOG("Card not found: %d", cardId);
        return;
    }

    // 检查是否可以匹配
    if (!CardMatchUtils::canMatchWithTray(clickedCard, trayCard))
    {
        CCLOG("Card %d cannot match with tray card", cardId);
        return;
    }

    // 执行移动
    movePlayfieldCardToTray(cardId);
}

void GameController::handleStackCardClick(int cardId)
{
    if (!_gameModel || !_gameView) return;

    // 备用牌堆的牌直接移动到底牌（不需要匹配）
    moveStackCardToTray(cardId);
}

void GameController::handleUndoClick()
{
    if (!_undoManager || !_undoManager->canUndo())
    {
        CCLOG("No undo available");
        return;
    }

    UndoModel undoModel;
    if (!_undoManager->popUndo(undoModel))
    {
        return;
    }

    // 执行撤销
    bool isFromStack = (undoModel.getActionType() == UAT_STACK_TO_TRAY);
    executeUndo(undoModel.getCardId(),
               undoModel.getPreviousTrayCardId(),
               undoModel.getOriginalPosition(),
               isFromStack);
}

void GameController::movePlayfieldCardToTray(int cardId)
{
    CardModel* card = _gameModel->findCardById(cardId);
    CardModel* previousTrayCard = _gameModel->getTrayCard();
    if (!card || !previousTrayCard) return;

    // 记录原始位置
    Vec2 originalPos = card->getPosition();

    // 记录撤销信息
    UndoModel undoModel(UAT_PLAYFIELD_TO_TRAY, cardId,
                       previousTrayCard->getId(), originalPos);
    _undoManager->addUndo(undoModel);

    // 从主牌区移除
    _gameModel->removePlayfieldCard(card);

    // 设置为新的底牌
    _gameModel->setTrayCard(card);

    // 更新视图
    CardView* cardView = _gameView->getCardView(cardId);
    if (cardView)
    {
        Vec2 trayPos = _gameView->getTrayPosition();
        Vec2 localTrayPos = cardView->getParent()->convertToNodeSpace(trayPos);

        cardView->playMoveAnimation(localTrayPos, 0.3f, [this, cardView]() {
            // 动画完成后更新视图
            _gameView->updateTrayCardView(cardView);
        });
    }

    // 之前的底牌不需要移回主牌区，已被消除
}

void GameController::moveStackCardToTray(int cardId)
{
    CardModel* card = _gameModel->findCardById(cardId);
    CardModel* previousTrayCard = _gameModel->getTrayCard();
    if (!card || !previousTrayCard) return;

    // 记录原始位置
    Vec2 originalPos = _gameView->getStackPosition();

    // 记录撤销信息
    UndoModel undoModel(UAT_STACK_TO_TRAY, cardId,
                       previousTrayCard->getId(), originalPos);
    _undoManager->addUndo(undoModel);

    // 从备用牌堆移除
    _gameModel->removeStackCard(card);

    // 设置为新的底牌
    _gameModel->setTrayCard(card);

    // 更新视图
    CardView* cardView = _gameView->getCardView(cardId);
    if (cardView)
    {
        Vec2 trayPos = _gameView->getTrayPosition();
        Vec2 localTrayPos = cardView->getParent()->convertToNodeSpace(trayPos);

        cardView->playMoveAnimation(localTrayPos, 0.3f, [this, cardView]() {
            _gameView->updateTrayCardView(cardView);
        });
    }

    // 之前的底牌不需要移回备用牌堆，已被消除
}

void GameController::executeUndo(int cardId, int previousTrayCardId,
                                const Vec2& originalPos, bool isFromStack)
{
    CardModel* card = _gameModel->findCardById(cardId);
    CardModel* previousTrayCard = _gameModel->findCardById(previousTrayCardId);
    if (!card || !previousTrayCard) return;

    // 更新视图
    CardView* cardView = _gameView->getCardView(cardId);
    CardView* previousTrayView = _gameView->getCardView(previousTrayCardId);

    if (!cardView || !previousTrayView) return;

    // 获取当前在底牌区的世界坐标位置
    Vec2 trayWorldPos = _gameView->getTrayPosition();

    // 1. 先将当前底牌（card）移回原位置
    if (isFromStack)
    {
        _gameView->addStackCardView(cardView);
        // 设置起始位置为底牌位置（在新父节点坐标系下）
        cardView->setPosition(cardView->getParent()->convertToNodeSpace(trayWorldPos));
        // 目标位置：备用牌堆位置
        Vec2 targetPos = cardView->getParent()->convertToNodeSpace(_gameView->getStackPosition());
        cardView->playMoveAnimation(targetPos, 0.3f, [cardView]() {
            cardView->setClickEnabled(true);
        });
    }
    else
    {
        _gameView->addPlayfieldCardView(cardView);
        // 设置起始位置为底牌位置（在新父节点坐标系下）
        cardView->setPosition(cardView->getParent()->convertToNodeSpace(trayWorldPos));
        // 目标位置：原始位置（已经是主牌区坐标系下的位置）
        cardView->playMoveAnimation(originalPos, 0.3f, [cardView]() {
            cardView->setClickEnabled(true);
        });
    }

    // 2. 更新数据模型
    card->setPosition(originalPos);
    if (isFromStack)
    {
        _gameModel->addStackCard(card);
    }
    else
    {
        _gameModel->addPlayfieldCard(card);
    }

    // 3. 恢复之前的底牌
    _gameModel->setTrayCard(previousTrayCard);

    // 4. 更新之前的底牌视图，使其成为顶部卡牌
    _gameView->updateTrayCardView(previousTrayView);
}
