require "spec_helper"
require "dieta"

describe Dieta do
	
	context "Menu dietetico DSL" do

		before :all do
			@menu = Dieta::Dieta_dsl.new("Etiqueta") do 
				titulo	    "Almuerzo"
				ingesta     :min => 30, :max => 35
				plato       :descripcion => "Macarrones con salsa de tomate y queso parmesano", :porcion => "1 1/2 cucharon", :gramos => 200 
				plato       :descripcion => "Escalope de ternera", :porcion => "1 bistec mediano", :gramos => 100 
				plato       :descripcion => "Ensalada basica con zanahoria rallada", :porcion => "guarnicion", :gramos => 120 
				plato       :descripcion => "Mandarina", :porcion => "1 grande", :gramos => 180 
				plato       :descripcion => "Pan de trigo integral", :porcion => "1 rodaja", :gramos => 20
				porcentajes :vct => 785.9, :proteinas => 19, :grasas => 34, :hidratos => 47
			end
		end	
		
		it "El menu tiene titulo" do
			expect(@menu.tit).to eq("Almuerzo")
		end

		it "El menu tiene los datos de ingesta" do
			expect(@menu.ing).to eq([30, 35])
		end

		it "El menu tiene los datos de los platos" do
			expect(@menu.platos).to eq([["Macarrones con salsa de tomate y queso parmesano","1 1/2 cucharon",200],["Escalope de ternera","1 bistec mediano",100],["Ensalada basica con zanahoria rallada","guarnicion",120],["Mandarina","1 grande",180],["Pan de trigo integral","1 rodaja",20]])
		end

		it "El menu tiene los datos de los porcentajes" do
			expect(@menu.porc).to eq([785.9,19,34,47])
		end

		it "El menu se imprime bien" do
			expect(@menu.to_s).to eq("Almuerzo (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n")
		end
	end	
end

describe Proyecto do

	context "Lista de menus dieteticos DSL" do

		before :all do
			@menu1 = Dieta::Dieta_dsl.new("menu1") do
                                titulo      "Desayuno"
                                ingesta     :min => 30, :max => 35
                                plato       :descripcion => "Macarrones con salsa de tomate y queso parmesano", :porcion => "1 1/2 cucharon", :gramos => 200
                                plato       :descripcion => "Escalope de ternera", :porcion => "1 bistec mediano", :gramos => 100
                                plato       :descripcion => "Ensalada basica con zanahoria rallada", :porcion => "guarnicion", :gramos => 120
                                plato       :descripcion => "Mandarina", :porcion => "1 grande", :gramos => 180
                                plato       :descripcion => "Pan de trigo integral", :porcion => "1 rodaja", :gramos => 20
                                porcentajes :vct => 785.9, :proteinas => 19, :grasas => 34, :hidratos => 47
                        end
			@menu2 = Dieta::Dieta_dsl.new("menu2") do
                                titulo      "Almuerzo"
                                ingesta     :min => 30, :max => 35
                                plato       :descripcion => "Macarrones con salsa de tomate y queso parmesano", :porcion => "1 1/2 cucharon", :gramos => 200
                                plato       :descripcion => "Escalope de ternera", :porcion => "1 bistec mediano", :gramos => 100
                                plato       :descripcion => "Ensalada basica con zanahoria rallada", :porcion => "guarnicion", :gramos => 120
                                plato       :descripcion => "Mandarina", :porcion => "1 grande", :gramos => 180
                                plato       :descripcion => "Pan de trigo integral", :porcion => "1 rodaja", :gramos => 20
                                porcentajes :vct => 785.9, :proteinas => 19, :grasas => 34, :hidratos => 47
                        end
			@menu3 = Dieta::Dieta_dsl.new("menu3") do
                                titulo      "Merienda"
                                ingesta     :min => 30, :max => 35
                                plato       :descripcion => "Macarrones con salsa de tomate y queso parmesano", :porcion => "1 1/2 cucharon", :gramos => 200
                                plato       :descripcion => "Escalope de ternera", :porcion => "1 bistec mediano", :gramos => 100
                                plato       :descripcion => "Ensalada basica con zanahoria rallada", :porcion => "guarnicion", :gramos => 120
                                plato       :descripcion => "Mandarina", :porcion => "1 grande", :gramos => 180
                                plato       :descripcion => "Pan de trigo integral", :porcion => "1 rodaja", :gramos => 20
                                porcentajes :vct => 785.9, :proteinas => 19, :grasas => 34, :hidratos => 47
                        end
			@menu4 = Dieta::Dieta_dsl.new("menu4") do
                                titulo      "Cena"
                                ingesta     :min => 30, :max => 35
                                plato       :descripcion => "Macarrones con salsa de tomate y queso parmesano", :porcion => "1 1/2 cucharon", :gramos => 200
                                plato       :descripcion => "Escalope de ternera", :porcion => "1 bistec mediano", :gramos => 100
                                plato       :descripcion => "Ensalada basica con zanahoria rallada", :porcion => "guarnicion", :gramos => 120
                                plato       :descripcion => "Mandarina", :porcion => "1 grande", :gramos => 180
                                plato       :descripcion => "Pan de trigo integral", :porcion => "1 rodaja", :gramos => 20
                                porcentajes :vct => 785.9, :proteinas => 19, :grasas => 34, :hidratos => 47
                        end

			@lista = Proyecto::Lista.new()
			@lista1 = Proyecto::Lista.new()
			@lista1.insert_fin("#-- Dia 1 --#")
			@lista1.insert_fin(@menu1)
			@lista1.insert_fin(@menu2)
			@lista1.insert_fin(@menu3)
			@lista1.insert_fin(@menu4)
			@lista2 = Proyecto::Lista.new()
                        @lista2.insert_fin("#-- Dia 2 --#")
                        @lista2.insert_fin(@menu1)
                        @lista2.insert_fin(@menu2)
                        @lista2.insert_fin(@menu3)
                        @lista2.insert_fin(@menu4)
			@lista3 = Proyecto::Lista.new()
                        @lista3.insert_fin("#-- Dia 3 --#")
                        @lista3.insert_fin(@menu1)
                        @lista3.insert_fin(@menu2)
                        @lista3.insert_fin(@menu3)
                        @lista3.insert_fin(@menu4)
			@lista4 = Proyecto::Lista.new()
                        @lista4.insert_fin("#-- Dia 4 --#")
                        @lista4.insert_fin(@menu1)
                        @lista4.insert_fin(@menu2)
                        @lista4.insert_fin(@menu3)
                        @lista4.insert_fin(@menu4)
			@lista5 = Proyecto::Lista.new()
                        @lista5.insert_fin("#-- Dia 5 --#")
                        @lista5.insert_fin(@menu1)
                        @lista5.insert_fin(@menu2)
                        @lista5.insert_fin(@menu3)
                        @lista5.insert_fin(@menu4)

			@lista.insert_fin(@lista1)
                        @lista.insert_fin(@lista2)
                        @lista.insert_fin(@lista3)
                        @lista.insert_fin(@lista4)
		end

		it "Se imprime bien la lista" do
			expect(@lista1.to_s).to eq("#-- Dia 1 --#\nDesayuno (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nAlmuerzo (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nMerienda (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nCena (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\n")
		end

		it "Se imprime bien la lista de dias" do
			expect(@lista.to_s).to eq("#-- Dia 1 --#\nDesayuno (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nAlmuerzo (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nMerienda (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nCena (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\n\n#-- Dia 2 --#\nDesayuno (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nAlmuerzo (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nMerienda (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nCena (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\n\n#-- Dia 3 --#\nDesayuno (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nAlmuerzo (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nMerienda (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nCena (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\n\n#-- Dia 4 --#\nDesayuno (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nAlmuerzo (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nMerienda (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\nCena (30-35)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200\n- Escalope de ternera, 1 bistec mediano, 100\n- Ensalada basica con zanahoria rallada, guarnicion, 120\n- Mandarina, 1 grande, 180\n- Pan de trigo integral, 1 rodaja, 20\nV.C.T | %\t785.9 kcal | 19% - 34% - 47%\n\n\n")
		end
	end
end
