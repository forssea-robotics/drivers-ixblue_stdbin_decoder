#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/speed_vessel_frame.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class SpeedVesselFrame : public DataSerializer
{
public:
    SpeedVesselFrame() : DataSerializer(22, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.speedVesselFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.speedVesselFrame.get().xv1_msec
                  << binaryNav.speedVesselFrame.get().xv2_msec
                  << binaryNav.speedVesselFrame.get().xv3_msec;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
