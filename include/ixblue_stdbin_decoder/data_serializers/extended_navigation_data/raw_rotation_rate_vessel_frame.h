#pragma once

#include "ixblue_stdbin_decoder/data_models/extended_navigation_data/raw_rotation_rate_vessel_frame.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class RawRotationRateVesselFrame : public DataSerializer
{
public:
    RawRotationRateVesselFrame() : DataSerializer(2, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.rawRotationRateVesselFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.rawRotationRateVesselFrame.get().xv1_degsec
                  << binaryNav.rawRotationRateVesselFrame.get().xv2_degsec
                  << binaryNav.rawRotationRateVesselFrame.get().xv3_degsec;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
