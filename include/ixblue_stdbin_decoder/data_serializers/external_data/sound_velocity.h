#pragma once

#include "ixblue_stdbin_decoder/data_models/external_data/sound_velocity.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class SoundVelocity : public DataSerializer
{
public:
    SoundVelocity() : DataSerializer(12, 8) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.soundVelocity.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.soundVelocity.get().validityTime_100us
                  << binaryNav.soundVelocity.get().ext_speedofsound_ms;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
