module Proyecto

Nodo = Struct.new(:prev,:valor,:sig)

class Lista
	include Enumerable

	attr_reader :inicio, :final	
	def initialize()
		@inicio = nil
		@final = nil
	end

	def insert_ini(val)
		aux = Nodo.new(nil,val,nil)
		if empty()
			@final = aux
		else
			@inicio.prev = aux
			aux.sig = @inicio
		end
		@inicio = aux
	end

	def insert_fin(val)
		aux = Nodo.new(nil,val,nil)
		if empty()
			@inicio = aux
		else
			@final.sig = aux
			aux.prev = @final
		end
		@final = aux
	end

	def extract_ini()
		if empty() 
			s = "Cannot extract from an empty list"
		else
			aux = @inicio
			@inicio = @inicio.sig
			@inicio.prev = nil
			aux.valor
		end
	end

	def extract_fin()
		if empty()
			s = "Cannot extract from an empty list"
		else
			aux = @final
			@final = @final.prev
			@final.sig = nil
			aux.valor
		end
	end
	
	def empty()
		if @inicio.nil?
			true
		else
			false
		end
	end
	
	def to_s()
		s = ""
		aux = @inicio
		while !aux.nil?
			s << aux.valor.to_s
			s << "\n"
			aux = aux.sig
		end
		
		s
	end

	def each
		aux = @inicio
		while !aux.nil?
			yield aux.valor
			aux = aux.sig
		end
	end
end

end
