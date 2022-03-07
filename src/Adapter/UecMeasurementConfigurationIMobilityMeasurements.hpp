/**
*******************************************************************************
* @file                  $HeadURL: https://beisop70.china.nsn-net.net/isource/svnroot/BTS_SC_CPLANE/trunk/C_Application/SC_UEC/SS_UecServices/SS_UeSpecificServices/CP_UeMeasurementProcessing/MobilityMeasurementsConfiguration/Include/UecMeasurementConfigurationIMobilityMeasureme $
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

namespace Uec
{

namespace MeasurementConfiguration
{

class IMobilityReconfigurationSession;

class IMobilityMeasurements
{
public:
    virtual bool activate(std::shared_ptr<IMobilityReconfigurationSession> p_a2ReconfigurationSession) = 0;
    virtual ~IMobilityMeasurements()= default;
};

} // namespace MeasurementConfiguration

} // namespace Uec
