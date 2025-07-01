# kernel_msm-5.15

Fonte do kernel e construtor para Redmi Note 12 4G NFC (topaz/tapas)

## Visão Geral

Este repositório contém o código-fonte do kernel e scripts de compilação para os modelos Redmi Note 12 4G NFC, com codinomes `topaz` e `tapas`. É baseado na versão 5.15 do kernel Linux (branch msm-5.15) e adaptado para plataformas Qualcomm MSM.

Este projeto é destinado a desenvolvedores, mantenedores e usuários avançados que desejam compilar, personalizar ou modificar o kernel para estes modelos específicos de dispositivos.

## Recursos

- **Linux Kernel 5.15:** Base de kernel atualizada para segurança, desempenho e compatibilidade de dispositivos aprimorados.
- **Suporte Específico do Dispositivo:** Personalizações, árvores de dispositivos e drivers para as variantes `topaz` e `tapas`.
- **Scripts de Compilação:** Ferramentas e scripts para um processo de compilação simplificado.
- **Patches e Correções:** Integração de patches importantes para estabilidade e desempenho do dispositivo.

## Compilando o Kernel usando GitHub Actions

Este repositório suporta a compilação do kernel usando GitHub Actions, que automatiza o processo de compilação na nuvem.

### Passos

1. **Fazer Fork do Repositório**  
   Clique no botão "Fork" no canto superior direito desta página para criar sua própria cópia do repositório.

2. **Configurar Parâmetros de Compilação**  
   - Se necessário, edite o arquivo de workflow (geralmente localizado em `.github/workflows/`) para personalizar parâmetros de compilação, como variante do dispositivo ou opções do compilador.
   - Você também pode usar secrets do repositório para definir variáveis de ambiente sensíveis com segurança.

3. **Disparar a Compilação**  
   - Vá para a aba **Actions** no seu repositório forkado.
   - Selecione o workflow (ex: "Kernel Build") e clique em **Run workflow**.
   - Opcionalmente, especifique parâmetros de compilação se o workflow suportar entradas.

4. **Aguardar Conclusão**  
   - O processo de compilação iniciará automaticamente. Você pode monitorar logs e progresso na aba Actions.
   - Uma vez finalizado, o kernel compilado e quaisquer artefatos (como `Image.gz-dtb` ou zips flasháveis) estarão disponíveis no resumo da execução do workflow sob **Artifacts**.

5. **Baixar Artefatos**  
   - Baixe o kernel compilado ou zip empacotado da seção de artefatos do workflow.

### Notas

- Você pode precisar habilitar GitHub Actions no seu fork antes de executar o workflow pela primeira vez.
- Se encontrar erros ou falhas de compilação, revise os logs para solução de problemas.
- Para personalização avançada, você pode editar os arquivos yaml do workflow em `.github/workflows/`.

## [Opcional] Envio Automatizado de Arquivos via Bot do Telegram

Você pode automatizar o envio dos arquivos de kernel compilados diretamente para o Telegram usando um bot após o processo de compilação.

### Como Habilitar

1. **Criar um Bot do Telegram**  
   - Converse com [@BotFather](https://t.me/BotFather) para criar um novo bot e obter seu `TELEGRAM_BOT_TOKEN`.

2. **Configurar GitHub Secrets**  
   - Vá para **Settings** do seu repositório > **Secrets and variables** > **Actions**.
   - Adicione um novo secret do repositório:
     - Nome: `TELEGRAM_BOT_TOKEN`
     - Valor: (Preencha com seu token da API do bot do Telegram)

3. **Definir o Destinatário**  
   - Adicione outro secret chamado `TELEGRAM_CHAT_ID` com o ID do chat do seu usuário ou grupo do Telegram.

4. **Integração do Workflow**  
   - Certifique-se de que seu workflow do GitHub Actions inclua passos/scripts para enviar artefatos usando seu bot.  
   - Exemplo de trecho de script (usando curl):

     ```sh
     curl -F document=@path_to_artifact.zip "https://api.telegram.org/bot${{ secrets.TELEGRAM_BOT_TOKEN }}/sendDocument?chat_id=${{ secrets.TELEGRAM_CHAT_ID }}&caption=Compilação do kernel concluída!"
     ```

   - Preencha o `TELEGRAM_BOT_TOKEN` com sua API do bot do Telegram.

5. **Pronto!**  
   - Após uma compilação bem-sucedida, seu arquivo de kernel será enviado automaticamente para seu chat do Telegram.

## Licenciamento

Este repositório contém tanto código-fonte do kernel quanto scripts/ferramentas de construção.  
**As licenças são as seguintes:**

- **Código-fonte do kernel:**  
  Licenciado sob a GNU General Public License v2.0 (GPLv2). Veja o arquivo [LICENSE](LICENSE) para detalhes.

- **Scripts de construção e automação (incluindo GitHub Actions):**  
  Licenciado sob a GNU General Public License v3.0 (GPLv3). Veja o arquivo [builder/LICENSE](builder/LICENSE) para detalhes.

## Contribuindo

Contribuições são bem-vindas! Por favor, abra issues ou envie pull requests para correções de bugs, melhorias ou aprimoramentos específicos do dispositivo.

## Aviso Legal

Este projeto é destinado a usuários avançados e desenvolvedores. Fazer flash de kernels personalizados pode anular a garantia do seu dispositivo ou causar comportamentos indesejados. Proceda com cautela e sempre faça backup dos seus dados.

---

Para perguntas, issues ou suporte, por favor abra uma issue neste repositório.