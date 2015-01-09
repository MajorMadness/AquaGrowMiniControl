#include <Wire.h>
#include <RTClib.h>
#include <PCA9685.h>
#include <avr/pgmspace.h>
#include <Timer.h>
#include <OneWire.h>
#include <MemoryFree.h>
#include <Keypad.h>  
#include <Keypad_I2C.h>  
#include <EEPROM.h>
#include "writeAnything.h" 
#include "structs.h"
#include "config.h"

#include <MicroLCD.h>
LCD_SSD1306 lcd; 

//#include <LiquidCrystal_I2C.h>
//#define LCD_ADR 0x27      // Adresse LCD
//LiquidCrystal_I2C lcd(LCD_ADR,2,1,0,4,5,6,7,3,POSITIVE);   // Set the LCD I2C address

Timer t;
RTC_DS1307 rtc;
PCA9685 ledDriver; 
OneWire  ds(PIN_TEMP);
boolean pumpReset=false;


boolean manualLight=false;
float temperatur;
unsigned long last_print = 0;
String inputString = "";
boolean stringComplete = false;


PROGMEM prog_uint16_t pwmtable[] = {0,2,4,7,9,11,13,15,18,20,22,24,26,29,31,33,35,37,39,42,44,46,48,50,53,55,57,59,61,64,66,68,70,72,74,77,79,81,83,85,87,90,92,94,96,98,101,103,105,107,109,111,114,116,118,120,122,124,127,129,131,133,135,137,139,142,144,146,148,150,152,155,157,159,161,163,165,167,170,172,174,176,178,180,183,185,187,189,191,193,195,198,200,202,204,206,208,210,213,215,217,219,221,223,225,227,230,232,234,236,238,240,242,244,247,249,251,253,255,257,259,261,264,266,268,270,272,274,276,278,281,283,285,287,289,291,293,295,297,300,302,304,306,308,310,312,314,316,319,321,323,325,327,329,331,333,335,337,340,342,344,346,348,350,352,354,356,358,361,363,365,367,369,371,373,375,377,379,381,384,386,388,390,392,394,396,398,400,402,404,406,408,411,413,415,417,419,421,423,425,427,429,431,433,435,437,440,442,444,446,448,450,452,454,456,458,460,462,464,466,468,471,473,475,477,479,481,483,485,487,489,491,493,495,497,499,501,503,505,507,510,512,514,516,518,520,522,524,526,528,530,532,534,536,538,540,542,544,546,548,550,552,554,556,558,560,562,565,567,569,571,573,575,577,579,581,583,585,587,589,591,593,595,597,599,601,603,605,607,609,611,613,615,617,619,621,623,625,627,629,631,633,635,637,639,641,643,645,647,649,651,653,655,657,659,661,663,665,667,669,671,673,675,677,679,681,683,685,687,689,691,693,695,697,699,701,703,705,707,709,711,713,715,717,719,721,723,725,727,729,731,733,735,737,739,741,743,745,747,749,750,752,754,756,758,760,762,764,766,768,770,772,774,776,778,780,782,784,786,788,790,792,794,796,798,800,801,803,805,807,809,811,813,815,817,819,821,823,825,827,829,831,833,835,837,838,840,842,844,846,848,850,852,854,856,858,860,862,864,866,868,869,871,873,875,877,879,881,883,885,887,889,891,893,895,896,898,900,902,904,906,908,910,912,914,916,918,919,921,923,925,927,929,931,933,935,937,939,940,942,944,946,948,950,952,954,956,958,960,961,963,965,967,969,971,973,975,977,979,980,982,984,986,988,990,992,994,996,997,999,1001,1003,1005,1007,1009,1011,1013,1014,1016,1018,1020,1022,1024,1026,1028,1029,1031,1033,1035,1037,1039,1041,1043,1044,1046,1048,1050,1052,1054,1056,1058,1059,1061,1063,1065,1067,1069,1071,1073,1074,1076,1078,1080,1082,1084,1086,1087,1089,1091,1093,1095,1097,1099,1100,1102,1104,1106,1108,1110,1112,1113,1115,1117,1119,1121,1123,1124,1126,1128,1130,1132,1134,1136,1137,1139,1141,1143,1145,1147,1148,1150,1152,1154,1156,1158,1159,1161,1163,1165,1167,1169,1170,1172,1174,1176,1178,1180,1181,1183,1185,1187,1189,1191,1192,1194,1196,1198,1200,1201,1203,1205,1207,1209,1211,1212,1214,1216,1218,1220,1221,1223,1225,1227,1229,1231,1232,1234,1236,1238,1240,1241,1243,1245,1247,1249,1250,1252,1254,1256,1258,1259,1261,1263,1265,1267,1268,1270,1272,1274,1276,1277,1279,1281,1283,1285,1286,1288,1290,1292,1294,1295,1297,1299,1301,1302,1304,1306,1308,1310,1311,1313,1315,1317,1318,1320,1322,1324,1326,1327,1329,1331,1333,1334,1336,1338,1340,1342,1343,1345,1347,1349,1350,1352,1354,1356,1357,1359,1361,1363,1365,1366,1368,1370,1372,1373,1375,1377,1379,1380,1382,1384,1386,1387,1389,1391,1393,1394,1396,1398,1400,1401,1403,1405,1407,1408,1410,1412,1414,1415,1417,1419,1421,1422,1424,1426,1428,1429,1431,1433,1435,1436,1438,1440,1442,1443,1445,1447,1448,1450,1452,1454,1455,1457,1459,1461,1462,1464,1466,1468,1469,1471,1473,1474,1476,1478,1480,1481,1483,1485,1486,1488,1490,1492,1493,1495,1497,1499,1500,1502,1504,1505,1507,1509,1511,1512,1514,1516,1517,1519,1521,1522,1524,1526,1528,1529,1531,1533,1534,1536,1538,1540,1541,1543,1545,1546,1548,1550,1551,1553,1555,1556,1558,1560,1562,1563,1565,1567,1568,1570,1572,1573,1575,1577,1578,1580,1582,1584,1585,1587,1589,1590,1592,1594,1595,1597,1599,1600,1602,1604,1605,1607,1609,1610,1612,1614,1615,1617,1619,1620,1622,1624,1625,1627,1629,1630,1632,1634,1635,1637,1639,1640,1642,1644,1645,1647,1649,1650,1652,1654,1655,1657,1659,1660,1662,1664,1665,1667,1669,1670,1672,1674,1675,1677,1679,1680,1682,1684,1685,1687,1688,1690,1692,1693,1695,1697,1698,1700,1702,1703,1705,1707,1708,1710,1711,1713,1715,1716,1718,1720,1721,1723,1725,1726,1728,1729,1731,1733,1734,1736,1738,1739,1741,1742,1744,1746,1747,1749,1751,1752,1754,1755,1757,1759,1760,1762,1764,1765,1767,1768,1770,1772,1773,1775,1776,1778,1780,1781,1783,1785,1786,1788,1789,1791,1793,1794,1796,1797,1799,1801,1802,1804,1805,1807,1809,1810,1812,1813,1815,1817,1818,1820,1821,1823,1825,1826,1828,1829,1831,1833,1834,1836,1837,1839,1841,1842,1844,1845,1847,1848,1850,1852,1853,1855,1856,1858,1860,1861,1863,1864,1866,1867,1869,1871,1872,1874,1875,1877,1878,1880,1882,1883,1885,1886,1888,1889,1891,1893,1894,1896,1897,1899,1900,1902,1904,1905,1907,1908,1910,1911,1913,1915,1916,1918,1919,1921,1922,1924,1925,1927,1929,1930,1932,1933,1935,1936,1938,1939,1941,1942,1944,1946,1947,1949,1950,1952,1953,1955,1956,1958,1959,1961,1963,1964,1966,1967,1969,1970,1972,1973,1975,1976,1978,1979,1981,1983,1984,1986,1987,1989,1990,1992,1993,1995,1996,1998,1999,2001,2002,2004,2005,2007,2009,2010,2012,2013,2015,2016,2018,2019,2021,2022,2024,2025,2027,2028,2030,2031,2033,2034,2036,2037,2039,2040,2042,2043,2045,2046,2048,2049,2051,2052,2054,2055,2057,2058,2060,2061,2063,2064,2066,2067,2069,2070,2072,2073,2075,2076,2078,2079,2081,2082,2084,2085,2087,2088,2090,2091,2093,2094,2096,2097,2099,2100,2102,2103,2105,2106,2108,2109,2111,2112,2114,2115,2117,2118,2120,2121,2123,2124,2125,2127,2128,2130,2131,2133,2134,2136,2137,2139,2140,2142,2143,2145,2146,2148,2149,2150,2152,2153,2155,2156,2158,2159,2161,2162,2164,2165,2167,2168,2169,2171,2172,2174,2175,2177,2178,2180,2181,2183,2184,2185,2187,2188,2190,2191,2193,2194,2196,2197,2199,2200,2201,2203,2204,2206,2207,2209,2210,2212,2213,2214,2216,2217,2219,2220,2222,2223,2224,2226,2227,2229,2230,2232,2233,2234,2236,2237,2239,2240,2242,2243,2244,2246,2247,2249,2250,2252,2253,2254,2256,2257,2259,2260,2262,2263,2264,2266,2267,2269,2270,2271,2273,2274,2276,2277,2279,2280,2281,2283,2284,2286,2287,2288,2290,2291,2293,2294,2295,2297,2298,2300,2301,2302,2304,2305,2307,2308,2309,2311,2312,2314,2315,2316,2318,2319,2321,2322,2323,2325,2326,2328,2329,2330,2332,2333,2335,2336,2337,2339,2340,2341,2343,2344,2346,2347,2348,2350,2351,2353,2354,2355,2357,2358,2359,2361,2362,2364,2365,2366,2368,2369,2370,2372,2373,2375,2376,2377,2379,2380,2381,2383,2384,2386,2387,2388,2390,2391,2392,2394,2395,2396,2398,2399,2400,2402,2403,2405,2406,2407,2409,2410,2411,2413,2414,2415,2417,2418,2419,2421,2422,2424,2425,2426,2428,2429,2430,2432,2433,2434,2436,2437,2438,2440,2441,2442,2444,2445,2446,2448,2449,2450,2452,2453,2454,2456,2457,2458,2460,2461,2462,2464,2465,2466,2468,2469,2470,2472,2473,2474,2476,2477,2478,2480,2481,2482,2484,2485,2486,2488,2489,2490,2492,2493,2494,2496,2497,2498,2499,2501,2502,2503,2505,2506,2507,2509,2510,2511,2513,2514,2515,2517,2518,2519,2520,2522,2523,2524,2526,2527,2528,2530,2531,2532,2533,2535,2536,2537,2539,2540,2541,2543,2544,2545,2546,2548,2549,2550,2552,2553,2554,2555,2557,2558,2559,2561,2562,2563,2565,2566,2567,2568,2570,2571,2572,2574,2575,2576,2577,2579,2580,2581,2582,2584,2585,2586,2588,2589,2590,2591,2593,2594,2595,2596,2598,2599,2600,2602,2603,2604,2605,2607,2608,2609,2610,2612,2613,2614,2615,2617,2618,2619,2621,2622,2623,2624,2626,2627,2628,2629,2631,2632,2633,2634,2636,2637,2638,2639,2641,2642,2643,2644,2646,2647,2648,2649,2651,2652,2653,2654,2656,2657,2658,2659,2661,2662,2663,2664,2666,2667,2668,2669,2670,2672,2673,2674,2675,2677,2678,2679,2680,2682,2683,2684,2685,2687,2688,2689,2690,2691,2693,2694,2695,2696,2698,2699,2700,2701,2702,2704,2705,2706,2707,2709,2710,2711,2712,2713,2715,2716,2717,2718,2719,2721,2722,2723,2724,2726,2727,2728,2729,2730,2732,2733,2734,2735,2736,2738,2739,2740,2741,2742,2744,2745,2746,2747,2748,2750,2751,2752,2753,2754,2756,2757,2758,2759,2760,2762,2763,2764,2765,2766,2768,2769,2770,2771,2772,2773,2775,2776,2777,2778,2779,2781,2782,2783,2784,2785,2787,2788,2789,2790,2791,2792,2794,2795,2796,2797,2798,2799,2801,2802,2803,2804,2805,2807,2808,2809,2810,2811,2812,2814,2815,2816,2817,2818,2819,2821,2822,2823,2824,2825,2826,2827,2829,2830,2831,2832,2833,2834,2836,2837,2838,2839,2840,2841,2843,2844,2845,2846,2847,2848,2849,2851,2852,2853,2854,2855,2856,2857,2859,2860,2861,2862,2863,2864,2865,2867,2868,2869,2870,2871,2872,2873,2875,2876,2877,2878,2879,2880,2881,2883,2884,2885,2886,2887,2888,2889,2890,2892,2893,2894,2895,2896,2897,2898,2899,2901,2902,2903,2904,2905,2906,2907,2908,2910,2911,2912,2913,2914,2915,2916,2917,2918,2920,2921,2922,2923,2924,2925,2926,2927,2928,2930,2931,2932,2933,2934,2935,2936,2937,2938,2940,2941,2942,2943,2944,2945,2946,2947,2948,2949,2951,2952,2953,2954,2955,2956,2957,2958,2959,2960,2961,2963,2964,2965,2966,2967,2968,2969,2970,2971,2972,2973,2975,2976,2977,2978,2979,2980,2981,2982,2983,2984,2985,2986,2988,2989,2990,2991,2992,2993,2994,2995,2996,2997,2998,2999,3000,3001,3003,3004,3005,3006,3007,3008,3009,3010,3011,3012,3013,3014,3015,3016,3017,3019,3020,3021,3022,3023,3024,3025,3026,3027,3028,3029,3030,3031,3032,3033,3034,3035,3037,3038,3039,3040,3041,3042,3043,3044,3045,3046,3047,3048,3049,3050,3051,3052,3053,3054,3055,3056,3057,3058,3060,3061,3062,3063,3064,3065,3066,3067,3068,3069,3070,3071,3072,3073,3074,3075,3076,3077,3078,3079,3080,3081,3082,3083,3084,3085,3086,3087,3088,3089,3090,3091,3092,3093,3095,3096,3097,3098,3099,3100,3101,3102,3103,3104,3105,3106,3107,3108,3109,3110,3111,3112,3113,3114,3115,3116,3117,3118,3119,3120,3121,3122,3123,3124,3125,3126,3127,3128,3129,3130,3131,3132,3133,3134,3135,3136,3137,3138,3139,3140,3141,3142,3143,3144,3145,3146,3147,3148,3149,3150,3151,3152,3153,3154,3155,3156,3157,3158,3159,3160,3161,3162,3163,3164,3165,3166,3166,3167,3168,3169,3170,3171,3172,3173,3174,3175,3176,3177,3178,3179,3180,3181,3182,3183,3184,3185,3186,3187,3188,3189,3190,3191,3192,3193,3194,3195,3196,3197,3198,3198,3199,3200,3201,3202,3203,3204,3205,3206,3207,3208,3209,3210,3211,3212,3213,3214,3215,3216,3217,3218,3219,3219,3220,3221,3222,3223,3224,3225,3226,3227,3228,3229,3230,3231,3232,3233,3234,3235,3236,3236,3237,3238,3239,3240,3241,3242,3243,3244,3245,3246,3247,3248,3249,3250,3250,3251,3252,3253,3254,3255,3256,3257,3258,3259,3260,3261,3262,3263,3263,3264,3265,3266,3267,3268,3269,3270,3271,3272,3273,3274,3274,3275,3276,3277,3278,3279,3280,3281,3282,3283,3284,3285,3285,3286,3287,3288,3289,3290,3291,3292,3293,3294,3294,3295,3296,3297,3298,3299,3300,3301,3302,3303,3303,3304,3305,3306,3307,3308,3309,3310,3311,3312,3312,3313,3314,3315,3316,3317,3318,3319,3320,3320,3321,3322,3323,3324,3325,3326,3327,3328,3328,3329,3330,3331,3332,3333,3334,3335,3335,3336,3337,3338,3339,3340,3341,3342,3342,3343,3344,3345,3346,3347,3348,3349,3349,3350,3351,3352,3353,3354,3355,3355,3356,3357,3358,3359,3360,3361,3362,3362,3363,3364,3365,3366,3367,3368,3368,3369,3370,3371,3372,3373,3374,3374,3375,3376,3377,3378,3379,3379,3380,3381,3382,3383,3384,3385,3385,3386,3387,3388,3389,3390,3390,3391,3392,3393,3394,3395,3396,3396,3397,3398,3399,3400,3401,3401,3402,3403,3404,3405,3406,3406,3407,3408,3409,3410,3411,3411,3412,3413,3414,3415,3416,3416,3417,3418,3419,3420,3420,3421,3422,3423,3424,3425,3425,3426,3427,3428,3429,3429,3430,3431,3432,3433,3434,3434,3435,3436,3437,3438,3438,3439,3440,3441,3442,3442,3443,3444,3445,3446,3446,3447,3448,3449,3450,3451,3451,3452,3453,3454,3455,3455,3456,3457,3458,3459,3459,3460,3461,3462,3462,3463,3464,3465,3466,3466,3467,3468,3469,3470,3470,3471,3472,3473,3474,3474,3475,3476,3477,3477,3478,3479,3480,3481,3481,3482,3483,3484,3485,3485,3486,3487,3488,3488,3489,3490,3491,3492,3492,3493,3494,3495,3495,3496,3497,3498,3498,3499,3500,3501,3502,3502,3503,3504,3505,3505,3506,3507,3508,3508,3509,3510,3511,3511,3512,3513,3514,3514,3515,3516,3517,3518,3518,3519,3520,3521,3521,3522,3523,3524,3524,3525,3526,3527,3527,3528,3529,3530,3530,3531,3532,3533,3533,3534,3535,3535,3536,3537,3538,3538,3539,3540,3541,3541,3542,3543,3544,3544,3545,3546,3547,3547,3548,3549,3550,3550,3551,3552,3552,3553,3554,3555,3555,3556,3557,3558,3558,3559,3560,3560,3561,3562,3563,3563,3564,3565,3565,3566,3567,3568,3568,3569,3570,3571,3571,3572,3573,3573,3574,3575,3576,3576,3577,3578,3578,3579,3580,3581,3581,3582,3583,3583,3584,3585,3585,3586,3587,3588,3588,3589,3590,3590,3591,3592,3593,3593,3594,3595,3595,3596,3597,3597,3598,3599,3599,3600,3601,3602,3602,3603,3604,3604,3605,3606,3606,3607,3608,3608,3609,3610,3611,3611,3612,3613,3613,3614,3615,3615,3616,3617,3617,3618,3619,3619,3620,3621,3621,3622,3623,3623,3624,3625,3626,3626,3627,3628,3628,3629,3630,3630,3631,3632,3632,3633,3634,3634,3635,3636,3636,3637,3638,3638,3639,3640,3640,3641,3642,3642,3643,3644,3644,3645,3646,3646,3647,3648,3648,3649,3649,3650,3651,3651,3652,3653,3653,3654,3655,3655,3656,3657,3657,3658,3659,3659,3660,3661,3661,3662,3662,3663,3664,3664,3665,3666,3666,3667,3668,3668,3669,3670,3670,3671,3671,3672,3673,3673,3674,3675,3675,3676,3677,3677,3678,3678,3679,3680,3680,3681,3682,3682,3683,3684,3684,3685,3685,3686,3687,3687,3688,3689,3689,3690,3690,3691,3692,3692,3693,3693,3694,3695,3695,3696,3697,3697,3698,3698,3699,3700,3700,3701,3702,3702,3703,3703,3704,3705,3705,3706,3706,3707,3708,3708,3709,3709,3710,3711,3711,3712,3712,3713,3714,3714,3715,3715,3716,3717,3717,3718,3718,3719,3720,3720,3721,3721,3722,3723,3723,3724,3724,3725,3726,3726,3727,3727,3728,3729,3729,3730,3730,3731,3732,3732,3733,3733,3734,3734,3735,3736,3736,3737,3737,3738,3739,3739,3740,3740,3741,3741,3742,3743,3743,3744,3744,3745,3745,3746,3747,3747,3748,3748,3749,3749,3750,3751,3751,3752,3752,3753,3753,3754,3755,3755,3756,3756,3757,3757,3758,3759,3759,3760,3760,3761,3761,3762,3762,3763,3764,3764,3765,3765,3766,3766,3767,3767,3768,3769,3769,3770,3770,3771,3771,3772,3772,3773,3774,3774,3775,3775,3776,3776,3777,3777,3778,3778,3779,3780,3780,3781,3781,3782,3782,3783,3783,3784,3784,3785,3786,3786,3787,3787,3788,3788,3789,3789,3790,3790,3791,3791,3792,3792,3793,3794,3794,3795,3795,3796,3796,3797,3797,3798,3798,3799,3799,3800,3800,3801,3801,3802,3802,3803,3803,3804,3805,3805,3806,3806,3807,3807,3808,3808,3809,3809,3810,3810,3811,3811,3812,3812,3813,3813,3814,3814,3815,3815,3816,3816,3817,3817,3818,3818,3819,3819,3820,3820,3821,3821,3822,3822,3823,3823,3824,3824,3825,3825,3826,3826,3827,3827,3828,3828,3829,3829,3830,3830,3831,3831,3832,3832,3833,3833,3834,3834,3835,3835,3836,3836,3837,3837,3838,3838,3839,3839,3840,3840,3841,3841,3842,3842,3843,3843,3844,3844,3844,3845,3845,3846,3846,3847,3847,3848,3848,3849,3849,3850,3850,3851,3851,3852,3852,3853,3853,3854,3854,3854,3855,3855,3856,3856,3857,3857,3858,3858,3859,3859,3860,3860,3860,3861,3861,3862,3862,3863,3863,3864,3864,3865,3865,3866,3866,3866,3867,3867,3868,3868,3869,3869,3870,3870,3871,3871,3871,3872,3872,3873,3873,3874,3874,3875,3875,3875,3876,3876,3877,3877,3878,3878,3879,3879,3879,3880,3880,3881,3881,3882,3882,3883,3883,3883,3884,3884,3885,3885,3886,3886,3886,3887,3887,3888,3888,3889,3889,3889,3890,3890,3891,3891,3892,3892,3892,3893,3893,3894,3894,3895,3895,3895,3896,3896,3897,3897,3898,3898,3898,3899,3899,3900,3900,3901,3901,3901,3902,3902,3903,3903,3903,3904,3904,3905,3905,3905,3906,3906,3907,3907,3908,3908,3908,3909,3909,3910,3910,3910,3911,3911,3912,3912,3912,3913,3913,3914,3914,3914,3915,3915,3916,3916,3916,3917,3917,3918,3918,3918,3919,3919,3920,3920,3920,3921,3921,3922,3922,3922,3923,3923,3924,3924,3924,3925,3925,3925,3926,3926,3927,3927,3927,3928,3928,3929,3929,3929,3930,3930,3930,3931,3931,3932,3932,3932,3933,3933,3933,3934,3934,3935,3935,3935,3936,3936,3936,3937,3937,3938,3938,3938,3939,3939,3939,3940,3940,3941,3941,3941,3942,3942,3942,3943,3943,3943,3944,3944,3945,3945,3945,3946,3946,3946,3947,3947,3947,3948,3948,3949,3949,3949,3950,3950,3950,3951,3951,3951,3952,3952,3952,3953,3953,3954,3954,3954,3955,3955,3955,3956,3956,3956,3957,3957,3957,3958,3958,3958,3959,3959,3959,3960,3960,3960,3961,3961,3961,3962,3962,3962,3963,3963,3963,3964,3964,3964,3965,3965,3966,3966,3966,3967,3967,3967,3968,3968,3968,3968,3969,3969,3969,3970,3970,3970,3971,3971,3971,3972,3972,3972,3973,3973,3973,3974,3974,3974,3975,3975,3975,3976,3976,3976,3977,3977,3977,3978,3978,3978,3979,3979,3979,3979,3980,3980,3980,3981,3981,3981,3982,3982,3982,3983,3983,3983,3983,3984,3984,3984,3985,3985,3985,3986,3986,3986,3987,3987,3987,3987,3988,3988,3988,3989,3989,3989,3990,3990,3990,3990,3991,3991,3991,3992,3992,3992,3993,3993,3993,3993,3994,3994,3994,3995,3995,3995,3995,3996,3996,3996,3997,3997,3997,3997,3998,3998,3998,3999,3999,3999,3999,4000,4000,4000,4001,4001,4001,4001,4002,4002,4002,4003,4003,4003,4003,4004,4004,4004,4004,4005,4005,4005,4006,4006,4006,4006,4007,4007,4007,4007,4008,4008,4008,4009,4009,4009,4009,4010,4010,4010,4010,4011,4011,4011,4011,4012,4012,4012,4013,4013,4013,4013,4014,4014,4014,4014,4015,4015,4015,4015,4016,4016,4016,4016,4017,4017,4017,4017,4018,4018,4018,4018,4019,4019,4019,4019,4020,4020,4020,4020,4021,4021,4021,4021,4022,4022,4022,4022,4023,4023,4023,4023,4024,4024,4024,4024,4025,4025,4025,4025,4026,4026,4026,4026,4026,4027,4027,4027,4027,4028,4028,4028,4028,4029,4029,4029,4029,4030,4030,4030,4030,4030,4031,4031,4031,4031,4032,4032,4032,4032,4032,4033,4033,4033,4033,4034,4034,4034,4034,4034,4035,4035,4035,4035,4036,4036,4036,4036,4036,4037,4037,4037,4037,4038,4038,4038,4038,4038,4039,4039,4039,4039,4039,4040,4040,4040,4040,4040,4041,4041,4041,4041,4042,4042,4042,4042,4042,4043,4043,4043,4043,4043,4044,4044,4044,4044,4044,4045,4045,4045,4045,4045,4046,4046,4046,4046,4046,4047,4047,4047,4047,4047,4048,4048,4048,4048,4048,4048,4049,4049,4049,4049,4049,4050,4050,4050,4050,4050,4051,4051,4051,4051,4051,4051,4052,4052,4052,4052,4052,4053,4053,4053,4053,4053,4053,4054,4054,4054,4054,4054,4055,4055,4055,4055,4055,4055,4056,4056,4056,4056,4056,4056,4057,4057,4057,4057,4057,4058,4058,4058,4058,4058,4058,4059,4059,4059,4059,4059,4059,4060,4060,4060,4060,4060,4060,4061,4061,4061,4061,4061,4061,4061,4062,4062,4062,4062,4062,4062,4063,4063,4063,4063,4063,4063,4064,4064,4064,4064,4064,4064,4064,4065,4065,4065,4065,4065,4065,4065,4066,4066,4066,4066,4066,4066,4067,4067,4067,4067,4067,4067,4067,4068,4068,4068,4068,4068,4068,4068,4069,4069,4069,4069,4069,4069,4069,4070,4070,4070,4070,4070,4070,4070,4070,4071,4071,4071,4071,4071,4071,4071,4072,4072,4072,4072,4072,4072,4072,4072,4073,4073,4073,4073,4073,4073,4073,4073,4074,4074,4074,4074,4074,4074,4074,4074,4075,4075,4075,4075,4075,4075,4075,4075,4076,4076,4076,4076,4076,4076,4076,4076,4076,4077,4077,4077,4077,4077,4077,4077,4077,4078,4078,4078,4078,4078,4078,4078,4078,4078,4078,4079,4079,4079,4079,4079,4079,4079,4079,4079,4080,4080,4080,4080,4080,4080,4080,4080,4080,4080,4081,4081,4081,4081,4081,4081,4081,4081,4081,4081,4082,4082,4082,4082,4082,4082,4082,4082,4082,4082,4083,4083,4083,4083,4083,4083,4083,4083,4083,4083,4083,4084,4084,4084,4084,4084,4084,4084,4084,4084,4084,4084,4084,4085,4085,4085,4085,4085,4085,4085,4085,4085,4085,4085,4085,4086,4086,4086,4086,4086,4086,4086,4086,4086,4086,4086,4086,4087,4087,4087,4087,4087,4087,4087,4087,4087,4087,4087,4087,4087,4087,4088,4088,4088,4088,4088,4088,4088,4088,4088,4088,4088,4088,4088,4088,4088,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4089,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4090,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4091,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4092,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4093,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4094,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095,4095};

 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

//char holdKey;
unsigned long t_hold;

//initialize an instance of class NewKeypad
Keypad_I2C keypad = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYPADI2C );


void setup() {

  Wire.begin();
  rtc.begin();
  keypad.begin( );  
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  
  
  Serial.begin(9600);

  ledDriver.begin(LED_DRV);
  ledDriver.init();
  lcd.begin();
    lcd.setCursor(0,0); 
    lcd.print(F("AquaGrow MiniControl"));
  for (int i=0;i<=PUMPCOUNTS;i++){
    pinMode(dosing[i].pinAddr, OUTPUT);
  }
  inputString.reserve(20);
  
}

void loop() {
  rtc.now();
  t.update();
  char key = keypad.getKey();
  
//  if (key) {
//    Serial.println(key);
//  }
 
/*
      if (keypad.getState() == HOLD && key && (millis() - t_hold) > 500 ) {
        Serial.println(key);
        if(key=='A'||key=='B'||key=='C'||key=='D'||key=='#'||key=='*'){
      }else{
        Serial.print(F(" keySWITCH1"));
        t_hold = millis();
        switch_holdKey(key);
      }
    } 
*/
  // print the string when a newline arrives:
  if (stringComplete) {
    serialHandler(inputString);
    inputString = "";
    stringComplete = false;
  }

      // Licht Dimmen
    if(!manualLight){
      setLight();
    }
  if (millis() - last_print > 1000) {
    last_print = millis();
    
    Serial.println(retTime());
//    Serial.println(freeMemory());
    
    setDosing();
    
    temperatur = getTemp();
    if(coolingTemp+2.0 < temperatur){
        analogWrite(PIN_PWM,pwmValue);
    }else if(coolingTemp-2.0 > temperatur){
        analogWrite(PIN_PWM,0);
    }
    
    printTime();
    printTemp(temperatur);

  }            
}

float getTemp(){
  byte present = 0;
  byte data[12];
  byte addr[8];
  ds.search(addr);
      
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); 
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  
  return (float)raw / 16.0; //celsius;
}
