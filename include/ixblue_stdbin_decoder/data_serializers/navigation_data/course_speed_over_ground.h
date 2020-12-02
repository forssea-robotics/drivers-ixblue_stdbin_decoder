#pragma once

#include "ixblue_stdbin_decoder/data_models/navigation_data/course_speed_over_ground.h"
#include "ixblue_stdbin_decoder/data_serializer.h"

namespace ixblue_stdbin_decoder
{
namespace Serializer
{
class CourseSpeedoverGround : public DataSerializer
{
public:
    CourseSpeedoverGround() : DataSerializer(24, 8) { }
    bool serialize(boost::asio::mutable_buffer& outBuffer,
                   const Data::BinaryNav& binaryNav) override
    {
        if (!binaryNav.courseSpeedoverGround.is_initialized()) {
            return false;
        }
        outBuffer << binaryNav.courseSpeedoverGround.get().course_over_ground
                  << binaryNav.courseSpeedoverGround.get().speed_over_ground;
        return true;
    }
};
} // namespace Serializer
} // namespace ixblue_stdbin_decoder
