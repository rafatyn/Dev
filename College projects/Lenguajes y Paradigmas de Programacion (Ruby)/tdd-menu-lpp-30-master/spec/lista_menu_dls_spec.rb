require "spec_helper"
require "./lib/dieta.rb"

describe Lista_DE do

	before:all do
        	@almuerzo = Dieta::Menu_dsl.new("Algo") do
            		titulo  "Almuerzo"
            		ingesta :min => 30, :max => 35
            		plato   :descripcion => "Macarrones con salsa de tomate y queso parmesano",
                    		:porcion => "1 1/2 cucharon",
                    		:gramos => 200
           	 	plato   :descripcion => "Escalope de ternera",
                    		:porcion => "1 bistec mediano",
                    		:gramos => 100
            		plato   :descripcion => "Ensalada basica con zanahoria rallada",
                    		:porcion => "guarnicion",
                    		:gramos => 120
            		plato :descripcion => "Mandarina", :porcion => "1 grande", :gramos => 180
            		plato :descripcion => "Pan de trigo integral", :porcion => "1 rodaja", :gramos => 20
            		valor :vct => 785.9, :proteinas => 19, :grasas => 34, :hidratos => 47
        	end

        	@desayuno = Dieta::Menu_dsl.new("Algo") do
            		titulo  "Desayuno"
            		ingesta :min => 20, :max => 25
            		plato   :descripcion => "Churros con chocolate",
                    		:porcion => "1",
                    		:gramos => 250
            		plato   :descripcion => "Cafe con leche",
                    		:porcion => "1",
                    		:gramos => 75
            		valor :vct => 999.9, :proteinas => 9, :grasas => 74, :hidratos => 37
        	end

        	@cena = Dieta::Menu_dsl.new("Algo") do
            		titulo  "Cena"
            		ingesta :min => 20, :max => 25
            		plato   :descripcion => "Pasta con queso",
                    		:porcion => "1",
                    		:gramos => 250
            		plato   :descripcion => "Cola-cao",
                    		:porcion => "1",
                    		:gramos => 75
            		valor :vct => 467, :proteinas => 0, :grasas => 34, :hidratos => 77
        	end
	

		@dia1 = Lista_DE.new()
        	@dia1.insert_ini(@desayuno)
        	@dia1.insert_ini(@almuerzo)
        	@dia1.insert_ini(@cena)
        	@dia2 = Lista_DE.new()
        	@dia2.insert_ini(@desayuno)
        	@dia2.insert_ini(@cena)
		@semana = Lista_DE.new()
		@semana.insert_ini(@dia2)
		@semana.insert_ini(@dia2)	
	end
		
		it "El menu diario tiene head" do
			expect(@dia1.head[:v].titular).to eq("Cena")

		end

		it "El menu diario tiene tail" do
			expect(@dia1.tail[:v].titular).to eq("Desayuno")
		end
		
		it "El menu diario se muestra bien" do
           		 expect(@dia2.to_s).to eq("1) Cena\n====\n\n20% - 25%\n\n1)  Pasta con queso | 1 | 250 gramos\n\n2)  Cola-cao | 1 | 75 gramos\n\nV.C.T | %\t467 kcal | 0% - 34% - 77%\n\n2) Desayuno\n========\n\n20% - 25%\n\n1)  Churros con chocolate | 1 | 250 gramos\n\n2)  Cafe con leche | 1 | 75 gramos\n\nV.C.T | %\t999.9 kcal | 9% - 74% - 37%\n\n")
        	end
		
		it "El menu semanal se muestra correctamente" do
			expect(@semana.to_s).to eq("Dieta numero 1 de la semana\n 1) Cena\n====\n\n20% - 25%\n\n1)  Pasta con queso | 1 | 250 gramos\n\n2)  Cola-cao | 1 | 75 gramos\n\nV.C.T | %\t467 kcal | 0% - 34% - 77%\n\n2) Desayuno\n========\n\n20% - 25%\n\n1)  Churros con chocolate | 1 | 250 gramos\n\n2)  Cafe con leche | 1 | 75 gramos\n\nV.C.T | %\t999.9 kcal | 9% - 74% - 37%\n\n\nDieta numero 2 de la semana\n 1) Cena\n====\n\n20% - 25%\n\n1)  Pasta con queso | 1 | 250 gramos\n\n2)  Cola-cao | 1 | 75 gramos\n\nV.C.T | %\t467 kcal | 0% - 34% - 77%\n\n2) Desayuno\n========\n\n20% - 25%\n\n1)  Churros con chocolate | 1 | 250 gramos\n\n2)  Cafe con leche | 1 | 75 gramos\n\nV.C.T | %\t999.9 kcal | 9% - 74% - 37%\n\n\n")

		end
end






