#ifndef __CAN_MSG_H
#define __CAN_MSG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef EINVAL
#    define EINVAL 22
#endif

/* Frame ids. */
#define CAN_AMK_INVERTER_AMK1_SET_POINTS1_FRAME_ID (0x186u)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES2_FRAME_ID (0x287u)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES1_FRAME_ID (0x285u)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES1_FRAME_ID (0x284u)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES2_FRAME_ID (0x286u)
#define CAN_AMK_INVERTER_AMK0_SET_POINTS1_FRAME_ID (0x185u)

/* Frame lengths in bytes. */
#define CAN_AMK_INVERTER_AMK1_SET_POINTS1_LENGTH (8u)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES2_LENGTH (8u)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES1_LENGTH (8u)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES1_LENGTH (8u)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES2_LENGTH (8u)
#define CAN_AMK_INVERTER_AMK0_SET_POINTS1_LENGTH (8u)

/* Extended or standard frame types. */
#define CAN_AMK_INVERTER_AMK1_SET_POINTS1_IS_EXTENDED (0)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES2_IS_EXTENDED (0)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES1_IS_EXTENDED (0)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES1_IS_EXTENDED (0)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES2_IS_EXTENDED (0)
#define CAN_AMK_INVERTER_AMK0_SET_POINTS1_IS_EXTENDED (0)

/* Frame cycle times in milliseconds. */
#define CAN_AMK_INVERTER_AMK1_SET_POINTS1_CYCLE_TIME_MS (5u)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES2_CYCLE_TIME_MS (5u)
#define CAN_AMK_INVERTER_AMK1_ACTUAL_VALUES1_CYCLE_TIME_MS (5u)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES1_CYCLE_TIME_MS (5u)
#define CAN_AMK_INVERTER_AMK0_ACTUAL_VALUES2_CYCLE_TIME_MS (5u)
#define CAN_AMK_INVERTER_AMK0_SET_POINTS1_CYCLE_TIME_MS (5u)

/* Signal choices. */


/**
 * Signals in message AMK1_SetPoints1.
 *
 * All signal values are as on the CAN bus.
 */
struct can_amk_inverter_amk1_set_points1_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_inverter_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_dc_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_enable;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_error_reset;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_target_velocity;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_torque_limit_positiv;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_torque_limit_negativ;
};

/**
 * Signals in message AMK1_ActualValues2.
 *
 * All signal values are as on the CAN bus.
 */
struct can_amk_inverter_amk1_actual_values2_t {
    /**
     * Range: -32768..32767 (-3276.8..3276.7 �C)
     * Scale: 0.1
     * Offset: 0
     */
    int16_t amk_temp_motor;

    /**
     * Range: -32768..32767 (-3276.8..3276.7 �C)
     * Scale: 0.1
     * Offset: 0
     */
    int16_t amk_temp_inverter;

    /**
     * Range: 0..65535 (0..65535 -)
     * Scale: 1
     * Offset: 0
     */
    uint16_t amk_error_info;

    /**
     * Range: -32768..32767 (-3276.8..3276.7 �C)
     * Scale: 0.1
     * Offset: 0
     */
    int16_t amk_temp_igbt;
};

/**
 * Signals in message AMK1_ActualValues1.
 *
 * All signal values are as on the CAN bus.
 */
struct can_amk_inverter_amk1_actual_values1_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_system_ready;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_error;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_warn;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_quit_dc_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_dc_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_quit_inverter_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_inverter_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_derating;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_actual_velocity;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_torque_current;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_magnetizing_current;
};

/**
 * Signals in message AMK0_ActualValues1.
 *
 * All signal values are as on the CAN bus.
 */
struct can_amk_inverter_amk0_actual_values1_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_system_ready;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_error;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_warn;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_quit_dc_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_dc_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_quit_inverter_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_inverter_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_derating;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_actual_velocity;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_torque_current;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_magnetizing_current;
};

/**
 * Signals in message AMK0_ActualValues2.
 *
 * All signal values are as on the CAN bus.
 */
struct can_amk_inverter_amk0_actual_values2_t {
    /**
     * Range: -32768..32767 (-3276.8..3276.7 �C)
     * Scale: 0.1
     * Offset: 0
     */
    int16_t amk_temp_motor;

    /**
     * Range: -32768..32767 (-3276.8..3276.7 �C)
     * Scale: 0.1
     * Offset: 0
     */
    int16_t amk_temp_inverter;

    /**
     * Range: 0..65535 (0..65535 -)
     * Scale: 1
     * Offset: 0
     */
    uint16_t amk_error_info;

    /**
     * Range: -32768..32767 (-3276.8..3276.7 �C)
     * Scale: 0.1
     * Offset: 0
     */
    int16_t amk_temp_igbt;
};

/**
 * Signals in message AMK0_SetPoints1.
 *
 * All signal values are as on the CAN bus.
 */
struct can_amk_inverter_amk0_set_points1_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_inverter_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_dc_on;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_enable;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint8_t amk_b_error_reset;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_target_velocity;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_torque_limit_positiv;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t amk_torque_limit_negativ;
};

/**
 * Pack message AMK1_SetPoints1.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int can_amk_inverter_amk1_set_points1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk1_set_points1_t *src_p,
    size_t size);

/**
 * Unpack message AMK1_SetPoints1.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int can_amk_inverter_amk1_set_points1_unpack(
    struct can_amk_inverter_amk1_set_points1_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_set_points1_amk_b_inverter_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_b_inverter_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_b_inverter_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_set_points1_amk_b_dc_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_b_dc_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_b_dc_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_set_points1_amk_b_enable_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_b_enable_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_b_enable_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_set_points1_amk_b_error_reset_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_b_error_reset_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_b_error_reset_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_set_points1_amk_target_velocity_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_target_velocity_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_target_velocity_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_set_points1_amk_torque_limit_positiv_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_torque_limit_positiv_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_torque_limit_positiv_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_set_points1_amk_torque_limit_negativ_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_set_points1_amk_torque_limit_negativ_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_set_points1_amk_torque_limit_negativ_is_in_range(int16_t value);

/**
 * Pack message AMK1_ActualValues2.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int can_amk_inverter_amk1_actual_values2_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk1_actual_values2_t *src_p,
    size_t size);

/**
 * Unpack message AMK1_ActualValues2.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int can_amk_inverter_amk1_actual_values2_unpack(
    struct can_amk_inverter_amk1_actual_values2_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_actual_values2_amk_temp_motor_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values2_amk_temp_motor_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values2_amk_temp_motor_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_actual_values2_amk_temp_inverter_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values2_amk_temp_inverter_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values2_amk_temp_inverter_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t can_amk_inverter_amk1_actual_values2_amk_error_info_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values2_amk_error_info_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values2_amk_error_info_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_actual_values2_amk_temp_igbt_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values2_amk_temp_igbt_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values2_amk_temp_igbt_is_in_range(int16_t value);

/**
 * Pack message AMK1_ActualValues1.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int can_amk_inverter_amk1_actual_values1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk1_actual_values1_t *src_p,
    size_t size);

/**
 * Unpack message AMK1_ActualValues1.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int can_amk_inverter_amk1_actual_values1_unpack(
    struct can_amk_inverter_amk1_actual_values1_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_system_ready_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_system_ready_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_system_ready_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_error_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_error_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_error_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_warn_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_warn_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_warn_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_quit_dc_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_quit_dc_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_quit_dc_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_dc_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_dc_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_dc_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_quit_inverter_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_quit_inverter_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_quit_inverter_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_inverter_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_inverter_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_inverter_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk1_actual_values1_amk_b_derating_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_b_derating_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_b_derating_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_actual_values1_amk_actual_velocity_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_actual_velocity_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_actual_velocity_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_actual_values1_amk_torque_current_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_torque_current_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_torque_current_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk1_actual_values1_amk_magnetizing_current_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk1_actual_values1_amk_magnetizing_current_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk1_actual_values1_amk_magnetizing_current_is_in_range(int16_t value);

/**
 * Pack message AMK0_ActualValues1.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int can_amk_inverter_amk0_actual_values1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk0_actual_values1_t *src_p,
    size_t size);

/**
 * Unpack message AMK0_ActualValues1.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int can_amk_inverter_amk0_actual_values1_unpack(
    struct can_amk_inverter_amk0_actual_values1_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_system_ready_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_system_ready_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_system_ready_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_error_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_error_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_error_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_warn_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_warn_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_warn_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_quit_dc_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_quit_dc_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_quit_dc_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_dc_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_dc_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_dc_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_quit_inverter_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_quit_inverter_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_quit_inverter_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_inverter_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_inverter_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_inverter_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_actual_values1_amk_b_derating_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_b_derating_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_b_derating_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_actual_values1_amk_actual_velocity_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_actual_velocity_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_actual_velocity_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_actual_values1_amk_torque_current_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_torque_current_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_torque_current_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_actual_values1_amk_magnetizing_current_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values1_amk_magnetizing_current_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values1_amk_magnetizing_current_is_in_range(int16_t value);

/**
 * Pack message AMK0_ActualValues2.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int can_amk_inverter_amk0_actual_values2_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk0_actual_values2_t *src_p,
    size_t size);

/**
 * Unpack message AMK0_ActualValues2.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int can_amk_inverter_amk0_actual_values2_unpack(
    struct can_amk_inverter_amk0_actual_values2_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_actual_values2_amk_temp_motor_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values2_amk_temp_motor_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values2_amk_temp_motor_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_actual_values2_amk_temp_inverter_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values2_amk_temp_inverter_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values2_amk_temp_inverter_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t can_amk_inverter_amk0_actual_values2_amk_error_info_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values2_amk_error_info_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values2_amk_error_info_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_actual_values2_amk_temp_igbt_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_actual_values2_amk_temp_igbt_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_actual_values2_amk_temp_igbt_is_in_range(int16_t value);

/**
 * Pack message AMK0_SetPoints1.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int can_amk_inverter_amk0_set_points1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk0_set_points1_t *src_p,
    size_t size);

/**
 * Unpack message AMK0_SetPoints1.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int can_amk_inverter_amk0_set_points1_unpack(
    struct can_amk_inverter_amk0_set_points1_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_set_points1_amk_b_inverter_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_b_inverter_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_b_inverter_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_set_points1_amk_b_dc_on_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_b_dc_on_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_b_dc_on_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_set_points1_amk_b_enable_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_b_enable_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_b_enable_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint8_t can_amk_inverter_amk0_set_points1_amk_b_error_reset_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_b_error_reset_decode(uint8_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_b_error_reset_is_in_range(uint8_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_set_points1_amk_target_velocity_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_target_velocity_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_target_velocity_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_set_points1_amk_torque_limit_positiv_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_torque_limit_positiv_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_torque_limit_positiv_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t can_amk_inverter_amk0_set_points1_amk_torque_limit_negativ_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double can_amk_inverter_amk0_set_points1_amk_torque_limit_negativ_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool can_amk_inverter_amk0_set_points1_amk_torque_limit_negativ_is_in_range(int16_t value);


#ifdef __cplusplus
}
#endif

#endif
