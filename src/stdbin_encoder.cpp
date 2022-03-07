#include <ixblue_stdbin_decoder/stdbin_encoder.h>

/* Navigation data blocs */
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/acceleration_geographic_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/acceleration_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/ahrs_algorithm_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/ahrs_system_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/ahrs_user_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/attitude_heading.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/attitude_heading_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/attitude_quaternion.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/attitude_quaternion_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/course_speed_over_ground.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/current_geographic_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/current_geographic_frame_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/heading_roll_pitch_rate.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/heave_surge_sway_speed.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/ins_algorithm_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/ins_system_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/ins_user_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/position.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/position_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/raw_acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/realtime_heave_surge_sway.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/rotation_rate_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/rotation_rate_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/sensor_status.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/smart_heave.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/speed_geographic_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/speed_geographic_frame_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/speed_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/system_date.h>
#include <ixblue_stdbin_decoder/data_serializers/navigation_data/temperatures.h>

/* Extended navigation data blocs */
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/raw_rotation_rate_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/rotation_acceleration_vessel_frame_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_attitude_heading.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_attitude_heading_deviation.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_position.h>
#include <ixblue_stdbin_decoder/data_serializers/extended_navigation_data/vehicle_position_deviation.h>

/* External data blocs */
#include <ixblue_stdbin_decoder/data_serializers/external_data/depth.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/dmi.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/dvl_ground_speed.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/dvl_water_speed.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/emlog.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/eventmarker.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/gnss.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/lbl.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/logbook.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/sound_velocity.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/turret_angles.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/usbl.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/utc.h>
#include <ixblue_stdbin_decoder/data_serializers/external_data/vtg.h>

#include <numeric>

using namespace boost::asio;

namespace ixblue_stdbin_decoder
{

StdBinEncoder::StdBinEncoder::StdBinEncoder(ProtocolVersion version, DataMode mode)
    : dataMode(mode)
    , protocolVersion(version)
    , navigationSerializers(
        { std::make_shared<Serializer::AttitudeHeading>(),
           std::make_shared<Serializer::AttitudeHeadingDeviation>(),
           std::make_shared<Serializer::RealTimeHeaveSurgeSway>(),
           std::make_shared<Serializer::SmartHeave>(),
           std::make_shared<Serializer::HeadingRollPitchRate>(),
           std::make_shared<Serializer::RotationRateVesselFrame>(),
           std::make_shared<Serializer::AccelerationVesselFrame>(),
           std::make_shared<Serializer::Position>(),
           std::make_shared<Serializer::PositionDeviation>(),
           std::make_shared<Serializer::SpeedGeographicFrame>(),
           std::make_shared<Serializer::SpeedGeographicFrameDeviation>(),
           std::make_shared<Serializer::CurrentGeographicFrame>(),
           std::make_shared<Serializer::CurrentGeographicFrameDeviation>(),
           std::make_shared<Serializer::SystemDate>(),
           std::make_shared<Serializer::SensorStatus>(),
           std::make_shared<Serializer::INSAlgorithmStatus>(),
           std::make_shared<Serializer::INSSystemStatus>(),
           std::make_shared<Serializer::INSUserStatus>(),
           std::make_shared<Serializer::AHRSAlgorithmStatus>(),
           std::make_shared<Serializer::AHRSSystemStatus>(),
           std::make_shared<Serializer::AHRSUserStatus>(),
           std::make_shared<Serializer::HeaveSurgeSwaySpeed>(),
           std::make_shared<Serializer::SpeedVesselFrame>(),
           std::make_shared<Serializer::AccelerationGeographicFrame>(),
           std::make_shared<Serializer::CourseSpeedoverGround>(),
           std::make_shared<Serializer::Temperatures>(),
           std::make_shared<Serializer::AttitudeQuaternion>(),
           std::make_shared<Serializer::AttitudeQuaternionDeviation>(),
           std::make_shared<Serializer::RawAccelerationVesselFrame>(),
           std::make_shared<Serializer::AccelerationVesselFrameDeviation>(),
           std::make_shared<Serializer::RotationRateVesselFrameDeviation>()},
          [](const DataSerializerPtr& lhs, const DataSerializerPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          })
    , extendedNavigationSerializers(
          {std::make_shared<Serializer::RotationAccelerationVesselFrame>(),
           std::make_shared<Serializer::RotationAccelerationVesselFrameDeviation>(),
           std::make_shared<Serializer::RawRotationRateVesselFrame>(),
           std::make_shared<Serializer::VehicleAttitudeHeading>(),
           std::make_shared<Serializer::VehiclePosition>(),
           std::make_shared<Serializer::VehiclePositionDeviation>()},
          [](const DataSerializerPtr& lhs, const DataSerializerPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          })
    , externalDataSerializers(
          { std::make_shared<Serializer::Utc>(),
            std::make_shared<Serializer::Gnss1>(),
            std::make_shared<Serializer::Gnss2>(),
            std::make_shared<Serializer::GnssManual>(),
            std::make_shared<Serializer::Emlog1>(),
            std::make_shared<Serializer::Emlog2>(),
            std::make_shared<Serializer::Depth>(),
            std::make_shared<Serializer::Usbl1>(),
            std::make_shared<Serializer::Usbl2>(),
            std::make_shared<Serializer::Usbl3>(),
            std::make_shared<Serializer::DvlGroundSpeed1>(),
            std::make_shared<Serializer::DvlWaterSpeed1>(),
            std::make_shared<Serializer::SoundVelocity>(),
            std::make_shared<Serializer::Dmi>(),
            std::make_shared<Serializer::Lbl1>(),
            std::make_shared<Serializer::Lbl2>(),
            std::make_shared<Serializer::Lbl3>(),
            std::make_shared<Serializer::Lbl4>(),
            std::make_shared<Serializer::EventMarkerA>(),
            std::make_shared<Serializer::EventMarkerB>(),
            std::make_shared<Serializer::EventMarkerC>(),
            std::make_shared<Serializer::DvlGroundSpeed2>(),
            std::make_shared<Serializer::DvlWaterSpeed2>(),
            std::make_shared<Serializer::TurretAngles>(),
            std::make_shared<Serializer::Vtg1>(),
            std::make_shared<Serializer::Vtg2>(),
            std::make_shared<Serializer::LogBook>() },
          [](const DataSerializerPtr& lhs, const DataSerializerPtr& rhs) -> bool {
              return lhs->getOffsetInMask() < rhs->getOffsetInMask();
          })
{
    if (dataMode != INPUT && dataMode != OUTPUT) {
        throw std::runtime_error(
            "This library can only serialize data in input/output mode"
        );
    }
}

std::pair<uint32_t, std::vector<uint8_t>> StdBinEncoder::processData(
    const Data::BinaryNav& binaryNav, const tSerializersSet& serializers
) const
{
    std::vector<uint8_t> data;
    std::bitset<32> bit_mask;

    for (const auto& serializer : serializers)
    {
        std::vector<uint8_t> memory(serializer->getBytesCount());
        boost::asio::mutable_buffer buffer(memory.data(), memory.size());

        if (serializer->serialize(buffer, bit_mask, binaryNav)) {
            data.insert(data.end(), memory.begin(), memory.end());
        }
    }

   return {bit_mask.to_ulong(), data };
}



size_t StdBinEncoder::getHeaderSize(const Data::BinaryNav& binaryNav) const
{
    switch (protocolVersion)
    {
    case V2: return 21;
    case V3: return 25;
    case V4: return 27;
    case V5: return 27;
    default: throw std::runtime_error("Unknown protocol version");
    }
}

std::vector<uint8_t> StdBinEncoder::serialize(const Data::BinaryNav& binaryNav) const
{
    uint32_t navigationDataBitMask = 0, extendedNavigationDataBitMask = 0, externalDataBitMask;
    std::vector<uint8_t> navigationData, extendedNavigationData, externalData;

    if (dataMode == OUTPUT)
    {
        std::tie(navigationDataBitMask, navigationData) = processData(binaryNav, navigationSerializers);
        std::tie(extendedNavigationDataBitMask, extendedNavigationData) = processData(binaryNav, extendedNavigationSerializers);
    }
    std::tie(externalDataBitMask, externalData) = processData(binaryNav, externalDataSerializers);

    uint16_t telegramSize =  getHeaderSize(binaryNav) + // the header size +
                             externalData.size() + 4;   // external sensor data size
                                                        // + 4 bytes checksum

    std::vector<uint8_t> memory(telegramSize);
    boost::asio::mutable_buffer buffer(memory.data(), memory.size());

    buffer << (uint8_t)'I';
    buffer << (uint8_t)'X';
    buffer << (uint8_t)protocolVersion;
    buffer << (uint32_t)navigationDataBitMask; // navigation bit mask (unused in input mode)

    if (protocolVersion > 2)
    {
        buffer << (uint32_t)extendedNavigationDataBitMask; // extended navigation bit mask
                               // (unused in input mode)
    }
    buffer << externalDataBitMask;

    if (protocolVersion > 3)
    {
        buffer << (uint16_t)0; // navigation size
                               // (unused in input mode)
    }

    buffer << telegramSize;

    buffer << (uint8_t)0x00; // UTC time reference
    buffer << std::array<uint8_t, 7>{ 0, 0, 0, 0, 0, 0, 0 }; // rfu (should be 0x00
                                                             // in input mode)

    buffer << navigationData;
    if (protocolVersion > 2)
    {
         buffer << extendedNavigationData;
    }
    buffer << externalData;

    uint32_t checksum = std::accumulate(memory.begin(), memory.end() - 4, 0);
    buffer << checksum;

    return memory;
}

} // namespace ixblue_stdbin_decoder

