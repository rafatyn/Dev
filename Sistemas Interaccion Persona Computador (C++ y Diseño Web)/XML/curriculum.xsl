<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Variables usadas para calcular la edad -->
	<xsl:variable name="Ano" select="substring(//Fecha,7,4)"/>
	<xsl:variable name="Mes" select="substring(//Fecha,4,2)"/>
	<xsl:variable name="Dia" select="substring(//Fecha,1,2)"/>

	<xsl:template match="/">
		<xsl:apply-templates select="curriculum"/>
	</xsl:template>

	<xsl:template match="curriculum">
		<html>
			<head>
				<!-- FontAwesome -->
				<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css"/>
				<!-- Media screen -->
				<style media="screen">
					@media screen and (min-width: 1300px) {
						#curr {
							width: 65%;
						}
						#exp {
						 	width: 60%;
							display: inline-block;
							margin-left: 5%;
						}
						#contact {
							width: 35%;
							display: inline-block;
						}
					}
					@media screen and (max-width: 1300px) {
						#curr {
							width: 90%;
						}
						#exp {
						 	width: 60%;
							display: inline-block;
							margin-left: 5%;
						}
						#contact {
							width: 35%;
							display: inline-block;
						}
					}
					@media screen and (max-width: 900px) {
						#exp, #contact {
							display: block;
							width: 100%;
							margin-left: 0;
						}
						#exp {
							margin-top: 25px;
						}
						.redes {
							display: inline-block;
							margin-left: 5%;
						}
					}

				</style>
			</head>
			<body style="font: 16px Helvetica, Sans-Serif; padding-top: 50px; background-image: url(data:image/png;base64,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);">
				<div id="curr" style="margin: auto;">
					<h1 style="font-size: 42px; font-weight: bold; border-bottom: 2px solid black;"><xsl:value-of select="titulo"/></h1>
					<xsl:apply-templates select="encabezado"/>
					<xsl:apply-templates select="cuerpo"/>
					<xsl:apply-templates select="js"/>
				</div>
			</body>
		</html>
	</xsl:template>

	<!-- Encabezado -->
    <xsl:template match="encabezado">
		<!-- Imagen personal -->
		<div style="width: 35%; display: inline-block;">
            <img style="width: 80%; max-width: 300px; height: 80%; max-height: 300px; margin: auto; display: block;" alt="Foto"><xsl:attribute name="src"><xsl:value-of select="//foto"/></xsl:attribute></img>
        </div>
		<!-- Datos personales -->
		<div style="width: 60%; min-width: 330px; margin-left: 5%; display: inline-block; vertical-align: top;">
			<!-- Encabezado datos -->
			<div style="margin-bottom: 20px;">
				<div style="float: left;">
					<i class="fa fa-address-card" aria-hidden="true"></i>
					<h2 style="margin: 0 7px; display: inline-block;">Informacion personal</h2>
				</div>
				<div style="overflow: hidden; padding-top: 15px; width: auto;">
					<div style="height: 2px; background-color: black;"></div>
				</div>
			</div>
			<!-- Lista datos personales -->
			<xsl:apply-templates select="datos_personales"/>
		</div>
    </xsl:template>

	<!-- Datos personales -->
    <xsl:template match="datos_personales">
		<ul style="list-style-type: none; padding: 0;">
	         <xsl:for-each select="//datos_personales/*">
				 <xsl:choose>
			          <xsl:when test="name()='Fecha'">
						  <li id="annos" style="margin: 4px 10px;">
							  <xsl:choose>
		 				          <xsl:when test="//js/text()='true'">
									  <b style="font-size: 20px;"><xsl:text>Edad: </xsl:text></b>
								  </xsl:when>
						          <xsl:otherwise>
							  		  <b style="font-size: 20px;"><xsl:text>Fecha de nacimiento: </xsl:text></b><xsl:value-of select="."/>
								  </xsl:otherwise>
						      </xsl:choose>
						  </li>
			          </xsl:when>
			          <xsl:otherwise>
						  <li style="margin: 4px 10px;"><b style="font-size: 20px;"><xsl:value-of select="name()"/><xsl:text>: </xsl:text></b><xsl:value-of select="."/></li>
			          </xsl:otherwise>
			     </xsl:choose>
			 </xsl:for-each>
	    </ul>
    </xsl:template>

	<!-- Cuerpo -->
	<xsl:template match="cuerpo">
		<!-- Contactame y experiencia -->
		<div style="margin: 25px 0;">
			<!-- Contactame -->
			<div id="contact" style="vertical-align: top;">
				<!-- Encabezado contactame -->
				<div style="margin-bottom: 25px;">
					<div style="float: left;">
						<i class="fa fa-envelope" aria-hidden="true"></i>
						<h2 style="margin: 0 7px; display: inline-block;">Contactame</h2>
					</div>
					<div style="overflow: hidden; padding-top: 15px; width: auto;">
						<div style="height: 2px; background-color: black;"></div>
					</div>
				</div>
				<!-- Lista contactame -->
				<xsl:apply-templates select="redes"/>
			</div>
			<!-- Experiencia -->
			<div id="exp">
				<!-- Encabezado experiencia -->
				<div style="margin-bottom: 25px;">
					<div style="float: left;">
						<i class="fa fa-briefcase" aria-hidden="true"></i>
						<h2 style="margin: 0 7px; display: inline-block;">Experiencia laboral</h2>
					</div>
					<div style="overflow: hidden; padding-top: 15px; width: auto;">
						<div style="height: 2px; background-color: black;"></div>
					</div>
				</div>
				<!-- Lista experiencia -->
				<xsl:apply-templates select="experiencia"/>
			</div>
		</div>
		<!-- Formacion -->
		<div style="margin: 25px 0;">
			<!-- Encabezado formacion -->
			<div style="margin-bottom: 25px;">
				<div style="float: left;">
					<i class="fa fa-graduation-cap" aria-hidden="true"></i>
					<h2 style="margin: 0 7px; display: inline-block;">Formacion</h2>
				</div>
				<div style="overflow: hidden; padding-top: 15px; width: auto;">
					<div style="height: 2px; background-color: black;"></div>
				</div>
			</div>
			<!-- Lista formacion -->
			<xsl:apply-templates select="formacion"/>
		</div>
		<!-- Aptitudes -->
		<div style="margin: 25px 0;">
			<!-- Encabezado aptitudes -->
			<div style="margin-bottom: 25px;">
				<div style="float: left;">
					<h2 style="margin: 0 7px; display: inline-block;">Aptitudes</h2>
				</div>
				<div style="overflow: hidden; padding-top: 15px; width: auto;">
					<div style="height: 2px; background-color: black;"></div>
				</div>
			</div>
			<!-- Listas aptitudes -->
			<div style="margin: auto; width: 90%;">
				<xsl:apply-templates select="aptitudes"/>
			</div>
		</div>
	</xsl:template>

	<!-- Formacion -->
	<xsl:template match="formacion">
		<ul style="list-style-type: none; padding: 0; margin-left: 20px;">
			<xsl:for-each select="//formacion/*">
				<xsl:sort data-type="number" select="@ff"/>
				<li style="margin: 3px 0;"><xsl:text>- </xsl:text><xsl:value-of select="."/>
					<xsl:choose>
						<xsl:when test="name()='estudio'">
							<xsl:variable name="Nanos" select="@ff - @fi"/>
							<xsl:value-of select="concat(' iniciado en el año ',@fi,' y concluido en el año ',@ff,'. (',$Nanos,' años)')"/>
						</xsl:when>
						<xsl:when test="name()='curso'">
							<xsl:value-of select="concat(' durante el año ',@ff,'.')"/>
						</xsl:when>
					</xsl:choose>
				</li>
			</xsl:for-each>
		</ul>
	</xsl:template>

	<!-- Experiencia -->
	<xsl:template match="experiencia">
		<ul style="list-style-type: none; padding: 0; margin-left: 20px;">
			<xsl:for-each select="//experiencia/*">
				<xsl:sort data-type="number" select="@fi"/>
				<li style="margin: 3px 0;"><xsl:text>- </xsl:text><xsl:value-of select="concat(.,' desde el año ',@fi)"/>
					<xsl:choose>
						 <xsl:when test="@ff='actual'">
							 <xsl:text> hasta la actualidad.</xsl:text>
						 </xsl:when>
						 <xsl:otherwise>
							 <xsl:variable name="Nanos" select="@ff - @fi"/>
							 <xsl:value-of select="concat(' hasta el año ',@ff,'. (',$Nanos,' años)')"/>
						 </xsl:otherwise>
					</xsl:choose>
				</li>
			</xsl:for-each>
		</ul>
	</xsl:template>

	<!-- Aptitudes -->
	<xsl:template match="aptitudes">
		<xsl:for-each select="//campog">
			<div style="display: inline-block; width: 30%; vertical-align: top; margin-left: 3%;">
				<!-- Icono y nombre de la lista -->
				<i style="margin-right: 5px;" aria-hidden="true"><xsl:attribute name="class"><xsl:value-of select="@icon"/></xsl:attribute></i>
				<p style="display: inline-block; font-style: italic; font-weight: bold; font-size: 18px; margin: 10px 0;"><xsl:value-of select="text()"/></p>
				<ul style="list-style-type: none; padding: 0; margin-left: 20px;">
					<xsl:for-each select="./*">
						<li><xsl:number value="position()" format="I. "/><xsl:value-of select="concat(' ',./text())"/>
							<xsl:if test=".[@c]">
								<xsl:value-of select="concat(' ',@c)"/>
							</xsl:if>
						</li>
					</xsl:for-each>
				</ul>
			</div>
		</xsl:for-each>
	</xsl:template>

	<!-- Redes -->
	<xsl:template match="redes">
		<ul style="list-style-type: none; margin: 0;">
			<xsl:for-each select="//redes/*">
				<li class="redes" style="margin-top: 4px; margin-bottom: 4px;">
					<!-- Icono y enlace -->
					<i style="margin-right: 5px;" aria-hidden="true"><xsl:attribute name="class"><xsl:value-of select="@icon"/></xsl:attribute></i>
					<a style="color: black; text-decoration: none;"><xsl:attribute name="href"><xsl:value-of select="./text()"/></xsl:attribute><xsl:value-of select="name()"/></a>
				</li>
			</xsl:for-each>
		</ul>
	</xsl:template>

	<!-- JS que calcula la edad actual -->
	<xsl:template match="js">
		<script type="text/javascript">
			var d = new Date();
			if(true==<xsl:value-of select="//js/text()"/>){
				if(d.getFullYear()!=<xsl:value-of select="$Ano"/>){
					if((d.getMonth()+1)==<xsl:value-of select="$Mes"/>){
						if(d.getDate()==<xsl:value-of select="$Dia"/>){
							document.getElementById('annos').innerHTML += d.getFullYear()-<xsl:value-of select="$Ano"/> + " años";
						}else if(d.getDate()<xsl:text disable-output-escaping="yes">&lt;</xsl:text><xsl:value-of select="$Dia"/>){
							document.getElementById('annos').innerHTML += (d.getFullYear()-<xsl:value-of select="$Ano"/>)-1 + " años";
						}else{
							document.getElementById('annos').innerHTML += d.getFullYear()-<xsl:value-of select="$Ano"/> + " años";
						}
					}else if((d.getMonth()+1)<xsl:text disable-output-escaping="yes">&gt;</xsl:text><xsl:value-of select="$Mes"/>){
						document.getElementById('annos').innerHTML += d.getFullYear()-<xsl:value-of select="$Ano"/> + " años";
					}else{
						document.getElementById('annos').innerHTML += (d.getFullYear()-<xsl:value-of select="$Ano"/>)-1 + " años";
					}
				}else{
					if((d.getMonth()+1)==<xsl:value-of select="$Mes"/>){
						document.getElementById('annos').innerHTML += d.getDate()-<xsl:value-of select="$Dia"/> + " dias";
					}else{
						document.getElementById('annos').innerHTML += (d.getMonth()+1)-<xsl:value-of select="$Mes"/> + " meses";
					}
				}
			}
		</script>
    </xsl:template>
</xsl:stylesheet>
