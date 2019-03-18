#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <limits.h>
#include <sstream>
#include "AverageKnownValues.h"
#include "KnownValuesStruct.h"
#include "EntropyValues.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Configuration;
using namespace System;

int main(array<System::String ^> ^args)
{
	double hpMPaValue = 11.0;
	double hptempKelvin = 620;
	double hpLeavingMPaValue = 11.0;
	double hpLeavingtempKelvin = 620;

	double ipEntryMPaValue = 11.0;
	double ipEntrytempKelvin = 620;
	double ipLeavingMPaValue = 11.0;
	double ipLeavingtempKelvin = 620;

	double lpEntryMPaValue = 11.0;
	double lpEntrytempKelvin = 620;
	double lpLeavingMPaValue = 11.0;
	double lpLeavingtempKelvin = 620;

	int entropy_HP_1_Start{};
	int entropy_HP_1_End{};

	int inlet_Temp_HP{};
	double pressure_HP_Inlet{};
	int outlet_Temp_HP{};
	double pressure_HP_Outlet{};
	int enthalpy_HP_Inlet{};
	int enthalpy_HP_Outlet{};

	std::cout << "Enter the High Pressure section INLET temp:";
	std::cin >> inlet_Temp_HP;
	std::cout << "Enter the High Pressure section INLET pressure:";
	std::cin >> pressure_HP_Inlet;
	//Convert  BAR to MPa
	hpMPaValue = pressure_HP_Inlet * 0.1;
	//Convert Degrees to Kelvin 
	hptempKelvin = inlet_Temp_HP + 273.15;
	std::cout << "Enter the High Pressure section OUTLET temp:";
	std::cin >> inlet_Temp_HP;
	std::cout << "Enter the High Pressure section OUTLET pressure:";
	std::cin >> pressure_HP_Inlet;
	//Convert  BAR to MPa
	hpLeavingMPaValue = pressure_HP_Inlet * 0.1;
	//Convert Degrees to Kelvin 
	hpLeavingtempKelvin = inlet_Temp_HP + 273.15;

	std::cout << "\nEnter the Intermediate Pressure section INLET temp:";
	std::cin >> inlet_Temp_HP;
	std::cout << "Enter the Intermediate Pressure section INLET pressure:";
	std::cin >> pressure_HP_Inlet;
	//Convert  BAR to MPa
	ipEntryMPaValue = pressure_HP_Inlet * 0.1;
	//Convert Degrees to Kelvin 
	ipEntrytempKelvin = inlet_Temp_HP + 273.15;
	std::cout << "Enter the Intermediate Pressure section OUTLET temp:";
	std::cin >> inlet_Temp_HP;
	std::cout << "Enter the Intermediate Pressure section OUTLET inlet:";
	std::cin >> pressure_HP_Inlet;
	//Convert  BAR to MPa
	ipLeavingMPaValue = pressure_HP_Inlet * 0.1;
	//Convert Degrees to Kelvin 
	ipLeavingtempKelvin = inlet_Temp_HP + 273.15;

	std::cout << "\nEnter the Low Pressure INLET temp:";
	std::cin >> inlet_Temp_HP;
	std::cout << "Enter the Low Pressure INLET pressure:";
	std::cin >> pressure_HP_Inlet;
	//Convert  BAR to MPa
	lpEntryMPaValue = pressure_HP_Inlet * 0.1;
	//Convert Degrees to Kelvin 
	lpEntrytempKelvin = inlet_Temp_HP + 273.15;
	std::cout << "Enter the Low Pressure OUTLET temp:";
	std::cin >> inlet_Temp_HP;
	std::cout << "Enter the Low Pressure OUTLET pressure:";
	std::cin >> pressure_HP_Inlet; //Vacuum 
	//Convert  BAR to MPa
	lpLeavingMPaValue = pressure_HP_Inlet * 0.0001;
	//Convert Degrees to Kelvin 
	lpLeavingtempKelvin = inlet_Temp_HP + 273.15;

	//Create the AverageKnownValues object
	AverageKnownValues ^AvgKnownValues = gcnew AverageKnownValues();
	KnownValuesStruct hpEntryValue = AvgKnownValues->KnownValues(hpMPaValue, hptempKelvin);
	Console::WriteLine("*** HP Entry values ***");
	Console::WriteLine(" V Mass :" + hpEntryValue.average_V_Mass);
	Console::WriteLine(" H Kj : " + hpEntryValue.average_H_kJ_kg);
	Console::WriteLine(" S Kj : " + hpEntryValue.average_S_kJ_kg);

	AverageKnownValues ^AvgKnownLeavingValues = gcnew AverageKnownValues();
	KnownValuesStruct hpLeavingValue = AvgKnownLeavingValues->KnownValues(hpLeavingMPaValue, hpLeavingtempKelvin);
	Console::WriteLine("*** HP leaving values ***");
	Console::WriteLine(" V Mass :" + hpLeavingValue.average_V_Mass);
	Console::WriteLine(" H Kj : " + hpLeavingValue.average_H_kJ_kg);
	Console::WriteLine(" S Kj : " + hpLeavingValue.average_S_kJ_kg);

	EntropyValues ^EntropyValueHP = gcnew EntropyValues();
	KnownValuesStruct HPEntropyValues = EntropyValueHP->EntropyCheck(hpLeavingMPaValue, hpEntryValue.average_S_kJ_kg, hptempKelvin);
	Console::WriteLine("*** HP Theoretical value ***");
	Console::WriteLine(" H Kj : " + HPEntropyValues.average_H_kJ_kg);

	AverageKnownValues ^AvgIPKnownValues = gcnew AverageKnownValues();
	KnownValuesStruct ipEntryValue = AvgIPKnownValues->KnownValues(ipEntryMPaValue, ipEntrytempKelvin);
	Console::WriteLine("***IP Pressure Entry values ***");
	Console::WriteLine(" V Mass :" + ipEntryValue.average_V_Mass);
	Console::WriteLine(" H Kj : " + ipEntryValue.average_H_kJ_kg);
	Console::WriteLine(" S Kj : " + ipEntryValue.average_S_kJ_kg);
	AverageKnownValues ^AvgIPLeavingKnownValues = gcnew AverageKnownValues();
	KnownValuesStruct ipLeavingValue = AvgIPLeavingKnownValues->KnownValues(ipLeavingMPaValue, ipLeavingtempKelvin);
	Console::WriteLine("***IP Pressure Leaving values ***");
	Console::WriteLine(" V Mass :" + ipLeavingValue.average_V_Mass);
	Console::WriteLine(" H Kj : " + ipLeavingValue.average_H_kJ_kg);
	Console::WriteLine(" S Kj : " + ipLeavingValue.average_S_kJ_kg);

	EntropyValues ^EntropyValueIP = gcnew EntropyValues();
	KnownValuesStruct IPEntropyValues = EntropyValueIP->EntropyCheck(ipLeavingMPaValue, ipEntryValue.average_S_kJ_kg, ipEntrytempKelvin);
	Console::WriteLine("*** IP Theoretical value ***");
	Console::WriteLine(" H Kj : " + IPEntropyValues.average_H_kJ_kg);

	AverageKnownValues ^AvgLPKnownValues = gcnew AverageKnownValues();
	KnownValuesStruct lpEntryValue = AvgLPKnownValues->KnownValues(lpEntryMPaValue, lpEntrytempKelvin);
	Console::WriteLine("***LP Pressure Entry values ***");
	Console::WriteLine(" V Mass :" + lpEntryValue.average_V_Mass);
	Console::WriteLine(" H Kj : " + lpEntryValue.average_H_kJ_kg);
	Console::WriteLine(" S Kj : " + lpEntryValue.average_S_kJ_kg);
	AverageKnownValues ^AvgLPLeavingKnownValues = gcnew AverageKnownValues();
	KnownValuesStruct lpLeavingValue = AvgLPLeavingKnownValues->KnownValues(lpLeavingMPaValue, lpLeavingtempKelvin);
	Console::WriteLine("***LP Pressure Leaving values ***");
	Console::WriteLine(" V Mass :" + lpLeavingValue.average_V_Mass);
	Console::WriteLine(" H Kj : " + lpLeavingValue.average_H_kJ_kg);
	Console::WriteLine(" S Kj : " + lpLeavingValue.average_S_kJ_kg);

	EntropyValues ^EntropyValueLP = gcnew EntropyValues();
	KnownValuesStruct LPEntropyValues = EntropyValueLP->EntropyCheck(lpLeavingMPaValue, lpEntryValue.average_S_kJ_kg, lpEntrytempKelvin);
	Console::WriteLine("*** LP Theoretical value ***");
	Console::WriteLine(" H Kj : " + LPEntropyValues.average_H_kJ_kg);

	return 0;
}
