# trabalho1-criptografia
Implementação do algoritmo de criptografia AES trocando a caixa-S por outra cifra, para fins de comparação com o algoritmo original

## Da Execução
Após clonar o repositório, basta executar "make" e o programa será compilado, o executável gerado se chama "aes".
A execução necessita de 3 argumentos: o nome do texto limpo, a chave, o nome do arquivo de saída.
$ ./aes dados80mb.txt senha.txt saida.txt

## Da Comparação de Tempo
Segue uma sugestão de comando para executar o AES do Openssl, utilizando a mesma chave utilizada no trabalho
$ cat dados80mb.txt| openssl enc -aes-128-ecb -K 4348415645424f41455353414845494e -nosalt -nopad -out cifrado.txt

utilizando o bash "time" com a nossa implementação e a implementação do Openssl os seguintes tempos foram obtidos para um arquivo de 80Mb:

Execução do trabalho
real	0m24,656s
user	0m23,602s
sys	    0m0,701s

Execução do openssl
real	0m1,041s
user	0m0,071s
sys	    0m0,569s

## Da Implementação
Para cumprir os requisitos do trabalho, trocamos a Caixa-S pela Cifra Viginere, uma cifra polialfabetica com um tempo igual a de Cesar.
A justificativa para termos utilizado a linguagem C para o trabalho se da também pela facilidade de manipulações mais delicadas quanto ao acesso da memória.
A tecnica Unroll & Jam foi aplicada em quase todas as manipulações de matrizes que conseguimos identificar que era possível alterar.
Há também algumas melhorias menores, como por exemplo, expandir a chave apenas uma vez, antes de se iniciar o ciclo de codificação.