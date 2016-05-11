Universidade de Brasília
Software Básico - 2016/01

Alunos:
	Anderson Pinheiro Zago - 12/0044706
	Ícaro da Costa Mota - 12/0051389

Instruções de utilização
	Coloque os arquivos que deseja montar na pasta files (cd ../files/)
	Ao executar o programa, será lhe dado 2 opções:
		1 Digitar o nome do arquivo que deseja montar sem a extensão do arquivo. Os arquivos gerados estarão na pasta assembled (cd ../assembled)
		2 Ir para o menu de ligação

	No menu de ligação, será lhe pedido o nome do primeiro e segundo arquivos que deseja ligar e o nome do arquivo que deseja gerar.


Instruções de compilação (Linux com cmake recente versão 2.8 ou acima)
	Dentro da pasta build, execute:

        cmake ..
        make -j4

    	O executável foi gerado e colocado em build/

Instruções de execução
	Ainda dentro da pasta build, executar o arquivo Tradutor, com o comando
		./Tradutor