#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/rotation_rate_vessel_frame_deviation.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class RotationRateVesselFrameDeviation : public DataSerializer
{
public:
    RotationRateVesselFrameDeviation() : DataSerializer(30, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rotationRateVesselFrameDeviation.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rotationRateVesselFrameDeviation.get().xv1_stddev_degsec
                  << binaryNav.rotationRateVesselFrameDeviation.get().xv2_stddev_degsec
                  << binaryNav.rotationRateVesselFrameDeviation.get().xv3_stddev_degsec;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
