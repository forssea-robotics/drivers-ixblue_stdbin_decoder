#pragma once

#include "ixblue_stdbin_decoder/data_models/external_data/turret_angles.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class TurretAngles : public DataSerializer
{
public:
    TurretAngles() : DataSerializer(24, 16) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.turretAngles.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.turretAngles.get().validityTime_100us
                  << binaryNav.turretAngles.get().headingbearingdrift_angle_deg
                  << binaryNav.turretAngles.get().roll_deg
                  << binaryNav.turretAngles.get().elevationpitch_deg;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
