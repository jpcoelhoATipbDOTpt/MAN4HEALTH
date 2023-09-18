# Gateway DRAGINO DSL08

Firmware associado à atualização da gateway e script Lua para processamento dos pacotes LoRa.

## 
- config zone
       - option name 'wan'
       - list network 'wan'
       - list network 'wwan'
       - list network 'wan6'
       - list network 'cellular'

## Parametrização do payload formater
. Usando o putty, aceder ao dispositivo via SSH (por defeito, root e dragino)
. navegar-se até ao diretório /etc/lora/decoder
. criar o ficheiro /etc/lora/decoder# vim Dragino_MQTT
. colar o conteúdo do payload decoder
. carregar na tecla “escape”, escrever :wq e alterar para executável com chmod +x Dragino_MQTT





