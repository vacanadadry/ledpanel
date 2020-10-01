#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include "panelcontrol.h"
#include "shinonome.h"
#include "config.h"

#define PINMASK_ONBOARDLED      (1 << 5)      // PB5

void lcdpanel_control(void);

/**
 * @brief ポート初期設定
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

    /* PORTD */
    pinMode(0, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);

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
#ifdef USE_NUMBER
const PROGMEM uint16_t flash_number_0[] = FONT_CODE_0X2330;    // (０)[ascii:u-0030]
const PROGMEM uint16_t flash_number_1[] = FONT_CODE_0X2331;    // (１)[ascii:u-0031]
const PROGMEM uint16_t flash_number_2[] = FONT_CODE_0X2332;    // (２)[ascii:u-0032]
const PROGMEM uint16_t flash_number_3[] = FONT_CODE_0X2333;    // (３)[ascii:u-0033]
const PROGMEM uint16_t flash_number_4[] = FONT_CODE_0X2334;    // (４)[ascii:u-0034]
const PROGMEM uint16_t flash_number_5[] = FONT_CODE_0X2335;    // (５)[ascii:u-0035]
const PROGMEM uint16_t flash_number_6[] = FONT_CODE_0X2336;    // (６)[ascii:u-0036]
const PROGMEM uint16_t flash_number_7[] = FONT_CODE_0X2337;    // (７)[ascii:u-0037]
const PROGMEM uint16_t flash_number_8[] = FONT_CODE_0X2338;    // (８)[ascii:u-0038]
const PROGMEM uint16_t flash_number_9[] = FONT_CODE_0X2339;    // (９)[ascii:u-0039]
#endif

#ifdef USE_ALPHABET_UPPER
const PROGMEM uint16_t flash_alphabet_A[] = FONT_CODE_0X2341;    // (Ａ)[ascii:u-0041]
const PROGMEM uint16_t flash_alphabet_B[] = FONT_CODE_0X2342;    // (Ｂ)[ascii:u-0042]
const PROGMEM uint16_t flash_alphabet_C[] = FONT_CODE_0X2343;    // (Ｃ)[ascii:u-0043]
const PROGMEM uint16_t flash_alphabet_D[] = FONT_CODE_0X2344;    // (Ｄ)[ascii:u-0044]
const PROGMEM uint16_t flash_alphabet_E[] = FONT_CODE_0X2345;    // (Ｅ)[ascii:u-0045]
const PROGMEM uint16_t flash_alphabet_F[] = FONT_CODE_0X2346;    // (Ｆ)[ascii:u-0046]
const PROGMEM uint16_t flash_alphabet_G[] = FONT_CODE_0X2347;    // (Ｇ)[ascii:u-0047]
const PROGMEM uint16_t flash_alphabet_H[] = FONT_CODE_0X2348;    // (Ｈ)[ascii:u-0048]
const PROGMEM uint16_t flash_alphabet_I[] = FONT_CODE_0X2349;    // (Ｉ)[ascii:u-0049]
const PROGMEM uint16_t flash_alphabet_J[] = FONT_CODE_0X234A;    // (Ｊ)[ascii:u-004a]
const PROGMEM uint16_t flash_alphabet_K[] = FONT_CODE_0X234B;    // (Ｋ)[ascii:u-004b]
const PROGMEM uint16_t flash_alphabet_L[] = FONT_CODE_0X234C;    // (Ｌ)[ascii:u-004c]
const PROGMEM uint16_t flash_alphabet_M[] = FONT_CODE_0X234D;    // (Ｍ)[ascii:u-004d]
const PROGMEM uint16_t flash_alphabet_N[] = FONT_CODE_0X234E;    // (Ｎ)[ascii:u-004e]
const PROGMEM uint16_t flash_alphabet_O[] = FONT_CODE_0X234F;    // (Ｏ)[ascii:u-004f]
const PROGMEM uint16_t flash_alphabet_P[] = FONT_CODE_0X2350;    // (Ｐ)[ascii:u-0050]
const PROGMEM uint16_t flash_alphabet_Q[] = FONT_CODE_0X2351;    // (Ｑ)[ascii:u-0051]
const PROGMEM uint16_t flash_alphabet_R[] = FONT_CODE_0X2352;    // (Ｒ)[ascii:u-0052]
const PROGMEM uint16_t flash_alphabet_S[] = FONT_CODE_0X2353;    // (Ｓ)[ascii:u-0053]
const PROGMEM uint16_t flash_alphabet_T[] = FONT_CODE_0X2354;    // (Ｔ)[ascii:u-0054]
const PROGMEM uint16_t flash_alphabet_U[] = FONT_CODE_0X2355;    // (Ｕ)[ascii:u-0055]
const PROGMEM uint16_t flash_alphabet_V[] = FONT_CODE_0X2356;    // (Ｖ)[ascii:u-0056]
const PROGMEM uint16_t flash_alphabet_W[] = FONT_CODE_0X2357;    // (Ｗ)[ascii:u-0057]
const PROGMEM uint16_t flash_alphabet_X[] = FONT_CODE_0X2358;    // (Ｘ)[ascii:u-0058]
const PROGMEM uint16_t flash_alphabet_Y[] = FONT_CODE_0X2359;    // (Ｙ)[ascii:u-0059]
const PROGMEM uint16_t flash_alphabet_Z[] = FONT_CODE_0X235A;    // (Ｚ)[ascii:u-005a]
#endif

#ifdef USE_ALPHABET_LOWER
const PROGMEM uint16_t flash_alphabet_a[] = FONT_CODE_0X2361;    // (ａ)[ascii:u-0061]
const PROGMEM uint16_t flash_alphabet_b[] = FONT_CODE_0X2362;    // (ｂ)[ascii:u-0062]
const PROGMEM uint16_t flash_alphabet_c[] = FONT_CODE_0X2363;    // (ｃ)[ascii:u-0063]
const PROGMEM uint16_t flash_alphabet_d[] = FONT_CODE_0X2364;    // (ｄ)[ascii:u-0064]
const PROGMEM uint16_t flash_alphabet_e[] = FONT_CODE_0X2365;    // (ｅ)[ascii:u-0065]
const PROGMEM uint16_t flash_alphabet_f[] = FONT_CODE_0X2366;    // (ｆ)[ascii:u-0066]
const PROGMEM uint16_t flash_alphabet_g[] = FONT_CODE_0X2367;    // (ｇ)[ascii:u-0067]
const PROGMEM uint16_t flash_alphabet_h[] = FONT_CODE_0X2368;    // (ｈ)[ascii:u-0068]
const PROGMEM uint16_t flash_alphabet_i[] = FONT_CODE_0X2369;    // (ｉ)[ascii:u-0069]
const PROGMEM uint16_t flash_alphabet_j[] = FONT_CODE_0X236A;    // (ｊ)[ascii:u-006a]
const PROGMEM uint16_t flash_alphabet_k[] = FONT_CODE_0X236B;    // (ｋ)[ascii:u-006b]
const PROGMEM uint16_t flash_alphabet_l[] = FONT_CODE_0X236C;    // (ｌ)[ascii:u-006c]
const PROGMEM uint16_t flash_alphabet_m[] = FONT_CODE_0X236D;    // (ｍ)[ascii:u-006d]
const PROGMEM uint16_t flash_alphabet_n[] = FONT_CODE_0X236E;    // (ｎ)[ascii:u-006e]
const PROGMEM uint16_t flash_alphabet_o[] = FONT_CODE_0X236F;    // (ｏ)[ascii:u-006f]
const PROGMEM uint16_t flash_alphabet_p[] = FONT_CODE_0X2370;    // (ｐ)[ascii:u-0070]
const PROGMEM uint16_t flash_alphabet_q[] = FONT_CODE_0X2371;    // (ｑ)[ascii:u-0071]
const PROGMEM uint16_t flash_alphabet_r[] = FONT_CODE_0X2372;    // (ｒ)[ascii:u-0072]
const PROGMEM uint16_t flash_alphabet_s[] = FONT_CODE_0X2373;    // (ｓ)[ascii:u-0073]
const PROGMEM uint16_t flash_alphabet_t[] = FONT_CODE_0X2374;    // (ｔ)[ascii:u-0074]
const PROGMEM uint16_t flash_alphabet_u[] = FONT_CODE_0X2375;    // (ｕ)[ascii:u-0075]
const PROGMEM uint16_t flash_alphabet_v[] = FONT_CODE_0X2376;    // (ｖ)[ascii:u-0076]
const PROGMEM uint16_t flash_alphabet_w[] = FONT_CODE_0X2377;    // (ｗ)[ascii:u-0077]
const PROGMEM uint16_t flash_alphabet_x[] = FONT_CODE_0X2378;    // (ｘ)[ascii:u-0078]
const PROGMEM uint16_t flash_alphabet_y[] = FONT_CODE_0X2379;    // (ｙ)[ascii:u-0079]
const PROGMEM uint16_t flash_alphabet_z[] = FONT_CODE_0X237A;    // (ｚ)[ascii:u-007a]
#endif

#ifdef USE_HIRAGANA
const PROGMEM uint16_t flash_hiragana_la[] = FONT_CODE_0X2421;      // (ぁ)
const PROGMEM uint16_t flash_hiragana_a[] = FONT_CODE_0X2422;      // (あ)
const PROGMEM uint16_t flash_hiragana_li[] = FONT_CODE_0X2423;      // (ぃ)
const PROGMEM uint16_t flash_hiragana_i[] = FONT_CODE_0X2424;      // (い)
const PROGMEM uint16_t flash_hiragana_lu[] = FONT_CODE_0X2425;      // (ぅ)
const PROGMEM uint16_t flash_hiragana_u[] = FONT_CODE_0X2426;      // (う)
const PROGMEM uint16_t flash_hiragana_le[] = FONT_CODE_0X2427;      // (ぇ)
const PROGMEM uint16_t flash_hiragana_e[] = FONT_CODE_0X2428;      // (え)
const PROGMEM uint16_t flash_hiragana_lo[] = FONT_CODE_0X2429;      // (ぉ)
const PROGMEM uint16_t flash_hiragana_o[] = FONT_CODE_0X242A;      // (お)
const PROGMEM uint16_t flash_hiragana_ka[] = FONT_CODE_0X242B;      // (か)
const PROGMEM uint16_t flash_hiragana_ga[] = FONT_CODE_0X242C;      // (が)
const PROGMEM uint16_t flash_hiragana_ki[] = FONT_CODE_0X242D;      // (き)
const PROGMEM uint16_t flash_hiragana_gi[] = FONT_CODE_0X242E;      // (ぎ)
const PROGMEM uint16_t flash_hiragana_ku[] = FONT_CODE_0X242F;      // (く)
const PROGMEM uint16_t flash_hiragana_gu[] = FONT_CODE_0X2430;      // (ぐ)
const PROGMEM uint16_t flash_hiragana_ke[] = FONT_CODE_0X2431;      // (け)
const PROGMEM uint16_t flash_hiragana_ge[] = FONT_CODE_0X2432;      // (げ)
const PROGMEM uint16_t flash_hiragana_ko[] = FONT_CODE_0X2433;      // (こ)
const PROGMEM uint16_t flash_hiragana_go[] = FONT_CODE_0X2434;      // (ご)
const PROGMEM uint16_t flash_hiragana_sa[] = FONT_CODE_0X2435;      // (さ)
const PROGMEM uint16_t flash_hiragana_za[] = FONT_CODE_0X2436;      // (ざ)
const PROGMEM uint16_t flash_hiragana_si[] = FONT_CODE_0X2437;      // (し)
const PROGMEM uint16_t flash_hiragana_zi[] = FONT_CODE_0X2438;      // (じ)
const PROGMEM uint16_t flash_hiragana_su[] = FONT_CODE_0X2439;      // (す)
const PROGMEM uint16_t flash_hiragana_zu[] = FONT_CODE_0X243A;      // (ず)
const PROGMEM uint16_t flash_hiragana_se[] = FONT_CODE_0X243B;      // (せ)
const PROGMEM uint16_t flash_hiragana_ze[] = FONT_CODE_0X243C;      // (ぜ)
const PROGMEM uint16_t flash_hiragana_so[] = FONT_CODE_0X243D;      // (そ)
const PROGMEM uint16_t flash_hiragana_zo[] = FONT_CODE_0X243E;      // (ぞ)
const PROGMEM uint16_t flash_hiragana_ta[] = FONT_CODE_0X243F;      // (た)
const PROGMEM uint16_t flash_hiragana_da[] = FONT_CODE_0X2440;      // (だ)
const PROGMEM uint16_t flash_hiragana_ti[] = FONT_CODE_0X2441;      // (ち)
const PROGMEM uint16_t flash_hiragana_di[] = FONT_CODE_0X2442;      // (ぢ)
const PROGMEM uint16_t flash_hiragana_ltu[] = FONT_CODE_0X2443;      // (っ)
const PROGMEM uint16_t flash_hiragana_tu[] = FONT_CODE_0X2444;      // (つ)
const PROGMEM uint16_t flash_hiragana_du[] = FONT_CODE_0X2445;      // (づ)
const PROGMEM uint16_t flash_hiragana_te[] = FONT_CODE_0X2446;      // (て)
const PROGMEM uint16_t flash_hiragana_de[] = FONT_CODE_0X2447;      // (で)
const PROGMEM uint16_t flash_hiragana_to[] = FONT_CODE_0X2448;      // (と)
const PROGMEM uint16_t flash_hiragana_do[] = FONT_CODE_0X2449;      // (ど)
const PROGMEM uint16_t flash_hiragana_na[] = FONT_CODE_0X244A;      // (な)
const PROGMEM uint16_t flash_hiragana_ni[] = FONT_CODE_0X244B;      // (に)
const PROGMEM uint16_t flash_hiragana_nu[] = FONT_CODE_0X244C;      // (ぬ)
const PROGMEM uint16_t flash_hiragana_ne[] = FONT_CODE_0X244D;      // (ね)
const PROGMEM uint16_t flash_hiragana_no[] = FONT_CODE_0X244E;      // (の)
const PROGMEM uint16_t flash_hiragana_ha[] = FONT_CODE_0X244F;      // (は)
const PROGMEM uint16_t flash_hiragana_ba[] = FONT_CODE_0X2450;      // (ば)
const PROGMEM uint16_t flash_hiragana_pa[] = FONT_CODE_0X2451;      // (ぱ)
const PROGMEM uint16_t flash_hiragana_hi[] = FONT_CODE_0X2452;      // (ひ)
const PROGMEM uint16_t flash_hiragana_bi[] = FONT_CODE_0X2453;      // (び)
const PROGMEM uint16_t flash_hiragana_pi[] = FONT_CODE_0X2454;      // (ぴ)
const PROGMEM uint16_t flash_hiragana_hy[] = FONT_CODE_0X2455;      // (ふ)
const PROGMEM uint16_t flash_hiragana_bu[] = FONT_CODE_0X2456;      // (ぶ)
const PROGMEM uint16_t flash_hiragana_pu[] = FONT_CODE_0X2457;      // (ぷ)
const PROGMEM uint16_t flash_hiragana_he[] = FONT_CODE_0X2458;      // (へ)
const PROGMEM uint16_t flash_hiragana_be[] = FONT_CODE_0X2459;      // (べ)
const PROGMEM uint16_t flash_hiragana_pe[] = FONT_CODE_0X245A;      // (ぺ)
const PROGMEM uint16_t flash_hiragana_ho[] = FONT_CODE_0X245B;      // (ほ)
const PROGMEM uint16_t flash_hiragana_bo[] = FONT_CODE_0X245C;      // (ぼ)
const PROGMEM uint16_t flash_hiragana_po[] = FONT_CODE_0X245D;      // (ぽ)
const PROGMEM uint16_t flash_hiragana_ma[] = FONT_CODE_0X245E;      // (ま)
const PROGMEM uint16_t flash_hiragana_mi[] = FONT_CODE_0X245F;      // (み)
const PROGMEM uint16_t flash_hiragana_mu[] = FONT_CODE_0X2460;      // (む)
const PROGMEM uint16_t flash_hiragana_me[] = FONT_CODE_0X2461;      // (め)
const PROGMEM uint16_t flash_hiragana_mo[] = FONT_CODE_0X2462;      // (も)
const PROGMEM uint16_t flash_hiragana_lya[] = FONT_CODE_0X2463;      // (ゃ)
const PROGMEM uint16_t flash_hiragana_ya[] = FONT_CODE_0X2464;      // (や)
const PROGMEM uint16_t flash_hiragana_lyu[] = FONT_CODE_0X2465;      // (ゅ)
const PROGMEM uint16_t flash_hiragana_yu[] = FONT_CODE_0X2466;      // (ゆ)
const PROGMEM uint16_t flash_hiragana_lyo[] = FONT_CODE_0X2467;      // (ょ)
const PROGMEM uint16_t flash_hiragana_yo[] = FONT_CODE_0X2468;      // (よ)
const PROGMEM uint16_t flash_hiragana_ra[] = FONT_CODE_0X2469;      // (ら)
const PROGMEM uint16_t flash_hiragana_ri[] = FONT_CODE_0X246A;      // (り)
const PROGMEM uint16_t flash_hiragana_ru[] = FONT_CODE_0X246B;      // (る)
const PROGMEM uint16_t flash_hiragana_re[] = FONT_CODE_0X246C;      // (れ)
const PROGMEM uint16_t flash_hiragana_ro[] = FONT_CODE_0X246D;      // (ろ)
const PROGMEM uint16_t flash_hiragana_lwa[] = FONT_CODE_0X246E;      // (ゎ)
const PROGMEM uint16_t flash_hiragana_wa[] = FONT_CODE_0X246F;      // (わ)
const PROGMEM uint16_t flash_hiragana_wi[] = FONT_CODE_0X2470;      // (ゐ)
const PROGMEM uint16_t flash_hiragana_we[] = FONT_CODE_0X2471;      // (ゑ)
const PROGMEM uint16_t flash_hiragana_wo[] = FONT_CODE_0X2472;      // (を)
const PROGMEM uint16_t flash_hiragana_n[] = FONT_CODE_0X2473;      // (ん)
#endif

#ifdef USE_KATAKANA
const PROGMEM uint16_t flash_katakana_la[] = FONT_CODE_0X2521;      // (ァ)
const PROGMEM uint16_t flash_katakana_a[] = FONT_CODE_0X2522;      // (ア)
const PROGMEM uint16_t flash_katakana_li[] = FONT_CODE_0X2523;      // (ィ)
const PROGMEM uint16_t flash_katakana_i[] = FONT_CODE_0X2524;      // (イ)
const PROGMEM uint16_t flash_katakana_lu[] = FONT_CODE_0X2525;      // (ゥ)
const PROGMEM uint16_t flash_katakana_u[] = FONT_CODE_0X2526;      // (ウ)
const PROGMEM uint16_t flash_katakana_le[] = FONT_CODE_0X2527;      // (ェ)
const PROGMEM uint16_t flash_katakana_e[] = FONT_CODE_0X2528;      // (エ)
const PROGMEM uint16_t flash_katakana_lo[] = FONT_CODE_0X2529;      // (ォ)
const PROGMEM uint16_t flash_katakana_o[] = FONT_CODE_0X252A;      // (オ)
const PROGMEM uint16_t flash_katakana_ka[] = FONT_CODE_0X252B;      // (カ)
const PROGMEM uint16_t flash_katakana_ga[] = FONT_CODE_0X252C;      // (ガ)
const PROGMEM uint16_t flash_katakana_ki[] = FONT_CODE_0X252D;      // (キ)
const PROGMEM uint16_t flash_katakana_gi[] = FONT_CODE_0X252E;      // (ギ)
const PROGMEM uint16_t flash_katakana_ku[] = FONT_CODE_0X252F;      // (ク)
const PROGMEM uint16_t flash_katakana_gu[] = FONT_CODE_0X2530;      // (グ)
const PROGMEM uint16_t flash_katakana_ke[] = FONT_CODE_0X2531;      // (ケ)
const PROGMEM uint16_t flash_katakana_ge[] = FONT_CODE_0X2532;      // (ゲ)
const PROGMEM uint16_t flash_katakana_ko[] = FONT_CODE_0X2533;      // (コ)
const PROGMEM uint16_t flash_katakana_go[] = FONT_CODE_0X2534;      // (ゴ)
const PROGMEM uint16_t flash_katakana_sa[] = FONT_CODE_0X2535;      // (サ)
const PROGMEM uint16_t flash_katakana_za[] = FONT_CODE_0X2536;      // (ザ)
const PROGMEM uint16_t flash_katakana_si[] = FONT_CODE_0X2537;      // (シ)
const PROGMEM uint16_t flash_katakana_zi[] = FONT_CODE_0X2538;      // (ジ)
const PROGMEM uint16_t flash_katakana_su[] = FONT_CODE_0X2539;      // (ス)
const PROGMEM uint16_t flash_katakana_zu[] = FONT_CODE_0X253A;      // (ズ)
const PROGMEM uint16_t flash_katakana_se[] = FONT_CODE_0X253B;      // (セ)
const PROGMEM uint16_t flash_katakana_ze[] = FONT_CODE_0X253C;      // (ゼ)
const PROGMEM uint16_t flash_katakana_so[] = FONT_CODE_0X253D;      // (ソ)
const PROGMEM uint16_t flash_katakana_zo[] = FONT_CODE_0X253E;      // (ゾ)
const PROGMEM uint16_t flash_katakana_ta[] = FONT_CODE_0X253F;      // (タ)
const PROGMEM uint16_t flash_katakana_da[] = FONT_CODE_0X2540;      // (ダ)
const PROGMEM uint16_t flash_katakana_ti[] = FONT_CODE_0X2541;      // (チ)
const PROGMEM uint16_t flash_katakana_di[] = FONT_CODE_0X2542;      // (ヂ)
const PROGMEM uint16_t flash_katakana_ltu[] = FONT_CODE_0X2543;      // (ッ)
const PROGMEM uint16_t flash_katakana_tu[] = FONT_CODE_0X2544;      // (ツ)
const PROGMEM uint16_t flash_katakana_du[] = FONT_CODE_0X2545;      // (ヅ)
const PROGMEM uint16_t flash_katakana_te[] = FONT_CODE_0X2546;      // (テ)
const PROGMEM uint16_t flash_katakana_de[] = FONT_CODE_0X2547;      // (デ)
const PROGMEM uint16_t flash_katakana_to[] = FONT_CODE_0X2548;      // (ト)
const PROGMEM uint16_t flash_katakana_do[] = FONT_CODE_0X2549;      // (ド)
const PROGMEM uint16_t flash_katakana_na[] = FONT_CODE_0X254A;      // (ナ)
const PROGMEM uint16_t flash_katakana_ni[] = FONT_CODE_0X254B;      // (ニ)
const PROGMEM uint16_t flash_katakana_nu[] = FONT_CODE_0X254C;      // (ヌ)
const PROGMEM uint16_t flash_katakana_ne[] = FONT_CODE_0X254D;      // (ネ)
const PROGMEM uint16_t flash_katakana_no[] = FONT_CODE_0X254E;      // (ノ)
const PROGMEM uint16_t flash_katakana_ha[] = FONT_CODE_0X254F;      // (ハ)
const PROGMEM uint16_t flash_katakana_ba[] = FONT_CODE_0X2550;      // (バ)
const PROGMEM uint16_t flash_katakana_pa[] = FONT_CODE_0X2551;      // (パ)
const PROGMEM uint16_t flash_katakana_hi[] = FONT_CODE_0X2552;      // (ヒ)
const PROGMEM uint16_t flash_katakana_bi[] = FONT_CODE_0X2553;      // (ビ)
const PROGMEM uint16_t flash_katakana_pi[] = FONT_CODE_0X2554;      // (ピ)
const PROGMEM uint16_t flash_katakana_hy[] = FONT_CODE_0X2555;      // (フ)
const PROGMEM uint16_t flash_katakana_bu[] = FONT_CODE_0X2556;      // (ブ)
const PROGMEM uint16_t flash_katakana_pu[] = FONT_CODE_0X2557;      // (プ)
const PROGMEM uint16_t flash_katakana_he[] = FONT_CODE_0X2558;      // (ヘ)
const PROGMEM uint16_t flash_katakana_be[] = FONT_CODE_0X2559;      // (ベ)
const PROGMEM uint16_t flash_katakana_pe[] = FONT_CODE_0X255A;      // (ペ)
const PROGMEM uint16_t flash_katakana_ho[] = FONT_CODE_0X255B;      // (ホ)
const PROGMEM uint16_t flash_katakana_bo[] = FONT_CODE_0X255C;      // (ボ)
const PROGMEM uint16_t flash_katakana_po[] = FONT_CODE_0X255D;      // (ポ)
const PROGMEM uint16_t flash_katakana_ma[] = FONT_CODE_0X255E;      // (マ)
const PROGMEM uint16_t flash_katakana_mi[] = FONT_CODE_0X255F;      // (ミ)
const PROGMEM uint16_t flash_katakana_mu[] = FONT_CODE_0X2560;      // (ム)
const PROGMEM uint16_t flash_katakana_me[] = FONT_CODE_0X2561;      // (メ)
const PROGMEM uint16_t flash_katakana_mo[] = FONT_CODE_0X2562;      // (モ)
const PROGMEM uint16_t flash_katakana_lya[] = FONT_CODE_0X2563;      // (ャ)
const PROGMEM uint16_t flash_katakana_ya[] = FONT_CODE_0X2564;      // (ヤ)
const PROGMEM uint16_t flash_katakana_lyu[] = FONT_CODE_0X2565;      // (ュ)
const PROGMEM uint16_t flash_katakana_yu[] = FONT_CODE_0X2566;      // (ユ)
const PROGMEM uint16_t flash_katakana_lyo[] = FONT_CODE_0X2567;      // (ョ)
const PROGMEM uint16_t flash_katakana_yo[] = FONT_CODE_0X2568;      // (ヨ)
const PROGMEM uint16_t flash_katakana_ra[] = FONT_CODE_0X2569;      // (ラ)
const PROGMEM uint16_t flash_katakana_ri[] = FONT_CODE_0X256A;      // (リ)
const PROGMEM uint16_t flash_katakana_ru[] = FONT_CODE_0X256B;      // (ル)
const PROGMEM uint16_t flash_katakana_re[] = FONT_CODE_0X256C;      // (レ)
const PROGMEM uint16_t flash_katakana_ro[] = FONT_CODE_0X256D;      // (ロ)
const PROGMEM uint16_t flash_katakana_lwa[] = FONT_CODE_0X256E;      // (ヮ)
const PROGMEM uint16_t flash_katakana_wa[] = FONT_CODE_0X256F;      // (ワ)
const PROGMEM uint16_t flash_katakana_wi[] = FONT_CODE_0X2570;      // (ヰ)
const PROGMEM uint16_t flash_katakana_we[] = FONT_CODE_0X2571;      // (ヱ)
const PROGMEM uint16_t flash_katakana_wo[] = FONT_CODE_0X2572;      // (ヲ)
const PROGMEM uint16_t flash_katakana_n[] = FONT_CODE_0X2573;      // (ン)
const PROGMEM uint16_t flash_katakana_vu[] = FONT_CODE_0X2574;      // (ヴ)
const PROGMEM uint16_t flash_katakana_lka[] = FONT_CODE_0X2575;      // (ヵ)
const PROGMEM uint16_t flash_katakana_lke[] = FONT_CODE_0X2576;      // (ヶ)
#endif

#ifdef USE_SYMBOL
const PROGMEM uint16_t flash_symbol_comma[]         = FONT_CODE_0X2124;   // (，)[ascii:u-002c]
const PROGMEM uint16_t flash_symbol_dot[]           = FONT_CODE_0X2125;   // (．)[ascii:u-002e]
const PROGMEM uint16_t flash_symbol_potsu[]         = FONT_CODE_0X2126;   // (・)
const PROGMEM uint16_t flash_symbol_colon[]         = FONT_CODE_0X2127;   // (：)[ascii:u-003a]
const PROGMEM uint16_t flash_symbol_semicolon[]     = FONT_CODE_0X2128;   // (；)[ascii:u-003b]
const PROGMEM uint16_t flash_symbol_question[]      = FONT_CODE_0X2129;   // (？)[ascii:u-003f]
const PROGMEM uint16_t flash_symbol_exclamation[]   = FONT_CODE_0X212A;   // (！)[ascii:u-0021]
const PROGMEM uint16_t flash_symbol_prolonged_sound[] = FONT_CODE_0X213C; // (ー)
const PROGMEM uint16_t flash_symbol_horizon_arrow[] = FONT_CODE_0X224E;   // (⇔)
const PROGMEM uint16_t flash_symbol_right_arrow[]   = FONT_CODE_0X222A;   // (→)
const PROGMEM uint16_t flash_symbol_left_arrow[]    = FONT_CODE_0X222B;   // (←)
#endif

const PROGMEM uint16_t flash_kanji_zoku[] =      FONT_CODE_0X4233;  // (続)
const PROGMEM uint16_t flash_kanji_soku[] =      FONT_CODE_0X422E;  // (速)
const PROGMEM uint16_t flash_kanji_do[] =      FONT_CODE_0X4559;    // (度)
const PROGMEM uint16_t flash_kanji_i[] =      FONT_CODE_0X3063;     // (違)
const PROGMEM uint16_t flash_kanji_han[] =      FONT_CODE_0X483F;   // (反)

const PROGMEM uint16_t flash_kanji_wa[] =      FONT_CODE_0X4F42;   // (和)
const PROGMEM uint16_t flash_kanji_ka[] =      FONT_CODE_0X324E;   // (歌)
const PROGMEM uint16_t flash_kanji_yama[] =      FONT_CODE_0X3B33;   // (山)
const PROGMEM uint16_t flash_kanji_hime[] =      FONT_CODE_0X4931;   // (姫)
const PROGMEM uint16_t flash_kanji_ji[] =      FONT_CODE_0X4F29;   // (路)

/**
 * @brief 画面表示内容制御処理
 */
void lcdpanel_control(void)
{
    uint8_t blank[NUM_PANEL * 64] = {0};

    uint8_t r_disp[NUM_PANEL * 64] = {0};
    uint8_t g_disp[NUM_PANEL * 64] = {0};

    /* パトカーに続け */
    uint16_t katakana_pa[NUM_LINES];
    uint16_t katakana_to[NUM_LINES];
    uint16_t katakana_ka[NUM_LINES];
    uint16_t symbol_prolonged_sound[NUM_LINES];
    uint16_t hiragana_ni[NUM_LINES];
    uint16_t kanji_zoku[NUM_LINES];
    uint16_t hiragana_ke[NUM_LINES];
    loadchar(flash_katakana_pa, katakana_pa);
    loadchar(flash_katakana_to, katakana_to);
    loadchar(flash_katakana_ka, katakana_ka);
    loadchar(flash_symbol_prolonged_sound, symbol_prolonged_sound);
    loadchar(flash_hiragana_ni, hiragana_ni);
    loadchar(flash_kanji_zoku, kanji_zoku);
    loadchar(flash_hiragana_ke, hiragana_ke);

    /* 速度違反 */
    uint16_t kanji_soku[NUM_LINES];
    uint16_t kanji_do[NUM_LINES];
    uint16_t kanji_i[NUM_LINES];
    uint16_t kanji_han[NUM_LINES];
    loadchar(flash_kanji_soku, kanji_soku);
    loadchar(flash_kanji_do, kanji_do);
    loadchar(flash_kanji_i, kanji_i);
    loadchar(flash_kanji_han, kanji_han);

    /* 0-9 */
    uint16_t number_0[NUM_LINES];
    uint16_t number_1[NUM_LINES];
    uint16_t number_2[NUM_LINES];
    uint16_t number_3[NUM_LINES];
    uint16_t number_4[NUM_LINES];
    uint16_t number_5[NUM_LINES];
    uint16_t number_6[NUM_LINES];
    uint16_t number_7[NUM_LINES];
    uint16_t number_8[NUM_LINES];
    uint16_t number_9[NUM_LINES];
    loadchar(flash_number_0, number_0);
    loadchar(flash_number_1, number_1);
    loadchar(flash_number_2, number_2);
    loadchar(flash_number_3, number_3);
    loadchar(flash_number_4, number_4);
    loadchar(flash_number_5, number_5);
    loadchar(flash_number_6, number_6);
    loadchar(flash_number_7, number_7);
    loadchar(flash_number_8, number_8);
    loadchar(flash_number_9, number_9);

    /* 姫路⇔和歌山 */
    uint16_t kanji_wa[NUM_LINES];
    uint16_t kanji_ka[NUM_LINES];
    uint16_t kanji_yama[NUM_LINES];
    uint16_t kanji_hime[NUM_LINES];
    uint16_t kanji_ji[NUM_LINES];
    uint16_t symbol_horizon_arrow[NUM_LINES];
    uint16_t symbol_right_arrow[NUM_LINES];
    uint16_t symbol_left_arrow[NUM_LINES];
    loadchar(flash_kanji_wa, kanji_wa);
    loadchar(flash_kanji_ka, kanji_ka);
    loadchar(flash_kanji_yama, kanji_yama);
    loadchar(flash_kanji_hime, kanji_hime);
    loadchar(flash_kanji_ji, kanji_ji);
    loadchar(flash_symbol_horizon_arrow, symbol_horizon_arrow);
    loadchar(flash_symbol_right_arrow, symbol_right_arrow);
    loadchar(flash_symbol_left_arrow, symbol_left_arrow);


    while(true)
    {
        memset(r_disp, 0x00, sizeof(r_disp));
        memset(g_disp, 0x00, sizeof(g_disp));

        switch((PIND ^ 0xFF) & 0x0F)
        {
            /* "パトカーに/続け" （公道での使用禁止） */
            case 0:
            {
                copyCharToBinary(r_disp, katakana_pa, 0+8, 0);
                // copyCharToBinary(g_disp, katakana_pa, 0+8, 0);
                copyCharToBinary(r_disp, katakana_to, 16+8, 0);
                // copyCharToBinary(g_disp, katakana_to, 16+8, 0);
                copyCharToBinary(r_disp, katakana_ka, 32+8, 0);
                // copyCharToBinary(g_disp, katakana_ka, 32+8, 0);
                copyCharToBinary(r_disp, symbol_prolonged_sound, 48+8, 0);
                // copyCharToBinary(g_disp, symbol_prolonged_sound, 48+8, 0);
                copyCharToBinary(r_disp, hiragana_ni, 64+8, 0);
                // copyCharToBinary(g_disp, hiragana_ni, 64+8, 0);
                u32nizer(r_disp);
                // u32nizer(g_disp);
                displayByBinary(r_disp, g_disp);
                _delay_ms(750);

                memset(r_disp, 0x00, sizeof(r_disp));
                // memset(g_disp, 0x00, sizeof(g_disp));
                copyCharToBinary(r_disp, kanji_zoku, 24, 0);
                // copyCharToBinary(g_disp, kanji_zoku, 24, 0);
                copyCharToBinary(r_disp, hiragana_ke, 56, 0);
                // copyCharToBinary(g_disp, hiragana_ke, 56, 0);
                u32nizer(r_disp);
                // u32nizer(g_disp);
                displayByBinary(r_disp, g_disp);
                _delay_ms(750);
            }
            break;

            /* "速度違反" （公道での使用禁止） */
            case 1:
            {
                copyCharToBinary(r_disp, kanji_soku, 0, 0);
                copyCharToBinary(r_disp, kanji_do, 26, 0);
                copyCharToBinary(r_disp, kanji_i, 52, 0);
                copyCharToBinary(r_disp, kanji_han, 80,0);
                u32nizer(r_disp);

                displayByBinary(r_disp, blank);
                _delay_ms(200);
                displayByBinary(blank, blank);
                _delay_ms(800);
            }
            break;

            /* "和歌山⇔姫路" */
            case 2:
            {
                copyCharToBinary(r_disp, kanji_wa, 0, 0);
                copyCharToBinary(r_disp, kanji_ka, 16, 0);
                copyCharToBinary(r_disp, kanji_yama, 32, 0);
                // copyCharToBinary(r_disp, symbol_horizon_arrow, 48, 0);
                copyCharToBinary(r_disp, kanji_hime, 64, 0);
                copyCharToBinary(r_disp, kanji_ji, 80, 0);
                u32nizer(r_disp);

                copyCharToBinary(g_disp, kanji_wa, 0, 0);
                copyCharToBinary(g_disp, kanji_ka, 16, 0);
                copyCharToBinary(g_disp, kanji_yama, 32, 0);
                copyCharToBinary(g_disp, symbol_horizon_arrow, 48, 0);
                copyCharToBinary(g_disp, kanji_hime, 64, 0);
                copyCharToBinary(g_disp, kanji_ji, 80, 0);
                u32nizer(g_disp);

                displayByBinary(r_disp, g_disp);
                _delay_ms(10);
            }
            break;

            /* "和歌山→姫路" */
            case 3:
            {
                copyCharToBinary(r_disp, kanji_wa, 0, 0);
                copyCharToBinary(r_disp, kanji_ka, 16, 0);
                copyCharToBinary(r_disp, kanji_yama, 32, 0);
                // copyCharToBinary(r_disp, symbol_right_arrow, 48, 0);
                copyCharToBinary(r_disp, kanji_hime, 64, 0);
                copyCharToBinary(r_disp, kanji_ji, 80, 0);
                u32nizer(r_disp);

                copyCharToBinary(g_disp, kanji_wa, 0, 0);
                copyCharToBinary(g_disp, kanji_ka, 16, 0);
                copyCharToBinary(g_disp, kanji_yama, 32, 0);
                copyCharToBinary(g_disp, symbol_right_arrow, 48, 0);
                copyCharToBinary(g_disp, kanji_hime, 64, 0);
                copyCharToBinary(g_disp, kanji_ji, 80, 0);
                u32nizer(g_disp);

                displayByBinary(r_disp, g_disp);
                _delay_ms(10);
            }
            break;

            /* "姫路→和歌山" */
            case 4:
            {
                copyCharToBinary(r_disp, kanji_hime, 0, 0);
                copyCharToBinary(r_disp, kanji_ji, 16, 0);
                copyCharToBinary(r_disp, symbol_right_arrow, 32, 0);
                // copyCharToBinary(r_disp, kanji_wa, 58, 0);
                copyCharToBinary(r_disp, kanji_ka, 64, 0);
                copyCharToBinary(r_disp, kanji_yama, 80, 0);
                u32nizer(r_disp);


                copyCharToBinary(g_disp, kanji_hime, 0, 0);
                copyCharToBinary(g_disp, kanji_ji, 16, 0);
                copyCharToBinary(g_disp, symbol_right_arrow, 32, 0);
                copyCharToBinary(g_disp, kanji_wa, 58, 0);
                copyCharToBinary(g_disp, kanji_ka, 64, 0);
                copyCharToBinary(g_disp, kanji_yama, 80, 0);
                u32nizer(g_disp);

                displayByBinary(r_disp, g_disp);
                _delay_ms(10);
            }
            break;


            case 5:
            {
                copyCharToBinary(r_disp, number_5, 0, 0);
                u32nizer(r_disp);
                displayByBinary(r_disp, blank);
                _delay_ms(10);
            }
            break;
            case 6:
            {
                copyCharToBinary(r_disp, number_6, 0, 0);
                u32nizer(r_disp);
                displayByBinary(r_disp, blank);
                _delay_ms(10);
            }
            break;
            case 7:
            {
                copyCharToBinary(r_disp, number_7, 0, 0);
                u32nizer(r_disp);
                displayByBinary(r_disp, blank);
                _delay_ms(10);
            }
            break;
            case 8:
            {
                copyCharToBinary(r_disp, number_8, 0, 0);
                u32nizer(r_disp);
                displayByBinary(r_disp, blank);
                _delay_ms(10);
            }
            break;
            case 9:
            {
                copyCharToBinary(r_disp, number_9, 0, 0);
                u32nizer(r_disp);
                displayByBinary(r_disp, blank);
                _delay_ms(10);
            }
            break;                                                                                                
        }
    }
}
