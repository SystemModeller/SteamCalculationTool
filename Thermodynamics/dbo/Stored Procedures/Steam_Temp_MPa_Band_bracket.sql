
-- =============================================
-- Author:		MG System Modeller
-- Create date: 14/07/2018
-- Description:	Pressure band / temp selection
-- =============================================
CREATE PROCEDURE [dbo].[Steam_Temp_MPa_Band_bracket] @Pressure_Band_MPa_Lower decimal(18,4),@Pressure_Band_MPa_Upper decimal(18,4), @Temp_K decimal(18,0)

AS
BEGIN

	SET NOCOUNT ON;
		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			Temp_K <= @Temp_K 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Lower
		ORDER BY 
			Temp_K 
		DESC 

		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			Temp_K >= @Temp_K 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Lower
		ORDER BY 
			Temp_K 
		ASC 


		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			Temp_K <= @Temp_K 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Upper
		ORDER BY 
			Temp_K 
		DESC 

		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			Temp_K >= @Temp_K 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Upper
		ORDER BY 
			Temp_K 
		ASC 
END

