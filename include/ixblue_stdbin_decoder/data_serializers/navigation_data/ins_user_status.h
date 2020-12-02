#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/ins_user_status.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class INSUserStatus : public DataSerializer
{
public:
    INSUserStatus() : DataSerializer(17, 4) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.insUserStatus.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.insUserStatus.get().status;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
