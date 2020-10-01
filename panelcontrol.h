#ifndef __PANELCONTROL_H
#define __PANELCONTROL_H

#include <stdint.h>

#define NUM_LINES       (16U)           // パネルの表示行数 (16行)

typedef enum
{
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN,
}direction_t;

extern void copyCharToBinary(uint8_t *dst_data, uint16_t *src_char, int16_t h_offset, int8_t v_offset);
extern void loadchar(const uint16_t *src, uint16_t *dst);
extern void u32nizer(uint8_t* data);
extern void displayByBinary(uint8_t *data_r, uint8_t *data_g);

#endif
