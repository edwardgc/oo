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
#include <vector>

#include "BoardPort.hpp"
#include "BoardPortFactory.hpp"

namespace SharpNose
{

class T_PpContext;
class PortTabMgnt;

class IBoardPlane
{
public:
    virtual bool init() = 0;
    virtual ActionResult send(T_PpContext &ctxt) = 0;
    virtual ActionResult receive(const uint8_t *pkt, size_t pktLen) = 0;
    virtual ~IBoardPlane() = default;
};

class IUserPlane : public IBoardPlane
{
public:
    virtual bool fillEgressInfo(T_PpContext &ctxt) = 0;
    virtual bool fillUsPort(T_PpContext &ctxt) = 0;
};

class PonUserPlane : public IUserPlane
{
public:
    PonUserPlane(const std::shared_ptr<IBoardPortFactory> &boardPortFactory, bool supportNgpon2);
    bool init() override;
    ActionResult send(T_PpContext &ctxt) override;
    ActionResult receive(const uint8_t *pkt, size_t pktLen) override;
    bool fillEgressInfo(T_PpContext &ctxt) override;
    bool fillUsPort(T_PpContext &ctxt) override;

private:
    void (*m_usPortHandler)(T_PpContext &ctxt);
    void (*m_gemportHandler)(T_PpContext &ctxt);
    std::shared_ptr<IBoardPortFactory> m_portFactory;
    std::shared_ptr<IBoardPort> m_socketPort;
};

class EthUserPlane : public IUserPlane
{
public:
    EthUserPlane(const std::shared_ptr<IBoardPortFactory> &portFactory,
                 PortTabMgnt &portTabMgnt);
    bool init() override;
    ActionResult send(T_PpContext &ctxt) override;
    ActionResult receive(const uint8_t *pkt, size_t pktLen) override;
    bool fillEgressInfo(T_PpContext &ctxt) override;
    bool fillUsPort(T_PpContext &ctxt) override;

private:
    std::shared_ptr<IBoardPortFactory> m_portFactory;
    PortTabMgnt &m_portTabMgnt;
    std::vector<std::shared_ptr<IBoardPort>> m_socketPorts;
    std::vector<std::shared_ptr<IBoardPort>> m_pcapPorts;
};

}
