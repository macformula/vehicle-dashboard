#include <string.h>
#include "can_msg.h"

static inline uint8_t pack_left_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_right_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint16_t unpack_left_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) << shift);
}

static inline uint8_t unpack_right_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value & mask) >> shift);
}

static inline uint16_t unpack_right_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) >> shift);
}

int can_amk_inverter_amk1_set_points1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk1_set_points1_t *src_p,
    size_t size)
{
    uint16_t amk_target_velocity;
    uint16_t amk_torque_limit_negativ;
    uint16_t amk_torque_limit_positiv;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_inverter_on, 0u, 0x01u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_dc_on, 1u, 0x02u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_enable, 2u, 0x04u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_error_reset, 3u, 0x08u);
    amk_target_velocity = (uint16_t)src_p->amk_target_velocity;
    dst_p[2] |= pack_left_shift_u16(amk_target_velocity, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(amk_target_velocity, 8u, 0xffu);
    amk_torque_limit_positiv = (uint16_t)src_p->amk_torque_limit_positiv;
    dst_p[4] |= pack_left_shift_u16(amk_torque_limit_positiv, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(amk_torque_limit_positiv, 8u, 0xffu);
    amk_torque_limit_negativ = (uint16_t)src_p->amk_torque_limit_negativ;
    dst_p[6] |= pack_left_shift_u16(amk_torque_limit_negativ, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(amk_torque_limit_negativ, 8u, 0xffu);

    return (8);
}

int can_amk_inverter_amk1_set_points1_unpack(
    struct can_amk_inverter_amk1_set_points1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t amk_target_velocity;
    uint16_t amk_torque_limit_negativ;
    uint16_t amk_torque_limit_positiv;

    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->amk_b_inverter_on = unpack_right_shift_u8(src_p[1], 0u, 0x01u);
    dst_p->amk_b_dc_on = unpack_right_shift_u8(src_p[1], 1u, 0x02u);
    dst_p->amk_b_enable = unpack_right_shift_u8(src_p[1], 2u, 0x04u);
    dst_p->amk_b_error_reset = unpack_right_shift_u8(src_p[1], 3u, 0x08u);
    amk_target_velocity = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    amk_target_velocity |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->amk_target_velocity = (int16_t)amk_target_velocity;
    amk_torque_limit_positiv = unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    amk_torque_limit_positiv |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    dst_p->amk_torque_limit_positiv = (int16_t)amk_torque_limit_positiv;
    amk_torque_limit_negativ = unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    amk_torque_limit_negativ |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);
    dst_p->amk_torque_limit_negativ = (int16_t)amk_torque_limit_negativ;

    return (0);
}

uint8_t can_amk_inverter_amk1_set_points1_amk_b_inverter_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_b_inverter_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_b_inverter_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_set_points1_amk_b_dc_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_b_dc_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_b_dc_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_set_points1_amk_b_enable_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_b_enable_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_b_enable_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_set_points1_amk_b_error_reset_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_b_error_reset_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_b_error_reset_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int16_t can_amk_inverter_amk1_set_points1_amk_target_velocity_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_target_velocity_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_target_velocity_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk1_set_points1_amk_torque_limit_positiv_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_torque_limit_positiv_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_torque_limit_positiv_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk1_set_points1_amk_torque_limit_negativ_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk1_set_points1_amk_torque_limit_negativ_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_set_points1_amk_torque_limit_negativ_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int can_amk_inverter_amk1_actual_values2_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk1_actual_values2_t *src_p,
    size_t size)
{
    uint16_t amk_temp_igbt;
    uint16_t amk_temp_inverter;
    uint16_t amk_temp_motor;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    amk_temp_motor = (uint16_t)src_p->amk_temp_motor;
    dst_p[0] |= pack_left_shift_u16(amk_temp_motor, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u16(amk_temp_motor, 8u, 0xffu);
    amk_temp_inverter = (uint16_t)src_p->amk_temp_inverter;
    dst_p[2] |= pack_left_shift_u16(amk_temp_inverter, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(amk_temp_inverter, 8u, 0xffu);
    dst_p[4] |= pack_left_shift_u16(src_p->amk_error_info, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(src_p->amk_error_info, 8u, 0xffu);
    amk_temp_igbt = (uint16_t)src_p->amk_temp_igbt;
    dst_p[6] |= pack_left_shift_u16(amk_temp_igbt, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(amk_temp_igbt, 8u, 0xffu);

    return (8);
}

int can_amk_inverter_amk1_actual_values2_unpack(
    struct can_amk_inverter_amk1_actual_values2_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t amk_temp_igbt;
    uint16_t amk_temp_inverter;
    uint16_t amk_temp_motor;

    if (size < 8u) {
        return (-EINVAL);
    }

    amk_temp_motor = unpack_right_shift_u16(src_p[0], 0u, 0xffu);
    amk_temp_motor |= unpack_left_shift_u16(src_p[1], 8u, 0xffu);
    dst_p->amk_temp_motor = (int16_t)amk_temp_motor;
    amk_temp_inverter = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    amk_temp_inverter |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->amk_temp_inverter = (int16_t)amk_temp_inverter;
    dst_p->amk_error_info = unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    dst_p->amk_error_info |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    amk_temp_igbt = unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    amk_temp_igbt |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);
    dst_p->amk_temp_igbt = (int16_t)amk_temp_igbt;

    return (0);
}

int16_t can_amk_inverter_amk1_actual_values2_amk_temp_motor_encode(double value)
{
    return (int16_t)(value / 0.1);
}

double can_amk_inverter_amk1_actual_values2_amk_temp_motor_decode(int16_t value)
{
    return ((double)value * 0.1);
}

bool can_amk_inverter_amk1_actual_values2_amk_temp_motor_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk1_actual_values2_amk_temp_inverter_encode(double value)
{
    return (int16_t)(value / 0.1);
}

double can_amk_inverter_amk1_actual_values2_amk_temp_inverter_decode(int16_t value)
{
    return ((double)value * 0.1);
}

bool can_amk_inverter_amk1_actual_values2_amk_temp_inverter_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

uint16_t can_amk_inverter_amk1_actual_values2_amk_error_info_encode(double value)
{
    return (uint16_t)(value);
}

double can_amk_inverter_amk1_actual_values2_amk_error_info_decode(uint16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values2_amk_error_info_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk1_actual_values2_amk_temp_igbt_encode(double value)
{
    return (int16_t)(value / 0.1);
}

double can_amk_inverter_amk1_actual_values2_amk_temp_igbt_decode(int16_t value)
{
    return ((double)value * 0.1);
}

bool can_amk_inverter_amk1_actual_values2_amk_temp_igbt_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int can_amk_inverter_amk1_actual_values1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk1_actual_values1_t *src_p,
    size_t size)
{
    uint16_t amk_actual_velocity;
    uint16_t amk_magnetizing_current;
    uint16_t amk_torque_current;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_system_ready, 0u, 0x01u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_error, 1u, 0x02u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_warn, 2u, 0x04u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_quit_dc_on, 3u, 0x08u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_dc_on, 4u, 0x10u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_quit_inverter_on, 5u, 0x20u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_inverter_on, 6u, 0x40u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_derating, 7u, 0x80u);
    amk_actual_velocity = (uint16_t)src_p->amk_actual_velocity;
    dst_p[2] |= pack_left_shift_u16(amk_actual_velocity, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(amk_actual_velocity, 8u, 0xffu);
    amk_torque_current = (uint16_t)src_p->amk_torque_current;
    dst_p[4] |= pack_left_shift_u16(amk_torque_current, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(amk_torque_current, 8u, 0xffu);
    amk_magnetizing_current = (uint16_t)src_p->amk_magnetizing_current;
    dst_p[6] |= pack_left_shift_u16(amk_magnetizing_current, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(amk_magnetizing_current, 8u, 0xffu);

    return (8);
}

int can_amk_inverter_amk1_actual_values1_unpack(
    struct can_amk_inverter_amk1_actual_values1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t amk_actual_velocity;
    uint16_t amk_magnetizing_current;
    uint16_t amk_torque_current;

    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->amk_b_system_ready = unpack_right_shift_u8(src_p[1], 0u, 0x01u);
    dst_p->amk_b_error = unpack_right_shift_u8(src_p[1], 1u, 0x02u);
    dst_p->amk_b_warn = unpack_right_shift_u8(src_p[1], 2u, 0x04u);
    dst_p->amk_b_quit_dc_on = unpack_right_shift_u8(src_p[1], 3u, 0x08u);
    dst_p->amk_b_dc_on = unpack_right_shift_u8(src_p[1], 4u, 0x10u);
    dst_p->amk_b_quit_inverter_on = unpack_right_shift_u8(src_p[1], 5u, 0x20u);
    dst_p->amk_b_inverter_on = unpack_right_shift_u8(src_p[1], 6u, 0x40u);
    dst_p->amk_b_derating = unpack_right_shift_u8(src_p[1], 7u, 0x80u);
    amk_actual_velocity = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    amk_actual_velocity |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->amk_actual_velocity = (int16_t)amk_actual_velocity;
    amk_torque_current = unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    amk_torque_current |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    dst_p->amk_torque_current = (int16_t)amk_torque_current;
    amk_magnetizing_current = unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    amk_magnetizing_current |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);
    dst_p->amk_magnetizing_current = (int16_t)amk_magnetizing_current;

    return (0);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_system_ready_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_system_ready_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_system_ready_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_error_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_error_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_error_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_warn_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_warn_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_warn_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_quit_dc_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_quit_dc_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_quit_dc_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_dc_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_dc_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_dc_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_quit_inverter_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_quit_inverter_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_quit_inverter_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_inverter_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_inverter_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_inverter_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk1_actual_values1_amk_b_derating_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_b_derating_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_b_derating_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int16_t can_amk_inverter_amk1_actual_values1_amk_actual_velocity_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_actual_velocity_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_actual_velocity_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk1_actual_values1_amk_torque_current_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_torque_current_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_torque_current_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk1_actual_values1_amk_magnetizing_current_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk1_actual_values1_amk_magnetizing_current_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk1_actual_values1_amk_magnetizing_current_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int can_amk_inverter_amk0_actual_values1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk0_actual_values1_t *src_p,
    size_t size)
{
    uint16_t amk_actual_velocity;
    uint16_t amk_magnetizing_current;
    uint16_t amk_torque_current;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_system_ready, 0u, 0x01u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_error, 1u, 0x02u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_warn, 2u, 0x04u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_quit_dc_on, 3u, 0x08u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_dc_on, 4u, 0x10u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_quit_inverter_on, 5u, 0x20u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_inverter_on, 6u, 0x40u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_derating, 7u, 0x80u);
    amk_actual_velocity = (uint16_t)src_p->amk_actual_velocity;
    dst_p[2] |= pack_left_shift_u16(amk_actual_velocity, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(amk_actual_velocity, 8u, 0xffu);
    amk_torque_current = (uint16_t)src_p->amk_torque_current;
    dst_p[4] |= pack_left_shift_u16(amk_torque_current, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(amk_torque_current, 8u, 0xffu);
    amk_magnetizing_current = (uint16_t)src_p->amk_magnetizing_current;
    dst_p[6] |= pack_left_shift_u16(amk_magnetizing_current, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(amk_magnetizing_current, 8u, 0xffu);

    return (8);
}

int can_amk_inverter_amk0_actual_values1_unpack(
    struct can_amk_inverter_amk0_actual_values1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t amk_actual_velocity;
    uint16_t amk_magnetizing_current;
    uint16_t amk_torque_current;

    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->amk_b_system_ready = unpack_right_shift_u8(src_p[1], 0u, 0x01u);
    dst_p->amk_b_error = unpack_right_shift_u8(src_p[1], 1u, 0x02u);
    dst_p->amk_b_warn = unpack_right_shift_u8(src_p[1], 2u, 0x04u);
    dst_p->amk_b_quit_dc_on = unpack_right_shift_u8(src_p[1], 3u, 0x08u);
    dst_p->amk_b_dc_on = unpack_right_shift_u8(src_p[1], 4u, 0x10u);
    dst_p->amk_b_quit_inverter_on = unpack_right_shift_u8(src_p[1], 5u, 0x20u);
    dst_p->amk_b_inverter_on = unpack_right_shift_u8(src_p[1], 6u, 0x40u);
    dst_p->amk_b_derating = unpack_right_shift_u8(src_p[1], 7u, 0x80u);
    amk_actual_velocity = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    amk_actual_velocity |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->amk_actual_velocity = (int16_t)amk_actual_velocity;
    amk_torque_current = unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    amk_torque_current |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    dst_p->amk_torque_current = (int16_t)amk_torque_current;
    amk_magnetizing_current = unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    amk_magnetizing_current |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);
    dst_p->amk_magnetizing_current = (int16_t)amk_magnetizing_current;

    return (0);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_system_ready_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_system_ready_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_system_ready_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_error_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_error_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_error_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_warn_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_warn_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_warn_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_quit_dc_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_quit_dc_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_quit_dc_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_dc_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_dc_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_dc_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_quit_inverter_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_quit_inverter_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_quit_inverter_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_inverter_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_inverter_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_inverter_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_actual_values1_amk_b_derating_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_b_derating_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_b_derating_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int16_t can_amk_inverter_amk0_actual_values1_amk_actual_velocity_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_actual_velocity_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_actual_velocity_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk0_actual_values1_amk_torque_current_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_torque_current_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_torque_current_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk0_actual_values1_amk_magnetizing_current_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk0_actual_values1_amk_magnetizing_current_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values1_amk_magnetizing_current_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int can_amk_inverter_amk0_actual_values2_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk0_actual_values2_t *src_p,
    size_t size)
{
    uint16_t amk_temp_igbt;
    uint16_t amk_temp_inverter;
    uint16_t amk_temp_motor;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    amk_temp_motor = (uint16_t)src_p->amk_temp_motor;
    dst_p[0] |= pack_left_shift_u16(amk_temp_motor, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u16(amk_temp_motor, 8u, 0xffu);
    amk_temp_inverter = (uint16_t)src_p->amk_temp_inverter;
    dst_p[2] |= pack_left_shift_u16(amk_temp_inverter, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(amk_temp_inverter, 8u, 0xffu);
    dst_p[4] |= pack_left_shift_u16(src_p->amk_error_info, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(src_p->amk_error_info, 8u, 0xffu);
    amk_temp_igbt = (uint16_t)src_p->amk_temp_igbt;
    dst_p[6] |= pack_left_shift_u16(amk_temp_igbt, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(amk_temp_igbt, 8u, 0xffu);

    return (8);
}

int can_amk_inverter_amk0_actual_values2_unpack(
    struct can_amk_inverter_amk0_actual_values2_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t amk_temp_igbt;
    uint16_t amk_temp_inverter;
    uint16_t amk_temp_motor;

    if (size < 8u) {
        return (-EINVAL);
    }

    amk_temp_motor = unpack_right_shift_u16(src_p[0], 0u, 0xffu);
    amk_temp_motor |= unpack_left_shift_u16(src_p[1], 8u, 0xffu);
    dst_p->amk_temp_motor = (int16_t)amk_temp_motor;
    amk_temp_inverter = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    amk_temp_inverter |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->amk_temp_inverter = (int16_t)amk_temp_inverter;
    dst_p->amk_error_info = unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    dst_p->amk_error_info |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    amk_temp_igbt = unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    amk_temp_igbt |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);
    dst_p->amk_temp_igbt = (int16_t)amk_temp_igbt;

    return (0);
}

int16_t can_amk_inverter_amk0_actual_values2_amk_temp_motor_encode(double value)
{
    return (int16_t)(value / 0.1);
}

double can_amk_inverter_amk0_actual_values2_amk_temp_motor_decode(int16_t value)
{
    return ((double)value * 0.1);
}

bool can_amk_inverter_amk0_actual_values2_amk_temp_motor_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk0_actual_values2_amk_temp_inverter_encode(double value)
{
    return (int16_t)(value / 0.1);
}

double can_amk_inverter_amk0_actual_values2_amk_temp_inverter_decode(int16_t value)
{
    return ((double)value * 0.1);
}

bool can_amk_inverter_amk0_actual_values2_amk_temp_inverter_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

uint16_t can_amk_inverter_amk0_actual_values2_amk_error_info_encode(double value)
{
    return (uint16_t)(value);
}

double can_amk_inverter_amk0_actual_values2_amk_error_info_decode(uint16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_actual_values2_amk_error_info_is_in_range(uint16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk0_actual_values2_amk_temp_igbt_encode(double value)
{
    return (int16_t)(value / 0.1);
}

double can_amk_inverter_amk0_actual_values2_amk_temp_igbt_decode(int16_t value)
{
    return ((double)value * 0.1);
}

bool can_amk_inverter_amk0_actual_values2_amk_temp_igbt_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int can_amk_inverter_amk0_set_points1_pack(
    uint8_t *dst_p,
    const struct can_amk_inverter_amk0_set_points1_t *src_p,
    size_t size)
{
    uint16_t amk_target_velocity;
    uint16_t amk_torque_limit_negativ;
    uint16_t amk_torque_limit_positiv;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8);

    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_inverter_on, 0u, 0x01u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_dc_on, 1u, 0x02u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_enable, 2u, 0x04u);
    dst_p[1] |= pack_left_shift_u8(src_p->amk_b_error_reset, 3u, 0x08u);
    amk_target_velocity = (uint16_t)src_p->amk_target_velocity;
    dst_p[2] |= pack_left_shift_u16(amk_target_velocity, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(amk_target_velocity, 8u, 0xffu);
    amk_torque_limit_positiv = (uint16_t)src_p->amk_torque_limit_positiv;
    dst_p[4] |= pack_left_shift_u16(amk_torque_limit_positiv, 0u, 0xffu);
    dst_p[5] |= pack_right_shift_u16(amk_torque_limit_positiv, 8u, 0xffu);
    amk_torque_limit_negativ = (uint16_t)src_p->amk_torque_limit_negativ;
    dst_p[6] |= pack_left_shift_u16(amk_torque_limit_negativ, 0u, 0xffu);
    dst_p[7] |= pack_right_shift_u16(amk_torque_limit_negativ, 8u, 0xffu);

    return (8);
}

int can_amk_inverter_amk0_set_points1_unpack(
    struct can_amk_inverter_amk0_set_points1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t amk_target_velocity;
    uint16_t amk_torque_limit_negativ;
    uint16_t amk_torque_limit_positiv;

    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->amk_b_inverter_on = unpack_right_shift_u8(src_p[1], 0u, 0x01u);
    dst_p->amk_b_dc_on = unpack_right_shift_u8(src_p[1], 1u, 0x02u);
    dst_p->amk_b_enable = unpack_right_shift_u8(src_p[1], 2u, 0x04u);
    dst_p->amk_b_error_reset = unpack_right_shift_u8(src_p[1], 3u, 0x08u);
    amk_target_velocity = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    amk_target_velocity |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->amk_target_velocity = (int16_t)amk_target_velocity;
    amk_torque_limit_positiv = unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    amk_torque_limit_positiv |= unpack_left_shift_u16(src_p[5], 8u, 0xffu);
    dst_p->amk_torque_limit_positiv = (int16_t)amk_torque_limit_positiv;
    amk_torque_limit_negativ = unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    amk_torque_limit_negativ |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);
    dst_p->amk_torque_limit_negativ = (int16_t)amk_torque_limit_negativ;

    return (0);
}

uint8_t can_amk_inverter_amk0_set_points1_amk_b_inverter_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_b_inverter_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_b_inverter_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_set_points1_amk_b_dc_on_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_b_dc_on_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_b_dc_on_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_set_points1_amk_b_enable_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_b_enable_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_b_enable_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

uint8_t can_amk_inverter_amk0_set_points1_amk_b_error_reset_encode(double value)
{
    return (uint8_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_b_error_reset_decode(uint8_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_b_error_reset_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

int16_t can_amk_inverter_amk0_set_points1_amk_target_velocity_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_target_velocity_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_target_velocity_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk0_set_points1_amk_torque_limit_positiv_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_torque_limit_positiv_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_torque_limit_positiv_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}

int16_t can_amk_inverter_amk0_set_points1_amk_torque_limit_negativ_encode(double value)
{
    return (int16_t)(value);
}

double can_amk_inverter_amk0_set_points1_amk_torque_limit_negativ_decode(int16_t value)
{
    return ((double)value);
}

bool can_amk_inverter_amk0_set_points1_amk_torque_limit_negativ_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}
