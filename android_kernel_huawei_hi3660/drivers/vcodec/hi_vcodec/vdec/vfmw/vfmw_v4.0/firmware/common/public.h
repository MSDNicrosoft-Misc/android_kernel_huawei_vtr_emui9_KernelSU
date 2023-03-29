/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhEDlG50G/Vcvyq2txYFjqt/X5GLe/SnYbE4r/A06
+TaRl5lB3SEwfHkLGFw8eexRQh7/B/dgSgI8INThiyYKg+hZ04gu5VZxVbhWf2kaj0i7cXDV
Nv0DVJKNzjCoYhavLSDl24fCwqYgiOgWzxpZ/6lwJDnTKsRY4a5PQylkmHJMtw==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************
*
* Copyright (c) 2006 HUAWEI - All Rights Reserved
*
* File: $public.h$
* Date: $2006/11/30$
* Revision: $v1.0$
* Purpose: header file for interface & interface & storage management 
*          module. this file only define internal information. the 
*          interface related data is defined in 'vfmw.h'
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ====== 
* 2006/11/30       z56361            Original
*
*
* Dependencies:
*
************************************************************************/
#ifndef __PUBLIC_H__
#define __PUBLIC_H__


#include "basedef.h"
#include "sysconfig.h"
#include "vfmw.h"
#include "scd_drv.h"
#include "vdm_hal.h"


/***********************************************************************
      constants 
 ***********************************************************************/
#define  SCD_SEG_BLANK_LEN      (128*1024)
#define  MIN_BOTTOM_SEG_LEN     (1*1024) //SCD_SEG_BLANK_LEN  //128K太大了吧，这么多码流拷贝一旦发生会耗时很长，给互斥实现带来麻烦
#define  SCD_AVS_SEG_BLANK_LEN  (1024*1024)
#define  MIN_BOTTOM_AVS_SEG_LEN (1023*1024)
#define  SM_MAX_SEG_BUF_SIZE    (2*1024*1024)
#define  SM_MIN_SEG_BUF_SIZE    (256*1024)

#define  VFMW_TRUE              (0)
#define  VFMW_FALSE             (1)

// debug message print control
#define  DEFAULT_PRINT_ENABLE   (0x0)          // 默认 关闭
#define  DEFAULT_PRINT_DEVICE   (DEV_SCREEN)   // 默认 'DEV_SCREEN'，即打印到屏幕

#define  MAX_USERDATA_NUM       (4)            // 最多支持4个，需保持与IMAGE结构体对应

/***********************************************************************
      enum  
 ***********************************************************************/
typedef enum
{
    DEV_SCREEN = 1,
    DEV_SYSLOG,
    DEV_FILE,
    DEV_MEM
} PRINT_DEVICE_TYPE;

typedef enum
{
    PRN_FATAL = 0,       // 0.  致命异常（fatal error），比如未知异常
    PRN_ERROR,           // 1.  一般异常（error），比如语法错误
    PRN_CTRL,            // 2.  控制信息, 比如状态灯，内部状态机跳转信息等
    PRN_VDMREG,          // 3.  VDM寄存器，包括控制寄存器、状态寄存器

    PRN_DNMSG,           // 4.  解码下行消息，各消息字的值打印
    PRN_RPMSG,           // 5.  修补消息，修补消息各个消息字
    PRN_UPMSG,           // 6.  上行消息，上行消息各个消息字
    PRN_STREAM,          // 7.  码流信息，如每个码流包的信息（地址，长度等）

    PRN_STR_HEAD,        // 8.  码流头字节，（前8字节，用于查找比对）
    PRN_STR_TAIL,        // 9.  码流尾字节，（后8字节，用于查找比对）
    PRN_STR_BODY,        // 10. 码流中部字节，（前后8字节之外的码流）
    PRN_IMAGE,           // 11. 解码图像信息（图像的id，地址，属性等）

    PRN_QUEUE,           // 12. 解码图队列信息（队列的图像个数，位置等）
    PRN_REF,             // 13. 参考图信息（H264打印LIST相关信息，MPEG打印参考图及其维护的信息）
    PRN_DPB,             // 14. DPB类信息（与dpb相关的各种信息）
    PRN_POC,             // 15. POC类信息（POC的解码和计算）

    PRN_MARK_MMCO,       // 16. MARK & MMCO操作信息（MARK和MMCO操作的信息，可表现执行的过程）
    PRN_SEQ,             // 17. 序列级重要语法信息，H264打印SPS，MPEG2打印sequence信息，MPEG4打印VOL及以上层信息
    PRN_PIC,             // 18. 图像级重要语法信息，H264打印PPS，MPEG2打印picture，MPEG4打印VOP/SHVOP头
    PRN_SLICE,           // 19. Slice级重要语法信息

    PRN_SEI,             // 20. SEI信息
    PRN_SE,              // 21. 语法信息
    PRN_DBG,             // 22. 调试信息
    PRN_BLOCK,           // 23. 解码线程阻塞信息

    PRN_SCD_REGMSG,      // 24. SCD寄存器及消息池信息
    PRN_SCD_STREAM,      // 25. SCD码流信息
    PRN_SCD_INFO,        // 26. 打印SCD一些运行状态的信息
    PRN_CRC,             // 27. CRC计算值
    
	PRN_POST,            // 28. 打印后级及其驱动程序相关信息
	PRN_PTS,             // 29. 打印与PTS处理相关的信息
    PRN_DEC_MODE,        // 30. 解码模式切换信息
    PRN_FS,              // 31. 动态帧存打印
	
    PRN_ALWS = 32        // 32. 不受控打印
} PRINT_MSG_TYPE;

/* state type */
typedef enum
{
    STATE_RCV_RAW = 0,           //接收RAW码流
    STATE_SCD_START,             //启动SCD
    STATE_SCD_INTERRUPT,         //SCD中断

    STATE_DECSYNTAX_SEG,         //语法解析SEG码流
    STATE_GENERATE_DECPARAM,     //生成解码参数

    STATE_VDH_START,             //启动VDH
    STATE_VDH_INTERRUPT,         //VDH中断
    STATE_VDH_REPAIR,            //VDH修补
    STATE_1D_TO_QUEUE,           //1D图像输出到队列

    STATE_2D_TO_QUEUE,           //2D图像输出到队列

    STATE_VO_RCV_IMG,            //VO读取图像
    STATE_VO_REL_IMG             //VO释放图像
} VFMW_STATE_TYPE_E;

/***********************************************************************
      structures    
 ***********************************************************************/

/* MPEG2, MPEG4 and DIVX311 dedode interface need code stream info from control module.
   Struct 'STREAM_PARAM' defines the stream info format. */
typedef struct
{
    UINT8*    VirAddr;    // 码流的虚拟地址
    UADDR     PhyAddr;    // 码流的物理地址
    SINT32    Length;     // 码流长度（字节数）
} STREAM_PARAM;

/* 内存打印数据结构  */
typedef struct 
{      
    SINT8*    buf_addr;
    SINT8*    cur_addr_offset;
    UINT32    buf_len;
    UINT32    total_msg_num;
} MEMPRINT;

/* MPEG2/4的码流暂存缓冲 */
typedef struct
{
	UINT8*    buf_vir_addr;
	SINT8     filled_new_data_flag;
    UADDR     buf_phy_addr;
	SINT32    buf_size;
	SINT32    length;
} STRM_LOCAL_BUF;

/* VDM 驱动的信息汇总 */
typedef struct
{
	SINT32    DecTaskState;
} VDMCMN_DECTASK_INFO_S;

/* 低延迟各模块时间统计信息 */
typedef struct
{
    SINT32    lowdly_enable;             /* 低延迟使能标志 */
    SINT32    chan_id;                   /* 通道 ID */
	SINT32    receive_raw;               /* 记录收到 RAW 包时间 */
	SINT32    scd_start;                 /* SCD 启动时间 */
	SINT32    scd_return;                /* SCD 中断返回 */
	SINT32    scd_count;                 /* SCD 工作一次所消耗的时间 */
	SINT32    vdh_start;                 /* VDH 启动时间 */
	SINT32    vdh_return;                /* VDH 中断返回 */
	SINT32    vdh_count;                 /* VDH 工作一次所消耗的时间 */
	SINT32    vo_read_img;               /* VO 成功读走图像的时间 */
	SINT32    raw_to_scd_return;         /* 从VFMW收到码流到解出一帧图像的时间, 只有按帧送码流时才较为准确 */
	SINT32    raw_to_img;                /* 从VFMW收到码流到解出一帧图像的时间, 只有按帧送码流时才较为准确 */
	SINT32    raw_to_vo;                 /* 从VFMW收到码流到解出一帧图像的时间，只有按帧送码流时才较为准确 */
	SINT32    OneTimeFlag;
}LOWDLY_INFO_S;

/***********************************************************************
      global vars   
 ***********************************************************************/
extern  UINT32                 g_PrintEnable;
extern  UINT32                 g_PrintDevice;
extern  SINT32                 g_TraceCtrl;
extern  SINT32                 g_TraceBsPeriod;
extern  SINT32                 g_TraceFramePeriod;
extern  SINT32                 g_TraceImgPeriod;
extern  LOWDLY_INFO_S          g_stLowdlyInfo[MAX_CHAN_NUM];
extern  EXT_FN_EVENT_CALLBACK  g_event_report;

// register address offset from register base address
#define    REG_VDM_STATE                  (0x01C>>2)    // VDM_STATE
#define    REG_INTERPRT_CLEAN             (0X020>>2)    // INT
#define    REG_INTERPRT_MASK              (0x024>>2)    // INT_MASK

// map first. take care!!!!

// debug related state definition
#define    DSTATE_WAIT_STREAM             (1<<1)
#define    DSTATE_WAIT_VDMFINISH          (1<<2)
#define    DSTATE_WAIT_FRAMESTORE         (1<<3)
#define    DSTATE_WAIT_VDMPROPERTY        (1<<4)

/***********************************************************************
      macro 
 ***********************************************************************/
//注意:有很多函数前面对空指针的判断就可以去掉了
//add for check null point parament
#define CHECK_NULL_PTR_ReturnValue(parPoint,ReturnValue)                        \
    do                                                  \
    {                                                   \
        if (NULL == parPoint)                           \
        {                                               \
            dprint(PRN_FATAL, "NULL pointer: %s, L%d\n", __FILE__, __LINE__);   \
            return ReturnValue;                         \
        }                                               \
    }while(0)

#define CHECK_NULL_PTR_Return(parPoint)                 \
    do                                                  \
    {                                                   \
        if (NULL == parPoint)                           \
        {                                               \
            dprint(PRN_FATAL,"NULL pointer: %s, L%d\n", __FILE__, __LINE__);    \
            return;                 \
        }                                               \
    }while(0)
//end

/*********************** 发送消息的宏封装 *************************/

/* type=1	图像的显示区域发生了变化 */
#define REPORT_DISP_AREA_CHANGE(chan_id,w,h,center_x,center_y)                  \
do{                                                         \
    if( NULL != g_event_report )                            \
    {                                                       \
        UINT16  para[4];                                    \
        para[0] = (UINT16)(w);                              \
        para[1] = (UINT16)(h);                              \
        para[2] = (UINT16)(center_x);                       \
        para[3] = (UINT16)(center_y);                       \
        g_event_report( chan_id, EVNT_DISP_EREA, (UINT8*)para, sizeof(para));   \
    }                                                       \
}while(0)

/* type=2, 图像宽高发生了变化 */
#define REPORT_IMGSIZE_CHANGE( chan_id, oldw, oldh, neww, newh )	            \
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT16  para[4];                                    \
        para[0] = (UINT16)(oldw);                        	\
        para[1] = (UINT16)(oldh);                          	\
        para[2] = (UINT16)(neww);                          	\
        para[3] = (UINT16)(newh);                          	\
        g_event_report( chan_id, EVNT_IMG_SIZE_CHANGE, (UINT8*)para, sizeof(para)); \
    }                                                       \
}while(0)

/* type=3, 帧率发生了变化 */
#define REPORT_FRMRATE_CHANGE( chan_id, newfr )    		    \
do{                                                      	\
    if( NULL != g_event_report )                 		    \
    {                                                       \
        UINT32  para[1];                                    \
        para[0] = (UINT32)(newfr);                         	\
        g_event_report( chan_id, EVNT_FRMRATE_CHANGE, (UINT8*)para, sizeof(para)); \
    }                                                       \
}while(0)

/* type=4, 图像的逐行/隔行信息变化，无参数 */
#define REPORT_SCAN_CHANGE( chan_id, newscan ) 			    \
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[1];                                    \
        para[0] = (UINT8)(newscan);                 		\
        g_event_report( chan_id, EVNT_SCAN_CHANGE, (UINT32*)para, sizeof(para));\
    }                                                       \
}while(0)

/* type=5, 有一帧图像进入队列 */
#define REPORT_IMGRDY( chan_id )            		        \
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        g_event_report( chan_id, EVNT_NEW_IMAGE, (UINT8*)0, 0);                 \
    }                                                       \
}while(0)

/* type=6, 发现了user data */
#define REPORT_USRDAT( chan_id, p_usrdat )              	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        g_event_report( chan_id, EVNT_USRDAT, (VDEC_USRDAT_S*)p_usrdat, sizeof(VDEC_USRDAT_S));	 \
    }                                                       \
}while(0)

/* type=7  发现宽高比发生变化 */
#define REPORT_ASPR_CHANGE( chan_id, oldasp, newasp )  	    \
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[2];                                    \
        para[0] = (UINT8)(oldasp);                        	\
        para[1] = (UINT8)(newasp);                       	\
        g_event_report( chan_id, EVNT_ASPR_CHANGE, (UINT32*)para, sizeof(para));\
    }                                                       \
}while(0)

/* type=8  即将输出一个尺寸与之前不同的帧 */
#define REPORT_OUTPUT_IMG_SIZE_CHANGE( chan_id, oldw, oldh, neww, newh )	    \
    do{                                                     \
        if( NULL != g_event_report )                        \
        {                                                   \
            UINT16  para[4];                                \
            para[0] = (UINT16)(oldw);                       \
            para[1] = (UINT16)(oldh);                       \
            para[2] = (UINT16)(neww);                       \
            para[3] = (UINT16)(newh);                       \
            g_event_report( chan_id, EVNT_OUTPUT_IMG_SIZE_CHANGE, (UINT8*)para, sizeof(para)); \
        }                                                   \
    }while(0)


/* type=20  发现一个I帧，准备解码此I帧 */
#define REPORT_FIND_IFRAME( chan_id, stream_size )          \
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[1];                                    \
        para[0] = stream_size;                              \
        g_event_report( chan_id, EVNT_FIND_IFRAME, (UINT8*)para, sizeof(para)); \
    }                                                       \
}while(0)

/*--------------------------------------------------------------*/
/* type=100 发现码流错误 p_args[3..0]：错误编号*/
#define REPORT_STRMERR(chan_id, err_code )          		\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[1];                                    \
        para[0] = (UINT32)(err_code);                     	\
        g_event_report( chan_id, EVNT_STREAM_ERR, (UINT8*)para, sizeof(para));	\
    }                                                       \
}while(0)

/* type=101 VDM不响应 */
#define REPORT_VDMERR(chan_id)                           	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        g_event_report( chan_id, EVNT_VDM_ERR, (UINT8*)0, 0); 	                \
    }                                                       \
}while(0)

/* type=102 发现不支持的规格 无 */
#define REPORT_UNSUPPORT(chan_id)                       	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        g_event_report( chan_id, EVNT_UNSUPPORT, (UINT8*)0, 0);  	            \
    }                                                       \
}while(0)

/* type=103	码流的语法错误	无 */
#define REPORT_SE_ERR(chan_id)                           	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        g_event_report( chan_id, EVNT_SE_ERR, (UINT8*)0, 0); 		            \
    }                                                       \
}while(0)

/* type=104  图像错误率超过ref_error_thr	无 */
#define REPORT_OVER_REFTHR(chan_id, CurrRate, RefRate)      \
do{ 														\
	if( NULL != g_event_report )							\
	{														\
		UINT32	para[2];									\
		para[0] = (UINT32)(CurrRate);						\
		para[1] = (UINT32)(RefRate);					    \
		g_event_report( chan_id, EVNT_OVER_REFTHR, (UINT8*)para, sizeof(para)); \
	}														\
}while(0)

/* type=105  图像错误率超过out_error_thr	无 */
#define REPORT_OVER_OUTTHR(chan_id)                     	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        g_event_report( chan_id, EVNT_OVER_OUTTHR, (UINT8*)0, 0);               \
    }                                                       \
}while(0)

/* type=106  参考帧个数超过了设定值 p_args[3..0]：参考帧个数， p_args[7..4]：设定值 */
#define REPORT_REF_NUM_OVER(chan_id, RefNum, MaxRefNum)    	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[2];                                    \
        para[0] = RefNum;                                   \
        para[1] = MaxRefNum;                                \
        g_event_report( chan_id, EVNT_REF_NUM_OVER, (UINT8*)para, sizeof(para));\
    }                                                       \
}while(0)

/* type=107, 图像宽高超过阈值 */
#define REPORT_IMGSIZE_OVER( chan_id, w, h, maxw, maxh )	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT16  para[4];                                    \
        para[0] = (UINT16)(w);                        	    \
        para[1] = (UINT16)(h);                          	\
        para[2] = (UINT16)(maxw);                          	\
        para[3] = (UINT16)(maxh);                          	\
        g_event_report( chan_id, EVNT_SIZE_OVER, (UINT8*)para, sizeof(para));   \
    }                                                       \
}while(0)

/* type=108, slice个数超过阈值 */
#define REPORT_SLICE_NUM_OVER( chan_id, SliceNum, MaxSliceNum )	                \
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[2];                                    \
        para[0] = SliceNum;                         	    \
        para[1] = MaxSliceNum;                          	\
        g_event_report( chan_id, EVNT_SLICE_NUM_OVER, (UINT8*)para, sizeof(para)); \
    }                                                       \
}while(0)

/* type=109, sps个数超过阈值 */
#define REPORT_SPS_NUM_OVER( chan_id, SpsNum, MaxSpsNum )	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[2];                                    \
        para[0] = SpsNum;                           	    \
        para[1] = MaxSpsNum;                            	\
        g_event_report( chan_id, EVNT_SPS_NUM_OVER, (UINT8*)para, sizeof(para));\
    }                                                       \
}while(0)

/* type=110, pps个数超过阈值 */
#define REPORT_PPS_NUM_OVER( chan_id, PpsNum, MaxPpsNum )	\
do{                                                         \
    if( NULL != g_event_report )                    		\
    {                                                       \
        UINT32  para[2];                                    \
        para[0] = PpsNum;                            	    \
        para[1] = MaxPpsNum;                             	\
        g_event_report( chan_id, EVNT_PPS_NUM_OVER, (UINT8*)para, sizeof(para));\
    }                                                       \
}while(0)

/* type=111  发现I帧解码错误    无 */
#define REPORT_IFRAME_ERR(chan_id)                     	    \
do{                                                         \
    if( NULL != g_event_report )                            \
    {                                                       \
        g_event_report( chan_id, EVNT_IFRAME_ERR, (UINT8*)0, 0);                \
    }                                                       \
}while(0)

/* type=112  发现新的帧结束符    无 */
#define REPORT_MEET_NEWFRM(chan_id)                     	\
do{                                                         \
    if( NULL != g_event_report )                            \
    {                                                       \
        g_event_report( chan_id, EVNT_MEET_NEWFRM, (UINT8*)0, 0);               \
    }                                                       \
}while(0)

/* type=113  码流解析错误*/
#define REPORT_DECSYNTAX_ERR(chan_id)                     	\
do{ 														\
    if( NULL != g_event_report )							\
    {														\
        g_event_report( chan_id, EVNT_DECSYNTAX_ERR, (UINT8*)0, 0);             \
    }														\
}while(0)

/* type=114  错误率非零上报 */
#define REPORT_RATIO_NOTZERO(chan_id, ErrRatio)                                 \
do{ 														\
    if( NULL != g_event_report )							\
    {														\
        UINT32  para[1];                                    \
        para[0] = ErrRatio;                                 \
        g_event_report( chan_id, EVNT_RATIO_NOTZERO, (UINT8*)para, sizeof(para));  \
    }														\
}while(0)

/* type=115  最后一帧输出结果上报 */
#define REPORT_LAST_FRAME(chan_id, flag)                    \
do{ 														\
    if( NULL != g_event_report )							\
    {														\
        UINT32  para[1];                                    \
        para[0] = (UINT32)(flag);                     	    \
        g_event_report( chan_id, EVNT_LAST_FRAME, (UINT8*)para, sizeof(para));  \
    }														\
}while(0)

/* type=116  变分辨率重新分割帧存上报 */
#define REPORT_RESOLUTION_CHANGE(chan_id)                   \
do{ 														\
    if( NULL != g_event_report )							\
    {														\
        g_event_report( chan_id, EVNT_RESOLUTION_CHANGE, (UINT8*)0, 0);         \
    }														\
}while(0)
	
/* type=117  码流结束符上报 */
#define REPORT_STREAM_END_SYNTAX(chan_id)                   \
do{ 														\
    if( NULL != g_event_report )							\
    {														\
	    g_event_report( chan_id, EVNT_STREAM_END_SYNTAX, (UINT8*)0, 0);         \
	}														\
}while(0)

/* type=118 码流信息上报划分帧存*/
#define REPORT_NEED_ARRANGE(chan_id, FrmNum, FrmSize, PmvSize, DecWidth, DecHeight, Stride, DispWidth, DispHeight)                     	\
do{ 														\
	if( NULL != g_event_report )							\
	{														\
        UINT32  para[8];                                    \
        para[0] = (UINT32)(FrmNum);                         \
        para[1] = (UINT32)(FrmSize);                        \
        para[2] = (UINT32)(PmvSize);                        \
        para[3] = (UINT32)(DecWidth);                       \
        para[4] = (UINT32)(DecHeight);                      \
        para[5] = (UINT32)(Stride);                         \
        para[6] = (UINT32)(DispWidth);                      \
        para[7] = (UINT32)(DispHeight);                     \
        g_event_report(chan_id, EVNT_NEED_ARRANGE, (UINT8*)para, sizeof(para));  \
	}														\
}while(0)
    
    /* type=119 发现不支持的规格 上报类型及数值 */
#define REPORT_UNSUPPORT_SPEC(chan_id, unsupport_spec, data)                       \
do{                                                         \
    if( NULL != g_event_report )                            \
    {                                                       \
        UINT32  para[2];                                    \
        para[0] = unsupport_spec;                           \
        para[1] = data;                                     \
        g_event_report( chan_id, EVNT_UNSUPPORT_SPEC, (UINT8*)para, sizeof(para)); \
    }                                                       \
}while(0)
    
/* type=120  变分辨率时输出假帧让后级还帧 */
#define REPORT_FAKE_FRAME(chan_id)                     	    \
do{                                                         \
    if( NULL != g_event_report )                            \
    {                                                       \
        g_event_report( chan_id, EVNT_FAKE_FRAME, (UINT8*)0, 0);                \
    }                                                       \
}while(0)

/* type=122  Report color aspects info */
#define REPORT_COLOR_ASPECTS_INFO(chan_id, para, len)                  \
do {                                                        \
    if (NULL != g_event_report)                             \
    {                                                       \
        g_event_report(chan_id, EVNT_COLOR_ASPECTS_CHG, (UINT8*)para, len); \
    }                                                       \
} while (0)

#define dprint_sos_kernel(type, fmt, arg...)                        \
do{                                                                 \
    if (((PRN_ALWS == type) || (0 != (g_PrintEnable & (1LL << type)))) \
        && (DEV_SCREEN == g_PrintDevice))                            \
    {                                                               \
        VFMW_OSAL_Print("S: ");                                     \
        VFMW_OSAL_Print(fmt, ##arg);                                \
    }                                                               \
}while(0)


#ifdef HI_ADVCA_FUNCTION_RELEASE
// 高安不能检测到字符串和printk
#define dprint(type, fmt, arg...)  vfmw_dprint_nothing()
#else

#ifdef ENV_SOS_KERNEL
#define dprint(type, fmt, arg...)  dprint_sos_kernel(type, fmt, ##arg)
#else
#define dprint(type, fmt, arg...)  dprint_linux_kernel(type, fmt, ##arg)
#endif

#endif
 

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
      functions 
 ***********************************************************************/
VOID   vfmw_dprint_nothing(VOID);
SINT32 IsDprintTypeEnable(UINT32 type);

#ifdef ENV_ARMLINUX_KERNEL
SINT32 dprint_linux_kernel( UINT32 type, const SINT8 *format, ... );
#endif

#ifdef VFMW_RECPOS_SUPPORT
#define  DBG_OK       (0)
#define  DBG_ERR     (-1)
SINT32   DBG_CreateTracer(VOID);
VOID     DBG_DestroyTracer(VOID);
VOID     DBG_AddTrace( SINT8 *pFuncName, SINT32 nLine, SINT32 Data );
VOID     DBG_GetTracerInfo( SINT32 *pMemPhyAddr, SINT32 *pMemLength, ULONG *pTracePhyAddr, SINT32 *pMaxNum, SINT32 *pCurIdx );
VOID     DBG_PrintTracer( SINT32 TraceDepth );
#endif

SINT32 CHECK_REC_POS_ENABLE(SINT32 type);

#ifdef VFMW_SCD_LOWDLY_SUPPORT
VOID DBG_CountTimeInfo(SINT32 ChanID, VFMW_STATE_TYPE_E SateType, SINT32 LowdlyFlag);
#endif

VOID     qsort( VOID *base, size_t num, size_t width, SINT32(*comp)(const VOID*, const VOID*) );

#ifdef __cplusplus
}
#endif

#endif

