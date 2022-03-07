/**
*******************************************************************************
* @file                  $HeadURL: https://beisop60.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/branches/maintenance/1604.135-x/C_Application/SC_UEC/SS_UecServices/SS_UeSpecificServices/CP_UeMeasurementProcessing/MobilityMeasurementsConfiguration/Include/UecInterFrequencyMeasurementsVoiceQualityAdapter.hpp $
* @version               $LastChangedRevision: 596729 $
* @date                  $LastChangedDate: 2017-12-20 16:38:49 +0800 (周三, 2017-12-20) $
* @author                $Author: taweisz $
*
* @module                UEC
* @owner                 LTE Control Plane
*
* Copyright (c) 2017 Nokia. All rights reserved.
*******************************************************************************/

#pragma once

#include "UecMeasurementConfigurationIMobilityMeasurements.hpp"
#include "UecMeasurementConfigurationIConfigurator.hpp"

namespace Uec
{
class IMobilityMeasurementsUpdater;

namespace MobilityMeasurementsConfiguration
{
class ILteReconfiguratorProvider;
}

class LteMobilityMeasurementsVoiceQualityAdapter : public MeasurementConfiguration::IMobilityMeasurements,
                                                   public MeasurementConfiguration::IConfigurator
{
public:
    LteMobilityMeasurementsVoiceQualityAdapter(
        MobilityMeasurementsConfiguration::ILteReconfiguratorProvider& p_lteReconfiguratorProvider,
        IMobilityMeasurementsUpdater& p_mobilityMeasurementsUpdater);

    bool activate(std::shared_ptr<MeasurementConfiguration::IMobilityReconfigurationSession>
                  p_reconfigurationSession) override;
    bool shouldActivate() const override;
    void configure(std::shared_ptr<MeasurementConfiguration::IMobilityReconfigurationSession> p_session) override;

private:
    MobilityMeasurementsConfiguration::ILteReconfiguratorProvider& m_lteReconfiguratorProvider;
    IMobilityMeasurementsUpdater& m_mobilityMeasurementsUpdater;
};

} //namespace Uec

