#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>

struct Usuario {
    std::string nome;
    std::string senha;
    double saldo;
};

void setColor(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

void consultarUsuarios(const std::vector<Usuario>& usuarios) {
    std::cout << "\n=== Lista de Usuarios Cadastrados ===\n";

    if (usuarios.empty()) {
        std::cout << "Nenhum usuario cadastrado.\n";
        return;
    }

    for (const auto& usuario : usuarios) {
        std::cout << "Nome: " << usuario.nome << " | Saldo: " << usuario.saldo << " $\n";
    }
}

std::vector<Usuario> usuarios;

void cadastrarUsuario(std::vector<Usuario>& usuarios) {
    Usuario novo;

    setColor(1);
    std::cout << "\n=== Cadastro de novo usuario ===\n";
    setColor(7);
    std::cout << "Digite o nome de usuario: ";
    std::cin >> novo.nome;

    std::cout << "Digite a senha: ";
    std::cin >> novo.senha;

    novo.saldo = 0.0;

    usuarios.push_back(novo);
    std::cout << "Usuario cadastrado com sucesso. \n";
}

int fazerLogin(const std::vector<Usuario>& usuarios) {
    std::string nome, senha;
    std::cout << "Login: ";
    std::cin >> nome;
    std::cout << "Senha: ";
    std::cin >> senha;

    for (size_t i = 0; i < usuarios.size(); ++i) {
        if (usuarios[i].nome == nome && usuarios[i].senha == senha) {
            return i;
        }
    }

    return -1;
}


void menu(Usuario& usuario, std::vector<Usuario>& usuarios) {
    int opcao;
    do {
        std::cout << "\nBem vindo, " << usuario.nome << "!\n";
        std::cout << "1. Consultar saldo\n";
        std::cout << "2. Depositar\n";
        std::cout << "3. Sacar\n";
        std::cout << "4. Transferir\n";
        std::cout << "5. Sair\n";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                setColor(2);
                std::cout << "Saldo atual: " << usuario.saldo << " $\n";
                setColor(7);
                break;

            case 2: {
                double valor;
                std::cout << "Valor parar depositar: $ ";
                std::cin >> valor;
                if (valor > 0) {
                    usuario.saldo += valor;
                    std::cout << "Deposito realizado com sucesso.\n";
                } else {
                    std::cout << "Valor invalido.\n";
                }
                break;
#ifdef _WIN32
    system("cls");
#endif    
            }

            case 3: {
                double valor;
                std::cout << "Valor para sacar: $ ";
                std::cin >> valor;
                if (valor > 0 && valor <= usuario.saldo) {
                    usuario.saldo -= valor;
                    std::cout << "Saque realizado com sucesso.\n";
                } else {
                    std::cout << "Saldo insuficiente ou valor invalido.\n";
                }
                break;
            }

#ifdef _WIN32
    system("cls");
#endif    

            case 4: {
                double valor;
                std::string nomeDestino;
                char confirmar;

                std::cout << "Valor para transferir: $ ";
                std::cin >> valor;

                std::cout << "Usuario a receber transferencia: ";
                std::cin >> nomeDestino;

                std::cout << "Transferencia de " << valor << " $ para " << nomeDestino << ". Confirma? (S/N):";
                std::cin >> confirmar;

                if ((confirmar == 'S' || confirmar == 's') && valor > 0 && valor <= usuario.saldo) {
                    bool encontrou = false;

                    for (auto& destinatario : usuarios) {
                        if (destinatario.nome == nomeDestino) {
                            if (destinatario.nome == usuario.nome) {
                                std::cout << "Voce nao pode transferir para si mesmo.\n";
                                break;
                            }

                            usuario.saldo -= valor;
                            destinatario.saldo += valor;
                            std::cout << "Transferencia realizada com sucesso.\n";
                            encontrou = true;
                            break;
                        }
                    }

                    if (!encontrou) {
                        std::cout << "Usuario destinatario nao encontrado.\n";
                    }

                } else {
                    std::cout << "Transferencia nao realizada.\n";
                }
                break;
            }

#ifdef _WIN32
    system("cls");
#endif                
            case 5: {
                setColor(4);
                std::cout << "Encerrando sessao....\n";
                setColor(7);
                break;

            default:
                std::cout <<"Opcao invalida.\n";
                break;
            }

            }
        } while (opcao != 5);

#ifdef _WIN32
    system("cls");
#endif    

    }    

    

int main() {
    std::vector<Usuario> usuarios;

    int escolhaInicial;

    while (true) {
        std::cout << "\n=== Bem vindo ao ATM ===\n";
        std::cout << "1. Cadastrar novo usuario\n";
        std::cout << "2. Fazer login\n";
        std::cout << "3. Sair\n";
        std::cout << "4. Consultar usuarios cadastrados (admin)\n";
        std::cout << "Escolha uma opcao";
        std::cin >> escolhaInicial;

        if (escolhaInicial == 1) {

            cadastrarUsuario(usuarios);

        } else if (escolhaInicial == 2) {

            int indiceUsuario = fazerLogin(usuarios);
            if (indiceUsuario == -1) {
                std::cout << "Login falhou!\n";
            } else {
                menu(usuarios[indiceUsuario], usuarios);

#ifdef _WIN32
    system("cls");
#endif                    
            }

        } else if (escolhaInicial == 3) {
            std::cout << "Encerrando programa.\n";
            break;
             
        } else if (escolhaInicial == 4) {
            consultarUsuarios(usuarios);
        

        } else {
            std::cout << "Opcao invalida.\n";

        }
    }

    return 0;
}