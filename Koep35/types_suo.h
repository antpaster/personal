/*----------------------------------------------------------------------------*
��� �����-35
��������� ������ ���
���_���, types_suo.h
��� ����, , 2008
������� �����������:
--------------------------
14���08,  - c�������
*----------------------------------------------------------------------------*/
#include <_defs_g.h>

#ifndef TYPES_SUO_H
#define TYPES_SUO_H

#ifdef SUO_C
#define EXTERN_SUO
#else
#define EXTERN_SUO extern
#endif

typedef enum 				// ������� ���������� 1, 2
{
	eSVAR_PRIM_PO1 = 1,		// �� �-�, ���, �� �-�, �-25, �� - �� 1; �-13, �-8 - �����; 
	eSVAR_PRIM_PO2 = 2,		// �� �-�, ���, �� �-�, �-25 - �� 2; �-13, �-8 - �� 2��;, �� - 0,5�
	eSVAR_PRIM_PO4 = 3,		// �� �-� - ���; ���, �� �-�, �-25 - �� 4; �-13, �-8 - �� 4��;, �� - ���
	eSVAR_PRIM_VSE = 4,		// �� �-� - ���; ���, �� �-�, �-13, �-8, �� - ���
} TSUO_VAR_PRIM;

typedef enum 				// �������� ����� ���
{
    eASP_NO_DEF      = -1,			    // �� ����������
    eASP_NO          = 0,			    // ���
    eASP_S_25		 = 0x02,			// �-25		[������ 35]
    eASP_S_8         = 0x04,			// �-8
    eASP_AB_MBD      = 0x05,			// �� �� ���
    eASP_AB2_MBD     = 0x06,			// �� �� ��� ��� 2
	eASP_S_13        = 0x07,			// �-13
	eASP_AB_RBK      = 0x08,			// �� ���
	eASP_AB2_RBK     = 0x09,			// �� ��� ��� 2
    eASP_K_07_05_07U = 0x0B,            // �-07, (�-05, �-07�)
    eASP_K_022       = 0x19,			// �-022
    eASP_K_05        = 0x1B,			// �-05**
    eASP_77P_AA1     = 0x21,            // 77� (��?)

    eASP_RVV_SD      = 0x23,			// 270			[������ 35]

    eASP_190         = 0x24,			// 190			[������ 35]
	eASP_470T1       = 0x25,			// 470�
    eASP_72E         = 0x29,			// 72 (72�)
    eASP_750         = 0x2B,			// 750*(750�)
	eASP_470R1       = 0x2E,			// 470�1
    eASP_470P1       = 0x2F,			// 470�1		[������ 35]
    eASP_64          = 0x30,			// 64
    eASP_620         = 0x31,			// ���-��		[������ 35]
    eASP_610M        = 0x33,			// 610M			[������ 35�]
    eASP_77A         = 0x34,			// 77�
    eASP_470ET1      = 0x35,			// 470�� 
    eASP_170_1       = 0x36,			// 170-1* 
    eASP_K_07U       = 0x3B,			// �-07�**
	eASP_470ER1      = 0x3E,			// 470��	
	eASP_470EP1      = 0x3F,			// 470��
	eASP_D9M2A       = 0x44,			// �9�2�
	eASP_D9MK        = 0x45,			// �9��			[������ 35]
	eASP_PTB         = 0x46,			// ���
	eASP_195PLD      = 0x4A,			// 195���		[������ 35]
    eASP_K_01S       = 0x50,			// �-01�*
    eASP_D_7USh      = 0x51,			// �-7��*
	eASP_K_021       = 0x5F,			// �-021
	eASP_77P_B1      = 0x61,			// 77� (�)
	eASP_77P_BC      = 0x62,            // 77� (�, �)

    eASP_PBK        = 0x4E,             // ���			[������ 35�]
    eASP_K_08B      = 0x4F,             // �-08�		[������ 35�]
    eASP_07         = 0x58,             // 07 
    eASP_77PK_AA1   = 0x63,             // 77��(��)		[������ 35�]
    eASP_77PK_B1    = 0x64,             // 77��(�)		[������ 35�]
    eASP_77PK_BC    = 0x65,             // 77��(�,C)	[������ 35�]
    eASP_63ME       = 0x70,             // 63M/63��
    eASP_50         = 0x78,             // ���.50
    eASP_50_1       = 0x79,             // ���.50-1
    eASP_P_06_K     = 0x7A,             // �-06(K)
    eASP_P_06_Y     = 0x7B,             // �-06(�)
    eASP_C_06_K     = 0x7C,             // C-06(K)
    eASP_C_06_Y     = 0x7D,             // C-06(�)
    eASP_810        = 0x26,             // 810
    eASP_810_C      = 0x27,             // 810(C)
    eASP_760        = 0x2C,             // 760
    eASP_610M_C     = 0x32,             // 610M(C)
    eASP_180        = 0x37,             // 180
    eASP_77AD       = 0x3C,             // 77��
    eASP_65ML_P     = 0x40,             // 65��(�)
    eASP_65ML_O     = 0x41,             // 65��(�)
    eASP_D9MK2      = 0x42,             // �9��2
    eASP_D_7UShK    = 0x52,             // �-7���
    eASP_K_029B     = 0x54,             // �-029�
    eASP_Man_r      = 0x5C,             // ���.���-�
    eASP_65K        = 0x67,             // 65�
    eASP_65MA       = 0x69,             // 65��
    eASP_65MT       = 0x6B,             // 65��
    eASP_K_08TB     = 0x6C,             // �-08��
    eASP_K_029TB    = 0x6D,             // �-029��
    eASP_K_047      = 0x73,             // �-047
    eASP_C_06_C     = 0x7E,             // �-06(�)

	eASP_3M_54A     = 0xFF01,			// 3�-54�*
	eASP_K_310A     = 0xFF02,			// �-310�*
	eASP_K_07M      = 0xFF04,			// �-07�*
	eASP_77PM       = 0xFF05,			// 77��*
	eASP_77AM       = 0xFF06,			// 77��*
	eASP_K_01LG     = 0xFF07,			// �-01�G*
	eASP_K_021M     = 0xFF08,			// �-021�*
	eASP_S_8UV      = 0xFF09,			// �-8��*
	eASP_172S_1     = 0xFF0A,			// 172�-1*

	eASP_Unknown    = 0x7F			    // ����������� ��� ���. 35� ��� ���
} TSUO_PR_ASP;

#define eASP_RVV_MD		eASP_750	// ���-��
#define eASP_RVV_MDM	eASP_760	// ���-���


typedef enum 				// ������� ���������
{
	eRAZGRUZ_1_2 = 0,		// �� 1-�� �� - 1-� ��������� ��� ���, �� 2-�� �� - 2-� ��������� ��� ���
	eRAZGRUZ_2_1 = 1		// �� 1-�� �� - 2-� ��������� ��� ���, �� 1-�� �� - 2-� ��������� ��� ���
} TSUO_RAZGRUZ;

typedef enum 				// ��������� ������� ��������� ��
{
	eTMBD_NO   = 0,			// �� �����
	eTMBD_0_1  = 1,			// 0,1�
	eTMBD_0_2  = 2,			// 0,2�
	eTMBD_0_3  = 3,			// 0,3�
	eTMBD_0_45 = 4			// 0,45�
} TSUO_TMBD;

typedef enum				// ���������� ��� ���������� ���
{
	eSUO_SUMTYPE_NO       = 0,		// ��� ���������� ���
	eSUO_SUMTYPE_VV       = 1,		// �� ��-»: 190, 470�1, 470��1, 470�1, 470��1, 470�1, 470��1, 72�(72�)
	eSUO_SUMTYPE_VP_LGSN  = 2,	  // ��� ��-ϻ � ����: 64, �-022, 195���
	eSUO_SUMTYPE_VP_TVGSN = 3,	  // ��� ��-ϻ � �����: �-07, �-07�, �-05, �-021, 63��
	eSUO_SUMTYPE_VP_ARGS  = 4,	  // �� ��-ϻ � ����: 77�, �9��
	eSUO_SUMTYPE_VP_PRGS  = 5,	  // �� ��-ϻ � ����: 77�
	eSUO_SUMTYPE_AB       = 6,		// ��, ���, �� �� ���
	eSUO_SUMTYPE_NAR      = 7		  // �-8, �-13, �-25
} TSUO_SUMTYPE_ASP;

typedef enum				// ������ (������� 4 ���)
{
	eNESH_ASP_NO    = 0,		// ��� ��������
	eNESH_ASP_NAL   = 1,		// ������ �� �������� ������� ���
	eNESH_ASP_SVR   = 2,		// ������ �� ��������� ���
	eNESH_ASP_OTKAZ = 3		  // ����� ���
} TSUO_NESH_ASP;

typedef enum				// ����� ���.� ��� (������� 8 ���)
{
	eREJ_ASP_NORM = 0,		// ������� ����� (������� ��� ������� � ����)
	eREJ_ASP_UTR  = 1,		// ������-������������� ����� (���)
	eREJ_ASP_OBL  = 2,		// �������� ����� (����)
	eREJ_ASP_TRN  = 3,		// ��������� ����� (���)
	eREJ_ASP_KCU  = 4		// ���
} TSUO_REJ_ASP;

// ������������ ����
//IKAR_Rezh_rab_s_ASP;		// ����� ���.� ���

// ������� ����� �������
typedef enum
{
	eTP1  = 0,  eTP2  = 1,  eTP3  = 2,  eTP4  = 3,
	eTP5  = 4,  eTP6  = 5,  eTP7  = 6,  eTP8  = 7,
	eTP9  = 8,  eTP10 = 9,  eTP11 = 10, eTP12 = 11,
	eTP1b = 12, eTP2b = 13, eTP3b = 14, eTP4b = 15
} TINDEX_TP;
#define eTP1a eTP1
#define eTP2a eTP2
#define eTP3a eTP3
#define eTP4a eTP4

// ������� �������� �������������� �������� (�� ��� � ����) ----------------------

// ��������� �� (������� ���������� Nal_gruza - 50��, ��������� - 12,5��)
// ��� ��� 72
typedef struct TBRPI_OCU_72
{
	unsigned char		Znak_Omega;
	double				Omega;
} TBRPI_OCU_72;

typedef struct TIKAR_BACK_TP
{
	unsigned      Ocher;			// ����������� ��: 0 - ������.������ ��� �������. ������� ��� �������
									// 1-��������� ���������,12-���������� ���������
	unsigned char P_kS_s;			// �-�/�-� ��
	unsigned char KPDv;				// ���� ��
	unsigned char PR;				// �� ��
	unsigned char Podg_vkl;			// ����. ���. ��
	unsigned char Vyb;				// ����� ��
	TSUO_PR_ASP   Priz_ASP;			// ������� ��� ��
	unsigned char Nal_gruza;		// ������� ����� ��
	unsigned char Zahv_0PUS;		// ������ 0���� ��
	unsigned char Svr;				// ��� ��
	TSUO_NESH_ASP Nesh;				// ������ ��
	unsigned char Otkaz_i_k;		// ����� ���. ������ 2���
	unsigned char DR;				// �� ��
	unsigned char PP;				// �� �� (������� ������)
	unsigned char Res_vyrab;		// ������ �����. ��
	unsigned char Pereh_prots;		// �����. ������� ��
	unsigned char Ispr;				// ����. ��
	unsigned char MPI_MRD;			// ��� ��� ��
	unsigned      Tek_kol_ASP;		// ������� ���������� ��� ��: 0..6, 7-������� ��� � �����
	unsigned char Ispr_BI_TP;		// ����. �� �� (��� 5,7 � 6,8 ���������)

	unsigned char O_sv_IKAR_BI_Os;	// ����� ��. ����-�� �� (��� 5,7 � 6,8 ���������)
	unsigned char O_sv_IKAR_BI_Rz;	
	unsigned char O_sv_BI_ASP_Os;	// ����� ��. ��-��� ��
	unsigned char O_sv_BI_ASP_Rz;

	unsigned Dop_Priz_ASP;				// ���. ������� ��� ��1a,2a,3a,4a,5,6,7,8,9,10,11,12
	unsigned char Priz_T_ost_ASP_pit;	// ������� ���������� ��1_2,3_4,9_10,11-12
	unsigned  T_res_ost_ASP_pit;		// ����/��������� ��1_2,3_4,9_10,11-12

	unsigned char SG;				// �� �� - ������� ������ (������ ��� �� 1, 3, 4, 11, 12)
	int Vrem_ohl;					// ����� ���. 72 ��: ��.�. = 1���. (������ ��� �� 3, 4, 5, 6, 7, 8)
	unsigned char OK;				// �� - �������� �������(������ ��� �� 3, 4, 5, 6, 7, 8, 11, 12)
	unsigned char Nal_pil;			// ���. ������ ��3 (������ ��� �� 3, 4, 5, 6, 11, 12)
	unsigned char BG;				// �� �� - ������� ������ (������ ��� �� 1, 3, 4, 11, 12)

	// ����������� ��� �����
	unsigned char O_sv_IKAR_BI;
	unsigned char O_sv_BI_ASP;
	unsigned  NLitRL;				// ����� �������

	TBRPI_OCU_72 OCU_72;			// // ��� ��� 72
} TIKAR_BACK_TP;

// ��������� �������� �������������� �������
typedef struct TIKAR_BACK_SUM		
{
	// 50��
	unsigned char PR_sum;				// �� c��.

	// 12.5, 50��
	unsigned char BK_fakt;				// �� ���� (��-���)
	unsigned char BK_v_VPU;				// �� � ���
	unsigned char BK_podhv;				// �� �����.
	unsigned char Nedop_zagr_MBD;		// �����. ����. ���

	// 12,5��
	unsigned char Korp_ispyt;			// ������ ���������
	unsigned char ZBK_5s;				// ��� 5�(���-35)
	unsigned char ZBK_3s;				// ��� 3�(���-35)
	unsigned char Ohl_27T;				// ���. 27� (��� ������ �� ���. 27�)
	unsigned char Ohl_72;				// ���. 72 (��� ������ �� ���. 72)
	unsigned char DR_ruchn;				// �� ����.(���-35)
	unsigned char Sbros_PTB;			// ����� ���
	unsigned char Pit_UR_VP;			// ���. �� ��
	unsigned char Avar_sbros_po_1;		// ����. ����� �� 1(���-35)
	unsigned char AR;					// �� - ���������� �����
	unsigned char PPS;					// ���(���-35)
	unsigned char Vozduh;				// ������(���-35)
	unsigned char Vzr;					// ���.(���-35)
	unsigned char Avar_sbros;			// ����. �����(���-35)
	unsigned char Avar_pusk;			// ����. ����(���-35)
	unsigned char Zvuk_signal;			// ����. ������ (��.���)

	unsigned char Glav;					// �����
	unsigned char ShU;					// �� (���)
	unsigned char TLM;					// ���

	unsigned char Im_ShU;				// �� ��
	unsigned char Ucheb_rab;			// ����. ������(���-35)
	unsigned char Dozapr_35P;			// ����������

	unsigned Razresh_TR;				// ���������� ��
	unsigned char Trenazh;				// ������
	unsigned char AKO;					// ���
	unsigned char Razr_AKO;				// ����. ���
	unsigned char N_kontrol;			// �� (��.���)

	unsigned char KTsU;					// ���
	unsigned char Avt_sbros_otrab;		// �������. �����.    
	unsigned char Sum_PR_1;				// ���. �� 1
	unsigned char Sum_PR_2;				// ���. �� 2
	unsigned char MGN;					// ���

	unsigned char AKO_V;				// ���-� (��.���)
	unsigned char Visit_hot_1;			// ����� ���� �� 1
	unsigned char Imit_BR;				// ����. ��
	unsigned char Zapret_BR_72;			// ������ �� 72
	unsigned char DRnasp;				// ������ (��.���)
	unsigned char VO;					// �� - ����� ������

	unsigned char MGN_1;				// ���-1
	unsigned char MGN_2;				// ���-2
	unsigned char MGN_3;				// ���-3
	unsigned char MGN_4;				// ���-4
	unsigned char Perekl_35P_v_AR;		// ������. 35� � �-� ��
	unsigned char Ohl_vseh_72;			// ���. ���� 72 (��.���)
	unsigned char A1suo;				// �1��� (��.���)
	unsigned char A2suo;				// �2��� (��.���)

	unsigned Rashod_bk_VPU;				// ������ �� ��� (0..150, 50-��)
	unsigned char Korot_ocher;			// �����. �������
	unsigned char Vybor_VPU;			// ����� ��� (��� - ��. "����� ���" )
	
	unsigned char El_spusk;				// ��. �����
	unsigned char Kompl_VPU;			// �����. ���
	unsigned char Pusk_v_SPP;			// ���� � ���

	unsigned char Kal_2_500;			// ������ �2 500 (��.���)

	unsigned char Zad_3_min;			// ���. 3 ���
	unsigned char Zad_5_min;			// ��� 5 ���

	unsigned Tek_kol_UR_na_TP;			// ������� ���-�� �� �� ��

	TSUO_REJ_ASP Rezh_rab_s_ASP;		// ����� ���.� ���
	TSUO_SUMTYPE_ASP Sumtype_ASP;		// ���������� ���

	unsigned char Kal_2_50;				// ������ �2 50 (��.���)
	unsigned char Kal_2_100;			// ������ �2 100 (��.���)
	unsigned char Kal_2_250M62;			// ������ �2 250�62 (��.���)
	unsigned char Kal_2_250M54;			// ������ �2 250�54 (��.���)

	unsigned Tek_kol_AB_na_TP;			// ������� ���-�� �� �� ��: 1..48
	unsigned char Avt_sbros;			// ��� �����
	unsigned char Imp_sbrosa;			// ���. ������
	unsigned char Kal_50;				// ������ 50
	unsigned char Kal_100;				// ������ 100
	unsigned char Kal_250M62;			// ������ 250�62
	unsigned char Kal_250M54;			// ������ 250�54
	unsigned char Kal_500;				// ������ 500

	unsigned char dva_tipa_AB;			// 2 ���� ���� (��.���)

	unsigned char Start_kontr;			// ��������� ��������
	unsigned char Ispr_sv_IUS_35P;		// ����. ��. ���-35�
	unsigned char Ispr_IKAR_01;			// ����. ����-01
	unsigned char Ispr_35P;				// ����. 35�
	unsigned char Ispr_BRPI_35P_l;		// ����. ����-35� ���
	unsigned char Ispr_BRPI_35P_p;		// ����. ����-35� ����

	unsigned char Ispr_35P_v_vyb;		// ����. 35� � ���.

	unsigned char Ispr_MAR;				// ����. ���
	unsigned char Ispr_MAP;				// ����. ���

	unsigned char SPARKA_TP1;      		// ������ ��1
	unsigned char SPARKA_TP2;      		// ������ ��2
	unsigned char SPARKA_TP3;      		// ������ ��3
	unsigned char SPARKA_TP4;      		// ������ ��4

	TSUO_PR_ASP Priz_1_tipa_ASP;		// ������� 1-�� ���������� ���� ���
	TSUO_VAR_PRIM Var_prim_1;			// ������� ���������� 1
	unsigned char DBK;					// ���
	TSUO_RAZGRUZ Por_razgruz;			// ������� ���������

	TSUO_PR_ASP Priz_2_tipa_ASP;		// ������� 2-�� ���������� ���� ���
	TSUO_VAR_PRIM Var_prim_2;			// ������� ���������� 2
	unsigned char Pr_ogr_PR;			// ��. ���. ��
	unsigned char IKAR_0_PUS_3aTP;		// 0 ��� ��3�	
	unsigned char IKAR_0_PUS_4aTP;		// 0 ��� ��4�	
	unsigned char IKAR_0_PUS_3bTP;		// 0 ��� ��3�	
	unsigned char IKAR_0_PUS_4bTP;		// 0 ��� ��4�	
	unsigned char IKAR_0_PUS_11TP;		// 0 ��� ��11	
	unsigned char IKAR_0_PUS_12TP;		// 0 ��� ��12	
	unsigned Var_Smen;					// ������� �����
	unsigned char Ust;					// ���������	

	unsigned char UV_Activ;				/* ����� */
	unsigned char UV_Allowed_Disp;		/* ���������� �� ������� */
	unsigned char UV_Auto;				/* ������� */
	unsigned char UV_CritPPI;			/* ����������� ���������� ��� */
	unsigned char UV_CritPPL;			/* ����������� ���������� ��� */
	unsigned char UV_CritPPR;			/* ����������� ���������� ��� */
	unsigned UV_Dispensing;				/* ���� ������� */
	unsigned char UV_Dost_Record;		/* ������-�� ������ */
	unsigned char UV_Ispr;				/* ����. �� */
	unsigned UV_Kol_P_Type10;			/* ���������� �������� ���� 10 */
	unsigned UV_Kol_P_Type11;			/* ���������� �������� ���� 11 */
	unsigned UV_Kol_P_Type2;			/* ���������� �������� ���� 2 */
	unsigned UV_Kol_P_Type22;			/* ���������� �������� ���� 22 */
	unsigned UV_Kol_P_Type3;			/* ���������� �������� ���� 3 */
	unsigned UV_Kol_P_Type31;			/* ���������� �������� ���� 31 */
	unsigned UV_Kol_P_Type32;			/* ���������� �������� ���� 32 */
	unsigned UV_Kol_P_Type33;			/* ���������� �������� ���� 33 */
	unsigned UV_Kol_P_Type35;			/* ���������� �������� ���� 35 */
	unsigned UV_Kol_P_Type7;			/* ���������� �������� ���� 7 */
	unsigned UV_Kol_P_Type8;			/* ���������� �������� ���� 8 */
	unsigned UV_Mode;					/* ����� ������ �� */
	unsigned char UV_NK;				/* �� �� */
	unsigned UV_N_Prog_Otstrela;		/* ����� ��������� �������� */
	unsigned UV_N_Zap_Mas;				/* ����� ����������� ������� */
	unsigned char UV_Otk_Sv_BV_1_IKAR;	/* ����� ��. ��1-���� */
	unsigned char UV_Otk_Sv_BV_2_IKAR;	/* ����� ��. ��2-���� */
	unsigned char UV_Otk_Sv_BV_3_IKAR;	/* ����� ��. ��3-���� */
	unsigned char UV_Otk_Sv_BV_4_IKAR;	/* ����� ��. ��4-���� */
	unsigned char UV_Otk_Sv_BV_5_IKAR;	/* ����� ��. ��5-���� */
	unsigned char UV_Otk_Sv_BV_6_IKAR;	/* ����� ��. ��6-���� */
	unsigned UV_QuantityPPI;			/* ���������� ��� */
	unsigned UV_QuantityPPL;			/* ���������� ��� */
	unsigned UV_QuantityPPR;			/* ���������� ��� */
	unsigned char UV_RBR;				/* ��� */
	unsigned char UV_Ready_to_Record;	/* ����� � ������ */
	unsigned char UV_Record;			/* ���� ������ */
	unsigned char UV_Ruchnoi;			/* ������ */
	unsigned char UV_Sbros_DO_LTC;		/* ����� ��/��� */
	unsigned UV_Sost_P_BV[84];
} TIKAR_BACK_SUM;

// ������� ������ �������������� �������� (�� ���� � ���) ----------------------

// �� ��� 72
typedef struct TBRPI_CU_72
{
	TSUO_PR_ASP			Prizn_ASP_TP;			// ������� ��� �� ��
	unsigned char		Vybor_TP;				// ����� ��

	unsigned char		Znak_f1_72;				// ���� �1
	double				f1_72;					// �1 
	unsigned char		KTsU_72;				// ���
	unsigned char		Hsr_72;					// ���
	unsigned char		WorkGround;				// ������ �� �����
	unsigned char		Otkl_PNTs_72;			// ����. ���
	unsigned char		Znak_f2_72;				// ���� �2
	double				f2_72;					// �2
	unsigned char		M1_72;					// �1
	unsigned char		M2_72;					// �2
	unsigned char		TTs1_72;				// ��1
	unsigned char		TTs2_72;				// ��2
} TBRPI_CU_72;
/* ������� ��������� 72:
   - �� 1: 5, 6, 3, 4, 7, 8 (� ��. �� �������/�� �����
     ��� �� ��. ����������� �������. � �� �� ���������)
   - �� 2: 5->6, 3->4, 7->8  � ������. 0.16�+-20% (� ��. �� �������/�� �����
     ��� �� ��. ����������� �������. � �� �� ���������, ������������
	 � ������ ��. ���������, ����� ����. 2.4�+-0.1)
*/

// �� ��� 470�
typedef struct TBRPI_CU_470T
{
	TSUO_PR_ASP			Prizn_ASP_TP;		// ������� ��� �� ��
	unsigned char		Vybor_TP;			// ����� ��

	unsigned char		P1;					// ����. 1 ����
	unsigned char		DR;					// ��
	unsigned char		Ispr;				// ����

	double				Fi1;				// �1, ������
	double				Fi2;				// �2, ������

	unsigned char		P2;					// ����. 2 ����
	unsigned char		VSK;				// ���
	unsigned char		BD;					// ����. ������.
	unsigned char		ZPS;				// ���
	unsigned char		PPO;				// ���

	unsigned char		CUR;				// ���

	unsigned			Code_Hn;			// ��� H�
	unsigned			Code_Hc;			// ��� H�
	unsigned			Code_Hsr;			// ��� Hsr

	double				D;					// �

	unsigned			TC;					// ��� ����:0-��., 1-���.,2-�����.
	unsigned			Code_Alfa_n;		// ��� ���� �����
	double				M;					// ����� ����

	double				Omega1;				// Omega1, ������/�
	double				Omega2;				// Omega2, ������/�

	double				Dt;					// d�/dt, �/�
	double				Vn;					// V�, �/�
} TBRPI_CU_470T;
/* ������� ��������� 470�:
   - �� 1: 3, 4, 11, 12 (� ��. �� �������/�� ����� ��� �� ��. 
     � ��3(��11) ����������� � ��4(��12))
   - �� 2: 3->4, 11->12 � ������. 0.4� (� ��. �� �������/�� �����
     ��� �� ��. ����������� �������. �� ���������)
*/

// ���������� ��
typedef struct TIKAR_CTRL_TP
{
	// 50��
	unsigned char DR;			// ��
	unsigned char Podg;			// ����.

	TBRPI_CU_72 BrpiCu72;		// �� ��� 72 �� ���� � ���� ���./����.

	// 12,5��
	TBRPI_CU_470T BrpiCu470T;	// �� ��� 470� �� ���� � ���� ���./����.

	unsigned char Otkaz_ASP;	// ����� ���
	unsigned Imit_priz_ASP;		// ������. ������� ���
	unsigned char Otkl_pit;		// ����. ���. ��
} TIKAR_CTRL_TP;
/*
(***) ������ ����� ������� ��� ��� ���. 470T1 (PZ_470T1[0]):
	4..10�.���� - ������� ���
	11�.���� - �����
	19�.���� - ����. ���� ���
��������� ����� (PZ_470T1[1]..PZ_470T1[18]) ����������� � �����. � ��� ����-470 (�������.)

���� ������������ ������ ����:
(������� ��� == ��� 470T1) && (����� == 1) && (����. ���� ��� == 1)
*/

// ��������� ������ �������������� �������
typedef struct TIKAR_CTRL_SUM		
{
	// 50��
	unsigned char PPS;					// ���

	// 12,5��
	TSUO_VAR_PRIM Var_prim_1;		    // ������� ���������� 1
	TSUO_TMBD tmbd;						// ����
	unsigned char DBK;					// ���
	unsigned char Por_razgruz;			// ������� ���������
	TSUO_VAR_PRIM Var_prim_2;			// ������� ���������� 2
	
	char Zah_PRR_3TP;					// ������ ��� 3��				
	char Zah_PRR_4TP;					// ������ ��� 4��				
	char Zah_PRR_9TP;					// ������ ��� 9��				
	char Zah_PRR_10TP;					// ������ ��� 10��				
	char Zah_PRR_11TP;					// ������ ��� 11��				
	char Zah_PRR_12TP;					// ������ ��� 12��				
	unsigned n_1_vyb_TP_PRR;			// � 1-�� ��������� �� ��� ���	
	unsigned n_2_vyb_TP_PRR;			// � 2-�� ��������� �� ��� ���	
	unsigned n_3_vyb_TP_PRR;			// � 3-� ��������� �� ��� ���	
	unsigned n_4_vyb_TP_PRR;			// � 4-�� ��������� �� ��� ���	

	unsigned char Smen_GSN_1;			// ����� ���-1
	unsigned char Smen_GSN_2;			// ����� ���-2
	unsigned char Smen_GSN_3;			// ����� ���-3
	unsigned char Smen_GSN_4;			// ����� ���-4
	unsigned char Ohl_vseh_72;		    // ���. ���� 72� (�� ����)

	unsigned char Kal_2_50;				// ������ �2 50
	unsigned char Kal_2_100;			// ������ �2 100
	unsigned char Kal_2_250M62;		    // ������ �2 250�62
	unsigned char Kal_2_250M54;		    // ������ �2 250�54
	unsigned char Kal_2_500;			// ������ �2 500

	/*
	unsigned char Otkl_pit_1_2TP;		// ����. ���. 1,2 ��
	unsigned char Otkl_pit_3_4TP;		// ����. ���. 3,4 ��
	unsigned char Otkl_pit_9_10TP;		// ����. ���. 9,10��
	unsigned char Otkl_pit_11_12TP;		// ����. ���. 11,12��
	*/

	unsigned char A1suo;				// �1���
	unsigned char A2suo;				// �2���
	unsigned char MGN_1;				// ���-1
	unsigned char MGN_2;				// ���-2
	unsigned char MGN_3;				// ���-3
	unsigned char MGN_4;				// ���-4
	unsigned char Ut_tip_KAB;			// �����. ���� ���
	unsigned char ResTv_KAB4;			// ����� ���4
	unsigned char BezSG_TvKAB;			// ��� �� �����
	unsigned char Zapr_Izm_Och1;		// ������� ����1
	unsigned char Zapr_Izm_Och2;		// ������� ����2
	unsigned char KOEP_35;				// ����-35
	unsigned char Kal_50;				// ������ 50
	unsigned char Kal_100;				// ������100
	unsigned char Kal_250M62;			// ������ 250�62
	unsigned char Kal_250M54;			// ������ 250�54
	unsigned char Kal_500;				// ������ 500

	unsigned char dva_tipa_AB;			// 2 ���� ����

	unsigned char Otkaz_ASP_2bTP;	// ����� ��� 2� ��	
	unsigned char Otkaz_ASP_1bTP;	// ����� ��� 1� ��	
	unsigned char Otkaz_ASP_2aTP;	// ����� ��� 2� ��	
	unsigned char Otkaz_ASP_1aTP;	// ����� ��� 1� ��	
	unsigned char Otkaz_ASP_10TP;	// ����� ��� 10 ��	
	unsigned char Otkaz_ASP_9TP;	// ����� ��� 9 ��	
	unsigned char Otkaz_ASP_12TP;	// ����� ��� 12 ��	
	unsigned char Otkaz_ASP_11TP;	// ����� ��� 11 ��	
	unsigned char Otkaz_ASP_4aTP;	// ����� ��� 4� ��	
	unsigned char Otkaz_ASP_3aTP;	// ����� ��� 3� ��	
	unsigned char Otkaz_ASP_6TP;	// ����� ��� 6 ��	
	unsigned char Otkaz_ASP_5TP;	// ����� ��� 5 ��	
	unsigned char Otkaz_ASP_8TP;	// ����� ��� 8 ��	
	unsigned char Otkaz_ASP_7TP;	// ����� ��� 7 ��	

	unsigned char MGN;					// ���
	unsigned char ZS;					// ��
	unsigned char NOP_SUO;				// ���

	unsigned char Vnesh_podsv;			// ����. �������
	unsigned char Strob_ot_KOEP;		// ����� �� ����
	unsigned char AKO;					// ���
	unsigned char NK;					// ��
	unsigned char Nach_TRN;				// ������ ���
	unsigned char Trenazh;				// ������
	unsigned char Ispr_BTsVM_IUS_72;	// ����. ���� ��� � ���� � ����
	unsigned Ish_kompl_VPU;				// �������� �������� ���: 0..150 (���)
	unsigned char Kompl_VPU;			// �����. ��� (���)
	unsigned char Korot_ocher;			// �����. ������� (���)
	unsigned char Pr_ogr_PR;			// ��. ���. ��
	unsigned char Uch_rab_VPU;			// ����. ���. ���

	/*
	1. � ��� ���� �����������
	2. AKO_V �������� ���
	*/
	unsigned char AvtoSbros;          // ���. �����
	unsigned char Impuls_Sbr;         // ������� ������
	unsigned char DRnasp;			  // ������
	unsigned char PRR_2_po_2_ts;	  // ��� �� 2 �� 2 �
	unsigned N_1_Vbr_TP_PRR;          // ����� 1-�� ��������� �� ��� ���
	unsigned N_2_Vbr_TP_PRR;          // ����� 2-�� ��������� �� ��� ���
	unsigned N_3_Vbr_TP_PRR;          // ����� 3-� ��������� �� ��� ���
	unsigned N_4_Vbr_TP_PRR;          // ����� 4-�� ��������� �� ��� ���
	unsigned char AKO_V;              // ���-�

	unsigned Var_Smen;				// ������� �����
	unsigned char NK_UV;			// �� ��
	unsigned N_Prog_OtstrelaPP_BG;	// ����� ��������� �������� �� � "������" ������ �� ��. "��"			
	unsigned N_Prog_OtstrelaPP_LTC;	// ����� ��������� �������� �� � "������" ������ �� ��. "����� �� ���"		
	unsigned char KPRNO_Ust_IKAR;	// ���������			

	unsigned char Rab_s_OU_ASP[16];	// ������ � �� ��� ��� ��
} TIKAR_CTRL_SUM;

// ��������� ���
typedef struct TSUO_STAT		
{
	IO_STATE ios_tx1;
	IO_STATE ios_tx2;
	IO_STATE ios_tx3;

	char bConnect;		// "����� ���"
	char bErr;			// ������������ ������� �������������
	int ErrCode;		// ��� �������������
	char bErrExt;		// ����� �� ������������ ������

	unsigned nErrIO;	// ������� ������ ������
	char bErrIO;		// ������� ������������� ������
	
	double T_powerOn;	// ����� �������� ��������� ������� 
	double T_full;		// ����� �����
	
	unsigned nErrSS;	// ������� ������ �� ��
	unsigned bErrSS;	// ������ �� ��

	char bErrTest;		// ����� �������� ��������

	char bTest_Suo35p;
	char bTest_Suo35p_prev;
} TSUO_STAT;

EXTERN_SUO TSUO_STAT SuoStat;				// ��������� ���
EXTERN_SUO TIKAR_BACK_SUM IkarBackSum;		// ��������� �������� �������������� �������
EXTERN_SUO TIKAR_BACK_TP IkarBackTp[16];	// �������� �������������� �������, ��������� ��
EXTERN_SUO TIKAR_CTRL_SUM IkarCtrlSum;		// ��������� ������ �������������� �������
EXTERN_SUO TIKAR_CTRL_TP IkarCtrlTp[16];	// ���������� ��

#endif	//TYPES_SUO_H
