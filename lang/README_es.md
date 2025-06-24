# kernel_msm-5.15

Fuente del kernel y constructor para Redmi Note 12 4G NFC (topaz/tapas)

## Resumen

Este repositorio contiene el código fuente del kernel y scripts de compilación para los modelos Redmi Note 12 4G NFC, con nombres en clave `topaz` y `tapas`. Está basado en la versión 5.15 del kernel Linux (rama msm-5.15) y adaptado para plataformas Qualcomm MSM.

Este proyecto está destinado a desarrolladores, mantenedores y usuarios avanzados que deseen compilar, personalizar o modificar el kernel para estos modelos específicos de dispositivos.

## Características

- **Linux Kernel 5.15:** Base de kernel actualizada para mayor seguridad, rendimiento y compatibilidad de dispositivos.
- **Soporte Específico del Dispositivo:** Personalizaciones, árboles de dispositivos y controladores para las variantes `topaz` y `tapas`.
- **Scripts de Compilación:** Herramientas y scripts para un proceso de compilación optimizado.
- **Parches y Correcciones:** Integración de parches importantes para la estabilidad y rendimiento del dispositivo.

## Compilando el Kernel usando GitHub Actions

Este repositorio soporta la compilación del kernel usando GitHub Actions, que automatiza el proceso de compilación en la nube.

### Pasos

1. **Hacer Fork del Repositorio**  
   Haz clic en el botón "Fork" en la parte superior derecha de esta página para crear tu propia copia del repositorio.

2. **Configurar Parámetros de Compilación**  
   - Si es necesario, edita el archivo de workflow (generalmente ubicado en `.github/workflows/`) para personalizar parámetros de compilación, como variante del dispositivo u opciones del compilador.
   - También puedes usar secrets del repositorio para establecer variables de entorno sensibles de forma segura.

3. **Activar la Compilación**  
   - Ve a la pestaña **Actions** en tu repositorio forkeado.
   - Selecciona el workflow (ej: "Kernel Build") y haz clic en **Run workflow**.
   - Opcionalmente, especifica parámetros de compilación si el workflow soporta entradas.

4. **Esperar la Finalización**  
   - El proceso de compilación comenzará automáticamente. Puedes monitorear los logs y el progreso en la pestaña Actions.
   - Una vez terminado, el kernel compilado y cualquier artefacto (como `Image.gz-dtb` o zips flasheables) estarán disponibles en el resumen de ejecución del workflow bajo **Artifacts**.

5. **Descargar Artefactos**  
   - Descarga el kernel compilado o zip empaquetado desde la sección de artefactos del workflow.

### Notas

- Es posible que necesites habilitar GitHub Actions en tu fork antes de ejecutar el workflow por primera vez.
- Si encuentras errores o fallos de compilación, revisa los logs para solucionar problemas.
- Para personalización avanzada, puedes editar los archivos yaml del workflow en `.github/workflows/`.

## [Opcional] Envío Automatizado de Archivos vía Bot de Telegram

Puedes automatizar el envío de los archivos de kernel compilados directamente a Telegram usando un bot después del proceso de compilación.

### Cómo Habilitar

1. **Crear un Bot de Telegram**  
   - Habla con [@BotFather](https://t.me/BotFather) para crear un nuevo bot y obtener tu `TELEGRAM_BOT_TOKEN`.

2. **Configurar GitHub Secrets**  
   - Ve a **Settings** de tu repositorio > **Secrets and variables** > **Actions**.
   - Añade un nuevo secret del repositorio:
     - Nombre: `TELEGRAM_BOT_TOKEN`
     - Valor: (Completa con tu token de la API del bot de Telegram)

3. **Establecer el Destinatario**  
   - Añade otro secret llamado `TELEGRAM_CHAT_ID` con el ID de chat de tu usuario o grupo de Telegram.

4. **Integración del Workflow**  
   - Asegúrate de que tu workflow de GitHub Actions incluya pasos/scripts para enviar artefactos usando tu bot.  
   - Ejemplo de fragmento de script (usando curl):

     ```sh
     curl -F document=@path_to_artifact.zip "https://api.telegram.org/bot${{ secrets.TELEGRAM_BOT_TOKEN }}/sendDocument?chat_id=${{ secrets.TELEGRAM_CHAT_ID }}&caption=¡Compilación del kernel completada!"
     ```

   - Completa el `TELEGRAM_BOT_TOKEN` con tu API del bot de Telegram.

5. **¡Listo!**  
   - Después de una compilación exitosa, tu archivo de kernel será enviado automáticamente a tu chat de Telegram.

## Licenciamiento

Este repositorio contiene tanto código fuente del kernel como scripts/herramientas de construcción.  
**Las licencias son las siguientes:**

- **Código fuente del kernel:**  
  Licenciado bajo la GNU General Public License v2.0 (GPLv2). Ver el archivo [LICENSE](LICENSE) para detalles.

- **Scripts de construcción y automatización (incluidas GitHub Actions):**  
  Licenciado bajo la GNU General Public License v3.0 (GPLv3). Ver el archivo [builder/LICENSE](builder/LICENSE) para detalles.

## Contribuyendo

¡Las contribuciones son bienvenidas! Por favor abre issues o envía pull requests para corrección de errores, mejoras o mejoras específicas del dispositivo.

## Descargo de Responsabilidad

Este proyecto está destinado a usuarios avanzados y desarrolladores. Flashear kernels personalizados puede anular la garantía de tu dispositivo o causar comportamientos no deseados. Procede con precaución y siempre respalda tus datos.

---

Para preguntas, issues o soporte, por favor abre un issue en este repositorio.