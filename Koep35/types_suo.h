/*----------------------------------------------------------------------------*
ФПО КПрНО-35
Структуры данных СУО
ТИП_СУО, types_suo.h
ОАО РПКБ, , 2008
История модификации:
--------------------------
14янв08,  - cоздание
*----------------------------------------------------------------------------*/
#include <_defs_g.h>

#ifndef TYPES_SUO_H
#define TYPES_SUO_H

#ifdef SUO_C
#define EXTERN_SUO
#else
#define EXTERN_SUO extern
#endif

typedef enum 				// Вариант применения 1, 2
{
	eSVAR_PRIM_PO1 = 1,		// УР В-В, КАБ, УР В-П, С-25, БВ - по 1; С-13, С-8 - учебн; 
	eSVAR_PRIM_PO2 = 2,		// УР В-В, КАБ, УР В-П, С-25 - по 2; С-13, С-8 - по 2бл;, БВ - 0,5К
	eSVAR_PRIM_PO4 = 3,		// УР В-В - нет; КАБ, УР В-П, С-25 - по 4; С-13, С-8 - по 4бл;, БВ - нет
	eSVAR_PRIM_VSE = 4,		// УР В-В - МЦО; КАБ, УР В-П, С-13, С-8, БВ - все
} TSUO_VAR_PRIM;

typedef enum 				// Признаки типов АСП
{
    eASP_NO_DEF      = -1,			    // не определено
    eASP_NO          = 0,			    // нет
    eASP_S_25		 = 0x02,			// С-25		[только 35]
    eASP_S_8         = 0x04,			// С-8
    eASP_AB_MBD      = 0x05,			// АБ на МБД
    eASP_AB2_MBD     = 0x06,			// АБ на МБД код 2
	eASP_S_13        = 0x07,			// С-13
	eASP_AB_RBK      = 0x08,			// АБ РБК
	eASP_AB2_RBK     = 0x09,			// АБ РБК код 2
    eASP_K_07_05_07U = 0x0B,            // К-07, (К-05, К-07У)
    eASP_K_022       = 0x19,			// К-022
    eASP_K_05        = 0x1B,			// К-05**
    eASP_77P_AA1     = 0x21,            // 77П (АА?)

    eASP_RVV_SD      = 0x23,			// 270			[только 35]

    eASP_190         = 0x24,			// 190			[только 35]
	eASP_470T1       = 0x25,			// 470Т
    eASP_72E         = 0x29,			// 72 (72У)
    eASP_750         = 0x2B,			// 750*(750У)
	eASP_470R1       = 0x2E,			// 470Р1
    eASP_470P1       = 0x2F,			// 470П1		[только 35]
    eASP_64          = 0x30,			// 64
    eASP_620         = 0x31,			// РВВ-БД		[только 35]
    eASP_610M        = 0x33,			// 610M			[только 35С]
    eASP_77A         = 0x34,			// 77А
    eASP_470ET1      = 0x35,			// 470ЭТ 
    eASP_170_1       = 0x36,			// 170-1* 
    eASP_K_07U       = 0x3B,			// К-07У**
	eASP_470ER1      = 0x3E,			// 470ЭР	
	eASP_470EP1      = 0x3F,			// 470ЭП
	eASP_D9M2A       = 0x44,			// Д9М2А
	eASP_D9MK        = 0x45,			// Д9МК			[только 35]
	eASP_PTB         = 0x46,			// ПТБ
	eASP_195PLD      = 0x4A,			// 195ПЛД		[только 35]
    eASP_K_01S       = 0x50,			// К-01С*
    eASP_D_7USh      = 0x51,			// Д-7УШ*
	eASP_K_021       = 0x5F,			// К-021
	eASP_77P_B1      = 0x61,			// 77П (В)
	eASP_77P_BC      = 0x62,            // 77П (В, С)

    eASP_PBK        = 0x4E,             // ПБК			[только 35С]
    eASP_K_08B      = 0x4F,             // К-08Б		[только 35С]
    eASP_07         = 0x58,             // 07 
    eASP_77PK_AA1   = 0x63,             // 77ПК(АА)		[только 35С]
    eASP_77PK_B1    = 0x64,             // 77ПК(В)		[только 35С]
    eASP_77PK_BC    = 0x65,             // 77ПК(В,C)	[только 35С]
    eASP_63ME       = 0x70,             // 63M/63МЕ
    eASP_50         = 0x78,             // изд.50
    eASP_50_1       = 0x79,             // изд.50-1
    eASP_P_06_K     = 0x7A,             // П-06(K)
    eASP_P_06_Y     = 0x7B,             // П-06(У)
    eASP_C_06_K     = 0x7C,             // C-06(K)
    eASP_C_06_Y     = 0x7D,             // C-06(У)
    eASP_810        = 0x26,             // 810
    eASP_810_C      = 0x27,             // 810(C)
    eASP_760        = 0x2C,             // 760
    eASP_610M_C     = 0x32,             // 610M(C)
    eASP_180        = 0x37,             // 180
    eASP_77AD       = 0x3C,             // 77АД
    eASP_65ML_P     = 0x40,             // 65МЛ(П)
    eASP_65ML_O     = 0x41,             // 65МЛ(О)
    eASP_D9MK2      = 0x42,             // Д9МК2
    eASP_D_7UShK    = 0x52,             // Д-7УШК
    eASP_K_029B     = 0x54,             // К-029Б
    eASP_Man_r      = 0x5C,             // изд.Ман-р
    eASP_65K        = 0x67,             // 65К
    eASP_65MA       = 0x69,             // 65МА
    eASP_65MT       = 0x6B,             // 65МТ
    eASP_K_08TB     = 0x6C,             // К-08ТВ
    eASP_K_029TB    = 0x6D,             // К-029ТВ
    eASP_K_047      = 0x73,             // К-047
    eASP_C_06_C     = 0x7E,             // С-06(С)

	eASP_3M_54A     = 0xFF01,			// 3М-54А*
	eASP_K_310A     = 0xFF02,			// К-310А*
	eASP_K_07M      = 0xFF04,			// К-07М*
	eASP_77PM       = 0xFF05,			// 77ПМ*
	eASP_77AM       = 0xFF06,			// 77АМ*
	eASP_K_01LG     = 0xFF07,			// К-01ЛG*
	eASP_K_021M     = 0xFF08,			// К-021М*
	eASP_S_8UV      = 0xFF09,			// С-8УВ*
	eASP_172S_1     = 0xFF0A,			// 172С-1*

	eASP_Unknown    = 0x7F			    // Неизвестный для изд. 35П тип АСП
} TSUO_PR_ASP;

#define eASP_RVV_MD		eASP_750	// РВВ-МД
#define eASP_RVV_MDM	eASP_760	// РВВ-МДМ


typedef enum 				// Порядок разгрузки
{
	eRAZGRUZ_1_2 = 0,		// по 1-му БК - 1-й выбранный тип АСП, по 2-му БК - 2-й выбранный тип АСП
	eRAZGRUZ_2_1 = 1		// по 1-му БК - 2-й выбранный тип АСП, по 1-му БК - 2-й выбранный тип АСП
} TSUO_RAZGRUZ;

typedef enum 				// Иинтервал времени разгрузки АБ
{
	eTMBD_NO   = 0,			// не задан
	eTMBD_0_1  = 1,			// 0,1с
	eTMBD_0_2  = 2,			// 0,2с
	eTMBD_0_3  = 3,			// 0,3с
	eTMBD_0_45 = 4			// 0,45с
} TSUO_TMBD;

typedef enum				// Обобщенный тип выбранного АСП
{
	eSUO_SUMTYPE_NO       = 0,		// нет выбранного АСП
	eSUO_SUMTYPE_VV       = 1,		// УР «В-В»: 190, 470Р1, 470ЭР1, 470Т1, 470ЭТ1, 470П1, 470ЭП1, 72Э(72У)
	eSUO_SUMTYPE_VP_LGSN  = 2,	  // АСП «В-П» с ЛГСН: 64, К-022, 195ПЛД
	eSUO_SUMTYPE_VP_TVGSN = 3,	  // АСП «В-П» с ТВГСН: К-07, К-07У, К-05, К-021, 63МЕ
	eSUO_SUMTYPE_VP_ARGS  = 4,	  // УР «В-П» с АРГС: 77А, Д9МК
	eSUO_SUMTYPE_VP_PRGS  = 5,	  // УР «В-П» с ПРГС: 77П
	eSUO_SUMTYPE_AB       = 6,		// АБ, РБК, АБ на МБД
	eSUO_SUMTYPE_NAR      = 7		  // С-8, С-13, С-25
} TSUO_SUMTYPE_ASP;

typedef enum				// Несход (таблица 4 ПИВ)
{
	eNESH_ASP_NO    = 0,		// нет признака
	eNESH_ASP_NAL   = 1,		// Несход по неснятию наличия АСП
	eNESH_ASP_SVR   = 2,		// Несход по неприходу СВР
	eNESH_ASP_OTKAZ = 3		  // Отказ АСП
} TSUO_NESH_ASP;

typedef enum				// Режим раб.с АСП (таблица 8 ПИВ)
{
	eREJ_ASP_NORM = 0,		// Штатный режим (рабочий или учебный с НАСП)
	eREJ_ASP_UTR  = 1,		// Учебно-тренировочный режим (УТР)
	eREJ_ASP_OBL  = 2,		// Облетный режим (ОблР)
	eREJ_ASP_TRN  = 3,		// Тренажный режим (ТРН)
	eREJ_ASP_KCU  = 4		// КЦУ
} TSUO_REJ_ASP;

// Сформировать типы
//IKAR_Rezh_rab_s_ASP;		// Режим раб.с АСП

// Индексы точек подвеса
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

// Массивы обратных энергетических сигналов (из СУО в БЦВМ) ----------------------

// состояние ТП (частота распаковки Nal_gruza - 50Гц, остальных - 12,5Гц)
// ОЦУ для 72
typedef struct TBRPI_OCU_72
{
	unsigned char		Znak_Omega;
	double				Omega;
} TBRPI_OCU_72;

typedef struct TIKAR_BACK_TP
{
	unsigned      Ocher;			// Очередность ТП: 0 - израсх.ресурс ИЛИ переход. процесс ИЛИ невыбор
									// 1-наивысший приоритет,12-наименьший приоритет
	unsigned char P_kS_s;			// П-к/С-с ТП
	unsigned char KPDv;				// КПДв ТП
	unsigned char PR;				// ПР ТП
	unsigned char Podg_vkl;			// Подг. вкл. ТП
	unsigned char Vyb;				// Выбор ТП
	TSUO_PR_ASP   Priz_ASP;			// Признак АСП ТП
	unsigned char Nal_gruza;		// Наличие Груза ТП
	unsigned char Zahv_0PUS;		// Захват 0ПУСа ТП
	unsigned char Svr;				// СВР ТП
	TSUO_NESH_ASP Nesh;				// Несход ТП
	unsigned char Otkaz_i_k;		// Отказ исп. канала 2бТП
	unsigned char DR;				// ДР ТП
	unsigned char PP;				// ПП ТП (питание подано)
	unsigned char Res_vyrab;		// Ресурс выраб. ТП
	unsigned char Pereh_prots;		// Перех. Процесс ТП
	unsigned char Ispr;				// Испр. ТП
	unsigned char MPI_MRD;			// МПИ МРД ТП
	unsigned      Tek_kol_ASP;		// Текущее количество АСП ТП: 0..6, 7-наличие НАР в блоке
	unsigned char Ispr_BI_TP;		// Испр. БИ ТП (для 5,7 и 6,8 совпадают)

	unsigned char O_sv_IKAR_BI_Os;	// Отказ св. ИКАР-БИ ТП (для 5,7 и 6,8 совпадают)
	unsigned char O_sv_IKAR_BI_Rz;	
	unsigned char O_sv_BI_ASP_Os;	// Отказ св. БИ-АСП ТП
	unsigned char O_sv_BI_ASP_Rz;

	unsigned Dop_Priz_ASP;				// Доп. Признак АСП ТП1a,2a,3a,4a,5,6,7,8,9,10,11,12
	unsigned char Priz_T_ost_ASP_pit;	// Признак ТостАСПпит ТП1_2,3_4,9_10,11-12
	unsigned  T_res_ost_ASP_pit;		// Трес/остАСПпит ТП1_2,3_4,9_10,11-12

	unsigned char SG;				// СГ ТП - система готова (только для ТП 1, 3, 4, 11, 12)
	int Vrem_ohl;					// Время Охл. 72 ТП: мл.р. = 1мин. (только для ТП 3, 4, 5, 6, 7, 8)
	unsigned char OK;				// ОК - открытие клапана(только для ТП 3, 4, 5, 6, 7, 8, 11, 12)
	unsigned char Nal_pil;			// Нал. пилона ТП3 (только для ТП 3, 4, 5, 6, 11, 12)
	unsigned char BG;				// БГ ТП - батареи готовы (только для ТП 1, 3, 4, 11, 12)

	// формируется при вводе
	unsigned char O_sv_IKAR_BI;
	unsigned char O_sv_BI_ASP;
	unsigned  NLitRL;				// литер текущий

	TBRPI_OCU_72 OCU_72;			// // ОЦУ для 72
} TIKAR_BACK_TP;

// суммарные обратные энергетические сигналы
typedef struct TIKAR_BACK_SUM		
{
	// 50Гц
	unsigned char PR_sum;				// ПР cум.

	// 12.5, 50Гц
	unsigned char BK_fakt;				// БК факт (БК-РУС)
	unsigned char BK_v_VPU;				// БК в ВПУ
	unsigned char BK_podhv;				// БК подхв.
	unsigned char Nedop_zagr_MBD;		// Недоп. загр. МБД

	// 12,5Гц
	unsigned char Korp_ispyt;			// Корпус испытаний
	unsigned char ZBK_5s;				// ЗБК 5с(ПАР-35)
	unsigned char ZBK_3s;				// ЗБК 3с(ПАР-35)
	unsigned char Ohl_27T;				// Охл. 27Т (при подаче ОК изд. 27Т)
	unsigned char Ohl_72;				// Охл. 72 (при подаче ОК изд. 72)
	unsigned char DR_ruchn;				// ДР ручн.(ПАР-35)
	unsigned char Sbros_PTB;			// Сброс ПТБ
	unsigned char Pit_UR_VP;			// Пит. УР ВП
	unsigned char Avar_sbros_po_1;		// Авар. сброс по 1(ПАР-35)
	unsigned char AR;					// АР - автономный режим
	unsigned char PPS;					// ППС(ПАР-35)
	unsigned char Vozduh;				// Воздух(ПАР-35)
	unsigned char Vzr;					// Взр.(ПАР-35)
	unsigned char Avar_sbros;			// Авар. сброс(ПАР-35)
	unsigned char Avar_pusk;			// Авар. пуск(ПАР-35)
	unsigned char Zvuk_signal;			// Звук. Сигнал (кв.ИУС)

	unsigned char Glav;					// Главн
	unsigned char ShU;					// ШУ (ОСО)
	unsigned char TLM;					// ТЛМ

	unsigned char Im_ShU;				// Им ШУ
	unsigned char Ucheb_rab;			// Учеб. работа(ПНП-35)
	unsigned char Dozapr_35P;			// Дозаправка

	unsigned Razresh_TR;				// Разрешение ТР
	unsigned char Trenazh;				// Тренаж
	unsigned char AKO;					// АКО
	unsigned char Razr_AKO;				// Разр. АКО
	unsigned char N_kontrol;			// НК (кв.ИУС)

	unsigned char KTsU;					// КЦУ
	unsigned char Avt_sbros_otrab;		// Автосбр. отраб.    
	unsigned char Sum_PR_1;				// Сум. ПР 1
	unsigned char Sum_PR_2;				// Сум. ПР 2
	unsigned char MGN;					// МГН

	unsigned char AKO_V;				// АКО-В (кв.ИУС)
	unsigned char Visit_hot_1;			// Висит хотя бы 1
	unsigned char Imit_BR;				// Имит. БР
	unsigned char Zapret_BR_72;			// Запрет БР 72
	unsigned char DRnasp;				// ДРнасп (кв.ИУС)
	unsigned char VO;					// ВО - Выбор оружия

	unsigned char MGN_1;				// МГН-1
	unsigned char MGN_2;				// МГН-2
	unsigned char MGN_3;				// МГН-3
	unsigned char MGN_4;				// МГН-4
	unsigned char Perekl_35P_v_AR;		// Перекл. 35П в р-м АР
	unsigned char Ohl_vseh_72;			// Охл. всех 72 (кв.ИУС)
	unsigned char A1suo;				// А1суо (кв.ИУС)
	unsigned char A2suo;				// А2суо (кв.ИУС)

	unsigned Rashod_bk_VPU;				// Расход бк ВПУ (0..150, 50-НЗ)
	unsigned char Korot_ocher;			// Корот. очередь
	unsigned char Vybor_VPU;			// Выбор ВПУ (РУС - кн. "Выбор ВПУ" )
	
	unsigned char El_spusk;				// Эл. Спуск
	unsigned char Kompl_VPU;			// Компл. ВПУ
	unsigned char Pusk_v_SPP;			// Пуск в СПП

	unsigned char Kal_2_500;			// Калибр №2 500 (кв.ИУС)

	unsigned char Zad_3_min;			// Зад. 3 мин
	unsigned char Zad_5_min;			// Зад 5 мин

	unsigned Tek_kol_UR_na_TP;			// Текущее кол-во УР на ТП

	TSUO_REJ_ASP Rezh_rab_s_ASP;		// Режим раб.с АСП
	TSUO_SUMTYPE_ASP Sumtype_ASP;		// Обобщённый тип

	unsigned char Kal_2_50;				// Калибр №2 50 (кв.ИУС)
	unsigned char Kal_2_100;			// Калибр №2 100 (кв.ИУС)
	unsigned char Kal_2_250M62;			// Калибр №2 250М62 (кв.ИУС)
	unsigned char Kal_2_250M54;			// Калибр №2 250М54 (кв.ИУС)

	unsigned Tek_kol_AB_na_TP;			// Текущее кол-во АБ на ТП: 1..48
	unsigned char Avt_sbros;			// Авт сброс
	unsigned char Imp_sbrosa;			// Имп. сброса
	unsigned char Kal_50;				// Калибр 50
	unsigned char Kal_100;				// Калибр 100
	unsigned char Kal_250M62;			// Калибр 250М62
	unsigned char Kal_250M54;			// Калибр 250М54
	unsigned char Kal_500;				// Калибр 500

	unsigned char dva_tipa_AB;			// 2 типа АБСП (кв.ИУС)

	unsigned char Start_kontr;			// Стартовый контроль
	unsigned char Ispr_sv_IUS_35P;		// Испр. св. ИУС-35П
	unsigned char Ispr_IKAR_01;			// Испр. ИКАР-01
	unsigned char Ispr_35P;				// Испр. 35П
	unsigned char Ispr_BRPI_35P_l;		// Испр. БРПИ-35П лев
	unsigned char Ispr_BRPI_35P_p;		// Испр. БРПИ-35П прав

	unsigned char Ispr_35P_v_vyb;		// Испр. 35П в выб.

	unsigned char Ispr_MAR;				// Испр. МАР
	unsigned char Ispr_MAP;				// Испр. МАП

	unsigned char SPARKA_TP1;      		// Спарка ТП1
	unsigned char SPARKA_TP2;      		// Спарка ТП2
	unsigned char SPARKA_TP3;      		// Спарка ТП3
	unsigned char SPARKA_TP4;      		// Спарка ТП4

	TSUO_PR_ASP Priz_1_tipa_ASP;		// Признак 1-го выбранного типа АСП
	TSUO_VAR_PRIM Var_prim_1;			// Вариант применения 1
	unsigned char DBK;					// ДБК
	TSUO_RAZGRUZ Por_razgruz;			// Порядок разгрузки

	TSUO_PR_ASP Priz_2_tipa_ASP;		// Признак 2-го выбранного типа АСП
	TSUO_VAR_PRIM Var_prim_2;			// Вариант применения 2
	unsigned char Pr_ogr_PR;			// Пр. огр. ПР
	unsigned char IKAR_0_PUS_3aTP;		// 0 ПУС ТП3а	
	unsigned char IKAR_0_PUS_4aTP;		// 0 ПУС ТП4а	
	unsigned char IKAR_0_PUS_3bTP;		// 0 ПУС ТП3б	
	unsigned char IKAR_0_PUS_4bTP;		// 0 ПУС ТП4б	
	unsigned char IKAR_0_PUS_11TP;		// 0 ПУС ТП11	
	unsigned char IKAR_0_PUS_12TP;		// 0 ПУС ТП12	
	unsigned Var_Smen;					// Вариант смены
	unsigned char Ust;					// Юстировка	

	unsigned char UV_Activ;				/* Актив */
	unsigned char UV_Allowed_Disp;		/* Разрешение на отстрел */
	unsigned char UV_Auto;				/* Автомат */
	unsigned char UV_CritPPI;			/* Критическое количество ППИ */
	unsigned char UV_CritPPL;			/* Критическое количество ППЛ */
	unsigned char UV_CritPPR;			/* Критическое количество ППР */
	unsigned UV_Dispensing;				/* Идет отстрел */
	unsigned char UV_Dost_Record;		/* Достов-ть записи */
	unsigned char UV_Ispr;				/* Испр. УВ */
	unsigned UV_Kol_P_Type10;			/* Количество патронов типа 10 */
	unsigned UV_Kol_P_Type11;			/* Количество патронов типа 11 */
	unsigned UV_Kol_P_Type2;			/* Количество патронов типа 2 */
	unsigned UV_Kol_P_Type22;			/* Количество патронов типа 22 */
	unsigned UV_Kol_P_Type3;			/* Количество патронов типа 3 */
	unsigned UV_Kol_P_Type31;			/* Количество патронов типа 31 */
	unsigned UV_Kol_P_Type32;			/* Количество патронов типа 32 */
	unsigned UV_Kol_P_Type33;			/* Количество патронов типа 33 */
	unsigned UV_Kol_P_Type35;			/* Количество патронов типа 35 */
	unsigned UV_Kol_P_Type7;			/* Количество патронов типа 7 */
	unsigned UV_Kol_P_Type8;			/* Количество патронов типа 8 */
	unsigned UV_Mode;					/* Режим работы УВ */
	unsigned char UV_NK;				/* НК УВ */
	unsigned UV_N_Prog_Otstrela;		/* Номер программы отстрела */
	unsigned UV_N_Zap_Mas;				/* Номер записанного массива */
	unsigned char UV_Otk_Sv_BV_1_IKAR;	/* Отказ св. БВ1-ИКАР */
	unsigned char UV_Otk_Sv_BV_2_IKAR;	/* Отказ св. БВ2-ИКАР */
	unsigned char UV_Otk_Sv_BV_3_IKAR;	/* Отказ св. БВ3-ИКАР */
	unsigned char UV_Otk_Sv_BV_4_IKAR;	/* Отказ св. БВ4-ИКАР */
	unsigned char UV_Otk_Sv_BV_5_IKAR;	/* Отказ св. БВ5-ИКАР */
	unsigned char UV_Otk_Sv_BV_6_IKAR;	/* Отказ св. БВ6-ИКАР */
	unsigned UV_QuantityPPI;			/* Количество ППИ */
	unsigned UV_QuantityPPL;			/* Количество ППЛ */
	unsigned UV_QuantityPPR;			/* Количество ППР */
	unsigned char UV_RBR;				/* РБР */
	unsigned char UV_Ready_to_Record;	/* Готов к записи */
	unsigned char UV_Record;			/* Идет запись */
	unsigned char UV_Ruchnoi;			/* Ручной */
	unsigned char UV_Sbros_DO_LTC;		/* Сброс ДО/ЛТЦ */
	unsigned UV_Sost_P_BV[84];
} TIKAR_BACK_SUM;

// Массивы прямых энергетических сигналов (из БЦВМ в СУО) ----------------------

// ЦУ для 72
typedef struct TBRPI_CU_72
{
	TSUO_PR_ASP			Prizn_ASP_TP;			// Признак АСП на ТП
	unsigned char		Vybor_TP;				// Выбор ТП

	unsigned char		Znak_f1_72;				// Знак ф1
	double				f1_72;					// ф1 
	unsigned char		KTsU_72;				// КЦУ
	unsigned char		Hsr_72;					// Нср
	unsigned char		WorkGround;				// Работа по земле
	unsigned char		Otkl_PNTs_72;			// Откл. ПНЦ
	unsigned char		Znak_f2_72;				// Знак ф2
	double				f2_72;					// ф2
	unsigned char		M1_72;					// М1
	unsigned char		M2_72;					// М2
	unsigned char		TTs1_72;				// ТЦ1
	unsigned char		TTs2_72;				// ТЦ2
} TBRPI_CU_72;
/* Порядок разгрузки 72:
   - по 1: 5, 6, 3, 4, 7, 8 (в сл. не захвата/не готов
     или не сх. применяется следующ. с ЗГ по диаграмме)
   - по 2: 5->6, 3->4, 7->8  с интерв. 0.16с+-20% (в сл. не захвата/не готов
     или не сх. применяется следующ. с ЗГ по диаграмме, одновременно
	 с одного кр. запрещено, время несх. 2.4с+-0.1)
*/

// ЦУ для 470Т
typedef struct TBRPI_CU_470T
{
	TSUO_PR_ASP			Prizn_ASP_TP;		// Признак АСП на ТП
	unsigned char		Vybor_TP;			// Выбор ТП

	unsigned char		P1;					// Подг. 1 вида
	unsigned char		DR;					// ДР
	unsigned char		Ispr;				// Испр

	double				Fi1;				// ф1, радиан
	double				Fi2;				// ф2, радиан

	unsigned char		P2;					// Подг. 2 вида
	unsigned char		VSK;				// ВСК
	unsigned char		BD;					// Ближ. дистан.
	unsigned char		ZPS;				// ЗПС
	unsigned char		PPO;				// ППО

	unsigned char		CUR;				// ЦУР

	unsigned			Code_Hn;			// Код Hн
	unsigned			Code_Hc;			// Код Hц
	unsigned			Code_Hsr;			// Код Hsr

	double				D;					// Д

	unsigned			TC;					// Тип цели:0-ср., 1-мал.,2-больш.
	unsigned			Code_Alfa_n;		// Код Угла атаки
	double				M;					// Число Маха

	double				Omega1;				// Omega1, радиан/с
	double				Omega2;				// Omega2, радиан/с

	double				Dt;					// dД/dt, м/с
	double				Vn;					// Vн, м/с
} TBRPI_CU_470T;
/* Порядок разгрузки 470Т:
   - по 1: 3, 4, 11, 12 (в сл. не захвата/не готов или не сх. 
     с ТП3(ТП11) применяется с ТП4(ТП12))
   - по 2: 3->4, 11->12 с интерв. 0.4с (в сл. не захвата/не готов
     или не сх. применяется следующ. по диаграмме)
*/

// управление ТП
typedef struct TIKAR_CTRL_TP
{
	// 50Гц
	unsigned char DR;			// ДР
	unsigned char Podg;			// Подг.

	TBRPI_CU_72 BrpiCu72;		// ЦУ для 72 из БЦВМ в БРПИ лев./прав.

	// 12,5Гц
	TBRPI_CU_470T BrpiCu470T;	// ЦУ для 470Т из БЦВМ в БРПИ лев./прав.

	unsigned char Otkaz_ASP;	// Отказ АСП
	unsigned Imit_priz_ASP;		// Имитир. признак АСП
	unsigned char Otkl_pit;		// Откл. пит. ТП
} TIKAR_CTRL_TP;
/*
(***) Первое слово массива ПЦУ для изд. 470T1 (PZ_470T1[0]):
	4..10р.МКИО - Признак АСП
	11р.МКИО - Выбор
	19р.МКИО - Испр. БЦВМ ИУС
Остальные слова (PZ_470T1[1]..PZ_470T1[18]) формируются в соотв. с ПИВ БЦВМ-470 (секретн.)

БРПИ обрабатывает массив если:
(Признак АСП == код 470T1) && (Выбор == 1) && (Испр. БЦВМ ИУС == 1)
*/

// суммарные прямые энергетические сигналы
typedef struct TIKAR_CTRL_SUM		
{
	// 50Гц
	unsigned char PPS;					// ППС

	// 12,5Гц
	TSUO_VAR_PRIM Var_prim_1;		    // Вариант применения 1
	TSUO_TMBD tmbd;						// Тмбд
	unsigned char DBK;					// ДБК
	unsigned char Por_razgruz;			// Порядок разгрузки
	TSUO_VAR_PRIM Var_prim_2;			// Вариант применения 2
	
	char Zah_PRR_3TP;					// Захват ПРР 3ТП				
	char Zah_PRR_4TP;					// Захват ПРР 4ТП				
	char Zah_PRR_9TP;					// Захват ПРР 9ТП				
	char Zah_PRR_10TP;					// Захват ПРР 10ТП				
	char Zah_PRR_11TP;					// Захват ПРР 11ТП				
	char Zah_PRR_12TP;					// Захват ПРР 12ТП				
	unsigned n_1_vyb_TP_PRR;			// № 1-ой выбранной ТП для ПРР	
	unsigned n_2_vyb_TP_PRR;			// № 2-ой выбранной ТП для ПРР	
	unsigned n_3_vyb_TP_PRR;			// № 3-й выбранной ТП для ПРР	
	unsigned n_4_vyb_TP_PRR;			// № 4-ой выбранной ТП для ПРР	

	unsigned char Smen_GSN_1;			// Смена ГСН-1
	unsigned char Smen_GSN_2;			// Смена ГСН-2
	unsigned char Smen_GSN_3;			// Смена ГСН-3
	unsigned char Smen_GSN_4;			// Смена ГСН-4
	unsigned char Ohl_vseh_72;		    // Охл. всех 72Э (от МФПИ)

	unsigned char Kal_2_50;				// Калибр №2 50
	unsigned char Kal_2_100;			// Калибр №2 100
	unsigned char Kal_2_250M62;		    // Калибр №2 250М62
	unsigned char Kal_2_250M54;		    // Калибр №2 250М54
	unsigned char Kal_2_500;			// Калибр №2 500

	/*
	unsigned char Otkl_pit_1_2TP;		// Откл. пит. 1,2 ТП
	unsigned char Otkl_pit_3_4TP;		// Откл. пит. 3,4 ТП
	unsigned char Otkl_pit_9_10TP;		// Откл. пит. 9,10ТП
	unsigned char Otkl_pit_11_12TP;		// Откл. пит. 11,12ТП
	*/

	unsigned char A1suo;				// А1суо
	unsigned char A2suo;				// А2суо
	unsigned char MGN_1;				// МГН-1
	unsigned char MGN_2;				// МГН-2
	unsigned char MGN_3;				// МГН-3
	unsigned char MGN_4;				// МГН-4
	unsigned char Ut_tip_KAB;			// Уточн. типа КАБ
	unsigned char ResTv_KAB4;			// РесТв КАБ4
	unsigned char BezSG_TvKAB;			// Без СГ ТвКАБ
	unsigned char Zapr_Izm_Och1;		// ЗапрИзм Очер1
	unsigned char Zapr_Izm_Och2;		// ЗапрИзм Очер2
	unsigned char KOEP_35;				// КОЭП-35
	unsigned char Kal_50;				// Калибр 50
	unsigned char Kal_100;				// Калибр100
	unsigned char Kal_250M62;			// Калибр 250М62
	unsigned char Kal_250M54;			// Калибр 250М54
	unsigned char Kal_500;				// Калибр 500

	unsigned char dva_tipa_AB;			// 2 типа АБСП

	unsigned char Otkaz_ASP_2bTP;	// Отказ АСП 2б ТП	
	unsigned char Otkaz_ASP_1bTP;	// Отказ АСП 1б ТП	
	unsigned char Otkaz_ASP_2aTP;	// Отказ АСП 2а ТП	
	unsigned char Otkaz_ASP_1aTP;	// Отказ АСП 1а ТП	
	unsigned char Otkaz_ASP_10TP;	// Отказ АСП 10 ТП	
	unsigned char Otkaz_ASP_9TP;	// Отказ АСП 9 ТП	
	unsigned char Otkaz_ASP_12TP;	// Отказ АСП 12 ТП	
	unsigned char Otkaz_ASP_11TP;	// Отказ АСП 11 ТП	
	unsigned char Otkaz_ASP_4aTP;	// Отказ АСП 4а ТП	
	unsigned char Otkaz_ASP_3aTP;	// Отказ АСП 3а ТП	
	unsigned char Otkaz_ASP_6TP;	// Отказ АСП 6 ТП	
	unsigned char Otkaz_ASP_5TP;	// Отказ АСП 5 ТП	
	unsigned char Otkaz_ASP_8TP;	// Отказ АСП 8 ТП	
	unsigned char Otkaz_ASP_7TP;	// Отказ АСП 7 ТП	

	unsigned char MGN;					// МГН
	unsigned char ZS;					// ЗС
	unsigned char NOP_SUO;				// НОП

	unsigned char Vnesh_podsv;			// Внеш. подсвет
	unsigned char Strob_ot_KOEP;		// Строб от КОЭП
	unsigned char AKO;					// АКО
	unsigned char NK;					// НК
	unsigned char Nach_TRN;				// Начать ТРН
	unsigned char Trenazh;				// Тренаж
	unsigned char Ispr_BTsVM_IUS_72;	// Испр. БЦВМ ИУС в ИКАР и БРПИ
	unsigned Ish_kompl_VPU;				// Исходный комплект ВПУ: 0..150 (ИУП)
	unsigned char Kompl_VPU;			// Компл. ВПУ (ИУП)
	unsigned char Korot_ocher;			// Корот. очередь (ИУП)
	unsigned char Pr_ogr_PR;			// Пр. огр. ПР
	unsigned char Uch_rab_VPU;			// Учеб. раб. ВПУ

	/*
	1. с ПРР надо разобраться
	2. AKO_V выдается ГУП
	*/
	unsigned char AvtoSbros;          // Авт. Сброс
	unsigned char Impuls_Sbr;         // импульс сброса
	unsigned char DRnasp;			  // ДРнасп
	unsigned char PRR_2_po_2_ts;	  // ПРР по 2 по 2 ц
	unsigned N_1_Vbr_TP_PRR;          // номер 1-ой выбранной ТР для ПРР
	unsigned N_2_Vbr_TP_PRR;          // номер 2-ой выбранной ТР для ПРР
	unsigned N_3_Vbr_TP_PRR;          // номер 3-й выбранной ТР для ПРР
	unsigned N_4_Vbr_TP_PRR;          // номер 4-ой выбранной ТР для ПРР
	unsigned char AKO_V;              // АКО-В

	unsigned Var_Smen;				// Вариант смены
	unsigned char NK_UV;			// НК УВ
	unsigned N_Prog_OtstrelaPP_BG;	// Номер программы отстрела ПП в "Ручном" режиме от гш. "БГ"			
	unsigned N_Prog_OtstrelaPP_LTC;	// Номер программы отстрела ПП в "Ручном" режиме от кн. "СБРОС ДО ЛТЦ"		
	unsigned char KPRNO_Ust_IKAR;	// Юстировка			

	unsigned char Rab_s_OU_ASP[16];	// Работа с ОУ АСП ххх ТП
} TIKAR_CTRL_SUM;

// состояние СУО
typedef struct TSUO_STAT		
{
	IO_STATE ios_tx1;
	IO_STATE ios_tx2;
	IO_STATE ios_tx3;

	char bConnect;		// "обмен был"
	char bErr;			// интегральный признак неисправности
	int ErrCode;		// код неисправности
	char bErrExt;		// отказ по расширенному отказу

	unsigned nErrIO;	// счетчик ошибок обмена
	char bErrIO;		// признак неисправности обмена
	
	double T_powerOn;	// время ожидания включения питания 
	double T_full;		// общее время
	
	unsigned nErrSS;	// счетчик ошибок по СС
	unsigned bErrSS;	// ошибка по СС

	char bErrTest;		// отказ тестовых значений

	char bTest_Suo35p;
	char bTest_Suo35p_prev;
} TSUO_STAT;

EXTERN_SUO TSUO_STAT SuoStat;				// состояние СУО
EXTERN_SUO TIKAR_BACK_SUM IkarBackSum;		// суммарные обратные энергетические сигналы
EXTERN_SUO TIKAR_BACK_TP IkarBackTp[16];	// обратные энергетические сигналы, состояние ТП
EXTERN_SUO TIKAR_CTRL_SUM IkarCtrlSum;		// суммарные прямые энергетические сигналы
EXTERN_SUO TIKAR_CTRL_TP IkarCtrlTp[16];	// управление ТП

#endif	//TYPES_SUO_H
