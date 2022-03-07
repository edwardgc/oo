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

#include "BoardPortFactory.hpp"

namespace SharpNose
{

class BoardPortFactoryMock : public IBoardPortFactory
{
public:
    MOCK_METHOD2(createPcapPort, std::shared_ptr<IBoardPort>(const std::string&, const std::shared_ptr<IBoardPort>&));
    MOCK_METHOD3(createSocketPort, std::shared_ptr<IBoardPort>(const std::string&, const std::string&, const std::shared_ptr<IReceiveHandler>&));
    MOCK_METHOD2(createSocketPort, std::shared_ptr<IBoardPort>(const std::string&, const std::shared_ptr<IReceiveHandler>&));
};

} //namespace SharpNose
