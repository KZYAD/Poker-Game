#include "UndoManager.h"

UndoManager::UndoManager()
{
}

UndoManager::~UndoManager()
{
}

void UndoManager::addUndo(const UndoModel& undoModel)
{
    _undoStack.push_back(undoModel);
}

bool UndoManager::popUndo(UndoModel& outModel)
{
    if (_undoStack.empty())
    {
        return false;
    }

    // 拷贝栈顶元素并弹出
    outModel = _undoStack.back();
    _undoStack.pop_back();
    return true;
}

bool UndoManager::canUndo() const
{
    return !_undoStack.empty();
}

int UndoManager::getUndoCount() const
{
    return static_cast<int>(_undoStack.size());
}

void UndoManager::clear()
{
    _undoStack.clear();
}
