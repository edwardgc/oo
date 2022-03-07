/**
 * Copyright (c) 2020 Nokia. All rights reserved.
 * This program contains proprietary information which is a trade secret
 * of Nokia and also is protected as an unpublished work under applicable
 * Copyright laws. Recipient is to retain this program in confidence and
 * is not permitted to use or make copies thereof other than as permitted
 * in a written agreement with Nokia.
 */

#pragma once

#include <gmock/gmock.h>

#include "BoardPort.hpp"

namespace SharpNose
{

class BoardPortMock : public IBoardPort
{
public:
    MOCK_METHOD0(valid, bool());
    MOCK_METHOD2(send, ActionResult(uint8_t*, size_t));
    MOCK_METHOD2(receive, ActionResult(const uint8_t*, size_t));
    MOCK_METHOD0(listen, void());
};

} //namespace SharpNose
