#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/heading_roll_pitch_rate.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class HeadingRollPitchRate : public DataSerializer
{
public:
    HeadingRollPitchRate() : DataSerializer(4, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.headingRollPitchRate.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.headingRollPitchRate.get().heading_rate
                  << binaryNav.headingRollPitchRate.get().roll_rate
                  << binaryNav.headingRollPitchRate.get().pitch_rate;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
