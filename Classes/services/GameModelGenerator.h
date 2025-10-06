#ifndef __GAME_MODEL_GENERATOR_H__
#define __GAME_MODEL_GENERATOR_H__

class LevelConfig;
class GameModel;

/**
 * @brief 游戏数据生成服务
 * 负责将静态配置（LevelConfig）转换为运行时动态数据（GameModel）
 * 这是一个无状态的服务类，不持有数据，通过参数操作或返回数据
 */
class GameModelGenerator
{
public:
    /**
     * @brief 从关卡配置生成游戏数据模型
     * @param levelConfig 关卡配置对象
     * @return 生成的游戏数据模型，失败返回nullptr
     * @note 调用方负责释放返回的GameModel对象
     */
    static GameModel* generateFromLevelConfig(const LevelConfig* levelConfig);

private:
    /**
     * @brief 生成唯一的卡牌ID
     * @return 新的卡牌ID
     */
    static int generateCardId();

    static int s_nextCardId;  // 下一个可用的卡牌ID
};

#endif // __GAME_MODEL_GENERATOR_H__
