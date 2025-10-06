#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "cocos2d.h"
#include <functional>

class CardModel;

/**
 * @brief 卡牌视图类
 * 负责单张卡牌的UI显示和交互
 * 通过回调接口与Controller交互
 */
class CardView : public cocos2d::Node
{
public:
    typedef std::function<void(int cardId)> CardClickCallback;

    CardView();
    virtual ~CardView();

    /**
     * @brief 创建卡牌视图
     * @param cardModel 卡牌数据模型（const指针）
     * @param callback 点击回调函数
     * @return 卡牌视图对象
     */
    static CardView* create(const CardModel* cardModel, const CardClickCallback& callback);

    /**
     * @brief 初始化卡牌视图
     * @param cardModel 卡牌数据模型（const指针）
     * @param callback 点击回调函数
     * @return 初始化成功返回true
     */
    bool init(const CardModel* cardModel, const CardClickCallback& callback);

    /**
     * @brief 获取卡牌ID
     * @return 卡牌ID
     */
    int getCardId() const { return _cardId; }

    /**
     * @brief 播放移动动画
     * @param targetPos 目标位置
     * @param duration 动画时长
     * @param callback 动画完成回调
     */
    void playMoveAnimation(const cocos2d::Vec2& targetPos, float duration, const std::function<void()>& callback = nullptr);

    /**
     * @brief 设置卡牌是否可点击
     * @param enabled 是否可点击
     */
    void setClickEnabled(bool enabled);

private:
    /**
     * @brief 设置触摸事件监听
     */
    void setupTouchListener();

    /**
     * @brief 创建卡牌UI
     */
    void createCardUI();

private:
    const CardModel* _cardModel;        // 卡牌数据模型（const指针）
    int _cardId;                        // 卡牌ID
    CardClickCallback _clickCallback;   // 点击回调函数
    cocos2d::Sprite* _cardSprite;       // 卡牌背景精灵
    cocos2d::EventListenerTouchOneByOne* _touchListener;  // 触摸监听器

    static const float kCardWidth;      // 卡牌宽度
    static const float kCardHeight;     // 卡牌高度
};

#endif // __CARD_VIEW_H__
