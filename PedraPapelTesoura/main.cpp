#include <iostream>
#include <string>
#include <random>
#include <locale.h>
#include <map>

using namespace std;

const string opcoes[]={"pedra", "papel", "tesoura"}; // Opções de mãos a serem jogadas
map<int, string> ganhou = {{0, "Empatou",},{1, "Ganhou",},{2, "Perdeu",}}; //Relaciona número de variável para dizer quem venceu o jogo

class Player { //Classe que define o jogador (pessoa ou máquina)
public:
	string jogada;
	string sorteia_jogada() { //Gera uma jogada aleatória quando a máquina é uma das jogadoras
		int x = (rand() % 2) + 1;
		return opcoes[x];
	}
	const static int verifica_vitoria(Player p1, Player p2) { //Verifica as mãos jogadas e retorna numero para identificar quem é o vencedor
		int vitorioso = 1; // 0 = Empate, 1 = Vitória , 2 = Derrota

		if (p1.jogada == p2.jogada) {
			vitorioso = 0;
			return vitorioso;
		}
		if (p1.jogada == "pedra")
		{
			vitorioso = (p2.jogada == "tesoura") ? 1 : 2;
		}
		else if (p1.jogada == "papel")
		{
			vitorioso = (p2.jogada == "pedra") ? 1 : 2;
		}
		else if (p1.jogada == "tesoura")
		{
			vitorioso = (p2.jogada == "papel") ? 1 : 2;
		}
		return vitorioso;
	}
};

bool verifica_opcao_invalida(string& opcao) {
	if (opcao != "pedra" && opcao != "papel" && opcao != "tesoura") {
		cout << "Opção inválida, digite: pedra, papel ou tesoura." << endl;
		return true;
	}
	return false;
}

int main() {
	srand(time(0)); //seed para gerar numero aleatório
	setlocale(LC_ALL, "Portuguese");

	Player p1, p2; //Inicializa variáveis para armazenar dados dos jogadores
	do
	{
		int modo = 0;
		cout << "\nBem vindo ao jogo Pedra, Papel e Tesoura!" << endl;
		cout << "Como deseja jogar? \n1. Jogador1 x Computador \n2. Jogador1 x Jogador2 \n3. Computador x Computador" << endl;
		cin >> modo;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Modo inválido, insira um valor de 1 a 3\n" << endl;
			continue;
		}
		switch (modo) //Menu para escolher modo de jogo
		{
		case 1: // Jogador x Máquina
			cout << "Jogador 1, escolha sua jogada: pedra , papel ou tesoura " << endl;
			cin >> p1.jogada;
			transform(p1.jogada.begin(), p1.jogada.end(), p1.jogada.begin(), ::tolower);
			if (verifica_opcao_invalida(p1.jogada)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			};

			p2.jogada = p2.sorteia_jogada(); // Jogada da máquina
			break;
		case 2: // Jogador x Jogador
			cout << "Jogador 1, escolha sua jogada: pedra , papel ou tesoura " << endl;
			cin >> p1.jogada;
			cout << "Jogador 2, escolha sua jogada: pedra , papel ou tesoura " << endl;
			cin >> p2.jogada;
			if (verifica_opcao_invalida(p1.jogada) || verifica_opcao_invalida(p2.jogada)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			};
			break;
		case 3: // Máquina x Máquina
			p1.jogada = p1.sorteia_jogada(); // Jogada da máquina 1
			p2.jogada = p2.sorteia_jogada(); // Jogada da máquina 2
			break;
		default:
			cout << "Modo inválido, insira um valor de 1 a 3\n" << endl;
			continue;
		}

		break;
	} while (true);

	cout << " A jogada do Jogador 1 foi : " << p1.jogada << " e a jogada do Jogador 2 foi : " << p2.jogada << endl;
	cout << "\nFim de jogo, você " << ganhou[Player::verifica_vitoria(p1, p2)] << endl; // Exibe o resultado

	system("pause");
	return 0;
}