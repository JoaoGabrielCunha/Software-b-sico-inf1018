.text        /*1*/
.globl foo    /*2*/


foo:           /*3*/

  pushq %rbp        /*4*/
  movq %rsp, %rbp    /*5*/
  subq $16, %rsp      /*6*/

L1:
  imul -16(%rbp) , %r10d  






FIM: 
  leave 
  ret





