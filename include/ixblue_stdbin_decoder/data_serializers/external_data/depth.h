#pragma once

#include "ixblue_stdbin_decoder/data_models/external_data/depth.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class Depth : public DataSerializer
{
public:
    Depth() : DataSerializer(9, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.depth.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.depth.get().validityTime_100us
                  << binaryNav.depth.get().depth_m
                  << binaryNav.depth.get().depth_stddev_m;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
