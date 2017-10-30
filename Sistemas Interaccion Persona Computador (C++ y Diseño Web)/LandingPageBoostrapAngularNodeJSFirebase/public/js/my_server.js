(function() {

    var config = {
       apiKey: "AIzaSyC4U73XLz12loZiwND4Js-Y_MLlRFtF2i4",
       authDomain: "prueba-742e7.firebaseapp.com",
       databaseURL: "https://prueba-742e7.firebaseio.com",
       storageBucket: "prueba-742e7.appspot.com",
       messagingSenderId: "330943010990"
     };
     firebase.initializeApp(config);

    angular
        .module('myApp', ['firebase'])
        .controller('MyCtrl', MyCtrl);

        function MyCtrl($firebaseObject) {
            const rootRef = firebase.database().ref().child('messages');
            this.auth($firebaseObject);
        }

        MyCtrl.prototype.login = function () {
            const email = this.object.lmail;
            const pass = this.object.lpass;

            console.log(email);
            console.log(pass);

            const auth = firebase.auth();

            if(document.getElementById('lepass').innerHTML == "" && document.getElementById('lemail').innerHTML == "") {
                auth.signInWithEmailAndPassword(email,pass)
                .then(e => {
                    document.getElementById('login').classList.remove('active');
                    document.getElementById('results').classList.add('active');
                    document.getElementById('nlog').classList.remove('active');
                    document.getElementById('nres').classList.add('active');
                    this.loadms();
                })
                .catch(er => {
                        if(er.message == "There is no user record corresponding to this identifier. The user may have been deleted."){
                            document.getElementById('lemail').innerHTML = "El email es incorrecto";
                        }else if(er.message == "The password is invalid or the user does not have a password."){
                            document.getElementById('lepass').innerHTML = "La contraseña es incorrecta";
                        }
                    });
            }
        };

        MyCtrl.prototype.reg = function () {
            const email = this.object.mail;
            const pass = this.object.pass;

            console.log(email);
            console.log(pass);

            const auth = firebase.auth();

            if(document.getElementById('epass').innerHTML == "" && document.getElementById('email').innerHTML == "") {
                auth.createUserWithEmailAndPassword(email,pass)
                .then(e => {
                    document.getElementById('register').classList.remove('active');
                    document.getElementById('results').classList.add('active');
                    document.getElementById('nreg').classList.remove('active');
                    document.getElementById('nres').classList.add('active');
                })
                .catch(er => {
                        document.getElementById('epass').innerHTML = er.message;
                    });
            }
        };

        MyCtrl.prototype.auth = function ($firebaseObject) {
            firebase.auth().onAuthStateChanged(firebaseUser => {
                if(firebaseUser) {
                    console.log(firebaseUser);
                    var lg = firebaseUser.email.indexOf('@');
                    var name = firebaseUser.email.slice(0,lg);
                    this.user = name;
                    document.getElementById('lbtnin').classList.add('hide');
                    document.getElementById('rbtnin').classList.add('hide');
                    document.getElementById('dlmail').classList.add('hide');
                    document.getElementById('dlpass').classList.add('hide');
                    document.getElementById('dmail').classList.add('hide');
                    document.getElementById('dpass').classList.add('hide');
                    document.getElementById('lbtnout').classList.remove('hide');
                    document.getElementById('rbtnout').classList.remove('hide');
                    document.getElementById('mschat').classList.add('hide');
                    document.getElementById('chatbox').classList.remove('hide');
                    this.loadms($firebaseObject);
                }else{
                    document.getElementById('lbtnout').classList.add('hide');
                    document.getElementById('lbtnin').classList.remove('hide');
                    document.getElementById('rbtnout').classList.add('hide');
                    document.getElementById('rbtnin').classList.remove('hide');
                    document.getElementById('dlmail').classList.remove('hide');
                    document.getElementById('dlpass').classList.remove('hide');
                    document.getElementById('dmail').classList.remove('hide');
                    document.getElementById('dpass').classList.remove('hide');
                    document.getElementById('mschat').classList.remove('hide');
                    document.getElementById('chatbox').classList.add('hide');
                }
            });
        };

        MyCtrl.prototype.logout = function () {
            firebase.auth().signOut()
            .then(e => {
                console.log(e);
                this.object.lmail = "";
                this.object.lpass = "";
                this.object.mail = "";
                this.object.pass = "";
            });
        };

        MyCtrl.prototype.sendms = function () {
            var today = new Date().toJSON().slice(0,19);
            console.log(today);
            var text = document.getElementById('mensaje').value;
            console.log(text);
            console.log(this.user);
            firebase.database().ref('messages/' + today).set({
                nombre: this.user,
                mensaje: text
            }).then(document.getElementById('mensaje').value = "");
        };

        MyCtrl.prototype.loadms = function($firebaseObject) {
            var messagesRef = firebase.database().ref().child('messages');
            this.mss = $firebaseObject(messagesRef);
        };
}());
