.source hamada.j
.class public test
.super java/lang/Object

.method public <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit locals 100
.limit stack 100
.line 1
iconst_0
istore 1
L_0:
iconst_0
istore 2
L_1:
fconst_0
fstore 3
L_2:
ldc 5
ldc 6
iadd
istore 1
L_3:
ldc 5.500000
fstore 3
L_4:
L_5:
iload 1
ldc 5
if_icmpgt L_6
goto L_11
L_6:
iload 1
ldc 4
if_icmpgt L_7
goto L_9
L_7:
ldc 1
istore 1
L_8:
ldc 2
istore 2
goto L_10
L_9:
ldc 3
istore 1
L_10:
iload 1
ldc 1
iadd
istore 1
goto L_5
L_11:
ldc 2
istore 2
L_12:
return
.end method
