<?php
	session_start();
	include 'config.php';
	include 'item.php';
	
	if (isset($_POST['action']) || isset($_GET['id'])){
		$action = $_POST['action'];
		$id = $_GET['id'];
		$cart = unserialize(serialize($_SESSION['cart']));
		
		if (isset($_POST['quantity'])) {
			for($i=0; $i<count($cart); $i++)
					if ($cart[$i]->id == $id){
						$cart[$i]->quantity = $_POST['quantity'];
						$_SESSION['cart'] = $cart;
						break;
					}
		}
		if ($action == 'delete'){
			for($i=0; $i<count($cart); $i++){
				if($cart[$i]->id == $id){
					unset($cart[$i]);
					$cart = array_values($cart);
					$_SESSION['cart'] = $cart;
					break;
				}
			}
		}
		else if ($action == 'add'){
			echo "hole";
			$cart = unserialize(serialize($_SESSION['cart']));
			if (in_array($item, $_SESSION['cart'])){
				
				for($i=0; $i<count($cart); $i++)
					if ($cart[$i]->id == $item->id)
						break;
						
				if (isset($_POST['quantity']))
					$cart[$i]->quantity = $_POST['quantity'];
				else
					$cart[$i]->quantity++;
				
			}
			else {
				$product = $mysqli->query("SELECT * FROM products WHERE id = '$id'")->fetch_object();
		
				$item = new Item();
				$item->id = $product->id;
				$item->name = $product->name;
				$item->category = $product->category;
				$item->image = $product->image;
				$item->price = $product->price;
				$item->url = $product->url;
				$item->quantity = 1;
				
				$_SESSION['cart'][] = $item;
				
			}
		}
	}
	
	
?>
<!DOCTYPE html>
<html lang="es">
	
    <link rel="stylesheet" type="text/css" href="stylesheet.css">
	<link rel="stylesheet" type="text/css" href="cart.css">
	<link rel="stylesheet" type="text/css" href="index.css">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
	<script src="js/jquery.js" ></script>
	<meta charset="utf-8"/>
	

	<title class="brand-name">Carrito de Compra</title>
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
	<div class="container">
	<table id="cart-page" cellspacing="0" cellpadding="4">
    				<thead>
						<tr class="columns">
							<th style="width:0%; text-align: left">Producto</th>
							<th style="width:10%">Precio</th>
							<th style="width:8%">Cantidad</th>
							<th style="width:22%" class="text-center">Subtotal</th>
							<th style="width:10%"></th>
						</tr>
					</thead>
					<tbody>
						<?php
								$cart = unserialize(serialize($_SESSION['cart']));
								for($i=0; $i<count($cart); $i++){ 
									$sum += $cart[$i]->price * $cart[$i]->quantity;
							?>
						<tr class="content">
							<td class="product">
								<div class="row">
									<div class="product-image"><img src="<?php echo $cart[$i]->image;?>" class="img-responsive"></div>
									<div class="text-column">
										<h3 class="product-name"><?php echo $cart[$i]->name;?></h3>
									</div>
								</div>
							</td>
							<td class="product-price"><?php echo $cart[$i]->price;?></td>
							<td class="product-quantity">
								<form action="cart.php?id=<?php echo $cart[$i]->id; ?>" method="post">
									<input type="text" name="quantity" autocomplete="off" value="<?php echo $cart[0]->quantity; ?>" />
								</form>
							</td>
							<td class="product-subtotal" class="text-center"><?php echo $cart[$i]->price * $cart[$i]->quantity;?></td>
							<td class="options">
								<form action="cart.php?id=<?php echo $cart[$i]->id; ?>" method="post">
									<button type="submit" name="action" value="delete"></button>
								</form>
							</td>
							
							
						</tr>
						<?php } ?>
					</tbody>
					<tfoot>
						<tr>
							<td><a href="index.php" class="myButton1">Continuar Comprando</a></td>
							<td colspan="2" class="hidden-xs"></td>
							<td class="hidden-xs text-center"><strong>Total <?php echo $sum." ".$currency; ?></strong></td>
							<td><a href="#" class="btn btn-success btn-block myButton2">Checkout</a></td>
						</tr>
					</tfoot>
				</table>
	</div>
</html>