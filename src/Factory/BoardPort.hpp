/**
 * Copyright (c) 2020 Nokia. All rights reserved.
 * This program contains proprietary information which is a trade secret
 * of Nokia and also is protected as an unpublished work under applicable
 * Copyright laws. Recipient is to retain this program in confidence and
 * is not permitted to use or make copies thereof other than as permitted
 * in a written agreement with Nokia.
 */

#pragma once

#include <string>

namespace SharpNose
{

using ActionResult = bool;
constexpr size_t HEAD_ROOM_SIZE = 256;

class IBoardPort
{
public:
    virtual ~IBoardPort() = default;
    virtual bool valid() = 0;
    virtual ActionResult send(uint8_t *pkt, size_t pktLen) = 0;
    virtual ActionResult receive(const uint8_t *pkt, size_t pktLen) = 0;
    virtual void listen() = 0;
};

void* listenProxy(void *listener);

class PcapPort : public IBoardPort
{
public:
    PcapPort(const std::string &eth, const std::shared_ptr<IBoardPort>& socketPort);
    ~PcapPort();
    bool valid() override;
    ActionResult send(uint8_t *pkt, size_t pktLen) override;
    ActionResult receive(const uint8_t *pkt, size_t pktLen) override;
    void listen() override;
private:
    ActionResult startListen();
    std::string m_eth;
    bool m_valid;
    std::shared_ptr<IBoardPort> m_socketPort;
};

class IReceiveHandler
{
public:
    virtual ~IReceiveHandler() = default;
    virtual ActionResult handle(uint8_t*, size_t) = 0;
};

class SocketPort : public IBoardPort
{
public:
    SocketPort(const std::string &socketPath, const std::shared_ptr<IReceiveHandler> &receiveHandler);
    SocketPort(const std::string &socketPath, const std::string &peerSocketPath, const std::shared_ptr<IReceiveHandler> &receiveHandler);
    ~SocketPort();
    bool valid() override;
    ActionResult send(uint8_t *pkt, size_t pktLen) override;
    ActionResult receive(const uint8_t *pkt, size_t pktLen) override;
    void listen() override;

private:
    void init();
    ActionResult startListen();
    std::string m_socketPath;
    std::string m_peerSocketPath;
    bool m_valid;
    std::shared_ptr<IReceiveHandler> m_receiveHandler;
    int m_fd;
};

} //namespace SharpNose
