/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/ISE/TFT_LCD/TFT_LCD.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_1744673427_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_0196099661_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    int t9;
    int t10;
    char *t11;
    char *t12;
    int t13;
    int t14;
    char *t15;

LAB0:    xsi_set_current_line(68, ng0);
    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)2);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 992U);
    t3 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 6144);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(69, ng0);
    t1 = (t0 + 6288);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((int *)t8) = 0;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(70, ng0);
    t1 = (t0 + 6352);
    t2 = (t1 + 56U);
    t5 = *((char **)t2);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((int *)t7) = 0;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB5:    xsi_set_current_line(72, ng0);
    t2 = (t0 + 1672U);
    t5 = *((char **)t2);
    t9 = *((int *)t5);
    t2 = (t0 + 2768U);
    t6 = *((char **)t2);
    t10 = *((int *)t6);
    t4 = (t9 == t10);
    if (t4 != 0)
        goto LAB7;

LAB9:    xsi_set_current_line(75, ng0);
    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t10 = (t9 + 1);
    t1 = (t0 + 6288);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((int *)t8) = t10;
    xsi_driver_first_trans_fast(t1);

LAB8:    xsi_set_current_line(77, ng0);
    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t1 = (t0 + 2768U);
    t5 = *((char **)t1);
    t10 = *((int *)t5);
    t3 = (t9 == t10);
    if (t3 != 0)
        goto LAB10;

LAB12:
LAB11:    goto LAB3;

LAB7:    xsi_set_current_line(73, ng0);
    t2 = (t0 + 6288);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    *((int *)t12) = 0;
    xsi_driver_first_trans_fast(t2);
    goto LAB8;

LAB10:    xsi_set_current_line(78, ng0);
    t1 = (t0 + 1832U);
    t6 = *((char **)t1);
    t13 = *((int *)t6);
    t1 = (t0 + 3368U);
    t7 = *((char **)t1);
    t14 = *((int *)t7);
    t4 = (t13 == t14);
    if (t4 != 0)
        goto LAB13;

LAB15:    xsi_set_current_line(81, ng0);
    t1 = (t0 + 1832U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t10 = (t9 + 1);
    t1 = (t0 + 6352);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((int *)t8) = t10;
    xsi_driver_first_trans_fast(t1);

LAB14:    goto LAB11;

LAB13:    xsi_set_current_line(79, ng0);
    t1 = (t0 + 6352);
    t8 = (t1 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t15 = *((char **)t12);
    *((int *)t15) = 0;
    xsi_driver_first_trans_fast(t1);
    goto LAB14;

}

static void work_a_0196099661_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    int t9;
    int t10;
    int t11;
    int t12;
    int t13;
    int t14;
    char *t15;
    int t16;
    int t17;
    char *t18;
    int t19;
    int t20;
    unsigned char t21;
    char *t22;
    int t23;
    char *t24;
    int t25;
    unsigned char t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;

LAB0:    xsi_set_current_line(90, ng0);
    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)2);
    if (t4 != 0)
        goto LAB2;

LAB4:    xsi_set_current_line(93, ng0);
    t1 = (t0 + 1832U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t1 = (t0 + 3488U);
    t5 = *((char **)t1);
    t10 = *((int *)t5);
    t1 = (t0 + 3608U);
    t6 = *((char **)t1);
    t11 = *((int *)t6);
    t12 = (t10 + t11);
    t4 = (t9 >= t12);
    if (t4 == 1)
        goto LAB8;

LAB9:    t3 = (unsigned char)0;

LAB10:    if (t3 != 0)
        goto LAB5;

LAB7:    xsi_set_current_line(102, ng0);
    t1 = (t0 + 6416);
    t2 = (t1 + 56U);
    t5 = *((char **)t2);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);

LAB6:
LAB3:    t1 = (t0 + 6160);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(91, ng0);
    t1 = (t0 + 6416);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB5:    xsi_set_current_line(94, ng0);
    t1 = (t0 + 1672U);
    t22 = *((char **)t1);
    t23 = *((int *)t22);
    t1 = (t0 + 3008U);
    t24 = *((char **)t1);
    t25 = *((int *)t24);
    t26 = (t23 == t25);
    if (t26 != 0)
        goto LAB11;

LAB13:    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t9 = *((int *)t2);
    t1 = (t0 + 3128U);
    t5 = *((char **)t1);
    t10 = *((int *)t5);
    t1 = (t0 + 3008U);
    t6 = *((char **)t1);
    t11 = *((int *)t6);
    t12 = (t10 + t11);
    t3 = (t9 == t12);
    if (t3 != 0)
        goto LAB14;

LAB15:    xsi_set_current_line(99, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 6416);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = t3;
    xsi_driver_first_trans_fast(t1);

LAB12:    goto LAB6;

LAB8:    t1 = (t0 + 1832U);
    t7 = *((char **)t1);
    t13 = *((int *)t7);
    t1 = (t0 + 3488U);
    t8 = *((char **)t1);
    t14 = *((int *)t8);
    t1 = (t0 + 3608U);
    t15 = *((char **)t1);
    t16 = *((int *)t15);
    t17 = (t14 + t16);
    t1 = (t0 + 3728U);
    t18 = *((char **)t1);
    t19 = *((int *)t18);
    t20 = (t17 + t19);
    t21 = (t13 <= t20);
    t3 = t21;
    goto LAB10;

LAB11:    xsi_set_current_line(95, ng0);
    t1 = (t0 + 6416);
    t27 = (t1 + 56U);
    t28 = *((char **)t27);
    t29 = (t28 + 56U);
    t30 = *((char **)t29);
    *((unsigned char *)t30) = (unsigned char)3;
    xsi_driver_first_trans_fast(t1);
    goto LAB12;

LAB14:    xsi_set_current_line(97, ng0);
    t1 = (t0 + 6416);
    t7 = (t1 + 56U);
    t8 = *((char **)t7);
    t15 = (t8 + 56U);
    t18 = *((char **)t15);
    *((unsigned char *)t18) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    goto LAB12;

}

static void work_a_0196099661_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    int t11;
    int t12;
    int t13;
    int t14;
    unsigned char t15;
    int t16;
    int t17;
    int t18;
    int t19;
    char *t20;
    int t21;
    int t22;
    unsigned char t23;
    unsigned char t24;
    char *t25;
    int t26;
    char *t27;
    int t28;
    char *t29;
    int t30;
    int t31;
    int t32;
    unsigned char t33;
    char *t34;
    int t35;
    char *t36;
    int t37;
    char *t38;
    int t39;
    int t40;
    int t41;
    unsigned char t42;
    unsigned char t43;
    char *t44;
    int t45;
    char *t46;
    int t47;
    char *t48;
    int t49;
    int t50;
    int t51;
    unsigned char t52;
    char *t53;
    int t54;
    char *t55;
    int t56;
    char *t57;
    int t58;
    int t59;
    int t60;
    unsigned char t61;
    char *t63;
    char *t64;
    char *t65;
    char *t66;
    char *t67;

LAB0:    xsi_set_current_line(110, ng0);
    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)2);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 992U);
    t3 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 6176);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(111, ng0);
    t1 = xsi_get_transient_memory(5U);
    memset(t1, 0, 5U);
    t5 = t1;
    memset(t5, (unsigned char)2, 5U);
    t6 = (t0 + 6480);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 5U);
    xsi_driver_first_trans_fast(t6);
    xsi_set_current_line(112, ng0);
    t1 = xsi_get_transient_memory(6U);
    memset(t1, 0, 6U);
    t2 = t1;
    memset(t2, (unsigned char)2, 6U);
    t5 = (t0 + 6544);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 6U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(113, ng0);
    t1 = xsi_get_transient_memory(5U);
    memset(t1, 0, 5U);
    t2 = t1;
    memset(t2, (unsigned char)2, 5U);
    t5 = (t0 + 6608);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 5U);
    xsi_driver_first_trans_fast(t5);
    goto LAB3;

LAB5:    xsi_set_current_line(115, ng0);
    t2 = (t0 + 1832U);
    t5 = *((char **)t2);
    t11 = *((int *)t5);
    t2 = (t0 + 3488U);
    t6 = *((char **)t2);
    t12 = *((int *)t6);
    t2 = (t0 + 3608U);
    t7 = *((char **)t2);
    t13 = *((int *)t7);
    t14 = (t12 + t13);
    t15 = (t11 >= t14);
    if (t15 == 1)
        goto LAB10;

LAB11:    t4 = (unsigned char)0;

LAB12:    if (t4 != 0)
        goto LAB7;

LAB9:
LAB8:    goto LAB3;

LAB7:    xsi_set_current_line(116, ng0);
    t2 = (t0 + 1672U);
    t25 = *((char **)t2);
    t26 = *((int *)t25);
    t2 = (t0 + 2888U);
    t27 = *((char **)t2);
    t28 = *((int *)t27);
    t2 = (t0 + 3008U);
    t29 = *((char **)t2);
    t30 = *((int *)t29);
    t31 = (t28 + t30);
    t32 = (t31 - 1);
    t33 = (t26 >= t32);
    if (t33 == 1)
        goto LAB16;

LAB17:    t24 = (unsigned char)0;

LAB18:    if (t24 != 0)
        goto LAB13;

LAB15:
LAB14:    goto LAB8;

LAB10:    t2 = (t0 + 1832U);
    t8 = *((char **)t2);
    t16 = *((int *)t8);
    t2 = (t0 + 3488U);
    t9 = *((char **)t2);
    t17 = *((int *)t9);
    t2 = (t0 + 3608U);
    t10 = *((char **)t2);
    t18 = *((int *)t10);
    t19 = (t17 + t18);
    t2 = (t0 + 3728U);
    t20 = *((char **)t2);
    t21 = *((int *)t20);
    t22 = (t19 + t21);
    t23 = (t16 <= t22);
    t4 = t23;
    goto LAB12;

LAB13:    xsi_set_current_line(117, ng0);
    t2 = (t0 + 1832U);
    t44 = *((char **)t2);
    t45 = *((int *)t44);
    t2 = (t0 + 3488U);
    t46 = *((char **)t2);
    t47 = *((int *)t46);
    t2 = (t0 + 3608U);
    t48 = *((char **)t2);
    t49 = *((int *)t48);
    t50 = (t47 + t49);
    t51 = (t50 - 1);
    t52 = (t45 >= t51);
    if (t52 == 1)
        goto LAB22;

LAB23:    t43 = (unsigned char)0;

LAB24:    if (t43 != 0)
        goto LAB19;

LAB21:    t1 = (t0 + 1832U);
    t2 = *((char **)t1);
    t11 = *((int *)t2);
    t1 = (t0 + 3488U);
    t5 = *((char **)t1);
    t12 = *((int *)t5);
    t1 = (t0 + 3608U);
    t6 = *((char **)t1);
    t13 = *((int *)t6);
    t14 = (t12 + t13);
    t16 = (t14 + 160);
    t4 = (t11 >= t16);
    if (t4 == 1)
        goto LAB27;

LAB28:    t3 = (unsigned char)0;

LAB29:    if (t3 != 0)
        goto LAB25;

LAB26:    t1 = (t0 + 1832U);
    t2 = *((char **)t1);
    t11 = *((int *)t2);
    t1 = (t0 + 3488U);
    t5 = *((char **)t1);
    t12 = *((int *)t5);
    t1 = (t0 + 3608U);
    t6 = *((char **)t1);
    t13 = *((int *)t6);
    t14 = (t12 + t13);
    t16 = (t14 + 320);
    t4 = (t11 >= t16);
    if (t4 == 1)
        goto LAB32;

LAB33:    t3 = (unsigned char)0;

LAB34:    if (t3 != 0)
        goto LAB30;

LAB31:
LAB20:    goto LAB14;

LAB16:    t2 = (t0 + 1672U);
    t34 = *((char **)t2);
    t35 = *((int *)t34);
    t2 = (t0 + 2888U);
    t36 = *((char **)t2);
    t37 = *((int *)t36);
    t2 = (t0 + 3008U);
    t38 = *((char **)t2);
    t39 = *((int *)t38);
    t40 = (t37 + t39);
    t41 = (t40 + 799);
    t42 = (t35 <= t41);
    t24 = t42;
    goto LAB18;

LAB19:    xsi_set_current_line(118, ng0);
    t2 = (t0 + 9341);
    t63 = (t0 + 6480);
    t64 = (t63 + 56U);
    t65 = *((char **)t64);
    t66 = (t65 + 56U);
    t67 = *((char **)t66);
    memcpy(t67, t2, 5U);
    xsi_driver_first_trans_fast(t63);
    xsi_set_current_line(119, ng0);
    t1 = xsi_get_transient_memory(6U);
    memset(t1, 0, 6U);
    t2 = t1;
    memset(t2, (unsigned char)2, 6U);
    t5 = (t0 + 6544);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 6U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(120, ng0);
    t1 = xsi_get_transient_memory(5U);
    memset(t1, 0, 5U);
    t2 = t1;
    memset(t2, (unsigned char)2, 5U);
    t5 = (t0 + 6608);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 5U);
    xsi_driver_first_trans_fast(t5);
    goto LAB20;

LAB22:    t2 = (t0 + 1832U);
    t53 = *((char **)t2);
    t54 = *((int *)t53);
    t2 = (t0 + 3488U);
    t55 = *((char **)t2);
    t56 = *((int *)t55);
    t2 = (t0 + 3608U);
    t57 = *((char **)t2);
    t58 = *((int *)t57);
    t59 = (t56 + t58);
    t60 = (t59 + 159);
    t61 = (t54 <= t60);
    t43 = t61;
    goto LAB24;

LAB25:    xsi_set_current_line(122, ng0);
    t1 = xsi_get_transient_memory(5U);
    memset(t1, 0, 5U);
    t10 = t1;
    memset(t10, (unsigned char)2, 5U);
    t20 = (t0 + 6480);
    t25 = (t20 + 56U);
    t27 = *((char **)t25);
    t29 = (t27 + 56U);
    t34 = *((char **)t29);
    memcpy(t34, t1, 5U);
    xsi_driver_first_trans_fast(t20);
    xsi_set_current_line(123, ng0);
    t1 = (t0 + 9346);
    t5 = (t0 + 6544);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 6U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(124, ng0);
    t1 = xsi_get_transient_memory(5U);
    memset(t1, 0, 5U);
    t2 = t1;
    memset(t2, (unsigned char)2, 5U);
    t5 = (t0 + 6608);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 5U);
    xsi_driver_first_trans_fast(t5);
    goto LAB20;

LAB27:    t1 = (t0 + 1832U);
    t7 = *((char **)t1);
    t17 = *((int *)t7);
    t1 = (t0 + 3488U);
    t8 = *((char **)t1);
    t18 = *((int *)t8);
    t1 = (t0 + 3608U);
    t9 = *((char **)t1);
    t19 = *((int *)t9);
    t21 = (t18 + t19);
    t22 = (t21 + 319);
    t15 = (t17 <= t22);
    t3 = t15;
    goto LAB29;

LAB30:    xsi_set_current_line(126, ng0);
    t1 = xsi_get_transient_memory(5U);
    memset(t1, 0, 5U);
    t10 = t1;
    memset(t10, (unsigned char)2, 5U);
    t20 = (t0 + 6480);
    t25 = (t20 + 56U);
    t27 = *((char **)t25);
    t29 = (t27 + 56U);
    t34 = *((char **)t29);
    memcpy(t34, t1, 5U);
    xsi_driver_first_trans_fast(t20);
    xsi_set_current_line(127, ng0);
    t1 = xsi_get_transient_memory(6U);
    memset(t1, 0, 6U);
    t2 = t1;
    memset(t2, (unsigned char)2, 6U);
    t5 = (t0 + 6544);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 6U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(128, ng0);
    t1 = (t0 + 9352);
    t5 = (t0 + 6608);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 5U);
    xsi_driver_first_trans_fast(t5);
    goto LAB20;

LAB32:    t1 = (t0 + 1832U);
    t7 = *((char **)t1);
    t17 = *((int *)t7);
    t1 = (t0 + 3488U);
    t8 = *((char **)t1);
    t18 = *((int *)t8);
    t1 = (t0 + 3608U);
    t9 = *((char **)t1);
    t19 = *((int *)t9);
    t21 = (t18 + t19);
    t22 = (t21 + 479);
    t15 = (t17 <= t22);
    t3 = t15;
    goto LAB34;

}

static void work_a_0196099661_3212880686_p_3(char *t0)
{
    char t4[16];
    char t10[16];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned char t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;

LAB0:    xsi_set_current_line(135, ng0);

LAB3:    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t1 = (t0 + 2312U);
    t3 = *((char **)t1);
    t5 = ((IEEE_P_2592010699) + 4024);
    t6 = (t0 + 9216U);
    t7 = (t0 + 9232U);
    t1 = xsi_base_array_concat(t1, t4, t5, (char)97, t2, t6, (char)97, t3, t7, (char)101);
    t8 = (t0 + 2472U);
    t9 = *((char **)t8);
    t11 = ((IEEE_P_2592010699) + 4024);
    t12 = (t0 + 9248U);
    t8 = xsi_base_array_concat(t8, t10, t11, (char)97, t1, t4, (char)97, t9, t12, (char)101);
    t13 = (5U + 6U);
    t14 = (t13 + 5U);
    t15 = (16U != t14);
    if (t15 == 1)
        goto LAB5;

LAB6:    t16 = (t0 + 6672);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    memcpy(t20, t8, 16U);
    xsi_driver_first_trans_fast_port(t16);

LAB2:    t21 = (t0 + 6192);
    *((int *)t21) = 1;

LAB1:    return;
LAB4:    goto LAB2;

LAB5:    xsi_size_not_matching(16U, t14, 0);
    goto LAB6;

}

static void work_a_0196099661_3212880686_p_4(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(136, ng0);

LAB3:    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 6736);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 6208);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_0196099661_3212880686_init()
{
	static char *pe[] = {(void *)work_a_0196099661_3212880686_p_0,(void *)work_a_0196099661_3212880686_p_1,(void *)work_a_0196099661_3212880686_p_2,(void *)work_a_0196099661_3212880686_p_3,(void *)work_a_0196099661_3212880686_p_4};
	xsi_register_didat("work_a_0196099661_3212880686", "isim/top_isim_beh.exe.sim/work/a_0196099661_3212880686.didat");
	xsi_register_executes(pe);
}
