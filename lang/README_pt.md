# 🚀 Guia de Compilação de Kernel com GitHub Actions

🌐 Idiomas disponíveis: [Indonésio 🇮🇩](README_id.md) | [Japonês 🇯🇵](README_jp.md) | [Espanhol 🇪🇸](README_es.md)

Bem-vindo!  
Este repositório oferece um **workflow do GitHub Actions pré-configurado** para compilar kernels facilmente através da interface do GitHub.

---

## 📝 Início Rápido: Faça Fork e Configure

1. **Faça fork deste repositório**  
   Clique no botão **Fork** no canto superior direito para criar sua própria cópia.

2. **Adicione um Token de Acesso Pessoal (GH_TOKEN) aos Secrets**  
   - Vá até as **Settings** → **Secrets and variables** → **Actions** do seu repositório.
   - Clique em **New repository secret**.
   - Dê o nome `GH_TOKEN`.
   - Cole seu [Token de Acesso Pessoal do GitHub](https://github.com/settings/tokens) com permissões `repo` e `workflow`.
   - Clique em **Add secret**.

---

## 🛠 Como Iniciar uma Compilação

1. Vá até a aba **Actions**.
2. Selecione o workflow chamado **builder**.
3. Clique em **Run workflow** e preencha os seguintes campos:

| Campo | Descrição | Exemplo |
|:------|:----------|:--------|
| **Custom kernel source URL** | URL do repositório Git com o código-fonte do kernel. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Marque se o repositório for privado. | (Deixe desmarcado se for público) |
| **Kernel branch** | Nome do branch para compilar. | `google` |
| **Device (defconfig)** | Nome do dispositivo ou defconfig a ser usado. | `gki` |
| **Kernel source name** | Nome para a pasta do kernel. | `kernel_msm-5.15` |
| **Custom localversion name** | *(Opcional)* Sufixo para a versão do kernel. | `-testbuild` |
| **Choose KernelSU version** | *(Opcional)* Versão do KernelSU a ser aplicada. | `None` |

---

> ✅ Clique em **Run workflow** para começar a compilação!

---
