#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/ins_system_status.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class INSSystemStatus : public DataSerializer
{
public:
    INSSystemStatus() : DataSerializer(16, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.insSystemStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.insSystemStatus.get().status1
                  << binaryNav.insSystemStatus.get().status2
                  << binaryNav.insSystemStatus.get().status3;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
