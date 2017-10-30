function comprobar() {

    document.getElementById('ename').innerHTML = "";
    document.getElementById('email').innerHTML = "";
    document.getElementById('epass').innerHTML = "";
    
    var name = document.getElementById('name').value;

    for (var i = 0; i < name.length; i++) {
        if(name.charCodeAt(i) < 65 || name.charCodeAt(i) > 122){
            document.getElementById('ename').innerHTML = "El nombre no puede contener numeros o caracteres especiales";
            return false;
        }
    }
    if(name.charCodeAt(0) < 65 || name.charCodeAt(0) > 90){
        document.getElementById('ename').innerHTML = "La primera letra debe ser mayuscula";
        return false;
    }

    var mail = document.getElementById('mail').value;

    var arroba = mail.indexOf('@');
    var ext = mail.lastIndexOf('.');

    if(arroba < 1 || ext - arroba < 2 || mail.length - ext < 2 || ext == -1){
        document.getElementById('email').innerHTML = "Formato del correo incorrecto";
        return false;
    }

    var pass = document.getElementById('pass').value;
    var mayus = 0;
    var num = 0;

    for (var i = 0; i < pass.length; i++) {
        if(pass.charCodeAt(i) > 64 && pass.charCodeAt(i) < 91){
            mayus = 1;
        }else if(pass.charCodeAt(i) > 47 && pass.charCodeAt(i) < 57){
            num = 1;
        }
    }
    if(!mayus){
        document.getElementById('epass').innerHTML = "La contraseña debe contener al menos una mayuscula";
        return false;
    }
    if(!num){
        document.getElementById('epass').innerHTML = "La contraseña debe contener al menos un numero";
        return false;
    }

    return true;
}
