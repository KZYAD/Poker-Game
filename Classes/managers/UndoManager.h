#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include "../models/UndoModel.h"
#include <vector>
#include <functional>

/**
 * @brief 撤销管理器
 * 作为Controller的成员变量，负责管理撤销操作的历史记录
 * 持有UndoModel数据并提供撤销/重做功能
 */
class UndoManager
{
public:
    UndoManager();
    ~UndoManager();

    /**
     * @brief 添加一条撤销记录
     * @param undoModel 撤销数据模型
     */
    void addUndo(const UndoModel& undoModel);

    /**
     * @brief 执行撤销操作
     * @param outModel 输出参数，保存撤销的操作数据
     * @return 有可撤销操作返回true，否则返回false
     */
    bool popUndo(UndoModel& outModel);

    /**
     * @brief 判断是否有可撤销的操作
     * @return 有可撤销操作返回true
     */
    bool canUndo() const;

    /**
     * @brief 获取撤销历史记录数量
     * @return 撤销历史记录的数量
     */
    int getUndoCount() const;

    /**
     * @brief 清空所有撤销记录
     */
    void clear();

private:
    std::vector<UndoModel> _undoStack;  // 撤销操作栈
};

#endif // __UNDO_MANAGER_H__
