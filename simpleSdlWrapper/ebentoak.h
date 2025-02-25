#ifndef EBENTUAK_H
#define EBENTUAK_H
#include <SDL.h>

typedef struct S_POSIZIOA
{
    double x;
    double y;

} POSIZIOA;

/*
  Helburua: Funztio hau tekla bat sakatu arte zain dago,
  eta ondoren zenbaki oso baten bitartez zein sakatu den adieraziko digu.
  Sarrera:
  Irteera: Sakatuta teklaren identifikadorea
*/
int ebentuaJasoGertatuBada(void);
POSIZIOA saguarenPosizioa();

#define SAGU_MUGIMENDUA 4
#define SAGU_BOTOIA_ESKUMA 5
#define SAGU_BOTOIA_EZKERRA 6
#define GERTAERA_IRTEN 12

#define TECLA_RETURN 13
#define TECLA_ESCAPE 27
#define TECLA_SPACE 32
#define TECLA_0 48
#define TECLA_1 49
#define TECLA_2 50
#define TECLA_3 51
#define TECLA_4 52
#define TECLA_5 53
#define TECLA_6 54
#define TECLA_7 55
#define TECLA_8 56
#define TECLA_9 57
#define TECLA_a 97
#define TECLA_b 98
#define TECLA_c 99
#define TECLA_d 100
#define TECLA_e 101
#define TECLA_f 102
#define TECLA_g 103
#define TECLA_h 104
#define TECLA_i 105
#define TECLA_j 106
#define TECLA_k 107
#define TECLA_l 108
#define TECLA_m 109
#define TECLA_n 110
#define TECLA_o 111
#define TECLA_p 112
#define TECLA_q 113
#define TECLA_r 114
#define TECLA_s 115
#define TECLA_t 116
#define TECLA_u 117
#define TECLA_v 118
#define TECLA_w 119
#define TECLA_x 120
#define TECLA_y 121
#define TECLA_z 122
#define TECLA_UP 273
#define TECLA_DOWN 274
#define TECLA_RIGHT 275
#define TECLA_LEFT 276

/*
#define TECLA_NUL 0
#define TECLA_SOH 1
#define TECLA_STX 2
#define TECLA_ETX 3
#define TECLA_EOT 4
#define TECLA_ENQ 5
#define TECLA_ACK 6
#define TECLA_BEL 7
#define TECLA_BS 8
#define TECLA_TAB 9
#define TECLA_LF 10
#define TECLA_VT 11
#define TECLA_FF 12
#define TECLA_CR 13
#define TECLA_SO 14
#define TECLA_SI 15
#define TECLA_DLE 16
#define TECLA_DC1 17
#define TECLA_DC2 18
#define TECLA_DC3 19
#define TECLA_DC4 20
#define TECLA_NAK 21
#define TECLA_SYN 22
#define TECLA_ETB 23
#define TECLA_CAN 24
#define TECLA_EM 25
#define TECLA_SUB 26
#define TECLA_ESC 27
#define TECLA_FS 28
#define TECLA_GS 29
#define TECLA_RS 30
#define TECLA_US 31
#define TECLA_SPACE 32
#define TECLA_EXCLAMATION 33
#define TECLA_QUOTE 34
#define TECLA_HASH 35
#define TECLA_DOLLAR 36
#define TECLA_PERCENT 37
#define TECLA_AMPERSAND 38
#define TECLA_SINGLE_QUOTE 39
#define TECLA_LEFT_PARENTHESIS 40
#define TECLA_RIGHT_PARENTHESIS 41
#define TECLA_ASTERISK 42
#define TECLA_PLUS 43
#define TECLA_COMMA 44
#define TECLA_MINUS 45
#define TECLA_DOT 46
#define TECLA_SLASH 47
#define TECLA_0 48
#define TECLA_1 49
#define TECLA_2 50
#define TECLA_3 51
#define TECLA_4 52
#define TECLA_5 53
#define TECLA_6 54
#define TECLA_7 55
#define TECLA_8 56
#define TECLA_9 57
#define TECLA_COLON 58
#define TECLA_SEMICOLON 59
#define TECLA_LESS_THAN 60
#define TECLA_EQUALS 61
#define TECLA_GREATER_THAN 62
#define TECLA_QUESTION 63
#define TECLA_AT 64
#define TECLA_A 65
#define TECLA_B 66
#define TECLA_C 67
#define TECLA_D 68
#define TECLA_E 69
#define TECLA_F 70
#define TECLA_G 71
#define TECLA_H 72
#define TECLA_I 73
#define TECLA_J 74
#define TECLA_K 75
#define TECLA_L 76
#define TECLA_M 77
#define TECLA_N 78
#define TECLA_O 79
#define TECLA_P 80
#define TECLA_Q 81
#define TECLA_R 82
#define TECLA_S 83
#define TECLA_T 84
#define TECLA_U 85
#define TECLA_V 86
#define TECLA_W 87
#define TECLA_X 88
#define TECLA_Y 89
#define TECLA_Z 90
#define TECLA_LEFT_BRACKET 91
#define TECLA_BACKSLASH 92
#define TECLA_RIGHT_BRACKET 93
#define TECLA_CARET 94
#define TECLA_UNDERSCORE 95
#define TECLA_BACKTICK 96
#define TECLA_a 97
#define TECLA_b 98
#define TECLA_c 99
#define TECLA_d 100
#define TECLA_e 101
#define TECLA_f 102
#define TECLA_g 103
#define TECLA_h 104
#define TECLA_i 105
#define TECLA_j 106
#define TECLA_k 107
#define TECLA_l 108
#define TECLA_m 109
#define TECLA_n 110
#define TECLA_o 111
#define TECLA_p 112
#define TECLA_q 113
#define TECLA_r 114
#define TECLA_s 115
#define TECLA_t 116
#define TECLA_u 117
#define TECLA_v 118
#define TECLA_w 119
#define TECLA_x 120
#define TECLA_y 121
#define TECLA_z 122
#define TECLA_LEFT_CURLY 123
#define TECLA_VERTICAL_BAR 124
#define TECLA_RIGHT_CURLY 125
#define TECLA_TILDE 126
#define TECLA_DEL 127
*/
#endif
