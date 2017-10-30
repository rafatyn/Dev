require "spec_helper"
require "dieta"

describe "Pruebas nodo" do

	context "Debe existir un nodo" do
		before :each do
			@nodo = Nodo.new(1,nil,nil)
		end

		it "Debe existir un nodo con su siguiente, su anterior y su dato" do
			expect(@nodo.v).to eq(1)
			expect(@nodo.s).to eq(nil)
			expect(@nodo.p).to eq(nil) 
	
		end
	end
end

describe Lista_DE do

	context "Pruebas de la lista_DE" do 
	
		before :all do
			@lista_DE1 = Lista_DE.new()
		end

	
		it "Insertar por el inicio un elemento a la lista" do
		
			@lista_DE1.insert_ini(5)
			expect(@lista_DE1.head[:v]).to eq(5)
			expect(@lista_DE1.head[:p]).to eq(nil)
		end

		it "Insertar varios por el inicio elementos en la lista_DE" do

			@lista_DE1.insert_ini(6)
			expect(@lista_DE1.head[:v]).to eq(6)
			@lista_DE1.insert_ini(7)
			expect(@lista_DE1.head[:v]).to eq(7)
		end

		it "Extraer el primer elemento de la lista" do
		
			expect(@lista_DE1.extract_ini()).to eq(7)
			expect(@lista_DE1.head[:v]).to eq(6)
		end		

		it "Debe existir un tail" do 
	
			expect(@lista_DE1.tail[:v]).to eq(5)
		end

		it "Insertar por el final un elemento en la lista" do
			@lista_DE1.insert_fin(4)
			expect(@lista_DE1.tail[:v]).to eq(4)
			expect(@lista_DE1.tail[:p][:v]).to eq(5)
		end

		it "Extraer por el final un elemento de la lista" do
			
			expect(@lista_DE1.extract_fin()).to eq(4)
			expect(@lista_DE1.tail[:v]).to eq (5)

		end
	end

	context "Pruebas de la lista_DE probando menus" do
	
		before :all do
			@lista_DE2 = Lista_DE.new()

			
                        @desayuno = Dieta::Dieta.new('DESAYUNO','15%',[['Leche Denatada','1 vaso','200ml'],['Colacao','1 cucharada','10gr'],['Cereales','1 bol pequeño','40gr'],['Almendras laminadas','2 cucharadas','20gr']],'400','10','20','10')
               	        @almuerzo = Dieta::Dieta.new('ALMUERZO','30%',[['Macarrones con salsa de tomate y queso parmesano','1 plato','200gr'],['Escalope de ternera','1 bistec mediano','100gr'],['Ensalada básica con zanahoria rayada','guarnición','120gr'],['Mandarina','1 grande','60gr'],['Pan de trigo','1 rodaja','40gr']],'400','10','20','10')
               	        @merienda = Dieta::Dieta.new('MERIENDA','15%',[['Manzana','1 unidad','60gr'],['Galletas integrales','4 unidad','80gr']],'400','10','20','10')
               	        @cena = Dieta::Dieta.new('CENA','15%',[['Crema de bubango','1 cucharon','100gr'],['Tortilla con espinacas','1 porción','60gr'],['Tomate con atun en dados','5 cucharadas','150gr'],['Piña natural o en su jugo','5 cucharadas','120gr'],['Pan integral','1 rebanada','20gr']],'400','10','20','10')

			@lista_DE_PE = Lista_DE.new()

			@desayuno1 = Dieta::Edad.new('DESAYUNO','15%',[['Leche Denatada','1 vaso','200ml'],['Colacao','1 cucharada','10gr'],['Cereales','1 bol pequeño','40gr']],'400','10','20','10','4 a 8 años')


			@lista_DE_PA = Lista_DE.new()
			
			@desayuno2 = Dieta::Alimentos.new('DESAYUNO','15%',[['Leche Denatada','1 vaso','200ml'],['Colacao','1 cucharada','10gr'],['Cereales','1 bol pequeño','40gr']],'400','10','20','10','Vegetariano')

		end


		it "Introduciendo menus" do
			 @lista_DE2.insert_ini(@desayuno)
			 expect(@lista_DE2.head[:v]).to have_attributes(:t => 'DESAYUNO', :ing => '15%', :pl =>[['Leche Denatada','1 vaso','200ml'],['Colacao','1 cucharada','10gr'],['Cereales','1 bol pequeño','40gr'],['Almendras laminadas','2 cucharadas','20gr']], :v => '400', :p => '10', :g => '20', :h => '10')
			 @lista_DE2.insert_ini(@almuerzo)
                         expect(@lista_DE2.head[:v]).to have_attributes(:t => 'ALMUERZO', :ing => '30%', :pl =>[['Macarrones con salsa de tomate y queso parmesano','1 plato','200gr'],['Escalope de ternera','1 bistec mediano','100gr'],['Ensalada básica con zanahoria rayada','guarnición','120gr'],['Mandarina','1 grande','60gr'],['Pan de trigo','1 rodaja','40gr']], :v => '400', :p => '10', :g => '20', :h => '10')
                         @lista_DE2.insert_ini(@merienda)
                         expect(@lista_DE2.head[:v]).to have_attributes(:t => 'MERIENDA', :ing => '15%', :pl =>[['Manzana','1 unidad','60gr'],['Galletas integrales','4 unidad','80gr']], :v => '400', :p => '10', :g => '20', :h => '10')
                         @lista_DE2.insert_ini(@cena)
                         expect(@lista_DE2.head[:v]).to have_attributes(:t => 'CENA', :ing => '15%', :pl =>[['Crema de bubango','1 cucharon','100gr'],['Tortilla con espinacas','1 porción','60gr'],['Tomate con atun en dados','5 cucharadas','150gr'],['Piña natural o en su jugo','5 cucharadas','120gr'],['Pan integral','1 rebanada','20gr']], :v => '400', :p => '10', :g => '20', :h => '10')
			
			@lista_DE_PE.insert_ini(@desayuno1)
                        expect(@lista_DE_PE.head[:v].to_s).to eq("DESAYUNO (15%)\n- Leche Denatada, 1 vaso, 200ml\n- Colacao, 1 cucharada, 10gr\n- Cereales, 1 bol pequeño, 40gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n4 a 8 años")

			
                        @lista_DE_PA.insert_ini(@desayuno2)
                        expect(@lista_DE_PA.head[:v].to_s).to eq("DESAYUNO (15%)\n- Leche Denatada, 1 vaso, 200ml\n- Colacao, 1 cucharada, 10gr\n- Cereales, 1 bol pequeño, 40gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\nVegetariano")
           		end


		it "Mostrar el contenido" do
			
                         expect(@lista_DE_PE.to_s).to eq("1) DESAYUNO (15%)\n- Leche Denatada, 1 vaso, 200ml\n- Colacao, 1 cucharada, 10gr\n- Cereales, 1 bol pequeño, 40gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n4 a 8 años\n")
			 expect(@lista_DE_PA.to_s).to eq("1) DESAYUNO (15%)\n- Leche Denatada, 1 vaso, 200ml\n- Colacao, 1 cucharada, 10gr\n- Cereales, 1 bol pequeño, 40gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\nVegetariano\n")
		

		end
	end

	context "Pruebas Enumerable Numeros" do
		
		before :all do
			@listaE = Lista_DE.new()

		end

		it " Insertando valores" do

			@listaE.insert_ini(1)
			expect(@listaE.head[:v]).to eq(1)
			@listaE.insert_ini(2)
                        expect(@listaE.head[:v]).to eq(2)
			@listaE.insert_ini(3)
                        expect(@listaE.head[:v]).to eq(3)

		end

		it " Se puede hacer MAX, MIN, SORT " do

			expect(@listaE.max).to eq(3)
			expect(@listaE.min).to eq(1)
			expect(@listaE.sort).to eq([1, 2, 3])		
		end


	end


	context "Pruebas Enumerable Dieta" do

		before :all do
			@listaED = Lista_DE.new()
		
		  	@desayuno = Dieta::Dieta.new('DESAYUNO','15%',[['Leche Denatada','1 vaso','200ml'],['Colacao','1 cucharada','10gr'],['Cereales','1 bol pequeño','40gr'],['Almendras laminadas','2 cucharadas','20gr']],'300','10','20','10')
                        @almuerzo = Dieta::Dieta.new('ALMUERZO','30%',[['Macarrones con salsa de tomate y queso parmesano','1 plato','200gr'],['Escalope de ternera','1 bistec mediano','100gr'],['Ensalada basica con zanahoria rayada','guarnicion','120gr'],['Mandarina','1 grande','60gr'],['Pan de trigo','1 rodaja','40gr']],'400','30','20','10')
                        @merienda = Dieta::Dieta.new('MERIENDA','15%',[['Manzana','1 unidad','60gr'],['Galletas integrales','4 unidad','80gr']],'400','10','20','10')
                        @cena = Dieta::Dieta.new('CENA','15%',[['Crema de bubango','1 cucharon','100gr'],['Tortilla con espinacas','1 porcin','60gr'],['Tomate con atun en dados','5 cucharadas','150gr'],['Piña natural o en su jugo','5 cucharadas','120gr'],['Pan integral','1 rebanada','20gr']],'600','10','20','10')

		end 

		it "Insertando valores menu" do

		 	 @listaED.insert_ini(@desayuno)
                         expect(@listaED.head[:v]).to have_attributes(:t => 'DESAYUNO', :ing => '15%', :pl =>[['Leche Denatada','1 vaso','200ml'],['Colacao','1 cucharada','10gr'],['Cereales','1 bol pequeño','40gr'],['Almendras laminadas','2 cucharadas','20gr']], :v => '300', :p => '10', :g => '20', :h => '10')
                         @listaED.insert_ini(@almuerzo)
                         expect(@listaED.head[:v]).to have_attributes(:t => 'ALMUERZO', :ing => '30%', :pl =>[['Macarrones con salsa de tomate y queso parmesano','1 plato','200gr'],['Escalope de ternera','1 bistec mediano','100gr'],['Ensalada basica con zanahoria rayada','guarnicion','120gr'],['Mandarina','1 grande','60gr'],['Pan de trigo','1 rodaja','40gr']], :v => '400', :p => '30', :g => '20', :h => '10')
                         @listaED.insert_ini(@merienda)
                         expect(@listaED.head[:v]).to have_attributes(:t => 'MERIENDA', :ing => '15%', :pl =>[['Manzana','1 unidad','60gr'],['Galletas integrales','4 unidad','80gr']], :v => '400', :p => '10', :g => '20', :h => '10')
                         @listaED.insert_ini(@cena)
                         expect(@listaED.head[:v]).to have_attributes(:t => 'CENA', :ing => '15%', :pl =>[['Crema de bubango','1 cucharon','100gr'],['Tortilla con espinacas','1 porcin','60gr'],['Tomate con atun en dados','5 cucharadas','150gr'],['Piña natural o en su jugo','5 cucharadas','120gr'],['Pan integral','1 rebanada','20gr']], :v => '600', :p => '10', :g => '20', :h => '10')


		end

		it "Se puede hacer MAX,MIN,SORT" do

			expect(@listaED.max).to eq(@cena)
                        expect(@listaED.min).to eq(@desayuno)
                        expect(@listaED.sort).to eq([@desayuno, @merienda, @almuerzo, @cena])

		end

		it " Funciona == " do

			expect(@merienda==@almuerzo).to eq(false)

		end

	end

end


describe Dieta do

	context "Pruebas de herencia" do

		before :all do

			@edad1 = Dieta::Edad.new('MERIENDA','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10','4 a 8 años')
			@alimentos =Dieta::Alimentos.new('MERIENDA','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10','verduras y hortalizas')
		end
		
		it "Dieta es superclass de Edad" do

			expect(Dieta::Edad.superclass).to eq(Dieta::Dieta)
		end
		
	        it "Mostrar el contenido" do
		       expect(@edad1.to_s).to eq("MERIENDA (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n4 a 8 años")
                end
		
		it " Dieta es superclass de alimentos" do
	
			expect(Dieta::Alimentos.superclass).to eq(Dieta::Dieta)
		end

		it " Pruebas de herencia" do

			expect(@edad1.is_a?Dieta::Dieta).to eq(true)
			expect(@alimentos.is_a?Dieta::Dieta).to eq(true)
			expect(@edad1.instance_of?Dieta::Edad).to eq(true)
		end


		it "Mostrar el contenido alimentos" do
			expect(@alimentos.to_s).to eq("MERIENDA (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\nverduras y hortalizas")

		end
	end
end



