//Variable global de fecha
var date = new Date();

//Vectores de conocimiento
var diasMes = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31];
var mesesAno = [31,28,31,30,31,30,31,31,30,31,30,31];
var mesesAnoBisiesto = [31,29,31,30,31,30,31,31,30,31,30,31];
var mesesNombre = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
var mesesNombreEsp = ["Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"];

//Pintar HTML
var calendar = document.getElementById('calendar');
calendar.innerHTML = '<div id="calendarEncabezado"><button id="calendarToday" onclick="IrHoy()">Hoy</button><button id="calendarMonthPrev" onclick="uptMonth(-1)">Anterior</button><div id="calendarMonthName"></div><button id="calendarMonthNext" onclick="uptMonth(1)">Siguiente</button></div><div class="semanas"><div class="titsem"><div class="day name">Lunes</div><div class="day name">Martes</div><div class="day name">Miercoles</div><div class="day name">Jueves</div><div class="day name">Viernes</div><div class="day name">Sabado</div><div class="day name">Domingo</div></div>';

var day=1;
for(var i=0; i<6; i++) {
    var sem = document.createElement('div');
    sem.id = "sem" + i;
    sem.className = "sem";
    calendar.appendChild(sem);
    for (var j=0; j<7 ; j++, day++) {
        sem.innerHTML += '<div class="day" id="d' + day + '"></div>';
    }
    calendar.innerHTML += '</div>';
}

//Rellenar  datos calendario
dibujarCalendario(1);

//Get pos de vector circular
function getEleVec(vec,pos) {
    if(pos<0){
        return vec[(vec.length+pos)];
    }else{
        return vec[pos];
    }
}

function dibujarCalendario(dibujaHoy) {
    //Calculo variables imporatantes de la fecha
    var fecha = date.toDateString();
    var diaMes = fecha.slice(8,10);
    var diaSemanaNum = date.getDay()-1;
    var mesNum = date.getMonth();
    var ano = date.getFullYear();
    var comienzo = diaSemanaNum - ((diaMes%7)-1);
    //Comprobacion es dia de primera semana
    if(comienzo<0){
        comienzo = 7 + comienzo;
    }
    //Relleno encabezado
    document.getElementById('calendarMonthName').innerHTML = getEleVec(mesesNombreEsp, mesNum) + ' ' + ano;

    //Relleno de numeros del calendario
    var indice = 0 - diaSemanaNum;
    //Selecciona las semanas
    for(var j=0; j<6; j++){
        var NumSemana = 'sem' + j;
        var DiasSemana = document.getElementById(NumSemana);
        if(j==5) var dy = [0,0,0,0,0,0,0];
        //Selecciona los dias
        for(var i=indice; i<(indice+7); i++){
            var dia = DiasSemana.childNodes[i+diaSemanaNum];
            var NumTemp = ((j*7)+(i+diaSemanaNum))-(comienzo-1);

            //Comprobacion de año bisiesto
            if((ano%4==0&&ano%100!=0)||(ano%100==0&&ano%400==0)){
                if(j==0){
                    //Comprobacion de dias anteriores al mes
                    if((i+diaSemanaNum)<comienzo){
                        dia.innerHTML = (getEleVec(mesesAnoBisiesto, mesNum-1) - ((comienzo-1)-(i+diaSemanaNum)));
                        dia.classList.add('disable');
                        if (j==5) dy[i-indice] = 0;
                    }else{
                        dia.innerHTML = NumTemp;
                        dia.classList.remove('disable');
                        if (j==5) dy[i-indice] = 1;
                    }
                }else {
                    //Comprobacion de dias siguientes al mes
                    if(NumTemp<=mesesAnoBisiesto[mesNum]){
                        dia.innerHTML = NumTemp;
                        dia.classList.remove('disable');
                        if (j==5) dy[i-indice] = 1;
                    }else{
                        dia.innerHTML = NumTemp%getEleVec(mesesAnoBisiesto, mesNum);
                        dia.classList.add('disable');
                        if (j==5) dy[i-indice] = 0;
                    }
                }
            }else{
                if(j==0){
                    if((i+diaSemanaNum)<comienzo){
                        dia.innerHTML = (getEleVec(mesesAno, mesNum-1) - ((comienzo-1)-(i+diaSemanaNum)));
                        dia.classList.add('disable');
                        if (j==5) dy[i-indice] = 0;
                    }else{
                        dia.innerHTML = NumTemp;
                        dia.classList.remove('disable');
                        if (j==5) dy[i-indice] = 1;
                    }
                }else {
                    if(NumTemp<=mesesAno[mesNum]){
                        dia.innerHTML = NumTemp;
                        dia.classList.remove('disable');
                        if (j==5) dy[i-indice] = 1;
                    }else{
                        dia.innerHTML = NumTemp%getEleVec(mesesAno, mesNum);
                        dia.classList.add('disable');
                        if (j==5) dy[i-indice] = 0;
                    }
                }
            }
        }
        if(j==5) {
            var dis = false;
            dy.forEach(function(e){
                if(e) dis=true;
            });
            if(!dis) {
                DiasSemana.style.display = "none";
            } else {
                DiasSemana.style.display = "block";
            }
        }
    }

    //Resalta el dia de hoy
    if(dibujaHoy){
        //Selecciona el dia de hoy
        var Hoy = document.getElementsByClassName('day');
        Hoy = Hoy[(6 + parseInt(diaMes) + comienzo)];
        Hoy.style.backgroundColor = '#ffffff';

        var temp, g, b, idb;
        //Inicia el resaltado
        var ids = setInterval(subirColor, 20);

        //Cambia entre intervalos
        function changeInterval(){
            clearInterval(ids);
            idb = setInterval(bajarColor, 20);
        }
        var InitColor = Hoy.style.backgroundColor;
        //Pinta el color
        function subirColor() {
            //Coge el color actual
            temp = Hoy.style.backgroundColor;
            temp = temp.replace('rgb(','').replace(')','').replace(' ','').split(',');
            //Guarda el canal verde y azul
            g = parseInt(temp[1]);
            b = parseInt(temp[2]);
            if(g==15&&b==15) {
                changeInterval();
            }else{
                g -= 16;
                b -= 16;
                //Se convierte a hexadecimal
                b = b.toString(16);
                if(b.length==1){
                    b = '0' + b.toString(16);
                }
                g = g.toString(16);
                if(g.length==1){
                    g = '0' + g.toString(16);
                }

                Hoy.style.backgroundColor = '#ff' + g + b;
            }
        }

        //Borra el color
        function bajarColor() {
            temp = Hoy.style.backgroundColor;
            temp = temp.replace('rgb(','').replace(')','').replace(' ','').split(',');
            g = parseInt(temp[1]);
            b = parseInt(temp[2]);
            if(g==255&&b==255) {
                Hoy.style.backgroundColor = InitColor;
                clearInterval(idb);
            }else{
                g += 16;
                b += 16;

                b = b.toString(16);
                if(b.length==1){
                    b = '0' + b.toString(16);
                }
                g = g.toString(16);
                if(g.length==1){
                    g = '0' + g.toString(16);
                }

                Hoy.style.backgroundColor = '#ff' + g + b;
            }
        }
    }
}

//Aumentar o disminuir el mes
function uptMonth(uptVal) {
    var mesNuevo;
    var anoNuevo = date.getFullYear();

    //Cambio de año
    if(date.getMonth()==0&&uptVal==-1){
        mesNuevo = 12;
        anoNuevo = date.getFullYear()-1;
    }else if(date.getMonth()==11&&uptVal==1){
        mesNuevo = 1;
        anoNuevo = date.getFullYear()+1;
    }else{
        mesNuevo = date.getMonth()+uptVal+1;
    }

    //Crear nueva fecha
    var fechaNueva = anoNuevo + '-' + mesNuevo + '-' + '1';
    date = new Date(fechaNueva);

    //Dibuja el calendario
    dibujarCalendario(0);
}

//Boton que te lleva al dia de hoy
function IrHoy() {
    date = new Date();

    dibujarCalendario(1);
}
