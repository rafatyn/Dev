function cambiar (sec, numero, ncolor, color, col1, col2, col3, col4) {
    var cont = numero-1;
    var y = document.getElementsByClassName('bt');
    for(var i=0; i<y.length; i++) {
        y[i].style.boxShadow =  "1px 1px 20px 1px black";
    }
    y[cont].style.boxShadow =  "1px 1px 20px 1px white";

    var col = [col1, col2, col3, col4];
    document.getElementById('bdf').innerHTML = numero;
    document.getElementById('bdc').innerHTML = ncolor;
    document.getElementById('bdcol').innerHTML = col;

    var x = document.getElementsByClassName('cdp');
    for(var i=0; i<ncolor; i++) {
        x[i].style.backgroundColor = col[i];
    }

    numero = sec*4 + Number(numero);
    var bi = "url('" + "img/" + document.getElementById('ci').innerHTML + "foto" + numero + "-" + color + ".jpg" + "')";
    var x = document.getElementsByClassName('ig');
    x[sec].style.backgroundImage = bi;

    var x = document.getElementsByClassName('cd');
    for(var i=0; i<x.length; i++) {
        x[i].style.display =  "none";
    }
    for(var i=0; i<ncolor; i++) {
        x[i].style.display =  "inline-block";
    }
}

function cambiarp (sec, numero, ncolor, col1, col2, col3, col4) {
    cambiar(sec,numero,ncolor,1, col1, col2, col3, col4);
}

function cambiarcol (sec, color) {
    var x = document.getElementById('bdf').innerHTML;
    var y = document.getElementById('bdc').innerHTML;
    var z = document.getElementById('bdcol').innerHTML;
    var h = z.split(",");
    cambiar(sec,x,y,color,h[0],h[1],h[2],h[3]);
}

function bcol (numero, cuadro) {
    var x = document.getElementsByClassName('bob');
    for(var i=0; i<x.length; i++) {
        x[i].style.backgroundColor =  "white";
    }
    x[numero-1].style.backgroundColor = "#ebebeb";

    var x = document.getElementsByClassName('cu_info')
    x[0].style.border = "2px solid #535353";

    var y = document.getElementsByClassName('cu_in');
    for(var i=0; i<y.length; i++) {
        y[i].style.display =  "none";
    }
    var x = document.getElementsByClassName(cuadro);
    x[0].style.display = "block";
}
