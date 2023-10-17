/*
 * Copyright (c) 1996-2006 MIPS Technologies, Inc.
 * Copyright (C) 2009 CodeSourcery, LLC,
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *      copyright
 *        notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with
 *        the distribution.
 *      * Neither the name of MIPS Technologies Inc. nor the names of its
 *        contributors may be used to endorse or promote products derived
 *        from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * MIPS SDE kit implementation specific defines.
 */


#ifndef __KIT_IMPL_H__
#define __KIT_IMPL_H__

#ifndef __ASSEMBLER__

#include <stddef.h>
#include <sys/types.h>
#include "loongarch32/xcpt.h"

#define __need___va_list
#include <stdarg.h>

extern void	_scandevs (void);
extern void	_sig_raise (pid_t, int, struct xcptcontext *);
extern void	_sig_deliver (struct xcptcontext *);

extern void 	_xcpt_sigcatch (int, int);
extern void 	_xcpt_catch (unsigned int, int);
extern int	_xcpt_deliver (struct xcptcontext *);
extern int	_xcpt_signo (const struct xcptcontext *);

extern int 	_debug_handler (int, struct xcptcontext *);
extern void	_debug_breakpoint (void);
extern int	_debug_sighook (int);
extern int	_debug_enabled (void);
extern int	_debug_connected (void);
extern void	_rdebug_load (void);

/* called from crt0 */
extern void	_cop1_init (int);
extern void	_debug_init (int);
extern void	_debug_exit (int);

/* sbrk query interfaces */
long		_sbrk_totalpages (void);
long		_sbrk_availpages (void);
void		_sbrk_init (void);

/* new timer / interrupts */
unsigned int	_sbd_tickspersec (void);
unsigned int	_sbd_gettickval (void);
void		_sbd_settickcmp (unsigned int);

/* polled delays */
extern void	(_sbd_nsdelay) (unsigned long);
extern void	(_sbd_usdelay) (unsigned long);
extern void	(_sbd_msdelay) (unsigned long);

#ifdef INTR_SETMASK
/* new interrupts */
void		_sbd_intrinit (void);
int		_sbd_intrpoll (int);
void		_sbd_intrpending (intrset_t *);
void		_sbd_intrenable (int);
void		_sbd_intrprocmask (int, const intrset_t *, intrset_t *);
int		_sbd_intrnext (int);
void		(_sbd_intrenter) (void);
void		(_sbd_intrleave) (void);
int		_sbd_intrhandler (unsigned int, struct xcptcontext *);
int		_sbd_intrtype (int, const intrtype_t *, intrtype_t *);
int		_sbd_probable_ipl (unsigned int);
int		_sbd_intr_howmany (void);
#endif

/* interface to fairly dumb alphanumeric display panel */
struct panelmode;
struct panelinfo;
extern void 	_sbdpanelmessage (int, int, const char *, size_t nb, int);
extern void	_sbdpanelprogress (int);
extern void	_sbdpanelflash (int);		/* deprecated */
extern void	_sbdpanelmode (const struct panelmode *, struct panelmode *);
extern void	_sbdpanelclear (void);
extern void	_sbdpanelsize (int *, int *);	/* deprecated */
extern void	_sbdpanelinfo (struct panelinfo *);
extern int 	_sbdpanelinit (void);

/* low-level nvram access */
extern unsigned int 	_sbd_nvram_size (unsigned int *, unsigned int *);
extern void		_sbd_nvram_flush (int);
extern int		_sbd_nvram_hwtest (void);
extern unsigned char	_sbd_nvram_getbyte (unsigned int);
extern void		_sbd_nvram_setbyte (unsigned int, unsigned char);
extern unsigned short	_sbd_nvram_getshort (unsigned int);
extern void		_sbd_nvram_setshort (unsigned int, unsigned short);

/* low-level environment access */
extern unsigned int	_sbd_env_size (unsigned int *, unsigned int *);
extern int		_sbd_env_erase (unsigned int, unsigned int);
extern unsigned char 	_sbd_env_getbyte (unsigned int);
extern void		_sbd_env_getbytes (unsigned int, unsigned char *,
					   unsigned int);
extern void		_sbd_env_setbyte (unsigned int offset, unsigned char);
extern void		_sbd_env_setbytes (unsigned int, const unsigned char *,
					   unsigned int);
extern void		_sbd_env_flush (unsigned int);
extern int 		_sbd_env_force_reset (void);


/* equivalent for flash environment */
struct flashcookie;
extern const struct flashcookie *_sbd_flashenv_open (void);

/* high-level non-volatile environment */
extern char *		_sbd_getenv (const char *);
extern int		_sbd_setenv (const char *, const char *, int);
extern void		_sbd_unsetenv (const char *);
extern void		_sbd_mapenv (int (*)(const char *, const char *));
extern const char * 	_sbd_envinit (void);

/* memory layout */
struct sbd_region {
    paddr_t	base;
    size_t	size;
    int		type;
};

#define SBD_MEM_END	0
#define SBD_MEM_RAM	1

extern const struct sbd_region * _sbd_memlayout (void);

/* debug support routines */
extern void	_dbg_panic (const char *, ...);
extern void	_dbg_printf (const char *, ...);
extern int	_dbg_init (void);
extern int	_dbg_inch (void);
extern int	_dbg_inpoll (void);
extern void	_dbg_outch (int);
extern void	_dbg_drain (void);

extern void	_dbg_signals (void);
extern void	_dbg_enterhook (void);
extern int	_dbg_exithook (void);
extern void	_dbg_attachhook (void);
extern void	_dbg_detachhook (void);
extern int	_dbg_put_byte (vaddr_t va, unsigned char v);
extern unsigned int _dbg_get_byte (vaddr_t va, int *err);
extern int	_dbg_put_half (vaddr_t va, unsigned short v);
extern unsigned int _dbg_get_half (vaddr_t va, int *err);
extern int	_dbg_put_word (vaddr_t va, unsigned int v);
extern unsigned int _dbg_get_word (vaddr_t va, int *err);
extern int	_dbg_accessible (vaddr_t va, size_t len, int rw);
extern int	_dbg_cacheable (vaddr_t va);
extern paddr_t	_dbg_vtop (vaddr_t va);
 
struct fpactx;

/* debug thread support routines */
extern int	_dbg_getthread (struct xcptcontext *);
extern int	_dbg_newthread (void);
extern struct xcptcontext *
		_dbg_setthread (struct xcptcontext *, int, int);
extern struct xcptcontext *
		_dbg_contthread (struct xcptcontext *);
extern int	_dbg_querythread (int);
extern int	_dbg_restart (struct xcptcontext *, int);
extern int	_dbg_getfpactx (struct xcptcontext *, struct fpactx *);
extern void	_dbg_putfpactx (struct xcptcontext *, struct fpactx *);
extern void	_dbg_write (const char *, size_t);

/* used at start/_exit time */
extern void	_call_init_funcs (int);
extern void	_call_fini_funcs (void);

extern void	_muldiv_emu_init (void);
extern void	_mips16_entry_init (void);
extern void	_mips_unaligned_init (void);
extern void	_mips_ecchandler_init (void);

extern int	_mips_bremul (struct xcptcontext *, struct fpactx *,
			      unsigned int, vaddr_t *, int *);

extern int	_mips16_bremul (struct xcptcontext *, 
				unsigned short, vaddr_t *, vaddr_t *);

extern unsigned int _mips_clz (unsigned int);
extern unsigned int _mips_dclz (unsigned long long);

#endif /* ! __ASSEMBLER__ */

#endif /* __KIT_IMPL_H__ */
