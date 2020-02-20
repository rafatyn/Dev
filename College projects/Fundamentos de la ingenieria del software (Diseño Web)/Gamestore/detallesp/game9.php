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
				<li class="home"><a href="../index.php">Home</a></li>
				<li class="products"><a class="dropdown-toggle" href="#">Productos<span>&#9662;</span></a>
					<ul class="prod-drop dropdown">
						<li><a href="../categories/consoles.php">Consolas</a></li>
						<li><a href="../categories/games.php">Videojuegos</a></li>
						<li><a href="../categories/accesories.php">Accesorios</a></li>
          			</ul>
		  		</li>
		  		<li class="about"><a href="../about.html">Acerca de</a></li>
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
	
    <body onload="cambiarp(0,1,2,'blue','green','','')">
        <div id="ci" style="display: none">Witcher3/</div> <!-- carpeta imagenes -->
        <div class="cuerpo" onclick="oc('droplist')">
            <div class="cu_cabecera">
                <div class="nombre">
                    <h1>The Witcher 3</h1>
                </div>
                <div class="imagen">
                    <div class="ip">
                        <div class="img" style="background-image: url('img/Witcher3/foto1-1.jpg')"><button class="bt" onclick="cambiarp(0,1,2,'blue','green','','')"></button></div>
                        <div class="img" style="background-image: url('img/Witcher3/foto2-1.jpg')"><button class="bt" onclick="cambiarp(0,2,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/Witcher3/foto3-1.jpg')"><button class="bt" onclick="cambiarp(0,3,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/Witcher3/foto4-1.jpg')"><button class="bt" onclick="cambiarp(0,4,0,'','','','')"></button></div>
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
                        <h3>44.90€</h3>
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
                </div>
            </div>
            <div class="cu_barra">
                <li class="bob"><h3>Especificaciones</h3><button onclick="bcol(1,'cu_espec')"></button>
                <li class="bob"><h3>Caracteristicas</h3><button onclick="bcol(2,'cu_carac')"></button>
                <li class="bob"><h3>Opiniones</h3><button onclick="bcol(3,'cu_opi')"></button>
            </div>
            <div class="cu_info">
                <div class="cu_espec cu_in">
                    <h3>Videojuego The Witcher 3</h3>
                    <ul class="espec">
                      <li>Fecha de estreno inicial: 19 de mayo de 2015</li>
                      <li>Desarrollador: CD Projekt RED</li>
                      <li>Adaptación de: Saga del Brujo</li>
                      <li>Distribuidores: CD Projekt, Bandai Namco Games, Spike Chunsoft, Warner Bros. Interactive Entertainment, 1C Company</li>
                      <li>Plataformas: PlayStation 4, Xbox One </li>
                      <li>Nominaciones: Premio BAFTA de Videojuegos al Mejor juego del año</li>.


                    </ul>
                </div>

                <div class="cu_carac cu_in">
                <p>The Witcher: Wild Hunt es un juego de rol de mundo abierto de nueva generación con una apasionante trama, ambientado en un espectacular universo de fantasía lleno de decisiones trascendentales y consecuencias impactantes. Encarnarás a Geralt de Rivia, un cazador de monstruos profesional que tiene que encontrar a la muchacha protagonista de una profecía en un amplio mundo abierto y rebosante de ciudades comerciales, islas con piratas vikingos, peligrosos puertos de montaña y cuevas olvidadas.

                Características: <br>

                Métete en la piel de un cazarrecompensas marginado y curtido <br>
                Adiestrados desde niños y sometidos a mutaciones para adquirir habilidades, fuerza y reflejos sobrehumanos, y aunque se recele de ellos, los brujos sirven de contrapeso en el mundo infestado de monstruos en el cual viven: <br>

                - Descuartiza enemigos metido en la piel de un cazador de monstruos profesional que cuenta con un arsenal de armas que es posible mejorar, pociones para generar mutaciones y hechizos de combate.<br>
                - Caza a un gran número de monstruos exóticos, desde bestias salvajes que merodean en puertos de montaña a astutos depredadores sobrenaturales que acechan en las sombras de urbes populosas.<br>
                - Invierte las recompensas en mejorar las armas y en comprar armaduras personalizadas; o fúndetelas en carreras de caballos, partidas de cartas, peleas a puñetazos y otros placeres que ofrece la noche.<br>

                Explora un mundo fantástico abierto y de moralidad tibia<br>
                Creado para albergar innumerables aventuras, el colosal mundo abierto de The Witcher 3: Wild Hunt alcanza nuevas cotas en cuanto a tamaño, detalle y complejidad:<br>

                - Recorre un mundo abierto fantástico, explora ruinas, cuevas y pecios olvidados, comercia con mercaderes y herreros en las ciudades, y caza en llanuras, montañas y mares.<br>
                - Trata con generales traicioneros, brujas taimadas y aristócratas corruptos mientras ofreces tus siniestros y peligrosos servicios.<br>
                - Repara agravios en un mundo indiferente y al límite donde no existen ni el bien ni el mal, solo las consecuencias.<br>
                - Los ciclos realistas de día y noche y el dinámico sistema meteorológico influyen en el mundo y afectan al comportamiento de los habitantes de las poblaciones y de los monstruos.<br>

                Encuentra a la niña de la profecía<br>
                The Witcher 3: Wild Hunt ofrece una trama independiente inspirada en la mitología eslava tradicional y en arquetipos dramáticos universales:<br>

                - Emprende la misión más trascendental y difícil, la búsqueda de un arma viva cuyo poder profetizaron las antiguas leyendas élficas.<br>
                - Enfréntate a soberanos, espíritus de la naturaleza e incluso a una amenaza de más allá del Velo que está decidida a controlar el mundo.<br>
                - Elige tu destino en un mundo que tal vez no merezca la pena salvar.</p>
                </div>

                <div class="cu_opi cu_in">
                    <div class="opi">
                        <div class="opiimg">
                            <img src="img/user.png" alt="Usurio"/>
                        </div>
                        <div class="tex">
                            <p> Este juego no funciona bien. Es el combate no es nada del otro mundo. Pero eso es todo. Esos son mis únicas quejas </p>
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
                    <div class="opi opiult">
                        <div class="opiimg">
                            <img src="img/user1.png" alt="Usurio"/>
                        </div>
                        <div class="tex">
                          <p> ste juego es absolutamente increíble. Los gráficos son increíbles, especialmente en un televisor 4k, banda de sonido irreal, algunos de la mejor música en un juego que he oído desde la ciudad de Arkham o Red Dead.  </p>
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
                </div>
            </div>
        </div>
    </body>
    <footer><p><a>&copy; 2016 E-Commerce, Inc. &middot; </a><a href="privacy.html">Privacidad</a> &middot; <a href="#">Términos</a><a style="float: right" href="#">Ir Arriba</a></p></footer>
</html>
