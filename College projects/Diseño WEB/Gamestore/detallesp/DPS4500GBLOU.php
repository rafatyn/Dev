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
	
    <body onload="cambiarp(0,1,2,'black','white','','')">
        <div id="ci" style="display: none">PS4500GBLOU/</div>
        <div class="cuerpo" onclick="oc('droplist')">
            <div class="cu_cabecera">
                <div class="nombre">
                    <h1>PS4 500GB + Last of Us</h1>
                </div>
                <div class="imagen">
                    <div class="ip">
                        <div class="img" style="background-image: url('img/PS4500GBLOU/foto1-1.jpg')"><button class="bt" onclick="cambiarp(0,1,2,'black','white','','')"></button></div>
                        <div class="img" style="background-image: url('img/PS4500GBLOU/foto2-1.jpg')"><button class="bt" onclick="cambiarp(0,2,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/PS4500GBLOU/foto3-1.jpg')"><button class="bt" onclick="cambiarp(0,3,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/PS4500GBLOU/foto4-1.jpg')"><button class="bt" onclick="cambiarp(0,4,0,'','','','')"></button></div>
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
                        <h3>385.75 €</h3>
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
                        <div class="est estsi"></div>
                        <div class="est estno"></div>
                    </div>
                    <div class="comprar">
                        <form method="post" action="../cart.php?id=10">
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
                    <h3>PlayStation 4</h3>
                    <ul class="espec">
                        <li>Dimensiones: Aprox 275mm x 53mm x 305mm</li>
                        <li>CPU: x86-64 "Jaguar" de 8 nucleos</li>
                        <li>GPU: AMD Radeon de próxima generación con 1.84 TFLOPS</li>
                        <li>Memoria: 8GB de GDDR5</li>
                        <li>Almacenamiento: Disco duro de 500GB</li>
                        <li>Unidad óptica: Unidad de lectura BD/DVD</li>
                        <li>Puertos: 2x USB 3.0, AUX, HDMI, ÓPTICO</li>
                        <li>Redes: Ethernet (10/100/1000 BASE-T) y WI-FI 802.11 b/g/n</li>
                    </ul>
                    <h3>La caja incluye:</h3>
                    <ul>
                        <li>Playstation 4</li>
                        <li>Videojuego Last of Us GOTY (Game of the Year)</li>
                        <li>Mando inalambrico DUALSHOCK 4</li>
                        <li>Auricular con microfono</li>
                        <li>Cable de alimentación AC</li>
                        <li>Cable HDMI</li>
                        <li>Cable USB</li>
                    </ul>
                </div>
                <div class="cu_carac cu_in">
                    <p>Con PS4 disfrutarás de los videojuegos más alucinantes y trepidantes de esta generación de videoconsolas con una fluidez bestial. Por fuera, la PlayStation 4 disfruta de un diseño soberbio que la convierte en un elemento decorativo. Pero lo importante de esta consola de Sony es su sorprendente interior y sus videojuegos en Full HD. <br><br>
Los números no mienten. La videoconsola Play 4 de 500GB es la consola más potente de la llamada Next Gen al incorporar la última tecnología y aplicarla también a su pad. La interacción de la videoconsola con el pad llega hasta cotas nunca antes vistas en una PlayStation. El Hiperrealismo ha llegado a los juegos de PS4. <br><br>
Los avances tecnológicos permiten a la PS4 hacer cosas sorprendentes. Por ejemplo, que los LED del pad  te avisen del estado de salud de tu personaje, guiar tus movimientos a través del panel táctil. Disfruta del sonido envolvente gracias a sus altavoces integrados. Este pad hace todo esto y además cuenta con todas las virtudes de los anteriores modelos de PlayStation. <br><br>
Y si todo esto te parece poco, comparte tus partidas con tan solo pulsar el botón Share y presume de lo pro que eres jugando con tu PlayStation 4. Puedes jugarlo todo en tu PS4 por las ofertas que PlayStation Plus. <br><br>
Comprar PlayStation 4 es entrar de lleno en un mundo de fantasía, hechizos y espadas, carreras trepidantes, acción a raudales… todos los géneros y los gráficos más hiperrealistas que hayas visto antes están en tu Play 4. <br><br>
Emitir  tus partidas de PS4 en tus juegos favoritos es fácil y puedes hacerlo  directamente en streaming en Twitch o Youtube, echar una mano a tus colegas a pasarse un jefe final podrás hacerlo incluso sin tener el juego. Todo eso y mucho más en tu PlayStation 4 al precio más competente. <br><br>
Y además incluye el Last of Us, para que puedas disfrutar de un viaje que termina en nuestros corazones y una de las experiencias audiovisuales y dentro del third person shooter más férreas que hemos visto y jugado jamás los habituados y los no tan asiduos a videojuegos. <br><br>
Joel y Ellie son ya dos pináculos de las aventuras de acción y sigilo, dos nombres clave en la generación que se despide y la Historia de las consolas en general, dos almas digitales que nos enseñaron una vez más pero como nunca antes por qué Naughty Dog es la mayor baza first party de Sony en materia de exclusivas y por qué su esmero técnico y jugable es envidiado por multitud de creativos y desarrolladoras. <br><br>
The Last of Us es una maravilla en PlayStation 3, y en PlayStation 4 se ha rearmado de alardes gráficos y una oleada de extras para colocar en las tiendas -por unos más que criticados 49,90 euros- esta versión definitiva y GOTY (Game of the Year) que es The Last of Us: Remasterizado. <br><br></p>
                </div>
                <div class="cu_opi cu_in">
                    <div class="opi opiult">
                        <div class="opiimg">
                            <img src="img/user1.png" alt="Usuario"/>
                        </div>
                        <div class="tex">
                            <p>Es la mejor consola de esta generación y la mejor de todo el mercado, junto con el mejor juego de aventuras, para mi compra 100% asegurada.</p>
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
