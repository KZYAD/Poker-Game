#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__

#include <string>

/**
 * @brief 卡牌资源配置类
 * 负责管理卡牌显示所需的图片资源路径
 */
class CardResConfig
{
public:
    /**
     * @brief 获取卡牌背面图片路径
     * @return 卡牌背面图片的资源路径
     */
    static std::string getCardBackPath();

    /**
     * @brief 获取卡牌正面花色图片路径
     * @param suit 花色类型 (0-梅花, 1-方块, 2-红桃, 3-黑桃)
     * @return 花色图片的资源路径
     */
    static std::string getCardSuitPath(int suit);

    /**
     * @brief 获取卡牌大数字图片路径
     * @param face 牌面数字 (0-A, 1-2, ..., 12-K)
     * @param isRed 是否为红色花色
     * @return 大数字图片的资源路径
     */
    static std::string getCardBigNumberPath(int face, bool isRed);

    /**
     * @brief 获取卡牌小数字图片路径
     * @param face 牌面数字 (0-A, 1-2, ..., 12-K)
     * @param isRed 是否为红色花色
     * @return 小数字图片的资源路径
     */
    static std::string getCardSmallNumberPath(int face, bool isRed);
};

#endif // __CARD_RES_CONFIG_H__
