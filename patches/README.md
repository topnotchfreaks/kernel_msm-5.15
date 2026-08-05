# ApkeSU + SUSFS для этого билдера

## Что здесь

| Файл | Назначение |
| --- | --- |
| `susfs-apkesu.patch` | Интеграция susfs4ksu в дерево ApkeSU. Применяется внутри `KernelSU/` после `kernel/setup.sh` ApkeSU. Заменяет `susfs4ksu/kernel_patches/KernelSU/10_enable_susfs_for_ksu.patch`, который к ApkeSU не подходит. |
| `advanced_build.yml` | Обновлённый workflow: третий вариант сборки `apkesu` рядом с `noksu` и `wildksu`. |

## Установка workflow

GitHub App, которым открывался PR, не имеет права писать в `.github/workflows/`,
поэтому новый workflow лежит здесь. Скопируйте его на место вручную:

```bash
cp patches/advanced_build.yml .github/workflows/advanced_build.yml
git commit -am "advanced_build: add ApkeSU variant"
```

`patches/susfs-apkesu.patch` уже лежит там, где его ждёт workflow.

## Почему ApkeSU нельзя патчить штатным патчем susfs4ksu

`10_enable_susfs_for_ksu.patch` написан под ревизию KernelSU с *ручными* хуками в ядре.
На дереве ApkeSU он даёт 11 отклонённых ханков и, что хуже, при применении:

* вырезает собственный хук-слой ApkeSU (`hook/lsm_hook.o`, `hook/syscall_hook_manager.o`,
  `hook/tp_marker.o`, `infra/symbol_resolver.o`, arm64 syscall hooks);
* переписывает `feature/sucompat.c` и `hook/setuid_hook.c` под другие сигнатуры;
* удаляет опцию `CONFIG_KSU_X86_PATCH_SYSCALL_DISPATCHER`;
* ломает `do_manage_mark()` в `supercall/dispatch.c`.

Для сравнения: у Wild KSU SUSFS входит в само дерево (`config KSU_SUSFS` есть в его
`kernel/Kconfig`), поэтому там этот патч просто падал в warning и ни на что не влиял.

## Что делает `susfs-apkesu.patch`

Только добавляет, ничего не удаляет:

* опции `CONFIG_KSU_SUSFS*` в `kernel/Kconfig` (по умолчанию `n`, workflow включает явно);
* `susfs_init()` в `kernel/core/init.c`;
* sid-хелперы SUSFS в `kernel/selinux/` и `susfs_set_batch_sid()`;
* `ksu_handle_sys_reboot()` — точку входа команд SUSFS, которую kernel-side патч
  вызывает прямо из `SYSCALL_DEFINE4(reboot)`;
* пометку процесса как umounted и запуск отложенной работы SUSFS в `kernel/feature/kernel_umount.c`;
* новый `kernel/feature/susfs_compat.c` — гейт-ключи и пустые заглушки для *ручных*
  хуков SUSFS (su compat, safe mode по кнопкам, init.rc). ApkeSU реализует всё это
  своими kprobe/syscall-хуками, поэтому ручные хуки остаются выключенными, иначе
  syscall'ы обрабатывались бы дважды;
* снимает `static` с внутренностей `selinux_hide`, на которые ссылается kernel-side патч;
* переименования, чтобы освободить имена, принадлежащие kernel-side патчу:
  `ksu_su_compat_enabled` → `ksu_su_compat_toggle`, двухаргументный
  `ksu_handle_setresuid` → `ksu_handle_setresuid_transition`.

## Как выбирается рут в workflow (v2, на стоковой базе)

Имена вариантов матрицы намеренно оставлены стоковыми — `noksu` и `ksu`. Это важно:
AnyKernel3 у topnotchfreaks **хардкодит** имена файлов `Image.ksu` и `Image.noksu`
в `anykernel.sh` и по ним предлагает выбор при прошивке. Если переименовать варианты
(например в `apkesu`), ZIP соберётся, но AnyKernel3 не найдёт образ и прошивка не пройдёт.

Поэтому выбор реализации рута — отдельный вход:

| Вход | Значения | Что делает |
| --- | --- | --- |
| `buildKSU` | `noksu` / `ksu` / `both` | как в стоке: собирать без рута, с рутом, или оба образа в один ZIP |
| `ksuFlavor` | `wildksu` / `apkesu` | какой именно KSU ставить в вариант `ksu` |
| `apkeSuRef` | branch/tag/commit | ревизия ApkeSU, по умолчанию `ApkeSU` |

Относительно стокового файла изменены всего две строки (условие шага Wild KSU и подпись
варианта в Telegram), остальное — добавленные шаги. Шаг BBG оставлен ровно как в стоке.

## Важные ограничения

* **`CONFIG_KSU=y` обязателен.** Kernel-side патч SUSFS ссылается на символы KernelSU
  из встроенного кода ядра, в режиме LKM (`CONFIG_KSU=m`) линковка не пройдёт.
* **Менеджер другой:** ApkeSU ждёт APK с пакетом `io.github.fixz.apkesu`, приложение
  Wild KSU с этим ядром не подойдёт.
* **Опции SUSFS сократились.** Актуальный susfs4ksu определяет только:
  `KSU_SUSFS`, `SUS_PATH`, `SUS_MOUNT`, `SUS_KSTAT`, `SUS_MAP`, `SPOOF_UNAME`,
  `SPOOF_CMDLINE_OR_BOOTCONFIG`, `OPEN_REDIRECT`, `ENABLE_LOG`, `HIDE_KSU_SUSFS_SYMBOLS`.
  Старых `HAS_MAGIC_MOUNT`, `AUTO_ADD_*`, `TRY_UMOUNT`, `SUS_SU` больше нет —
  в defconfig они остались только для варианта `wildksu`, у которого свой Kconfig.
* Патч привязан к ревизии ApkeSU `f2d024608d99` и susfs4ksu `ccb1918684b2`.
  Если ApkeSU уедет вперёд и патч начнёт отклоняться, workflow упадёт с явной ошибкой
  (`::error::ApkeSU SUSFS patch left rejected hunks`), а не соберёт полусломанное ядро.
