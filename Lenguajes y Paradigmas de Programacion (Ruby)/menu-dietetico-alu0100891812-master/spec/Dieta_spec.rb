require "spec_helper"
require "dieta"

=begin
describe Dieta do 

	context "Menu de dieta" do

		before :each do
			@menu = Dieta::Dieta.new('DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10')
		end

		it 'Debe existir un título' do
			expect(@menu.t).to eq('DESAYUNO')
		end
		
		it 'Debe existir un porcentaje de ingesta diaria' do
			expect(@menu.ing).to eq('15%')
		end

		it 'Debe mostrar un conjunto de platos' do 
			expect(@menu.pl).to eq([['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']])
		end

		it 'Debe mostrar kcal' do
			expect(@menu.v).to eq('400')
		end

		it 'Debe mostrar proteinas' do
			expect(@menu.p).to eq('10')
		end
	
		it 'Debe mostrar grasas' do
			expect(@menu.g).to eq('20')
		end

		it 'Debe mostrar hidratos de carbono' do
			expect(@menu.h).to eq('10')
		end

		it 'Debe mostrar un plato' do
			expect(@menu.get_plato(1)).to eq(['Pera','1 unidad','60gr'])
		end

		it 'Debe mostrar todo el menu' do
			expect(@menu.to_s).to eq("DESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n")
		end
	end
end

describe Proyecto do
	
	context "Nodo" do
		
		before :each do
			@n1 = Proyecto::Nodo.new(5,nil)
		end

		it "Debe existir un Nodo de la lista con sus datos y su siguiente" do
			expect(@n1.valor).to eq(5)
			expect(@n1.sig).to eq(nil)
		end
	end

	context "Lista" do

		before :each do
			@l1 = Proyecto::Lista.new()
		end		

		it "Se extrae el primer elemento de la lista" do
			@l1.insert(1)
			expect(@l1.extract).to eq(1)
		end

		it "Se puede insertar un elemento" do
			@l1.insert(2)
			expect(@l1.to_s).to eq("2\n")
		end

		it "Se puede insertar varios elementos" do
			@l1.insert(3)
			@l1.insert(4)
			@l1.insert(5)
			@l1.insert(6)
			expect(@l1.to_s).to eq("3\n4\n5\n6\n")
		end

		it "Debe de existir una cabeza en la lista" do
			@l1.insert(7)
			expect(@l1.inicio.valor).to eq(7)
		end
	end
	
	context "Lista de menus" do
	
		before :all do
			@lista = Proyecto::Lista.new()
			@desayuno = Dieta::Dieta.new('DESAYUNO','15%',[['Leche desnatada','1 vaso','200 ml'],['Cacao instantaneo','1 c/sopera','10 g'],['Cereales de desayuno en hojuelas','1 bol pequeño','40 g'],['Almendras laminadas (10 unidades)','2 c/soperas','10 g']],'288,0','17','21','62')
			@media_mañana = Dieta::Dieta.new('MEDIA MAÑANA','10%',[['Cerezas','10-12 unidades medianas','120 g'],['Galletas dificus con sesamo','4 unidades','40 g']],'255,5','7','24','69')
			@almuerzo = Dieta::Dieta.new('ALMUERZO','30-35%',[['Macarrones con salsa de tomate y queso parmesano','1 1/2 cucharon','200 g'],['Escalope de ternera','1 bistec mediano','100 g'],['Ensalada basica con zanahoria rallada','1','guarnicion de 120 g'],['Mandarina','1 grande','180 g'],['Pan de trigo integral','1 rodaja','20 g']],'785,9','19','34','47')
			@merienda = Dieta::Dieta.new('MERIENDA','15%',[['Galletas de leche con chocolate y yogur','4 unidades','46 g'],['Flan de vainilla sin huevo','1 unidad','110 g']],'313,6','10','30','60')
			@cena = Dieta::Dieta.new('CENA','25-30%',[['Crema de bubango','2 cucharones','200 g'],['Tortilla campesina con espinacas','1 cuña grande','150 g'],['Tomate en dados con atun','5 a 6 c/soperas','150 g'],['Piña natural en su jugo picada','5 c/soperas','120 g'],['Pan de trigo integral','1 rodaja','20 g']],'561,6','19','40','41')
			@lista.insert(@desayuno)
			@lista.insert(@media_mañana)
			@lista.insert(@almuerzo)
			@lista.insert(@merienda)
			@lista.insert(@cena)
		end

		it "Mostrar el menu" do
			expect(@lista.to_s).to eq("DESAYUNO (15%)\n- Leche desnatada, 1 vaso, 200 ml\n- Cacao instantaneo, 1 c/sopera, 10 g\n- Cereales de desayuno en hojuelas, 1 bol pequeño, 40 g\n- Almendras laminadas (10 unidades), 2 c/soperas, 10 g\nV.C.T | %\t288,0 kcal | 17% - 21% - 62%\n\nMEDIA MAÑANA (10%)\n- Cerezas, 10-12 unidades medianas, 120 g\n- Galletas dificus con sesamo, 4 unidades, 40 g\nV.C.T | %\t255,5 kcal | 7% - 24% - 69%\n\nALMUERZO (30-35%)\n- Macarrones con salsa de tomate y queso parmesano, 1 1/2 cucharon, 200 g\n- Escalope de ternera, 1 bistec mediano, 100 g\n- Ensalada basica con zanahoria rallada, 1, guarnicion de 120 g\n- Mandarina, 1 grande, 180 g\n- Pan de trigo integral, 1 rodaja, 20 g\nV.C.T | %\t785,9 kcal | 19% - 34% - 47%\n\nMERIENDA (15%)\n- Galletas de leche con chocolate y yogur, 4 unidades, 46 g\n- Flan de vainilla sin huevo, 1 unidad, 110 g\nV.C.T | %\t313,6 kcal | 10% - 30% - 60%\n\nCENA (25-30%)\n- Crema de bubango, 2 cucharones, 200 g\n- Tortilla campesina con espinacas, 1 cuña grande, 150 g\n- Tomate en dados con atun, 5 a 6 c/soperas, 150 g\n- Piña natural en su jugo picada, 5 c/soperas, 120 g\n- Pan de trigo integral, 1 rodaja, 20 g\nV.C.T | %\t561,6 kcal | 19% - 40% - 41%\n\n")
		end
	end
end
=end

describe Proyecto do

	context "Nodo" do
		
		before :each do
			@n1 = Proyecto::Nodo.new(nil,1,nil)
		end	
	
		it "Debe existir un Nodo de la lista con anterior, siguiente y valor" do
			expect(@n1.prev).to eq(nil)
			expect(@n1.valor).to eq(1)
			expect(@n1.sig).to eq(nil)
		end
	end

	context "Lista" do
		
		before :each do
			@l1 = Proyecto::Lista.new()
		end

		it "Se puede insertar en la lista por el principio" do
			@l1.insert_ini(1)
			@l1.insert_ini(2)
			expect(@l1.to_s).to eq("2\n1\n")
		end

		it "Se puede extraer por el principio" do
			@l1.insert_ini(3)
			@l1.insert_ini(4)
			expect(@l1.extract_ini).to eq(4)
		end

		it "Debe tener inicio y final" do
			@l1.insert_ini(5)
			@l1.insert_ini(6)
			expect(@l1.inicio.valor).to eq(6)
			expect(@l1.final.valor).to eq(5)
		end

		it "Se puede insertar en la lista por el final" do
			@l1.insert_fin(1)
			@l1.insert_fin(2)
			expect(@l1.to_s).to eq("1\n2\n")
		end

		it "Se puede extraer por el final" do
			@l1.insert_fin(3)
			@l1.insert_fin(4)
			expect(@l1.extract_fin).to eq(4)
		end

		it "Se puede enumerar elementos de la lista" do
			@l1.insert_ini(2)
			@l1.insert_ini(3)
			@l1.insert_ini(1)
			expect(@l1.max).to eq(3)
			expect(@l1.min).to eq(1)
			expect(@l1.sort).to eq([1, 2, 3])
		end
	end
end

describe Dieta do
	
	context "Alimentos" do
	
		before :each do
			@ali1 = Dieta::Alimentos.new('Cereales, legumbres y féculas','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10')
		end

		it "Se crea un menu por alimentos y se muestra bien" do
			expect(@ali1.to_s).to eq("-Cereales, legumbres y féculas-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n")
		end
	
		it "Es de clase class" do
			expect(Dieta::Alimentos.class).to eq(Class)
		end

		it "Es hija de dieta" do
			expect(Dieta::Alimentos.superclass).to eq(Dieta::Dieta)
		end

		it "Es una instancia de Alimentos" do
			expect(@ali1.instance_of?Dieta::Alimentos).to eq(true)
		end

		it "Es de tipo dieta" do
			expect(@ali1.is_a?Dieta::Dieta).to eq(true)
		end
	end

	context "Edad" do

		before :each do
			@eda1 = Dieta::Edad.new('4 a 8 años','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10')
		end

		it "Se crea un menu por edad y se muestra bien" do
			expect(@eda1.to_s).to eq("-4 a 8 años-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n")
		end

		it "Es de clase class" do
                        expect(Dieta::Edad.class).to eq(Class)
                end
                  
		it "Es hija de dieta" do
                        expect(Dieta::Edad.superclass).to eq(Dieta::Dieta)
                end
		
		it "Es una instancia de Edad" do
			expect(@eda1.instance_of?Dieta::Edad).to eq(true)
		end	

                it "Es de tipo dieta" do
                        expect(@eda1.is_a?Dieta::Dieta).to eq(true)
                end
	end

	context "ListaAlimentos" do
		
		before :all do
			@l1 = Proyecto::Lista.new()
			@ali1 = Dieta::Alimentos.new('Verduras y otras hortalizas','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'350','10','20','10')
			@ali2 = Dieta::Alimentos.new('Leche, huevos, pescado, carne y frutos secos','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10')
			@ali3 = Dieta::Alimentos.new('Cereales, legumbres y féculas','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'300','10','20','10')
			@ali4 = Dieta::Alimentos.new('Cereales, legumbres y féculas','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'450','10','20','10')
			@ali5 = Dieta::Alimentos.new('Cereales, legumbres y féculas','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'450','30','20','10')
			@l1.insert_fin(@ali1)
			@l1.insert_fin(@ali2)
			@l1.insert_fin(@ali3)
		end
	
		it "Lista de menu por alimentos" do
			expect(@l1.to_s).to eq("-Verduras y otras hortalizas-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t350 kcal | 10% - 20% - 10%\n\n-Leche, huevos, pescado, carne y frutos secos-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n\n-Cereales, legumbres y féculas-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t300 kcal | 10% - 20% - 10%\n\n")
		end

		it "Se puede enumerar los menus" do
			expect(@l1.max).to eq(@ali2)
			expect(@l1.min).to eq(@ali3)
			expect(@l1.sort).to eq([@ali3, @ali1, @ali2])
		end

		it "Se sobreescribe el metodo ==" do
			expect(@ali4 == @ali5).to eq(false)
		end
	end

	context "ListaEdad" do

                before :all do
                        @l1 = Proyecto::Lista.new()
                        @eda1 = Dieta::Edad.new('4 a 8 años','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'350','10','20','10')
                        @eda2 = Dieta::Edad.new('9 a 13 años','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'400','10','20','10')
                        @eda3 = Dieta::Edad.new('14 a 18 años','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'300','10','20','10')
			@eda4 = Dieta::Edad.new('14 a 18 años','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'350','10','20','10')
 			@eda5 = Dieta::Edad.new('14 a 18 años','DESAYUNO','15%',[['Manzana','1 unidad','60gr'],['Pera','1 unidad','60gr']],'350','10','30','10')
                        @l1.insert_fin(@eda1)
                        @l1.insert_fin(@eda2)
                        @l1.insert_fin(@eda3) 
                end

                it "Lista de menu por edad" do
                        expect(@l1.to_s).to eq("-4 a 8 años-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t350 kcal | 10% - 20% - 10%\n\n-9 a 13 años-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t400 kcal | 10% - 20% - 10%\n\n-14 a 18 años-\nDESAYUNO (15%)\n- Manzana, 1 unidad, 60gr\n- Pera, 1 unidad, 60gr\nV.C.T | %\t300 kcal | 10% - 20% - 10%\n\n") 
                end

		it "Se puede enumerar los menus" do
                        expect(@l1.max).to eq(@eda2)
                        expect(@l1.min).to eq(@eda3)
                        expect(@l1.sort).to eq([@eda3, @eda1, @eda2])
                end

		it "Se sobreescribe el metodo ==" do
			expect(@eda4 == @eda5).to eq(false)
		end
        end
end
