#include "stdafx.h"
#include "KnownValuesStruct.h"
#include "AverageKnownValues.h"
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

AverageKnownValues::AverageKnownValues()
{

}
	
KnownValuesStruct AverageKnownValues::KnownValues(double MPaValue, double tempKelvin)
	{

	KnownValuesStruct KVN;
		try
		{
			ConnectionStringSettings^ settings = ConfigurationManager::ConnectionStrings["SteamPower"];
			if (settings == nullptr)
			{
				Console::WriteLine("Could not obtain settings");
				//	return -1;
			}

			SqlClient::SqlConnection ^conn = gcnew SqlClient::SqlConnection();
			conn->ConnectionString = settings->ConnectionString;
			conn->Open();
			SqlClient::SqlCommand ^cmd = gcnew SqlClient::SqlCommand();

			if (MPaValue == 0.0040 || MPaValue == 3.0 || MPaValue == 4.0 || MPaValue == 6.0 || MPaValue == 8.0 || MPaValue == 10.0 || MPaValue == 15.0 || MPaValue == 20.0)
			{
				cmd->CommandText = ("Steam_Temp_MPa_Band");
				cmd->CommandType = CommandType::StoredProcedure;
				cmd->Parameters->Add("@Pressure_Band_MPa", SqlDbType::Decimal)->Value = MPaValue;
				cmd->Parameters->Add("@Temp_K", SqlDbType::Decimal)->Value = tempKelvin;
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

				tempLowDivision = lowMPA_High_Temp_K - lowMPA_Low_Temp_K;
				tempSetValue = tempKelvin - lowMPA_Low_Temp_K;

				tempLow_V_Mass = (lowMPA_High_V_Mass - lowMPA_Low_V_Mass) / tempLowDivision;
				newBaseLineLow_V_Mass = (tempLow_V_Mass * tempSetValue) + lowMPA_Low_V_Mass;

				tempLow_H_kJ_kg = (lowMPA_High_H_kJ_kg - lowMPA_Low_H_kJ_kg) / tempLowDivision;
				newBaseLineLow_H_kJ_kg = (tempLow_H_kJ_kg * tempSetValue) + lowMPA_Low_H_kJ_kg;

				tempLow_S_kJ_kg = (lowMPA_High_S_kJ_kg - lowMPA_Low_S_kJ_kg) / tempLowDivision;
				newBaseLineLowS_kJ_kg = (tempLow_S_kJ_kg * tempSetValue) + lowMPA_Low_S_kJ_kg;

				KVN.average_V_Mass = newBaseLineLow_V_Mass;
				KVN.average_H_kJ_kg = newBaseLineLow_H_kJ_kg;
				KVN.average_S_kJ_kg = newBaseLineLowS_kJ_kg;

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
				cmd->CommandText = ("Steam_Temp_MPa_Band_bracket");
				cmd->CommandType = CommandType::StoredProcedure;
				cmd->Parameters->Add("@Pressure_Band_MPa_Lower", SqlDbType::Decimal)->Value = lowBand;
				cmd->Parameters->Add("@Pressure_Band_MPa_Upper", SqlDbType::Decimal)->Value = highBand;
				cmd->Parameters->Add("@Temp_K", SqlDbType::Decimal)->Value = tempKelvin;
				cmd->Connection = conn;
				SqlClient::SqlDataReader ^rdr = nullptr;

				rdr = cmd->ExecuteReader();
				//Console::WriteLine("***** Value between steam table bands ***************");
				while (rdr->Read())
				{
					lowMPA_Low_Temp_K = Convert::ToDouble(rdr["Temp_K"]);
					lowMPA_Low_V_Mass = Convert::ToDouble(rdr["V_Mass"]);
					lowMPA_Low_H_kJ_kg = Convert::ToDouble(rdr["H_kJ_kg"]);
					lowMPA_Low_S_kJ_kg = Convert::ToDouble(rdr["S_kJ_kg"]);
					//Console::WriteLine("*****Low MPa Band {0} For Kelvin {1} **** Low ****** ", lowBand, rdr["Temp_K"]);
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
					//Console::WriteLine("*****Low MPa Band {0} For Kelvin {1} **** High ****** ", lowBand, rdr["Temp_K"]);
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
					//Console::WriteLine("*****High MPa Band {0} For Kelvin {1} **** Low ****** ", highBand, rdr["Temp_K"]);
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
					//Console::WriteLine("*****Low MPa Band {0} For Kelvin {1} **** High ****** ", highBand, rdr["Temp_K"]);
					//Console::WriteLine(" V Mass :" + Convert::ToDouble(rdr["V_Mass"]));
					//Console::WriteLine(" H Kj : " + Convert::ToDouble(rdr["H_kJ_kg"]));
					//Console::WriteLine(" S Kj : " + Convert::ToDouble(rdr["S_kJ_kg"]));
				}
				rdr->Close();

				tempLowDivision = lowMPA_High_Temp_K - lowMPA_Low_Temp_K;
				tempSetValue = tempKelvin - lowMPA_Low_Temp_K;

				tempLow_V_Mass = (lowMPA_High_V_Mass - lowMPA_Low_V_Mass) / tempLowDivision;
				newBaseLineLow_V_Mass = (tempLow_V_Mass * tempSetValue) + lowMPA_Low_V_Mass;

				tempLow_H_kJ_kg = (lowMPA_High_H_kJ_kg - lowMPA_Low_H_kJ_kg) / tempLowDivision;
				newBaseLineLow_H_kJ_kg = (tempLow_H_kJ_kg * tempSetValue) + lowMPA_Low_H_kJ_kg;

				tempLow_S_kJ_kg = (lowMPA_High_S_kJ_kg - lowMPA_Low_S_kJ_kg) / tempLowDivision;
				newBaseLineLowS_kJ_kg = (tempLow_S_kJ_kg * tempSetValue) + lowMPA_Low_S_kJ_kg;

				tempHighDivision = highMPA_High_Temp_K - highMPA_Low_Temp_K;
				tempHighSetValue = tempKelvin - highMPA_Low_Temp_K;

				tempHigh_V_Mass = (highMPA_High_V_Mass - highMPA_Low_V_Mass) / tempHighDivision;
				newBaseLineHigh_V_Mass = (tempHigh_V_Mass * tempSetValue) + highMPA_Low_V_Mass;

				tempHigh_H_kJ_kg = (highMPA_High_H_kJ_kg - highMPA_Low_H_kJ_kg) / tempHighDivision;
				newBaseLineHigh_H_kJ_kg = (tempHigh_H_kJ_kg * tempSetValue) + highMPA_Low_H_kJ_kg;

				tempHigh_S_kJ_kg = (highMPA_High_S_kJ_kg - highMPA_Low_S_kJ_kg) / tempHighDivision;
				newBaseLineHighS_kJ_kg = (tempHigh_S_kJ_kg * tempSetValue) + highMPA_Low_S_kJ_kg;
				double midCheck_V_Mass{};
				double midCheck_H_kJ_kg{};
				double midCheck_S_kJ_kg{};

				midCheck_V_Mass = (newBaseLineHigh_V_Mass - newBaseLineLow_V_Mass) / MPa_Band_Gap;
				midPoint_V_Mass = (midCheck_V_Mass * MPaDifference) + newBaseLineLow_V_Mass;

				midCheck_H_kJ_kg = (newBaseLineHigh_H_kJ_kg - newBaseLineLow_H_kJ_kg) / MPa_Band_Gap;
				midPoint_H_kJ_kg = (midCheck_H_kJ_kg * MPaDifference) + newBaseLineLow_H_kJ_kg;

				midCheck_S_kJ_kg = (newBaseLineHighS_kJ_kg - newBaseLineLowS_kJ_kg) / MPa_Band_Gap;
				midPoint_S_kJ_kg = (midCheck_S_kJ_kg * MPaDifference) + newBaseLineLowS_kJ_kg;
				KVN.average_V_Mass = midPoint_V_Mass;
				KVN.average_H_kJ_kg = midPoint_H_kJ_kg;
				KVN.average_S_kJ_kg = midPoint_S_kJ_kg;
				//Console::WriteLine("***** Mid Values ****** ");
				//Console::WriteLine(" V Mass :" + midPoint_V_Mass);
				//Console::WriteLine(" H Kj : " + midPoint_H_kJ_kg);
				//Console::WriteLine(" S Kj : " + midPoint_S_kJ_kg);
				return KVN;

			}
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

