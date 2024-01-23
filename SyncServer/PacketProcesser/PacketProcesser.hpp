#pragma once

#include "../pch.hpp"
#include "../Packet/Packet.hpp"
#include "../UserManager/UserManager.hpp"
#include "../Session/Session.hpp"

class PacketProcesser
{
public:
    PacketProcesser();
    
    void Process(BuffVec* buffVec, Session* session);
    void StartStatusLogging();
    void StopStatusLogging();
private:
    using FuncType = std::function<void(BuffVec*, Session*)>;
    UserManager _userManager;
    std::map<int, FuncType> _packetFuncMap;
    void CharacterStatusFunc(BuffVec* buffVec, Session* session);
    void CatchFunc(BuffVec* buffVec, Session* session);
};