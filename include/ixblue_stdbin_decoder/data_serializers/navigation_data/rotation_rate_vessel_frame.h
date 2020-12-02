#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/rotation_rate_vessel_frame.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class RotationRateVesselFrame : public DataSerializer
{
public:
    RotationRateVesselFrame() : DataSerializer(5, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rotationRateVesselFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rotationRateVesselFrame.get().xv1_degsec
                  << binaryNav.rotationRateVesselFrame.get().xv2_degsec
                  << binaryNav.rotationRateVesselFrame.get().xv3_degsec;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
