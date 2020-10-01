#include <avr/pgmspace.h>
#include <avr/io.h>
#include "config.h"
#include "panelcontrol.h"

/* PORTC用定義 */
#define PINMASK_SE      (1 << 5)        // 内部バッファRAM 切り替えモード選択(Hi=手動, Lo=自動)
#define PINMASK_AB      (1 << 4)        // RAM-A(Hi) / RAM-B(Lo) 選択

/* PORTB用定義 */
#define PINMASK_DG      (1 << 0)        // 緑表示データ出力
#define PINMASK_CLK     (1 << 1)        // クロック(立下り変化、立上り取込)
#define PINMASK_WE      (1 << 2)        // 書き込み許可
#define PINMASK_DR      (1 << 3)        // 赤表示データ出力
#define PINMASK_ALE     (1 << 4)        // アドレスラッチ有効


static void send_oneline(uint8_t iaddr_y, uint32_t *idata_r, uint32_t *idata_g);

/**
 * @brief 1文字データ(16x16 bit)を、任意の位置に張り付け
 * @param[in,out]   *dst_data 赤表示データ（パネル枚数*64byte）
 * @param[in]       *src_char 張り付ける1文字ぶんのデータ
 * @param[in]       h_offset   水平貼り付け位置 (左から h_offset 列だけ位置シフトした位置に張り付ける)
 * @param[in]       v_offset   垂直貼り付け位置 (上から v_offset 行だけ位置シフトした位置に張り付ける)
 * @note ようはバイト境界をまたぐビットシフト。ワープはしない。
 */
void copyCharToBinary(uint8_t *dst_data, uint16_t *src_char, int16_t h_offset, int8_t v_offset)
{
    // One Line length(bit) = 32bit(4byte) * NUM_PANEL

    // 水平シフト計算
    int16_t h_shift_byte;
    int8_t h_shift_bit;
    direction_t h_dir;
    if(h_offset < 0)
    {
        h_dir = DIRECTION_LEFT;
        h_offset = -h_offset;
    }
    else
    {
        h_dir = DIRECTION_RIGHT;
    }
    h_shift_byte = h_offset / 8;        // 1
    h_shift_bit = h_offset % 8;         // 7

#if 0
    // TODO: 垂直シフト計算: そのうち作る
    int8_t v_shift_bit;
    direction_t v_dir;
    if(v_offset < 0)
    {
        v_dir = DIRECTION_UP;
        v_offset = -v_offset;
    }
    else
    {
        v_dir = DIRECTION_DOWN;
    }
    v_shift_bit = v_offset;
#endif
    
    if(h_dir == DIRECTION_RIGHT)
    {
        for(uint8_t lc=0; lc<NUM_LINES; lc++)
        {
            uint16_t paste_pos = h_shift_byte + (lc * NUM_PANEL * 4);

            dst_data[paste_pos + 0] |=  (uint8_t)((src_char[lc] >> 8) & 0x00FF) >> (h_shift_bit);       // uint16_tの上8bitを右shift_bitビットシフト(下shift_bitビット落と)して+0バイト目セット
            
            if (!((paste_pos+1) % (NUM_PANEL*4)))
            {
                continue;
            }
            dst_data[paste_pos + 1] |=  (uint8_t)((src_char[lc] >> 8) & 0x00FF) << (8 - h_shift_bit);   // uint16_tの上8bitの下shift_bitビットを先頭に→ 左に(8-shift_bit)ビットシフトして+1バイト目にセット
            dst_data[paste_pos + 1] |=  (uint8_t)((src_char[lc] >> 0) & 0x00FF) >> (h_shift_bit);       // uint16_tの下8bitの下shift_bitビットをその後ろ → 右にshift_bitビットシフトしてORでセット
            
            if (!((paste_pos+2) % (NUM_PANEL*4)))
            {
                continue;
            }
            dst_data[paste_pos + 2] |=  (uint8_t)((src_char[lc] >> 0) & 0x00FF) << (8 - h_shift_bit);   // uint16_tの下8bitの下shift_bitビットを先頭に→ 左に(8-shift_bit)ビットシフトして+2バイト目にセット
        }
    }
    else
    {
        for(uint8_t lc=0; lc<NUM_LINES; lc++)
        {
            int16_t paste_pos = (lc * NUM_PANEL * 4) - h_shift_byte;        // -1

            if(paste_pos+2 < 0) continue;   // 1
            dst_data[paste_pos + 2] |=  (uint8_t)((src_char[lc] >> 0) & 0x00FF) << (h_shift_bit);   // uint16_tの下8bitの下shift_bitビットを先頭に→ 左に(8-shift_bit)ビットシフトして+2バイト目にセット
            if(paste_pos+1 < 0) continue;   // 0
            dst_data[paste_pos + 1] |=  (uint8_t)((src_char[lc] >> 0) & 0x00FF) >> (8 - h_shift_bit);       // uint16_tの下8bitの下shift_bitビットをその後ろ → 右にshift_bitビットシフトしてORでセット
            dst_data[paste_pos + 1] |=  (uint8_t)((src_char[lc] >> 8) & 0x00FF) << (h_shift_bit);   // uint16_tの上8bitの下shift_bitビットを先頭に→ 左に(8-shift_bit)ビットシフトして+1バイト目にセット
            if(paste_pos+0 < 0) continue;   // -1
            dst_data[paste_pos + 0] |=  (uint8_t)((src_char[lc] >> 8) & 0x00FF) >> (8 - h_shift_bit);       // uint16_tの上8bitを右shift_bitビットシフト(下shift_bitビット落と)して+0バイト目セット
        }
    }
}

/**
 * @brief uint8_t x4 を uint32_t にエンディアン変換するやつ
 * @todo マクロで作り変えたほうがいいかな
 */
void loadchar(const uint16_t *src, uint16_t *dst)
{
    do{ for(uint8_t lc=0; lc<NUM_LINES; lc++) dst[lc] = pgm_read_word_near(&(src[lc])); } while(0);
}

/**
 * @brief uint8_t x4 を uint32_t にエンディアン変換するやつ
 */
void u32nizer(uint8_t* data)
{
    uint32_t tmp;
    for(uint8_t line=0; line<NUM_LINES; line++)
    {
        uint16_t lines_offset = 4 * line * NUM_PANEL;
        for(uint8_t lc=0; lc<NUM_PANEL; lc++)
        {
            tmp = *(uint32_t*)&(data[lines_offset + lc*4]);
    #if 0   
            /* BIG ENDIAN */
            data[lines_offset + (lc*4) + 0] = (uint8_t)((tmp >>  0) & 0x000000FF);
            data[lines_offset + (lc*4) + 1] = (uint8_t)((tmp >>  8) & 0x000000FF);
            data[lines_offset + (lc*4) + 2] = (uint8_t)((tmp >> 16) & 0x000000FF);
            data[lines_offset + (lc*4) + 3] = (uint8_t)((tmp >> 24) & 0x000000FF);
    #else
            /* LITTLE ENDIAN */
            data[lines_offset + (lc*4) + 0] = (uint8_t)((tmp >> 24) & 0x000000FF);
            data[lines_offset + (lc*4) + 1] = (uint8_t)((tmp >> 16) & 0x000000FF);
            data[lines_offset + (lc*4) + 2] = (uint8_t)((tmp >>  8) & 0x000000FF);
            data[lines_offset + (lc*4) + 3] = (uint8_t)((tmp >>  0) & 0x000000FF);
    #endif
        }
    }
}


/**
 * @brief 1画面ぶんの送信処理（バイナリ）
 * @param[in]   *data_r 赤表示データ（パネル枚数*64byte）
 * @param[in]   *data_g 緑表示データ（パネル枚数*64byte）
 * @note パネル枚数とdata_r / data_gのサイズに注意すること。バッファオーバーランの可能性あり。
 */
void displayByBinary(uint8_t *data_r, uint8_t *data_g)
{
    uint8_t r_line[NUM_PANEL*4] = {0};
    uint8_t g_line[NUM_PANEL*4] = {0};

    for(uint8_t line=0; line<NUM_LINES; line++)
    {
        for(uint8_t pos=0; pos<NUM_PANEL*4; pos++)
        {
            r_line[pos] = data_r[line*(NUM_PANEL*4) + pos];      // 1行につき32bit(4byte) * パネル枚数なので
            g_line[pos] = data_g[line*(NUM_PANEL*4) + pos];
        }
    
        send_oneline(line, (void*)r_line, (void*)g_line);
    }

    return;    
}

/**
 * @brief 1行ぶんの送信処理
 * @param[in]   iaddr_y 行目(4bit:0～15)
 * @param[in]   *idata_r 赤色32bit分データへのポインタ (複数パネル時:配列)
 * @param[in]   *idata_g 緑色32bit分データへのポインタ (複数パネル時:配列)
 */
static void send_oneline(uint8_t iaddr_y, uint32_t *idata_r, uint32_t *idata_g)
{
    int32_t i,j;
    uint32_t r_line;
    uint32_t g_line;

    for(i=0; i<NUM_PANEL; i++)
    {
        r_line = idata_r[i];
        g_line = idata_g[i];

        /* 32ビット(パネル1枚の1行分)の表示データを、下位ビットから順番に送る */
        for(j=0; j<32; j++)
        {
            /* CLK=Lo (立下り変化) */
            PORTB = PORTB & ~(PINMASK_CLK);
            
            /* データビット(DR/DG)をセット */
            PORTB = PORTB & ~(PINMASK_DR | PINMASK_DG);         // まずビット落として
            if((r_line & 0x80000000UL) != 0)                    // ビットを立てる必要があるなら立てる
            {
                PORTB = PORTB | (PINMASK_DR);
            }
            if((g_line & 0x80000000UL) != 0)                    // DG分もおなじ。
            {
                PORTB = PORTB | (PINMASK_DG);
            }

            /* CLK=Hi (立上り取込) */
            PORTB = PORTB | (PINMASK_CLK);

            /* 次のデータ */
            r_line = r_line << 1;
            g_line = g_line << 1;
        }
    }

    /* 書き込むRAMのアドレスセット */
    PORTC = PORTC & 0xF0;
    PORTC = PORTC | (iaddr_y & 0x0F);

    /* アドレスラッチ = H */
    PORTB = PORTB | (PINMASK_ALE);

    /* 書き込み信号を与える */
    PORTB = PORTB | (PINMASK_WE);          // WE=H
    PORTB = PORTB & ~(PINMASK_WE);         // WE=L

    /* アドレスラッチを戻してフィニッシュ */
    PORTB = PORTB & ~(PINMASK_ALE);
}
