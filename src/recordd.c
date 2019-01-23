/*
 * recordd.c
 *
 *  Created on: 11.01.2019
 *      Author: piotr
 */

#include "waverecorder.h"
#include "filter.h"

const float32_t base[19][65] =
{
		{15.5194,16.0291,13.2536,12.8950,15.4579,10.0736,11.5148,11.5535,13.4629,14.2590,11.1572,12.3465,12.8945,12.8730,10.5300,10.1777,11.5817,10.8636,12.3430,12.0444,12.2593,11.7767,11.3484,12.4669,12.6126,13.7759,13.3000,12.9076,11.4859,10.6558,12.3885,12.7835,12.8530,12.6919,13.5346,13.0331,12.6029,15.7118,12.2447,15.5737,14.9635,14.9612,13.6965,14.8138,12.5109,14.1611,12.7687,14.1052,15.2769,16.4341,16.1361,16.2136,16.2288,15.2257,15.2137,15.5785,14.6923,14.5921,15.1388,15.1678,17.7487,15.4442,14.8170,14.7344,11.1606},
		{-5.2356,-4.8733,-5.5428,-4.4432,-6.7770,-6.0946,-6.6859,-6.6259,-7.5534,-6.3091,-7.6956,-6.7338,-7.1699,-6.4331,-6.6144,-6.0485,-5.6131,-5.5593,-5.5353,-5.4326,-5.1073,-4.7818,-4.6732,-5.1673,-4.6583,-4.3475,-4.9187,-5.0421,-4.7174,-5.5061,-4.6470,-5.5963,-4.7000,-5.4320,-5.3438,-4.1697,-4.0002,-4.3053,-4.3365,-5.4993,-4.4735,-4.2286,-4.7989,-4.4561,-4.0504,-4.2277,-4.6987,-5.3314,-5.7291,-4.6774,-4.7805,-4.0131,-4.4300,-4.9455,-5.5278,-4.0518,-3.6408,-2.4751,-3.4101,-1.9166,-2.0627,-4.5005,-5.2432,-4.8521,-3.7811},
		{-7.6042,-7.6798,-6.6570,-5.0965,-6.7549,-5.5631,-6.3214,-6.0100,-7.2394,-5.6145,-5.9672,-5.6253,-6.3454,-6.8026,-6.8626,-6.3078,-6.2396,-6.2223,-8.1332,-7.6699,-7.0726,-6.2078,-6.2759,-7.7330,-9.0371,-9.9661,-9.0239,-7.2693,-6.3991,-7.2459,-6.4230,-7.7765,-7.1146,-6.8974,-8.3080,-7.2356,-6.9168,-7.3112,-6.4824,-7.9632,-7.7978,-7.6873,-7.9606,-7.1311,-6.0256,-5.9377,-6.3769,-7.7802,-8.9422,-9.2029,-9.8782,-9.9857,-9.6165,-8.6781,-9.7131,-8.4100,-7.2943,-6.4494,-8.1860,-6.5851,-6.5867,-7.4364,-7.8437,-7.5123,-0.4096},
		{2.7136,3.0428,1.5306,1.4966,2.8239,0.7635,0.5651,1.1368,0.9408,2.2741,1.4317,1.4291,1.9399,2.5182,0.9555,0.5202,0.8159,1.1747,2.0596,1.6184,1.7186,1.2113,1.7078,1.2693,2.1104,2.4773,1.9247,1.3103,0.7669,-0.0737,1.4606,2.8300,2.0219,1.2111,0.8067,0.8555,0.0214,1.6640,-0.0323,0.9309,1.5174,1.3138,1.7342,2.2942,0.4725,1.2228,1.1107,1.8916,1.6646,2.6812,1.7804,1.4345,1.3509,2.0053,0.9997,0.9281,-0.3406,-1.2069,-1.4143,-1.4758,0.4013,0.2391,0.4544,0.7066,0.4662},
		{1.4964,2.2560,1.1306,0.9412,0.0694,0.7894,0.1398,0.0928,-0.1171,1.0431,0.4904,0.0734,0.3545,0.6387,0.9242,0.6185,1.0308,1.3232,1.1787,1.4171,1.6944,1.5493,1.0177,1.5540,1.4912,2.9919,2.2317,1.3518,1.4484,0.2523,0.7951,1.6830,2.8721,1.8096,1.7332,2.2136,2.0806,2.3225,1.6615,1.3979,2.3732,1.8776,2.0857,2.3407,1.7562,2.4779,1.8450,1.8865,1.5045,1.3122,0.7524,0.8803,1.2835,1.9576,1.0599,0.9588,0.7412,0.3488,0.0845,0.8038,1.2059,0.8619,0.2214,1.2193,0.0179},
		{-2.0251,-2.7764,-1.9676,-1.8739,-1.1268,-0.1863,-1.0048,-1.8165,-3.7913,-3.7398,-2.7707,-2.8677,-4.7063,-5.5381,-4.0945,-3.9608,-3.3667,-3.4846,-5.9899,-5.0712,-3.9804,-3.7634,-4.3458,-4.3417,-4.4464,-4.8812,-4.0291,-3.1123,-2.4876,-3.2555,-2.4979,-2.7792,-1.3759,-2.1096,-2.8234,-2.0720,-1.2751,-1.8774,-1.6142,-2.5624,-1.5207,-1.5799,-1.7110,-2.0778,-0.9591,-0.8953,-1.5998,-2.4506,-3.9315,-3.8036,-4.7899,-4.2323,-3.2183,-3.3837,-3.5577,-3.0176,-2.1464,-1.2271,-2.6460,-1.0071,-1.7733,-2.2061,-3.0292,-2.3775,-0.4906},
		{-0.8183,-0.9704,-0.9160,-1.1295,0.7498,0.7042,0.8260,0.4982,-0.0205,0.4819,-0.1547,0.5736,1.0686,0.5988,-1.5463,-2.0048,-0.7318,-1.0998,-0.5541,-0.2207,-0.3005,-1.3474,-1.3834,-0.9408,-0.8660,1.2461,-0.2633,-0.6317,-0.5629,-0.4712,-0.0349,0.3568,-0.7733,-1.4639,-1.1461,-1.6089,-1.7634,-0.5274,-2.5222,0.1013,-0.4839,-0.1315,-0.5338,-0.4584,-1.4866,-1.1967,-1.7323,-0.6335,-0.2134,1.2959,1.3094,0.7939,0.3581,-0.3701,0.7288,0.4345,-0.8820,-0.4248,-0.1180,0.0274,0.6212,0.1186,0.1118,-0.4506,0.3971},
		{0.1239,-0.7007,-0.2713,0.1850,0.6973,1.4287,1.1897,1.1498,1.8139,1.5767,1.4190,1.2996,1.5046,1.0333,1.4112,1.2852,1.9861,1.9665,1.5182,2.0132,1.7212,2.0304,2.3277,1.6357,1.3258,1.8775,0.3012,1.4342,1.0899,1.3115,1.4453,-1.4977,-1.3858,-1.2353,-1.6778,-1.5632,-0.9163,-1.2220,-1.1512,-1.2587,-1.3900,-0.4577,-0.9632,-1.7741,-0.8335,-0.5422,-0.9596,-1.3433,-1.9198,-1.4709,-1.4182,-1.0747,-1.3686,-2.3583,-2.0065,-1.1353,-0.4912,-0.9358,-0.9930,-1.1930,-0.5383,-0.4800,-0.5042,0.1826,-0.1330},
		{0.3115,0.4238,0.5377,2.0362,1.3449,2.4040,1.9040,1.4006,-0.4022,0.8742,2.0511,1.0405,1.7870,2.1202,2.7240,2.6232,2.7929,3.1822,2.7726,3.5866,3.7456,3.8445,4.6974,3.6056,3.8140,1.9941,1.4935,1.7453,2.5535,1.5973,0.8282,1.0129,1.6319,0.7209,1.0394,1.2778,1.6594,1.5578,0.8819,1.4556,0.9952,0.9143,1.2933,1.1297,0.4384,1.1447,0.8198,0.9673,-0.2357,-0.3763,-1.1508,-0.0478,0.1140,0.7775,0.1397,-0.0925,0.3709,-0.3782,0.0512,-0.8662,0.3906,-0.0138,0.0726,0.1531,-0.2769},
		{0.2075,-0.0182,0.7125,2.4496,3.0252,4.0101,4.1157,4.0964,5.2482,4.3679,4.2165,3.7228,4.1906,3.2862,2.6351,2.3701,2.3681,2.7198,2.6145,3.1852,2.7999,3.0010,3.5092,2.0650,1.6052,2.8439,2.2532,1.3304,2.3327,1.4371,0.4789,1.1502,1.2955,1.4181,1.1657,1.5729,1.8420,1.8621,1.0376,0.8034,0.1063,0.2263,1.2614,1.3962,0.8500,1.2785,1.4144,1.6324,1.4038,0.3612,-0.2070,0.7510,1.7379,1.4022,0.4708,-0.4678,-1.0745,-0.7543,-0.8104,-0.8306,-0.8057,-1.1272,-1.0019,-0.6254,0.5180},
		{2.1929,3.3629,3.2140,2.2254,3.2444,1.9479,2.0267,1.9404,2.4967,2.7342,3.1981,2.8238,3.1546,2.6623,2.6069,2.3945,2.8407,2.8532,2.9496,2.9108,3.0585,2.6262,3.2774,3.0046,3.2495,3.5711,3.7041,3.6494,3.7308,3.7611,4.3001,4.7851,3.6357,3.1626,2.2910,2.4365,2.8329,2.3026,1.1701,2.0367,1.4857,1.7659,3.1515,3.0932,1.5628,1.7004,2.2501,2.8946,1.9422,1.0973,0.8388,0.8685,0.5430,1.8630,1.1899,-0.1391,-0.5225,-0.3738,-0.5327,-0.2393,-0.6870,-0.1247,0.3158,0.7357,-0.6254},
		{0.7069,1.7316,1.2598,-1.1565,-3.2706,-3.4013,-3.8704,-4.1934,-5.2518,-3.9752,-2.1593,-2.9023,-3.2796,-2.7987,-0.0957,-0.2742,0.7554,0.5011,-0.5564,-0.8451,-0.5527,-0.5346,-1.0212,0.2416,0.5233,1.4162,2.7615,2.5470,2.0619,3.1597,3.3236,2.6167,2.1957,2.3193,2.4943,2.6725,2.8104,2.3812,1.8065,1.5321,1.1628,1.4434,1.9983,1.9137,1.4468,1.8235,1.8091,2.0395,1.5400,0.1238,-0.4022,0.5942,1.5441,1.5782,0.8206,0.9765,1.3875,1.4113,1.6582,1.2261,1.2595,1.5720,1.3851,0.9949,0.5487},
		{2.1703,0.4257,-0.5076,-2.2776,-2.8924,-3.5531,-3.5160,-4.2631,-4.4786,-3.2347,-3.1763,-3.0377,-2.5165,-2.2775,-2.3269,-2.7202,-1.9790,-2.2466,-1.9108,-1.8777,-2.2576,-2.9134,-2.5400,-2.4348,-2.4626,-0.8346,-1.1666,-0.7069,-1.7325,-1.4466,-0.6894,0.9420,0.5949,0.3793,1.6293,1.0922,1.1114,1.9419,1.6657,3.1217,2.8101,2.7414,1.1934,1.0010,1.3219,1.7630,1.5996,1.5662,1.7771,3.0007,3.1453,3.5884,3.4153,2.4285,3.3764,3.5456,2.8268,3.1819,3.4326,2.6316,3.1530,2.6460,2.7369,1.4391,-0.3836},
		{-0.0983,-3.2549,-3.4886,-1.2124,-0.1898,0.4088,1.9402,0.6266,-0.1463,-1.4032,-0.4709,0.0376,-1.4706,-2.9057,-2.8109,-2.8465,-2.7763,-2.7804,-2.8341,-3.0910,-3.1615,-2.6509,-2.0555,-2.9596,-3.0112,-4.2296,-3.9537,-3.7555,-3.0177,-3.9329,-5.3158,-3.6092,-2.7587,-2.2922,-1.4989,-1.8612,-2.0719,-1.2451,-1.1407,-0.1313,-0.4465,0.2712,-1.0980,-1.2060,-1.0250,-0.9365,-1.1690,-1.1199,-1.1061,-0.2709,0.3659,0.3556,-0.6788,-1.6645,-0.4599,1.3935,1.3574,1.9083,1.1522,1.7770,0.8434,1.6740,1.9218,0.9463,0.2402},
		{-0.8644,-2.4738,-0.8836,1.0865,2.3888,2.0050,3.1798,3.0014,4.3029,3.4656,2.3118,2.9489,3.0973,1.6503,1.1364,0.9862,0.7892,0.9110,1.8764,2.2579,1.5062,1.7700,2.8892,1.3454,1.0958,-1.2438,-1.2787,-0.8477,-0.8269,-1.4359,-1.8108,-2.6358,-4.0080,-3.3180,-1.9255,-2.9488,-3.1133,-2.0508,-2.8449,-0.9492,-1.5078,-0.9713,-2.7224,-3.2514,-2.5678,-2.5955,-2.6415,-2.3776,-1.6371,-1.4030,-1.3247,-1.0883,-1.0372,-1.7143,-0.8767,-0.1134,0.2705,0.7232,0.4045,1.0970,-0.0207,0.2288,0.1214,0.2598,-0.1125},
		{-1.7004,-0.7624,0.0784,0.5200,-0.8607,-0.3214,0.4192,-0.4028,-1.7265,-1.2835,-0.2245,-0.3386,-0.4611,0.5351,1.1666,1.0217,1.1220,1.0977,1.3738,1.4477,0.9483,1.2568,2.0640,1.0989,1.1142,1.1192,0.2458,-0.5526,0.1216,0.1179,-0.2382,-0.6734,-1.7799,-1.7187,-1.8547,-1.9739,-1.4179,-2.3694,-1.9704,-1.7325,-1.9278,-1.4767,-1.6627,-1.9100,-2.0539,-2.1364,-2.2185,-2.6098,-2.7397,-1.9579,-1.4321,-1.1383,-1.4959,-2.7607,-1.4391,-1.2796,-1.3322,-1.2570,-0.8940,-1.4514,-1.5477,-1.2604,-1.4413,-0.9913,0.1002},
		{1.0317,0.9236,0.2909,-0.7064,-0.5041,-1.0780,-0.3429,-0.7189,-0.3337,-0.4624,-1.0565,-0.2905,-0.7891,-1.7501,-1.7281,-1.7092,-1.4115,-1.6512,-1.6112,-2.1243,-2.1399,-2.0158,-1.7256,-1.7707,-1.7554,-1.7110,-0.1726,0.1304,-0.7053,-0.0571,0.7248,1.4273,1.4565,1.2797,1.6545,1.6231,1.2473,1.9967,1.0877,1.3293,1.0027,0.7084,1.6269,1.8958,0.8404,1.0729,1.4401,2.0381,2.0742,0.3174,-0.3829,0.2220,0.9214,2.0394,0.8161,-0.5529,-0.8558,-0.8335,-0.8035,-1.5927,-0.9960,-1.0719,-0.5651,-0.1193,-0.0547},
		{0.6859,0.7461,-0.0709,-0.4716,-0.2707,-0.3654,0.3822,-0.4760,-1.6304,-1.3115,-0.6870,-0.3330,-1.1343,-1.5011,-1.1975,-1.2592,-0.9988,-1.1817,-0.9019,-1.4718,-1.4768,-1.7758,-1.8586,-1.4094,-1.4415,-1.7964,-0.7294,-0.4225,-0.5284,-0.6973,-0.8060,0.9289,1.0043,0.9793,0.4878,0.7572,0.8639,0.5226,0.7099,0.6058,0.2144,0.4250,1.0117,1.1628,0.5554,0.6002,0.9853,0.8403,0.5980,0.1503,-0.0653,0.4271,0.3294,0.7017,0.1635,0.1696,-0.2135,-0.2882,-0.0455,-0.4031,-0.2169,-0.1231,0.2026,0.3102,0.0920},
		{-0.6395,-0.1069,0.8538,0.4351,0.7156,0.1327,0.4041,0.0104,0.0920,-0.2321,-0.0516,0.1247,-0.4957,-0.4760,0.3181,0.0959,0.2844,0.2431,-0.0866,0.0898,0.1481,0.0885,-0.3194,0.4150,0.6461,1.6671,1.7100,1.0150,0.6127,0.4741,0.2654,-0.0969,-0.8782,-0.1943,0.3591,0.1395,-0.0254,0.0077,-0.0959,0.0303,-0.2331,-0.0063,-0.7166,-0.6893,-0.4104,-0.2952,-0.0094,-0.1917,-0.1547,-0.0343,0.4163,0.2953,0.0579,0.0639,-0.0074,0.4980,1.1968,1.1170,1.2919,1.5793,1.0301,1.0277,0.9505,0.4067,-0.0474}

};


float32_t testInput[] =
{
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
-0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
-0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
};

//zmienne do lcd - filter/nofilter
#define TOUCH_RECORD_XMIN       180
#define TOUCH_RECORD_XMAX       210
#define TOUCH_RECORD_YMIN       210
#define TOUCH_RECORD_YMAX       239

#define TOUCH_STOP_XMIN         100
#define TOUCH_STOP_XMAX         125
#define TOUCH_STOP_YMIN         210
#define TOUCH_STOP_YMAX         239

#define TOUCH_PAUSE_XMIN        20
#define TOUCH_PAUSE_XMAX        60
#define TOUCH_PAUSE_YMIN        210
#define TOUCH_PAUSE_YMAX        239

#define TOUCH_CHOOSE1_XMIN 	    20
#define TOUCH_CHOOSE1_XMAX 		123
#define TOUCH_CHOOSE1_YMIN 		100
#define TOUCH_CHOOSE1_YMAX 		239

#define TOUCH_CHOOSE2_XMAX 		230
#define TOUCH_CHOOSE2_XMIN 		127
#define TOUCH_CHOOSE2_YMIN 		100
#define TOUCH_CHOOSE2_YMAX 		239
//Private variables
uint8_t Header_Buffer[44];
static AUDIO_IN_BufferTypeDef  BufferCtl;
static __IO uint32_t uwVolume = 100;
extern WAVE_FormatTypeDef WaveFormat;
extern FIL WavFile;
static uint32_t  display_update = 1;
static uint32_t filtration = 0;
static uint32_t t = 0;
static float32_t mfcc_section[69][19];//mfcc for section

//FIR Coefficients buffer generated using fir1() MATLAB function.
//fir1(28, 6/24)
const float32_t firCoeffs32[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};//*/
/*const float32_t firCoeffs32[NUM_TAPS] = {
		1, -0.9735
};//*/
// Declare State buffer of size (numTaps + blockSize - 1)
//static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
//arm_fir_instance_f32 S;
//Private functions
static uint32_t WavProcess_EncInit(uint32_t Freq, uint8_t* pHeader);
static uint32_t WavProcess_HeaderInit(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct);
static uint32_t WavProcess_HeaderUpdate(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct);
static void AUDIO_REC_DisplayButtons(void);
static void DisplayChoose(void);
static void LCD_ClearZone(void);

AUDIO_ErrorTypeDef AUDIO_REC_Start(void)
{
  uint32_t byteswritten = 0;
  uwVolume = 100;

  //init filter
  //arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], BLOCK_SIZE);
  /* Create a new file system */
  if(f_open(&WavFile, REC_WAVE_NAME, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
  {
    /* Initialize header file */
    WavProcess_EncInit(DEFAULT_AUDIO_IN_FREQ, Header_Buffer);
    /* Write header file */
    if(f_write(&WavFile, Header_Buffer, 44, (void*)&byteswritten) == FR_OK)
    {
      AudioState = AUDIO_STATE_PRERECORD_CHOOSE;
      DisplayChoose();
      {
        if(byteswritten != 0)
        {
          BSP_AUDIO_IN_InitEx(INPUT_DEVICE_DIGITAL_MICROPHONE_2, BSP_AUDIO_FREQUENCY_8K, DEFAULT_AUDIO_IN_BIT_RESOLUTION, DEFAULT_AUDIO_IN_CHANNEL_NBR);
          BSP_AUDIO_IN_Record((uint16_t*)&BufferCtl.pcm_buff[0], AUDIO_IN_BUFFER_SIZE);//zmiana na float
          BufferCtl.fptr = byteswritten;
          BufferCtl.pcm_ptr = 0;
          BufferCtl.offset = 0;
          BufferCtl.wr_state = BUFFER_EMPTY;
          return AUDIO_ERROR_NONE;
        }
      }
    }
  }
  return AUDIO_ERROR_IO;
}

AUDIO_ErrorTypeDef AUDIO_REC_Process(void)
{
  uint32_t byteswritten = 0;
  float32_t cepstrum[19]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float32_t cepstrumtest[20]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float32_t  inputtest[256];

  AUDIO_ErrorTypeDef audio_error = AUDIO_ERROR_NONE;
  uint32_t elapsed_time;
  static uint32_t prev_elapsed_time = 0xFFFFFFFF;
  uint8_t str[FILEMGR_FILE_NAME_SIZE + 20];
  uint8_t x,y;
  static TS_StateTypeDef  TS_State={0};

  switch(AudioState)
  {
  case AUDIO_STATE_PRERECORD_CHOOSE:
 	 if(TS_State.touchDetected == 1)   /* If previous touch has not been released, we don't proceed any touch command */
     {
 		BSP_TS_GetState(&TS_State);
     }
 	 else
 	 {
 		 BSP_TS_GetState(&TS_State);
 		 x = TouchScreen_Get_Calibrated_X(TS_State.touchX[0]);
 		 y = TouchScreen_Get_Calibrated_Y(TS_State.touchY[0]);
 		 if(TS_State.touchDetected == 1)
 		 {
 			 if ((x > TOUCH_CHOOSE1_XMIN) && (x < TOUCH_CHOOSE1_XMAX) &&
 					 (y > TOUCH_CHOOSE1_YMIN) && (y < TOUCH_CHOOSE1_YMAX))
 	         {
 				 filtration = 1;
 				 AudioState = AUDIO_STATE_BEFORE_PRERECORD;
 	         }
 			 else if ((x > TOUCH_CHOOSE2_XMIN) && (x < TOUCH_CHOOSE2_XMAX) &&
 					 (y > TOUCH_CHOOSE2_YMIN) && (y < TOUCH_CHOOSE2_YMAX))
 	         {
 				 filtration = 0;
 				 AudioState = AUDIO_STATE_BEFORE_PRERECORD;
 	         }
 		 }
 		 else
 		 {
 			 AudioState = AUDIO_STATE_PRERECORD_CHOOSE;
 		 }
 	 }
   	  break;

  case AUDIO_STATE_BEFORE_PRERECORD:
		LCD_ClearZone();
	    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	    sprintf((char *)str, "Recording file: %s",
	            (char *)REC_WAVE_NAME);
	    BSP_LCD_DisplayStringAtLine(4, str);


	    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
	    sprintf((char *)str,  "Sample rate : %d Hz", (int)DEFAULT_AUDIO_IN_FREQ);
	    BSP_LCD_DisplayStringAtLine(6, str);

	    sprintf((char *)str,  "Channels number : %d", (int)DEFAULT_AUDIO_IN_CHANNEL_NBR);
	    BSP_LCD_DisplayStringAtLine(7, str);

	    sprintf((char *)str,  "Volume : %d ", (int)uwVolume);
	    BSP_LCD_DisplayStringAtLine(8, str);

	    sprintf((char *)str, "File Size :");
	    BSP_LCD_DisplayStringAtLine(9, str);

	    BSP_LCD_DisplayStringAt(15, LINE(6), (uint8_t *)"  [     ]", RIGHT_MODE);

	    AUDIO_REC_DisplayButtons();
	  AudioState = AUDIO_STATE_PRERECORD;
	break;

  case AUDIO_STATE_PRERECORD:
    if(TS_State.touchDetected == 1)   /* If previous touch has not been released, we don't proceed any touch command */
    {
      BSP_TS_GetState(&TS_State);
    }
    else
    {
      BSP_TS_GetState(&TS_State);
      x = TouchScreen_Get_Calibrated_X(TS_State.touchX[0]);
      y = TouchScreen_Get_Calibrated_Y(TS_State.touchY[0]);
      if(TS_State.touchDetected == 1)
      {
        if ((x > TOUCH_STOP_XMIN) && (x < TOUCH_STOP_XMAX) &&
            (y > TOUCH_STOP_YMIN) && (y < TOUCH_STOP_YMAX))
        {
          AudioState = AUDIO_STATE_STOP;
        }
        else if ((x > TOUCH_RECORD_XMIN) && (x < TOUCH_RECORD_XMAX) &&
                 (y > TOUCH_RECORD_YMIN) && (y < TOUCH_RECORD_YMAX))
        {
          display_update = 1;
          AudioState = AUDIO_STATE_RECORD;
        }
      }
      else
      {
        AudioState = AUDIO_STATE_PRERECORD;
      }
    }
    break;
    break;

  case AUDIO_STATE_RECORD:
    if (display_update)
    {
      BSP_LCD_SetTextColor(LCD_COLOR_RED);    /* Display red record circle */
      BSP_LCD_FillCircle((TOUCH_RECORD_XMAX+TOUCH_RECORD_XMIN)/2,
                         (TOUCH_RECORD_YMAX+TOUCH_RECORD_YMIN)/2,
                         (TOUCH_RECORD_XMAX-TOUCH_RECORD_XMIN)/2);
      BSP_LCD_SetFont(&LCD_LOG_TEXT_FONT);
      BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
      BSP_LCD_DisplayStringAt(15, LINE(6), (uint8_t *)"  [RECORD]", RIGHT_MODE);
      display_update = 0;
    }

    if(TS_State.touchDetected == 1)   /* If previous touch has not been released, we don't proceed any touch command */
    {
      BSP_TS_GetState(&TS_State);
    }
    else
    {
      BSP_TS_GetState(&TS_State);
      x = TouchScreen_Get_Calibrated_X(TS_State.touchX[0]);
      y = TouchScreen_Get_Calibrated_Y(TS_State.touchY[0]);
      if(TS_State.touchDetected == 1)
      {
        if ((x > TOUCH_STOP_XMIN) && (x < TOUCH_STOP_XMAX) &&
            (y > TOUCH_STOP_YMIN) && (y < TOUCH_STOP_YMAX))
        {
          AudioState = AUDIO_STATE_STOP;
        }
        else if ((x > TOUCH_PAUSE_XMIN) && (x < TOUCH_PAUSE_XMAX) &&
                 (y > TOUCH_PAUSE_YMIN) && (y < TOUCH_PAUSE_YMAX))
        {
          AudioState = AUDIO_STATE_PAUSE;
        }
      }
    }

    /* MAX Recording time reached, so stop audio interface and close file */
    if(BufferCtl.fptr >= REC_SAMPLE_LENGTH)
    {
      display_update = 1;
      AudioState = AUDIO_STATE_STOP;
      break;
    }

    /* Check if there are Data to write to USB Key */
    if(BufferCtl.wr_state == BUFFER_FULL)
    {
      /* write buffer in file */ //+ filtracja
    if(filtration == 1)
	{
    	//arm_fir_f32(&S, (uint8_t*)(BufferCtl.pcm_buff + BufferCtl.offset), outputF32, BLOCK_SIZE);
    	//outputF32=mfcc();
    	if(t<65){
    		mfcc((float32_t*)(BufferCtl.pcm_buff + BufferCtl.offset),cepstrumtest);
    		for(uint8_t n = 1; n<20;++n){
    			mfcc_section[n-1][t] = cepstrumtest[n];
    		}
    		++t;
    	}
    	else
    	{

    		t = 0;
    	}

    	//if(f_write(&WavFile,(uint8_t*)(BufferCtl.pcm_buff + BufferCtl.offset), //FIXME
      //         AUDIO_IN_BUFFER_SIZE,
      //         (void*)&byteswritten) != FR_OK)
   	//	{
     //  		BSP_LCD_SetTextColor(LCD_COLOR_RED);
     //      	BSP_LCD_DisplayStringAtLine(14, (uint8_t *)"RECORD FAIL");
    //       	return AUDIO_ERROR_IO;
   	//	}
	}
	else
	{
    	if(f_write(&WavFile, (uint8_t*)(BufferCtl.pcm_buff + BufferCtl.offset),
                 AUDIO_IN_BUFFER_SIZE,
                 (void*)&byteswritten) != FR_OK)
    	{
    		BSP_LCD_SetTextColor(LCD_COLOR_RED);
        	BSP_LCD_DisplayStringAtLine(14, (uint8_t *)"RECORD FAIL");
        	return AUDIO_ERROR_IO;
    	}
      }
      BufferCtl.fptr += byteswritten;
      BufferCtl.wr_state =  BUFFER_EMPTY;
    }

    /* Display elapsed time */
    elapsed_time = BufferCtl.fptr / (DEFAULT_AUDIO_IN_FREQ * DEFAULT_AUDIO_IN_CHANNEL_NBR * 2);
    if(prev_elapsed_time != elapsed_time)
    {
      prev_elapsed_time = elapsed_time;
      sprintf((char *)str, "[%02d:%02d]", (int)(elapsed_time /60), (int)(elapsed_time%60));
      BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
      BSP_LCD_DisplayStringAt(31, LINE(9), str, RIGHT_MODE);
      sprintf((char *)str, "%4d KB", (int)((int32_t)BufferCtl.fptr/1024));
      BSP_LCD_DisplayStringAt(83, LINE(9), str, LEFT_MODE);
    }
    break;

  case AUDIO_STATE_STOP:
    /* Stop recorder */
    BSP_AUDIO_IN_Stop(CODEC_PDWN_SW);
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);   /* Display blue cyan record circle */
    BSP_LCD_FillCircle((TOUCH_RECORD_XMAX+TOUCH_RECORD_XMIN)/2,
                       (TOUCH_RECORD_YMAX+TOUCH_RECORD_YMIN)/2,
                       (TOUCH_RECORD_XMAX-TOUCH_RECORD_XMIN)/2);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillRect(TOUCH_STOP_XMIN, TOUCH_STOP_YMIN , /* Stop rectangle */
                     TOUCH_STOP_XMAX - TOUCH_STOP_XMIN,
                     TOUCH_STOP_YMAX - TOUCH_STOP_YMIN);
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
    display_update = 1;
    HAL_Delay(150);
    if(f_lseek(&WavFile, 0) == FR_OK)
    {
      /* Update the wav file header save it into wav file */
      WavProcess_HeaderUpdate(Header_Buffer, &WaveFormat);
      if(f_write(&WavFile, Header_Buffer, sizeof(WAVE_FormatTypeDef), (void*)&byteswritten) == FR_OK)
      {
        audio_error = AUDIO_ERROR_EOF;
      }
      else
      {
        audio_error = AUDIO_ERROR_IO;
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAtLine(14, (uint8_t *)"RECORD FAIL");
      }
    }
    else
    {
      BSP_LCD_SetTextColor(LCD_COLOR_RED);
      BSP_LCD_DisplayStringAtLine(14, (uint8_t *)"RECORD FAIL");
      audio_error = AUDIO_ERROR_IO;
    }
    AudioState = AUDIO_STATE_IDLE;
    /* Close file */
    f_close(&WavFile);
    break;

  case AUDIO_STATE_PAUSE:
    BSP_LCD_SetTextColor(LCD_COLOR_RED);    /* Displays red pause rectangles */
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);   /* Display blue cyan record circle */
    BSP_LCD_FillCircle((TOUCH_RECORD_XMAX+TOUCH_RECORD_XMIN)/2,
                       (TOUCH_RECORD_YMAX+TOUCH_RECORD_YMIN)/2,
                       (TOUCH_RECORD_XMAX-TOUCH_RECORD_XMIN)/2);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_DisplayStringAt(15, LINE(6), (uint8_t *)"  [PAUSE] ", RIGHT_MODE);
    BSP_AUDIO_IN_Pause();
    AudioState = AUDIO_STATE_WAIT;
    break;

  case AUDIO_STATE_RESUME:
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);    /* Displays blue cyan pause rectangles */
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);    /* Display red record circle */
    BSP_LCD_FillCircle((TOUCH_RECORD_XMAX+TOUCH_RECORD_XMIN)/2,
                       (TOUCH_RECORD_YMAX+TOUCH_RECORD_YMIN)/2,
                       (TOUCH_RECORD_XMAX-TOUCH_RECORD_XMIN)/2);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_DisplayStringAt(15, LINE(6), (uint8_t *)"  [RECORD]", RIGHT_MODE);
    BSP_AUDIO_IN_Resume();
    AudioState = AUDIO_STATE_RECORD;
    break;

  case AUDIO_STATE_NEXT:
  case AUDIO_STATE_PREVIOUS:
    AudioState = AUDIO_STATE_RECORD;
    break;

  case AUDIO_STATE_WAIT:
    if(TS_State.touchDetected == 1)   /* If previous touch has not been released, we don't proceed any touch command */
    {
      BSP_TS_GetState(&TS_State);
    }
    else
    {
      BSP_TS_GetState(&TS_State);
      x = TouchScreen_Get_Calibrated_X(TS_State.touchX[0]);
      y = TouchScreen_Get_Calibrated_Y(TS_State.touchY[0]);
      if(TS_State.touchDetected == 1)
      {
        if ((x > TOUCH_RECORD_XMIN) && (x < TOUCH_RECORD_XMAX) &&
            (y > TOUCH_RECORD_YMIN) && (y < TOUCH_RECORD_YMAX))
        {
          AudioState = AUDIO_STATE_RESUME;
        }
        else if ((x > TOUCH_PAUSE_XMIN) && (x < TOUCH_PAUSE_XMAX) &&
                 (y > TOUCH_PAUSE_YMIN) && (y < TOUCH_PAUSE_YMAX))
        {
          AudioState = AUDIO_STATE_RESUME;
        }
      }
    }
    break;

  case AUDIO_STATE_IDLE:
  case AUDIO_STATE_INIT:
  default:
    /* Do Nothing */
    break;
  }
  return audio_error;
}

void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  BufferCtl.pcm_ptr+= AUDIO_IN_BUFFER_SIZE/2;
  if(BufferCtl.pcm_ptr == AUDIO_IN_BUFFER_SIZE/2)
  {
    BufferCtl.wr_state   =  BUFFER_FULL;
    BufferCtl.offset  = 0;
  }

  if(BufferCtl.pcm_ptr >= AUDIO_IN_BUFFER_SIZE)
  {
    BufferCtl.wr_state   =  BUFFER_FULL;
    BufferCtl.offset  = AUDIO_IN_BUFFER_SIZE/2;
    BufferCtl.pcm_ptr = 0;
  }
}

void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  BufferCtl.pcm_ptr+= AUDIO_IN_BUFFER_SIZE/2;
  if(BufferCtl.pcm_ptr == AUDIO_IN_BUFFER_SIZE/2)
  {
    BufferCtl.wr_state   =  BUFFER_FULL;
    BufferCtl.offset  = 0;
  }

  if(BufferCtl.pcm_ptr >= AUDIO_IN_BUFFER_SIZE)
  {
    BufferCtl.wr_state   =  BUFFER_FULL;
    BufferCtl.offset  = AUDIO_IN_BUFFER_SIZE/2;
    BufferCtl.pcm_ptr = 0;
  }
}

static uint32_t WavProcess_EncInit(uint32_t Freq, uint8_t *pHeader)
{
  /* Initialize the encoder structure */
  WaveFormat.SampleRate = Freq;        /* Audio sampling frequency */
  WaveFormat.NbrChannels = 1;          /* Number of channels: 1:Mono or 2:Stereo */
  WaveFormat.BitPerSample = 16;        /* Number of bits per sample (16, 24 or 32) */
  WaveFormat.FileSize = 0x001D4C00;    /* Total length of useful audio data (payload) */
  WaveFormat.SubChunk1Size = 44;       /* The file header chunk size */
  WaveFormat.ByteRate = (WaveFormat.SampleRate * \
                        (WaveFormat.BitPerSample/8) * \
                         WaveFormat.NbrChannels);     /* Number of bytes per second  (sample rate * block align)  */
  WaveFormat.BlockAlign = WaveFormat.NbrChannels * \
                         (WaveFormat.BitPerSample/8); /* channels * bits/sample / 8 */

  /* Parse the wav file header and extract required information */
  if(WavProcess_HeaderInit(pHeader, &WaveFormat))
  {
    return 1;
  }
  return 0;
}

static uint32_t WavProcess_HeaderInit(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct)
{
  /* Write chunkID, must be 'RIFF'  ------------------------------------------*/
  pHeader[0] = 'R';
  pHeader[1] = 'I';
  pHeader[2] = 'F';
  pHeader[3] = 'F';

  /* Write the file length ---------------------------------------------------*/
  /* The sampling time: this value will be written back at the end of the
     recording operation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
  pHeader[4] = 0x00;
  pHeader[5] = 0x4C;
  pHeader[6] = 0x1D;
  pHeader[7] = 0x00;
  /* Write the file format, must be 'WAVE' -----------------------------------*/
  pHeader[8]  = 'W';
  pHeader[9]  = 'A';
  pHeader[10] = 'V';
  pHeader[11] = 'E';

  /* Write the format chunk, must be'fmt ' -----------------------------------*/
  pHeader[12]  = 'f';
  pHeader[13]  = 'm';
  pHeader[14]  = 't';
  pHeader[15]  = ' ';

  /* Write the length of the 'fmt' data, must be 0x10 ------------------------*/
  pHeader[16]  = 0x10;
  pHeader[17]  = 0x00;
  pHeader[18]  = 0x00;
  pHeader[19]  = 0x00;

  /* Write the audio format, must be 0x01 (PCM) ------------------------------*/
  pHeader[20]  = 0x01;
  pHeader[21]  = 0x00;

  /* Write the number of channels, ie. 0x01 (Mono) ---------------------------*/
  pHeader[22]  = pWaveFormatStruct->NbrChannels;
  pHeader[23]  = 0x00;

  /* Write the Sample Rate in Hz ---------------------------------------------*/
  /* Write Little Endian ie. 8000 = 0x00001F40 => byte[24]=0x40, byte[27]=0x00*/
  pHeader[24]  = (uint8_t)((pWaveFormatStruct->SampleRate & 0xFF));
  pHeader[25]  = (uint8_t)((pWaveFormatStruct->SampleRate >> 8) & 0xFF);
  pHeader[26]  = (uint8_t)((pWaveFormatStruct->SampleRate >> 16) & 0xFF);
  pHeader[27]  = (uint8_t)((pWaveFormatStruct->SampleRate >> 24) & 0xFF);

  /* Write the Byte Rate -----------------------------------------------------*/
  pHeader[28]  = (uint8_t)((pWaveFormatStruct->ByteRate & 0xFF));
  pHeader[29]  = (uint8_t)((pWaveFormatStruct->ByteRate >> 8) & 0xFF);
  pHeader[30]  = (uint8_t)((pWaveFormatStruct->ByteRate >> 16) & 0xFF);
  pHeader[31]  = (uint8_t)((pWaveFormatStruct->ByteRate >> 24) & 0xFF);

  /* Write the block alignment -----------------------------------------------*/
  pHeader[32]  = pWaveFormatStruct->BlockAlign;
  pHeader[33]  = 0x00;

  /* Write the number of bits per sample -------------------------------------*/
  pHeader[34]  = pWaveFormatStruct->BitPerSample;
  pHeader[35]  = 0x00;

  /* Write the Data chunk, must be 'data' ------------------------------------*/
  pHeader[36]  = 'd';
  pHeader[37]  = 'a';
  pHeader[38]  = 't';
  pHeader[39]  = 'a';

  /* Write the number of sample data -----------------------------------------*/
  /* This variable will be written back at the end of the recording operation */
  pHeader[40]  = 0x00;
  pHeader[41]  = 0x4C;
  pHeader[42]  = 0x1D;
  pHeader[43]  = 0x00;

  /* Return 0 if all operations are OK */
  return 0;
}

static uint32_t WavProcess_HeaderUpdate(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct)
{
  /* Write the file length ---------------------------------------------------*/
  /* The sampling time: this value will be written back at the end of the
     recording operation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
  pHeader[4] = (uint8_t)(BufferCtl.fptr);
  pHeader[5] = (uint8_t)(BufferCtl.fptr >> 8);
  pHeader[6] = (uint8_t)(BufferCtl.fptr >> 16);
  pHeader[7] = (uint8_t)(BufferCtl.fptr >> 24);
  /* Write the number of sample data -----------------------------------------*/
  /* This variable will be written back at the end of the recording operation */
  BufferCtl.fptr -=44;
  pHeader[40] = (uint8_t)(BufferCtl.fptr);
  pHeader[41] = (uint8_t)(BufferCtl.fptr >> 8);
  pHeader[42] = (uint8_t)(BufferCtl.fptr >> 16);
  pHeader[43] = (uint8_t)(BufferCtl.fptr >> 24);

  /* Return 0 if all operations are OK */
  return 0;
}

static void AUDIO_REC_DisplayButtons(void)
{
  BSP_LCD_SetFont(&LCD_LOG_HEADER_FONT);
  BSP_LCD_ClearStringLine(12);            /* Clear dedicated zone */
  BSP_LCD_ClearStringLine(13);
  BSP_LCD_ClearStringLine(14);
  BSP_LCD_ClearStringLine(15);

  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
  BSP_LCD_FillCircle((TOUCH_RECORD_XMAX+TOUCH_RECORD_XMIN)/2, /* Record circle */
                     (TOUCH_RECORD_YMAX+TOUCH_RECORD_YMIN)/2,
                     (TOUCH_RECORD_XMAX-TOUCH_RECORD_XMIN)/2);
  BSP_LCD_FillRect(TOUCH_PAUSE_XMIN, TOUCH_PAUSE_YMIN , 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);    /* Pause rectangles */
  BSP_LCD_FillRect(TOUCH_PAUSE_XMIN + 20, TOUCH_PAUSE_YMIN, 15, TOUCH_PAUSE_YMAX - TOUCH_PAUSE_YMIN);
  BSP_LCD_FillRect(TOUCH_STOP_XMIN, TOUCH_STOP_YMIN , /* Stop rectangle */
                   TOUCH_STOP_XMAX - TOUCH_STOP_XMIN,
                   TOUCH_STOP_YMAX - TOUCH_STOP_YMIN);
  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_SetFont(&LCD_LOG_TEXT_FONT);
  BSP_LCD_DisplayStringAtLine(14, (uint8_t *)"Use record button to start record,");
  BSP_LCD_DisplayStringAtLine(15, (uint8_t *)"stop to exit");
  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
}

static void DisplayChoose(void)
{
	  LCD_ClearZone();
	  BSP_LCD_SetFont(&LCD_LOG_HEADER_FONT);
	  BSP_LCD_ClearStringLine(12);            /* Clear dedicated zone */
	  BSP_LCD_ClearStringLine(13);
	  BSP_LCD_ClearStringLine(14);
	  BSP_LCD_ClearStringLine(15);

	  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
	  BSP_LCD_FillRect(TOUCH_CHOOSE1_XMIN, TOUCH_CHOOSE1_YMIN , /* Stop rectangle */
			  TOUCH_CHOOSE1_XMAX - TOUCH_CHOOSE1_XMIN,
			  TOUCH_CHOOSE1_YMAX - TOUCH_CHOOSE1_YMIN);

	  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	  BSP_LCD_FillRect(TOUCH_CHOOSE2_XMIN, TOUCH_CHOOSE2_YMIN , /* Stop rectangle */
			  TOUCH_CHOOSE2_XMAX - TOUCH_CHOOSE2_XMIN,
			  TOUCH_CHOOSE2_YMAX - TOUCH_CHOOSE2_YMIN);

	  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	  BSP_LCD_SetFont(&LCD_LOG_TEXT_FONT);
	  BSP_LCD_DisplayStringAt(0,80,(uint8_t *)"FILTER", LEFT_MODE);
	  BSP_LCD_DisplayStringAt(0,80,(uint8_t *)"NO FILTER", RIGHT_MODE);
	  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
}


static void LCD_ClearZone(void)
{
  uint8_t i = 0;

  for(i= 0; i < 13; i++)
  {
    BSP_LCD_ClearStringLine(i + 3);
  }
}



