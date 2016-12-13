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
  	
    <body onload="cambiarp(0,1,4,'#ff0ff3','#0fbfff','#00a811','#ff841f')">
        <div id="ci" style="display: none">RazerKraken/</div> <!-- carpeta imagenes -->
        <div class="cuerpo" onclick="oc('droplist')">
            <div class="cu_cabecera">
                <div class="nombre">
                    <h1>Razer-KRAKEN MOBILE</h1>
                </div>
                <div class="imagen">
                    <div class="ip">
                        <div class="img" style="background-image: url('img/RazerKraken/foto1-1.jpg')"><button class="bt" onclick="cambiarp(0,1,4,'#ff0ff3','#0fbfff','#00a811','#ff841f')"></button></div>
                        <div class="img" style="background-image: url('img/RazerKraken/foto2-1.jpg')"><button class="bt" onclick="cambiarp(0,2,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/RazerKraken/foto3-1.jpg')"><button class="bt" onclick="cambiarp(0,3,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('img/RazerKraken/foto4-1.jpg')"><button class="bt" onclick="cambiarp(0,4,0,'','','','')"></button></div>
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
                        <h3>74.90€</h3>
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
                        <div class="est estsi"></div>
                        <div class="est estno"></div>
                    </div>
                    <div class="comprar">
                        <div class="imgcomprar"></div>
                        <h3>Comprar</h3>
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
                    <h3>Auticulares Razer-Kraken Mobile</h3>
                    <ul class="espec">
                      <li>Respuesta de frecuencia: 20 - 20.000 Hz</li>
                      <li>Impedancia: 32 Ω a 1 kHz</li>
                      <li>Sensibilidad (@1 kHz, 1 V/Pa): 110 ± 4 dB a 1 kHz máx.</li>
                      <li>Potencia de entrada: 50 mW</li>
                      <li>Transductores: 40 mm, con imanes de neodimio</li>
                      <li>Diámetro interno de cada auricular: 50 mm / 0,16”</li>
                      <li>Longitud del cable: 1,3 m / 4,27 pies</li>
                      <li>Peso aproximado: 315 g / 0,69 lb</li>
                      <li>Conector: analógico con clavija de 3,5 mm</li>

                    </ul>
                    <h3>Especificaciones de micrófono:</h3>
                    <ul>
                        <li>Respuesta de frecuencia: 100 - 10.000 Hz</li>
                        <li>Relación señal-ruido: 55 dB</li>
                        <li>Sensibilidad (@1 kHz, 1 V/Pa): -42 ± 3dB</li>
                        <li>Patrón de captación: Omnidireccional</li>
                        <li>Control remoto en línea</li>
                        <li>Botón central de control remoto</li>
                    </ul>
                </div>
                <div class="cu_carac cu_in">
                    <p>Creado como el accesorio perfecto para un estilo de vida dinámico, el Razer Kraken Mobile te ofrece una impresionante calidad de audio en un formato realmente móvil.<br> Estos auriculares son resistente y ligeros, se han fabricado para Apple™ iOS e incluyen controles de micrófono en línea y multimedia para darte fácil acceso a todas las características que necesitas cuando estás en movimiento.</br>

Debajo del llamativo neón, el Razer Kraken Mobile integra potentes transductores de alta calidad dentro de cómodas almohadillas circumaurales de tamaño extragrande. Esto te permite disfrutar de una experiencia de audio inmersiva, con un diseño exterior que no dejará indiferente a nadie.</p>
                </div>
                <div class="cu_opi cu_in">
                    <div class="opi">
                        <div class="opiimg">
                            <img src="img/user.png" alt="Usurio"/>
                        </div>
                        <div class="tex">
                            <p>El audio es muy bueno y los colores hacen que su diseño sea muy bonito.</p>
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
                                <div class="est estsi"></div>
                            </div>
                        </div>
                        <div class="opibar"></div>
                    </div>
                    <div class="opi opiult">
                        <div class="opiimg">
                            <img src="img/user1.png" alt="Usurio"/>
                        </div>
                        <div class="tex">
                            <p>Tenía que cambiar mis auriculares y me recomendaron estos.Es la mejor elección que podría haber hecho.</p>
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
                                <div class="est estm"></div>
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
