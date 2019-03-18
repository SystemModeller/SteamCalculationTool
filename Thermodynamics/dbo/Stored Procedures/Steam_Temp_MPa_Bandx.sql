
-- =============================================
-- Author:		MG System Modeller
-- Create date: 14/07/2018
-- Description:	Pressure band / temp selection
-- =============================================
CREATE PROCEDURE [dbo].[Steam_Temp_MPa_Bandx]

AS
BEGIN
	SET NOCOUNT ON;
		SELECT  * FROM 
			dbo.Steam_Temp_Pressure
		
		--SELECT TOP 1 Temp_K, V_Mass,H_kJ_kg,S_kJ_kg FROM 
		--	dbo.Steam_Temp_Pressure
		--WHERE
		--	Temp_K >= @Temp_K 
		--AND 
		--	Pressure_Band_MPa = @Pressure_Band_MPa
		--ORDER BY 
		--	Temp_K 
		--ASC 
END



