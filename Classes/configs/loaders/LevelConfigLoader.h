#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

#include "../models/LevelConfig.h"
#include <string>

/**
 * @brief 关卡配置加载器
 * 负责从JSON文件加载关卡配置数据
 */
class LevelConfigLoader
{
public:
    /**
     * @brief 从JSON文件加载关卡配置
     * @param levelId 关卡ID
     * @return 关卡配置对象指针，失败返回nullptr
     */
    static LevelConfig* loadLevelConfig(int levelId);

    /**
     * @brief 从JSON字符串解析关卡配置
     * @param jsonStr JSON字符串
     * @return 关卡配置对象指针，失败返回nullptr
     */
    static LevelConfig* parseLevelConfig(const std::string& jsonStr);

    /**
     * @brief 检查关卡配置文件是否存在
     * @param levelId 关卡ID
     * @return 存在返回true，否则返回false
     */
    static bool levelExists(int levelId);

private:
    /**
     * @brief 获取关卡配置文件路径
     * @param levelId 关卡ID
     * @return 配置文件路径
     */
    static std::string getLevelConfigPath(int levelId);
};

#endif // __LEVEL_CONFIG_LOADER_H__
