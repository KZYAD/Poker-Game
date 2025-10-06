#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include <vector>
#include "cocos2d.h"

/**
 * @brief 关卡配置中的卡牌数据
 * 包含卡牌的花色、点数、位置和层级信息
 */
struct CardConfigData
{
    int cardFace;               // 牌面点数 (0-A, 1-2, ..., 12-K)
    int cardSuit;               // 花色 (0-梅花, 1-方块, 2-红桃, 3-黑桃)
    cocos2d::Vec2 position;     // 卡牌位置
    int zOrder;                 // Z轴层级(数值越大越在上层)
    std::vector<int> blockedBy; // 被哪些卡牌遮挡(存储卡牌索引)
    bool isFaceUp;              // 是否翻开显示(true:翻开, false:背面)

    CardConfigData() : cardFace(0), cardSuit(0), zOrder(0), isFaceUp(true) {}
};

/**
 * @brief 关卡配置类
 * 包含一个关卡的所有静态配置信息
 */
class LevelConfig
{
public:
    LevelConfig();
    ~LevelConfig();

    /**
     * @brief 获取主牌区的卡牌配置列表
     * @return 主牌区卡牌配置的引用
     */
    const std::vector<CardConfigData>& getPlayfieldCards() const { return _playfieldCards; }

    /**
     * @brief 获取备用牌堆的卡牌配置列表
     * @return 备用牌堆卡牌配置的引用
     */
    const std::vector<CardConfigData>& getStackCards() const { return _stackCards; }

    /**
     * @brief 设置主牌区的卡牌配置列表
     * @param cards 卡牌配置列表
     */
    void setPlayfieldCards(const std::vector<CardConfigData>& cards) { _playfieldCards = cards; }

    /**
     * @brief 设置备用牌堆的卡牌配置列表
     * @param cards 卡牌配置列表
     */
    void setStackCards(const std::vector<CardConfigData>& cards) { _stackCards = cards; }

    /**
     * @brief 获取/设置关卡奖励金币
     */
    int getCoinReward() const { return _coinReward; }
    void setCoinReward(int reward) { _coinReward = reward; }

private:
    std::vector<CardConfigData> _playfieldCards;  // 主牌区卡牌列表
    std::vector<CardConfigData> _stackCards;       // 备用牌堆卡牌列表
    int _coinReward;                               // 通关奖励金币
};

#endif // __LEVEL_CONFIG_H__
