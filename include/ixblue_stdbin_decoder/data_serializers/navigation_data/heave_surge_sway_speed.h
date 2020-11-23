#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/heave_surge_sway_speed.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class HeaveSurgeSwaySpeed : public DataSerializer
{
public:
    HeaveSurgeSwaySpeed() : DataSerializer(21, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.heaveSurgeSwaySpeed.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.heaveSurgeSwaySpeed.get().realtime_heave_speed
                  << binaryNav.heaveSurgeSwaySpeed.get().surge_speed
                  << binaryNav.heaveSurgeSwaySpeed.get().sway_speed;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
