#pragma once
#include "KnownValuesStruct.h"

ref class AverageKnownValues
{
private:
	int entropy_HP_1_Start{};
	int entropy_HP_1_End{};

	int inlet_Temp_HP{};
	int pressure_HP_Inlet{};
	int outlet_Temp_HP{};
	int pressure_HP_Outlet{};
	int enthalpy_HP_Inlet{};
	int enthalpy_HP_Outlet{};

	double lowBand = 0.0;
	double highBand = 0.0;

	double lowMPA_Low_Temp_K = 0.0;
	double lowMPA_Low_V_Mass = 0.0;
	double lowMPA_Low_H_kJ_kg = 0.0;
	double lowMPA_Low_S_kJ_kg = 0.0;

	double lowMPA_High_Temp_K = 0.0;
	double lowMPA_High_V_Mass = 0.0;
	double lowMPA_High_H_kJ_kg = 0.0;
	double lowMPA_High_S_kJ_kg = 0.0;

	double highMPA_Low_Temp_K = 0.0;
	double highMPA_Low_V_Mass = 0.0;
	double highMPA_Low_H_kJ_kg = 0.0;
	double highMPA_Low_S_kJ_kg = 0.0;

	double highMPA_High_Temp_K = 0.0;
	double highMPA_High_V_Mass = 0.0;
	double highMPA_High_H_kJ_kg = 0.0;
	double highMPA_High_S_kJ_kg = 0.0;

	double tempLowDivision{};
	double tempSetValue{};

	double tempHighDivision{};
	double tempHighSetValue{};

	double tempLowResults{};
	double tempLowMass{};

	double tempLow_V_Mass{};
	double newBaseLineLow_V_Mass{};

	double tempLow_H_kJ_kg{};
	double newBaseLineLow_H_kJ_kg{};

	double tempLow_S_kJ_kg{};
	double newBaseLineLowS_kJ_kg{};

	double tempHigh_V_Mass{};
	double newBaseLineHigh_V_Mass{};

	double tempHigh_H_kJ_kg{};
	double newBaseLineHigh_H_kJ_kg{};

	double tempHigh_S_kJ_kg{};
	double newBaseLineHighS_kJ_kg{};

	double tempGen_V_Mass{};
	double newBaseLineGen_V_Mass{};

	double tempGen_H_kJ_kg{};
	double newBaseLineGen_H_kJ_kg{};

	double tempGen_S_kJ_kg{};
	double newBaseLineGenS_kJ_kg{};

	double midPoint_V_Mass{};
	double midPoint_H_kJ_kg{};
	double midPoint_S_kJ_kg{};
	double MPa_Band_Gap;
	double MPaDifference{};
public:
	AverageKnownValues();
	KnownValuesStruct KnownValues(double MPaValue, double tempKelvin);

};