/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_CELLC/SS_CellcServices/CP_CellcSystemInformationBroadcastManagement/Include/CellcISibManager.hpp $
* @version               $LastChangedRevision: 604706 $
* @date                  $LastChangedDate: 2018-01-19 15:53:19 +0800 (周五, 2018-01-19) $
* @author                $Author: yongjiyu $
*
* @module                CELLC
*
* Copyright (c) 2010-2018 Nokia. All rights reserved.
*******************************************************************************/

#pragma once

#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>
#include <string>
#include "CellcISibManagerObserver.hpp"

namespace Cellc
{
namespace SibMgmt
{
struct ISimCallback;
struct IBroadcastTransaction;
} // namespace SibMgmt

struct IAcBarringParams;

class ISibManager : private boost::noncopyable
{
public:
    virtual ~ISibManager() = default;

    virtual void startSimAfterCmas() = 0;
    virtual void startSimAfterRachPowerOptimization(const std::shared_ptr<SibMgmt::IBroadcastTransaction>&) = 0;
    virtual void startSimAfterCellReconfiguration(const std::shared_ptr<SibMgmt::IBroadcastTransaction>&,
                                                  const std::weak_ptr<SibMgmt::ISimCallback>&) = 0;
    virtual void startSimAfterPlmnChange(const std::shared_ptr<SibMgmt::IBroadcastTransaction>&,
                                         const std::weak_ptr<SibMgmt::ISimCallback>&) = 0;
    virtual void startSimAfterMbmsReconfiguration(std::unique_ptr<SibMgmt::IBroadcastTransaction>,
                                                  const std::weak_ptr<SibMgmt::ISimCallback>&) = 0;

    virtual void startSimAfterCellSetup(const std::shared_ptr<SibMgmt::IBroadcastTransaction>&) = 0;
    virtual void startSimAfterCellS1AvailabilityInd(std::unique_ptr<SibMgmt::IBroadcastTransaction>,
                                                    const std::weak_ptr<SibMgmt::ISimCallback>&) = 0;
    virtual void startSimAfterCellBarring(const std::shared_ptr<SibMgmt::IBroadcastTransaction>&,
                                          const std::weak_ptr<SibMgmt::ISimCallback>&) = 0;
    virtual void startSimAfterSyncStatusChange() = 0;
    virtual void startSimAfterOverloadStateChange(std::unique_ptr<SibMgmt::IBroadcastTransaction>) = 0;
    virtual unsigned getCmasFsmsCnt() = 0;
    virtual void registerObserver(std::unique_ptr<SibMgmt::ICellSibManagerObserver>) = 0;
};

} // namespace Cellc

