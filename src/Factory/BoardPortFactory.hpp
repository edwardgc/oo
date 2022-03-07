/**
 * Copyright (c) 2020 Nokia. All rights reserved.
 * This program contains proprietary information which is a trade secret
 * of Nokia and also is protected as an unpublished work under applicable
 * Copyright laws. Recipient is to retain this program in confidence and
 * is not permitted to use or make copies thereof other than as permitted
 * in a written agreement with Nokia.
 */

#pragma once

#include <memory>

#include "BoardPort.hpp"

namespace SharpNose
{

class IBoardPortFactory
{
public:
    virtual std::shared_ptr<IBoardPort> createPcapPort(const std::string &eth, const std::shared_ptr<IBoardPort>& socketPort) = 0;
    virtual std::shared_ptr<IBoardPort> createSocketPort(const std::string &socketPath, const std::string &peerSocketPath,
                                                         const std::shared_ptr<IReceiveHandler> &receiveHandler) = 0;
    virtual std::shared_ptr<IBoardPort> createSocketPort(const std::string &socketPath, const std::shared_ptr<IReceiveHandler> &receiveHandler) = 0;
    virtual ~IBoardPortFactory() = default;
};

class BoardPortFactory : public IBoardPortFactory
{
public:
    BoardPortFactory() = default;
    std::shared_ptr<IBoardPort> createPcapPort(const std::string &eth, const std::shared_ptr<IBoardPort>& socketPort) override;
    std::shared_ptr<IBoardPort> createSocketPort(const std::string &socketPath, const std::string &peerSocketPath,
                                                 const std::shared_ptr<IReceiveHandler> &receiveHandler) override;
    std::shared_ptr<IBoardPort> createSocketPort(const std::string &socketPath, const std::shared_ptr<IReceiveHandler> &receiveHandler) override;

};

} //namespace SharpNose
