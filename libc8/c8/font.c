/**
 * @file c8/font.c
 *
 * Stuff related to loading fonts.
 */

#include "font.h"

#include "chip8.h"
#include "private/exception.h"

#include <stdint.h>
#include <string.h>

#define SMALLFONT_OCTO 0
#define SMALLFONT_VIP 1
#define SMALLFONT_DREAM6800 2
#define SMALLFONT_ETI660 3
#define SMALLFONT_FISH 4

#define BIGFONT_OCTO 0
#define BIGFONT_SCHIP 1
#define BIGFONT_FISH 2

#define OCTO_S "octo"
#define VIP_S "vip"
#define DREAM6800_S "dream6800"
#define ETI660_S "eti660"
#define FISH_S "fish"
#define SCHIP_S "schip"

const char* c8_fontNames[2][5] = {
    {
        OCTO_S,
        VIP_S,
        DREAM6800_S,
        ETI660_S,
        FISH_S,
    },
    {
        OCTO_S,
        SCHIP_S,
        FISH_S,
    },
};

/**
 * Small fonts.
 *
 * From Octo (https://github.com/JohnEarnest/Octo).
 */
const uint8_t smallFonts[5][80] = {
    {
        /* SMALLFONT_OCTO */
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80, // F
    },
    {
        /* SMALLFONT_VIP */
        0xF0, 0x90, 0x90, 0x90, 0xF0,
        0x60, 0x20, 0x20, 0x20, 0x70,
        0xF0, 0x10, 0xF0, 0x80, 0xF0,
        0xF0, 0x10, 0xF0, 0x10, 0xF0,
        0xA0, 0xA0, 0xF0, 0x20, 0x20,
        0xF0, 0x80, 0xF0, 0x10, 0xF0,
        0xF0, 0x80, 0xF0, 0x90, 0xF0,
        0xF0, 0x10, 0x10, 0x10, 0x10,
        0xF0, 0x90, 0xF0, 0x90, 0xF0,
        0xF0, 0x90, 0xF0, 0x10, 0xF0,
        0xF0, 0x90, 0xF0, 0x90, 0x90,
        0xF0, 0x50, 0x70, 0x50, 0xF0,
        0xF0, 0x80, 0x80, 0x80, 0xF0,
        0xF0, 0x50, 0x50, 0x50, 0xF0,
        0xF0, 0x80, 0xF0, 0x80, 0xF0,
        0xF0, 0x80, 0xF0, 0x80, 0x80,
    },
    {
        /* SMALLFONT_DREAM6800 */
        0xE0, 0xA0, 0xA0, 0xA0, 0xE0,
        0x40, 0x40, 0x40, 0x40, 0x40,
        0xE0, 0x20, 0xE0, 0x80, 0xE0,
        0xE0, 0x20, 0xE0, 0x20, 0xE0,
        0x80, 0xA0, 0xA0, 0xE0, 0x20,
        0xE0, 0x80, 0xE0, 0x20, 0xE0,
        0xE0, 0x80, 0xE0, 0xA0, 0xE0,
        0xE0, 0x20, 0x20, 0x20, 0x20,
        0xE0, 0xA0, 0xE0, 0xA0, 0xE0,
        0xE0, 0xA0, 0xE0, 0x20, 0xE0,
        0xE0, 0xA0, 0xE0, 0xA0, 0xA0,
        0xC0, 0xA0, 0xE0, 0xA0, 0xC0,
        0xE0, 0x80, 0x80, 0x80, 0xE0,
        0xC0, 0xA0, 0xA0, 0xA0, 0xC0,
        0xE0, 0x80, 0xE0, 0x80, 0xE0,
        0xE0, 0x80, 0xC0, 0x80, 0x80,
    },
    {
        /* SMALLFONT_ETI660 */
        0xE0, 0xA0, 0xA0, 0xA0, 0xE0,
        0x20, 0x20, 0x20, 0x20, 0x20,
        0xE0, 0x20, 0xE0, 0x80, 0xE0,
        0xE0, 0x20, 0xE0, 0x20, 0xE0,
        0xA0, 0xA0, 0xE0, 0x20, 0x20,
        0xE0, 0x80, 0xE0, 0x20, 0xE0,
        0xE0, 0x80, 0xE0, 0xA0, 0xE0,
        0xE0, 0x20, 0x20, 0x20, 0x20,
        0xE0, 0xA0, 0xE0, 0xA0, 0xE0,
        0xE0, 0xA0, 0xE0, 0x20, 0xE0,
        0xE0, 0xA0, 0xE0, 0xA0, 0xA0,
        0x80, 0x80, 0xE0, 0xA0, 0xE0,
        0xE0, 0x80, 0x80, 0x80, 0xE0,
        0x20, 0x20, 0xE0, 0xA0, 0xE0,
        0xE0, 0x80, 0xE0, 0x80, 0xE0,
        0xE0, 0x80, 0xC0, 0x80, 0x80,
    },
    {
        /* SMALLFONT_FISH */
        0x60, 0xA0, 0xA0, 0xA0, 0xC0,
        0x40, 0xC0, 0x40, 0x40, 0xE0,
        0xC0, 0x20, 0x40, 0x80, 0xE0,
        0xC0, 0x20, 0x40, 0x20, 0xC0,
        0x20, 0xA0, 0xE0, 0x20, 0x20,
        0xE0, 0x80, 0xC0, 0x20, 0xC0,
        0x40, 0x80, 0xC0, 0xA0, 0x40,
        0xE0, 0x20, 0x60, 0x40, 0x40,
        0x40, 0xA0, 0x40, 0xA0, 0x40,
        0x40, 0xA0, 0x60, 0x20, 0x40,
        0x40, 0xA0, 0xE0, 0xA0, 0xA0,
        0xC0, 0xA0, 0xC0, 0xA0, 0xC0,
        0x60, 0x80, 0x80, 0x80, 0x60,
        0xC0, 0xA0, 0xA0, 0xA0, 0xC0,
        0xE0, 0x80, 0xC0, 0x80, 0xE0,
        0xE0, 0x80, 0xC0, 0x80, 0x80,
    }
};

/**
 * Big fonts.
 *
 * From Octo (https://github.com/JohnEarnest/Octo).
 */
const uint8_t bigFonts[3][160] = {
    {
        /* BIGFONT_OCTO */
        0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, // 0
        0x18, 0x78, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, // 1
        0xFF, 0xFF, 0x03, 0x03, 0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, // 2
        0xFF, 0xFF, 0x03, 0x03, 0xFF, 0xFF, 0x03, 0x03, 0xFF, 0xFF, // 3
        0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, // 4
        0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, 0x03, 0x03, 0xFF, 0xFF, // 5
        0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, 0xC3, 0xC3, 0xFF, 0xFF, // 6
        0xFF, 0xFF, 0x03, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x18, // 7
        0xFF, 0xFF, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0xFF, 0xFF, // 8
        0xFF, 0xFF, 0xC3, 0xC3, 0xFF, 0xFF, 0x03, 0x03, 0xFF, 0xFF, // 9
        0x7E, 0xFF, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, // A
        0xFC, 0xFC, 0xC3, 0xC3, 0xFC, 0xFC, 0xC3, 0xC3, 0xFC, 0xFC, // B
        0x3C, 0xFF, 0xC3, 0xC0, 0xC0, 0xC0, 0xC0, 0xC3, 0xFF, 0x3C, // C
        0xFC, 0xFE, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xFE, 0xFC, // D
        0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, // E
        0xFF, 0xFF, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0,  // F
    },
    {
        /* BIGFONT_SCHIP */
        0x3C, 0x7E, 0xE7, 0xC3, 0xC3, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C,
        0x18, 0x38, 0x58, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C,
        0x3E, 0x7F, 0xC3, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFF, 0xFF,
        0x3C, 0x7E, 0xC3, 0x03, 0x0E, 0x0E, 0x03, 0xC3, 0x7E, 0x3C,
        0x06, 0x0E, 0x1E, 0x36, 0x66, 0xC6, 0xFF, 0xFF, 0x06, 0x06,
        0xFF, 0xFF, 0xC0, 0xC0, 0xFC, 0xFE, 0x03, 0xC3, 0x7E, 0x3C,
        0x3E, 0x7C, 0xE0, 0xC0, 0xFC, 0xFE, 0xC3, 0xC3, 0x7E, 0x3C,
        0xFF, 0xFF, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x60, 0x60,
        0x3C, 0x7E, 0xC3, 0xC3, 0x7E, 0x7E, 0xC3, 0xC3, 0x7E, 0x3C,
        0x3C, 0x7E, 0xC3, 0xC3, 0x7F, 0x3F, 0x03, 0x03, 0x3E, 0x7C,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // no hex chars!
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    },
    {
        /* BIGFONT_FISH */
        0x7C, 0xC6, 0xCE, 0xDE, 0xD6, 0xF6, 0xE6, 0xC6, 0x7C, 0x00, // at most 7x9 pixels!
        0x10, 0x30, 0xF0, 0x30, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00,
        0x78, 0xCC, 0xCC, 0x0C, 0x18, 0x30, 0x60, 0xCC, 0xFC, 0x00,
        0x78, 0xCC, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0xCC, 0x78, 0x00,
        0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x1E, 0x00,
        0xFC, 0xC0, 0xC0, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00,
        0x38, 0x60, 0xC0, 0xC0, 0xF8, 0xCC, 0xCC, 0xCC, 0x78, 0x00,
        0xFE, 0xC6, 0xC6, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00,
        0x78, 0xCC, 0xCC, 0xEC, 0x78, 0xDC, 0xCC, 0xCC, 0x78, 0x00,
        0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x18, 0x18, 0x30, 0x70, 0x00,
        0x30, 0x78, 0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00,
        0xFC, 0x66, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0xFC, 0x00,
        0x3C, 0x66, 0xC6, 0xC0, 0xC0, 0xC0, 0xC6, 0x66, 0x3C, 0x00,
        0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00,
        0xFE, 0x62, 0x60, 0x64, 0x7C, 0x64, 0x60, 0x62, 0xFE, 0x00,
        0xFE, 0x66, 0x62, 0x64, 0x7C, 0x64, 0x60, 0x60, 0xF0, 0x00,
    }
};

/**
 * @brief Loads small and/or big fonts in `c8`
 *
 * @param c8 `c8_t` to set fonts
 * @param small small font identifier (-1 to not set)
 * @param big big font identifier (-1 to not set)
 */
void c8_set_fonts(c8_t* c8, int small, int big) {
    if (small > -1 && small < 5) {
        c8->fonts[0] = small;
        memcpy(&c8->mem[C8_FONT_START], smallFonts[small], 80);
    }

    if (big > -1 && big < 3) {
        c8->fonts[1] = big;
        memcpy(&c8->mem[C8_HIGH_FONT_START], bigFonts[big], 160);
    }
}

/**
 * @brief Set fonts from string
 *
 * @param c8 `c8_t` to set fonts
 * @param s string to get fonts from (comma-separated `fontNames` names)
 *
 * @return 1 if success, 0 otherwise
 */
int c8_set_fonts_s(c8_t* c8, char* s) {
    int len = strlen(s);
    int small = -1;
    int big = -1;

    const char* s2 = NULL;

    for (int i = 0; i < len - 1; i++) {
        if (s[i] == ',') {
            s2 = &s[i + 1];
            s[i] = '\0';
        }
    }

    if (!c8_set_small_font(c8, s)) {
        fprintf(stderr, "Invalid font: %s\n", s);
        return 0;
    }
    if (s2) {
        if (!c8_set_big_font(c8, s2)) {
            fprintf(stderr, "Invalid font: %s\n", s2);
            return 0;
        }
    }

    c8_set_fonts(c8, small, big);
    return 1;
}

/**
 * @brief Set small font from `s` (`fontNames` name)
 *
 * @param c8 `c8_t` to set font from
 * @param s string to get font from
 *
 * @return 1 if success, 0 otherwise
 */
int c8_set_small_font(c8_t* c8, const char* s) {
    int f = -1;

    for (int i = 0; i < 5; i++) {
        if (!strcmp(s, c8_fontNames[0][i])) {
            f = i;
        }
    }
    c8_set_fonts(c8, f, -1);
    return f != -1;
}

/**
 * @brief Set big font from `s` (`fontNames` name)
 *
 * @param c8 `c8_t` to set font from
 * @param s string to get font from
 *
 * @return 1 if success, 0 otherwise
 */
int c8_set_big_font(c8_t* c8, const char* s) {
    int f = -1;
    for (int i = 0; i < 3; i++) {
        if (!strcmp(s, c8_fontNames[1][i])) {
            f = i;
        }
    }

    c8_set_fonts(c8, -1, f);
    return f != -1;
}

/**
 * @brief Print fonts (for debug)
 *
 * @param c8 `c8_t` to get fonts from
 */
void print_fonts(c8_t* c8) {
    printf("SFONT: %s\tBFONT: %s\n", c8_fontNames[0][c8->fonts[0]],
        c8_fontNames[1][c8->fonts[1]]);
}
