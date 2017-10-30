class Receta
	def initialize(n, p, t, ig, is)
		@n, @p, @t, @ig, @is = n, p, t, ig, is
	end
	
	def to_s
		s = "#{@n}\n"
		s << "===========\n\n"
		s << "Porciones: #{@p}\n"
		s << "Tiempo de preparacion: #{@t} minutos\n\n"
		s << "Ingredientes:\n"
		@ig.each_with_index do |x, index|
			s << ", " if(index!=0)
			s << "#{x}" 
		end
		s << "\n\nInstrucciones:\n"
		@is.each_with_index do |x, index|
			s << "#{index+1}) #{x}\n"
		end
		s << ""
	end
end
