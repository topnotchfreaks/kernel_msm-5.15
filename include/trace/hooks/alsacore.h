/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM alsacore
#define TRACE_INCLUDE_PATH trace/hooks

#if !defined(_TRACE_HOOK_ALSACORE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_HOOK_ALSACORE_H
#include <trace/hooks/vendor_hooks.h>
#include <sound/soc.h>
/*
 * Following tracepoints are not exported in tracefs and provide a
 * mechanism for vendor modules to hook and extend functionality
 */

DECLARE_HOOK(android_vh_pcm_sanity_check_extn,
             TP_PROTO(struct snd_pcm_substream *p),
             TP_ARGS(p));

DECLARE_HOOK(android_vh_snd_pcm_pre_start_extn,
             TP_PROTO(int *ret, struct snd_pcm_substream *sub),
             TP_ARGS(ret, sub));

DECLARE_HOOK(android_vh_soc_new_pcm_extn,
             TP_PROTO(struct snd_pcm_str **stream, struct snd_soc_pcm_runtime *rtd, struct snd_pcm *pcm),
             TP_ARGS(stream, rtd, pcm));

#endif /* _TRACE_HOOK_ALSACORE_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
