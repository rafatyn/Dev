<!DOCTYPE html>
<html lang="es">

    <link rel="stylesheet" type="text/css" href="../stylesheet.css">
	<link rel="stylesheet" type="text/css" href="product.css">
	<link rel="stylesheet" type="text/css" href="../index.css">
	
	<link rel="stylesheet" type="text/css" href="../detallesp/all.css">
    <link rel="stylesheet" type="text/css" href="../stylesheet.css">
    <script src="detalles.js" charset="utf-8"></script>
	
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
	<script src="../js/jquery.js" ></script>
	<meta charset="utf-8"/>
	
	<?php
		ob_start();
		include "../cart.php";
		ob_end_clean();
	?>

	<title class="brand-name">Gamestore</title>
	<header>
		
		<div class="nav">
			<ul class="navbar-elements">
				<li class="home"><a href="../index.php">Home</a></li>
				<li class="products"><a class="dropdown-toggle" href="#">Productos<span>&#9662;</span></a>
					<ul class="prod-drop dropdown">
						<li><a href="consoles.php">Consolas</a></li>
						<li><a href="games.php">Videojuegos</a></li>
						<li><a href="accesories.php">Accesorios</a></li>
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
											<img src="../<?php echo $cart[$i]->image;?>" alt="<?php echo $cart[$i]->name;?>" />
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

								<a href="../cart.php" class="button">Checkout</a>
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
  	
<?php
	
	$id = $_GET["id"];
	$query = sprintf("SELECT * FROM products WHERE id='$id'");
	$results = $mysqli->query($query);

	if($results){
		$product = $results->fetch_assoc();
	}
?>
  	
  	<body onload="cambiarp(0,1,2,'black','white','','')">
        <div id="ci" style="display: none"></div>
        <div class="cuerpo" onclick="oc('droplist')">
            <div class="cu_cabecera">
                <div class="nombre">
                    <h1><?php echo $product[name]; ?></h1>
                </div>
                <div class="imagen">
                    <div class="ip">
                        <div class="img" style="background-image: url('../<?php echo $product[image]; ?>')"><button class="bt" onclick="cambiarp(0,1,2,'black','white','','')"></button></div>
                        <div class="img" style="background-image: url('../<?php echo $product[image]; ?>')"><button class="bt" onclick="cambiarp(0,2,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('../<?php echo $product[image]; ?>')"><button class="bt" onclick="cambiarp(0,3,0,'','','','')"></button></div>
                        <div class="img" style="background-image: url('../<?php echo $product[image]; ?>')"><button class="bt" onclick="cambiarp(0,4,0,'','','','')"></button></div>
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
                        <h3><?php echo $product[price]; ?></h3>
                        <p>/unidad</p>
                    </div>
                    <div class="envio">
                        <div class="disp"></div>
                        <h3>Envío en 24 horas</h3>
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
                        <h3>Valoración:</h3>
                        <div class="est est1 estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estsi"></div>
                        <div class="est estm"></div>
                    </div>
                    <div class="comprar">
                        <form action="../cart.php?id=<?php echo $product[id]; ?>" method="post">
	                        <button type="submit" value="add">Añadir a la Cesta</button>
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
                        <li>Almacenamiento: Disco duro de 1TB</li>
                        <li>Unidad óptica: Unidad de lectura BD/DVD</li>
                        <li>Puertos: 2x USB 3.0, AUX, HDMI, ÓPTICO</li>
                        <li>Redes: Ethernet (10/100/1000 BASE-T) y WI-FI 802.11 b/g/n</li>
                    </ul>
                    <h3>La caja incluye:</h3>
                    <ul>
                        <li>Playstation 4</li>
                        <li>Mando inalambrico DUALSHOCK 4</li>
                        <li>Auricular con microfono</li>
                        <li>Cable de alimentación AC</li>
                        <li>Cable HDMI</li>
                        <li>Cable USB</li>
                    </ul>
                </div>
                <div class="cu_carac cu_in">
                    <p><?php echo $product[description]; ?></p>
                </div>
                <div class="cu_opi cu_in">
                    <div class="opi">
                        <div class="opiimg">
                            <img src="img/user.png" alt="Usurio"/>
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
    		

</body>

	<footer>
		 <p><a>&copy; 2016 E-Commerce, Inc. &middot; </a><a href="../privacy.html">Privacidad</a> &middot; <a href="#">Términos</a><a style="float: right" href="#top">Ir Arriba</a></p>
	</footer>

</html>