// Standard Template Library example using a class.

#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstdlib> 
#include <cstring>
#include <vector>
#include "elements.h"

using namespace std;

// The Set STL template requires overloading operators =, == and <.

int opcion;
set <elements> potencia(set <elements> &Cjto, int exponente);
set <elements> inversa(set <elements> &Cjto);
set <elements> concatenacion(set <elements> &Cjto, set <elements> &Cjto2);
void sublenguaje(set <elements> &Cjto, set <elements> &Cjto2);
void igualdad(set <elements> &Cjto, set <elements> &Cjto2);

void print (set <elements> Cjto){
	for (set<elements>::iterator i = Cjto.begin(); i != Cjto.end(); i++)
	cout << (*i); 
}

void leer(set <elements> &Cjto, char* cadena)
{

	if(Cjto.empty() == false){
		Cjto.erase(Cjto.begin(), Cjto.end());
	}
	char* pch = strtok(cadena,"{}, ");
	
	while(pch != NULL){
		
	 	if(pch[0] =='&'){
	 		char token = 0;
	 		elements tmp(token);
	 		Cjto.insert(tmp);
	 	}else{
			elements tmp(pch);
			Cjto.insert(tmp);
	 	}	
	 	pch = strtok(NULL,"{}, ");
	}
}

void menu(void){
    
    cout << endl;
    cout << "1. Potencia" << endl;
    cout << "2. Inversa" << endl;
    cout << "3. Concatenación" << endl;
    cout << "4. Unión" << endl;
    cout << "5. Intersección" << endl;
    cout << "6. Diferencia" << endl;
    cout << "7. Sublenguajes" << endl;
    cout << "8. Igualdad de lenguajes" << endl;
    cout << "0. Salir" << endl;
    cout << endl << ">>> Introduzca una opción: ";
    cin >> opcion;
    cin.get();
}

int main(){
	
	int interfaz;
	char cadena[100];
	int exponente;
	ostream_iterator< elements > iter( cout, "" );
                      
	set <elements> CjtoA;
	set <elements> CjtoB;
	
	cout << "0. Interfaz estandar" << endl;
	cout << "1. Interfaz interprete interactivo" << endl;
	cout << ">>> ";
	cin >> interfaz;
	cin.get();
	
	if(interfaz == 0){
		do{
			menu();
			switch(opcion){
				
				case 1:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Indique el exponente: ";
					cin >> exponente;
					cin.get();
					cout << endl;
					
					print(potencia(CjtoA, exponente));
				break;
				
				case 2:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoA, cadena);
					
					print(inversa(CjtoA));
				break;
				
				case 3:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Defina el segundo lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoB, cadena);
					
					print(concatenacion(CjtoA,CjtoB));
				break;
				
				case 4:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Defina el segundo lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoB, cadena);
					set_union(CjtoA.begin(), CjtoA.end(), CjtoB.begin(), CjtoB.end(), iter);
				break;
				
				case 5:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Defina el segundo lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoB, cadena);
					set_intersection(CjtoA.begin(), CjtoA.end(), CjtoB.begin(), CjtoB.end(), iter);
				break;
				
				case 6:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Defina el segundo lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoB, cadena);
					set_difference(CjtoA.begin(), CjtoA.end(), CjtoB.begin(), CjtoB.end(), iter);
				break;
				
				case 7:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Defina el segundo lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoB, cadena);
					
					sublenguaje(CjtoA, CjtoB);
				break;
				
				case 8:
					cout << "Defina el lenguaje: ";
					cin.getline(cadena,100);
					leer(CjtoA, cadena);
					cout << "Defina el segundo lenguaje: ";
					cin.getline(cadena,100);
					cout << endl;
					leer(CjtoB, cadena);
					
					igualdad(CjtoA, CjtoB);
				break;
				
				default:
					if(opcion!=0){
						cout << "La opcion introducida no es valida" << endl;
					}
			}
		}while(opcion != 0);
	
	}else{
		
		string saux;
		char salir[6]={"Salir"};
		ostream_iterator< elements > iter( cout, "" );
		vector <set <elements> > lenguaje;
		lenguaje.resize(9);
		set <elements> CjtoA;
		set <elements> CjtoB;
		vector <char* > tokens;
		bool aux, auxi;
		char token;
		char cadena[80];
		int i, j, k;
		while(1){
			
			cout<<">>> ";
			cin.getline(cadena,80);
			aux=1;
			
			for(int x=0; x<5 && aux; x++){
				if(salir[x] != cadena[x]){
					aux=0;
				}
			}
			if(aux){
				exit(0);
			}
			aux=0;
			auxi=0;
			for(int x=0; cadena[x]!='\0'&&!aux; x++){
				if(cadena[x]=='{'){
					aux=1;
				}else{
					if(cadena[x]=='='){
						auxi=1;
					}
				}
			}
			if(aux){
				char * pch=strtok(cadena,"L={}, ");
				while(pch!=NULL){
			  	tokens.push_back(pch);
			  	pch=strtok(NULL,"={}, ");
			    }
			}else{
				char * pch=strtok(cadena,"L ={},");
				while(pch!=NULL){
			  	tokens.push_back(pch);
			  	pch=strtok(NULL,"L ={},");
			    }
			}
		  i=j=k=-1;
		  
		  switch(aux){
		  	
		  	case 0:
				switch(tokens.size()){
				  	case 0:
				  	break;
				  	
				  	case 1:
				    	i=atoi(tokens[0])-1;
				      	if(lenguaje[i].begin() == lenguaje[i].end()){
				      		const char* aux = "{}";
				      		elements tmp(aux);
				      		lenguaje[i].insert(tmp);
				      	}				      	
				      	print(lenguaje[i]);
				    break;
				    
				    case 2:
				    	if(auxi){
					    	i=atoi(tokens[0])-1;
					    	j=atoi(tokens[1])-1;
					    	if(lenguaje[i].empty() == false){
					    		lenguaje[i].erase(lenguaje[i].begin(), lenguaje[i].end());
					    	}
					    	for(set<elements>::iterator it = lenguaje[j].begin(); it != lenguaje[j].end(); it++){
									lenguaje[i].insert(*it);
					    	}
				    	}else{
				    		
				    		token=tokens[0][0];
				    		i=atoi(tokens[1])-1;
				    		switch(token){
				    			case 'v':
				    				print(inversa(lenguaje[i]));
								break;
								
								default:
									cout << "Operación no encontrada" << endl;
								break;
				    		}
				    	}
				    break;
				    
				    case 3: 
				    	i=atoi(tokens[0])-1;
					    j=atoi(tokens[2])-1;
					    token=tokens[1][0];
				    	if(!auxi){
				    		
					    	switch(token){
					    		
					    		case '*':
					    			print(concatenacion(lenguaje[i], lenguaje[j]));
					    		break;
					    		
					    		case '^':
					    			j++;
					    			print(potencia(lenguaje[i],j));
					    		break;
					    		
					    		case 'U':
				    				set_union(lenguaje[i].begin(), lenguaje[i].end(), lenguaje[j].begin(), lenguaje[j].end(), iter);
					    		break;
					    		
					    		case '-':
				    				set_difference(lenguaje[i].begin(), lenguaje[i].end(), lenguaje[j].begin(), lenguaje[j].end(), iter);
					    		break;
					    		
					    		case 'i':
				    				set_intersection(lenguaje[i].begin(), lenguaje[i].end(), lenguaje[j].begin(), lenguaje[j].end(), iter);
					    		break;
					    		
					    		case 'v':
					    			print(inversa(lenguaje[j]));
								break;
								
				    			case 's':
				    				sublenguaje(lenguaje[i], lenguaje[j]);
				    			break;
				    			
				    			case 'q':
				    				igualdad(lenguaje[i], lenguaje[j]);
				    			break;
				    			
					    		default:
									cout<<"Operación no encontrada."<<endl;
								break;
					    	}
				    	}else{
				    		
				    		switch(token){
				    			case 'v':
					    			CjtoA = inversa(lenguaje[j]);
									if(lenguaje[i].empty() == false){
										lenguaje[i].erase(lenguaje[i].begin(), lenguaje[i].end());
									}
									copy(CjtoA.begin(), CjtoA.end(), inserter(lenguaje[i], lenguaje[i].begin()));
								break;
				    		
				    			default:
									cout<<"Operación no encontrada."<<endl;
								break;
				    		}
				    	}
				    break;
				    
				    case 4:
				    	i=atoi(tokens[0])-1;
				    	j=atoi(tokens[1])-1;
				    	k=atoi(tokens[3])-1;
				    	token=tokens[2][0];
				    	switch(token){
				    		
				    		case '*':
				    			CjtoA = concatenacion(lenguaje[j], lenguaje[k]);
						    	if(lenguaje[i].empty() == false){
						    		lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
						    	}
						    	copy(CjtoA.begin(), CjtoA.end(), inserter(lenguaje[i], lenguaje[i].begin()));
							break;
							
				    		case '^':
				    			k++;
						    	if(k==0){
						    		if(!lenguaje[i].empty())
						    			lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
						    		token=0;
										elements tmp(token);
						    		lenguaje[i].insert(tmp);
						    	}else{
						    		CjtoA = potencia(lenguaje[j], k);
									if(lenguaje[i].empty() == false){
						    		lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
						    		}
									copy(CjtoA.begin(), CjtoA.end(), inserter(lenguaje[i], lenguaje[i].begin()));
							    }
						    break;	
						    
				    		case 'U':
				    			if(CjtoA.empty() == false){
						    		CjtoA.erase(CjtoA.begin(),CjtoA.end());
				    			}
				    			set_union(lenguaje[j].begin(), lenguaje[j].end(), lenguaje[k].begin(), lenguaje[k].end(), inserter(CjtoA, CjtoA.begin()));
				    			if(lenguaje[i].empty() == false){
						    		lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
						    	}
						    	copy(CjtoA.begin(), CjtoA.end(), inserter(lenguaje[i], lenguaje[i].begin()));
				    		break;
				    		
				    		case '-':
				    			if(CjtoA.empty() == false){
						    		CjtoA.erase(CjtoA.begin(),CjtoA.end());
				    			}
				    			set_difference(lenguaje[j].begin(), lenguaje[j].end(), lenguaje[k].begin(), lenguaje[k].end(), inserter(CjtoA, CjtoA.begin()));
				    			if(lenguaje[i].empty() == false){
						    		lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
				    			}
						    	copy(CjtoA.begin(), CjtoA.end(), inserter(lenguaje[i], lenguaje[i].begin()));
				    		break;
				    			
				    		case 'i':
				    			if(CjtoA.empty() == false){
						    		CjtoA.erase(CjtoA.begin(),CjtoA.end());
				    			}
				    			set_intersection(lenguaje[j].begin(), lenguaje[j].end(), lenguaje[k].begin(), lenguaje[k].end(), inserter(CjtoA, CjtoA.begin()));
				    			if(lenguaje[i].empty() == false){
						    		lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
				    			}
						    	copy(CjtoA.begin(), CjtoA.end(), inserter(lenguaje[i], lenguaje[i].begin()));
				    		break;
				    			
				    		default:
								cout<<"Operación no encontrada."<<endl;
							break;
							
				    	}
				    	break;
				    	
				  }
				  break;
				  
				case 1:
				
					i=atoi(tokens[0])-1;
					
					if(lenguaje[i].empty() == false){
						lenguaje[i].erase(lenguaje[i].begin(),lenguaje[i].end());
					}
					for(int x=1; x<tokens.size(); x++)
					{
						token=tokens[x][0];
						if(token =='&'){
							tokens[x][0]='&';
							elements tmp(tokens[x]);
							lenguaje[i].insert(tmp);
						}else{
							elements tmp(tokens[x]);
							lenguaje[i].insert(tmp);
						}
					}
					break;
					
		  }
		  tokens.clear();
		}
	}
}

set <elements> potencia(set <elements> &Cjto, int exponente)
{
	char aux;
	set <elements> Cjto2;
	set <elements> Cjto3;
	
	if(exponente == 0){
		if(Cjto.empty() == false){
			Cjto.erase(Cjto.begin(), Cjto.end());
		}
		aux = '&';
		elements tmp(aux);
		Cjto.insert(tmp);
		return Cjto;
	}else{

		copy(Cjto.begin(), Cjto.end(), inserter(Cjto2, Cjto2.begin()));
		for(int k=0; k<exponente-1; k++){
			Cjto3 = concatenacion(Cjto2,Cjto);
			Cjto2.erase(Cjto2.begin(),Cjto2.end());
			copy(Cjto3.begin(), Cjto3.end(), inserter(Cjto2, Cjto2.begin()));
			Cjto3.erase(Cjto3.begin(), Cjto3.end());
		}
		return Cjto2;
	}
}

set <elements> concatenacion(set <elements> &Cjto, set <elements> &Cjto2)
{
	set <elements> Cjto3;
	
	for(set<elements>::iterator i = Cjto.begin(); i != Cjto.end(); i++){
		for(set<elements>::iterator j = Cjto2.begin(); j != Cjto2.end(); j++){
			elements tmp((*i).s,(*j).s);
			Cjto3.insert(tmp);
		}
	}
	if((Cjto.begin() == Cjto.end())||(Cjto2.begin() == Cjto2.end())){
		const char* aux = "{}";
		elements tmp2(aux);
		Cjto3.insert(tmp2);
	}
	return Cjto3;
}

set <elements> inversa(set <elements> &Cjto)
{
	string s_aux;
	set <elements> Cjto2;

	for(set<elements>::iterator ii = Cjto.begin(); ii != Cjto.end(); ii++){
			s_aux = "";
			for(int i = (*ii).s.size(); i >= 0; i--){
				s_aux += (*ii).s[i];
			}
			elements tmp(s_aux);
			Cjto2.insert(tmp);
	}
	if(Cjto.begin() == Cjto.end()){
		const char* aux = "{}";
		elements tmp2(aux);
		Cjto2.insert(tmp2);
	}
	return Cjto2;
}

void sublenguaje(set <elements> &Cjto, set <elements> &Cjto2)
{
	set <elements> Cjto3;
	
	set_intersection(Cjto.begin(), Cjto.end(), Cjto2.begin(), Cjto2.end(), inserter(Cjto3, Cjto3.begin()));
	if(Cjto2.size() == Cjto3.size() && equal(Cjto2.begin(), Cjto2.end(), Cjto3.begin())){
		cout << "Es un sublenguaje" << endl;
	}else{
		cout << "No es un sublenguaje" << endl;
	}
}

void igualdad(set <elements> &Cjto, set <elements> &Cjto2)
{
	if(Cjto.size() == Cjto2.size() && equal(Cjto.begin(), Cjto.end(), Cjto2.begin())){
		cout<<"Los lenguajes son iguales"<<endl;
	}else{
		cout<<"Los lenguajes no son iguales"<<endl;
	}
}