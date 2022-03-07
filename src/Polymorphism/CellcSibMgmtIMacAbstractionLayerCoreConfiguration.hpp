/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_CELLC/SS_CellcServices/CP_CellcSystemInformationBroadcastManagement/Include/CellcSibMgmtIMacAbstractionLayerCoreConfiguration.hpp $
* @version               $LastChangedRevision: 592686 $
* @date                  $LastChangedDate: 2017-12-07 01:36:08 +0800 (周四, 2017-12-07) $
* @author                $Author: crpj83 $
*
* @module                CELLC
* @owner                 LTE Control Plane
*
* Copyright (c) 2012-2017 Nokia. All rights reserved.
*******************************************************************************/

#pragma once

#include <memory>

namespace Cellc
{
namespace SibMgmt
{
struct CellcSibs;
struct CellcMfSibs;
class IBroadcastContent;
class TBcchModPeriodLength;
class EPagingNB;
class SfnTime;

class IMacAbstractionLayerCoreConfiguration
{
public:
    virtual ~IMacAbstractionLayerCoreConfiguration()= default;
    virtual TBcchModPeriodLength getModificationPeriodLength() const = 0;
    virtual TBcchModPeriodLength getModificationPeriodLength(const SfnTime& p_activationTime) const = 0;
    virtual void updateConfiguration(const std::shared_ptr<IBroadcastContent>) = 0;
    virtual std::shared_ptr<IBroadcastContent> getPredictedConfiguration() const = 0;
    virtual EPagingNB getPagingNBCatM() const = 0;
    virtual EPagingNB getPagingNB() const = 0;
    virtual EPagingNB getPagingNB(const SfnTime& p_activationTime) const = 0;
    virtual void updateConfirmedWrwrSibs() = 0;
    virtual void revertWrwrSibsToLastConfirmed() = 0;
    virtual bool isCmasActive() const = 0;
    virtual bool isMultefireActive () const = 0;
};

} // namespace SibMgmt
} // namespace Cellc

