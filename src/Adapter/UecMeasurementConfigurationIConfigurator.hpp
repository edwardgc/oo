/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/SS_UecServices/SS_UeSpecificServices/CP_UeMeasurementProcessing/MobilityMeasurementsConfiguration/Include/UecMeasurementConfigurationIConfigurator.hpp $
* @version               $LastChangedRevision: 592686 $
* @date                  $LastChangedDate: 2017-12-07 01:36:08 +0800 (周四, 2017-12-07) $
* @author                $Author: crpj83 $
*
* @module                UEC
* @owner                 LTE Control Plane
*
* Copyright (c) 2014-2015 Nokia. All rights reserved.
*******************************************************************************/

#pragma once

#include <memory>
#include <vector>

namespace Uec
{

namespace MeasurementConfiguration
{

class MobilityReconfigurationSessionPtr;

class IConfigurator
{
public:
    virtual ~IConfigurator() = default;
    virtual void configure(MobilityReconfigurationSessionPtr p_session) = 0;
};

typedef std::shared_ptr<IConfigurator> IConfiguratorPtr;
typedef std::vector<IConfiguratorPtr> ConfiguratorCollection;

} // namespace MeasurementConfiguration

} // namespace Uec
