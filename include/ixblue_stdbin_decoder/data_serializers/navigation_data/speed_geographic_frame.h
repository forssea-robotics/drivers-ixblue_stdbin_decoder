#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/speed_geographic_frame.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class SpeedGeographicFrame : public DataSerializer
{
public:
    SpeedGeographicFrame() : DataSerializer(9, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.speedGeographicFrame.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.speedGeographicFrame.get().north_msec
                  << binaryNav.speedGeographicFrame.get().east_msec
                  << binaryNav.speedGeographicFrame.get().up_msec;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
