#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include "cocos2d.h"

/**
 * @brief 撤销操作类型枚举
 */
enum UndoActionType
{
    UAT_NONE = 0,
    UAT_PLAYFIELD_TO_TRAY,  // 主牌区卡牌移动到底牌
    UAT_STACK_TO_TRAY,      // 备用牌堆卡牌移动到底牌
};

/**
 * @brief 撤销操作数据模型
 * 记录一次操作的所有必要信息，用于撤销该操作
 */
class UndoModel
{
public:
    UndoModel();
    UndoModel(UndoActionType type, int cardId, int previousTrayCardId, const cocos2d::Vec2& originalPos);
    ~UndoModel();

    /**
     * @brief 获取撤销操作类型
     * @return 操作类型
     */
    UndoActionType getActionType() const { return _actionType; }

    /**
     * @brief 获取移动的卡牌ID
     * @return 卡牌ID
     */
    int getCardId() const { return _cardId; }

    /**
     * @brief 获取之前的底牌ID
     * @return 之前底牌的ID
     */
    int getPreviousTrayCardId() const { return _previousTrayCardId; }

    /**
     * @brief 获取卡牌原始位置
     * @return 原始位置坐标
     */
    const cocos2d::Vec2& getOriginalPosition() const { return _originalPosition; }

    /**
     * @brief 设置撤销操作类型
     * @param type 操作类型
     */
    void setActionType(UndoActionType type) { _actionType = type; }

    /**
     * @brief 设置移动的卡牌ID
     * @param cardId 卡牌ID
     */
    void setCardId(int cardId) { _cardId = cardId; }

    /**
     * @brief 设置之前的底牌ID
     * @param cardId 之前底牌的ID
     */
    void setPreviousTrayCardId(int cardId) { _previousTrayCardId = cardId; }

    /**
     * @brief 设置卡牌原始位置
     * @param position 原始位置坐标
     */
    void setOriginalPosition(const cocos2d::Vec2& position) { _originalPosition = position; }

private:
    UndoActionType _actionType;         // 操作类型
    int _cardId;                        // 移动的卡牌ID
    int _previousTrayCardId;            // 之前的底牌ID
    cocos2d::Vec2 _originalPosition;    // 卡牌原始位置
};

#endif // __UNDO_MODEL_H__
