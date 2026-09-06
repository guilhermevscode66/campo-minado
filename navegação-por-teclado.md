###Navegação pelo teclado no tabuleiro de campo minado
###Explicação: 
O jogo de campo minado normalmente é jogado com o mouse. Isso é geralmente um problema para quem tem deviciência visual e usa leitor de tela, como é o caso deste "humilde" programador.
Nos terminais do linux, windows etc, a gentesempre utiliza o teclado para executar os mais diversos comandos. Isso é incrivelmente útil porque ao menos no linux, dá para fazer tudo no terminal, e, como os terminais são baseados em texto, e os leitores de tela (Os softwares queleem a tela do computador para nós) processam justamente o texto. Numa interface de usuário comun, dessas que qualquer aplicativo usa, o que faz com que o leitor de tela consiga ler os botões, os links, campos de texto para que o usuário consiga usar aquele software, é preciso que esses elementos visuais tenham um texto descritivo para o leitor de tela. Como o texto já é a forma de comunicação usada nos terminais, Dá para afirmar, com um gral de confiança bem alto, que as interfaces de texto / terminal são as mais acessíveis que existem para fazer um aplicativo, pelo menos para quem precisa usar o leitor de tela, um App.
Existem vários softwares que utilizam interface de terminal e que por isso são totalmente acessíveis para usuários de leitores de tela: docker, gcloud, mysql e postgre provavelmente, interpretadores do python, java, npm do react, o próprio compilador gcc, em fim, uma variedade de, se fossemos sitar todos, ficaria até amanhã escrevendo este readme, hehehe.

###O que foi feito no campo minado?
Implementei nele uma navegação pelas células do tabuleiro atravéz do teclado, para que o jogador consiga navegar entre as células do tabuleiro e tenha um feedback audível do leitor de tela, para saber em qual linha e coluna está.
###Principais atalhos:
*seta para cima: move para a linha acima
*seta para baixo: move para a linha abaixo
*seta para a direita: move uma coluna para a direita
*seta para a esquerda: move uma coluna para a esquerda
*enter: revela a célula celecionada, se tiver uma bomba termina o jogo
*q: sai do jogo

