SELECT * FROM (
	SELECT SUBSTRING(CONVERT(NVARCHAR(10),Fecha,103),4,7) Fec,Municipio,Localidad,CodigoPostal,Direccion,Rotulo,Latitud,Longitud,AVG(Gasolina98) Gasolina98
	FROM FuelHistory
	WHERE (Municipio = 'SAN CRISTÓBAL DE LA LAGUNA' OR Municipio = 'SANTA CRUZ DE TENERIFE')
	AND DATEPART(yyyy,Fecha) = '2019'
	GROUP BY SUBSTRING(CONVERT(NVARCHAR(10),Fecha,103),4,7),Municipio,Localidad,CodigoPostal,Direccion,Rotulo,Latitud,Longitud) AS C
WHERE Gasolina98 IS NOT NULL
ORDER BY Gasolina98;