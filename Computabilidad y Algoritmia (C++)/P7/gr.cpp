#include "gr.hpp"

gr::gr(void):
alfabeto(),
nt(),
S()
{}

gr::~gr(void)
{}

void gr::crear_gr(vector <set <transicion> > nt_, set <transicion> S_, set <char> alfabeto_)
{
    alfabeto=alfabeto_;
    nt=nt_;
    S=S_;
}

void gr::exporta(char* nombre)
{
    ofstream fichero;
    fichero.open(nombre);
    fichero << alfabeto.size() << "\n";
    for(set <char>::iterator i=alfabeto.begin(); i!=alfabeto.end(); i++){
        fichero << (*i) << " ";
    }
    fichero << "\n" << nt.size() << "\n";
    char letras[nt.size()];
    letras[0]='S';
    fichero << 'S';
    for(int i=1; i<nt.size(); i++){
        char aux=64+i;
        fichero << " " << aux;
        letras[i]=aux;
    }
    int n=0;
    int x=0;
    for(int i=0; i<nt.size(); i++){
        fichero << "\n" << letras[n] << " -> ";
        for(set <transicion>::iterator j=nt[i].begin(); j!=nt[i].end(); j++){
            if((*j).get_sig_estado()!=-5){
                if(x!=0){
                    fichero << " | " << (*j).get_entrada() << letras[(*j).get_sig_estado()];
                }else{
                    fichero << (*j).get_entrada() << letras[(*j).get_sig_estado()];
                }
            }else{
                if(x!=0){
                    fichero << " | " << (*j).get_entrada();
                }else{
                    fichero << (*j).get_entrada();
                }
            }
            x++;
        }
        x=0;
        n++;
    }
    fichero << "\n";
    fichero.close();
}