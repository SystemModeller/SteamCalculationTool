CREATE TABLE [dbo].[Steam_Temp_Pressure] (
    [Steam_ID]          INT             IDENTITY (1, 1) NOT NULL,
    [Pressure_Band_MPa] DECIMAL (18, 4) NULL,
    [Temp_K]            DECIMAL (18, 3) NULL,
    [V_Mass]            NUMERIC (18, 5) NULL,
    [H_kJ_kg]           DECIMAL (18, 1) NULL,
    [S_kJ_kg]           DECIMAL (18, 4) NULL,
    [Data_Type]         INT             NULL
);

