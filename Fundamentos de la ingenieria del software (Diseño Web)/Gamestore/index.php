<!doctype html>

<html lang="es">
	<link rel="stylesheet" type="text/css" href="stylesheet.css">
	<link rel="stylesheet" type="text/css" href="index.css">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
	<script src="js/jquery.js" ></script>
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

	<body>

		<div class="slideshow" onclick="oc('droplist')">
			<img src="img/5.jpg" align="middle">
   			<img src="img/6.jpg" align="middle">
   			<img src="img/7.jpg" align="middle">
		</div>
		<script>
			$(function(){
				$('.slideshow img:gt(0)').hide();
					setInterval(function(){
					$('.slideshow :first-child').fadeOut()
					.next('img').fadeIn()
					.end().appendTo('.slideshow');},
					3000);
			});
		</script>
		
		<!--PRUEBA PARA LA PARTE DE NOVEDADES-->
		<div id="lista_novedades">
			
			<h2 id="titulo_novedades"><strong>ÚLTIMAS NOVEDADES</strong></h2>
			
			<ul class="rig columns-3">
				
				<a href="detallesp/DPS41TB.html"><li>
					<img src="img/consoles/ps4.jpg"/>
					<h3>Sony PS4 Playstation 4 1TB</h3>
					<p>Nuevo modelo, ahora con 1TB de disco duro. Con el doble de capacidad, experimenta hasta dónde puede llegar tu experiencia.</p>
					<p>OFERTA 389€ por tiempo limitado, válido hasta el 15 de Junio de 2016</p>
				</li></a>
				
				<a href=""><li>
					<img src="img/consoles/xbox1.png"/>
					<h3>Microsoft Xbox One 1TB</h3>
					<p>Sumérgete en la experiencia One con el mejor centro multimedia para toda la familia.</p>
					<p>Ahora por sólo 310€. Expande para más información</p>
				</li></a>
					
				<a href=""><li>
					<img src="img/consoles/xbox1elite.jpg"/>
					<h3>Xbox One 1Tb + Controller Elite</h3>
					<p>¿De verdad aún no has probado el nuevo Elite Controller?</p>
					<p>489€</p>
				</li></a>
				
				<a href=""><li>
					<img src="img/games/tw3.jpg"/>
					<p>Sobrevive a la cacería salvaje en la aclamada obra de CD Project Red. Mejor juego por los Video Game Awards 2015.</p>
					<p>44.90€</p>
				</li></a>
				
				<a href=""><li>
					<img src="img/games/fallout4.jpg"/>
					<p>Explora una Boston postapocalíptica en el nuevo RPG de mundo abierto de Bethesda, los creadores de Skyrim y Fallout 3.</p>
					<p>45.95€</p>
				</li></a>
				
				<a href=""><li>
					<img src="img/games/quantb.jpg"/>
					<p>Lo nuevo de Remedy, un trepidante thriller en el que darás forma al tiempo y lo dominarás para sobrevivir.</p>
					<p>54.93€</p>
				</li></a>
				
			</ul>
			
		</div>

	</body>
	
	<footer class="footer">
		 <p><a>&copy; 2016 E-Commerce, Inc. &middot; </a><a href="privacy.html">Privacidad</a> &middot; <a href="#">Términos</a><a style="float: right" href="#">Ir Arriba</a></p>
	</footer>

</html>
