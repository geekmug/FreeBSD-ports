--- rpython/translator/c/src/asm.c.orig	2016-06-14 07:46:04 UTC
+++ rpython/translator/c/src/asm.c
@@ -8,10 +8,6 @@
 /* #  include "src/asm_gcc_x86_64.c" */
 #endif
 
-#if defined(__GNUC__) && defined(__ppc__)
-#  include "src/asm_ppc.c"
-#endif
-
 #if defined(_MSC_VER)
 #  include "src/asm_msvc.c"
 #endif
