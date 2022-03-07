/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_CELLC/SS_CellcServices/CP_CellcSystemInformationBroadcastManagement/Include/CellcSibMgmtMacAbstractionLayerCoreConfigurationMf.hpp $
* @version               $LastChangedRevision: 596349 $
* @date                  $LastChangedDate: 2017-12-19 18:47:42 +0800 (周二, 2017-12-19) $
* @author                $Author: xlan001 $
*
* @module                CELLC
* @owner                 LTE Control Plane
*
* Copyright (c) 2017 Nokia. All rights reserved.
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

class MacAbstractionLayerCoreConfigurationMf : public IMacAbstractionLayerCoreConfiguration
{
public:
    MacAbstractionLayerCoreConfigurationMf(
            std::shared_ptr<IBroadcastAirConfig> p_broadcastQueue,
            std::shared_ptr<IModificationPeriodCalculator> p_modPeriodCalculator);

    TBcchModPeriodLength getModificationPeriodLength() const override;
    TBcchModPeriodLength getModificationPeriodLength(const SfnTime&) const override;
    EPagingNB getPagingNBCatM() const override;
    EPagingNB getPagingNB() const override;
    EPagingNB getPagingNB(const SfnTime&) const override;
    std::shared_ptr<IBroadcastContent> getPredictedConfiguration() const override;

    void updateConfiguration(const std::shared_ptr<IBroadcastContent> p_updatedConfig) override;
    void updateConfirmedWrwrSibs() override {};
    void revertWrwrSibsToLastConfirmed() override {};
    bool isCmasActive() const override {return false;};
    bool isMultefireActive() const override {return true;};

private:
    TBcchModPeriodLength calculateModificationPeriod(const CellcMfSibs &p_sibs) const;
    std::shared_ptr<IBroadcastAirConfig> m_broadcastQueue;
    EPagingNB m_pagingNB{};
    std::shared_ptr<IModificationPeriodCalculator> m_modPeriodCalculator;
    EPagingNB getSib2NbMf();
};

} // namespace SibMgmt
} // namespace Cellc

