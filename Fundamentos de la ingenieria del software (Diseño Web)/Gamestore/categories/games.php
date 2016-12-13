<!DOCTYPE html>
<html lang="es">
	<link rel="stylesheet" type="text/css" href="../stylesheet.css">
	<link rel="stylesheet" type="text/css" href="category.css">
	<link rel="stylesheet" type="text/css" href="../index.css">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
	<script src="../js/jquery.js" ></script>
	<meta charset="utf-8"/>
	
	<?php
		include '../config.php';
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

	<body>
		
		<ul class="rig columns-3" onclick="oc('droplist')">

<?php
include '../config.php';

$query = sprintf("SELECT * FROM `products` WHERE category='games'");
$results = $mysqli->query($query);

if($results){
	while($row = $results->fetch_assoc()){
		echo "<li>";
		echo "<a href='product.php?id=$row[id]'><img src='../$row[image]'>";
		echo "<h3>$row[name]</h3></a>";
		echo "<p>$row[price]€</p>";
		echo "</li>";
	}
}
?>
	
		</ul>

	</body>

	<footer>
		 <p><a>&copy; 2016 E-Commerce, Inc. &middot; </a><a href="../privacy.html">Privacidad</a> &middot; <a href="#">Términos</a><a style="float: right" href="#top">Ir Arriba</a></p>
	</footer>

</html>