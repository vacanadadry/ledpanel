#include <stdint.h>
#include <stdbool.h>
#include "shinonome.h"

#ifndef PORTB
#define PORTB           (*(volatile uint32_t*)(0x00001000))        // こういう定義がある？
#define PORTC           (*(volatile uint32_t*)(0x00001004))        // こういう定義がある？
#endif

#define PINMASK_ONBOARDLED      (1 << 5)      // PB5
#define ACTIVITY_CHECK          do{ PORTB = PORTB & ~(PINMASK_ONBOARDLED); _delay_ms(100); PORTB = PORTB | PINMASK_ONBOARDLED; }

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
  

    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(300);
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(300);
    
    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(300);
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(300);

    PORTB = PORTB & ~(PINMASK_ONBOARDLED);
    _delay_ms(300);
    PORTB = PORTB | PINMASK_ONBOARDLED;
    _delay_ms(300);    

    // PORTC = PORTC | (1 << 4);       // SE=Hi (自動切換え無効)
    PORTC = PORTC & ~(1 << 4);       // SE=Lo (自動切換え有効)
}


/**
 * @brief 周期処理
 */
void loop(void)
{
    PORTB = PORTB ^ PINMASK_ONBOARDLED;
    lcdpanel_control();
}

// --
#if 0
uint16_t alphabet_A[] = FONT_CODE_0X2341;    // (Ａ)[ascii:u-0041]
uint16_t alphabet_B[] = FONT_CODE_0X2342;    // (Ｂ)[ascii:u-0042]
uint16_t alphabet_C[] = FONT_CODE_0X2343;    // (Ｃ)[ascii:u-0043]
uint16_t alphabet_D[] = FONT_CODE_0X2344;    // (Ｄ)[ascii:u-0044]
uint16_t alphabet_E[] = FONT_CODE_0X2345;    // (Ｅ)[ascii:u-0045]
uint16_t alphabet_F[] = FONT_CODE_0X2346;    // (Ｆ)[ascii:u-0046]
uint16_t alphabet_G[] = FONT_CODE_0X2347;    // (Ｇ)[ascii:u-0047]
uint16_t alphabet_H[] = FONT_CODE_0X2348;    // (Ｈ)[ascii:u-0048]
uint16_t alphabet_I[] = FONT_CODE_0X2349;    // (Ｉ)[ascii:u-0049]
uint16_t alphabet_J[] = FONT_CODE_0X234A;    // (Ｊ)[ascii:u-004a]
uint16_t alphabet_K[] = FONT_CODE_0X234B;    // (Ｋ)[ascii:u-004b]
uint16_t alphabet_L[] = FONT_CODE_0X234C;    // (Ｌ)[ascii:u-004c]
uint16_t alphabet_M[] = FONT_CODE_0X234D;    // (Ｍ)[ascii:u-004d]
uint16_t alphabet_N[] = FONT_CODE_0X234E;    // (Ｎ)[ascii:u-004e]
uint16_t alphabet_O[] = FONT_CODE_0X234F;    // (Ｏ)[ascii:u-004f]
uint16_t alphabet_P[] = FONT_CODE_0X2350;    // (Ｐ)[ascii:u-0050]
uint16_t alphabet_Q[] = FONT_CODE_0X2351;    // (Ｑ)[ascii:u-0051]
uint16_t alphabet_R[] = FONT_CODE_0X2352;    // (Ｒ)[ascii:u-0052]
uint16_t alphabet_S[] = FONT_CODE_0X2353;    // (Ｓ)[ascii:u-0053]
uint16_t alphabet_T[] = FONT_CODE_0X2354;    // (Ｔ)[ascii:u-0054]
uint16_t alphabet_U[] = FONT_CODE_0X2355;    // (Ｕ)[ascii:u-0055]
uint16_t alphabet_V[] = FONT_CODE_0X2356;    // (Ｖ)[ascii:u-0056]
uint16_t alphabet_W[] = FONT_CODE_0X2357;    // (Ｗ)[ascii:u-0057]
uint16_t alphabet_X[] = FONT_CODE_0X2358;    // (Ｘ)[ascii:u-0058]
uint16_t alphabet_Y[] = FONT_CODE_0X2359;    // (Ｙ)[ascii:u-0059]
uint16_t alphabet_Z[] = FONT_CODE_0X235A;    // (Ｚ)[ascii:u-005a]
uint16_t alphabet_a[] = FONT_CODE_0X2361;    // (ａ)[ascii:u-0061]
uint16_t alphabet_b[] = FONT_CODE_0X2362;    // (ｂ)[ascii:u-0062]
uint16_t alphabet_c[] = FONT_CODE_0X2363;    // (ｃ)[ascii:u-0063]
uint16_t alphabet_d[] = FONT_CODE_0X2364;    // (ｄ)[ascii:u-0064]
uint16_t alphabet_e[] = FONT_CODE_0X2365;    // (ｅ)[ascii:u-0065]
uint16_t alphabet_f[] = FONT_CODE_0X2366;    // (ｆ)[ascii:u-0066]
uint16_t alphabet_g[] = FONT_CODE_0X2367;    // (ｇ)[ascii:u-0067]
uint16_t alphabet_h[] = FONT_CODE_0X2368;    // (ｈ)[ascii:u-0068]
uint16_t alphabet_i[] = FONT_CODE_0X2369;    // (ｉ)[ascii:u-0069]
uint16_t alphabet_j[] = FONT_CODE_0X236A;    // (ｊ)[ascii:u-006a]
uint16_t alphabet_k[] = FONT_CODE_0X236B;    // (ｋ)[ascii:u-006b]
uint16_t alphabet_l[] = FONT_CODE_0X236C;    // (ｌ)[ascii:u-006c]
uint16_t alphabet_m[] = FONT_CODE_0X236D;    // (ｍ)[ascii:u-006d]
uint16_t alphabet_n[] = FONT_CODE_0X236E;    // (ｎ)[ascii:u-006e]
uint16_t alphabet_o[] = FONT_CODE_0X236F;    // (ｏ)[ascii:u-006f]
uint16_t alphabet_p[] = FONT_CODE_0X2370;    // (ｐ)[ascii:u-0070]
uint16_t alphabet_q[] = FONT_CODE_0X2371;    // (ｑ)[ascii:u-0071]
uint16_t alphabet_r[] = FONT_CODE_0X2372;    // (ｒ)[ascii:u-0072]
uint16_t alphabet_s[] = FONT_CODE_0X2373;    // (ｓ)[ascii:u-0073]
uint16_t alphabet_t[] = FONT_CODE_0X2374;    // (ｔ)[ascii:u-0074]
uint16_t alphabet_u[] = FONT_CODE_0X2375;    // (ｕ)[ascii:u-0075]
uint16_t alphabet_v[] = FONT_CODE_0X2376;    // (ｖ)[ascii:u-0076]
uint16_t alphabet_w[] = FONT_CODE_0X2377;    // (ｗ)[ascii:u-0077]
uint16_t alphabet_x[] = FONT_CODE_0X2378;    // (ｘ)[ascii:u-0078]
uint16_t alphabet_y[] = FONT_CODE_0X2379;    // (ｙ)[ascii:u-0079]
uint16_t alphabet_z[] = FONT_CODE_0X237A;    // (ｚ)[ascii:u-007a]
#endif

uint16_t symbol_space[] =   FONT_CODE_0X2121; // (　)
uint16_t kanji_kyu[] =      FONT_CODE_0X355E; // (急)
uint16_t kanji_kou[] =      FONT_CODE_0X3954; // (行)
uint16_t kanji_mori[] =     FONT_CODE_0X4039; // (盛)
uint16_t kanji_oka[] =      FONT_CODE_0X322C; // (岡)

uint16_t kanji_tsugi[] =    FONT_CODE_0X3C21; // (次)
uint16_t hiragana_ha[] =    FONT_CODE_0X244F; // (は)
uint16_t kanji_asa[] =      FONT_CODE_0X4075; // (浅)
uint16_t kanji_kusa[] =     FONT_CODE_0X4170; // (草)

#if 0
uint16_t symbol_comma[]         = FONT_CODE_0X2124;   // (，)[ascii:u-002c]
uint16_t symbol_dot[]           = FONT_CODE_0X2125;   // (．)[ascii:u-002e]
uint16_t symbol_potsu[]         = FONT_CODE_0X2126;   // (・)
uint16_t symbol_colon[]         = FONT_CODE_0X2127;   // (：)[ascii:u-003a]
uint16_t symbol_semicolon[]     = FONT_CODE_0X2128;   // (；)[ascii:u-003b]
uint16_t symbol_question[]      = FONT_CODE_0X2129;   // (？)[ascii:u-003f]
uint16_t symbol_exclamation[]   = FONT_CODE_0X212A;   // (！)[ascii:u-0021]
#endif

#if 0
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

#define NUM_PANEL       (3U)            // パネル枚数(3枚買った)
#define NUM_LINES       (16U)           // パネルの表示行数 (16行)

typedef enum charcolor
{
    COLOR_GREEN     = 0x01,
    COLOR_RED       = 0x02,
    COLOR_ORANGE    = (COLOR_GREEN | COLOR_RED),
}charcolor_t;

typedef struct onechar_struct
{
    uint16_t    *font;
    charcolor_t color;
}onechar_t;

static void send_string(onechar_t* data, uint8_t size);
static void send_oneline(uint8_t iaddr_y, uint32_t *idata_r, uint32_t *idata_g);

/**
 * @brief 画面表示内容制御処理
 */
void lcdpanel_control(void)
{
    onechar_t disp_str[NUM_PANEL*2];

    disp_str[0].font = kanji_kyu;
    disp_str[0].color = COLOR_RED;
    disp_str[1].font = kanji_kou;
    disp_str[1].color = COLOR_RED;
    disp_str[2].font = symbol_space;
    disp_str[2].color = COLOR_ORANGE;
    disp_str[3].font = kanji_mori;
    disp_str[3].color = COLOR_ORANGE;
    disp_str[4].font = kanji_oka;
    disp_str[4].color = COLOR_ORANGE;
    disp_str[5].font = kanji_kou;
    disp_str[5].color = COLOR_GREEN;
    send_string(disp_str, sizeof(disp_str) / sizeof(disp_str[0]) );
    _delay_ms(3000);

    disp_str[0].font = kanji_tsugi;
    disp_str[0].color = COLOR_GREEN;
    disp_str[1].font = hiragana_ha;
    disp_str[1].color = COLOR_GREEN;
    disp_str[2].font = symbol_space;
    disp_str[2].color = COLOR_ORANGE;
    disp_str[3].font = kanji_asa;
    disp_str[3].color = COLOR_ORANGE;
    disp_str[4].font = kanji_kusa;
    disp_str[4].color = COLOR_ORANGE;
    disp_str[5].font = symbol_space;
    disp_str[5].color = COLOR_ORANGE;
    send_string(disp_str, sizeof(disp_str) / sizeof(disp_str[0]) );
    _delay_ms(3000);
}


/**
 * @brief 1画面ぶん(パネル数x2)の送信処理
 * @param[in]   *data 表示文字列データ
 * @param[in]   size 文字数
 */
static void send_string(onechar_t* data, uint8_t size)
{
    /* サイズチェック */
    if(size <= 0 || (NUM_PANEL*2) < size)
    {
        return;
    }

    for(uint8_t line=0; line<NUM_LINES; line++)
    {
        uint32_t r_line[NUM_PANEL] = {0};
        uint32_t g_line[NUM_PANEL] = {0};
        for(uint8_t charcnt=0; charcnt<size; charcnt+=2)
        {
            /* 偶数番目(0,2,4...)の文字 */
            if(data[charcnt].color & COLOR_RED)
            {
                r_line[charcnt/2] =  ((uint32_t)data[charcnt].font[line] << 16) & 0xFFFF0000;
            }
            if(data[charcnt].color & COLOR_GREEN) 
            {
                g_line[charcnt/2] =  ((uint32_t)data[charcnt].font[line] << 16) & 0xFFFF0000;
            }

            if(charcnt+1 >= size)
            {
                break;
            }

            /* 奇数番目(1,3,5...)の文字 */
            if(data[charcnt+1].color & COLOR_RED)
            {
                r_line[charcnt/2] |= data[charcnt+1].font[line];
            }
            if(data[charcnt+1].color & COLOR_GREEN) 
            {
                g_line[charcnt/2] |= data[charcnt+1].font[line];
            }
        }
        send_oneline(line, r_line, g_line);
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
