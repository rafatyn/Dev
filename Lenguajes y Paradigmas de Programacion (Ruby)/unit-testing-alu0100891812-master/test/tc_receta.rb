require_relative '../lib/receta'
require 'test/unit'

class TestReceta < Test::Unit::TestCase
	def setup
		@receta1 = Receta.new("Sandwich mixto",1,2,["2 rebanadas de pan", "1 loncha de jamon", "1 loncha de queso", "mantequilla al gusto"],["Unte con mantequilla uno de los lados de la rebanada de pan.", "Coloque encima la loncha de queso.", "Coloque encima la loncha de jamon.","Ponga la otra rebanada de pan encima."])
		@receta2 = Receta.new("Pasta con salsa de tomate",2,10,["400 gramos de pasta","100 gramos de salsa de tomate","1 litro de agua","1 pizca de pimienta"],["Ponga a hervir el agua.","Añada la pasta, deje hervir durante 6 minutos.","Escurra el agua.","Mezcle la salsa de tomate y la pimienta con la salsa.","Sirva caliente."])
	end
	
	def test_receta1
		assert_equal("Sandwich mixto\n===========\n\nPorciones: 1\nTiempo de preparacion: 2 minutos\n\nIngredientes:\n2 rebanadas de pan, 1 loncha de jamon, 1 loncha de queso, mantequilla al gusto\n\nInstrucciones:\n1) Unte con mantequilla uno de los lados de la rebanada de pan.\n2) Coloque encima la loncha de queso.\n3) Coloque encima la loncha de jamon.\n4) Ponga la otra rebanada de pan encima.\n", @receta1.to_s)
	end
	def test_receta2
		assert_equal("Pasta con salsa de tomate\n===========\n\nPorciones: 2\nTiempo de preparacion: 10 minutos\n\nIngredientes:\n400 gramos de pasta, 100 gramos de salsa de tomate, 1 litro de agua, 1 pizca de pimienta\n\nInstrucciones:\n1) Ponga a hervir el agua.\n2) Añada la pasta, deje hervir durante 6 minutos.\n3) Escurra el agua.\n4) Mezcle la salsa de tomate y la pimienta con la salsa.\n5) Sirva caliente.\n", @receta2.to_s)
	end
end
