#pragma once

#include "../pch.hpp"

enum PacketId
{
    CharaterStatReqId = 1,
    CharaterStatResId = 2,
    ChatchReqId = 3,
    ChatchResId = 4
};

class PacketBase
{
public:
    int packetId;

    BuffVec Serialize()
    {
        BuffVec rt;
        int offset = 0;
        std::memcpy(rt.data() + offset, &packetId, sizeof(packetId));
        offset += sizeof(packetId);
        
        return std::move(rt);
    }

    int Deserialize(std::array<char, MAX_BUF_SIZE>* data, int dataSize)
    {
        int offset = 0;
        std::memcpy(&packetId, data->data() + offset, sizeof(PacketBase::packetId));
        offset += sizeof(PacketBase::packetId);
        return offset;
    }
};

class CharaterStatReq : PacketBase
{
public:
    float locX;
    float locY;
    float velX;
    float velY;
    float sendReqCliTime;
    float ttsThis;
    float ttsOther;

    int Deserialize(std::array<char, MAX_BUF_SIZE>* data, int dataSize)
    {
        if (dataSize != sizeof(CharaterStatReq))
        {
            std::cerr << "CharaterStatReq worng size in" << std::endl;
        }
        int offset = this->PacketBase::Deserialize(data, dataSize);
        
        std::memcpy(&locX, data->data() + offset, sizeof(CharaterStatReq::locX));
        offset += sizeof(CharaterStatReq::locX);
        std::memcpy(&locY, data->data() + offset, sizeof(CharaterStatReq::locY));
        offset += sizeof(CharaterStatReq::locY);
        std::memcpy(&velX, data->data() + offset, sizeof(CharaterStatReq::velX));
        offset += sizeof(CharaterStatReq::velX);
        std::memcpy(&velY, data->data() + offset, sizeof(CharaterStatReq::velY));
        offset += sizeof(CharaterStatReq::velY);
        std::memcpy(&sendReqCliTime, data->data() + offset, sizeof(CharaterStatReq::sendReqCliTime));
        offset += sizeof(CharaterStatReq::sendReqCliTime);
        std::memcpy(&ttsThis, data->data() + offset, sizeof(CharaterStatReq::ttsThis));
        offset += sizeof(CharaterStatReq::ttsThis);
        std::memcpy(&ttsOther, data->data() + offset, sizeof(CharaterStatReq::ttsOther));
        offset += sizeof(CharaterStatReq::ttsOther);

        return offset;
    }
};

class CharaterStatRes : PacketBase
{
public:
    float locX;
    float locY;
    float velX;
    float velY;
    float ttsThis;
    float ttsOther;

    CharaterStatRes(float inputLocX, float inputLocY, float inputVelX, float inputVelY, float inputTtsThis, float inputTtsOther)
    : locX(inputLocX), locY(inputLocY), velX(inputVelX), velY(inputVelY), ttsThis(inputTtsThis),  ttsOther(inputTtsOther)
    {
        PacketBase::packetId = PacketId::CharaterStatResId;
    }

    BuffVec Serialize()
    {
        BuffVec rt = this->PacketBase::Serialize();
        int offset = sizeof(PacketBase);
        std::memcpy(rt.data() + offset, &locX, sizeof(locX));
        offset += sizeof(locX);
        std::memcpy(rt.data() + offset, &locY, sizeof(locY));
        offset += sizeof(locY);
        std::memcpy(rt.data() + offset, &velX, sizeof(velX));
        offset += sizeof(velX);
        std::memcpy(rt.data() + offset, &velY, sizeof(velY));
        offset += sizeof(velY);
        std::memcpy(rt.data() + offset, &ttsThis, sizeof(ttsThis));
        offset += sizeof(ttsThis);
        std::memcpy(rt.data() + offset, &ttsOther, sizeof(ttsOther));
        offset += sizeof(ttsOther);
        
        return std::move(rt);
    }
};