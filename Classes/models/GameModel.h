#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include "CardModel.h"
#include <vector>
#include <map>

/**
 * @brief 游戏数据模型
 * 存储整个游戏的运行时数据，包括主牌区、底牌堆和备用牌堆的卡牌数据
 */
class GameModel
{
public:
    GameModel();
    ~GameModel();

    /**
     * @brief 获取主牌区的所有卡牌
     * @return 主牌区卡牌列表的引用
     */
    std::vector<CardModel*>& getPlayfieldCards() { return _playfieldCards; }
    const std::vector<CardModel*>& getPlayfieldCards() const { return _playfieldCards; }

    /**
     * @brief 获取备用牌堆的所有卡牌
     * @return 备用牌堆卡牌列表的引用
     */
    std::vector<CardModel*>& getStackCards() { return _stackCards; }
    const std::vector<CardModel*>& getStackCards() const { return _stackCards; }

    /**
     * @brief 获取底牌
     * @return 底牌指针，如果没有底牌返回nullptr
     */
    CardModel* getTrayCard() const { return _trayCard; }

    /**
     * @brief 设置底牌
     * @param card 底牌指针
     */
    void setTrayCard(CardModel* card) { _trayCard = card; }

    /**
     * @brief 根据ID查找卡牌
     * @param cardId 卡牌ID
     * @return 卡牌指针，找不到返回nullptr
     */
    CardModel* findCardById(int cardId) const;

    /**
     * @brief 从主牌区移除卡牌
     * @param card 要移除的卡牌指针
     * @return 移除成功返回true
     */
    bool removePlayfieldCard(CardModel* card);

    /**
     * @brief 从备用牌堆移除卡牌
     * @param card 要移除的卡牌指针
     * @return 移除成功返回true
     */
    bool removeStackCard(CardModel* card);

    /**
     * @brief 添加卡牌到主牌区
     * @param card 要添加的卡牌指针
     */
    void addPlayfieldCard(CardModel* card);

    /**
     * @brief 添加卡牌到备用牌堆
     * @param card 要添加的卡牌指针
     */
    void addStackCard(CardModel* card);

    /**
     * @brief 清空所有数据
     */
    void clear();

private:
    std::vector<CardModel*> _playfieldCards;  // 主牌区卡牌列表
    std::vector<CardModel*> _stackCards;      // 备用牌堆卡牌列表
    CardModel* _trayCard;                     // 底牌
    std::map<int, CardModel*> _cardMap;       // 卡牌ID到卡牌的映射表，用于快速查找
};

#endif // __GAME_MODEL_H__
