/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/CP_Utilities/Include/UecTupSrbSignallingPortMultefireStrategy.hpp $
* @version               $LastChangedRevision: 606931 $
* @date                  $LastChangedDate: 2018-01-26 19:04:29 +0800 (周五, 2018-01-26) $
* @author                $Author: Libowa $
*
* @brief
* @module                UEC
* @owner                 LTE Control Plane
*
* Copyright (c) 2017-2018 Nokia. All rights reserved.
*******************************************************************************/
#pragma once

#include "UecITupSrbSignallingPortStrategy.hpp"

namespace Asn1DataClasses
{
class SErrcRRCConnectionReconfiguration;
}

namespace Uec
{

class TupSrbSignallingPortMultefireStrategy : public ITupSrbSignallingPortStrategy //CPD_IGNORE_BEGIN
{
public:
    TupSrbSignallingPortMultefireStrategy(const ICellData&);

    void sendUECapabilityEnquiry(
        UecIServiceControllerTransmit&,
        const IRrcMsgBuilder&,
        const UecIUeContextData& ,
        const ICellData&,
        const UemRrcUeCapability&,
        const boost::optional<std::vector<TOaMBandNumber>>&) const override final;

    void sendRrcConnectionRelease(
        UecIServiceControllerTransmit&,
        const IRrcConnectionReleaseBuilder&,
        const UecIUeContextData&,
        const ICellData&,
        const Asn1DataClasses::US1apCause&) const override final;

    void sendRrcConnectionRelease(
        UecIServiceControllerTransmit&,
        const UecIUeContextData&,
        const TUP_SrbSendReq&,
        std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionRelease>) const override final;

    void sendSecurityModeCommand(UecIServiceControllerTransmit&,
                                 const IRrcMsgBuilder&,
                                 const UecIUeContextData&,
                                 const ICellData&) const override final;
    void sendRrcConnReconfCommon(UecIServiceControllerTransmit&,
                                 const UecIUeContextData&,
                                 IMuiGenerator&,
                                 IRrcTransactionIdManager&,
                                 TUecRadActAckForMacTriggeredRRCReconf&,
                                 const UemRrcConnectionReconfigurationGeneric&,
                                 const IMultefireRrcReconfigurationFiller&,
                                 std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const override final;
    void sendRrcConnectionReconfiguration(UecIServiceControllerTransmit& p_uecTransmit,
                                          const IRrcMsgFillerFacade&,
                                          const UemRrcConnectionReconfiguration&,
                                          const UecIUeContextData&,
                                          IMuiGenerator&,
                                          TUecRadActAckForMacTriggeredRRCReconf&,
                                          std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const override final;
    void sendRrcConnectionReconfigurationGeneric(UecIServiceControllerTransmit&,
                                                 const IRrcMsgFillerFacade&,
                                                 const UemRrcConnectionReconfigurationGeneric&,
                                                 const UecIUeContextData&,
                                                 const bool,
                                                 IMuiGenerator&,
                                                 TUecRadActAckForMacTriggeredRRCReconf&,
                                                 std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const override final;
private:
    const ICellData& m_cellData;

}; //CPD_IGNORE_END
} // namespace

