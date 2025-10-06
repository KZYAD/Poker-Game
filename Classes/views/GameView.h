#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "CardView.h"
#include <map>
#include <functional>

class GameModel;

/**
 * @brief 游戏主视图类
 * 负责整个游戏界面的显示，包括主牌区、底牌区和备用牌堆
 */
class GameView : public cocos2d::Layer
{
public:
    typedef std::function<void(int cardId)> CardClickCallback;
    typedef std::function<void()> UndoClickCallback;

    GameView();
    virtual ~GameView();

    /**
     * @brief 创建游戏视图
     * @param gameModel 游戏数据模型（const指针）
     * @param playfieldCallback 主牌区卡牌点击回调
     * @param stackCallback 备用牌堆卡牌点击回调
     * @param undoCallback 撤销按钮点击回调
     * @return 游戏视图对象
     */
    static GameView* create(const GameModel* gameModel,
                           const CardClickCallback& playfieldCallback,
                           const CardClickCallback& stackCallback,
                           const UndoClickCallback& undoCallback);

    /**
     * @brief 初始化游戏视图
     */
    bool init(const GameModel* gameModel,
              const CardClickCallback& playfieldCallback,
              const CardClickCallback& stackCallback,
              const UndoClickCallback& undoCallback);

    /**
     * @brief 根据ID获取卡牌视图
     * @param cardId 卡牌ID
     * @return 卡牌视图指针，未找到返回nullptr
     */
    CardView* getCardView(int cardId);

    /**
     * @brief 从主牌区移除卡牌视图
     * @param cardId 卡牌ID
     */
    void removePlayfieldCardView(int cardId);

    /**
     * @brief 从备用牌堆移除卡牌视图
     * @param cardId 卡牌ID
     */
    void removeStackCardView(int cardId);

    /**
     * @brief 添加卡牌视图到主牌区
     * @param cardView 卡牌视图
     */
    void addPlayfieldCardView(CardView* cardView);

    /**
     * @brief 添加卡牌视图到备用牌堆
     * @param cardView 卡牌视图
     */
    void addStackCardView(CardView* cardView);

    /**
     * @brief 更新底牌显示
     * @param cardView 新的底牌视图
     */
    void updateTrayCardView(CardView* cardView);

    /**
     * @brief 获取底牌位置
     * @return 底牌的世界坐标
     */
    cocos2d::Vec2 getTrayPosition() const;

    /**
     * @brief 获取备用牌堆位置
     * @return 备用牌堆的世界坐标
     */
    cocos2d::Vec2 getStackPosition() const;

private:
    /**
     * @brief 创建主牌区
     */
    void createPlayfield();

    /**
     * @brief 创建底牌区
     */
    void createTrayArea();

    /**
     * @brief 创建备用牌堆
     */
    void createStackArea();

    /**
     * @brief 创建UI按钮
     */
    void createUIButtons();

private:
    const GameModel* _gameModel;                // 游戏数据模型（const指针）
    CardClickCallback _playfieldCallback;       // 主牌区点击回调
    CardClickCallback _stackCallback;           // 备用牌堆点击回调
    UndoClickCallback _undoCallback;            // 撤销按钮回调

    cocos2d::Node* _playfieldNode;              // 主牌区节点
    cocos2d::Node* _trayNode;                   // 底牌区节点
    cocos2d::Node* _stackNode;                  // 备用牌堆节点

    std::map<int, CardView*> _cardViews;        // 卡牌ID到视图的映射
    int _trayZOrder;                            // 底牌区下一个卡牌的z-order

    static const float kPlayfieldHeight;        // 主牌区高度
    static const float kTrayAreaHeight;         // 底牌区高度
    static const cocos2d::Vec2 kTrayPosition;   // 底牌位置
    static const cocos2d::Vec2 kStackPosition;  // 备用牌堆位置
};

#endif // __GAME_VIEW_H__
