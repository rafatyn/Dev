var estadistica = [0,0,0,0,0,0];
var showing = false;

function lanzar() {
  var numero = Math.random();
  var dado = document.getElementById("dado");
  for(var i=1; i<7; i++) {
      if(numero<(i/6)) {
          numero = i;
          break;
      }
  }
  estadistica[numero-1]++;
  dado.style.backgroundImage = 'url("dice' + numero + '.png")';

  actEst();
}

function mostrarEst() {
  if(!showing) {
    document.getElementById("bars").style.height = "210px";
    document.getElementById("estadistica").style.height = "240px";
    document.getElementById('showEst').innerHTML = "Ocultar estadistica";
    showing = true;
  }else{
    document.getElementById("bars").style.height = "0px";
    document.getElementById("estadistica").style.height = "80px";
    document.getElementById('showEst').innerHTML = "Mostrar estadistica";
    showing = false;
  }

  actEst();
}

function actEst() {
  var max = 0;
  for(var i=0; i<6; i++){
    if(estadistica[i]>max){
      max=estadistica[i];
    }
  }

  for(var j=0; j<6; j++){
    document.getElementById((j+1) + "bar").style.width = ((270/max)*estadistica[j])+ "px";
    document.getElementById((j+1) + "bar").innerHTML = estadistica[j];
  }
}
