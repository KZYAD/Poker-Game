#include "LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"

USING_NS_CC;

LevelConfig* LevelConfigLoader::loadLevelConfig(int levelId)
{
    std::string path = getLevelConfigPath(levelId);
    std::string content = FileUtils::getInstance()->getStringFromFile(path);

    if (content.empty())
    {
        CCLOG("Failed to load level config: %s", path.c_str());
        return nullptr;
    }

    return parseLevelConfig(content);
}

LevelConfig* LevelConfigLoader::parseLevelConfig(const std::string& jsonStr)
{
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    if (doc.HasParseError())
    {
        CCLOG("Failed to parse level config JSON");
        return nullptr;
    }

    LevelConfig* config = new LevelConfig();

    // 解析主牌区卡牌
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value& playfield = doc["Playfield"];
        std::vector<CardConfigData> playfieldCards;

        for (rapidjson::SizeType i = 0; i < playfield.Size(); i++)
        {
            const rapidjson::Value& card = playfield[i];
            CardConfigData data;

            if (card.HasMember("CardFace") && card["CardFace"].IsInt())
                data.cardFace = card["CardFace"].GetInt();

            if (card.HasMember("CardSuit") && card["CardSuit"].IsInt())
                data.cardSuit = card["CardSuit"].GetInt();

            if (card.HasMember("Position") && card["Position"].IsObject())
            {
                const rapidjson::Value& pos = card["Position"];
                if (pos.HasMember("x") && pos.HasMember("y"))
                {
                    data.position.x = pos["x"].GetFloat();
                    data.position.y = pos["y"].GetFloat();
                }
            }

            if (card.HasMember("ZOrder") && card["ZOrder"].IsInt())
                data.zOrder = card["ZOrder"].GetInt();

            if (card.HasMember("IsFaceUp") && card["IsFaceUp"].IsBool())
                data.isFaceUp = card["IsFaceUp"].GetBool();

            playfieldCards.push_back(data);
        }

        config->setPlayfieldCards(playfieldCards);
    }

    // 解析备用牌堆
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value& stack = doc["Stack"];
        std::vector<CardConfigData> stackCards;

        for (rapidjson::SizeType i = 0; i < stack.Size(); i++)
        {
            const rapidjson::Value& card = stack[i];
            CardConfigData data;

            if (card.HasMember("CardFace") && card["CardFace"].IsInt())
                data.cardFace = card["CardFace"].GetInt();

            if (card.HasMember("CardSuit") && card["CardSuit"].IsInt())
                data.cardSuit = card["CardSuit"].GetInt();

            if (card.HasMember("Position") && card["Position"].IsObject())
            {
                const rapidjson::Value& pos = card["Position"];
                if (pos.HasMember("x") && pos.HasMember("y"))
                {
                    data.position.x = pos["x"].GetFloat();
                    data.position.y = pos["y"].GetFloat();
                }
            }

            stackCards.push_back(data);
        }

        config->setStackCards(stackCards);
    }

    // 解析关卡奖励金币
    if (doc.HasMember("CoinReward") && doc["CoinReward"].IsInt())
    {
        config->setCoinReward(doc["CoinReward"].GetInt());
    }

    return config;
}

bool LevelConfigLoader::levelExists(int levelId)
{
    std::string path = getLevelConfigPath(levelId);
    return FileUtils::getInstance()->isFileExist(path);
}

std::string LevelConfigLoader::getLevelConfigPath(int levelId)
{
    char path[128];
    sprintf(path, "levels/level_%d.json", levelId);
    return path;
}
