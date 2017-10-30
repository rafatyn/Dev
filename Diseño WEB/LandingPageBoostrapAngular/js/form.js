var app = angular.module('myApp', []);

var app = angular.module('myApp', []);
app.directive('myLmail', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attr, mCtrl) {
            function myValidation(value) {
                var arroba = value.indexOf('@');
                var ext = value.lastIndexOf('.');

                if(arroba < 1 || ext - arroba < 2 || value.length - ext < 2 || ext == -1){
                    document.getElementById('lemail').innerHTML = "Formato del correo incorrecto";
                    mCtrl.$setValidity('lmail', false);
                }else{
                    document.getElementById('lemail').innerHTML = "";
                    mCtrl.$setValidity('lmail', true);
                }
                return value;
            }
            mCtrl.$parsers.push(myValidation);
        }
    };
});

app.directive('myLpass', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attr, mCtrl) {
            function myValidation(value) {
                var mayus = 0;
                var num = 0;

                for (var i = 0; i < value.length; i++) {
                    if(value.charCodeAt(i) > 64 && value.charCodeAt(i) < 91){
                        mayus = 1;
                    }else if(value.charCodeAt(i) > 47 && value.charCodeAt(i) < 57){
                        num = 1;
                    }
                }

                if(!mayus){
                    document.getElementById('lepass').innerHTML = "La contraseña debe contener al menos una mayuscula";
                    mCtrl.$setValidity('lpass', false);
                }

                if(!num){
                    document.getElementById('lepass').innerHTML = "La contraseña debe contener al menos un numero";
                    mCtrl.$setValidity('lpass', false);
                }

                if(num&&mayus){
                    document.getElementById('lepass').innerHTML = "";
                    mCtrl.$setValidity('lpass', true);
                }
                return value;
            }
            mCtrl.$parsers.push(myValidation);
        }
    };
});

app.directive('myName', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attr, mCtrl) {
            function myValidation(value) {
                var esp = 0;
                var mayus = 0;
                var tam = 0;

                for (var i = 0; i < value.length; i++) {
                    if(value.charCodeAt(i) < 65 || value.charCodeAt(i) > 122){
                        esp = 1;
                    }
                }
                if(value.length < 2){
                    document.getElementById('ename').innerHTML = "El tamaño del nombre es muy pequeño";
                    mCtrl.$setValidity('name', false);
                    tam = 1;
                }
                if(esp){
                    document.getElementById('ename').innerHTML = "El nombre no puede contener numeros o caracteres especiales";
                    mCtrl.$setValidity('name', false);
                }
                if(value.charCodeAt(0) < 65 || value.charCodeAt(0) > 90){
                    document.getElementById('ename').innerHTML = "La primera letra debe ser mayuscula";
                    mayus = 1;
                    mCtrl.$setValidity('name', false);
                }
                if(!esp&&!mayus&&!tam){
                    document.getElementById('ename').innerHTML = "";
                    mCtrl.$setValidity('name', true);
                }
                return value;
            }
            mCtrl.$parsers.push(myValidation);
        }
    };
});

app.directive('myFname', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attr, mCtrl) {
            function myValidation(value) {
                var esp = 0;
                var mayus = 0;
                var tam = 0;

                for (var i = 0; i < value.length; i++) {
                    if(value.charCodeAt(i) < 65 || value.charCodeAt(i) > 122){
                        esp = 1;
                    }
                }
                if(value.length < 2){
                    document.getElementById('efname').innerHTML = "El tamaño del nombre es muy pequeño";
                    mCtrl.$setValidity('fname', false);
                    tam = 1;
                }
                if(esp){
                    document.getElementById('efname').innerHTML = "El nombre no puede contener numeros o caracteres especiales";
                    mCtrl.$setValidity('fname', false);
                }
                if(value.charCodeAt(0) < 65 || value.charCodeAt(0) > 90){
                    document.getElementById('efname').innerHTML = "La primera letra debe ser mayuscula";
                    mayus = 1;
                    mCtrl.$setValidity('fname', false);
                }
                if(!esp&&!mayus&&!tam){
                    document.getElementById('efname').innerHTML = "";
                    mCtrl.$setValidity('fname', true);
                }
                return value;
            }
            mCtrl.$parsers.push(myValidation);
        }
    };
});

app.directive('myMail', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attr, mCtrl) {
            function myValidation(value) {
                var arroba = value.indexOf('@');
                var ext = value.lastIndexOf('.');

                if(arroba < 1 || ext - arroba < 2 || value.length - ext < 2 || ext == -1){
                    document.getElementById('email').innerHTML = "Formato del correo incorrecto";
                    mCtrl.$setValidity('mail', false);
                }else{
                    document.getElementById('email').innerHTML = "";
                    mCtrl.$setValidity('mail', true);
                }
                return value;
            }
            mCtrl.$parsers.push(myValidation);
        }
    };
});

app.directive('myPass', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attr, mCtrl) {
            function myValidation(value) {
                var mayus = 0;
                var num = 0;

                for (var i = 0; i < value.length; i++) {
                    if(value.charCodeAt(i) > 64 && value.charCodeAt(i) < 91){
                        mayus = 1;
                    }else if(value.charCodeAt(i) > 47 && value.charCodeAt(i) < 57){
                        num = 1;
                    }
                }

                if(!mayus){
                    document.getElementById('epass').innerHTML = "La contraseña debe contener al menos una mayuscula";
                    mCtrl.$setValidity('pass', false);
                }

                if(!num){
                    document.getElementById('epass').innerHTML = "La contraseña debe contener al menos un numero";
                    mCtrl.$setValidity('pass', false);
                }

                if(num&&mayus){
                    document.getElementById('epass').innerHTML = "";
                    mCtrl.$setValidity('pass', true);
                }
                return value;
            }
            mCtrl.$parsers.push(myValidation);
        }
    };
});
