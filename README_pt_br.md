# MultiplayerLearn
Learn multiplayer topics of UE4

## Modelo Client Servidor
- Um único servidor com autoridade sobre o jogo
- Servidor toma decisões importantes
    * Contém todo estado autoritário
    * lida com conexões de rede
    * viaja para novos mapas
    * fluxo geral do jogo(iniciar,terminar)

- Linhas de comandos
    * Server Listen
    ``UE4Editor.exe [ProjectName] [MapName]?Listen -game``
    * Server Dedicated
    ``UE4Editor.exe [ProjectName] [MapName] -server -game -log``
    * Client
    ``UE4Editor.exe [ProjectName] [ServerIP] -game``

- Ator GameMode é somente do servido, Para comunicar esse estado ao cliente é usado o **GameState**
- Processo de conexão
    1) Cliente envia solicitação de conexão
    2) Se o server aceitou, ele envia para o mapa atual
    3) O servidor aguarda o client carregar o mapa
    4) Depois de carregado o **GameMode** tem liberdade de rejeitar pelo ``AGameMode::PreLogin()``
    5) Se aceito, o server chama ``AGameMode::Login()``
    6) Se tudo certo é chamado ``AGameMode::PostLogin``

