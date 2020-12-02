#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/temperatures.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class Temperatures : public DataSerializer
{
public:
    Temperatures() : DataSerializer(25, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.temperatures.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.temperatures.get().mean_temp_fog
                  << binaryNav.temperatures.get().mean_temp_acc
                  << binaryNav.temperatures.get().board_temperature;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
