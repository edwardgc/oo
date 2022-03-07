/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/CP_Utilities/Include/UecITupSrbSignallingPortStrategy.hpp $
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
#include <vector>
#include <memory>
#include <boost/optional.hpp>

struct TUP_SrbSendReq;

namespace Asn1DataClasses
{
class SErrcRRCConnectionReconfiguration;
class US1apCause;
class SErrcRRCConnectionRelease;
}

namespace Uec
{
class TOaMBandNumber;
class ICellData;
class IMuiGenerator;
class IRrcMsgBuilder;
class IRrcMsgFillerFacade;
class IRrcTransactionIdManager;
class UemRrcConnectionReconfiguration;
class UemRrcConnectionReconfigurationGeneric;
class UecIServiceControllerTransmit;
class UecIUeContextData;
class IRrcConnectionReleaseBuilder;
class UecEvent;
class UemRrcUeCapability;
class IMultefireRrcReconfigurationFiller;
class TUecRadActAckForMacTriggeredRRCReconf;

class ITupSrbSignallingPortStrategy
{
public:
    virtual ~ITupSrbSignallingPortStrategy() = default;

    virtual void sendUECapabilityEnquiry(UecIServiceControllerTransmit&,
        const IRrcMsgBuilder&,
        const UecIUeContextData&,
        const ICellData&,
        const UemRrcUeCapability&,
        const boost::optional<std::vector<TOaMBandNumber>>&) const = 0;

    virtual void sendRrcConnectionRelease(
        UecIServiceControllerTransmit&,
        const IRrcConnectionReleaseBuilder&,
        const UecIUeContextData&,
        const ICellData&,
        const Asn1DataClasses::US1apCause&) const = 0;

    virtual void sendRrcConnectionRelease(
        UecIServiceControllerTransmit&,
        const UecIUeContextData&,
        const TUP_SrbSendReq&,
        std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionRelease>) const = 0;


    virtual void sendSecurityModeCommand(UecIServiceControllerTransmit&,
                                         const IRrcMsgBuilder&,
                                         const UecIUeContextData&,
                                         const ICellData&) const = 0;
    virtual void sendRrcConnReconfCommon(UecIServiceControllerTransmit&,
                                          const UecIUeContextData&,
                                          IMuiGenerator&,
                                          IRrcTransactionIdManager&,
                                          TUecRadActAckForMacTriggeredRRCReconf&,
                                          const UemRrcConnectionReconfigurationGeneric&,
                                          const IMultefireRrcReconfigurationFiller&,
                                          std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const = 0;
    virtual void sendRrcConnectionReconfiguration(UecIServiceControllerTransmit&,
                                                const IRrcMsgFillerFacade&,
                                                const UemRrcConnectionReconfiguration&,
                                                const UecIUeContextData&,
                                                IMuiGenerator&,
                                                TUecRadActAckForMacTriggeredRRCReconf&,
                                                std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const = 0;
    virtual void sendRrcConnectionReconfigurationGeneric(UecIServiceControllerTransmit&,
                                                const IRrcMsgFillerFacade&,
                                                const UemRrcConnectionReconfigurationGeneric&,
                                                const UecIUeContextData&,
                                                const bool,
                                                IMuiGenerator&,
                                                TUecRadActAckForMacTriggeredRRCReconf&,
                                                std::shared_ptr<Asn1DataClasses::SErrcRRCConnectionReconfiguration>&) const = 0;
};
} // namespace Uec

