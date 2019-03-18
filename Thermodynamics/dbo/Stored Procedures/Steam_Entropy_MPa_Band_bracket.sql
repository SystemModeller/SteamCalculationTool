
-- =============================================
-- Author:		MG System Modeller
-- Create date: 14/07/2018
-- Description:	Pressure band / entropy selection
-- =============================================
CREATE PROCEDURE [dbo].[Steam_Entropy_MPa_Band_bracket] @Pressure_Band_MPa_Lower decimal(18,4),@Pressure_Band_MPa_Upper decimal(18,4), @entropy decimal(18,4)

AS
BEGIN
	SET NOCOUNT ON;
		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			S_kJ_kg <= @entropy 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Lower
		ORDER BY 
			S_kJ_kg 
		DESC 

		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			S_kJ_kg >= @entropy 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Lower
		ORDER BY 
			S_kJ_kg 
		ASC 


		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			S_kJ_kg <= @entropy 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Upper
		ORDER BY 
			S_kJ_kg 
		DESC 

		SELECT TOP 1 Pressure_Band_MPa, Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
			dbo.Steam_Temp_Pressure
		WHERE
			S_kJ_kg >= @entropy 
		AND 
			Pressure_Band_MPa = @Pressure_Band_MPa_Upper
		ORDER BY 
			S_kJ_kg 
		ASC 
END
