#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/ahrs_algorithm_status.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class AHRSAlgorithmStatus : public DataSerializer
{
public:
    AHRSAlgorithmStatus() : DataSerializer(18, 4) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.ahrsAlgorithmStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.ahrsAlgorithmStatus.get().status;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
