require "spec_helper"

require "./lib/dieta.rb"

describe Dieta do
	
	context "Pruebas para todo menu" do
		before :all do
	
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
		end

		it "Debe tener un titulo" do
			expect(@almuerzo.titular).to eq("Almuerzo")
		end
		
		it "Contiene un porcentaje de ingesta" do
      		      expect(@almuerzo.ingesta).not_to be(nil)
        	end
   
	        it "Contiene platos" do
        	      expect(@almuerzo.platos).not_to be(nil)
        	end

   	        it "No es un valor nulo" do
        	     expect(@almuerzo.valor).not_to be(nil)
        	end

		it "La funcion to_s debe mostrar el menu adecuadamente" do
            		expect(@almuerzo.to_s).to eq("Almuerzo\n========\n\n30% - 35%\n\n1)  Macarrones con salsa de tomate y queso parmesano | 1 1/2 cucharon | 200 gramos\n\n2)  Escalope de ternera | 1 bistec mediano | 100 gramos\n\n3)  Ensalada basica con zanahoria rallada | guarnicion | 120 gramos\n\n4)  Mandarina | 1 grande | 180 gramos\n\n5)  Pan de trigo integral | 1 rodaja | 20 gramos\n\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n")
        	end
	end	

end
