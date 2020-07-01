/**
 *******************************************************************************
 * @file  hc32m423_efm.h
 * @brief This file contains all the functions prototypes of the EFM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-06       Heqb          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co., Ltd. ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACCOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 *******************************************************************************
 */
#ifndef __HC32M423_EFM_H__
#define __HC32M423_EFM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_EFM
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Types EFM Global Types
 * @{
 */

/**
 * @brief EFM configure structure
 */
typedef struct
{
    uint32_t            u32WaitCycle;   /*!< Specifies the efm read wait cycles.
                                            This parameter can be a value of @ref EFM_Wait_Cycle.              */

    uint32_t            u32CacheRst;    /*!< Specifies the data cache reset on or off.
                                            This parameter can be a value of @ref EFM_CacheRst_Func.       */

    uint32_t            u32InsCache;    /*!< Specifies the instruction cache on or off.
                                            This parameter can be a value of @ref EFM_InsCache_Func.       */

    uint32_t            u32DataCache;   /*!< Specifies the data cache on or off.
                                            This parameter can be a value of @ref EFM_DataCache_Func.        */

    uint32_t            u32BusStatus;   /*!< Specifies the bus status busy or release while program & erase.
                                            This parameter can be a value of @ref EFM_Bus_Status.            */
} stc_efm_cfg_t;

/**
 * @brief EFM unique ID definition
 */
typedef struct
{
    uint32_t            u32UniqueID0;      /*!< unique ID 0.       */
    uint32_t            u32UniqueID1;      /*!< unique ID 1.       */
    uint32_t            u32UniqueID2;      /*!< unique ID 2.       */
    uint32_t            u32UniqueID3;      /*!< unique ID 3.       */
} stc_efm_unique_id_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Macros EFM Global Macros
 * @{
 */

/**
 * @defgroup EFM_Address EFM address area
 * @{
 */
#define EFM_START_ADDR              (0x00000000UL)  /*!< Flash start address */
#define EFM_END_ADDR                (0x0001FFFFUL)  /*!< Flash end address */
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Address EFM Sector Address
 * @{
 */
#define EFM_SECTOR0_ADRR            (0x00000000UL)   /*!< Sector 0 */
#define EFM_SECTOR1_ADRR            (0x00000200UL)   /*!< Sector 1 */
#define EFM_SECTOR2_ADRR            (0x00000400UL)   /*!< Sector 2 */
#define EFM_SECTOR3_ADRR            (0x00000600UL)   /*!< Sector 3 */
#define EFM_SECTOR4_ADRR            (0x00000800UL)   /*!< Sector 4 */
#define EFM_SECTOR5_ADRR            (0x00000A00UL)   /*!< Sector 5 */
#define EFM_SECTOR6_ADRR            (0x00000C00UL)   /*!< Sector 6 */
#define EFM_SECTOR7_ADRR            (0x00000E00UL)   /*!< Sector 7 */
#define EFM_SECTOR8_ADRR            (0x00001000UL)   /*!< Sector 8 */
#define EFM_SECTOR9_ADRR            (0x00001200UL)   /*!< Sector 9 */
#define EFM_SECTOR10_ADRR           (0x00001400UL)   /*!< Sector 10 */
#define EFM_SECTOR11_ADRR           (0x00001600UL)   /*!< Sector 11 */
#define EFM_SECTOR12_ADRR           (0x00001800UL)   /*!< Sector 12 */
#define EFM_SECTOR13_ADRR           (0x00001A00UL)   /*!< Sector 13 */
#define EFM_SECTOR14_ADRR           (0x00001C00UL)   /*!< Sector 14 */
#define EFM_SECTOR15_ADRR           (0x00001E00UL)   /*!< Sector 15 */
#define EFM_SECTOR16_ADRR           (0x00002000UL)   /*!< Sector 16 */
#define EFM_SECTOR17_ADRR           (0x00002200UL)   /*!< Sector 17 */
#define EFM_SECTOR18_ADRR           (0x00002400UL)   /*!< Sector 18 */
#define EFM_SECTOR19_ADRR           (0x00002600UL)   /*!< Sector 19 */
#define EFM_SECTOR20_ADRR           (0x00002800UL)   /*!< Sector 20 */
#define EFM_SECTOR21_ADRR           (0x00002A00UL)   /*!< Sector 21 */
#define EFM_SECTOR22_ADRR           (0x00002C00UL)   /*!< Sector 22 */
#define EFM_SECTOR23_ADRR           (0x00002E00UL)   /*!< Sector 23 */
#define EFM_SECTOR24_ADRR           (0x00003000UL)   /*!< Sector 24 */
#define EFM_SECTOR25_ADRR           (0x00003200UL)   /*!< Sector 25 */
#define EFM_SECTOR26_ADRR           (0x00003400UL)   /*!< Sector 26 */
#define EFM_SECTOR27_ADRR           (0x00003600UL)   /*!< Sector 27 */
#define EFM_SECTOR28_ADRR           (0x00003800UL)   /*!< Sector 28 */
#define EFM_SECTOR29_ADRR           (0x00003A00UL)   /*!< Sector 29 */
#define EFM_SECTOR30_ADRR           (0x00003C00UL)   /*!< Sector 30 */
#define EFM_SECTOR31_ADRR           (0x00003E00UL)   /*!< Sector 31 */
#define EFM_SECTOR32_ADRR           (0x00004000UL)   /*!< Sector 32 */
#define EFM_SECTOR33_ADRR           (0x00004200UL)   /*!< Sector 33 */
#define EFM_SECTOR34_ADRR           (0x00004400UL)   /*!< Sector 34 */
#define EFM_SECTOR35_ADRR           (0x00004600UL)   /*!< Sector 35 */
#define EFM_SECTOR36_ADRR           (0x00004800UL)   /*!< Sector 36 */
#define EFM_SECTOR37_ADRR           (0x00004A00UL)   /*!< Sector 37 */
#define EFM_SECTOR38_ADRR           (0x00004C00UL)   /*!< Sector 38 */
#define EFM_SECTOR39_ADRR           (0x00004E00UL)   /*!< Sector 39 */
#define EFM_SECTOR40_ADRR           (0x00005000UL)   /*!< Sector 40 */
#define EFM_SECTOR41_ADRR           (0x00005200UL)   /*!< Sector 41 */
#define EFM_SECTOR42_ADRR           (0x00005400UL)   /*!< Sector 42 */
#define EFM_SECTOR43_ADRR           (0x00005600UL)   /*!< Sector 43 */
#define EFM_SECTOR44_ADRR           (0x00005800UL)   /*!< Sector 44 */
#define EFM_SECTOR45_ADRR           (0x00005A00UL)   /*!< Sector 45 */
#define EFM_SECTOR46_ADRR           (0x00005C00UL)   /*!< Sector 46 */
#define EFM_SECTOR47_ADRR           (0x00005E00UL)   /*!< Sector 47 */
#define EFM_SECTOR48_ADRR           (0x00006000UL)   /*!< Sector 48 */
#define EFM_SECTOR49_ADRR           (0x00006200UL)   /*!< Sector 49 */
#define EFM_SECTOR50_ADRR           (0x00006400UL)   /*!< Sector 50 */
#define EFM_SECTOR51_ADRR           (0x00006600UL)   /*!< Sector 51 */
#define EFM_SECTOR52_ADRR           (0x00006800UL)   /*!< Sector 52 */
#define EFM_SECTOR53_ADRR           (0x00006A00UL)   /*!< Sector 53 */
#define EFM_SECTOR54_ADRR           (0x00006C00UL)   /*!< Sector 54 */
#define EFM_SECTOR55_ADRR           (0x00006E00UL)   /*!< Sector 55 */
#define EFM_SECTOR56_ADRR           (0x00007000UL)   /*!< Sector 56 */
#define EFM_SECTOR57_ADRR           (0x00007200UL)   /*!< Sector 57 */
#define EFM_SECTOR58_ADRR           (0x00007400UL)   /*!< Sector 58 */
#define EFM_SECTOR59_ADRR           (0x00007600UL)   /*!< Sector 59 */
#define EFM_SECTOR60_ADRR           (0x00007800UL)   /*!< Sector 60 */
#define EFM_SECTOR61_ADRR           (0x00007A00UL)   /*!< Sector 61 */
#define EFM_SECTOR62_ADRR           (0x00007C00UL)   /*!< Sector 62 */
#define EFM_SECTOR63_ADRR           (0x00007E00UL)   /*!< Sector 63 */
#define EFM_SECTOR64_ADRR           (0x00008000UL)   /*!< Sector 64 */
#define EFM_SECTOR65_ADRR           (0x00008200UL)   /*!< Sector 65 */
#define EFM_SECTOR66_ADRR           (0x00008400UL)   /*!< Sector 66 */
#define EFM_SECTOR67_ADRR           (0x00008600UL)   /*!< Sector 67 */
#define EFM_SECTOR68_ADRR           (0x00008800UL)   /*!< Sector 68 */
#define EFM_SECTOR69_ADRR           (0x00008A00UL)   /*!< Sector 69 */
#define EFM_SECTOR70_ADRR           (0x00008C00UL)   /*!< Sector 70 */
#define EFM_SECTOR71_ADRR           (0x00008E00UL)   /*!< Sector 71 */
#define EFM_SECTOR72_ADRR           (0x00009000UL)   /*!< Sector 72 */
#define EFM_SECTOR73_ADRR           (0x00009200UL)   /*!< Sector 73 */
#define EFM_SECTOR74_ADRR           (0x00009400UL)   /*!< Sector 74 */
#define EFM_SECTOR75_ADRR           (0x00009600UL)   /*!< Sector 75 */
#define EFM_SECTOR76_ADRR           (0x00009800UL)   /*!< Sector 76 */
#define EFM_SECTOR77_ADRR           (0x00009A00UL)   /*!< Sector 77 */
#define EFM_SECTOR78_ADRR           (0x00009C00UL)   /*!< Sector 78 */
#define EFM_SECTOR79_ADRR           (0x00009E00UL)   /*!< Sector 79 */
#define EFM_SECTOR80_ADRR           (0x0000A000UL)   /*!< Sector 80 */
#define EFM_SECTOR81_ADRR           (0x0000A200UL)   /*!< Sector 81 */
#define EFM_SECTOR82_ADRR           (0x0000A400UL)   /*!< Sector 82 */
#define EFM_SECTOR83_ADRR           (0x0000A600UL)   /*!< Sector 83 */
#define EFM_SECTOR84_ADRR           (0x0000A800UL)   /*!< Sector 84 */
#define EFM_SECTOR85_ADRR           (0x0000AA00UL)   /*!< Sector 85 */
#define EFM_SECTOR86_ADRR           (0x0000AC00UL)   /*!< Sector 86 */
#define EFM_SECTOR87_ADRR           (0x0000AE00UL)   /*!< Sector 87 */
#define EFM_SECTOR88_ADRR           (0x0000B000UL)   /*!< Sector 88 */
#define EFM_SECTOR89_ADRR           (0x0000B200UL)   /*!< Sector 89 */
#define EFM_SECTOR90_ADRR           (0x0000B400UL)   /*!< Sector 90 */
#define EFM_SECTOR91_ADRR           (0x0000B600UL)   /*!< Sector 91 */
#define EFM_SECTOR92_ADRR           (0x0000B800UL)   /*!< Sector 92 */
#define EFM_SECTOR93_ADRR           (0x0000BA00UL)   /*!< Sector 93 */
#define EFM_SECTOR94_ADRR           (0x0000BC00UL)   /*!< Sector 94 */
#define EFM_SECTOR95_ADRR           (0x0000BE00UL)   /*!< Sector 95 */
#define EFM_SECTOR96_ADRR           (0x0000C000UL)   /*!< Sector 96 */
#define EFM_SECTOR97_ADRR           (0x0000C200UL)   /*!< Sector 97 */
#define EFM_SECTOR98_ADRR           (0x0000C400UL)   /*!< Sector 98 */
#define EFM_SECTOR99_ADRR           (0x0000C600UL)   /*!< Sector 99 */
#define EFM_SECTOR100_ADRR          (0x0000C800UL)   /*!< Sector 100 */
#define EFM_SECTOR101_ADRR          (0x0000CA00UL)   /*!< Sector 101 */
#define EFM_SECTOR102_ADRR          (0x0000CC00UL)   /*!< Sector 102 */
#define EFM_SECTOR103_ADRR          (0x0000CE00UL)   /*!< Sector 103 */
#define EFM_SECTOR104_ADRR          (0x0000D000UL)   /*!< Sector 104 */
#define EFM_SECTOR105_ADRR          (0x0000D200UL)   /*!< Sector 105 */
#define EFM_SECTOR106_ADRR          (0x0000D400UL)   /*!< Sector 106 */
#define EFM_SECTOR107_ADRR          (0x0000D600UL)   /*!< Sector 107 */
#define EFM_SECTOR108_ADRR          (0x0000D800UL)   /*!< Sector 108 */
#define EFM_SECTOR109_ADRR          (0x0000DA00UL)   /*!< Sector 109 */
#define EFM_SECTOR110_ADRR          (0x0000DC00UL)   /*!< Sector 110 */
#define EFM_SECTOR111_ADRR          (0x0000DE00UL)   /*!< Sector 111 */
#define EFM_SECTOR112_ADRR          (0x0000E000UL)   /*!< Sector 112 */
#define EFM_SECTOR113_ADRR          (0x0000E200UL)   /*!< Sector 113 */
#define EFM_SECTOR114_ADRR          (0x0000E400UL)   /*!< Sector 114 */
#define EFM_SECTOR115_ADRR          (0x0000E600UL)   /*!< Sector 115 */
#define EFM_SECTOR116_ADRR          (0x0000E800UL)   /*!< Sector 116 */
#define EFM_SECTOR117_ADRR          (0x0000EA00UL)   /*!< Sector 117 */
#define EFM_SECTOR118_ADRR          (0x0000EC00UL)   /*!< Sector 118 */
#define EFM_SECTOR119_ADRR          (0x0000EE00UL)   /*!< Sector 119 */
#define EFM_SECTOR120_ADRR          (0x0000F000UL)   /*!< Sector 120 */
#define EFM_SECTOR121_ADRR          (0x0000F200UL)   /*!< Sector 121 */
#define EFM_SECTOR122_ADRR          (0x0000F400UL)   /*!< Sector 122 */
#define EFM_SECTOR123_ADRR          (0x0000F600UL)   /*!< Sector 123 */
#define EFM_SECTOR124_ADRR          (0x0000F800UL)   /*!< Sector 124 */
#define EFM_SECTOR125_ADRR          (0x0000FA00UL)   /*!< Sector 125 */
#define EFM_SECTOR126_ADRR          (0x0000FC00UL)   /*!< Sector 126 */
#define EFM_SECTOR127_ADRR          (0x0000FE00UL)   /*!< Sector 127 */
#define EFM_SECTOR128_ADRR          (0x00010000UL)   /*!< Sector 128 */
#define EFM_SECTOR129_ADRR          (0x00010200UL)   /*!< Sector 129 */
#define EFM_SECTOR130_ADRR          (0x00010400UL)   /*!< Sector 130 */
#define EFM_SECTOR131_ADRR          (0x00010600UL)   /*!< Sector 131 */
#define EFM_SECTOR132_ADRR          (0x00010800UL)   /*!< Sector 132 */
#define EFM_SECTOR133_ADRR          (0x00010A00UL)   /*!< Sector 133 */
#define EFM_SECTOR134_ADRR          (0x00010C00UL)   /*!< Sector 134 */
#define EFM_SECTOR135_ADRR          (0x00010E00UL)   /*!< Sector 135 */
#define EFM_SECTOR136_ADRR          (0x00011000UL)   /*!< Sector 136 */
#define EFM_SECTOR137_ADRR          (0x00011200UL)   /*!< Sector 137 */
#define EFM_SECTOR138_ADRR          (0x00011400UL)   /*!< Sector 138 */
#define EFM_SECTOR139_ADRR          (0x00011600UL)   /*!< Sector 139 */
#define EFM_SECTOR140_ADRR          (0x00011800UL)   /*!< Sector 140 */
#define EFM_SECTOR141_ADRR          (0x00011A00UL)   /*!< Sector 141 */
#define EFM_SECTOR142_ADRR          (0x00011C00UL)   /*!< Sector 142 */
#define EFM_SECTOR143_ADRR          (0x00011E00UL)   /*!< Sector 143 */
#define EFM_SECTOR144_ADRR          (0x00012000UL)   /*!< Sector 144 */
#define EFM_SECTOR145_ADRR          (0x00012200UL)   /*!< Sector 145 */
#define EFM_SECTOR146_ADRR          (0x00012400UL)   /*!< Sector 146 */
#define EFM_SECTOR147_ADRR          (0x00012600UL)   /*!< Sector 147 */
#define EFM_SECTOR148_ADRR          (0x00012800UL)   /*!< Sector 148 */
#define EFM_SECTOR149_ADRR          (0x00012A00UL)   /*!< Sector 149 */
#define EFM_SECTOR150_ADRR          (0x00012C00UL)   /*!< Sector 150 */
#define EFM_SECTOR151_ADRR          (0x00012E00UL)   /*!< Sector 151 */
#define EFM_SECTOR152_ADRR          (0x00013000UL)   /*!< Sector 152 */
#define EFM_SECTOR153_ADRR          (0x00013200UL)   /*!< Sector 153 */
#define EFM_SECTOR154_ADRR          (0x00013400UL)   /*!< Sector 154 */
#define EFM_SECTOR155_ADRR          (0x00013600UL)   /*!< Sector 155 */
#define EFM_SECTOR156_ADRR          (0x00013800UL)   /*!< Sector 156 */
#define EFM_SECTOR157_ADRR          (0x00013A00UL)   /*!< Sector 157 */
#define EFM_SECTOR158_ADRR          (0x00013C00UL)   /*!< Sector 158 */
#define EFM_SECTOR159_ADRR          (0x00013E00UL)   /*!< Sector 159 */
#define EFM_SECTOR160_ADRR          (0x00014000UL)   /*!< Sector 160 */
#define EFM_SECTOR161_ADRR          (0x00014200UL)   /*!< Sector 161 */
#define EFM_SECTOR162_ADRR          (0x00014400UL)   /*!< Sector 162 */
#define EFM_SECTOR163_ADRR          (0x00014600UL)   /*!< Sector 163 */
#define EFM_SECTOR164_ADRR          (0x00014800UL)   /*!< Sector 164 */
#define EFM_SECTOR165_ADRR          (0x00014A00UL)   /*!< Sector 165 */
#define EFM_SECTOR166_ADRR          (0x00014C00UL)   /*!< Sector 166 */
#define EFM_SECTOR167_ADRR          (0x00014E00UL)   /*!< Sector 167 */
#define EFM_SECTOR168_ADRR          (0x00015000UL)   /*!< Sector 168 */
#define EFM_SECTOR169_ADRR          (0x00015200UL)   /*!< Sector 169 */
#define EFM_SECTOR170_ADRR          (0x00015400UL)   /*!< Sector 170 */
#define EFM_SECTOR171_ADRR          (0x00015600UL)   /*!< Sector 171 */
#define EFM_SECTOR172_ADRR          (0x00015800UL)   /*!< Sector 172 */
#define EFM_SECTOR173_ADRR          (0x00015A00UL)   /*!< Sector 173 */
#define EFM_SECTOR174_ADRR          (0x00015C00UL)   /*!< Sector 174 */
#define EFM_SECTOR175_ADRR          (0x00015E00UL)   /*!< Sector 175 */
#define EFM_SECTOR176_ADRR          (0x00016000UL)   /*!< Sector 176 */
#define EFM_SECTOR177_ADRR          (0x00016200UL)   /*!< Sector 177 */
#define EFM_SECTOR178_ADRR          (0x00016400UL)   /*!< Sector 178 */
#define EFM_SECTOR179_ADRR          (0x00016600UL)   /*!< Sector 179 */
#define EFM_SECTOR180_ADRR          (0x00016800UL)   /*!< Sector 180 */
#define EFM_SECTOR181_ADRR          (0x00016A00UL)   /*!< Sector 181 */
#define EFM_SECTOR182_ADRR          (0x00016C00UL)   /*!< Sector 182 */
#define EFM_SECTOR183_ADRR          (0x00016E00UL)   /*!< Sector 183 */
#define EFM_SECTOR184_ADRR          (0x00017000UL)   /*!< Sector 184 */
#define EFM_SECTOR185_ADRR          (0x00017200UL)   /*!< Sector 185 */
#define EFM_SECTOR186_ADRR          (0x00017400UL)   /*!< Sector 186 */
#define EFM_SECTOR187_ADRR          (0x00017600UL)   /*!< Sector 187 */
#define EFM_SECTOR188_ADRR          (0x00017800UL)   /*!< Sector 188 */
#define EFM_SECTOR189_ADRR          (0x00017A00UL)   /*!< Sector 189 */
#define EFM_SECTOR190_ADRR          (0x00017C00UL)   /*!< Sector 190 */
#define EFM_SECTOR191_ADRR          (0x00017E00UL)   /*!< Sector 191 */
#define EFM_SECTOR192_ADRR          (0x00018000UL)   /*!< Sector 192 */
#define EFM_SECTOR193_ADRR          (0x00018200UL)   /*!< Sector 193 */
#define EFM_SECTOR194_ADRR          (0x00018400UL)   /*!< Sector 194 */
#define EFM_SECTOR195_ADRR          (0x00018600UL)   /*!< Sector 195 */
#define EFM_SECTOR196_ADRR          (0x00018800UL)   /*!< Sector 196 */
#define EFM_SECTOR197_ADRR          (0x00018A00UL)   /*!< Sector 197 */
#define EFM_SECTOR198_ADRR          (0x00018C00UL)   /*!< Sector 198 */
#define EFM_SECTOR199_ADRR          (0x00018E00UL)   /*!< Sector 199 */
#define EFM_SECTOR200_ADRR          (0x00019000UL)   /*!< Sector 200 */
#define EFM_SECTOR201_ADRR          (0x00019200UL)   /*!< Sector 201 */
#define EFM_SECTOR202_ADRR          (0x00019400UL)   /*!< Sector 202 */
#define EFM_SECTOR203_ADRR          (0x00019600UL)   /*!< Sector 203 */
#define EFM_SECTOR204_ADRR          (0x00019800UL)   /*!< Sector 204 */
#define EFM_SECTOR205_ADRR          (0x00019A00UL)   /*!< Sector 205 */
#define EFM_SECTOR206_ADRR          (0x00019C00UL)   /*!< Sector 206 */
#define EFM_SECTOR207_ADRR          (0x00019E00UL)   /*!< Sector 207 */
#define EFM_SECTOR208_ADRR          (0x0001A000UL)   /*!< Sector 208 */
#define EFM_SECTOR209_ADRR          (0x0001A200UL)   /*!< Sector 209 */
#define EFM_SECTOR210_ADRR          (0x0001A400UL)   /*!< Sector 210 */
#define EFM_SECTOR211_ADRR          (0x0001A600UL)   /*!< Sector 211 */
#define EFM_SECTOR212_ADRR          (0x0001A800UL)   /*!< Sector 212 */
#define EFM_SECTOR213_ADRR          (0x0001AA00UL)   /*!< Sector 213 */
#define EFM_SECTOR214_ADRR          (0x0001AC00UL)   /*!< Sector 214 */
#define EFM_SECTOR215_ADRR          (0x0001AE00UL)   /*!< Sector 215 */
#define EFM_SECTOR216_ADRR          (0x0001B000UL)   /*!< Sector 216 */
#define EFM_SECTOR217_ADRR          (0x0001B200UL)   /*!< Sector 217 */
#define EFM_SECTOR218_ADRR          (0x0001B400UL)   /*!< Sector 218 */
#define EFM_SECTOR219_ADRR          (0x0001B600UL)   /*!< Sector 219 */
#define EFM_SECTOR220_ADRR          (0x0001B800UL)   /*!< Sector 220 */
#define EFM_SECTOR221_ADRR          (0x0001BA00UL)   /*!< Sector 221 */
#define EFM_SECTOR222_ADRR          (0x0001BC00UL)   /*!< Sector 222 */
#define EFM_SECTOR223_ADRR          (0x0001BE00UL)   /*!< Sector 223 */
#define EFM_SECTOR224_ADRR          (0x0001C000UL)   /*!< Sector 224 */
#define EFM_SECTOR225_ADRR          (0x0001C200UL)   /*!< Sector 225 */
#define EFM_SECTOR226_ADRR          (0x0001C400UL)   /*!< Sector 226 */
#define EFM_SECTOR227_ADRR          (0x0001C600UL)   /*!< Sector 227 */
#define EFM_SECTOR228_ADRR          (0x0001C800UL)   /*!< Sector 228 */
#define EFM_SECTOR229_ADRR          (0x0001CA00UL)   /*!< Sector 229 */
#define EFM_SECTOR230_ADRR          (0x0001CC00UL)   /*!< Sector 230 */
#define EFM_SECTOR231_ADRR          (0x0001CE00UL)   /*!< Sector 231 */
#define EFM_SECTOR232_ADRR          (0x0001D000UL)   /*!< Sector 232 */
#define EFM_SECTOR233_ADRR          (0x0001D200UL)   /*!< Sector 233 */
#define EFM_SECTOR234_ADRR          (0x0001D400UL)   /*!< Sector 234 */
#define EFM_SECTOR235_ADRR          (0x0001D600UL)   /*!< Sector 235 */
#define EFM_SECTOR236_ADRR          (0x0001D800UL)   /*!< Sector 236 */
#define EFM_SECTOR237_ADRR          (0x0001DA00UL)   /*!< Sector 237 */
#define EFM_SECTOR238_ADRR          (0x0001DC00UL)   /*!< Sector 238 */
#define EFM_SECTOR239_ADRR          (0x0001DE00UL)   /*!< Sector 239 */
#define EFM_SECTOR240_ADRR          (0x0001E000UL)   /*!< Sector 240 */
#define EFM_SECTOR241_ADRR          (0x0001E200UL)   /*!< Sector 241 */
#define EFM_SECTOR242_ADRR          (0x0001E400UL)   /*!< Sector 242 */
#define EFM_SECTOR243_ADRR          (0x0001E600UL)   /*!< Sector 243 */
#define EFM_SECTOR244_ADRR          (0x0001E800UL)   /*!< Sector 244 */
#define EFM_SECTOR245_ADRR          (0x0001EA00UL)   /*!< Sector 245 */
#define EFM_SECTOR246_ADRR          (0x0001EC00UL)   /*!< Sector 246 */
#define EFM_SECTOR247_ADRR          (0x0001EE00UL)   /*!< Sector 247 */
#define EFM_SECTOR248_ADRR          (0x0001F000UL)   /*!< Sector 248 */
#define EFM_SECTOR249_ADRR          (0x0001F200UL)   /*!< Sector 249 */
#define EFM_SECTOR250_ADRR          (0x0001F400UL)   /*!< Sector 250 */
#define EFM_SECTOR251_ADRR          (0x0001F600UL)   /*!< Sector 251 */
#define EFM_SECTOR252_ADRR          (0x0001F800UL)   /*!< Sector 252 */
#define EFM_SECTOR253_ADRR          (0x0001FA00UL)   /*!< Sector 253 */
#define EFM_SECTOR254_ADRR          (0x0001FC00UL)   /*!< Sector 254 */
#define EFM_SECTOR255_ADRR          (0x0001FE00UL)   /*!< Sector 255 */
/**
 * @}
 */

/**
 * @defgroup EFM_Status EFM Status
 * @{
 */
#define EFM_ON                      (0x00000000UL)   /*!< Flash Enable */
#define EFM_OFF                     (EFM_FSTP_FSTP)  /*!< Flash Disable */
/**
 * @}
 */

/**
 * @defgroup EFM_Wait_Cycle EFM Wait Cycle 
 * @{
 */
#define EFM_WAIT_CYCLE_0            (0x00000000UL)   /*!< Don't insert read wait cycle */
#define EFM_WAIT_CYCLE_1            (0x00000001UL)   /*!< Insert 1 read wait cycles */
#define EFM_WAIT_CYCLE_2            (0x00000002UL)   /*!< Insert 2 read wait cycles */
#define EFM_WAIT_CYCLE_3            (0x00000003UL)   /*!< Insert 3 read wait cycles */
#define EFM_WAIT_CYCLE_4            (0x00000004UL)   /*!< Insert 4 read wait cycles */
#define EFM_WAIT_CYCLE_5            (0x00000005UL)   /*!< Insert 5 read wait cycles */
#define EFM_WAIT_CYCLE_6            (0x00000006UL)   /*!< Insert 6 read wait cycles */
#define EFM_WAIT_CYCLE_7            (0x00000007UL)   /*!< Insert 7 read wait cycles */
/**
 * @}
 */

/**
 * @defgroup EFM_CacheRst_Func EFM data cache reset function
 * @{
 */
#define EFM_CACHERST_ON             (EFM_FRMC_CRST)  /*!< Enable data cache reset function */
#define EFM_CACHERST_OFF            (0x00000000UL)   /*!< Disable data cache reset function */
/**
 * @}
 */

/**
 * @defgroup EFM_InsCache_Func EFM instruction cache function
 * @{
 */
#define EFM_INSCACHE_ON             (EFM_FRMC_ICHE)  /*!< Enable instruction cache function */
#define EFM_INSCACHE_OFF            (0x00000000UL)   /*!< Disable instruction cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_DataCache_Func EFM data cache function
 * @{
 */
#define EFM_DATACACHE_ON            (EFM_FRMC_DCHE)  /*!< Enable data cache function */
#define EFM_DATACACHE_OFF           (0x00000000UL)   /*!< Disable data cache function */
/**
 * @}
 */

/**
 * @defgroup EFM_Bus_Status EFM Bus status while flash program or erase
 * @{
 */
#define EFM_BUS_BUSY                (0x00000000UL)      /*!< Bus busy while flash program or erase */
#define EFM_BUS_RELEASE             (EFM_FWMC_BUSHLDCTL)/*!< Bus release while flash program or erase */
/**
 * @}
 */

/**
 * @defgroup EFM_Mode_definition EFM program or erase mode definition
 * @{
 */
#define EFM_MODE_PROGRAMSINGLE      (0x00000010UL)         /*!< Program single mode */
#define EFM_MODE_PROGRAMREADBACK    (0x00000020UL)         /*!< Program and read back mode */
#define EFM_MODE_PROGRAMSEQUENCE    (0x00000030UL)         /*!< Program sequence mode */
#define EFM_MODE_ERASESECTOR        (0x00000040UL)         /*!< Sector erase */
#define EFM_MODE_ERASECHIP          (0x00000050UL)         /*!< Chip erase */
#define EFM_MODE_READONLY           (0x00000000UL)         /*!< Read only */
#define EFM_MODE_READONLY1          (0x00000060UL)         /*!< Read only */
#define EFM_MODE_READONLY2          (0x00000070UL)         /*!< Read only */
/**
 * @}
 */

/**
 * @defgroup EFM_Flag_definition EFM Flag definition
 * @{
 */
#define EFM_FLAG_PEWERR             (EFM_FSR_PEWERR)          /*!< EFM Programming/erase error flag.              */
#define EFM_FLAG_PEPRTERR           (EFM_FSR_PEPRTERR)        /*!< EFM Programming/erase protect area error flag. */
#define EFM_FLAG_PGMISMTCHERR       (EFM_FSR_PGMISMTCH)       /*!< EFM Programming  miss match error flag         */
#define EFM_FLAG_OPTEND             (EFM_FSR_OPTEND)          /*!< EFM End of Operation flag.                     */
#define EFM_FLAG_COLERR             (EFM_FSR_RDCOLERR)        /*!< EFM Read collide error flag.                   */
#define EFM_FLAG_RDY                (EFM_FSR_RDY)             /*!< EFM ready flag.                                */

#define EFM_CLR_FLAG_PEWERRCLR      (EFM_FSCLR_PEWERRCLR)     /*!< EFM Clear Programming/erase error flag.              */
#define EFM_CLR_FLAG_PEPRTERRCLR    (EFM_FSCLR_PEPRTERRCLR)   /*!< EFM Clear Programming/erase protect area error flag. */
#define EFM_CLR_FLAG_PGMISMTCHCLR   (EFM_FSCLR_PGMISMTCHCLR)  /*!< EFM Clear Programming  miss match error flag         */
#define EFM_CLR_FLAG_OPTENDCLR      (EFM_FSCLR_OPTENDCLR)     /*!< EFM Clear End of Operation flag.                     */
#define EFM_CLR_FLAG_COLERRCLR      (EFM_FSCLR_RDCOLERRCLR)   /*!< EFM Clear Read collide error flag.                   */

/**
 * @}
 */

/**
 * @defgroup EFM_Interrupt_definition EFM Interrupt definition
 * @{
 */
#define EFM_INT_EOP                 (EFM_FITE_OPTENDITE)      /*!< End of EFM Operation Interrupt source      */
#define EFM_INT_PEERR               (EFM_FITE_PEERRITE)       /*!< Program/erase error Interrupt source       */
#define EFM_INT_RDCOLERR            (EFM_FITE_RDCOLERRITE)    /*!< Read collide error Interrupt source        */
#define EFM_INT_PEERR_OPTEND        (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_OPTENDITE)       /*!< Program/erase error and End of EFM operation */
#define EFM_INT_PEERR_RDCOLERR      (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_RDCOLERRITE)     /*!< Program/erase error and Read collide error*/
#define EFM_INT_OPTEND_RDCOLERR     (EFM_FITE_OPTENDITE |  \
                                    EFM_FITE_RDCOLERRITE)     /*!< End of EFM operation and Read collide error*/
#define EFM_INT_ALL                 (EFM_FITE_PEERRITE  |  \
                                    EFM_FITE_OPTENDITE  |  \
                                    EFM_FITE_RDCOLERRITE)     /*!< Program/erase error and End of EFM operation \
                                                                   and Read collide error Interrupt source */
/**
 * @}
 */

/**
 * @defgroup EFM_Keys EFM Keys
 * @{
 */
#define EFM_KEY1                    (0x0123U)
#define EFM_KEY2                    (0x3210U)
/**
 * @}
 */


/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EFM_Global_Functions
 * @{
 */

void EFM_Unlock(void);
void EFM_Lock(void);

void EFM_Cmd(uint32_t u32efmstatus);
void EFM_SetWaitCycle(uint32_t u32WaitCycle);
void EFM_SetBusStatus(uint32_t u32Status);
void EFM_DataCacheCmd(en_functional_state_t enNewState);
void EFM_DataCacheRstCmd(en_functional_state_t enNewState);
void EFM_InsCacheCmd(en_functional_state_t enNewState);
void EFM_SetWinProtectAddr(uint32_t u32StartAddr, uint32_t u32EndAddr);
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState);
void EFM_SetOperateMode(uint32_t u32PeMode);
void EFM_ClearFlag(uint32_t u32Flag);

en_result_t EFM_StrucInit(stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg);
en_result_t EFM_ProgramWord(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_ProgramHalfWord(uint32_t u32Addr, uint16_t u16Data);
en_result_t EFM_ProgramWordRB(uint32_t u32Addr, uint32_t u32Data);
en_result_t EFM_ProgramHalfWordRB(uint32_t u32Addr, uint16_t u16Data);
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, uint8_t *u8pBuf);
en_result_t EFM_SectorErase(uint32_t u32Addr);
en_result_t EFM_ChipErase(void);

en_flag_status_t EFM_GetFlagStatus(uint32_t u32Flag);
stc_efm_unique_id_t EFM_ReadUID(void);
/**
 * @}
 */

#endif /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_EFM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
