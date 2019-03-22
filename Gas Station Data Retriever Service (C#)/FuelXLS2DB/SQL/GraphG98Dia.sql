SELECT * FROM (
	SELECT Fecha,Municipio,Localidad,CodigoPostal,Direccion,Rotulo,Latitud,Longitud,AVG(Gasolina98) Gasolina98
	FROM FuelHistory
	WHERE (Municipio = 'SAN CRISTÓBAL DE LA LAGUNA' OR Municipio = 'SANTA CRUZ DE TENERIFE')
	AND DATEPART(dd,Fecha) = '13' AND DATEPART(mm,Fecha) = '03' AND DATEPART(yyyy,Fecha) = '2019'
	GROUP BY Fecha,Municipio,Localidad,CodigoPostal,Direccion,Rotulo,Latitud,Longitud) AS C
WHERE Gasolina98 IS NOT NULL
ORDER BY Gasolina98, Direccion;