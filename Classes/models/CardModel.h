#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "cocos2d.h"

// 花色类型
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 正面类型
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

/**
 * @brief 卡牌数据模型
 * 存储单张卡牌的运行时数据，包括ID、花色、点数和位置
 */
class CardModel
{
public:
    CardModel();
    CardModel(int id, CardFaceType face, CardSuitType suit);
    ~CardModel();

    /**
     * @brief 获取卡牌ID
     * @return 卡牌的唯一标识ID
     */
    int getId() const { return _id; }

    /**
     * @brief 获取卡牌点数
     * @return 卡牌点数类型
     */
    CardFaceType getFace() const { return _face; }

    /**
     * @brief 获取卡牌花色
     * @return 卡牌花色类型
     */
    CardSuitType getSuit() const { return _suit; }

    /**
     * @brief 获取卡牌位置
     * @return 卡牌当前位置
     */
    const cocos2d::Vec2& getPosition() const { return _position; }

    /**
     * @brief 设置卡牌ID
     * @param id 卡牌唯一标识ID
     */
    void setId(int id) { _id = id; }

    /**
     * @brief 设置卡牌点数
     * @param face 卡牌点数类型
     */
    void setFace(CardFaceType face) { _face = face; }

    /**
     * @brief 设置卡牌花色
     * @param suit 卡牌花色类型
     */
    void setSuit(CardSuitType suit) { _suit = suit; }

    /**
     * @brief 设置卡牌位置
     * @param position 卡牌位置
     */
    void setPosition(const cocos2d::Vec2& position) { _position = position; }

    /**
     * @brief 判断花色是否为红色
     * @return 如果是红桃或方块返回true，否则返回false
     */
    bool isRed() const;

    /**
     * @brief 获取卡牌点数的数值
     * @return 点数数值 (A=1, 2-10=2-10, J=11, Q=12, K=13)
     */
    int getFaceValue() const;

    /**
     * @brief 设置/获取卡牌是否翻开
     */
    bool isFaceUp() const { return _isFaceUp; }
    void setFaceUp(bool faceUp) { _isFaceUp = faceUp; }

    /**
     * @brief 设置/获取卡牌是否被遮挡
     * 被遮挡的卡牌不能点击
     */
    bool isBlocked() const { return _isBlocked; }
    void setBlocked(bool blocked) { _isBlocked = blocked; }

    /**
     * @brief 设置/获取Z轴层级
     */
    int getZOrder() const { return _zOrder; }
    void setZOrder(int zOrder) { _zOrder = zOrder; }

private:
    int _id;                    // 卡牌唯一ID
    CardFaceType _face;         // 卡牌点数
    CardSuitType _suit;         // 卡牌花色
    cocos2d::Vec2 _position;    // 卡牌位置
    bool _isFaceUp;             // 是否翻开
    bool _isBlocked;            // 是否被其他牌遮挡
    int _zOrder;                // Z轴层级
};

#endif // __CARD_MODEL_H__
