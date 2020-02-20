(function(){
 
  $("#cart").on("click", function() {
    $(".shopping-cart").fadeToggle( "fast");
  });
  
})();

function toggleMenu(menu){
    if(document.getElementById(menu).style.display == 'none'){
	    document.getElementById(menu).style.display = 'block';
    }else{
        document.getElementById(menu).style.display = 'none';
    }
}

function initMap() {
    var mapDiv = document.getElementById('map');
    var map = new google.maps.Map(mapDiv, {
      center: {lat: 28.482785, lng: -16.321384},
      zoom: 17
    });
}

function oc(menu) {
  document.getElementById(menu).style.display='none';
}
