// importar
var express = require('express');

// instanciar
var app = express();

app.use(express.static("public"));
 // ruteo
app.get('/', function(req, res){
    res.sendFile(__dirname + '/public/index.html');
});
// escuchar
app.listen(3000);

console.log("Servidor Express escuchando en modo %s", app.settings.env);
