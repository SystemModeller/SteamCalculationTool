#include "stdafx.h"
#include "EntropyValues.h"
#include "KnownValuesStruct.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <limits.h>
#include <sstream>


using namespace System;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Configuration;


EntropyValues::EntropyValues()
{

}


KnownValuesStruct EntropyValues::EntropyCheck(double MPaValue, double entropy, double tempKelvin)
{
	double midCheck_V_Mass{};
	double midCheck_H_kJ_kg{};
	double midCheck_S_kJ_kg{};
	KnownValuesStruct KVN;
	KnownValuesStruct KVN_LOW;
	KnownValuesStruct KVN_HIGH;
	try
	{
		ConnectionStringSettings^ settings = ConfigurationManager::ConnectionStrings["SteamPower"];
		if (settings == nullptr)
		{
			Console::WriteLine("Could not obtain settings");
		}
		SqlClient::SqlConnection ^conn = gcnew SqlClient::SqlConnection();
		conn->ConnectionString = settings->ConnectionString;
		conn->Open();
		SqlClient::SqlCommand ^cmd = gcnew SqlClient::SqlCommand();
		if (MPaValue == 0.0040 || MPaValue == 3.0 || MPaValue == 4.0 || MPaValue == 6.0 || MPaValue == 8.0 || MPaValue == 10.0 || MPaValue == 15.0 || MPaValue == 20.0)
		{
			cmd->CommandText = ("Steam_Entropy_MPa_Band");
			cmd->CommandType = CommandType::StoredProcedure;
			cmd->Parameters->Add("@Pressure_Band_MPa", SqlDbType::Decimal)->Value = MPaValue;
			cmd->Parameters->Add("@entropy", SqlDbType::Decimal)->Value = entropy;
			cmd->Connection = conn;
			SqlClient::SqlDataReader ^rdr = nullptr;
			rdr = cmd->ExecuteReader();
			while (rdr->Read())
			{
				//Console::WriteLine("Output is:  {0},{1},{2},{3}", rdr["Temp_K"], rdr["V_Mass"], rdr["H_kJ_kg"], rdr["S_kJ_kg"]);
				lowMPA_Low_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
				lowMPA_Low_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
				lowMPA_Low_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
				lowMPA_Low_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
			}
			rdr->NextResult();
			while (rdr->Read())
			{
				//Console::WriteLine("Output is:  {0},{1},{2},{3}", rdr["Temp_K"], rdr["V_Mass"], rdr["H_kJ_kg"], rdr["S_kJ_kg"]);
				lowMPA_High_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
				lowMPA_High_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
				lowMPA_High_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
				lowMPA_High_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
			}

			double divisonValue = { 10000.00 };
			double dividedLowEntropy = lowMPA_High_S_kJ_kg - lowMPA_Low_S_kJ_kg;
			double divisionResult = dividedLowEntropy / divisonValue;
			double tempLowDivisionEntropy = lowMPA_High_H_kJ_kg - lowMPA_Low_H_kJ_kg;
			double low_H_kJResult = tempLowDivisionEntropy / divisonValue;
			double tempKAvg = lowMPA_High_Temp_K - lowMPA_Low_Temp_K;
			double lowAvgTemp = tempKAvg / divisonValue;
			int upCountValue{ 1 };
			double additionValue{};
			additionValue = lowMPA_Low_S_kJ_kg;

			for (size_t i{}; i <= 10000; ++i)
			{
				additionValue = additionValue + divisionResult;
				double x;
				std::string addditionValueText = std::to_string(additionValue);
				addditionValueText.erase(6); //TODO find the decimal place and go to 4 points! 
				std::string midPoint_S_kJ_kgText = std::to_string(entropy);
				int pointMidPointValueText = midPoint_S_kJ_kgText.find(".");
				midPoint_S_kJ_kgText.erase(6);
				if (midPoint_S_kJ_kgText == addditionValueText)
				{
					//Console::WriteLine("Mid point reached on itteration {0} / {1}", upCountValue, i);
					//Console::WriteLine("**** iteration values are midpoint: {0}  LOWMPA {1}", midPoint_S_kJ_kg, additionValue);
					KVN_LOW.average_H_kJ_kg = (low_H_kJResult * i) + lowMPA_Low_H_kJ_kg;
					KVN_LOW.average_MPA_Temp_K = (lowAvgTemp * i) + lowMPA_Low_Temp_K;
					KVN.average_H_kJ_kg = (low_H_kJResult * i) + lowMPA_Low_H_kJ_kg;
					break;
				}
			}
			return KVN;
		}

		else
		{
			if (MPaValue >= 0.400  && MPaValue <= 0.700)
			{
				lowBand = 0.400;
				highBand = 0.700;
				MPa_Band_Gap = 0.300;
				MPaDifference = MPaValue - lowBand;
			}

			if (MPaValue >= 3.0  && MPaValue <= 4.0)
			{
				lowBand = 3.0;
				highBand = 4.0;
				MPa_Band_Gap = 1.0;
				MPaDifference = MPaValue - lowBand;
			}

			if (MPaValue >= 4.0  && MPaValue <= 6.0)
			{
				lowBand = 4.0;
				highBand = 6.0;
				MPa_Band_Gap = 2.0;
				MPaDifference = MPaValue - lowBand;
			}

			if (MPaValue >= 6.0  && MPaValue <= 8.0)
			{
				lowBand = 6.0;
				highBand = 8.0;
				MPa_Band_Gap = 2.0;
				MPaDifference = MPaValue - lowBand;
			}

			if (MPaValue >= 8.0  && MPaValue <= 10.0)
			{
				lowBand = 8.0;
				highBand = 10.0;
				MPa_Band_Gap = 2.0;
				MPaDifference = MPaValue - lowBand;
			}
			if (MPaValue >= 10.0 && MPaValue <= 15.0)
			{
				lowBand = 10.0;
				highBand = 15.0;
				MPa_Band_Gap = 5.0;
				MPaDifference = MPaValue - lowBand;
			}

			if (MPaValue >= 15.0 && MPaValue <= 20.0)
			{
				lowBand = 15.0;
				highBand = 20.0;
				MPa_Band_Gap = 5.0;
				MPaDifference = MPaValue - lowBand;
			}

			cmd->CommandText = ("Steam_Entropy_MPa_Band_bracket");
			cmd->CommandType = CommandType::StoredProcedure;
			cmd->Parameters->Clear();
			cmd->Parameters->Add("@Pressure_Band_MPa_Lower", SqlDbType::Decimal)->Value = lowBand;
			cmd->Parameters->Add("@Pressure_Band_MPa_Upper", SqlDbType::Decimal)->Value = highBand;
			cmd->Parameters->Add("@entropy", SqlDbType::Decimal)->Value = entropy;
			cmd->Connection = conn;
			SqlClient::SqlDataReader ^rdr = nullptr;

			rdr = cmd->ExecuteReader();
			//Console::WriteLine("*****ENTROPY Value between steam table bands ***************");
			while (rdr->Read())
			{
				lowMPA_Low_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
				lowMPA_Low_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
				lowMPA_Low_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
				lowMPA_Low_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
				//Console::WriteLine("*****ENTROPY Low MPa Band {0} For Kelvin {1} **** Low ****** ", lowBand, rdr["Temp_K"]);
				//Console::WriteLine(" V Mass :" + Convert::ToDouble(rdr["V_Mass"]));
				//Console::WriteLine(" H Kj : " + Convert::ToDouble(rdr["H_kJ_kg"]));
				//Console::WriteLine(" S Kj : " + Convert::ToDouble(rdr["S_kJ_kg"]));
			}
			rdr->NextResult();
			while (rdr->Read())
			{
				lowMPA_High_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
				lowMPA_High_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
				lowMPA_High_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
				lowMPA_High_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
				//Console::WriteLine("*****ENTROPY Low MPa Band {0} For Kelvin {1} **** High ****** ", lowBand, rdr["Temp_K"]);
				//Console::WriteLine(" V Mass :" + Convert::ToDouble(rdr["V_Mass"]));
				//Console::WriteLine(" H Kj : " + Convert::ToDouble(rdr["H_kJ_kg"]));
				//Console::WriteLine(" S Kj : " + Convert::ToDouble(rdr["S_kJ_kg"]));
			}

			rdr->NextResult();
			while (rdr->Read())
			{
				highMPA_Low_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
				highMPA_Low_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
				highMPA_Low_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
				highMPA_Low_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
				//Console::WriteLine("*****ENTROPY High MPa Band {0} For Kelvin {1} **** Low ****** ", highBand, rdr["Temp_K"]);
				//Console::WriteLine(" V Mass :" + Convert::ToDouble(rdr["V_Mass"]));
				//Console::WriteLine(" H Kj : " + Convert::ToDouble(rdr["H_kJ_kg"]));
				//Console::WriteLine(" S Kj : " + Convert::ToDouble(rdr["S_kJ_kg"]));
			}
			rdr->NextResult();
			while (rdr->Read())
			{
				highMPA_High_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
				highMPA_High_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
				highMPA_High_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
				highMPA_High_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
				//Console::WriteLine("*****ENTROPY Low MPa Band {0} For Kelvin {1} **** High ****** ", highBand, rdr["Temp_K"]);
				//Console::WriteLine(" V Mass :" + Convert::ToDouble(rdr["V_Mass"]));
				//Console::WriteLine(" H Kj : " + Convert::ToDouble(rdr["H_kJ_kg"]));
				//Console::WriteLine(" S Kj : " + Convert::ToDouble(rdr["S_kJ_kg"]));
			}
		}

		tempSetValue = tempKelvin - lowMPA_Low_Temp_K;

		//Console::WriteLine("***** Check values are: lowMPA: {0}  Mid point ****** {1}", lowMPA_Low_S_kJ_kg, midPoint_S_kJ_kg);

		double divisonValue = { 10000.00 };
		double dividedLowEntropy = lowMPA_High_S_kJ_kg - lowMPA_Low_S_kJ_kg;
		double divisionResult = dividedLowEntropy / divisonValue;
		double tempLowDivisionEntropy = lowMPA_High_H_kJ_kg - lowMPA_Low_H_kJ_kg;
		double low_H_kJResult = tempLowDivisionEntropy / divisonValue;
		double tempKAvg = lowMPA_High_Temp_K - lowMPA_Low_Temp_K;
		double lowAvgTemp = tempKAvg / divisonValue;

		int upCountValue{ 1 };
		double additionValue{};
		additionValue = lowMPA_Low_S_kJ_kg;


		for (size_t i{}; i <= 10000; ++i)
		{
			additionValue = additionValue + divisionResult;
			double x;
			std::string addditionValueText = std::to_string(additionValue);
			addditionValueText.erase(6); //TODO find the decimal place and go to 4 points! 
			std::string midPoint_S_kJ_kgText = std::to_string(entropy);
			int pointMidPointValueText = midPoint_S_kJ_kgText.find(".");
			midPoint_S_kJ_kgText.erase(6);
			if (midPoint_S_kJ_kgText == addditionValueText)
			{
				//Console::WriteLine("Mid point reached on itteration {0} / {1}", upCountValue, i);
				//Console::WriteLine("**** iteration values are midpoint: {0}  LOWMPA {1}", midPoint_S_kJ_kg, additionValue);
				KVN_LOW.average_H_kJ_kg = (low_H_kJResult * i) + lowMPA_Low_H_kJ_kg;
				KVN_LOW.average_MPA_Temp_K = (lowAvgTemp * i) + lowMPA_Low_Temp_K;
				break;
			}
		}

		 dividedLowEntropy = highMPA_High_S_kJ_kg - highMPA_Low_S_kJ_kg;
		 divisionResult = dividedLowEntropy / divisonValue;
		 tempLowDivisionEntropy = highMPA_High_H_kJ_kg - highMPA_Low_H_kJ_kg;
		 low_H_kJResult = tempLowDivisionEntropy / divisonValue;
		 tempKAvg = highMPA_High_Temp_K - highMPA_Low_Temp_K;
		 lowAvgTemp = tempKAvg / divisonValue;
		additionValue = highMPA_Low_S_kJ_kg;
		for (size_t i{}; i <= 10000; ++i)
		{
			additionValue = additionValue + divisionResult;
			double x;
			std::string addditionValueText = std::to_string(additionValue);
			addditionValueText.erase(6); //TODO find the decimal place and go to 4 points! 
			std::string midPoint_S_kJ_kgText = std::to_string(entropy);
			int pointMidPointValueText = midPoint_S_kJ_kgText.find(".");
			midPoint_S_kJ_kgText.erase(6);
			if (midPoint_S_kJ_kgText == addditionValueText)
			{
				//Console::WriteLine("Mid point reached on itteration {0} / {1}", upCountValue, i);
				//Console::WriteLine("**** iteration values are midpoint: {0}  LOWMPA {1}", midPoint_S_kJ_kg, additionValue);
				KVN_HIGH.average_H_kJ_kg = (low_H_kJResult * i) + highMPA_Low_H_kJ_kg;
				KVN_HIGH.average_MPA_Temp_K = (lowAvgTemp * i) + highMPA_Low_Temp_K;
				break;
			}
		}

		double averageKVN = (KVN_HIGH.average_H_kJ_kg - KVN_LOW.average_H_kJ_kg) / MPa_Band_Gap; 
		KVN.average_H_kJ_kg = (averageKVN * MPaDifference) + KVN_LOW.average_H_kJ_kg; 

		return KVN; 

	}
	catch (Exception ^ex)
	{
		return KVN;
		Console::WriteLine(ex->Message);
	}
	finally
	{

	}
	return KVN;
}
