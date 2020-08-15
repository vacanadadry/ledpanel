#include <stdint.h>
#include <stdbool.h>
#include "shinonome.h"

#ifndef PORTB
#define PORTB           (*(volatile uint32_t*)(0x00001000))        // こういう定義がある？
#define PORTC           (*(volatile uint32_t*)(0x00001004))        // こういう定義がある？
#endif

#define PINMASK_ONBOARDLED      (1 << 5)      // PB5

void lcdpanel_control(void);

/**
 * @brief レジスタの初期設定とかするんちゃうか？しらんけど
 */
void setup(void)
{
    pinMode(13, OUTPUT);   // 13: オンボードLED

    /* PORTB */
    pinMode(8, OUTPUT);    // 08: PB0: DG
    pinMode(9, OUTPUT);    // 09: PB1: CLK
    pinMode(10, OUTPUT);   // 10: PB2: WE
    pinMode(11, OUTPUT);   // 11: PB3: DR
    pinMode(12, OUTPUT);   // 12: PB4: ALE

    /* PORTC */
    pinMode(14, OUTPUT);   // 14: PC0: A0
    pinMode(15, OUTPUT);   // 15: PC1: A1
    pinMode(16, OUTPUT);   // 16: PC2: A2
    pinMode(17, OUTPUT);   // 17: PC3: A3
    pinMode(18, OUTPUT);   // 18: PC4: SE
    pinMode(19, OUTPUT);   // 19: PC5: A/B
  
    _delay_ms(100);     // パネルパワーオンリセット待ち

    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(300);     // パネルパワーオンリセット待ち
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(300);     // パネルパワーオンリセット待ち
    
    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(300);     // パネルパワーオンリセット待ち
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(300);     // パネルパワーオンリセット待ち

    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(300);     // パネルパワーオンリセット待ち
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(300);     // パネルパワーオンリセット待ち    
}


/**
 * @brief 周期処理
 */
void loop(void)
{
    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(100);     // パネルパワーオンリセット待ち
    lcdpanel_control();
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(100);     // パネルパワーオンリセット待ち    
}

// --
#if 1
// 最大32256バイトのフラッシュメモリのうち、スケッチが1014バイト（3%）を使っています。
// 最大2048バイトのRAMのうち、グローバル変数が73バイト（3%）を使っていて、ローカル変数で1975バイト使うことができます。
uint16_t symbol_add[] = FONT_CODE_0X215C;
uint16_t symbol_mul[] = FONT_CODE_0X215F;

uint16_t alphabet_v[] = FONT_CODE_0X2376;
uint16_t alphabet_a[] = FONT_CODE_0X2361;
uint16_t alphabet_c[] = FONT_CODE_0X2363;
uint16_t hiragana_na[] = FONT_CODE_0X244A;
uint16_t hiragana_da[] = FONT_CODE_0X2440;
#else
// 最大32256バイトのフラッシュメモリのうち、スケッチが992バイト（3%）を使っています。
// 最大2048バイトのRAMのうち、グローバル変数が9バイト（0%）を使っていて、ローカル変数で2039バイト使うことができます。
const PROGMEM uint16_t symbol_add[] = FONT_CODE_0X215C;
const PROGMEM uint16_t symbol_mul[] = FONT_CODE_0X215F;

const PROGMEM uint16_t alphabet_v[] = FONT_CODE_0X2376;
const PROGMEM uint16_t alphabet_a[] = FONT_CODE_0X2361;
const PROGMEM uint16_t alphabet_c[] = FONT_CODE_0X2363;
const PROGMEM uint16_t hiragana_na[] = FONT_CODE_0X244A;
const PROGMEM uint16_t hiragana_da[] = FONT_CODE_0X2440;
#endif

/* PORTC用定義 */
#define PINMASK_SE      (1 << 5)        // 内部バッファRAM 切り替えモード選択(Hi=手動, Lo=自動)
#define PINMASK_AB      (1 << 4)        // RAM-A(Hi) / RAM-B(Lo) 選択

/* PORTB用定義 */
#define PINMASK_DG      (1 << 0)        // 緑表示データ出力
#define PINMASK_CLK     (1 << 1)        // クロック(立下り変化、立上り取込)
#define PINMASK_WE      (1 << 2)        // 書き込み許可
#define PINMASK_DR      (1 << 3)        // 赤表示データ出力
#define PINMASK_ALE     (1 << 4)        // アドレスラッチ有効

// #define NUM_PANEL       (3U)        // パネル枚数(3枚買った)
#define NUM_PANEL       (1U)        // パネル枚数(1枚でテスト)

static void send_data(uint8_t iaddr_y, uint32_t *idata_r, uint32_t *idata_g);

void lcdpanel_control(void)
{
    uint32_t r_line[NUM_PANEL];
    uint32_t g_line[NUM_PANEL];

    /* "vc"出力 */
    for(uint8_t line=0; line<16; line++)
    {
        r_line[0] = ((uint32_t)alphabet_v[line] << 16) | alphabet_a[line];
        g_line[0] = ((uint32_t)alphabet_v[line] << 16) | alphabet_a[line];
        send_data(line, r_line, g_line);
    }
    _delay_ms(1000);

    for(uint8_t line=0; line<16; line++)
    {
        r_line[0] = ((uint32_t)alphabet_c[line] << 16) | alphabet_a[line];
        g_line[0] = ((uint32_t)alphabet_c[line] << 16) | alphabet_a[line];
        send_data(line, r_line, g_line);
    }
    _delay_ms(1000);

    for(uint8_t line=0; line<16; line++)
    {
        r_line[0] = ((uint32_t)hiragana_na[line] << 16) | hiragana_da[line];
        g_line[0] = ((uint32_t)hiragana_na[line] << 16) | hiragana_da[line];        
        send_data(line, r_line, g_line);
    }
    _delay_ms(1000);

}

/**
 * @brief 1行ぶんの送信処理
 * @param[in]   iaddr_y 行目(4bit:0～15)
 * @param[in]   *idata_r 赤色32bit分データへのポインタ (複数パネル時:配列)
 * @param[in]   *idata_g 緑色32bit分データへのポインタ (複数パネル時:配列)
 */
static void send_data(uint8_t iaddr_y, uint32_t *idata_r, uint32_t *idata_g)
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

            /* 次のデータ */
            r_line = r_line << 1;
            g_line = g_line << 1;
            
            /* CLK=Hi (立上り取込) */
            PORTB = PORTB | (PINMASK_CLK);
        }
        
        /* 書き込むRAMのアドレスセット */
        PORTC = PORTC & 0xF0;
        PORTC = PORTC | (iaddr_y & 0x0F);

        /* アドレスラッチ = H */
        PORTB = PORTB | (PINMASK_ALE);

        /* 書き込み信号を与える */
        PORTB = PORTB | (PINMASK_WE);          // WE=H
        // TODO: ノーウェイトでいいのか？
        PORTB = PORTB & ~(PINMASK_WE);         // WE=L

        /* アドレスラッチを戻してフィニッシュ */
        PORTB = PORTB & ~(PINMASK_ALE);
    }
}

#if 0
static void cat_twochar(uint16_t *first, uint16_t *second, uint32_t *result)
{
    for(int lc=0; lc<16; lc++)
    {
        result[lc] = ((uint32_t)first[lc] << (sizeof(uint16_t)*8)) | second[lc];
    }
}
#endif
