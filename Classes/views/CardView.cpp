#include "CardView.h"
#include "../models/CardModel.h"
#include "../configs/models/CardResConfig.h"

USING_NS_CC;

const float CardView::kCardWidth = 120.0f;
const float CardView::kCardHeight = 160.0f;

CardView::CardView()
    : _cardModel(nullptr)
    , _cardId(0)
    , _cardSprite(nullptr)
    , _touchListener(nullptr)
{
}

CardView::~CardView()
{
    if (_touchListener)
    {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener = nullptr;
    }
}

CardView* CardView::create(const CardModel* cardModel, const CardClickCallback& callback)
{
    CardView* view = new (std::nothrow) CardView();
    if (view && view->init(cardModel, callback))
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool CardView::init(const CardModel* cardModel, const CardClickCallback& callback)
{
    if (!Node::init())
    {
        return false;
    }

    _cardModel = cardModel;
    _cardId = cardModel ? cardModel->getId() : 0;
    _clickCallback = callback;

    // 设置节点大小
    setContentSize(Size(kCardWidth, kCardHeight));
    setAnchorPoint(Vec2(0.5f, 0.5f));

    // 创建卡牌UI
    createCardUI();

    // 设置触摸监听
    setupTouchListener();

    return true;
}

void CardView::createCardUI()
{
    if (!_cardModel) return;

    // 创建卡牌背景
    std::string backPath = CardResConfig::getCardBackPath();
    _cardSprite = Sprite::create(backPath);
    if (_cardSprite)
    {
        _cardSprite->setPosition(kCardWidth / 2, kCardHeight / 2);
        addChild(_cardSprite, 0);
    }
    else
    {
        CCLOG("Failed to load card back: %s", backPath.c_str());
    }

    // 添加大数字（中间偏下）
    bool isRed = _cardModel->isRed();
    std::string bigNumPath = CardResConfig::getCardBigNumberPath(_cardModel->getFace(), isRed);
    Sprite* bigNumSprite = Sprite::create(bigNumPath);
    if (bigNumSprite)
    {
        bigNumSprite->setPosition(kCardWidth / 2, kCardHeight / 2 - 20);
        addChild(bigNumSprite, 1);
        CCLOG("Loaded big number: %s at position (%f, %f)", bigNumPath.c_str(), kCardWidth / 2, kCardHeight / 2 - 20);
    }
    else
    {
        CCLOG("Failed to load big number: %s", bigNumPath.c_str());
    }

    // 添加小数字（左上角，更靠上）
    std::string smallNumPath = CardResConfig::getCardSmallNumberPath(_cardModel->getFace(), isRed);
    Sprite* smallNumSprite = Sprite::create(smallNumPath);
    if (smallNumSprite)
    {
        smallNumSprite->setPosition(15, kCardHeight - 5);
        smallNumSprite->setScale(0.8f);
        addChild(smallNumSprite, 2);
        CCLOG("Loaded small number: %s at position (15, %f)", smallNumPath.c_str(), kCardHeight - 5);
    }
    else
    {
        CCLOG("Failed to load small number: %s", smallNumPath.c_str());
    }

    // 添加花色图标（右上角，更靠上）
    std::string suitPath = CardResConfig::getCardSuitPath(_cardModel->getSuit());
    Sprite* suitSprite = Sprite::create(suitPath);
    if (suitSprite)
    {
        suitSprite->setPosition(kCardWidth - 15, kCardHeight - 5);
        suitSprite->setScale(0.6f);
        addChild(suitSprite, 2);
        CCLOG("Loaded suit: %s at position (%f, %f)", suitPath.c_str(), kCardWidth - 15, kCardHeight - 5);
    }
    else
    {
        CCLOG("Failed to load suit: %s", suitPath.c_str());
    }
}

void CardView::setupTouchListener()
{
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);

    _touchListener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);

        if (rect.containsPoint(locationInNode))
        {
            return true;
        }
        return false;
    };

    _touchListener->onTouchEnded = [this](Touch* touch, Event* event) {
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);

        if (rect.containsPoint(locationInNode))
        {
            if (_clickCallback)
            {
                _clickCallback(_cardId);
            }
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

void CardView::playMoveAnimation(const Vec2& targetPos, float duration, const std::function<void()>& callback)
{
    auto moveTo = MoveTo::create(duration, targetPos);

    if (callback)
    {
        auto seq = Sequence::create(moveTo, CallFunc::create(callback), nullptr);
        runAction(seq);
    }
    else
    {
        runAction(moveTo);
    }
}

void CardView::setClickEnabled(bool enabled)
{
    if (_touchListener)
    {
        _touchListener->setEnabled(enabled);
    }
}
