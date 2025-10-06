#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"

class GameModel;
class GameView;
class LevelConfig;
class UndoManager;

/**
 * @brief 游戏控制器
 * 负责协调Model和View，处理游戏核心逻辑
 * 包括卡牌匹配、撤销操作等
 */
class GameController
{
public:
    GameController();
    ~GameController();

    /**
     * @brief 开始游戏
     * @param levelId 关卡ID
     * @param parentNode 父节点，用于添加游戏视图
     * @return 启动成功返回true
     */
    bool startGame(int levelId, cocos2d::Node* parentNode);

    /**
     * @brief 处理主牌区卡牌点击
     * @param cardId 点击的卡牌ID
     */
    void handlePlayfieldCardClick(int cardId);

    /**
     * @brief 处理备用牌堆卡牌点击
     * @param cardId 点击的卡牌ID
     */
    void handleStackCardClick(int cardId);

    /**
     * @brief 处理撤销按钮点击
     */
    void handleUndoClick();

private:
    /**
     * @brief 初始化游戏数据
     * @param levelConfig 关卡配置
     * @return 初始化成功返回true
     */
    bool initGameData(const LevelConfig* levelConfig);

    /**
     * @brief 初始化游戏视图
     * @param parentNode 父节点
     */
    void initGameView(cocos2d::Node* parentNode);

    /**
     * @brief 执行主牌区卡牌移动到底牌
     * @param cardId 卡牌ID
     */
    void movePlayfieldCardToTray(int cardId);

    /**
     * @brief 执行备用牌堆卡牌移动到底牌
     * @param cardId 卡牌ID
     */
    void moveStackCardToTray(int cardId);

    /**
     * @brief 执行撤销操作
     * @param cardId 要撤销的卡牌ID
     * @param previousTrayCardId 之前的底牌ID
     * @param originalPos 原始位置
     * @param isFromStack 是否来自备用牌堆
     */
    void executeUndo(int cardId, int previousTrayCardId,
                    const cocos2d::Vec2& originalPos, bool isFromStack);

private:
    GameModel* _gameModel;          // 游戏数据模型
    GameView* _gameView;            // 游戏视图
    UndoManager* _undoManager;      // 撤销管理器
};

#endif // __GAME_CONTROLLER_H__
