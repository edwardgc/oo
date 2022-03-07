/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_CELLC/SS_CellcServices/CP_CellcSystemInformationBroadcastManagement/Include/CellcSibMgmtMacAbstractionLayerCoreConfiguration.hpp $
* @version               $LastChangedRevision: 586587 $
* @date                  $LastChangedDate: 2017-11-15 16:23:16 +0800 (周三, 2017-11-15) $
* @author                $Author: xlan001 $
*
* @module                CELLC
* @owner                 LTE Control Plane
*
* Copyright (c) 2012-2017 Nokia. All rights reserved.
*******************************************************************************/

#pragma once

#include "CellcSibMgmtIMacAbstractionLayerCoreConfiguration.hpp"
#include <boost/optional.hpp>
#include <map>
#include <memory>

namespace Cellc
{

namespace SibMgmt
{
class IModificationPeriodCalculator;
class IBroadcastAirConfig;
class IBroadcastContent;
class CellcWarningSystemsSibs;

class MacAbstractionLayerCoreConfiguration : public IMacAbstractionLayerCoreConfiguration
{
public:
    MacAbstractionLayerCoreConfiguration(
            std::shared_ptr<IBroadcastAirConfig> p_broadcastQueue,
            EPagingNB p_pagingNBCatM,
            EPagingNB p_pagingNB,
            std::shared_ptr<IModificationPeriodCalculator> p_modPeriodCalculator,
            bool p_multefireActive = false);

    TBcchModPeriodLength getModificationPeriodLength() const override;
    TBcchModPeriodLength getModificationPeriodLength(const SfnTime& p_activationTime) const override;
    EPagingNB getPagingNBCatM() const override { return m_pagingNBCatM; }
    EPagingNB getPagingNB() const override { return m_pagingNB; }
    EPagingNB getPagingNB(const SfnTime& p_activationTime) const override;
    std::shared_ptr<IBroadcastContent> getPredictedConfiguration() const override;

    void updateConfiguration(const std::shared_ptr<IBroadcastContent> p_updatedConfig) override;
    void updateConfirmedWrwrSibs() override;
    void revertWrwrSibsToLastConfirmed() override;
    bool isCmasActive() const override;
    bool isMultefireActive() const override;

private:
    TBcchModPeriodLength calculateModificationPeriod(const CellcSibs &p_sibs) const;
    std::shared_ptr<IBroadcastAirConfig> m_broadcastQueue;
    CellcWarningSystemsSibs m_lastConfirmedWrwrSibs;
    EPagingNB m_pagingNBCatM;
    EPagingNB m_pagingNB;
    std::shared_ptr<IModificationPeriodCalculator> m_modPeriodCalculator;
    bool m_multefireActive;
};

} // namespace SibMgmt
} // namespace Cellc

