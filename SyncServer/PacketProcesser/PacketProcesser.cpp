#include "PacketProcesser.hpp"

PacketProcesser::PacketProcesser()
{
    _packetFuncMap[(int)PacketId::CharaterStatReqId] = std::bind(&PacketProcesser::CharacterStatusFunc, this, std::placeholders::_1, std::placeholders::_2);
    _packetFuncMap[(int)PacketId::ChatchReqId] = std::bind(&PacketProcesser::CatchFunc, this, std::placeholders::_1, std::placeholders::_2);
}

void PacketProcesser::StartStatusLogging()
{
    _userManager.DoLogging();
}

void PacketProcesser::StopStatusLogging()
{
    _userManager.StopLogging();
}

void PacketProcesser::Process(BuffVec* buffVec, Session* session)
{
    int packetId = *(reinterpret_cast<int*>(buffVec->data()));
    std::map<int, std::function<void(BuffVec*, Session*)>>::iterator finded = _packetFuncMap.find(packetId);
    if (finded == _packetFuncMap.end())
    {
        std::cerr << "Wrong PacketId in" << std::endl;
        return ;
    }
    finded->second(buffVec, session);
}

void PacketProcesser::CharacterStatusFunc(BuffVec* buffVec, Session* session)
{
    CharaterStatReq req;
    req.Deserialize(buffVec, sizeof(req));

    UserStatus userStatus(req.locX, req.locY, req.velX, req.velY, req.ttsThis, req.ttsOther);
    _userManager.ReserveStatus(userStatus);
    
    CharaterStatRes res(req.locX, req.locY, req.velX, req.velY, req.ttsThis, req.ttsOther);
    session->send(res.Serialize(), sizeof(res));
}

void PacketProcesser::CatchFunc(BuffVec* buffVec, Session* session)
{
    // Todo
}