# 🚀 Guía de Compilación de Kernel con GitHub Actions

🌐 Idiomas disponibles: [Indonesio 🇮🇩](README_id.md) | [Japonés 🇯🇵](README_jp.md) | [Portugués 🇧🇷](README_pt.md)

¡Bienvenido!  
Este repositorio ofrece un **flujo de trabajo preconfigurado de GitHub Actions** para compilar kernels fácilmente desde la interfaz de GitHub.

---

## 📝 Inicio Rápido: Haz Fork y Configura

1. **Haz fork de este repositorio**  
   Haz clic en el botón **Fork** en la esquina superior derecha para crear tu propia copia.

2. **Agrega un Token de Acceso Personal (GH_TOKEN) a los Secrets**  
   - Ve a **Settings** → **Secrets and variables** → **Actions** en tu repositorio bifurcado.
   - Haz clic en **New repository secret**.
   - Nómbralo `GH_TOKEN`.
   - Pega tu [Token de Acceso Personal de GitHub](https://github.com/settings/tokens) con permisos `repo` y `workflow`.
   - Haz clic en **Add secret**.

---

## 🛠 Cómo Iniciar una Compilación

1. Ve a la pestaña **Actions**.
2. Selecciona el flujo de trabajo llamado **builder**.
3. Haz clic en **Run workflow** y completa los siguientes campos:

| Campo | Descripción | Ejemplo |
|:------|:------------|:--------|
| **Custom kernel source URL** | URL del repositorio Git del kernel. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Marca si el repositorio es privado. | (Déjalo sin marcar si es público) |
| **Kernel branch** | Nombre de la rama a compilar. | `google` |
| **Device (defconfig)** | Nombre del dispositivo o defconfig a usar. | `gki` |
| **Kernel source name** | Nombre para la carpeta del kernel. | `kernel_msm-5.15` |
| **Custom localversion name** | *(Opcional)* Sufijo para la versión del kernel. | `-testbuild` |
| **Choose KernelSU version** | *(Opcional)* Versión de KernelSU a aplicar. | `None` |

---

> ✅ ¡Haz clic en **Run workflow** para empezar la compilación!

---
