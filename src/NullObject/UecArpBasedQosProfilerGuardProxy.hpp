/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/SS_UecServices/SS_UeSpecificServices/CP_CellSpecificInterfacesProxy/Include/UecArpBasedQosProfilerGuardProxy.hpp $
* @version               $LastChangedRevision: 555249 $
* @date                  $LastChangedDate: 2017-07-20 19:48:39 +0800 (Thu, 20 Jul 2017) $
* @author                $Author: crpj83 $
*
* @module                Uec
* @owner                 LTE Control Plane
*
* Copyright (c) 2017 Nokia. All rights reserved.
*******************************************************************************/

#pragma once
#include <memory>

namespace Uec
{

class UEC_CellSetupReq;
class CellSpecificInterfaces;
class SUecUeDb;

class CellNotSetException
{
};

class IArpBasedQosProfiler
{
public:
    virtual void update(const UEC_CellSetupReq&) = 0;
    virtual void profileDb(SUecUeDb&) const = 0;
    virtual ~IArpBasedQosProfiler() = default;
};

class ArpBasedQosProfilerGuardProxy : public IArpBasedQosProfiler
{
private:
    std::shared_ptr<IArpBasedQosProfiler> m_arpBasedQosProfiler;
public:
    ArpBasedQosProfilerGuardProxy();
    ~ArpBasedQosProfilerGuardProxy() override = default;

    void update(const UEC_CellSetupReq&) override;
    void profileDb(SUecUeDb&) const override;
};

} // namespace Uec
