	.file	"test_pile.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB2139:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE2139:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.text._ZNK11PileTableauI5PointE7estVideEv,"axG",@progbits,_ZNK11PileTableauI5PointE7estVideEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK11PileTableauI5PointE7estVideEv
	.type	_ZNK11PileTableauI5PointE7estVideEv, @function
_ZNK11PileTableauI5PointE7estVideEv:
.LFB3038:
	.cfi_startproc
	endbr64
	movl	20(%rdi), %eax
	testl	%eax, %eax
	sete	%al
	ret
	.cfi_endproc
.LFE3038:
	.size	_ZNK11PileTableauI5PointE7estVideEv, .-_ZNK11PileTableauI5PointE7estVideEv
	.section	.text._ZNK11PileTableauI5PointE6tailleEv,"axG",@progbits,_ZNK11PileTableauI5PointE6tailleEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK11PileTableauI5PointE6tailleEv
	.type	_ZNK11PileTableauI5PointE6tailleEv, @function
_ZNK11PileTableauI5PointE6tailleEv:
.LFB3039:
	.cfi_startproc
	endbr64
	movl	20(%rdi), %eax
	ret
	.cfi_endproc
.LFE3039:
	.size	_ZNK11PileTableauI5PointE6tailleEv, .-_ZNK11PileTableauI5PointE6tailleEv
	.section	.text._ZN11PileTableauI5PointED2Ev,"axG",@progbits,_ZN11PileTableauI5PointED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN11PileTableauI5PointED2Ev
	.type	_ZN11PileTableauI5PointED2Ev, @function
_ZN11PileTableauI5PointED2Ev:
.LFB2711:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L5
	jmp	_ZdaPv@PLT
	.p2align 4,,10
	.p2align 3
.L5:
	ret
	.cfi_endproc
.LFE2711:
	.size	_ZN11PileTableauI5PointED2Ev, .-_ZN11PileTableauI5PointED2Ev
	.weak	_ZN11PileTableauI5PointED1Ev
	.set	_ZN11PileTableauI5PointED1Ev,_ZN11PileTableauI5PointED2Ev
	.section	.text._ZN11PileTableauI5PointED0Ev,"axG",@progbits,_ZN11PileTableauI5PointED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN11PileTableauI5PointED0Ev
	.type	_ZN11PileTableauI5PointED0Ev, @function
_ZN11PileTableauI5PointED0Ev:
.LFB2713:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L13
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rax, 8(%rsp)
	call	_ZdaPv@PLT
	movq	8(%rsp), %rax
	movl	$24, %esi
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	movq	%rax, %rdi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L13:
	movl	$24, %esi
	movq	%rax, %rdi
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE2713:
	.size	_ZN11PileTableauI5PointED0Ev, .-_ZN11PileTableauI5PointED0Ev
	.section	.text._ZN11PileTableauI5PointE7empilerERKS0_,"axG",@progbits,_ZN11PileTableauI5PointE7empilerERKS0_,comdat
	.align 2
	.p2align 4
	.weak	_ZN11PileTableauI5PointE7empilerERKS0_
	.type	_ZN11PileTableauI5PointE7empilerERKS0_, @function
_ZN11PileTableauI5PointE7empilerERKS0_:
.LFB2714:
	.cfi_startproc
	endbr64
	movslq	20(%rdi), %rcx
	movq	%rdi, %r8
	cmpl	16(%rdi), %ecx
	je	.L17
	leal	1(%rcx), %edx
	movq	8(%rdi), %rax
	movl	%edx, 20(%rdi)
	movq	(%rsi), %rdx
	movq	%rdx, (%rax,%rcx,8)
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	leal	(%rcx,%rcx), %eax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movslq	%eax, %rdi
	movl	%eax, %ebx
	movq	%rdi, %rax
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	shrq	$60, %rax
	jne	.L19
	salq	$3, %rdi
	movl	%ecx, 8(%rsp)
	movq	%r8, 16(%rsp)
	movq	%rsi, 24(%rsp)
	call	_Znam@PLT
	movslq	8(%rsp), %rsi
	movq	16(%rsp), %r8
	xorl	%edx, %edx
	movq	24(%rsp), %r9
	movq	%rsi, %rcx
	salq	$3, %rsi
	movq	8(%r8), %rdi
	testl	%ecx, %ecx
	je	.L29
	.p2align 5
	.p2align 4
	.p2align 3
.L23:
	movq	(%rdi,%rdx), %rcx
	movq	%rcx, (%rax,%rdx)
	addq	$8, %rdx
	cmpq	%rdx, %rsi
	jne	.L23
.L21:
	movq	%r9, 24(%rsp)
	movq	%r8, 16(%rsp)
	movq	%rax, 8(%rsp)
	call	_ZdaPv@PLT
	movq	16(%rsp), %r8
	movq	24(%rsp), %r9
	movq	8(%rsp), %rax
	movslq	20(%r8), %rcx
.L22:
	leal	1(%rcx), %edx
	movq	%rax, 8(%r8)
	movl	%edx, 20(%r8)
	movq	(%r9), %rdx
	movl	%ebx, 16(%r8)
	movq	%rdx, (%rax,%rcx,8)
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L29:
	.cfi_restore_state
	testq	%rdi, %rdi
	je	.L22
	jmp	.L21
.L19:
	call	__cxa_throw_bad_array_new_length@PLT
	.cfi_endproc
.LFE2714:
	.size	_ZN11PileTableauI5PointE7empilerERKS0_, .-_ZN11PileTableauI5PointE7empilerERKS0_
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4
	.type	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, @function
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0:
.LFB3046:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rdi), %rax
	movq	-24(%rax), %rax
	movq	240(%rdi,%rax), %rdi
	testq	%rdi, %rdi
	je	.L35
	cmpb	$0, 56(%rdi)
	je	.L32
	movsbl	67(%rdi), %esi
.L33:
	movq	%rbx, %rdi
	call	_ZNSo3putEc@PLT
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%rax, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_ZNSo5flushEv@PLT
.L32:
	.cfi_restore_state
	movq	%rdi, 8(%rsp)
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	8(%rsp), %rdi
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	(%rdi), %rax
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L33
	movl	$10, %esi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L33
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold, @function
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold:
.LFSB3046:
.L35:
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -16
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE3046:
	.text
	.size	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, .-_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	.section	.text.unlikely
	.size	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold, .-_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata._ZNK11PileTableauI5PointE9getSommetEv.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Pile vide"
	.section	.text._ZNK11PileTableauI5PointE9getSommetEv,"axG",@progbits,_ZNK11PileTableauI5PointE9getSommetEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK11PileTableauI5PointE9getSommetEv
	.type	_ZNK11PileTableauI5PointE9getSommetEv, @function
_ZNK11PileTableauI5PointE9getSommetEv:
.LFB3037:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3037
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	leaq	_ZNK11PileTableauI5PointE7estVideEv(%rip), %rdx
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	(%rdi), %rax
	movq	40(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L38
	movslq	20(%rdi), %rax
	testl	%eax, %eax
	je	.L39
.L40:
	movq	8(%rdi), %rdx
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	leaq	-8(%rdx,%rax,8), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L38:
	.cfi_restore_state
	movq	%rdi, 8(%rsp)
.LEHB0:
	call	*%rax
.LEHE0:
	testb	%al, %al
	jne	.L39
	movq	8(%rsp), %rdi
	movslq	20(%rdi), %rax
	jmp	.L40
.L39:
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %rbx
.LEHB1:
	call	_ZNSt15underflow_errorC1EPKc@PLT
.LEHE1:
	movq	_ZNSt15underflow_errorD1Ev@GOTPCREL(%rip), %rdx
	leaq	_ZTISt15underflow_error(%rip), %rsi
	movq	%rbx, %rdi
.LEHB2:
	call	__cxa_throw@PLT
.L42:
	endbr64
	movq	%rax, %r14
.L41:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r14, %rdi
	call	_Unwind_Resume@PLT
.LEHE2:
	.cfi_endproc
.LFE3037:
	.section	.gcc_except_table._ZNK11PileTableauI5PointE9getSommetEv,"aG",@progbits,_ZNK11PileTableauI5PointE9getSommetEv,comdat
.LLSDA3037:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3037-.LLSDACSB3037
.LLSDACSB3037:
	.uleb128 .LEHB0-.LFB3037
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB3037
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L42-.LFB3037
	.uleb128 0
	.uleb128 .LEHB2-.LFB3037
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE3037:
	.section	.text._ZNK11PileTableauI5PointE9getSommetEv,"axG",@progbits,_ZNK11PileTableauI5PointE9getSommetEv,comdat
	.size	_ZNK11PileTableauI5PointE9getSommetEv, .-_ZNK11PileTableauI5PointE9getSommetEv
	.section	.text._ZN11PileTableauI5PointE7depilerEv,"axG",@progbits,_ZN11PileTableauI5PointE7depilerEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN11PileTableauI5PointE7depilerEv
	.type	_ZN11PileTableauI5PointE7depilerEv, @function
_ZN11PileTableauI5PointE7depilerEv:
.LFB3036:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3036
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	leaq	_ZNK11PileTableauI5PointE7estVideEv(%rip), %rdx
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	(%rdi), %rax
	movq	40(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L49
	movl	20(%rdi), %eax
	testl	%eax, %eax
	je	.L50
.L51:
	movq	8(%rdi), %rdx
	subl	$1, %eax
	movl	%eax, 20(%rdi)
	cltq
	movq	(%rdx,%rax,8), %rax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L49:
	.cfi_restore_state
	movq	%rdi, 8(%rsp)
.LEHB3:
	call	*%rax
.LEHE3:
	testb	%al, %al
	jne	.L50
	movq	8(%rsp), %rdi
	movl	20(%rdi), %eax
	jmp	.L51
.L50:
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %rbx
.LEHB4:
	call	_ZNSt15underflow_errorC1EPKc@PLT
.LEHE4:
	movq	_ZNSt15underflow_errorD1Ev@GOTPCREL(%rip), %rdx
	leaq	_ZTISt15underflow_error(%rip), %rsi
	movq	%rbx, %rdi
.LEHB5:
	call	__cxa_throw@PLT
.L53:
	endbr64
	movq	%rax, %r14
.L52:
	movq	%rbx, %rdi
	call	__cxa_free_exception@PLT
	movq	%r14, %rdi
	call	_Unwind_Resume@PLT
.LEHE5:
	.cfi_endproc
.LFE3036:
	.section	.gcc_except_table._ZN11PileTableauI5PointE7depilerEv,"aG",@progbits,_ZN11PileTableauI5PointE7depilerEv,comdat
.LLSDA3036:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3036-.LLSDACSB3036
.LLSDACSB3036:
	.uleb128 .LEHB3-.LFB3036
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB3036
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L53-.LFB3036
	.uleb128 0
	.uleb128 .LEHB5-.LFB3036
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE3036:
	.section	.text._ZN11PileTableauI5PointE7depilerEv,"axG",@progbits,_ZN11PileTableauI5PointE7depilerEv,comdat
	.size	_ZN11PileTableauI5PointE7depilerEv, .-_ZN11PileTableauI5PointE7depilerEv
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"("
.LC3:
	.string	","
.LC4:
	.string	")"
	.text
	.p2align 4
	.globl	_ZlsRSoRK5Point
	.type	_ZlsRSoRK5Point, @function
_ZlsRSoRK5Point:
.LFB2403:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$1, %edx
	movq	%rsi, %rbp
	leaq	.LC2(%rip), %rsi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	0(%rbp), %esi
	movq	%rbx, %rdi
	call	_ZNSolsEi@PLT
	movl	$1, %edx
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	4(%rbp), %esi
	movq	%rbx, %rdi
	call	_ZNSolsEi@PLT
	movl	$1, %edx
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2403:
	.size	_ZlsRSoRK5Point, .-_ZlsRSoRK5Point
	.section	.rodata._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_.str1.8,"aMS",@progbits,1
	.align 8
.LC5:
	.string	"basic_string: construction from null is not valid"
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC5IS3_EEPKcRKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_:
.LFB2701:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$32, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rbp
	movq	%rbp, 24(%rsp)
	leaq	16(%rdi), %rbp
	movq	%rbp, (%rdi)
	testq	%rsi, %rsi
	je	.L74
	movq	%rdi, %rbx
	movq	%rsi, %rdi
	movq	%rsi, %r12
	call	strlen@PLT
	movq	%rax, 16(%rsp)
	movq	%rax, %rcx
	cmpq	$15, %rax
	ja	.L75
	cmpq	$1, %rax
	jne	.L66
	movzbl	(%r12), %edx
	movb	%dl, 16(%rbx)
.L67:
	movq	%rax, 8(%rbx)
	movb	$0, 0(%rbp,%rax)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L73
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L66:
	.cfi_restore_state
	testq	%rax, %rax
	je	.L67
	jmp	.L65
	.p2align 4,,10
	.p2align 3
.L75:
	leaq	16(%rsp), %rsi
	xorl	%edx, %edx
	movq	%rbx, %rdi
	movq	%rax, 8(%rsp)
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm@PLT
	movq	8(%rsp), %rcx
	movq	%rax, (%rbx)
	movq	%rax, %rbp
	movq	16(%rsp), %rax
	movq	%rax, 16(%rbx)
.L65:
	movq	%rbp, %rdi
	movq	%rcx, %rdx
	movq	%r12, %rsi
	call	memcpy@PLT
	movq	16(%rsp), %rax
	movq	(%rbx), %rbp
	jmp	.L67
.L74:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	je	.L63
.L73:
	call	__stack_chk_fail@PLT
.L63:
	leaq	.LC5(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
	.cfi_endproc
.LFE2701:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
	.set	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_
	.section	.rodata._Z15viderEtAfficherIcEvR4PileIT_E.str1.1,"aMS",@progbits,1
.LC6:
	.string	"  depilement :"
.LC7:
	.string	" "
	.section	.text._Z15viderEtAfficherIcEvR4PileIT_E,"axG",@progbits,_Z15viderEtAfficherIcEvR4PileIT_E,comdat
	.p2align 4
	.weak	_Z15viderEtAfficherIcEvR4PileIT_E
	.type	_Z15viderEtAfficherIcEvR4PileIT_E, @function
_Z15viderEtAfficherIcEvR4PileIT_E:
.LFB2718:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$14, %edx
	leaq	.LC6(%rip), %rsi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	leaq	_ZSt4cout(%rip), %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rbp
	movq	%rbp, 8(%rsp)
	movq	%rdi, %rbp
	movq	%rbx, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	.p2align 4
	.p2align 3
.L77:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*40(%rax)
	testb	%al, %al
	jne	.L90
.L80:
	movl	$1, %edx
	leaq	.LC7(%rip), %rsi
	movq	%rbx, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	movq	(%rbx), %rdx
	movb	%al, 7(%rsp)
	movq	-24(%rdx), %rdx
	cmpq	$0, 16(%rbx,%rdx)
	je	.L78
	movq	%rbx, %rdi
	leaq	7(%rsp), %rsi
	movl	$1, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*40(%rax)
	testb	%al, %al
	je	.L80
.L90:
	movq	_ZSt4cout(%rip), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L91
	cmpb	$0, 56(%rbp)
	je	.L83
	movsbl	67(%rbp), %esi
.L84:
	movq	%rbx, %rdi
	call	_ZNSo3putEc@PLT
	movq	8(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L89
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rax, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZNSo5flushEv@PLT
	.p2align 4,,10
	.p2align 3
.L78:
	.cfi_restore_state
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc@PLT
	jmp	.L77
	.p2align 4,,10
	.p2align 3
.L83:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%rbp), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L84
	movq	%rbp, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L84
.L91:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	je	.L82
.L89:
	call	__stack_chk_fail@PLT
.L82:
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE2718:
	.size	_Z15viderEtAfficherIcEvR4PileIT_E, .-_Z15viderEtAfficherIcEvR4PileIT_E
	.section	.text._Z7mesurerI11PileTableauIiEEdi,"axG",@progbits,_Z7mesurerI11PileTableauIiEEdi,comdat
	.p2align 4
	.weak	_Z7mesurerI11PileTableauIiEEdi
	.type	_Z7mesurerI11PileTableauIiEEdi, @function
_Z7mesurerI11PileTableauIiEEdi:
.LFB2721:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2721
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rbp
	movq	%rbp, 56(%rsp)
	movl	%edi, %ebp
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	movl	$4, %esi
	leaq	32(%rsp), %rdi
	movq	%rax, %r13
.LEHB6:
	call	_ZN11PileTableauIiEC1Ei@PLT
.LEHE6:
	movl	$0, 28(%rsp)
	testl	%ebp, %ebp
	jle	.L95
	.p2align 4
	.p2align 3
.L94:
	leaq	28(%rsp), %rsi
	leaq	32(%rsp), %rdi
.LEHB7:
	call	_ZN11PileTableauIiE7empilerERKi@PLT
	movl	28(%rsp), %eax
	addl	$1, %eax
	movl	%eax, 28(%rsp)
	cmpl	%ebp, %eax
	jl	.L94
	jmp	.L95
	.p2align 4,,10
	.p2align 3
.L96:
	leaq	32(%rsp), %rdi
	call	_ZN11PileTableauIiE7depilerEv@PLT
.L95:
	leaq	32(%rsp), %rdi
	call	_ZNK11PileTableauIiE7estVideEv@PLT
.LEHE7:
	testb	%al, %al
	je	.L96
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	pxor	%xmm0, %xmm0
	leaq	32(%rsp), %rdi
	subq	%r13, %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC8(%rip), %xmm0
	movsd	%xmm0, 8(%rsp)
	call	_ZN11PileTableauIiED1Ev@PLT
	movsd	8(%rsp), %xmm0
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L102
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L97:
	.cfi_restore_state
	leaq	32(%rsp), %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	je	.L98
.L102:
	call	__stack_chk_fail@PLT
.L100:
	endbr64
	movq	%rax, %rbp
	jmp	.L97
.L98:
	movq	%rbp, %rdi
.LEHB8:
	call	_Unwind_Resume@PLT
.LEHE8:
	.cfi_endproc
.LFE2721:
	.section	.gcc_except_table._Z7mesurerI11PileTableauIiEEdi,"aG",@progbits,_Z7mesurerI11PileTableauIiEEdi,comdat
.LLSDA2721:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2721-.LLSDACSB2721
.LLSDACSB2721:
	.uleb128 .LEHB6-.LFB2721
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB2721
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L100-.LFB2721
	.uleb128 0
	.uleb128 .LEHB8-.LFB2721
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
.LLSDACSE2721:
	.section	.text._Z7mesurerI11PileTableauIiEEdi,"axG",@progbits,_Z7mesurerI11PileTableauIiEEdi,comdat
	.size	_Z7mesurerI11PileTableauIiEEdi, .-_Z7mesurerI11PileTableauIiEEdi
	.section	.text._Z7mesurerI9PileListeIiEEdi,"axG",@progbits,_Z7mesurerI9PileListeIiEEdi,comdat
	.p2align 4
	.weak	_Z7mesurerI9PileListeIiEEdi
	.type	_Z7mesurerI9PileListeIiEEdi, @function
_Z7mesurerI9PileListeIiEEdi:
.LFB2725:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2725
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rbp
	movq	%rbp, 56(%rsp)
	movl	%edi, %ebp
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	leaq	32(%rsp), %rdi
	movq	%rax, %r13
.LEHB9:
	call	_ZN9PileListeIiEC1Ev@PLT
.LEHE9:
	movl	$0, 28(%rsp)
	testl	%ebp, %ebp
	jle	.L107
	.p2align 4
	.p2align 3
.L106:
	leaq	28(%rsp), %rsi
	leaq	32(%rsp), %rdi
.LEHB10:
	call	_ZN9PileListeIiE7empilerERKi@PLT
	movl	28(%rsp), %eax
	addl	$1, %eax
	movl	%eax, 28(%rsp)
	cmpl	%ebp, %eax
	jl	.L106
	jmp	.L107
	.p2align 4,,10
	.p2align 3
.L108:
	leaq	32(%rsp), %rdi
	call	_ZN9PileListeIiE7depilerEv@PLT
.L107:
	leaq	32(%rsp), %rdi
	call	_ZNK9PileListeIiE7estVideEv@PLT
.LEHE10:
	testb	%al, %al
	je	.L108
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	pxor	%xmm0, %xmm0
	leaq	32(%rsp), %rdi
	subq	%r13, %rax
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC8(%rip), %xmm0
	movsd	%xmm0, 8(%rsp)
	call	_ZN9PileListeIiED1Ev@PLT
	movsd	8(%rsp), %xmm0
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L114
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L109:
	.cfi_restore_state
	leaq	32(%rsp), %rdi
	call	_ZN9PileListeIiED1Ev@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	je	.L110
.L114:
	call	__stack_chk_fail@PLT
.L112:
	endbr64
	movq	%rax, %rbp
	jmp	.L109
.L110:
	movq	%rbp, %rdi
.LEHB11:
	call	_Unwind_Resume@PLT
.LEHE11:
	.cfi_endproc
.LFE2725:
	.section	.gcc_except_table._Z7mesurerI9PileListeIiEEdi,"aG",@progbits,_Z7mesurerI9PileListeIiEEdi,comdat
.LLSDA2725:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2725-.LLSDACSB2725
.LLSDACSB2725:
	.uleb128 .LEHB9-.LFB2725
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB10-.LFB2725
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L112-.LFB2725
	.uleb128 0
	.uleb128 .LEHB11-.LFB2725
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
.LLSDACSE2725:
	.section	.text._Z7mesurerI9PileListeIiEEdi,"axG",@progbits,_Z7mesurerI9PileListeIiEEdi,comdat
	.size	_Z7mesurerI9PileListeIiEEdi, .-_Z7mesurerI9PileListeIiEEdi
	.section	.rodata.str1.1
.LC9:
	.string	"=== 1. PileTableau<int> ==="
.LC10:
	.string	"  empiler("
.LC11:
	.string	") -> taille="
.LC12:
	.string	" capacite="
.LC13:
	.string	"  contenu : "
.LC14:
	.string	"  sommet  : "
.LC15:
	.string	"  depiler : "
.LC16:
	.string	"\n=== 2. PileListe<string> ==="
.LC17:
	.string	"alpha"
.LC18:
	.string	"beta"
.LC19:
	.string	"gamma"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC20:
	.string	"\n=== 3. PileTableau<Point> (type utilisateur) ==="
	.section	.rodata.str1.1
.LC23:
	.string	"[ "
.LC24:
	.string	"]"
	.section	.rodata.str1.8
	.align 8
.LC25:
	.string	"\n=== 4. Polymorphisme via Pile<T>& ==="
	.section	.rodata.str1.1
.LC26:
	.string	"PileTableau<char>"
.LC27:
	.string	"PileListe<char>"
.LC28:
	.string	"\n=== 5. Copie profonde ==="
.LC29:
	.string	"  original : "
.LC30:
	.string	"  copie    : "
.LC31:
	.string	"  t1 : "
.LC32:
	.string	"   t2 : "
	.section	.rodata.str1.8
	.align 8
.LC33:
	.string	"\n=== 6. Exceptions (pile vide) ==="
	.align 8
.LC34:
	.string	"\n=== 7. Performance (empiler puis depiler n entiers) ==="
	.section	.rodata.str1.1
.LC35:
	.string	"  n="
.LC36:
	.string	"\tTableau: "
.LC37:
	.string	" ms\tListe: "
.LC38:
	.string	" ms"
.LC39:
	.string	"  PileTableau : "
.LC40:
	.string	"  PileListe   : "
	.section	.text.unlikely
.LCOLDB41:
	.section	.text.startup,"ax",@progbits
.LHOTB41:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB2406:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2406
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	_ZSt4cout(%rip), %rdi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	$10, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$456, %rsp
	.cfi_def_cfa_offset 512
	movq	%fs:40, %rsi
	movq	%rsi, 440(%rsp)
	leaq	.LC9(%rip), %rsi
	leaq	64(%rsp), %rbp
	leaq	352(%rsp), %rbx
.LEHB12:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	movl	$2, %esi
	movq	%rbp, %rdi
	call	_ZN11PileTableauIiEC1Ei@PLT
.LEHE12:
	jmp	.L121
	.p2align 4,,10
	.p2align 3
.L211:
	movsbl	67(%r13), %esi
.L120:
	movq	%r14, %rdi
.LEHB13:
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	addl	$10, %r12d
	cmpl	$70, %r12d
	je	.L210
.L121:
	movq	%rbx, %rsi
	movq	%rbp, %rdi
	movl	%r12d, 352(%rsp)
	call	_ZN11PileTableauIiE7empilerERKi@PLT
	movl	$10, %edx
	leaq	.LC10(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	%r12d, %esi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSolsEi@PLT
	movl	$12, %edx
	leaq	.LC11(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r13
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbp, %rdi
	call	_ZNK11PileTableauIiE6tailleEv@PLT
	movl	%eax, %esi
	movq	%r13, %rdi
	call	_ZNSolsEi@PLT
	movl	$10, %edx
	leaq	.LC12(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r13
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbp, %rdi
	call	_ZNK11PileTableauIiE11getCapaciteEv@PLT
	movl	%eax, %esi
	movq	%r13, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %r14
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r14,%rax), %r13
	testq	%r13, %r13
	je	.L202
	cmpb	$0, 56(%r13)
	jne	.L211
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%r15, %rax
	je	.L120
	movq	%r13, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L120
	.p2align 4,,10
	.p2align 3
.L210:
	leaq	.LC13(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%rbp, %rdi
	call	_ZNK11PileTableauIiE8afficherERSo@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC14(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rbp, %rdi
	movq	%rax, %r12
	call	_ZNK11PileTableauIiE9getSommetEv@PLT
	movl	(%rax), %esi
	movq	%r12, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC15(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rbp, %rdi
	movq	%rax, %r12
	call	_ZN11PileTableauIiE7depilerEv@PLT
	movl	%eax, %esi
	movq	%r12, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC13(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%rbp, %rdi
	call	_ZNK11PileTableauIiE8afficherERSo@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC16(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	96(%rsp), %r15
	movq	%r15, %rdi
	movq	%r15, 48(%rsp)
	call	_ZN9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEC1Ev@PLT
.LEHE13:
	leaq	400(%rsp), %r13
	movq	%rbx, %rdx
	leaq	.LC17(%rip), %rsi
	movq	%r13, %rdi
.LEHB14:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
.LEHE14:
	movq	%r13, %rsi
	movq	%r15, %rdi
.LEHB15:
	call	_ZN9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEE7empilerERKS5_@PLT
.LEHE15:
	movq	%r13, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	%rbx, %rdx
	leaq	.LC18(%rip), %rsi
	movq	%r13, %rdi
.LEHB16:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
.LEHE16:
	movq	%r13, %rsi
	movq	%r15, %rdi
.LEHB17:
	call	_ZN9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEE7empilerERKS5_@PLT
.LEHE17:
	movq	%r13, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	%rbx, %rdx
	leaq	.LC19(%rip), %rsi
	movq	%r13, %rdi
.LEHB18:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
.LEHE18:
	movq	%r13, %rsi
	movq	%r15, %rdi
.LEHB19:
	call	_ZN9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEE7empilerERKS5_@PLT
.LEHE19:
	movq	%r13, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	.LC13(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
.LEHB20:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%r15, %rdi
	call	_ZNK9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEE8afficherERSo@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC14(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%r15, %rdi
	movq	%rax, %r12
	call	_ZNK9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEE9getSommetEv@PLT
	movq	8(%rax), %rdx
	movq	(%rax), %rsi
	movq	%r12, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC20(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	16+_ZTV11PileTableauI5PointE(%rip), %rax
	movl	$32, %edi
	movl	$4, 144(%rsp)
	movq	%rax, 128(%rsp)
	call	_Znam@PLT
.LEHE20:
	movq	.LC21(%rip), %rdx
	movq	%rbx, %rsi
	leaq	128(%rsp), %rdi
	movq	%rax, 136(%rsp)
	movl	$0, 148(%rsp)
	movq	%rdx, 352(%rsp)
.LEHB21:
	call	_ZN11PileTableauI5PointE7empilerERKS0_
.LEHE21:
	movq	.LC22(%rip), %rax
	movq	%rbx, %rsi
	leaq	128(%rsp), %rdi
	movq	%rax, 352(%rsp)
.LEHB22:
	call	_ZN11PileTableauI5PointE7empilerERKS0_
.LEHE22:
	movq	136(%rsp), %rax
	leaq	.LC13(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	148(%rsp), %r15d
	movq	%rax, 40(%rsp)
.LEHB23:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movl	$2, %edx
	leaq	.LC23(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	testl	%r15d, %r15d
	jle	.L128
	movq	40(%rsp), %rcx
	movslq	%r15d, %rax
	salq	$3, %rax
	leaq	-16(%rcx,%rax), %r14
	leaq	-8(%rcx,%rax), %r12
	leal	-1(%r15), %eax
	salq	$3, %rax
	subq	%rax, %r14
	.p2align 4
	.p2align 3
.L127:
	movq	%r12, %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZlsRSoRK5Point
	movl	$1, %edx
	leaq	.LC7(%rip), %rsi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	subq	$8, %r12
	cmpq	%r12, %r14
	jne	.L127
.L128:
	movl	$1, %edx
	leaq	.LC24(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC25(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	160(%rsp), %r15
	leaq	192(%rsp), %r14
	movq	%rax, %rdi
	movq	%r15, %xmm1
	movq	%r14, %xmm2
	movq	%r15, 24(%rsp)
	punpcklqdq	%xmm2, %xmm1
	movq	%r14, 32(%rsp)
	movaps	%xmm1, (%rsp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	movl	$4, %esi
	movq	%r15, %rdi
	call	_ZN11PileTableauIcEC1Ei@PLT
.LEHE23:
	movq	%r14, %rdi
.LEHB24:
	call	_ZN9PileListeIcEC1Ev@PLT
.LEHE24:
	leaq	384(%rsp), %rax
	movdqa	(%rsp), %xmm1
	leaq	404(%rsp), %r12
	movq	%rax, (%rsp)
	leaq	416(%rsp), %rax
	movq	%rax, 16(%rsp)
	movaps	%xmm1, 384(%rsp)
.L131:
	movq	(%rsp), %rax
	movq	%r13, %r15
	movq	(%rax), %r14
	movq	16(%rsp), %rax
	movq	%rax, 400(%rsp)
	movl	$1162627408, (%rax)
	movq	$4, 408(%rsp)
	movb	$0, 420(%rsp)
	.p2align 4
	.p2align 3
.L129:
	movzbl	16(%r15), %eax
	movq	%rbx, %rsi
	movq	%r14, %rdi
	movb	%al, 352(%rsp)
	movq	(%r14), %rax
.LEHB25:
	call	*16(%rax)
.LEHE25:
	addq	$1, %r15
	cmpq	%r12, %r15
	jne	.L129
	movq	400(%rsp), %rdi
	cmpq	16(%rsp), %rdi
	je	.L130
	movq	416(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L130:
	addq	$8, (%rsp)
	cmpq	(%rsp), %r13
	jne	.L131
	leaq	.LC26(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
.LEHB26:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	movq	24(%rsp), %rdi
	call	_Z15viderEtAfficherIcEvR4PileIT_E
	leaq	.LC27(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	movq	32(%rsp), %rdi
	call	_Z15viderEtAfficherIcEvR4PileIT_E
	leaq	.LC28(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	224(%rsp), %r12
	movq	%r12, %rdi
	call	_ZN9PileListeIiEC1Ev@PLT
.LEHE26:
	movq	%rbx, %rsi
	movq	%r12, %rdi
	movl	$1, 352(%rsp)
.LEHB27:
	call	_ZN9PileListeIiE7empilerERKi@PLT
	movq	%rbx, %rsi
	movq	%r12, %rdi
	movl	$2, 352(%rsp)
	call	_ZN9PileListeIiE7empilerERKi@PLT
	leaq	256(%rsp), %r15
	movq	%r12, %rsi
	movq	%r15, %rdi
	movq	%r15, 56(%rsp)
	call	_ZN9PileListeIiEC1ERKS0_@PLT
.LEHE27:
	movq	%rbx, %rsi
	movq	%r15, %rdi
	movl	$99, 352(%rsp)
.LEHB28:
	call	_ZN9PileListeIiE7empilerERKi@PLT
	leaq	.LC29(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%r12, %rdi
	call	_ZNK9PileListeIiE8afficherERSo@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC30(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%r15, %rdi
	call	_ZNK9PileListeIiE8afficherERSo@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	288(%rsp), %r15
	movl	$4, %esi
	movq	%r15, %rdi
	call	_ZN11PileTableauIiEC1Ei@PLT
.LEHE28:
	leaq	320(%rsp), %r13
	movl	$4, %esi
	movq	%r13, %rdi
.LEHB29:
	call	_ZN11PileTableauIiEC1Ei@PLT
.LEHE29:
	movq	%rbx, %rsi
	movq	%r15, %rdi
	movl	$5, 352(%rsp)
.LEHB30:
	call	_ZN11PileTableauIiE7empilerERKi@PLT
	movq	%r15, %rsi
	movq	%r13, %rdi
	call	_ZN11PileTableauIiEaSERKS0_@PLT
	movq	%rbx, %rsi
	movq	%r13, %rdi
	movl	$6, 352(%rsp)
	call	_ZN11PileTableauIiE7empilerERKi@PLT
	leaq	.LC31(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%r15, %rdi
	call	_ZNK11PileTableauIiE8afficherERSo@PLT
	leaq	.LC32(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	_ZSt4cout(%rip), %rsi
	movq	%r13, %rdi
	call	_ZNK11PileTableauIiE8afficherERSo@PLT
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	.LC33(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
.LEHE30:
	movl	$4, %esi
	movq	%rbx, %rdi
.LEHB31:
	call	_ZN11PileTableauIiEC1Ei@PLT
.LEHE31:
	movq	%rbx, %rdi
.LEHB32:
	call	_ZN11PileTableauIiE7depilerEv@PLT
.LEHE32:
	movq	%rbx, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
.L148:
	movq	%rbx, %rdi
.LEHB33:
	call	_ZN9PileListeIiEC1Ev@PLT
.LEHE33:
	movq	%rbx, %rdi
.LEHB34:
	call	_ZNK9PileListeIiE9getSommetEv@PLT
.LEHE34:
	movq	%rbx, %rdi
	call	_ZN9PileListeIiED1Ev@PLT
.L153:
	leaq	.LC34(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
.LEHB35:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	leaq	C.1.0(%rip), %rbx
.L136:
	movl	(%rbx), %r14d
	movl	%r14d, %edi
	call	_Z7mesurerI11PileTableauIiEEdi
	movl	%r14d, %edi
	movsd	%xmm0, (%rsp)
	call	_Z7mesurerI9PileListeIiEEdi
	movl	$4, %edx
	leaq	.LC35(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movsd	%xmm0, 16(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	%r14d, %esi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSolsEi@PLT
	movl	$10, %edx
	leaq	.LC36(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r14
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movsd	(%rsp), %xmm0
	movq	%r14, %rdi
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$11, %edx
	leaq	.LC37(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r14
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movsd	16(%rsp), %xmm0
	movq	%r14, %rdi
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$3, %edx
	leaq	.LC38(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r14
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	(%r14), %rax
	movq	-24(%rax), %rax
	movq	240(%r14,%rax), %rdi
	testq	%rdi, %rdi
	je	.L203
	cmpb	$0, 56(%rdi)
	je	.L134
	movsbl	67(%rdi), %esi
.L135:
	movq	%r14, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	addq	$4, %rbx
	leaq	12+C.1.0(%rip), %rax
	cmpq	%rbx, %rax
	jne	.L136
	movq	%r13, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
	movq	%r15, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
	movq	56(%rsp), %rdi
	call	_ZN9PileListeIiED1Ev@PLT
	movq	%r12, %rdi
	call	_ZN9PileListeIiED1Ev@PLT
	movq	32(%rsp), %rdi
	call	_ZN9PileListeIcED1Ev@PLT
	movq	24(%rsp), %rdi
	call	_ZN11PileTableauIcED1Ev@PLT
	movq	40(%rsp), %rax
	testq	%rax, %rax
	je	.L137
	movq	%rax, %rdi
	call	_ZdaPv@PLT
.L137:
	movq	48(%rsp), %rdi
	call	_ZN9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEED1Ev@PLT
	movq	%rbp, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
	movq	440(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L212
	addq	$456, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L134:
	.cfi_restore_state
	movq	%rdi, (%rsp)
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%rsp), %rdi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	(%rdi), %rax
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L135
	call	*%rax
.LEHE35:
	movsbl	%al, %esi
	jmp	.L135
.L212:
	call	__stack_chk_fail@PLT
.L182:
	endbr64
	movq	%rax, %r14
	jmp	.L150
.L181:
	endbr64
	movq	%rax, %rdi
	jmp	.L151
.L179:
	endbr64
	movq	%rax, %r14
	jmp	.L144
.L178:
	endbr64
	movq	%rax, %rdi
	jmp	.L145
.L200:
	endbr64
	jmp	.L201
.L176:
	endbr64
	movq	%rax, %rbx
	jmp	.L155
.L175:
	endbr64
	movq	%rax, %rbx
	jmp	.L156
.L174:
	endbr64
	movq	%rax, %rbx
	jmp	.L157
.L173:
	endbr64
	movq	%rax, %rbx
	jmp	.L143
.L172:
	endbr64
	movq	%rax, %rbx
	jmp	.L142
.L171:
	endbr64
	movq	%rax, %rbx
	jmp	.L158
.L186:
	endbr64
	movq	%rax, %rbx
	jmp	.L124
.L185:
	endbr64
	movq	%rax, %rbx
	jmp	.L159
.L184:
	endbr64
	movq	%rax, %rbx
	jmp	.L159
.L170:
	endbr64
	movq	%rax, %rbx
	jmp	.L141
.L169:
	endbr64
	movq	%rax, %rbx
	jmp	.L141
.L167:
	endbr64
	movq	%rax, %rbx
	jmp	.L141
.L168:
	endbr64
	movq	%rax, %rbx
	jmp	.L139
.L198:
	endbr64
	jmp	.L199
	.section	.gcc_except_table,"a",@progbits
	.align 4
.LLSDA2406:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT2406-.LLSDATTD2406
.LLSDATTD2406:
	.byte	0x1
	.uleb128 .LLSDACSE2406-.LLSDACSB2406
.LLSDACSB2406:
	.uleb128 .LEHB12-.LFB2406
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB13-.LFB2406
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L198-.LFB2406
	.uleb128 0
	.uleb128 .LEHB14-.LFB2406
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L168-.LFB2406
	.uleb128 0
	.uleb128 .LEHB15-.LFB2406
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L167-.LFB2406
	.uleb128 0
	.uleb128 .LEHB16-.LFB2406
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L168-.LFB2406
	.uleb128 0
	.uleb128 .LEHB17-.LFB2406
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L169-.LFB2406
	.uleb128 0
	.uleb128 .LEHB18-.LFB2406
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L168-.LFB2406
	.uleb128 0
	.uleb128 .LEHB19-.LFB2406
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L170-.LFB2406
	.uleb128 0
	.uleb128 .LEHB20-.LFB2406
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L168-.LFB2406
	.uleb128 0
	.uleb128 .LEHB21-.LFB2406
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L184-.LFB2406
	.uleb128 0
	.uleb128 .LEHB22-.LFB2406
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L185-.LFB2406
	.uleb128 0
	.uleb128 .LEHB23-.LFB2406
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L186-.LFB2406
	.uleb128 0
	.uleb128 .LEHB24-.LFB2406
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L171-.LFB2406
	.uleb128 0
	.uleb128 .LEHB25-.LFB2406
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L172-.LFB2406
	.uleb128 0
	.uleb128 .LEHB26-.LFB2406
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L173-.LFB2406
	.uleb128 0
	.uleb128 .LEHB27-.LFB2406
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L174-.LFB2406
	.uleb128 0
	.uleb128 .LEHB28-.LFB2406
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L175-.LFB2406
	.uleb128 0
	.uleb128 .LEHB29-.LFB2406
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L176-.LFB2406
	.uleb128 0
	.uleb128 .LEHB30-.LFB2406
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L200-.LFB2406
	.uleb128 0
	.uleb128 .LEHB31-.LFB2406
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L178-.LFB2406
	.uleb128 0x3
	.uleb128 .LEHB32-.LFB2406
	.uleb128 .LEHE32-.LEHB32
	.uleb128 .L179-.LFB2406
	.uleb128 0x3
	.uleb128 .LEHB33-.LFB2406
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L181-.LFB2406
	.uleb128 0x3
	.uleb128 .LEHB34-.LFB2406
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L182-.LFB2406
	.uleb128 0x3
	.uleb128 .LEHB35-.LFB2406
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L200-.LFB2406
	.uleb128 0
.LLSDACSE2406:
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x7d
	.align 4
	.long	DW.ref._ZTISt15underflow_error-.
.LLSDATT2406:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC2406
	.type	main.cold, @function
main.cold:
.LFSB2406:
.L203:
	.cfi_def_cfa_offset 512
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	440(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L213
.LEHB36:
	call	_ZSt16__throw_bad_castv@PLT
.LEHE36:
.L150:
	movq	%rbx, %rdi
	movq	%rdx, (%rsp)
	call	_ZN9PileListeIiED1Ev@PLT
	movq	(%rsp), %rdx
	movq	%r14, %rdi
.L151:
	subq	$1, %rdx
	jne	.L209
	call	__cxa_begin_catch@PLT
	leaq	.LC40(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movq	%rax, %r14
.LEHB37:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rbx
	movq	(%r14), %rax
	movq	%r14, %rdi
	call	*16(%rax)
	movq	%rbx, %rdi
	movq	%rax, %rsi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
.LEHE37:
	call	__cxa_end_catch@PLT
	jmp	.L153
.L144:
	movq	%rbx, %rdi
	movq	%rdx, (%rsp)
	call	_ZN11PileTableauIiED1Ev@PLT
	movq	(%rsp), %rdx
	movq	%r14, %rdi
.L145:
	subq	$1, %rdx
	jne	.L209
	call	__cxa_begin_catch@PLT
	leaq	.LC39(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movq	%rax, %r14
.LEHB38:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, (%rsp)
	movq	(%r14), %rax
	movq	%r14, %rdi
	call	*16(%rax)
	movq	(%rsp), %rdi
	movq	%rax, %rsi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
.LEHE38:
	call	__cxa_end_catch@PLT
	jmp	.L148
.L213:
	call	__stack_chk_fail@PLT
.L209:
	movq	%rdi, %rbx
.L147:
	movq	%r13, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
.L155:
	movq	%r15, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
.L156:
	movq	56(%rsp), %rdi
	call	_ZN9PileListeIiED1Ev@PLT
.L157:
	movq	%r12, %rdi
	call	_ZN9PileListeIiED1Ev@PLT
.L143:
	movq	32(%rsp), %rdi
	call	_ZN9PileListeIcED1Ev@PLT
.L158:
	movq	24(%rsp), %rdi
	call	_ZN11PileTableauIcED1Ev@PLT
.L124:
	cmpq	$0, 40(%rsp)
	jne	.L214
.L139:
	movq	48(%rsp), %rdi
	call	_ZN9PileListeINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEED1Ev@PLT
.L161:
	movq	%rbp, %rdi
	call	_ZN11PileTableauIiED1Ev@PLT
	movq	440(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L215
	movq	%rbx, %rdi
.LEHB39:
	call	_Unwind_Resume@PLT
.LEHE39:
.L183:
	endbr64
.L208:
	movq	%rax, %rbx
	call	__cxa_end_catch@PLT
	jmp	.L147
.L177:
	endbr64
.L201:
	movq	%rax, %rbx
	jmp	.L147
.L180:
	endbr64
	jmp	.L208
.L214:
	movq	40(%rsp), %rdi
	call	_ZdaPv@PLT
	jmp	.L139
.L215:
	call	__stack_chk_fail@PLT
.L142:
	movq	%r13, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	jmp	.L143
.L159:
	movq	136(%rsp), %rax
	movq	%rax, 40(%rsp)
	jmp	.L124
.L141:
	movq	%r13, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	jmp	.L139
.L202:
	movq	440(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L216
.LEHB40:
	call	_ZSt16__throw_bad_castv@PLT
.LEHE40:
.L216:
	call	__stack_chk_fail@PLT
.L166:
	endbr64
.L199:
	movq	%rax, %rbx
	jmp	.L161
	.cfi_endproc
.LFE2406:
	.section	.gcc_except_table
	.align 4
.LLSDAC2406:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATTC2406-.LLSDATTDC2406
.LLSDATTDC2406:
	.byte	0x1
	.uleb128 .LLSDACSEC2406-.LLSDACSBC2406
.LLSDACSBC2406:
	.uleb128 .LEHB36-.LCOLDB41
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L177-.LCOLDB41
	.uleb128 0
	.uleb128 .LEHB37-.LCOLDB41
	.uleb128 .LEHE37-.LEHB37
	.uleb128 .L183-.LCOLDB41
	.uleb128 0
	.uleb128 .LEHB38-.LCOLDB41
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L180-.LCOLDB41
	.uleb128 0
	.uleb128 .LEHB39-.LCOLDB41
	.uleb128 .LEHE39-.LEHB39
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB40-.LCOLDB41
	.uleb128 .LEHE40-.LEHB40
	.uleb128 .L166-.LCOLDB41
	.uleb128 0
.LLSDACSEC2406:
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x7d
	.align 4
	.long	DW.ref._ZTISt15underflow_error-.
.LLSDATTC2406:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE41:
	.section	.text.startup
.LHOTE41:
	.section	.rodata
	.align 8
	.type	C.1.0, @object
	.size	C.1.0, 12
C.1.0:
	.long	100000
	.long	1000000
	.long	10000000
	.weak	_ZTS4PileI5PointE
	.section	.rodata._ZTS4PileI5PointE,"aG",@progbits,_ZTS4PileI5PointE,comdat
	.align 8
	.type	_ZTS4PileI5PointE, @object
	.size	_ZTS4PileI5PointE, 14
_ZTS4PileI5PointE:
	.string	"4PileI5PointE"
	.weak	_ZTI4PileI5PointE
	.section	.data.rel.ro._ZTI4PileI5PointE,"awG",@progbits,_ZTI4PileI5PointE,comdat
	.align 8
	.type	_ZTI4PileI5PointE, @object
	.size	_ZTI4PileI5PointE, 16
_ZTI4PileI5PointE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS4PileI5PointE
	.weak	_ZTS11PileTableauI5PointE
	.section	.rodata._ZTS11PileTableauI5PointE,"aG",@progbits,_ZTS11PileTableauI5PointE,comdat
	.align 16
	.type	_ZTS11PileTableauI5PointE, @object
	.size	_ZTS11PileTableauI5PointE, 22
_ZTS11PileTableauI5PointE:
	.string	"11PileTableauI5PointE"
	.weak	_ZTI11PileTableauI5PointE
	.section	.data.rel.ro._ZTI11PileTableauI5PointE,"awG",@progbits,_ZTI11PileTableauI5PointE,comdat
	.align 8
	.type	_ZTI11PileTableauI5PointE, @object
	.size	_ZTI11PileTableauI5PointE, 24
_ZTI11PileTableauI5PointE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS11PileTableauI5PointE
	.quad	_ZTI4PileI5PointE
	.weak	_ZTV11PileTableauI5PointE
	.section	.data.rel.ro.local._ZTV11PileTableauI5PointE,"awG",@progbits,_ZTV11PileTableauI5PointE,comdat
	.align 8
	.type	_ZTV11PileTableauI5PointE, @object
	.size	_ZTV11PileTableauI5PointE, 72
_ZTV11PileTableauI5PointE:
	.quad	0
	.quad	_ZTI11PileTableauI5PointE
	.quad	_ZN11PileTableauI5PointED1Ev
	.quad	_ZN11PileTableauI5PointED0Ev
	.quad	_ZN11PileTableauI5PointE7empilerERKS0_
	.quad	_ZN11PileTableauI5PointE7depilerEv
	.quad	_ZNK11PileTableauI5PointE9getSommetEv
	.quad	_ZNK11PileTableauI5PointE7estVideEv
	.quad	_ZNK11PileTableauI5PointE6tailleEv
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC8:
	.long	0
	.long	1093567616
	.align 8
.LC21:
	.long	1
	.long	2
	.align 8
.LC22:
	.long	3
	.long	4
	.hidden	DW.ref._ZTISt15underflow_error
	.weak	DW.ref._ZTISt15underflow_error
	.section	.data.rel.local.DW.ref._ZTISt15underflow_error,"awG",@progbits,DW.ref._ZTISt15underflow_error,comdat
	.align 8
	.type	DW.ref._ZTISt15underflow_error, @object
	.size	DW.ref._ZTISt15underflow_error, 8
DW.ref._ZTISt15underflow_error:
	.quad	_ZTISt15underflow_error
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.globl	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 15.2.0-16ubuntu1) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
