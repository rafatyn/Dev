<!DOCTYPE html>
<html lang="es">
        
    <link rel="stylesheet" type="text/css" href="all.css">
    <link rel="stylesheet" type="text/css" href="../stylesheet.css">
	<link rel="stylesheet" type="text/css" href="../index.css">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
	<script src="detalles.js" charset="utf-8"></script>
	<script src="../js/jquery.js" ></script>
	<meta charset="utf-8"/>
	
	<?php
		include 'config.php';
		ob_start();
		include "cart.php";
		ob_end_clean();
	?>

	<title class="brand-name">Gamestore</title>
	<header>
		
		<div class="nav">
			<ul class="navbar-elements">
				<li class="home"><a href="index.php">Home</a></li>
				<li class="products"><a class="dropdown-toggle" href="#">Productos<span>&#9662;</span></a>
					<ul class="prod-drop dropdown">
						<li><a href="categories/consoles.php">Consolas</a></li>
						<li><a href="categories/games.php">Videojuegos</a></li>
						<li><a href="categories/accesories.php">Accesorios</a></li>
          			</ul>
		  		</li>
		  		<li class="about"><a href="about.html">Acerca de</a></li>
		  		<li class="cart" style="float: right"><a id="cart" href="#"><i class="fa fa-shopping-cart"></i> Carrito</a>
		  			<div class="container">
			  				<div class="shopping-cart">
				  				
			  					<div class="shopping-cart-header">
				  					<div class="shopping-cart-icons">
			  							<i class="fa fa-shopping-cart cart-icon"></i>
			  							<span class="badge"><?php for($i=0; $i<count($cart); $i++){
				  													$n_products += $cart[$i]->quantity;
				  												  }
				  												  echo $n_products;?>
				  						</span>
				  					</div>
			  						<div class="shopping-cart-total">
			  							<span class="lighter-text">Total:</span>
			  							<span class="main-color-text"><?php echo $sum.$currency;?></span>
      								</div>
    							</div> <!--end shopping-cart-header -->

								<ul class="shopping-cart-items">
																		
									<?php
										$cart = unserialize(serialize($_SESSION['cart']));
										for($i=0; $i<count($cart); $i++){
									?>
									
									<li class="clearfix" href="<?php echo $cart[$i]->category;?>.php?id=<?php echo $cart[$i]->id;?>">
										<div class="item-img">
											<img src="<?php echo $cart[$i]->image;?>" alt="<?php echo $cart[$i]->name;?>" />
										</div>
										<div class="item-data">
											<div class="item-name">
												<span><?php echo $cart[$i]->name;?></span>
											</div>
											<div class="item-quan-pri">
												<span class="item-price"><?php echo $cart[$i]->price.$currency;?></span>
												<span class="item-quantity" style="font-size: 13px">Cantidad: <?php echo $cart[$i]->quantity;?></span>
											</div>
										</div>
									</li>
									
									<?php } ?>
									
    							</ul>

								<a href="cart.php" class="button">Checkout</a>
  							</div> <!--end shopping-cart -->
						</div> <!--end container -->
		  		</li>
      		</ul>
    	</div>		  		
  	</header>
  	
  	<script>
		$(function() {
  
			$('.dropdown-toggle').click(function(){
				$(this).next('.dropdown').toggle();
			});

			$(document).click(function(e) {
				var target = e.target;
				if (!$(target).is('.dropdown-toggle') && !$(target).parents().is('.dropdown-toggle')) {
					$('.dropdown').hide();
  				}
			});

		});
  	</script>
  	<script>
	  	(function(){
 
	  		$("#cart").on("click", function() {
	  			$(".shopping-cart").toggle("fast");
  			});
  
		})();
	</script>
	
    <body onload="cambiarp(0,1,3,'black','blue','red','')">
        <div id="ci" style="display: none">NEW3DSXL/</div>
        <div class="cuerpo" onclick="oc('droplist')">
            <div class="cu_cabecera">
                <div class="nombre">
                    <h1>NEW Nintendo 3DS XL</h1>
                </div>
                <div class="imagen">
                    <div class="ip">
                        <div class="img" style="background-image: url('img/NEW3DSXL/foto1-1.jpg')"><button class="bt" onclick="cambiarp(0,1,3,'black','blue','red','')"></button></div>
                        <div class="img" style="background-image: url('img/NEW3DSXL/foto2-1.jpg')"><button class="bt" onclick="cambiarp(0,2,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/NEW3DSXL/foto3-1.jpg')"><button class="bt" onclick="cambiarp(0,3,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/NEW3DSXL/foto4-1.jpg')"><button class="bt" onclick="cambiarp(0,4,0,'','','','')"></button></div>
                    </div>
                    <div class="ig">
                        <div id="bdf" style="display: none"></div>
                        <div id="bdc" style="display: none"></div>
                        <div id="bdcol" style="display: none"></div>
                        <ul class="color">
                            <li class="cd"><div class="cdp"></div><button onclick="cambiarcol(0,1)"></button></li>
                            <li class="cd"><div class="cdp"></div><button onclick="cambiarcol(0,2)"></button></li>
                            <li class="cd"><div class="cdp"></div><button onclick="cambiarcol(0,3)"></button></li>
                            <li class="cd"><div class="cdp"></div><button onclick="cambiarcol(0,4)"></button></li>
                        </ul>
                    </div>
                </div>
                <div class="precio">
                    <div class="mon">
                        <h3>189 €</h3>
                        <p>/unidad</p>
                    </div>
                    <div class="envio">
                        <div class="disp"></div>
                        <h3>Envio en 24 horas</h3>
                    </div>
                    <div class="disponibilidad">
                        <h3>Disponibilidad:</h3>
                        <div class="barradisp">
                            <div class="bdis bdis1 bdissi"></div>
                            <div class="bdis bdis2 bdissi"></div>
                            <div class="bdis bdis3 bdissi"></div>
                            <div class="bdis bdis4 bdisno"></div>
                        </div>
                    </div>
                    <div class="valor">
                        <h3>Valoracion:</h3>
                        <div class="est est1 estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estm"></div>
                        <div class="est estno"></div>
                    </div>
                    <div class="comprar">
                        <form method="post" action="../cart.php?id=4">
                            <button type="sumbit" name="action" value="add" style="width: 100%; background-color: #a18951;"><div class="imgcomprar"></div><h3>Comprar</h3></button>
                        </form>
                    </div>
                </div>
            </div>
            <div class="cu_barra">
                <li class="bob"><h3>Especificaciones</h3><button onclick="bcol(1,'cu_espec')"></button>
                <li class="bob"><h3>Caracteristicas</h3><button onclick="bcol(2,'cu_carac')"></button>
                <li class="bob"><h3>Opiniones</h3><button onclick="bcol(3,'cu_opi')"></button>
            </div>
            <div class="cu_info">
                <div class="cu_espec cu_in">
                    <h3>WII U 32GB</h3>
                    <ul class="espec">
                        <li>Tamaño&nbsp;93,5 mm de alto, 160 mm de ancho y 21,5 mm de grosor (cerrada)</li>
                        <li>Peso&nbsp;Aproximadamente 329 gramos (incluyendo batería, lápiz y tarjeta de memoria microSD)</li>
                        <li>Pantalla superior
                        <ul>
                            <li>Pantalla LCD panorámica en 3D (con 3D superestable)</li>
                            <li>4,88 pulgadas diagonalmente (106,2 mm de ancho x 63,72 mm de alto)</li>
                            <li>800x240 píxeles (400 píxeles por ojo con la función 3D)</li>
                            <li>Puede mostrar 16,77 millones de colores</li>
                        </ul>
                        </li>
                        <li>Pantalla inferior
                        <ul>
                            <li>Pantalla LCD táctil</li>
                            <li>4,18 pulgadas diagonalmente (84,96 mm de ancho x 63,72 mm de alto)</li>
                            <li>320x240 píxeles</li>
                            <li>Puede mostrar 16,77 millones de colores</li>
                        </ul>
                        </li>
                            <li>Lápiz táctil&nbsp;Lápiz de New Nintendo 3DS XL [RED-004] 86 mm</li>
                            <li>Adaptador de corriente/batería
                        <ul>
                            <li>Adaptador de corriente de Nintendo 3DS [WAP-002 (EUR)] (de venta por separado)</li>
                            <li>Batería [SPR-003]</li>
                            <li>Puedes usar el adaptador de corriente suministrado con las consolas Nintendo 3DS/3DS XL/2DS/DSi/DSi XL si ya lo posees, o adquirirlo por separado.</li>
                        </ul>
                        </li>
                        <li>Autonomía de la batería
                        <ul>
                            <li>Entre 3,5 y 7 horas aprox. al usar programas de Nintendo 3DS</li>
                            <li>Entre 7 y 12 horas aprox. al usar programas de Nintendo DS</li>
                            <li>La autonomía de la batería varía dependiendo del brillo de las pantallas. Cuando el brillo automático está activado, el brillo de las pantallas cambia automáticamente en función de la luz que te rodee y, por lo tanto, la batería dura más en sitios oscuros y menos en sitios muy iluminados. Por otra parte, la batería también aumenta su duración cuando está activado el modo de ahorro de energía.</li>
                            <li>Las horas indicadas más arriba representan cálculos aproximados y pueden diferir según el uso.</li>
                        </ul>
                        </li>
                        <li>Tiempo de carga&nbsp;Aproximadamente 3,5 horas</li>
                        <li>Cámara
                        <ul>
                            <li>Cámara interior: 1/Cámara exterior: 2</li>
                            <li>Resolución: 640x480 píxeles (0,3 megapíxeles)</li>
                            <li>Lente: distancia focal fija/Sensor de imagen: CMOS/Píxeles efectivos: aprox. 300 000</li>
                        </ul>
                        </li>
                        <li>Comunicación inalámbrica
                        <ul>
                            <li>Banda de 2,4 GHz (11b: 1-13 ca./11g: 1-11 ca.)</li>
                            <li>Local wireless gameplay and StreetPass function Juego a través de red local inalámbrica y función StreetPass</li>
                            <li>Conexión a internet mediante un punto de acceso inalámbrico (enrutador)</li>
                            <li>Distancia de comunicación recomendada: 30 m (la distancia máxima donde se puede establecer la comunicación puede reducirse dependiendo del entorno)</li>
                        </ul>
                        </li>
                        <li>Controles
                        <ul>
                            <li>Botones A/B/X/Y, cruz de control. Botones L/R, botones ZL/ZR, botones START/SELECT</li>
                            <li>Botón deslizante (entrada analógica de 360º)</li>
                            <li>Palanca C (entrada analógica de 360º)</li>
                            <li>Pantalla táctil</li>
                            <li>Micrófono</li>
                            <li>Cámaras</li>
                            <li>Sensor de aceleración</li>
                            <li>Sensor de giro</li>
                        </ul>
                        </li>
                        <li>Otros controles
                        <ul>
                            <li>Regulador 3D: ajusta la profundidad de las imágenes tridimensionales</li>
                            <li>Botón HOME: muestra el menú HOME</li>
                            <li>Botón POWER</li>
                        </ul>
                        </li>
                            <li>Sensor de aceleración, sensor de giro</li>
                            <li>Sonido&nbsp;Altavoces en estéreo instalados a ambos lados de la pantalla superior (compatible con pseudo-surround)</li>
                            <li>Otras funciones
                        <ul>
                            <li>Comunicación por infrarrojos (comunicación recomendada: distancia de 20 cm)&nbsp;</li>
                            <li>La distancia máxima donde se puede establecer la comunicación puede verse reducida dependiendo del entorno.</li>
                            <li>Sistema de comunicación de corto alcance (NFC)</li>
                        </ul>
                        </li>
                        <li>Entradas y salidas
                        <ul>
                            <li>Ranura para tarjetas de juego</li>
                            <li>Ranura para tarjetas microSD</li>
                            <li>Conector de la base</li>
                            <li>Conector del adaptador de corriente</li>
                            <li>Conector de audio (salida estéreo)</li>
                        </ul>
                        </li>
                        </ul>
                </div>
                <div class="cu_carac cu_in">
                    <p>New 3DS XL supone una vuelta de tuerca en el mundo de las consolas. Un golpe sobre la mesa de Nintendo para demostrar que, desde la Game Boy, sigue siendo la reina de la diversión portátil. Y es que la Nintendo New 3DS XL supone un gran avance con respecto a la Nintendo 3DS. <br><br>
La Nintendo 3DS New XL mejora la velocidad de descarga y de procesado para que no pierdas el tiempo en nimiedades y pases directamente a la acción. Ahora que al comprar Nintendo 3DS tienes la oportunidad de disfrutar de tus Amiibo también en esta consola Nintendo. <br><br>
Juega con tus personajes favoritos con tan solo acoplar su base a tu consola y descubre la forma en que interactúan con tus juegos. ¿Has probado a Link en el Super Mario?  ¡A qué esperas! Experimenta una nueva forma de jugar gracias a la incorporación de nuevos botones laterales y las mejoras de la pantalla y los controles. <br><br>
La Visualizacion 3D ha sido mejorada en la Nintendo 3DS New XL para cansar menos la vista y gracias a su cámara inferior ajusta en tiempo real en ángulo para que la experiencia de juego sea plena por mucho que te muevas. Además, podrás personalizarla con las distintas cubiertas intercambiables especialmente diseñadas para New 3DS Precio de escándalo y diversión sin fin van de la mano en esta consola portátil de Nintendo. <br><br></p>
                </div>
                <div class="cu_opi cu_in">
                    <div class="opi">
                        <div class="opiimg">
                            <img src="img/user.png" alt="Usuario"/>
                        </div>
                        <div class="tex">
                            <p>Es un gran producto que te va a aportar horas de diversión solo o en compañia, no me ha fallado nunca por lo que por mi producto de 10.</p>
                            <div class="reco">
                                <h3>Recomendarias este producto:</h3>
                                <div class="disp"></div>
                            </div>
                            <div class="valor">
                                <h3>Valoracion:</h3>
                                <div class="est est1 estsi"></div>
                                <div class="est estsi"></div>
                                <div class="est estsi"></div>
                                <div class="est estsi"></div>
                                <div class="est estno"></div>
                            </div>
                        </div>
                        <div class="opibar"></div>
                    </div>
                    <div class="opi opiult">
                        <div class="opiimg">
                            <img src="img/user1.png" alt="Usurio"/>
                        </div>
                        <div class="tex">
                            <p>Es la mejor consola de esta generación y la mejor de todo el mercado, para mi compra 100% asegurada.</p>
                            <div class="reco">
                                <h3>Recomendarias este producto:</h3>
                                <div class="disp"></div>
                            </div>
                            <div class="valor">
                                <h3>Valoracion:</h3>
                                <div class="est est1 estsi"></div>
                                <div class="est estsi"></div>
                                <div class="est estsi"></div>
                                <div class="est estm"></div>
                                <div class="est estno"></div>
                            </div>
                        </div>
                        <div class="opibar"></div>
                    </div>
                </div>
            </div>
        </div>
    </body>
    <footer><p><a>&copy; 2016 E-Commerce, Inc. &middot; </a><a href="privacy.html">Privacidad</a> &middot; <a href="#">Términos</a><a style="float: right" href="#">Ir Arriba</a></p></footer>
</html>
