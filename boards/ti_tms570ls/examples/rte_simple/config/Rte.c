/*
* Configuration of module: Rte (Rte.c)
*
* Created by:              
* Copyright:               
*
* Configured for (MCU):    TMS570
*
* Module vendor:           ArcCore
* Generator version:       0.0.13
*
* Generated by Arctic Studio (http://arccore.com) 
*/

/* Rte.c */
#include "Os.h"
#include "Rte_Type.h"
#include "Rte_Data.h"
#include <string.h>
#include "Rte_Calculator_Internal.h"
#include "Rte_Tester_Internal.h"
#include "Rte_Logger_Internal.h"
#include "Rte_Logger2_Internal.h"
#include "Com.h"

Rte_DE_Read_TesterRunnable_ReadArg1 Rte_Buf_TesterRunnable_Argumentsarg1_ibuffer;
Rte_DE_Read_TesterRunnable_ReadArg2 Rte_Buf_TesterRunnable_Argumentsarg2_ibuffer;
Rte_DE_Read_FreqReqRunnable_ReadFreqReq Rte_Buf_FreqReqRunnable_FreqReqfreq_ibuffer;
Rte_DE_Write_TesterRunnable_WriteResult Rte_Buf_TesterRunnable_Resultresult_ibuffer;
Rte_DE_Write_FreqReqRunnable_WriteFreqReqInd Rte_Buf_FreqReqRunnable_FreqReqIndfreq_ibuffer;
Rte_CDS_Tester Rte_Inst_Tester =
{
	.TesterRunnable_Arguments_arg1 = &Rte_Buf_TesterRunnable_Argumentsarg1_ibuffer,
	.TesterRunnable_Arguments_arg2 = &Rte_Buf_TesterRunnable_Argumentsarg2_ibuffer,
	.FreqReqRunnable_FreqReq_freq = &Rte_Buf_FreqReqRunnable_FreqReqfreq_ibuffer,
	.TesterRunnable_Result_result = &Rte_Buf_TesterRunnable_Resultresult_ibuffer,
	.FreqReqRunnable_FreqReqInd_freq = &Rte_Buf_FreqReqRunnable_FreqReqIndfreq_ibuffer,
};

Rte_DE_Read_LoggerRunnable_ReadResult Rte_Buf_LoggerRunnable_Resultresult_ibuffer;
Rte_CDS_Logger Rte_Inst_Logger =
{
	.LoggerRunnable_Result_result = &Rte_Buf_LoggerRunnable_Resultresult_ibuffer,
};

Rte_DE_Read_Logger2Runnable_ReadResult Rte_Buf_Logger2Runnable_Resultresult_ibuffer;
Rte_CDS_Logger2 Rte_Inst_Logger2 =
{
	.Logger2Runnable_Result_result = &Rte_Buf_Logger2Runnable_Resultresult_ibuffer,
};

void Rte_PRE_TesterRunnable() {
	GetResource(RES_SCHEDULER);

	uint8 Arg1_buf = 0;
	Com_ReceiveSignal(Arg1, &Arg1_buf);
	Rte_Inst_Tester.TesterRunnable_Arguments_arg1->value = (UInt8) Arg1_buf;

	uint8 Arg2_buf = 0;
	Com_ReceiveSignal(Arg2, &Arg2_buf);
	Rte_Inst_Tester.TesterRunnable_Arguments_arg2->value = (UInt8) Arg2_buf;

	ReleaseResource(RES_SCHEDULER);

}

void Rte_PRE_FreqReqRunnable() {
	GetResource(RES_SCHEDULER);

	uint32 FreqReqSig_buf = 0;
	Com_ReceiveSignal(FreqReqSig, &FreqReqSig_buf);
	Rte_Inst_Tester.FreqReqRunnable_FreqReq_freq->value =
			(UInt32) FreqReqSig_buf;

	ReleaseResource(RES_SCHEDULER);

}

void Rte_PRE_LoggerRunnable() {
	GetResource(RES_SCHEDULER);

	Rte_Inst_Logger.LoggerRunnable_Result_result->value =
			Rte_Buf_Tester_prototype_Result_result;

	ReleaseResource(RES_SCHEDULER);

}

void Rte_PRE_Logger2Runnable() {
	GetResource(RES_SCHEDULER);

	Rte_Inst_Logger2.Logger2Runnable_Result_result->value =
			Rte_Buf_Tester_prototype_Result_result;

	ReleaseResource(RES_SCHEDULER);

}

void Rte_POST_TesterRunnable() {
	GetResource(RES_SCHEDULER);

	uint8 ResultSig_buf =
			(uint8) Rte_Inst_Tester.TesterRunnable_Result_result->value;
	Com_SendSignal(ResultSig, &ResultSig_buf);

	Rte_WriteBuffer_Rte_Buf_Tester_prototype_Result_result(
			Rte_Inst_Tester.TesterRunnable_Result_result->value);

	ReleaseResource(RES_SCHEDULER);

}

void Rte_POST_FreqReqRunnable() {
	GetResource(RES_SCHEDULER);

	uint32 FreqIndSig_buf =
			(uint32) Rte_Inst_Tester.FreqReqRunnable_FreqReqInd_freq->value;
	Com_SendSignal(FreqIndSig, &FreqIndSig_buf);

	ReleaseResource(RES_SCHEDULER);

}

void Rte_TesterRunnable() {
	Rte_PRE_TesterRunnable();
	TesterRunnable();
	Rte_POST_TesterRunnable();
}

void Rte_FreqReqRunnable() {
	Rte_PRE_FreqReqRunnable();
	FreqReqRunnable();
	Rte_POST_FreqReqRunnable();
}

Std_ReturnType Rte_Multiply(const UInt8 arg1, const UInt8 arg2,
		UInt16* result) {
	Std_ReturnType retVal = Multiply(arg1, arg2, result);
	return retVal;
}

void Rte_LoggerRunnable() {
	Rte_PRE_LoggerRunnable();
	LoggerRunnable();
}

void Rte_Logger2Runnable() {
	Rte_PRE_Logger2Runnable();
	Logger2Runnable();
}

Std_ReturnType Rte_Start() {
	return RTE_E_OK;
}

void StepTask() {
	EventMaskType eventMask = 0;
	while (1) {
		WaitEvent(EVENT_MASK_StepEvent);
		GetResource(RES_SCHEDULER);
		GetEvent(TASK_ID_StepTask, &eventMask);
		ClearEvent(EVENT_MASK_StepEvent);
		ReleaseResource(RES_SCHEDULER);
		if (eventMask & EVENT_MASK_StepEvent) {
			Rte_TesterRunnable();
		}
		if (eventMask & EVENT_MASK_StepEvent) {
			Rte_Logger2Runnable();
		}
		if (eventMask & EVENT_MASK_StepEvent) {
			Rte_LoggerRunnable();
		}
	}
}

