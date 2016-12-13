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
	
    <body onload="cambiarp(0,1,4,'black','blue','grey','white')">
        <div id="ci" style="display: none">XBOXONE1TB/</div>
        <div class="cuerpo" onclick="oc('droplist')">
            <div class="cu_cabecera">
                <div class="nombre">
                    <h1>XBOX ONE 1TB</h1>
                </div>
                <div class="imagen">
                    <div class="ip">
                        <div class="img" style="background-image: url('img/XBOXONE1TB/foto1-1.jpg')"><button class="bt" onclick="cambiarp(0,1,4,'black','blue','grey','white')"></button></div>
                        <div class="img" style="background-image: url('img/XBOXONE1TB/foto2-1.jpg')"><button class="bt" onclick="cambiarp(0,2,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/XBOXONE1TB/foto3-1.jpg')"><button class="bt" onclick="cambiarp(0,3,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/XBOXONE1TB/foto4-1.jpg')"><button class="bt" onclick="cambiarp(0,4,0,'','','','')"></button></div>
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
                        <h3>310 €</h3>
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
                            <div class="bdis bdis4 bdissi"></div>
                        </div>
                    </div>
                    <div class="valor">
                        <h3>Valoracion:</h3>
                        <div class="est est1 estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estno"></div>
                        <div class="est estno"></div>
                    </div>
                    <div class="comprar">
                        <form method="post" action="../cart.php?id=2">
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
                    <h3>XBOX ONE 1TB</h3>
                    <ul class="espec">
                        <li>CPU: 8 nucleos</li>
                        <li>Memoria: 8GB de RAM</li>
                        <li>Almacenamiento: Disco duro de 1TB</li>
                        <li>Unidad óptica: Unidad de lectura Blu-Ray</li>
                        <li>Puertos: USB 3.0, HDMI</li>
                        <li>Redes: Ethernet (10/100/1000 BASE-T) y WI-FI 802.11 b/g/n</li>
                    </ul>
                    <h3>La caja incluye:</h3>
                    <ul>
                        <li>XBOX ONE 1TB</li>
                        <li>Mando inalambrico de XBOX ONE</li>
                        <li>Cable de alimentación AC</li>
                        <li>Cable HDMI</li>
                        <li>Cable USB</li>
                    </ul>
                </div>
                <div class="cu_carac cu_in">
                    <p>Xbox One es una videoconsola dispuesta a ofrecerte miles de horas de diversión en épicas aventuras y trepidantes partidas multijugador en la plataforma de juegos más avanzada de la next gen. Disfruta de los mejores juegos y grandes exclusivas en tu consola Xbox One y sé la envidia de tus amigos. <br><br>
Microsoft ha diseñado esta Xbox One pensando en los jugadores, encontrando el equilibrio perfecto entre potencia y rendimiento gráfico. Flípalo con el hiperrealismo de la nueva generación de videojuegos y con la avanzada IA de tus enemigos. ¡El mayor reto será que logres separarte de ella!. <br><br>
Varios millones de jugadores repartidos por todo el mundo, más de 300.00 servidores y una extensa historia proporcionando grandes experiencias multijugador con Xbox Live, convierten a Xbox One en la consola por excelencia para jugar. Disfruta de un sistema de emparejamientos mejorado, con menos esperas y un rendimiento aumentado con Xbox Live en tu Xbox One. ¡Podrás grabar, emitir y compartir tus mejores partidas con todo el mundo! Además, todos los miembros de la familia podrán disfrutar del multijugador con una suscripción Gold. <br><br>
Xbox One cuenta con un extenso catálogo de juegos y aúna en una misma videoconsola un gran número de opciones de ocio para que no tengas que salir de tu salón para poder disfrutarlo todo. ¿Quieres ver películas? ¿escuchar música? ¿ver la TV o llamar por Skype?. Si la respuesta es sí, no dudes en comprar Xbox One y convertirla en la piedra angular de tu diversión. La consola no deja de recibir nuevas actualizaciones, por lo que a las funcionalidades que ya conoces, se irán uniendo otras nuevas, más contenidos y prestaciones para que tu diversión no tenga fin. <br><br>
Bajo un diseño plagado de rectas, aristas y plástico negro. Se esconde toda una serie de innovaciones y características dispuestas a ofrecer la mejor experiencia al usuario. En Xbox One decimos adiós a la bandeja para discos – sustituida por una práctica y cómoda ranura – y nos encontramos con una más que eficiente – sorprendentemente silenciosa – ventilación. <br><br>
En cuanto al apartado técnico, encontramos que monta un Procesador AMD Jaguar de 8 núcleos. Capaz de mover con fluidez todo tipo de entornos virtuales en alta definición gracias a su GPU AMD 7000 Series, nos adentraremos en una experiencia Full HD nunca antes vista en una consola. Sus 8GB de RAM DDR3 nos asegurarán que los tiempos de carga sean inexistentes y que podamos tirar a tope con todo el catálogo de la videoconsola. Con un disco duro de 1TB tendrás más que suficiente para tus juegos y partidas. <br><br>
Esta consola Xbox One es la única en la que puedes reanudar tu partida justo en el momento que lo dejaste, da igual que la apagues. También podrás pasar tus partidas al PC o a una Tablet con Windows 10 y continuar con tu partida en cualquier parte de tu casa. Además, cuenta con la novedosa tecnología Kinect y el mando más potente del sector. <br><br>
Accede anticipadamente a todos los juegos de EA antes de su lanzamiento para el resto de plataformas gracias al EA Access. Disfruta de juegazos como Fallout 4 y los mejores exclusivos: Halo 5: Guardians, Gears of War: Ultimate Edition, o Rise of the Tomb Raider, por mencionar algunos. Comparte tu tiempo de juego con amigos a través de Xbox Live y dale una segunda vida a tus juegos de la consola Xbox 360 en Xbox One. Ponte al día comprando tu Xbox One al mejor precio y sigue disfrutando de tus juegos favoritos de la generación anterior. ¡Mata dos pájaros de un tiro!. <br><br></p>
                </div>
                <div class="cu_opi cu_in">
                    <div class="opivac">No hay opiniones de este producto</div>
                </div>
            </div>
        </div>
    </body>
    <footer><p><a>&copy; 2016 E-Commerce, Inc. &middot; </a><a href="privacy.html">Privacidad</a> &middot; <a href="#">Términos</a><a style="float: right" href="#">Ir Arriba</a></p></footer>
</html>
