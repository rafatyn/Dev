module Dieta
	class Dieta
		include Comparable
		attr_reader :t, :ing, :pl, :v, :p, :g, :h
		def initialize(t,ing,pl,v,p,g,h)
			@t, @ing, @pl, @v, @p, @g, @h = t, ing, pl, v, p, g, h
		end
		def get_plato(i)
			@pl[i]
		end
		def to_s
			s = "#{@t} (#{@ing})\n"
			i=0
			while i<@pl.length
				s << "- #{@pl[i][0]}, #{@pl[i][1]}, #{@pl[i][2]}\n"
				i+=1
			end
			s << "V.C.T | %\t#{@v} kcal | #{@p}% - #{@g}% - #{@h}%\n"
		end
		def <=>(otro)
			return nil unless otro.is_a? Dieta
			v <=> otro.v
		end
		def ==(otro)
			if((v == otro.v)&&(p == otro.p)&&(g == otro.g)&&(h == otro.h))
				return true
			else
				return false
			end
		end
        end

	class Alimentos < Dieta
		def initialize(al,t,ing,pl,v,p,g,h)
			super(t,ing,pl,v,p,g,h)
			@al = al
		end
		def to_s
			s = "-#{@al}-\n"
			s << super.to_s
		end
	end

	 class Edad < Dieta
                 def initialize(ed,t,ing,pl,v,p,g,h)
                         super(t,ing,pl,v,p,g,h)
                         @ed = ed
                 end
                 def to_s
                         s = "-#{@ed}-\n"
                         s << super.to_s
                 end
         end

	
	class Dieta_dsl
		attr_reader :tit, :ing, :platos, :porc
		def initialize(etiqueta,&block)
			
			@ing = []
			@platos = []
			@porc = []
			@etiqueta = etiqueta	
			
			if block_given?
	 			if block.arity == 1
	 				yield self
	 			else
	 				instance_eval &block
	 			end
	 		end		
		end
	
		def titulo(nombre)
			@tit = nombre
		end

		def ingesta(val = {})
			@ing << val[:min]
			@ing << val[:max]
		end

		def plato(val = {})
			pl = []
			pl << val[:descripcion]
			pl << val[:porcion]
			pl << val[:gramos]
			@platos << pl
		end

		def porcentajes(val = {})
			@porc << val[:vct]
			@porc << val[:proteinas]
			@porc << val[:grasas]
			@porc << val[:hidratos]
		end

		def to_s
			s = "#{@tit} (#{@ing[0]}-#{@ing[1]})\n"
			i=0
                        while i<@platos.length
                                s << "- #{@platos[i][0]}, #{@platos[i][1]}, #{@platos[i][2]}\n"
                                i+=1
                        end
                        s << "V.C.T | %\t#{@porc[0]} kcal | #{@porc[1]}% - #{@porc[2]}% - #{@porc[3]}%\n" 
		end
	end
end
