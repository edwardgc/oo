/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_CELLC/SS_CellcServices/CP_CellcSystemInformationBroadcastManagement/Include/CellcSibManagerObserver.hpp $
* @version               $LastChangedRevision: 611037 $
* @date                  $LastChangedDate: 2018-02-09 15:44:19 +0800 (周五, 2018-02-09) $
* @author                $Author: puzh $
*
* @module                CELLC
* @owner                 LTE Control Plane
*
*
* Copyright (c) 2017-2018 Nokia. All rights reserved.
*******************************************************************************/

#pragma once
#include <set>
#include "CellcISibManagerObserver.hpp"

namespace Cellc
{
namespace SibMgmt
{

using TOaMEutraCelId = int;

class CatmEssentialModIndSender : public ICellSibManagerObserver
{
public:
    CatmEssentialModIndSender(TOaMEutraCelId p_eutraCelId)
      : m_eutraCelId(p_eutraCelId)
        {}
    void onSimStartWithCatmEssentialParametersChanged(const FsmId p_fsmId);
    void onSimStop(const FsmId p_fsmId);
private:
    void sendCatmEssentialModInd(const bool p_cellCatmEssentialModOnGoing) const;
    std::set<FsmId> m_essentialModFsmSet;
    TOaMEutraCelId m_eutraCelId;
};

} // namespace SibMgmt
} // namespace Cellc

