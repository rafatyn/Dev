(function() {
    var myapp = angular.module('myApp');
        myapp.controller("GCtrl", function($http,$scope) {
            $scope.gethttp = function (){
                    $http.get('http://opendatacanarias.es/datos/dataset/6b13318c-5b25-4334-99ec-9606aa95b15a/resource/d686f190-6b3c-4e50-8cdc-f770765c7515/download/playas.json').then(function(value) {
                        $scope.info = value;
                });
            };
        });
}());
