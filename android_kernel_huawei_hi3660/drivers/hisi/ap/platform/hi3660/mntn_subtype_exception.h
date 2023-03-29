#ifndef __MNTN_SUBTYPE_EXCEPTION_H__
#define __MNTN_SUBTYPE_EXCEPTION_H__ 
#include "soc_acpu_baseaddr_interface.h"
#include "pmic_interface.h"
#include "global_ddr_map.h"
#define PMU_EXCSUBTYPE_REG_OFFSET (PMIC_HRST_REG2_ADDR(0))
enum mmc_exception_subtype
{
 MMC_EXCEPT_INIT_FAIL = 0x0,
 MMC_EXCEPT_CMD_TIMEOUT,
 MMC_EXCEPT_COLDBOOT,
};
enum appanic_subtype
{
 HI_APPANIC_RESERVED = 0x0,
 HI_APPANIC_BC_PANIC = 0x1,
 HI_APPANIC_L3CACHE_ECC = 0x2,
 HI_APPANIC_SOFTLOCKUP = 0x3,
 HI_APPANIC_OHARDLOCKUP = 0x4,
 HI_APPANIC_HARDLOCKUP = 0x5,
};
enum apbl31panic_subtype
{
 HI_APBL31PANIC_RESERVED = 0x0,
 HI_APBL31PANIC_ASSERT = 0x1,
};
enum apvndpanic_subtype
{
 HI_APVNDPANIC_RESERVED = 0x0,
 HI_APVNDPANIC_CFI = 0x1,
};
enum apwdt_subtype
{
 HI_APWDT_HW = 0x0,
 HI_APWDT_LPM3 = 0x1,
 HI_APWDT_BL31 = 0x2,
 HI_APWDT_BL31LPM3 = 0x3,
 HI_APWDT_AP = 0x4,
 HI_APWDT_BL31AP = 0x6,
 HI_APWDT_APBL31LPM3 = 0x7,
};
enum lpm3_subtype
{
 PSCI_RESERVED = 0x0,
 PSCI_AP_WDT_LOCAL,
 PSCI_AP_WDT_REMOTE,
 PSCI_M3_WDT_LOCAL,
 PSCI_M3_WDT_REMOTE,
 PSCI_REASON_WDT_END,
 PSCI_AP_SYS_PANIC = PSCI_REASON_WDT_END,
 PSCI_M3_SYS_PANIC,
 PSCI_PMUSSI_PANIC,
 PSCI_CLK_ERR,
 PSCI_REGULATOR_ERR,
 PSCI_OCBC_ERR,
 PSCI_DMA_ERR,
 PSCI_NOC_TIMEOUT,
 PSCI_G3D_PWR_ERR,
 PSCI_CPU_PWR_ERR,
 PSCI_TSENSOR_ERR,
 PSCI_CPUDVFS_ERR,
 PSCI_GPUDVFS_ERR,
 PSCI_MEMRP_ERR,
 PSCI_NOC_BUS_IDLE_PEND,
 PSCI_AHB_TIMEOUT,
 PSCI_REASON_SYS_EXC_END = 0x1f,
 PSCI_REASON_DDR_UNAVAILABLE_BEGIN = 0x20,
 PSCI_DDR_PANIC = PSCI_REASON_DDR_UNAVAILABLE_BEGIN,
 PSCI_DDR_FATAL_ERR,
 PSCI_DDR_SREF_ERR,
 PSCI_DDR_OSC_ERR,
 PSCI_DDR_TMON_LOW,
 PSCI_DDR_TMON_HIGH,
 PSCI_DDR_GATE_ERR,
 PSCI_UCE0_EXC,
 PSCI_UCE1_EXC,
 PSCI_UCE2_EXC,
 PSCI_UCE3_EXC,
 PSCI_DDR_AREF_ALARM,
 PSCI_DDR_RDTIMEOUT,
 PSCI_DDR_PLLUNLOCK_ERR,
 PSCI_DDR_RETRAIN_ERR,
 PSCI_DDR_TMON_ERR,
 PSCI_DDR_DFS_ERR,
 PSCI_DDR_DVALID_ERR,
 PSCI_DDR_DFI_SEL_ERR,
 PSCI_DDR_PLLUNLOCK_LP,
 PSCI_DDR_UNKNOWN_ERR,
 PSCI_UCE_EXC,
 PSCI_REASON_DDR_PANIC_END = 0x5f,
 PSCI_DMA_TIMEOUT = 0x60,
 PSCI_SUBPMU0_PANIC,
 PSCI_SUBPMU1_PANIC,
 PSCI_REASON_DDR_UNAVAILABLE_END = 0x9f,
 PSCI_REASON_OTHERIP_REQ_BEGIN = 0xa0,
 PSCI_OTHERIP_REQ_MODEM,
 PSCI_OTHERIP_REQ_HIFI,
 PSCI_OTHERIP_REQ_IOMCU,
 PSCI_REASON_OTHERIP_REQ_END = 0xaf,
 PSCI_REASON_MAX,
 PSCI_REASON_UNKNOWN = 0xff,
};
enum scharger_subtype{
 PMU_VSYS_OV = 0x1,
 PMU_VSYS_PWROFF_ABS = 0x2,
 PMU_VSYS_PWROFF_DEB = 0x4,
};
enum pmu_subtype
{
 OCP_LDO2 = 0x01,
 OCP_LDO1,
 OCP_LDO0_2,
 OCP_BUCK4,
 OCP_BUCK3,
 OCP_BUCK2,
 OCP_BUCK1,
 OCP_BUCK0,
 OCP_LDO10,
 OCP_LDO8,
 OCP_LDO7,
 OCP_LDO5,
 OCP_LDO4,
 OCP_LDO3,
 OCP_LDO20,
 OCP_LDO19,
 OCP_LDO17,
 OCP_LDO15,
 OCP_LDO14,
 OCP_LDO13,
 OCP_LDO28,
 OCP_LDO27,
 OCP_LDO26,
 OCP_LDO25,
 OCP_LDO24,
 OCP_LDO23,
 OCP_LDO22,
 OCP_LDO21,
 OCP_CLASSD,
 OCP_LDO32,
 OCP_LDO31,
 OCP_LDO30,
 OCP_LDO29,
 SCP_BUCK4,
 SCP_BUCK3,
 SCP_BUCK2,
 SCP_BUCK1,
 SCP_BUCK0,
 SYS_NRST_1S,
};
enum conn_subtype
{
    CONN_WIFI_EXEC = 0,
    CONN_WIFI_CHAN_EXEC,
    CONN_WIFI_WAKEUP_FAIL,
    CONN_BFGX_EXEC,
    CONN_BFGX_BEAT_TIMEOUT,
    CONN_BFGX_WAKEUP_FAIL,
};
enum hisee_subtype
{
 EXC_SENSOR_CTRL = 0,
 EXC_SIC,
 EXC_MED_ROM,
 EXC_MED_RAM,
 EXC_OTPC,
 EXC_HARD,
 EXC_IPC_MAILBOX,
 EXC_MPU,
 EXC_BUS,
 EXC_TIMER,
 EXC_SEC_EXTERN,
 EXC_WDG,
 EXC_SYSALARM,
 EXC_NV_COUNTER,
 EXC_SWP,
 EXC_COS,
 EXC_BB,
 EXC_MNTN_COS,
 EXC_MNTN_COS_RESET,
 EXC_LIBC,
 EXC_NVM,
 EXC_SECENG_TRNG,
 EXC_SECENG_TRIM,
 EXC_SECENG_SCE,
 EXC_SECENG_RSA,
 EXC_SECENG_SM2,
 EXC_SECENG_KM,
 EXC_SECENG_SCRAMBLING,
 EXC_BOTTOM,
 SIMULATE_EXC_RPMB_KO,
 SIMULATE_EXC_PD_SWIPE,
 EXC_ALARM0,
 EXC_ALARM1,
 EXC_AS2AP_IRQ,
 EXC_DS2AP_IRQ,
 EXC_SENC2AP_IRQ,
 EXC_SENC2AP_IRQ0,
 EXC_SENC2AP_IRQ1,
 EXC_LOCKUP,
 EXC_EH2H_SLV,
 EXC_TSENSOR1,
 EXC_UNKNOWN,
};
typedef enum {
 RDR_REG_BACKUP_IDEX_0 = 0,
 RDR_REG_BACKUP_IDEX_1,
 RDR_REG_BACKUP_IDEX_2,
 RDR_REG_BACKUP_IDEX_3,
 RDR_REG_BACKUP_IDEX_MAX
} RDR_REG_BACKUP_IDEX;
typedef enum {
 CATEGORY_START = 0x0,
 NORMALBOOT,
 PANIC,
 HWWATCHDOG,
 LPM3EXCEPTION,
 BOOTLOADER_CRASH,
 TRUSTZONE_REBOOTSYS,
 MODEM_REBOOTSYS,
 BOOTFAIL,
 HARDWARE_FAULT,
 MODEMCRASH,
 HIFICRASH,
 SENSORHUBCRASH,
 ISPCRASH,
 IVPCRASH,
 TRUSTZONECRASH,
 HISEECRASH,
 UNKNOWNS,
 PRESS10S,
 PRESS6S,
 NPUEXCEPTION,
 CONNEXCEPTION,
 SUBTYPE = 0xff,
}CATEGORY_SOURCE;
struct exp_subtype {
 unsigned int exception;
 unsigned char category_name[24];
 unsigned char subtype_name[24];
 unsigned int subtype_num;
};
typedef struct exc_special_backup_data {
 unsigned char reset_reason[RDR_REG_BACKUP_IDEX_MAX];
 unsigned int slice;
 unsigned int rtc;
 unsigned int REG_Reg13;
 unsigned int REG_LR1;
 unsigned int REG_PC;
 unsigned int REG_XPSR;
 unsigned int NVIC_CFSR;
 unsigned int NVIC_HFSR;
 unsigned int NVIC_BFAR;
 unsigned char exc_trace;
 unsigned char ddr_exc;
 unsigned short irq_id;
 unsigned int task_id;
} EXC_SPECIAL_BACKUP_DATA_STRU;
typedef struct rdr_reg_backup_head {
 unsigned int idex;
 unsigned int reason[RDR_REG_BACKUP_IDEX_MAX - 1];
} RDR_REG_BACKUP_HEAD_STRU;
typedef struct rdr_reg_backup_data {
 unsigned int Reg0;
 unsigned int Reg1;
 unsigned int Reg2;
 unsigned int Reg3;
 unsigned int Reg4;
 unsigned int Reg5;
 unsigned int Reg6;
 unsigned int Reg7;
 unsigned int Reg8;
 unsigned int Reg9;
 unsigned int Reg10;
 unsigned int Reg11;
 unsigned int Reg12;
 unsigned int Reg13;
 unsigned int MSP;
 unsigned int PSP;
 unsigned int LR0_CONTROL;
 unsigned int LR1;
 unsigned int PC;
 unsigned int XPSR;
 unsigned int PRIMASK;
 unsigned int BASEPRI;
 unsigned int FAULTMASK;
 unsigned int CONTROL;
} RDR_REG_BACKUP_DATA_STRU;
#endif
