#ifndef __CARD_MATCH_UTILS_H__
#define __CARD_MATCH_UTILS_H__

class CardModel;

/**
 * @brief 卡牌匹配工具类
 * 提供卡牌匹配规则的判断逻辑
 */
class CardMatchUtils
{
public:
    /**
     * @brief 判断两张卡牌是否可以匹配消除
     * 匹配规则：卡牌点数差值为1（无花色限制）
     * 例如：7可以和6或8匹配，A可以和2或K匹配
     *
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 可以匹配返回true，否则返回false
     */
    static bool canMatch(const CardModel* card1, const CardModel* card2);

    /**
     * @brief 判断卡牌是否可以和底牌匹配
     * @param card 要判断的卡牌
     * @param trayCard 底牌
     * @return 可以匹配返回true，否则返回false
     */
    static bool canMatchWithTray(const CardModel* card, const CardModel* trayCard);

private:
    /**
     * @brief 获取两个点数之间的差值（考虑A和K的循环）
     * @param face1 第一张卡牌的点数值
     * @param face2 第二张卡牌的点数值
     * @return 点数差值的绝对值
     */
    static int getFaceDifference(int face1, int face2);
};

#endif // __CARD_MATCH_UTILS_H__
