/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/SS_UecServices/SS_UeSpecificServices/CP_CellSpecificInterfacesProxy/Source/UecArpBasedQosProfilerGuardProxy.cpp $
* @version               $LastChangedRevision: 568930 $
* @date                  $LastChangedDate: 2017-09-08 22:34:02 +0800 (Fri, 08 Sep 2017) $
* @author                $Author: crpj83 $
*
* @module                Uec
* @owner                 LTE Control Plane
*
* Copyright (c) 2017 Nokia. All rights reserved.
*******************************************************************************/
#include "UecArpBasedQosProfilerGuardProxy.hpp"

namespace Uec
{

struct NullArpBasedQosProfiler : IArpBasedQosProfiler
{
    void update(const UEC_CellSetupReq&) override
    {
        throw CellNotSetException();
    }

    void profileDb(SUecUeDb&) const override
    {
        throw CellNotSetException();
    }
};

static std::shared_ptr<IArpBasedQosProfiler> g_nullArpBasedQosProfiler = std::make_shared<NullArpBasedQosProfiler>();

ArpBasedQosProfilerGuardProxy::ArpBasedQosProfilerGuardProxy()
    : m_arpBasedQosProfiler(g_nullArpBasedQosProfiler)
{
}

void ArpBasedQosProfilerGuardProxy::update(const UEC_CellSetupReq& p_msg)
{
    m_arpBasedQosProfiler->update(p_msg);
}

void ArpBasedQosProfilerGuardProxy::profileDb(SUecUeDb& p_db) const
{
    m_arpBasedQosProfiler->profileDb(p_db);
}

} // namespace Uec
