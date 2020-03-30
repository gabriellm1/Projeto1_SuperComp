#include<iostream>
#include<vector>
#include<tuple>
#include <sstream>
#include <string>
#include<chrono>
#include<cmath>



using namespace std;

using namespace chrono;

void escolhe_alunos(vector<vector<int>> prefs, 
                                        vector<int> aluno_projeto, 
                                        vector<int> vagas, 
                                        tuple <vector<int>, int>& melhor,
                                        int i=0,
                                        int satisfacao_atual=0,
                                        bool isNull = false){

        if(i==aluno_projeto.size()){
            if(!isNull){
                get<0>(melhor) = aluno_projeto;
                get<1>(melhor) = satisfacao_atual;
                isNull = true;
                }   
            if(satisfacao_atual>get<1>(melhor)){
                get<0>(melhor) = aluno_projeto;
                get<1>(melhor) = satisfacao_atual; 
                isNull = true;
                }
        }
        
        for (int proj_atual = 0; proj_atual < prefs[1].size(); proj_atual++){
            if(vagas[proj_atual]>0){
                vagas[proj_atual] -= 1;
                aluno_projeto[i] = proj_atual;

                escolhe_alunos(prefs,aluno_projeto,vagas,melhor,i+1,satisfacao_atual+prefs[i][proj_atual],isNull);
                isNull = true;

                aluno_projeto[i] = -1;
                vagas[proj_atual] += 1;
            }
        }
    }



int main(){

    vector<int> input, temp_vect;
    string line;
    int tmp;

    getline(cin, line);
    istringstream ss(line);
    while(ss >> tmp) {
        input.push_back(tmp);
    }

    
    int n_alunos = input[0];
    int n_projetos = input[1];
    int n_choices = input[2];

    vector<vector<int>> prefs(n_alunos, vector<int>(n_projetos));


    for (int i=0; i< n_alunos; i++){        
        getline(std::cin, line);
        istringstream ss(line);
        temp_vect.clear();
        while(ss >> tmp) {
            temp_vect.push_back(tmp);
        }
        for(int j = 0; j < n_choices; j++){           
            prefs[i][temp_vect[j]] = pow(n_choices - j,2);
        }
    }

    vector<int> vagas(n_projetos, 3);
    vector<int> aluno_projeto(n_alunos, -1);
 

    tuple <vector<int>, int> melhor ;
    escolhe_alunos(prefs, aluno_projeto, vagas, melhor);

    cout << get<1>(melhor) << " 1 \n";
    for ( auto z = get<0>(melhor).begin(); z != get<0>(melhor).end(); z++){
        cout << *z << " ";
    }
    cout << "\n";

}
