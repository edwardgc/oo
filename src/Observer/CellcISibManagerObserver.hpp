/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_CELLC/SS_CellcServices/CP_CellcSystemInformationBroadcastManagement/Include/CellcISibManagerObserver.hpp $
* @version               $LastChangedRevision: 592686 $
* @date                  $LastChangedDate: 2017-12-07 01:36:08 +0800 (周四, 2017-12-07) $
* @author                $Author: crpj83 $
*
* @module                CELLC
* @owner                 LTE Control Plane
*
*
* Copyright (c) 2017 Nokia. All rights reserved.
*******************************************************************************/

#pragma once

namespace Cellc
{
namespace SibMgmt
{

using FsmId = int;

class ICellSibManagerObserver
{
public:
    virtual ~ICellSibManagerObserver() = default;
    virtual void onSimStartWithCatmEssentialParametersChanged(const FsmId) = 0;
    virtual void onSimStop(const FsmId) = 0;
};

} // namespace SibMgmt
} // namespace Cellc

