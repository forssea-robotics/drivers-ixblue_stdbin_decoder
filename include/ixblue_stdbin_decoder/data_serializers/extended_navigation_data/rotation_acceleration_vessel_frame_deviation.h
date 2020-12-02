#pragma once

#include "ixblue_stdbin_decoder/data_models/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class RotationAccelerationVesselFrameDeviation : public DataSerializer
{
public:
    RotationAccelerationVesselFrameDeviation() : DataSerializer(1, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rotationAccelerationVesselFrameDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rotationAccelerationVesselFrameDeviation.get().xv1_stddev_degsec2
                  << binaryNav.rotationAccelerationVesselFrameDeviation.get().xv2_stddev_degsec2
                  << binaryNav.rotationAccelerationVesselFrameDeviation.get().xv3_stddev_degsec2;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
