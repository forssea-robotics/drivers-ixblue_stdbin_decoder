#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/ahrs_system_status.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class AHRSSystemStatus : public DataSerializer
{
public:
    AHRSSystemStatus() : DataSerializer(19, 12) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.ahrsSystemStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.ahrsSystemStatus.get().status1
                  << binaryNav.ahrsSystemStatus.get().status2
                  << binaryNav.ahrsSystemStatus.get().status3;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
