#include "GameView.h"
#include "../models/GameModel.h"
#include "../models/CardModel.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

const float GameView::kPlayfieldHeight = 1500.0f;
const float GameView::kTrayAreaHeight = 580.0f;
const Vec2 GameView::kTrayPosition = Vec2(540, 300);
const Vec2 GameView::kStackPosition = Vec2(200, 300);

GameView::GameView()
    : _gameModel(nullptr)
    , _playfieldNode(nullptr)
    , _trayNode(nullptr)
    , _stackNode(nullptr)
    , _trayZOrder(0)
{
}

GameView::~GameView()
{
}

GameView* GameView::create(const GameModel* gameModel,
                          const CardClickCallback& playfieldCallback,
                          const CardClickCallback& stackCallback,
                          const UndoClickCallback& undoCallback)
{
    GameView* view = new (std::nothrow) GameView();
    if (view && view->init(gameModel, playfieldCallback, stackCallback, undoCallback))
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool GameView::init(const GameModel* gameModel,
                   const CardClickCallback& playfieldCallback,
                   const CardClickCallback& stackCallback,
                   const UndoClickCallback& undoCallback)
{
    if (!Layer::init())
    {
        return false;
    }

    _gameModel = gameModel;
    _playfieldCallback = playfieldCallback;
    _stackCallback = stackCallback;
    _undoCallback = undoCallback;

    // 设置背景色
    auto bg = LayerColor::create(Color4B(34, 139, 34, 255));
    addChild(bg, -1);

    // 创建各个区域
    createPlayfield();
    createTrayArea();
    createStackArea();
    createUIButtons();

    return true;
}

void GameView::createPlayfield()
{
    _playfieldNode = Node::create();
    _playfieldNode->setPosition(0, kTrayAreaHeight);
    addChild(_playfieldNode);

    if (!_gameModel) return;

    // 创建主牌区卡牌视图
    const auto& playfieldCards = _gameModel->getPlayfieldCards();
    for (auto cardModel : playfieldCards)
    {
        CardView* cardView = CardView::create(cardModel, _playfieldCallback);
        if (cardView)
        {
            cardView->setPosition(cardModel->getPosition());
            _playfieldNode->addChild(cardView);
            _cardViews[cardModel->getId()] = cardView;
        }
    }
}

void GameView::createTrayArea()
{
    _trayNode = Node::create();
    _trayNode->setPosition(0, 0);
    addChild(_trayNode);

    if (!_gameModel) return;

    // 创建底牌视图
    CardModel* trayCard = _gameModel->getTrayCard();
    if (trayCard)
    {
        CardView* cardView = CardView::create(trayCard, nullptr);
        if (cardView)
        {
            cardView->setPosition(kTrayPosition);
            cardView->setClickEnabled(false);  // 底牌不可点击
            _trayNode->addChild(cardView, _trayZOrder++);
            _cardViews[trayCard->getId()] = cardView;
        }
    }
}

void GameView::createStackArea()
{
    _stackNode = Node::create();
    _stackNode->setPosition(0, 0);
    addChild(_stackNode);

    if (!_gameModel) return;

    // 创建备用牌堆视图（显示为一叠牌）
    const auto& stackCards = _gameModel->getStackCards();
    for (size_t i = 0; i < stackCards.size(); i++)
    {
        CardModel* cardModel = stackCards[i];
        CardView* cardView = CardView::create(cardModel, _stackCallback);
        if (cardView)
        {
            // 叠放效果：每张牌稍微偏移一点
            Vec2 offset(i * 2, i * 2);
            cardView->setPosition(kStackPosition + offset);

            // 只有最上面的牌可以点击
            cardView->setClickEnabled(i == stackCards.size() - 1);

            _stackNode->addChild(cardView);
            _cardViews[cardModel->getId()] = cardView;
        }
    }
}

void GameView::createUIButtons()
{
    // 创建撤销按钮
    auto undoButton = ui::Button::create();
    undoButton->setTitleText("回退");
    undoButton->setTitleFontSize(36);
    undoButton->setPosition(Vec2(880, 300));
    undoButton->addClickEventListener([this](Ref*) {
        if (_undoCallback)
        {
            _undoCallback();
        }
    });
    addChild(undoButton);
}

CardView* GameView::getCardView(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end())
    {
        return it->second;
    }
    return nullptr;
}

void GameView::removePlayfieldCardView(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end())
    {
        it->second->removeFromParent();
        _cardViews.erase(it);
    }
}

void GameView::removeStackCardView(int cardId)
{
    removePlayfieldCardView(cardId);
}

void GameView::addPlayfieldCardView(CardView* cardView)
{
    if (!cardView) return;

    // 从当前父节点移除后添加到主牌区
    cardView->retain();
    cardView->removeFromParent();
    _playfieldNode->addChild(cardView);
    cardView->release();

    _cardViews[cardView->getCardId()] = cardView;
}

void GameView::addStackCardView(CardView* cardView)
{
    if (!cardView) return;

    // 从当前父节点移除后添加到备用牌堆
    cardView->retain();
    cardView->removeFromParent();
    _stackNode->addChild(cardView);
    cardView->release();

    _cardViews[cardView->getCardId()] = cardView;
}

void GameView::updateTrayCardView(CardView* cardView)
{
    if (!cardView) return;

    // 将卡牌移动到底牌区
    cardView->retain();
    cardView->removeFromParent();
    // 设置递增的z-order，确保新卡牌显示在上方
    _trayNode->addChild(cardView, _trayZOrder++);
    cardView->release();

    cardView->setPosition(kTrayPosition);
    cardView->setClickEnabled(false);
}

Vec2 GameView::getTrayPosition() const
{
    return _trayNode->convertToWorldSpace(kTrayPosition);
}

Vec2 GameView::getStackPosition() const
{
    return _stackNode->convertToWorldSpace(kStackPosition);
}
