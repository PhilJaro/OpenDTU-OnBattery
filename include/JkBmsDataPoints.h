#pragma once

#include <Arduino.h>
#include <optional>
#include <string>
#include <sstream>
#include <unordered_map>
#include <variant>

namespace JkBms {

enum class DataPointLabel : uint8_t {
    BmsTempCelsius = 0x80,
    BatteryTempOneCelsius = 0x81,
    BatteryTempTwoCelsius = 0x82,
    BatteryVoltageMilliVolt = 0x83,
    BatteryCurrentMilliAmps = 0x84,
    BatterySoCPercent = 0x85,
    BatteryTemperatureSensorAmount = 0x86,
    BatteryCycles = 0x87,
    BatteryCycleCapacity = 0x89,
    BatteryCellAmount = 0x8a,
    AlarmsBitmask = 0x8b,
    StatusBitmask = 0x8c,
    TotalOvervoltageThresholdMilliVolt = 0x8e,
    TotalUndervoltageThresholdMilliVolt = 0x8f,
    CellOvervoltageThresholdMilliVolt = 0x90,
    CellOvervoltageRecoveryMilliVolt = 0x91,
    CellOvervoltageProtectionDelaySeconds = 0x92,
    CellUndervoltageThresholdMilliVolt = 0x93,
    CellUndervoltageRecoveryMilliVolt = 0x94,
    CellUndervoltageProtectionDelaySeconds = 0x95,
    CellVoltageDiffThresholdMilliVolt = 0x96,
    DischargeOvercurrentThresholdAmperes = 0x97,
    DischargeOvercurrentDelaySeconds = 0x98,
    ChargeOvercurrentThresholdAmps = 0x99,
    ChargeOvercurrentDelaySeconds = 0x9a,
    BalanceCellVoltageThresholdMilliVolt = 0x9b,
    BalanceVoltageDiffThresholdMilliVolt = 0x9c,
    BalancingEnabled = 0x9d,
    BmsTempProtectionThresholdCelsius = 0x9e,
    BmsTempRecoveryThresholdCelsius = 0x9f,
    BatteryTempProtectionThresholdCelsius = 0xa0,
    BatteryTempRecoveryThresholdCelsius = 0xa1,
    BatteryTempDiffThresholdCelsius = 0xa2,
    ChargeHighTempThresholdCelsius = 0xa3,
    DischargeHighTempThresholdCelsius = 0xa4,
    ChargeLowTempThresholdCelsius = 0xa5,
    ChargeLowTempRecoveryCelsius = 0xa6,
    DischargeLowTempThresholdCelsius = 0xa7,
    DischargeLowTempRecoveryCelsius = 0xa8,
    CellAmountSetting = 0xa9,
    BatteryCapacitySettingAmpHours = 0xaa,
    BatteryChargeEnabled = 0xab,
    BatteryDischargeEnabled = 0xac,
    CurrentCalibrationMilliAmps = 0xad,
    BmsAddress = 0xae,
    BatteryType = 0xaf,
    SleepWaitTime = 0xb0, // what's this?
    LowCapacityAlarmThresholdPercent = 0xb1,
    ModificationPassword = 0xb2,
    DedicatedChargerSwitch = 0xb3, // what's this?
    EquipmentId = 0xb4,
    DateOfManufacturing = 0xb5,
    BmsHourMeterMinutes = 0xb6,
    BmsSoftwareVersion = 0xb7,
    CurrentCalibration = 0xb8,
    ActualBatteryCapacityAmpHours = 0xb9,
    ProductId = 0xba,
    ProtocolVersion = 0xc0
};

template<DataPointLabel> struct DataPointLabelTraits;

#define LABEL_TRAIT(n, t) template<> struct DataPointLabelTraits<DataPointLabel::n> { \
    using type = t; \
    static constexpr char const name[] = #n; \
};

/**
 * the types associated with the labels are the types for the respective data
 * points in the JkBms::DataPoint class. they are *not* always equal to the
 * type used in the serial message.
 *
 * it is unfortunate that we have to repeat all enum values here to define the
 * traits. code generation could help here (labels are defined in a single
 * source of truth and this code is generated -- no typing errors, etc.).
 * however, the compiler will complain if an enum is misspelled or traits are
 * defined for a removed enum, so we will notice. it will also complain when a
 * trait is missing and if a data point for a label without traits is added to
 * the DataPointContainer class, because the traits must be available then.
 * even though this is tedious to maintain, human errors will be caught.
 */
LABEL_TRAIT(BmsTempCelsius, int16_t);
LABEL_TRAIT(BatteryTempOneCelsius, int16_t);
LABEL_TRAIT(BatteryTempTwoCelsius, int16_t);
LABEL_TRAIT(BatteryVoltageMilliVolt, uint16_t);
LABEL_TRAIT(BatteryCurrentMilliAmps, int16_t);
LABEL_TRAIT(BatterySoCPercent, uint8_t);
LABEL_TRAIT(BatteryTemperatureSensorAmount, uint8_t);
LABEL_TRAIT(BatteryCycles, uint16_t);
LABEL_TRAIT(BatteryCycleCapacity, uint32_t);
LABEL_TRAIT(BatteryCellAmount, uint16_t);
LABEL_TRAIT(AlarmsBitmask, uint16_t);
LABEL_TRAIT(StatusBitmask, uint16_t);
LABEL_TRAIT(TotalOvervoltageThresholdMilliVolt, uint32_t);
LABEL_TRAIT(TotalUndervoltageThresholdMilliVolt, uint32_t);
LABEL_TRAIT(CellOvervoltageThresholdMilliVolt, uint16_t);
LABEL_TRAIT(CellOvervoltageRecoveryMilliVolt, uint16_t);
LABEL_TRAIT(CellOvervoltageProtectionDelaySeconds, uint16_t);
LABEL_TRAIT(CellUndervoltageThresholdMilliVolt, uint16_t);
LABEL_TRAIT(CellUndervoltageRecoveryMilliVolt, uint16_t);
LABEL_TRAIT(CellUndervoltageProtectionDelaySeconds, uint16_t);
LABEL_TRAIT(CellVoltageDiffThresholdMilliVolt, uint16_t);
LABEL_TRAIT(DischargeOvercurrentThresholdAmperes, uint16_t);
LABEL_TRAIT(DischargeOvercurrentDelaySeconds, uint16_t);
LABEL_TRAIT(ChargeOvercurrentThresholdAmps, uint16_t);
LABEL_TRAIT(ChargeOvercurrentDelaySeconds, uint16_t);
LABEL_TRAIT(BalanceCellVoltageThresholdMilliVolt, uint16_t);
LABEL_TRAIT(BalanceVoltageDiffThresholdMilliVolt, uint16_t);
LABEL_TRAIT(BalancingEnabled, bool);
LABEL_TRAIT(BmsTempProtectionThresholdCelsius, uint16_t);
LABEL_TRAIT(BmsTempRecoveryThresholdCelsius, uint16_t);
LABEL_TRAIT(BatteryTempProtectionThresholdCelsius, int16_t);
LABEL_TRAIT(BatteryTempRecoveryThresholdCelsius, int16_t);
LABEL_TRAIT(BatteryTempDiffThresholdCelsius, int16_t);
LABEL_TRAIT(ChargeHighTempThresholdCelsius, int16_t);
LABEL_TRAIT(DischargeHighTempThresholdCelsius, int16_t);
LABEL_TRAIT(ChargeLowTempThresholdCelsius, int16_t);
LABEL_TRAIT(ChargeLowTempRecoveryCelsius, int16_t);
LABEL_TRAIT(DischargeLowTempThresholdCelsius, int16_t);
LABEL_TRAIT(DischargeLowTempRecoveryCelsius, int16_t);
LABEL_TRAIT(CellAmountSetting, uint8_t);
LABEL_TRAIT(BatteryCapacitySettingAmpHours, uint32_t);
LABEL_TRAIT(BatteryChargeEnabled, bool);
LABEL_TRAIT(BatteryDischargeEnabled, bool);
LABEL_TRAIT(CurrentCalibrationMilliAmps, uint16_t);
LABEL_TRAIT(BmsAddress, uint8_t);
LABEL_TRAIT(BatteryType, uint8_t);
LABEL_TRAIT(SleepWaitTime, uint16_t);
LABEL_TRAIT(LowCapacityAlarmThresholdPercent, uint8_t);
LABEL_TRAIT(ModificationPassword, std::string);
LABEL_TRAIT(DedicatedChargerSwitch, uint8_t);
LABEL_TRAIT(EquipmentId, std::string);
LABEL_TRAIT(DateOfManufacturing, std::string);
LABEL_TRAIT(BmsHourMeterMinutes, uint32_t);
LABEL_TRAIT(BmsSoftwareVersion, std::string);
LABEL_TRAIT(CurrentCalibration, bool);
LABEL_TRAIT(ActualBatteryCapacityAmpHours, uint32_t);
LABEL_TRAIT(ProductId, std::string);
LABEL_TRAIT(ProtocolVersion, uint8_t);
#undef LABEL_TRAIT

class DataPoint {
    friend class DataPointContainer;

    public:
        using tValue = std::variant<bool, uint8_t, uint16_t, uint32_t, int16_t, std::string>;

        DataPoint() = delete;

        DataPoint(DataPoint const& other)
            : _strLabel(other._strLabel)
            , _strValue(other._strValue)
            , _value(other._value)
            , _timestamp(other._timestamp) { }

        DataPoint(std::string const& strLabel, std::string const& strValue, tValue value, uint32_t timestamp)
            : _strLabel(strLabel)
            , _strValue(strValue)
            , _value(std::move(value))
            , _timestamp(timestamp) { }

        std::string const& getLabelText() const { return _strLabel; }
        std::string const& getValueText() const { return _strValue; }
        uint32_t getTimestamp() const { return _timestamp; }

    private:
        std::string _strLabel;
        std::string _strValue;
        tValue _value;
        uint32_t _timestamp;
};

template<typename T> std::string dataPointValueToStr(T const& v);

class DataPointContainer {
    public:
        DataPointContainer() = default;

        using Label = DataPointLabel;
        template<Label L> using Traits = JkBms::DataPointLabelTraits<L>;

        template<Label L>
        void add(typename Traits<L>::type val) {
            _dataPoints.emplace(
                    L,
                    DataPoint(
                        Traits<L>::name,
                        dataPointValueToStr(val),
                        DataPoint::tValue(std::move(val)),
                        millis()
                    )
            );
        }

        template<Label L>
        std::optional<DataPoint const> getDataPointFor() {
            auto it = _dataPoints.find(L);
            if (it == _dataPoints.end()) { return std::nullopt; }
            return it->second;
        }

        template<Label L>
        std::optional<typename Traits<L>::type> get() {
            auto optionalDataPoint = getDataPointFor<L>();
            if (!optionalDataPoint.has_value()) { return std::nullopt; }
            return std::get<typename Traits<L>::type>(optionalDataPoint->_value);
        }

        using tMap = std::unordered_map<Label, DataPoint const>;
        tMap::const_iterator cbegin() const { return _dataPoints.cbegin(); }
        tMap::const_iterator cend() const { return _dataPoints.cend(); }

    private:
        tMap _dataPoints;
};

} /* namespace JkBms */
