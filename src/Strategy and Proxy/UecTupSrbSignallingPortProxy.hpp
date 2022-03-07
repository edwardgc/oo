/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/CP_Utilities/Include/UecTupSrbSignallingPortProxy.hpp $
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

namespace Uec
{
class IRrcMsgBuilder;
class UecIServiceControllerTransmit;
class ICommonData;
class ICellPortIdentityProvider;

namespace PcmdTickets
{
class IPcmdService;
}
class IMultefireRrcReconfigurationFiller;

class TupSrbSignallingPortProxy : public ITupSrbSignallingPortStrategy
{
public:
    explicit constexpr TupSrbSignallingPortProxy(const ICellPortIdentityProvider& p_cellPortIdentityProvider,
            UecIServiceControllerTransmit& p_uecTransmit,
            const IRrcMsgBuilder& p_rrcMsgBuilder,
            TUecRadActAckForMacTriggeredRRCReconf& p_actAckForMacTriggeredRRCReconf,
            const UecIUeContextData& p_ueContextData,
            const ICommonData& p_commonData,
            PcmdTickets::IPcmdService& p_pcmdService,
            const IMultefireRrcReconfigurationFiller& p_multefireRrcReconfigurationFiller) noexcept
    : m_cellPortIdentityProvider(p_cellPortIdentityProvider),
      m_uecTransmit(p_uecTransmit),
      m_rrcMsgBuilder(p_rrcMsgBuilder),
      m_actAckForMacTriggeredRRCReconf(p_actAckForMacTriggeredRRCReconf),
      m_ueContextData(p_ueContextData),
      m_commonData(p_commonData),
      m_pcmdService(p_pcmdService),
      m_multefireRrcReconfigurationFiller(p_multefireRrcReconfigurationFiller)
    {
    }

    void sendRrcConnectionRelease(
        const IRrcConnectionReleaseBuilder&,
        const UecIUeContextData&,
        const ICellData&,
        const Asn1DataClasses::US1apCause&) const override;

    void sendRrcConnectionRelease(
        const UecIUeContextData&,
        const TUP_SrbSendReq&,
        std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionRelease>) const override;

    void sendUECapabilityEnquiry(
        const UecIUeContextData&,
        const ICellData&,
        const UemRrcUeCapability&,
        const boost::optional<std::vector<TOaMBandNumber>>&) const override;

    void sendSecurityModeCommand(const UecIUeContextData&, const ICellData&) const override;
    void sendRrcConnReconfCommon(IMuiGenerator&,
                                 IRrcTransactionIdManager&,
                                 const UemRrcConnectionReconfigurationGeneric&,
                                 std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const override;
    void sendRrcConnectionReconfiguration(IMuiGenerator&,
                                          const IRrcMsgFillerFacade&,
                                          const UemRrcConnectionReconfiguration&,
                                          std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const override;
    void sendRrcConnectionReconfigurationGeneric(const bool,
                                                 IMuiGenerator&,
                                                 const IRrcMsgFillerFacade&,
                                                 const UemRrcConnectionReconfigurationGeneric&,
                                                 std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const override;
private:
    const ICellPortIdentityProvider& m_cellPortIdentityProvider;
    UecIServiceControllerTransmit& m_uecTransmit;
    const IRrcMsgBuilder& m_rrcMsgBuilder;
    TUecRadActAckForMacTriggeredRRCReconf& m_actAckForMacTriggeredRRCReconf;
    const UecIUeContextData& m_ueContextData;
    const ICommonData& m_commonData;
    PcmdTickets::IPcmdService& m_pcmdService;
    const IMultefireRrcReconfigurationFiller& m_multefireRrcReconfigurationFiller;
};
}

