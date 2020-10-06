#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEN_MB (3*512*1024*1024)

int main() {
    int* ptr;
    for (int i = 0; i < 10; i++) {
        ptr = malloc(TEN_MB);
        memset(ptr, 0, TEN_MB);
        sleep(1);
    }
    return 0;
}

/* for 10 MB:
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0      0 11054616 151120 2635916    0    0   188   111  792 1309  3  2 92  3  0
 1  0      0 11043764 151120 2635956    0    0     0     0 5444 9340  2  1 98  0  0
 0  0      0 11033180 151128 2635948    0    0     0    68 5436 9393  1  1 97  0  0
 0  0      0 11023100 151128 2635956    0    0     0  1708 5512 9486  1  1 97  0  0
 0  0      0 11010508 151128 2637908    0    0     0     0 8299 12002  2  2 96  0  0
 1  0      0 10998924 151128 2637960    0    0     0     0 5555 9528  2  1 97  0  0
 0  0      0 10988592 151128 2637960    0    0     0     0 5655 9780  2  1 97  0  0
 1  0      0 10978252 151128 2637960    0    0     0     0 5400 9311  2  2 97  0  0
 0  0      0 11079400 151136 2637952    0    0     0   612 5473 9499  2  1 96  1  0
 1  0      0 11079564 151136 2637960    0    0     0     0 5465 9271  1  1 98  0  0
 1  0      0 11079564 151136 2637960    0    0     0     0 5574 9565  2  1 97  0  0
*/
/*
    So si and so weren't changed as there was a lot of physical memory present
*/


/* for 1.5 GB:
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  0      0 8997228 152008 2690100    0    0   146    89  778 1295  3  2 93  2  0
 0  0      0 7872048 152016 2690100    0    0     0   124 1827 2856  1  4 95  0  0
 0  0      0 6297804 152016 2690100    0    0     0   112 1770 2789  2  4 94  0  0
 2  0      0 4922388 152016 2690100    0    0     0     0 1670 2647  1  4 95  0  0
 1  0      0 4721932 152016 2690100    0    0     0     0 1531 2528  1  1 98  0  0
 1  0      0 3147048 152016 2690100    0    0     0     0 1708 2736  2  4 94  0  0
 3  0      0 1572048 152016 2690100    0    0     0     0 1682 2649  1  5 94  0  0
 2  0      0 885096 152024 2690100    0    0     0    56 1776 2764  1  2 96  0  0
 2  0   1036 204108 149164 2483660    0  736   128  1428 2388 3668  1  5 93  1  0
 2  0  13836 291572  23908 980156   32 12688   464 12688 3273 4704  2 12 85  1  0
 2  0  16384 135248   2648 441744    0 2444  4288  3252 3199 4783  1  8 88  2  0
 2 35 546816 139124   1264 215556  748 738480 54327 738592 31572 39511  0  4  9 86  0
 1 24 847116 134332   2900 226028  340 91568 10263 91568 8032 9322  0  3 14 83  0
 1 27 914700 134440   2532 225124   52 67712  2804 67712 2506 2511  0  3  7 89  0
 0 37 1142016 133148   1940 222428 1016 300164 28003 300164 13094 17631  0  3  1 96  0
 1 38 1280000 147728   2420 222648  120 65936  2156 65936 3907 6164  0  2  0 98  0
 0 34 1331468 151020   1604 225696  152 51364  4763 51376 1358 1840  0  2  0 98  0
 0 34 1398016 135960   1816 225444  256 66936  2351 66940 1732 2261  0  3  0 96  0
 0 34 1453352 140976   1700 226124  352 55372  2877 55372 2057 2265  0  3  0 97  0
 0 38 1530880 134904   1784 224040  172 78268  1124 78268 2315 2501  0  4  0 96  0
 0 38 1569792 150024   2160 218060  492 39144  4439 39144 2043 2645  0  2  0 98  0
procs ----RU
488 144516   1196 213480  184 65164  2033 65164 2590 3152  0  3  0 97  0
 0 34 1854208 134020   1164 210672  224 62756  4328 62760 3159 3220  0  4  2 94  0
 0 36 1879040 134660   1268 213852   80 25128  4966 25140 1393 1899  0  1  6 93  0
 0 35 1955088 133292   1428 213812  216 76308  4612 76308 2149 2687  0  4  1 94  0
 0 35 2014976 137012   2040 213236  220 59568  5104 59568 3602 2579  0  4  0 96  0
 1 35 2073856 161616   1984 215220  196 58876  6808 58876 4082 2510  0  4  0 96  0
 0 38 2092280 147140   2024 214608  200 20164  3409 20164 2272 2925  0  2  0 98  0
 0 33 2092516 142424   2472 219156  124 1836  5008  1836 1890 2379  0  1  0 99  0
 0 30 2093484 134424   2504 222056  248 1252  3257  1252 1911 2445  0  2  1 98  0
 2 36 2094212 133348   2660 224076  332 1144  2784  1144 2054 2636  0  2  1 98  0
 1 42 2095408 133704   2764 224852  100 1304   860  1304 1610 2419  0  2  0 98  0
 0 49 1965576 15504032   1384 225852 1840 2612 43677  2616 6678 8286  0  4  0 96  0
 1 45 1964684 15491904   3212 235088 1072    0 10781     0 2208 2610  0  3  0 97  0
 0 45 1963284 15483832   3440 241340 1644    0  7567     0 2337 2660  0  1  0 98  0
 0 46 1961936 15474580   4340 247996 1428    0  6856     0 2437 2689  0  2  0 98  0
 0 49 1960976 15463492   5380 256744 1008    0  8274     0 2612 2863  0  5  0 95  0
 0 35 1959620 15456672   6100 261400 1356    0  5226     0 2672 2917  0  2  0 98  0
 1 30 1958028 15448340   7008 266940 1772    0  6103     0 2510 2912  0  2  3 94  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1 30 1956804 15442796   7280 271216 1280    0  5136     0 2567 2993  0  1  3 95  0
 0 27 1955340 15437504   7436 274584 1552    0  5040    24 2229 2737  0  1  1 98  0
 1 25 1953836 15430196   8216 280112 1484    0  5547     0 2740 3272  0  3  1 97  0
 0 23 1952324 15423392   8508 283984 1508    0  4930     0 2726 3021  0  2  0 98  0
 0 36 1950124 15418352   8780 287516 1904    0  4972     0 2963 3429  0  2  1 97  0
 1 34 1946488 15397436   9088 289488 6404    0  8281     0 3378 4722  0  1  0 98  0
 0 31 1942100 15395256   9708 293576 4716    0  7145    12 2752 3336  0  3  0 96  0
 0 25 1938172 15397736  10320 295592 2824    0  4757     0 2463 2711  0  1  0 98  0
 0 22 1936080 15398280  10844 299072 1564    0  3660     0 2293 2590  0  2  0 98  0
 1 20 1934384 15396240  11252 302808 1552    0  4817     0 2217 2343  0  2  8 90  0
 0 17 1932832 15389964  12176 307632 1652    0  4800     0 2592 2824  0  3  7 90  0
 0 18 1931328 15382908  13100 312260 1528    0  4040     0 2765 2858  0  3  6 91  0
 1 15 1929996 15378372  13468 314832 1340    0  3449    20 2352 2654  0  1 16 83  0
 0 13 1928536 15375308  13792 316540 1408    0  2286     0 2328 2688  0  2 20 79  0
 0 14 1926908 15366464  15180 322784 1700    0  5625     0 2613 3239  0  4 20 75  0
 1 13 1925364 15361408  15636 325908 1508    0  3758     0 2803 3955  0  3 38 58  0
 1 13 1924012 15356368  16276 328612 1348    0  3864     0 4029 6064  0  2 25 73  0
 0 16 1922032 15349840  17108 332376 1984    0  4296     0 2676 3360  0  3 23 74  0
 1 15 1918432 15341808  17904 335648 3584    0  5446     0 3337 4313  0  4 17 79  0
 1  9 1916416 15335264  18944 340072 2184    0  4540     0 2517 3259  0  3 18 79  0
 0 10 1914548 15329980  19560 342644 2092    0  4423     0 2036 2736  0  1 48 51  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  9 1912684 15326452  20096 344512 1892    0  3010     0 2197 2796  0  1 46 53  0
 1  9 1911060 15322672  20400 345972 1600    0  2796     0 2103 2702  0  1 62 36  0
 0  8 1909464 15320152  20580 347176 1508    0  2024    20 2060 2687  0  1 62 37  0
 1  7 1907664 15317632  20800 347832 1788    0  2228     0 2283 2930  0  1 54 45  0
 1 10 1905784 15313340  21212 349660 1980    0  2923     0 3055 4234  1  1 51 47  0
 1  6 1904224 15309804  21320 351176 1572    0  3025     0 2618 3223  0  1 54 45  0
 1  6 1902760 15303700  21960 354756 1504    0  3974    72 2696 3190  0  2 49 49  0
 3  9 1901196 15297368  22784 358564 1548    0  3773     0 2431 3167  0  3 47 50  0
 2  8 1899428 15291564  23720 361808 1780    0  3321     0 2528 3174  0  3 42 55  0
 0  6 1897604 15286020  24668 364864 1772    0  3362     0 2988 3060  0  2 33 65  0
 1  5 1896140 15284256  24820 365076 1460    0  1844    36 1996 2480  0  1 47 52  0
 1  6 1894776 15281256  25200 366852 1328    0  2009  1992 2740 2590  0  1 54 45  0
 1  5 1893136 15278736  25296 367284 1700    0  1972     0 1837 2419  0  1 65 34  0
 0  5 1891220 15275964  25296 368108 2048    0  2876     0 2166 2696  0  0 62 37  0
 1  8 1889496 15271428  25768 370388 1740    0  3332     0 2210 2951  0  2 37 62  0
 0  7 1887760 15266640  26392 373020 1696    0  2850     0 2291 2926  0  2 47 51  0
 1  8 1885932 15263616  26620 373952 1808    0  2439     0 2569 3005  0  1 40 58  0
 0  8 1884352 15262104  26628 374104 1548    0  1548    16 2426 2860  0  1 38 61  0
 0  7 1882636 15260592  26628 374356 1700    0  2036     0 2350 2814  0  1 29 70  0
 1  6 1880944 15257568  26628 374844 1640    0  2188     0 2365 2991  0  1 39 60  0
 0  7 1879132 15254716  26760 375896 1748    0  2748     0 2661 3361  0  1 43 56  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  6 1877504 15252848  26764 376224 1628    0  2004     0 2548 3248  1  0 49 50  0
 2  4 1875908 15250580  26796 376196 1732    0  1792     0 2475 3222  0  1 56 43  0
 0  5 1874416 15249068  26804 376584 1596    0  1724    24 2506 3249  0  1 48 51  0
 1  5 1872772 15246800  26804 376836 1732    0  1984     0 2508 3300  0  1 62 37  0
 1  5 1870964 15244280  26804 377904 1812    0  2900     0 2438 3323  0  0 69 30  0
 1  5 1869268 15241224  26960 378656 1816    0  2748    44 2490 3374  0  0 62 37  0
 1  5 1867312 15238704  26960 378756 2076    0  2228     0 2602 3580  0  1 69 31  0
 1  5 1865388 15236688  26960 379000 1964    0  2092     0 2453 3462  0  1 69 30  0
 0  5 1863412 15234672  26960 379032 1936    0  1936     0 2568 3537  0  1 63 36  0
 1  6 1861248 15232136  26960 379396 2304    0  2672     0 2591 3482  0  0 50 50  0
 3  7 1858900 15228860  27000 380068 2460    0  3110     0 2849 3774  1  1 57 41  0
 0  6 1857232 15222040  27660 383852 1712    0  3869    40 3192 4005  1  2 42 55  0
 1  7 1855376 15217488  28032 386288 2064    0  3374     0 2732 3764  1  2 56 42  0
 0  6 1853712 15213456  28424 387704 1824    0  3091     0 2646 3811  1  1 61 38  0
 1  6 1851824 15210432  28560 388596 2036    0  2312     0 2744 3860  1  1 62 36  0
 1  6 1850080 15208368  28596 389048 1812    0  2144     0 2636 3544  1  1 59 40  0
 3  6 1848316 15205060  28712 390228 1768    0  2801     0 2432 3471  0  1 68 31  0
 0  6 1846380 15203044  28712 390720 1976    0  2424     0 2462 3287  0  1 58 41  0
 1  8 1844668 15199500  28812 392092 1840    0  3260     0 2150 2928  0  1 51 48  0
 1  7 1842912 15194208  29028 394656 1924    0  3768     0 2426 3254  0  1 53 45  0
 1  6 1841296 15186868  29692 399348 1732    0  4970     0 2477 3635  0  2 61 37  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 3  6 1839748 15180632  30208 402752 1736    0  4197     0 2355 3415  0  1 61 38  0
 0  6 1838024 15175324  30376 403808 1812    0  2561     0 2408 3414  1  1 59 39  0
 1  6 1836112 15168708  30520 405368 1920    0  3337     0 2604 3530  1  1 55 43  0
 1  7 1834360 15164660  30620 407368 1816    0  3549    20 2504 3290  1  1 62 37  0
 0  8 1832584 15159864  31264 410248 2028    0  3880     0 2476 3431  1  2 57 41  0
 1  6 1831280 15150036  33164 418116 1328    0  6251    68 3351 3765  0  4 46 49  0
 0  6 1829836 15146508  33528 420104 1528    0  2896     0 2529 3285  1  1 52 46  0
 0  6 1828388 15141412  34292 422536 1552    0  2992     0 2947 3444  0  2 44 53  0
 0  6 1826996 15137868  34784 424828 1328    0  2505     0 2792 3206  0  2 49 49  0
 0  8 1825528 15134340  34960 425976 1480    0  2369     0 2812 3404  2  1 45 53  0
 1  7 1823956 15132324  34960 426388 1532    0  2052     0 2441 3260  1  1 53 46  0
 0  7 1822348 15129048  35164 428388 1760    0  3202     0 2471 3231  1  1 46 53  0
 0  7 1820876 15123504  35600 431720 1600    0  4084   292 2691 3170  0  2 28 70  0
 0  6 1819592 15121000  35620 432536 1412    0  2100   296 2163 2901  1  1 36 63  0
 0  6 1818044 15114952  36116 436392 1712    0  4700     0 2888 3290  0  2 36 63  0
 0  6 1816684 15109408  36488 440208 1504    0  4620     0 2524 3150  0  1 44 55  0
 1  7 1814416 15104320  36640 442296 2512    0  4438     0 2058 2545  0  1 43 56  0
 1  8 1812792 15102052  36640 442804 1568    0  1928     0 2096 2654  0  1 42 57  0
 1 11 1810804 15099784  36748 443332 2092    0  2634     0 2409 3028  0  1 32 67  0
 1  5 1808940 15097264  36880 444228 1956    0  2712     0 2084 2655  0  0 50 49  0
 1  5 1806952 15093468  36880 444832 2280    0  2960     0 1849 2323  0  0 53 47  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 3  5 1805596 15090444  36880 446816 1484    0  3508     0 1662 2253  0  1 57 43  0
 0  4 1804252 15085152  36880 450432 1376    0  4960     0 1734 2226  0  1 52 47  0
 1  4 1802400 15081844  36880 451928 1888    0  3348     0 2040 2565  0  1 68 31  0
 0  4 1799820 15076536  36888 453916 3444    0  5492    20 5522 8773  0  0 61 39  0
 0  5 1797540 15069736  36888 455920 2692    0  4680     0 6486 11031  0  1 50 49  0
 0  8 1795272 15065944  36928 456776 2452    0  3236     0 6079 11430  0  0 51 48  0
 0  8 1792516 15061492  37092 458048 2976    0  4110     0 4687 8091  0  1 45 54  0
 0  8 1790184 15057376  37300 459812 2532    0  3856     0 6298 10673  1  1 28 71  0
 1 11 1787824 15053572  37372 460468 2672    0  3051     0 5484 9441  0  1 25 74  0
 1  9 1785332 15049784  37428 461160 2880    0  3469    28 6180 10904  1  1 32 66  0
 1  7 1782844 15046484  37540 461772 2768    0  3215     0 3273 4464  1  1 38 60  0
 1  6 1780716 15043280  37540 461752 2392    0  2392     0 4522 6857  0  1 41 58  0
 1  7 1778836 15040656  37540 462268 2104    0  2576     0 3256 4406  0  1 45 54  0
 0  4 1777340 15038292  37540 462932 1512    0  2348     0 3074 4426  0  1 55 44  0
 1  3 1775724 15035000  37676 464204 1640    0  2667     0 2326 2884  0  1 58 41  0
 1  3 1774552 15032732  37680 464932 1224    0  1948     4 1700 2100  0  1 72 27  0
 0  7 1772872 15029440  37816 466380 1968    0  3041     0 2713 3720  1  1 53 45  0
 1  4 1771528 15024652  38384 468456 1512    0  3281    16 2485 3425  1  1 58 40  0
 1  4 1769680 15018280  39000 472028 2180    0  4678     0 2838 4024  1  2 56 41  0
 1  5 1767692 15014484  39052 473404 2344    0  3693     0 2456 3540  0  1 66 33  0
 0  2 1766244 15010704  39192 475616 1648    0  3968     0 2489 3578  1  1 71 27  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  3 1763756 15006924  39192 475876 3220    0  3460     0 2702 3672  1  1 83 16  0
 0  4 1762388 15003120  39332 478012 1568    0  4092     0 2923 4248  1  1 74 24  0
 0  3 1761256 15000876  39908 478324 1264    0  2044    12 2145 3063  0  0 72 27  0
 0  2 1759980 14997096  40176 480744 1380    0  3852     0 2261 3354  1  1 75 23  0
 0  2 1758308 14993576  40176 482144 1916    0  3464    32 2832 4021  1  1 73 24  0
 1  1 1756284 14990024  40176 484184 2160    0  4000     0 2848 3950  1  1 81 18  0
 0  2 1753824 14984984  40176 486112 2752    0  4768     0 6509 11286  1  1 76 22  0
 2  5 1752040 14980880  40176 488144 2072    0  3928     0 6054 9621  2  1 68 29  0
 0  5 1749788 14976960  40176 489280 2464    0  3616     0 5853 9140  1  1 52 46  0
 0  4 1747776 14973164  40176 490644 2300    0  3928     0 6184 9919  0  1 54 45  0
 1  4 1745460 14969116  40176 492420 2560    0  4060     0 2338 3137  0  1 58 41  0
 0  3 1743148 14965588  40176 492688 2680    0  2964     0 2602 3485  2  1 58 39  0
 0  3 1740068 14962240  40176 492800 3496    0  3656     0 4942 8288  1  1 55 44  0
 1  6 1737796 14959484  40180 493016 2560    0  2740     0 4237 6906  1  1 52 45  0
 0  6 1733700 14954948  40184 492968 4776    0  4848   144 3218 4076  0  1 21 78  0
 1  5 1731864 14950152  40184 495480 2056    0  4708     0 3376 5076  2  2 52 45  0
 1  4 1729568 14944268  40184 498860 2516    0  5636     0 4794 8371  2  2 53 43  0
 1  4 1727720 14941244  40196 499588 1988    0  2720     0 3345 5114  3  2 70 26  0
 1  3 1725100 14936944  40196 500484 3216    0  4072     0 2224 2956  1  1 77 22  0
 1  2 1723308 14934896  40196 500516 1928    0  2172     0 2043 2759  1  1 79 20  0
 1  3 1721204 14932360  40204 501180 2348    0  2892    12 2216 3241  1  1 69 30  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  2 1718972 14929336  40204 501380 2368    0  2436     0 2070 2955  1  1 76 22  0
 1  2 1717136 14926816  40204 502220 1860    0  2688     0 1919 2532  1  1 76 23  0
 1  4 1715256 14923728  40208 503388 2080    0  3320     0 5299 9930  0  1 72 27  0
 0  5 1712444 14919680  40208 503204 3124    0  3124     0 3416 5087  2  1 58 40  0
 0  3 1709940 14915396  40208 503644 2788    0  2908     0 2943 4558  2  1 58 40  0
 0 27 1707264 14912624  40284 503756 3076    0  3169     0 2714 3830  2  1 30 68  0
 2 16 1705340 14910648  40284 503824 1964    0  1964     0 4700 7836  0  1  1 98  0
*/
/* Comments
So at first, the physical RAM was enough and it worked fine, but after some time the space was over so Linux had
to use swapped memory (on disk) as we can see by "so" column. After the total space wasn't enough (1.5 GB * 10 = 15 GB when there was 14 gigs free)
the computer frozen and in a few minutes somehow resolved this issue (aparrentely killed the process 
"[1]+  Killed                  ./ex2") and started to retrieve data from swapped memory (see "si" column). 
*/