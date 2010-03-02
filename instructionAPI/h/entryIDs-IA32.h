/*
 * Copyright (c) 1996-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#if !defined(ENTRYIDS_IA32_H)
#define ENTRYIDS_IA32_H

#include "dyntypes.h"

enum entryID {
  e_jb = 0,
  e_jb_jnaej_j,
  e_jbe,
  e_jcxz_jec,
  e_jl,
  e_jle,
  e_jmp,
  e_jmpe,
  e_jnb,
  e_jnb_jae_j,
  e_jnbe,
  e_jnl,
  e_jnle,
  e_jno,
  e_jnp,
  e_jns,
  e_jnz,
  e_jo,
  e_jp,
  e_js,
  e_jz,
  e_loop,
  e_loope,
  e_loopn,
  e_call,
  e_cmp,
  e_cmppd,
  e_cmpps,
  e_cmpsb,
  e_cmpsd,
  e_cmpss,
  e_cmpsw,
  e_cmpxch,
  e_cmpxch8b,
  e_ret_far,
  e_ret_near,
  e_prefetch,
  e_prefetchNTA,
  e_prefetchT0,
  e_prefetchT1,
  e_prefetchT2,
  e_prefetch_w,
  e_prefetchw,
  e_No_Entry,
  e_aaa,
  e_aad,
  e_aam,
  e_aas,
  e_adc,
  e_add,
  e_addpd,
  e_addps,
  e_addsd,
  e_addss,
  e_addsubpd,
  e_addsubps,
  e_and,
  e_andnpd,
  e_andnps,
  e_andpd,
  e_andps,
  e_arpl,
  e_bound,
  e_bsf,
  e_bsr,
  e_bswap,
  e_bt,
  e_btc,
  e_btr,
  e_bts,
  e_cbw_cwde,
  e_clc,
  e_cld,
  e_clflush,
  e_cli,
  e_clts,
  e_cmc,
  e_cmovbe,
  e_cmove,
  e_cmovnae,
  e_cmovnb,
  e_cmovnbe,
  e_cmovne,
  e_cmovng,
  e_cmovnge,
  e_cmovnl,
  e_cmovno,
  e_cmovns,
  e_cmovo,
  e_cmovpe,
  e_cmovpo,
  e_cmovs,
  e_comisd,
  e_comiss,
  e_cpuid,
  e_cvtdq2pd,
  e_cvtdq2ps,
  e_cvtpd2dq,
  e_cvtpd2pi,
  e_cvtpd2ps,
  e_cvtpi2pd,
  e_cvtpi2ps,
  e_cvtps2dq,
  e_cvtps2pd,
  e_cvtps2pi,
  e_cvtsd2si,
  e_cvtsd2ss,
  e_cvtsi2sd,
  e_cvtsi2ss,
  e_cvtss2sd,
  e_cvtss2si,
  e_cvttpd2dq,
  e_cvttpd2pi,
  e_cvttps2dq,
  e_cvttps2pi,
  e_cvttsd2si,
  e_cvttss2si,
  e_cwd_cdq,
  e_daa,
  e_das,
  e_dec,
  e_div,
  e_divpd,
  e_divps,
  e_divsd,
  e_divss,
  e_emms,
  e_enter,
  e_extrq,
  e_fadd,
  e_fbld,
  e_fbstp,
  e_fcom,
  e_fcomp,
  e_fdiv,
  e_fdivr,
  e_femms,
  e_fiadd,
  e_ficom,
  e_ficomp,
  e_fidiv,
  e_fidivr,
  e_fild,
  e_fimul,
  e_fist,
  e_fistp,
  e_fisttp,
  e_fisub,
  e_fisubr,
  e_fld,
  e_fldcw,
  e_fldenv,
  e_fmul,
  e_fnop,
  e_frstor,
  e_fsave,
  e_fst,
  e_fstcw,
  e_fstenv,
  e_fstp,
  e_fstsw,
  e_fsub,
  e_fsubr,
  e_fucomp,
  e_fxrstor,
  e_fxsave,
  e_haddpd,
  e_haddps,
  e_hlt,
  e_hsubpd,
  e_hsubps,
  e_idiv,
  e_imul,
  e_in,
  e_inc,
  e_insb,
  e_insertq,
  e_insw_d,
  e_int,
  e_int3,
  e_int1,
  e_int80,
  e_into,
  e_invd,
  e_invlpg,
  e_iret,
  e_lahf,
  e_lar,
  e_lddqu,
  e_ldmxcsr,
  e_lds,
  e_lea,
  e_leave,
  e_les,
  e_lfence,
  e_lfs,
  e_lgdt,
  e_lgs,
  e_lidt,
  e_lldt,
  e_lmsw,
  e_lodsb,
  e_lodsw,
  e_lsl,
  e_lss,
  e_ltr,
  e_maskmovdqu,
  e_maskmovq,
  e_maxpd,
  e_maxps,
  e_maxsd,
  e_maxss,
  e_mfence,
  e_minpd,
  e_minps,
  e_minsd,
  e_minss,
  e_mmxud,
  e_mov,
  e_movapd,
  e_movaps,
  e_movd,
  e_movddup,
  e_movdq2q,
  e_movdqa,
  e_movdqu,
  e_movhpd,
  e_movhps,
  e_movhps_movlhps,
  e_movlpd,
  e_movlps,
  e_movlps_movhlps,
  e_movmskpd,
  e_movmskps,
  e_movntdq,
  e_movnti,
  e_movntpd,
  e_movntps,
  e_movntq,
  e_movntsd,
  e_movntss,
  e_movq,
  e_movq2dq,
  e_movsb,
  e_movsd,
  e_movshdup,
  e_movsldup,
  e_movss,
  e_movsw_d,
  e_movsx,
  e_movsxd,
  e_movupd,
  e_movups,
  e_movzx,
  e_mul,
  e_mulpd,
  e_mulps,
  e_mulsd,
  e_mulss,
  e_neg,
  e_nop,
  e_not,
  e_or,
  e_orpd,
  e_orps,
  e_out,
  e_outsb,
  e_outsw_d,
  e_packssdw,
  e_packsswb,
  e_packuswb,
  e_paddb,
  e_paddd,
  e_paddq,
  e_paddsb,
  e_paddsw,
  e_paddusb,
  e_paddusw,
  e_paddw,
  e_pand,
  e_pandn,
  e_pavgb,
  e_pavgw,
  e_pcmpeqb,
  e_pcmpeqd,
  e_pcmpeqw,
  e_pcmpgdt,
  e_pcmpgtb,
  e_pcmpgtw,
  e_pextrw,
  e_pinsrw,
  e_pmaddwd,
  e_pmaxsw,
  e_pmaxub,
  e_pminsw,
  e_pminub,
  e_pmovmskb,
  e_pmulhuw,
  e_pmulhw,
  e_pmullw,
  e_pmuludq,
  e_pop,
  e_popa_d,
  e_popf_d,
  e_popcnt,
  e_por,
  e_psadbw,
  e_pshufd,
  e_pshufhw,
  e_pshuflw,
  e_pshufw,
  e_pslld,
  e_pslldq,
  e_psllq,
  e_psllw,
  e_psrad,
  e_psraw,
  e_psrld,
  e_psrldq,
  e_psrlq,
  e_psrlw,
  e_psubb,
  e_psubd,
  e_psubsb,
  e_psubsw,
  e_psubusb,
  e_psubusw,
  e_psubw,
  e_punpckhbw,
  e_punpckhdq,
  e_punpckhqd,
  e_punpckhwd,
  e_punpcklbw,
  e_punpcklqd,
  e_punpcklqld,
  e_punpcklwd,
  e_push,
  e_pusha_d,
  e_pushf_d,
  e_pxor,
  e_rcl,
  e_rcpps,
  e_rcpss,
  e_rcr,
  e_rdmsr,
  e_rdpmc,
  e_rdtsc,
  e_rol,
  e_ror,
  e_rsm,
  e_rsqrtps,
  e_rsqrtss,
  e_sahf,
  e_salc,
  e_sar,
  e_sbb,
  e_scasb,
  e_scasw_d,
  e_setb,
  e_setbe,
  e_setl,
  e_setle,
  e_setnb,
  e_setnbe,
  e_setnl,
  e_setnle,
  e_setno,
  e_setnp,
  e_setns,
  e_setnz,
  e_seto,
  e_setp,
  e_sets,
  e_setz,
  e_sfence,
  e_sgdt,
  e_shl_sal,
  e_shld,
  e_shr,
  e_shrd,
  e_shufpd,
  e_shufps,
  e_sidt,
  e_sldt,
  e_smsw,
  e_sqrtpd,
  e_sqrtps,
  e_sqrtsd,
  e_sqrtss,
  e_stc,
  e_std,
  e_sti,
  e_stmxcsr,
  e_stosb,
  e_stosw_d,
  e_str,
  e_sub,
  e_subpd,
  e_subps,
  e_subsd,
  e_subss,
  e_syscall,
  e_sysenter,
  e_sysexit,
  e_sysret,
  e_test,
  e_ucomisd,
  e_ucomiss,
  e_ud,
  e_ud2,
  e_ud2grp10,
  e_unpckhpd,
  e_unpckhps,
  e_unpcklpd,
  e_unpcklps,
  e_verr,
  e_verw,
  e_vmread,
  e_vmwrite,
  e_vsyscall,
  e_wait,
  e_wbinvd,
  e_wrmsr,
  e_xadd,
  e_xchg,
  e_xlat,
  e_xor,
  e_xorpd,
  e_xorps,
  e_fp_generic,
  e_3dnow_generic
};

#if defined(__GNUC__)
//***************** GCC ***********************
  #if !defined(cap_tr1)
  //**************** GCC < 4.3.0 ************
  namespace __gnu_cxx {
    
    template<> struct hash<entryID> {
      hash<unsigned int> h;
      unsigned operator()(const entryID &e) const 
      {
	return h(static_cast<unsigned int>(e));
      };
    };
  }
	#else
  namespace std
  {
    namespace tr1
    {
      template <>
      struct hash<entryID>
      {
	size_t operator()(const entryID &eid) const
	{
	  return static_cast<size_t>(eid);
	}
      };
    }
  }
	#endif
#endif
extern dyn_hash_map<entryID, std::string> entryNames_IAPI;

#endif // defined(ENTRYIDS_IA32_H)
