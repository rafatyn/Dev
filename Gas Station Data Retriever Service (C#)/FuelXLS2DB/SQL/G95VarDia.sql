SELECT DISTINCT min(FH1.Fecha), min(FH2.Fecha), FH1.Municipio, FH1.CodigoPostal, FH1.Direccion, FH1.Gasolina95, FH2.Gasolina95 
from FuelHistory as FH1, FuelHistory as FH2
WHERE DATEPART(dd,FH1.Fecha) = '13' AND DATEPART(mm,FH1.Fecha) = '03' AND DATEPART(yyyy,FH1.Fecha) = '2019'
AND DATEPART(dd,FH2.Fecha) = '13' AND DATEPART(mm,FH2.Fecha) = '03' AND DATEPART(yyyy,FH2.Fecha) = '2019'
AND (FH1.Municipio = 'SAN CRISTÓBAL DE LA LAGUNA' OR FH1.Municipio = 'SANTA CRUZ DE TENERIFE')
AND (FH2.Municipio = 'SAN CRISTÓBAL DE LA LAGUNA' OR FH2.Municipio = 'SANTA CRUZ DE TENERIFE')
AND FH1.CodigoPostal = FH2.CodigoPostal
AND FH1.Direccion = FH2.Direccion
AND CONVERT(NVARCHAR(10),FH1.Fecha,103) = CONVERT(NVARCHAR(10),FH2.Fecha,103)
AND FH1.Fecha < FH2.Fecha
AND FH1.Gasolina95 <> FH2.Gasolina95
GROUP BY FH1.Municipio, FH1.CodigoPostal, FH1.Direccion, FH1.Gasolina95, FH2.Gasolina95;