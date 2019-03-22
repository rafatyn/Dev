SELECT * FROM (
	SELECT CONVERT(NVARCHAR(10),Fecha,103) Fec,Municipio,Localidad,CodigoPostal,Direccion,Rotulo,Latitud,Longitud,AVG(Gasolina95) Gasolina95
	FROM FuelHistory
	WHERE (Municipio = 'SAN CRISTÓBAL DE LA LAGUNA' OR Municipio = 'SANTA CRUZ DE TENERIFE')
	AND DATEPART(mm,Fecha) = '03' AND DATEPART(yyyy,Fecha) = '2019'
	GROUP BY CONVERT(NVARCHAR(10),Fecha,103),Municipio,Localidad,CodigoPostal,Direccion,Rotulo,Latitud,Longitud) AS C
WHERE Gasolina95 IS NOT NULL
ORDER BY Gasolina95, Direccion;