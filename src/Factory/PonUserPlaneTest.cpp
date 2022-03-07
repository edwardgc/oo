/**
 * Copyright (c) 2020 Nokia. All rights reserved.
 * This program contains proprietary information which is a trade secret
 * of Nokia and also is protected as an unpublished work under applicable
 * Copyright laws. Recipient is to retain this program in confidence and
 * is not permitted to use or make copies thereof other than as permitted
 * in a written agreement with Nokia.
 */

#include <gtest/gtest.h>

#include "BoardPortFactoryMock.hpp"
#include "BoardPortMock.hpp"
#include "BoardPlane.hpp"

using namespace testing;
using std::make_shared;
using std::shared_ptr;

namespace
{

constexpr size_t PKT_LEN = 10;
constexpr int GEMPORT = 6;
constexpr int PON_ID = 9;
}

namespace SharpNose
{


class PonUserPlaneTest : public Test
{
public:
    PonUserPlaneTest()
            : m_socketPort(make_shared<BoardPortMock>()),
              m_portFactory(make_shared<BoardPortFactoryMock>()),
              m_plane(m_portFactory, false),
              m_ctx(),
              m_rxPktPassivelyOrg()
    {
        EXPECT_CALL(*m_portFactory, createSocketPort(_, _, _)).WillOnce(Return(m_socketPort));
        EXPECT_CALL(*m_socketPort, valid()).WillOnce(Return(true));
        m_plane.init();
    }

private:
    shared_ptr<BoardPortMock> m_socketPort;
    shared_ptr<BoardPortFactoryMock> m_portFactory;
    PonUserPlane m_plane;
    T_PpContext m_ctx;
    uint8_t pkt[PKT_LEN];
    bool m_rxPktPassivelyOrg;
};

TEST_F(PonUserPlaneTest, shouldCallPcapSendWhenSendPackage)
{
    EXPECT_CALL(*m_socketPort, send(pkt, PKT_LEN)).WillOnce(Return(true));
    m_plane.send(m_ctx);
}

TEST_F(PonUserPlaneTest, shouldCallSstSendWhenSstOn)
{
    EXPECT_CALL(*m_socketPort, send(pkt, PKT_LEN)).Times(0);
    m_plane.send(m_ctx);
}

TEST_F(PonUserPlaneTest, shouldCallSocketReceiveWhenReceivePackage)
{
    EXPECT_CALL(*m_socketPort, receive(pkt, PKT_LEN)).WillOnce(Return(true));
    m_plane.receive(pkt, PKT_LEN);
}

TEST_F(PonUserPlaneTest, validateGemportFailWhenZero)
{
    ASSERT_FALSE(m_plane.fillEgressInfo(m_ctx));
}

} //namespace SharpNose

