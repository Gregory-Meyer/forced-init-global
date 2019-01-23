A simple demo of a global object shared between translation units and
constructed/destructed using atomic refcounting. The header "global.h" is
included by multiple client files and its functions are defined in libglobal.a;
construction only occurs the first time it is "constructed" and destruction
only occurs the last time it is "destroyed". In this example, there will be
three pairs of constructor/destructor calls to the global object. When the
global object is constructed for the first time, it outputs a message to the
file "output.txt" indicating so. When destructed for the last time, it appends
a message to "output.txt". When the client is compiled and run on my system,
here is the contents of "output.txt":

```
ctor 0x558e05707002
dtor 0x558e05707002
```

And here is the disassembled object file:

```

client:     file format elf64-x86-64


Disassembly of section .text:

0000000000001000 <_start>:
    1000:   f3 0f 1e fa             endbr64 
    1004:   31 ed                   xor    %ebp,%ebp
    1006:   49 89 d1                mov    %rdx,%r9
    1009:   5e                      pop    %rsi
    100a:   48 89 e2                mov    %rsp,%rdx
    100d:   48 83 e4 f0             and    $0xfffffffffffffff0,%rsp
    1011:   50                      push   %rax
    1012:   54                      push   %rsp
    1013:   4c 8d 05 76 04 00 00    lea    0x476(%rip),%r8        # 1490 <__libc_csu_fini>
    101a:   48 8d 0d ff 03 00 00    lea    0x3ff(%rip),%rcx        # 1420 <__libc_csu_init>
    1021:   48 8d 3d d8 00 00 00    lea    0xd8(%rip),%rdi        # 1100 <main>
    1028:   ff 15 e2 21 00 00       callq  *0x21e2(%rip)        # 3210 <__libc_start_main@GLIBC_2.2.5>
    102e:   f4                      hlt    
    102f:   cc                      int3   

0000000000001030 <deregister_tm_clones>:
    1030:   48 8d 3d e1 0f 00 00    lea    0xfe1(%rip),%rdi        # 2018 <__TMC_END__>
    1037:   48 8d 05 da 0f 00 00    lea    0xfda(%rip),%rax        # 2018 <__TMC_END__>
    103e:   48 39 f8                cmp    %rdi,%rax
    1041:   74 15                   je     1058 <deregister_tm_clones+0x28>
    1043:   48 8b 05 d6 21 00 00    mov    0x21d6(%rip),%rax        # 3220 <_ITM_deregisterTMCloneTable@Base>
    104a:   48 85 c0                test   %rax,%rax
    104d:   74 09                   je     1058 <deregister_tm_clones+0x28>
    104f:   ff e0                   jmpq   *%rax
    1051:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)
    1058:   c3                      retq   
    1059:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001060 <register_tm_clones>:
    1060:   48 8d 3d b1 0f 00 00    lea    0xfb1(%rip),%rdi        # 2018 <__TMC_END__>
    1067:   48 8d 35 aa 0f 00 00    lea    0xfaa(%rip),%rsi        # 2018 <__TMC_END__>
    106e:   48 29 fe                sub    %rdi,%rsi
    1071:   48 c1 fe 03             sar    $0x3,%rsi
    1075:   48 89 f0                mov    %rsi,%rax
    1078:   48 c1 e8 3f             shr    $0x3f,%rax
    107c:   48 01 c6                add    %rax,%rsi
    107f:   48 d1 fe                sar    %rsi
    1082:   74 14                   je     1098 <register_tm_clones+0x38>
    1084:   48 8b 05 9d 21 00 00    mov    0x219d(%rip),%rax        # 3228 <_ITM_registerTMCloneTable@Base>
    108b:   48 85 c0                test   %rax,%rax
    108e:   74 08                   je     1098 <register_tm_clones+0x38>
    1090:   ff e0                   jmpq   *%rax
    1092:   66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
    1098:   c3                      retq   
    1099:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)

00000000000010a0 <__do_global_dtors_aux>:
    10a0:   f3 0f 1e fa             endbr64 
    10a4:   80 3d 55 2f 00 00 00    cmpb   $0x0,0x2f55(%rip)        # 4000 <completed.7287>
    10ab:   75 33                   jne    10e0 <__do_global_dtors_aux+0x40>
    10ad:   55                      push   %rbp
    10ae:   48 83 3d 7a 21 00 00    cmpq   $0x0,0x217a(%rip)        # 3230 <__cxa_finalize@GLIBC_2.2.5>
    10b5:   00 
    10b6:   48 89 e5                mov    %rsp,%rbp
    10b9:   74 0d                   je     10c8 <__do_global_dtors_aux+0x28>
    10bb:   48 8b 3d 46 0f 00 00    mov    0xf46(%rip),%rdi        # 2008 <__dso_handle>
    10c2:   ff 15 68 21 00 00       callq  *0x2168(%rip)        # 3230 <__cxa_finalize@GLIBC_2.2.5>
    10c8:   e8 63 ff ff ff          callq  1030 <deregister_tm_clones>
    10cd:   c6 05 2c 2f 00 00 01    movb   $0x1,0x2f2c(%rip)        # 4000 <completed.7287>
    10d4:   5d                      pop    %rbp
    10d5:   c3                      retq   
    10d6:   66 2e 0f 1f 84 00 00    nopw   %cs:0x0(%rax,%rax,1)
    10dd:   00 00 00 
    10e0:   c3                      retq   
    10e1:   66 66 2e 0f 1f 84 00    data16 nopw %cs:0x0(%rax,%rax,1)
    10e8:   00 00 00 00 
    10ec:   0f 1f 40 00             nopl   0x0(%rax)

00000000000010f0 <frame_dummy>:
    10f0:   f3 0f 1e fa             endbr64 
    10f4:   e9 67 ff ff ff          jmpq   1060 <register_tm_clones>
    10f9:   cc                      int3   
    10fa:   cc                      int3   
    10fb:   cc                      int3   
    10fc:   cc                      int3   
    10fd:   cc                      int3   
    10fe:   cc                      int3   
    10ff:   cc                      int3   

0000000000001100 <main>:
    1100:   53                      push   %rbx
    1101:   48 83 ec 10             sub    $0x10,%rsp
    1105:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    110c:   00 00 
    110e:   48 89 44 24 08          mov    %rax,0x8(%rsp)
    1113:   48 8b 1d 1e 21 00 00    mov    0x211e(%rip),%rbx        # 3238 <std::cout@GLIBCXX_3.4>
    111a:   48 8d 35 b1 fa ff ff    lea    -0x54f(%rip),%rsi        # bd2 <_IO_stdin_used+0xa>
    1121:   ba 07 00 00 00          mov    $0x7,%edx
    1126:   48 89 df                mov    %rbx,%rdi
    1129:   e8 b2 03 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    112e:   e8 9d 00 00 00          callq  11d0 <client::foo()>
    1133:   48 89 df                mov    %rbx,%rdi
    1136:   89 c6                   mov    %eax,%esi
    1138:   e8 b3 03 00 00          callq  14f0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>
    113d:   48 89 c3                mov    %rax,%rbx
    1140:   48 8d 35 93 fa ff ff    lea    -0x56d(%rip),%rsi        # bda <_IO_stdin_used+0x12>
    1147:   ba 08 00 00 00          mov    $0x8,%edx
    114c:   48 89 c7                mov    %rax,%rdi
    114f:   e8 8c 03 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    1154:   e8 b7 00 00 00          callq  1210 <client::bar()>
    1159:   48 89 df                mov    %rbx,%rdi
    115c:   89 c6                   mov    %eax,%esi
    115e:   e8 8d 03 00 00          callq  14f0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>
    1163:   c6 44 24 07 0a          movb   $0xa,0x7(%rsp)
    1168:   48 8d 74 24 07          lea    0x7(%rsp),%rsi
    116d:   ba 01 00 00 00          mov    $0x1,%edx
    1172:   48 89 c7                mov    %rax,%rdi
    1175:   e8 66 03 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    117a:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    1181:   00 00 
    1183:   48 3b 44 24 08          cmp    0x8(%rsp),%rax
    1188:   75 08                   jne    1192 <main+0x92>
    118a:   31 c0                   xor    %eax,%eax
    118c:   48 83 c4 10             add    $0x10,%rsp
    1190:   5b                      pop    %rbx
    1191:   c3                      retq   
    1192:   e8 69 03 00 00          callq  1500 <__stack_chk_fail@plt>
    1197:   cc                      int3   
    1198:   cc                      int3   
    1199:   cc                      int3   
    119a:   cc                      int3   
    119b:   cc                      int3   
    119c:   cc                      int3   
    119d:   cc                      int3   
    119e:   cc                      int3   
    119f:   cc                      int3   

00000000000011a0 <_GLOBAL__sub_I_client_main.cpp>:
    11a0:   53                      push   %rbx
    11a1:   48 8d 1d 59 2e 00 00    lea    0x2e59(%rip),%rbx        # 4001 <std::__ioinit>
    11a8:   48 89 df                mov    %rbx,%rdi
    11ab:   e8 60 03 00 00          callq  1510 <std::ios_base::Init::Init()@plt>
    11b0:   48 8b 3d 89 20 00 00    mov    0x2089(%rip),%rdi        # 3240 <std::ios_base::Init::~Init()@GLIBCXX_3.4>
    11b7:   48 8d 15 4a 0e 00 00    lea    0xe4a(%rip),%rdx        # 2008 <__dso_handle>
    11be:   48 89 de                mov    %rbx,%rsi
    11c1:   5b                      pop    %rbx
    11c2:   e9 59 03 00 00          jmpq   1520 <__cxa_atexit@plt>
    11c7:   cc                      int3   
    11c8:   cc                      int3   
    11c9:   cc                      int3   
    11ca:   cc                      int3   
    11cb:   cc                      int3   
    11cc:   cc                      int3   
    11cd:   cc                      int3   
    11ce:   cc                      int3   
    11cf:   cc                      int3   

00000000000011d0 <client::foo()>:
    11d0:   b8 05 00 00 00          mov    $0x5,%eax
    11d5:   c3                      retq   
    11d6:   cc                      int3   
    11d7:   cc                      int3   
    11d8:   cc                      int3   
    11d9:   cc                      int3   
    11da:   cc                      int3   
    11db:   cc                      int3   
    11dc:   cc                      int3   
    11dd:   cc                      int3   
    11de:   cc                      int3   
    11df:   cc                      int3   

00000000000011e0 <_GLOBAL__sub_I_client_a.cpp>:
    11e0:   53                      push   %rbx
    11e1:   48 8d 1d 1a 2e 00 00    lea    0x2e1a(%rip),%rbx        # 4002 <global::init>
    11e8:   48 89 df                mov    %rbx,%rdi
    11eb:   e8 60 00 00 00          callq  1250 <global::Init::Init()>
    11f0:   48 8b 3d 51 20 00 00    mov    0x2051(%rip),%rdi        # 3248 <__init_array_end+0x218>
    11f7:   48 8d 15 0a 0e 00 00    lea    0xe0a(%rip),%rdx        # 2008 <__dso_handle>
    11fe:   48 89 de                mov    %rbx,%rsi
    1201:   5b                      pop    %rbx
    1202:   e9 19 03 00 00          jmpq   1520 <__cxa_atexit@plt>
    1207:   cc                      int3   
    1208:   cc                      int3   
    1209:   cc                      int3   
    120a:   cc                      int3   
    120b:   cc                      int3   
    120c:   cc                      int3   
    120d:   cc                      int3   
    120e:   cc                      int3   
    120f:   cc                      int3   

0000000000001210 <client::bar()>:
    1210:   b8 0a 00 00 00          mov    $0xa,%eax
    1215:   c3                      retq   
    1216:   cc                      int3   
    1217:   cc                      int3   
    1218:   cc                      int3   
    1219:   cc                      int3   
    121a:   cc                      int3   
    121b:   cc                      int3   
    121c:   cc                      int3   
    121d:   cc                      int3   
    121e:   cc                      int3   
    121f:   cc                      int3   

0000000000001220 <_GLOBAL__sub_I_client_b.cpp>:
    1220:   53                      push   %rbx
    1221:   48 8d 1d db 2d 00 00    lea    0x2ddb(%rip),%rbx        # 4003 <global::init>
    1228:   48 89 df                mov    %rbx,%rdi
    122b:   e8 20 00 00 00          callq  1250 <global::Init::Init()>
    1230:   48 8b 3d 11 20 00 00    mov    0x2011(%rip),%rdi        # 3248 <__init_array_end+0x218>
    1237:   48 8d 15 ca 0d 00 00    lea    0xdca(%rip),%rdx        # 2008 <__dso_handle>
    123e:   48 89 de                mov    %rbx,%rsi
    1241:   5b                      pop    %rbx
    1242:   e9 d9 02 00 00          jmpq   1520 <__cxa_atexit@plt>
    1247:   cc                      int3   
    1248:   cc                      int3   
    1249:   cc                      int3   
    124a:   cc                      int3   
    124b:   cc                      int3   
    124c:   cc                      int3   
    124d:   cc                      int3   
    124e:   cc                      int3   
    124f:   cc                      int3   

0000000000001250 <global::Init::Init()>:
    1250:   41 56                   push   %r14
    1252:   53                      push   %rbx
    1253:   48 81 ec 18 02 00 00    sub    $0x218,%rsp
    125a:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    1261:   00 00 
    1263:   48 89 84 24 10 02 00    mov    %rax,0x210(%rsp)
    126a:   00 
    126b:   b8 01 00 00 00          mov    $0x1,%eax
    1270:   f0 0f c1 05 90 2d 00    lock xadd %eax,0x2d90(%rip)        # 4008 <refcount>
    1277:   00 
    1278:   85 c0                   test   %eax,%eax
    127a:   75 5e                   jne    12da <global::Init::Init()+0x8a>
    127c:   48 89 fb                mov    %rdi,%rbx
    127f:   48 8d 35 5d f9 ff ff    lea    -0x6a3(%rip),%rsi        # be3 <_IO_stdin_used+0x1b>
    1286:   4c 8d 74 24 10          lea    0x10(%rsp),%r14
    128b:   ba 10 00 00 00          mov    $0x10,%edx
    1290:   4c 89 f7                mov    %r14,%rdi
    1293:   e8 98 02 00 00          callq  1530 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt>
    1298:   48 8d 35 2d f9 ff ff    lea    -0x6d3(%rip),%rsi        # bcc <_IO_stdin_used+0x4>
    129f:   ba 05 00 00 00          mov    $0x5,%edx
    12a4:   4c 89 f7                mov    %r14,%rdi
    12a7:   e8 34 02 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    12ac:   48 8d 7c 24 10          lea    0x10(%rsp),%rdi
    12b1:   48 89 de                mov    %rbx,%rsi
    12b4:   e8 87 02 00 00          callq  1540 <std::basic_ostream<char, std::char_traits<char> >& std::basic_ostream<char, std::char_traits<char> >::_M_insert<void const*>(void const*)@plt>
    12b9:   c6 44 24 0f 0a          movb   $0xa,0xf(%rsp)
    12be:   48 8d 74 24 0f          lea    0xf(%rsp),%rsi
    12c3:   ba 01 00 00 00          mov    $0x1,%edx
    12c8:   48 89 c7                mov    %rax,%rdi
    12cb:   e8 10 02 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    12d0:   48 8d 7c 24 10          lea    0x10(%rsp),%rdi
    12d5:   e8 76 02 00 00          callq  1550 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    12da:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    12e1:   00 00 
    12e3:   48 3b 84 24 10 02 00    cmp    0x210(%rsp),%rax
    12ea:   00 
    12eb:   75 0b                   jne    12f8 <global::Init::Init()+0xa8>
    12ed:   48 81 c4 18 02 00 00    add    $0x218,%rsp
    12f4:   5b                      pop    %rbx
    12f5:   41 5e                   pop    %r14
    12f7:   c3                      retq   
    12f8:   e8 03 02 00 00          callq  1500 <__stack_chk_fail@plt>
    12fd:   48 89 c3                mov    %rax,%rbx
    1300:   48 8d 7c 24 10          lea    0x10(%rsp),%rdi
    1305:   e8 46 02 00 00          callq  1550 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    130a:   48 89 df                mov    %rbx,%rdi
    130d:   e8 4e 02 00 00          callq  1560 <_Unwind_Resume@plt>
    1312:   66 2e 0f 1f 84 00 00    nopw   %cs:0x0(%rax,%rax,1)
    1319:   00 00 00 
    131c:   0f 1f 40 00             nopl   0x0(%rax)

0000000000001320 <global::Init::~Init()>:
    1320:   53                      push   %rbx
    1321:   48 81 ec 10 02 00 00    sub    $0x210,%rsp
    1328:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    132f:   00 00 
    1331:   48 89 84 24 08 02 00    mov    %rax,0x208(%rsp)
    1338:   00 
    1339:   f0 83 2d c7 2c 00 00    lock subl $0x1,0x2cc7(%rip)        # 4008 <refcount>
    1340:   01 
    1341:   75 5d                   jne    13a0 <global::Init::~Init()+0x80>
    1343:   48 89 fb                mov    %rdi,%rbx
    1346:   48 8d 35 96 f8 ff ff    lea    -0x76a(%rip),%rsi        # be3 <_IO_stdin_used+0x1b>
    134d:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    1352:   ba 01 00 00 00          mov    $0x1,%edx
    1357:   e8 d4 01 00 00          callq  1530 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt>
    135c:   48 8d 35 8b f8 ff ff    lea    -0x775(%rip),%rsi        # bee <_IO_stdin_used+0x26>
    1363:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    1368:   ba 05 00 00 00          mov    $0x5,%edx
    136d:   e8 6e 01 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    1372:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    1377:   48 89 de                mov    %rbx,%rsi
    137a:   e8 c1 01 00 00          callq  1540 <std::basic_ostream<char, std::char_traits<char> >& std::basic_ostream<char, std::char_traits<char> >::_M_insert<void const*>(void const*)@plt>
    137f:   c6 44 24 07 0a          movb   $0xa,0x7(%rsp)
    1384:   48 8d 74 24 07          lea    0x7(%rsp),%rsi
    1389:   ba 01 00 00 00          mov    $0x1,%edx
    138e:   48 89 c7                mov    %rax,%rdi
    1391:   e8 4a 01 00 00          callq  14e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    1396:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    139b:   e8 b0 01 00 00          callq  1550 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    13a0:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    13a7:   00 00 
    13a9:   48 3b 84 24 08 02 00    cmp    0x208(%rsp),%rax
    13b0:   00 
    13b1:   75 09                   jne    13bc <global::Init::~Init()+0x9c>
    13b3:   48 81 c4 10 02 00 00    add    $0x210,%rsp
    13ba:   5b                      pop    %rbx
    13bb:   c3                      retq   
    13bc:   e8 3f 01 00 00          callq  1500 <__stack_chk_fail@plt>
    13c1:   48 89 c7                mov    %rax,%rdi
    13c4:   e8 17 00 00 00          callq  13e0 <__clang_call_terminate>
    13c9:   48 89 c3                mov    %rax,%rbx
    13cc:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    13d1:   e8 7a 01 00 00          callq  1550 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    13d6:   48 89 df                mov    %rbx,%rdi
    13d9:   e8 02 00 00 00          callq  13e0 <__clang_call_terminate>
    13de:   cc                      int3   
    13df:   cc                      int3   

00000000000013e0 <__clang_call_terminate>:
    13e0:   50                      push   %rax
    13e1:   e8 8a 01 00 00          callq  1570 <__cxa_begin_catch@plt>
    13e6:   e8 95 01 00 00          callq  1580 <std::terminate()@plt>
    13eb:   cc                      int3   
    13ec:   cc                      int3   
    13ed:   cc                      int3   
    13ee:   cc                      int3   
    13ef:   cc                      int3   

00000000000013f0 <_GLOBAL__sub_I_global.cpp>:
    13f0:   53                      push   %rbx
    13f1:   48 8d 1d 0c 2c 00 00    lea    0x2c0c(%rip),%rbx        # 4004 <global::init>
    13f8:   48 89 df                mov    %rbx,%rdi
    13fb:   e8 50 fe ff ff          callq  1250 <global::Init::Init()>
    1400:   48 8d 3d 19 ff ff ff    lea    -0xe7(%rip),%rdi        # 1320 <global::Init::~Init()>
    1407:   48 8d 15 fa 0b 00 00    lea    0xbfa(%rip),%rdx        # 2008 <__dso_handle>
    140e:   48 89 de                mov    %rbx,%rsi
    1411:   5b                      pop    %rbx
    1412:   e9 09 01 00 00          jmpq   1520 <__cxa_atexit@plt>
    1417:   cc                      int3   
    1418:   cc                      int3   
    1419:   cc                      int3   
    141a:   cc                      int3   
    141b:   cc                      int3   
    141c:   cc                      int3   
    141d:   cc                      int3   
    141e:   cc                      int3   
    141f:   cc                      int3   

0000000000001420 <__libc_csu_init>:
    1420:   f3 0f 1e fa             endbr64 
    1424:   41 57                   push   %r15
    1426:   49 89 d7                mov    %rdx,%r15
    1429:   41 56                   push   %r14
    142b:   49 89 f6                mov    %rsi,%r14
    142e:   41 55                   push   %r13
    1430:   41 89 fd                mov    %edi,%r13d
    1433:   41 54                   push   %r12
    1435:   4c 8d 25 cc 1b 00 00    lea    0x1bcc(%rip),%r12        # 3008 <__frame_dummy_init_array_entry>
    143c:   55                      push   %rbp
    143d:   48 8d 2d ec 1b 00 00    lea    0x1bec(%rip),%rbp        # 3030 <__init_array_end>
    1444:   53                      push   %rbx
    1445:   4c 29 e5                sub    %r12,%rbp
    1448:   48 83 ec 08             sub    $0x8,%rsp
    144c:   67 e8 46 00 00 00       addr32 callq 1498 <_init>
    1452:   48 c1 fd 03             sar    $0x3,%rbp
    1456:   74 1e                   je     1476 <__libc_csu_init+0x56>
    1458:   31 db                   xor    %ebx,%ebx
    145a:   66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
    1460:   4c 89 fa                mov    %r15,%rdx
    1463:   4c 89 f6                mov    %r14,%rsi
    1466:   44 89 ef                mov    %r13d,%edi
    1469:   41 ff 14 dc             callq  *(%r12,%rbx,8)
    146d:   48 83 c3 01             add    $0x1,%rbx
    1471:   48 39 dd                cmp    %rbx,%rbp
    1474:   75 ea                   jne    1460 <__libc_csu_init+0x40>
    1476:   48 83 c4 08             add    $0x8,%rsp
    147a:   5b                      pop    %rbx
    147b:   5d                      pop    %rbp
    147c:   41 5c                   pop    %r12
    147e:   41 5d                   pop    %r13
    1480:   41 5e                   pop    %r14
    1482:   41 5f                   pop    %r15
    1484:   c3                      retq   
    1485:   66 66 2e 0f 1f 84 00    data16 nopw %cs:0x0(%rax,%rax,1)
    148c:   00 00 00 00 

0000000000001490 <__libc_csu_fini>:
    1490:   f3 0f 1e fa             endbr64 
    1494:   c3                      retq   

Disassembly of section .init:

0000000000001498 <_init>:
    1498:   f3 0f 1e fa             endbr64 
    149c:   48 83 ec 08             sub    $0x8,%rsp
    14a0:   48 8b 05 71 1d 00 00    mov    0x1d71(%rip),%rax        # 3218 <__gmon_start__@Base>
    14a7:   48 85 c0                test   %rax,%rax
    14aa:   74 02                   je     14ae <_init+0x16>
    14ac:   ff d0                   callq  *%rax
    14ae:   48 83 c4 08             add    $0x8,%rsp
    14b2:   c3                      retq   

Disassembly of section .fini:

00000000000014b4 <_fini>:
    14b4:   f3 0f 1e fa             endbr64 
    14b8:   48 83 ec 08             sub    $0x8,%rsp
    14bc:   48 83 c4 08             add    $0x8,%rsp
    14c0:   c3                      retq   

Disassembly of section .plt:

00000000000014d0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt-0x10>:
    14d0:   ff 35 4a 0b 00 00       pushq  0xb4a(%rip)        # 2020 <__TMC_END__+0x8>
    14d6:   ff 25 4c 0b 00 00       jmpq   *0xb4c(%rip)        # 2028 <__TMC_END__+0x10>
    14dc:   0f 1f 40 00             nopl   0x0(%rax)

00000000000014e0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>:
    14e0:   ff 25 4a 0b 00 00       jmpq   *0xb4a(%rip)        # 2030 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@GLIBCXX_3.4.9>
    14e6:   68 00 00 00 00          pushq  $0x0
    14eb:   e9 e0 ff ff ff          jmpq   14d0 <_fini+0x1c>

00000000000014f0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>:
    14f0:   ff 25 42 0b 00 00       jmpq   *0xb42(%rip)        # 2038 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@GLIBCXX_3.4>
    14f6:   68 01 00 00 00          pushq  $0x1
    14fb:   e9 d0 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001500 <__stack_chk_fail@plt>:
    1500:   ff 25 3a 0b 00 00       jmpq   *0xb3a(%rip)        # 2040 <__stack_chk_fail@GLIBC_2.4>
    1506:   68 02 00 00 00          pushq  $0x2
    150b:   e9 c0 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001510 <std::ios_base::Init::Init()@plt>:
    1510:   ff 25 32 0b 00 00       jmpq   *0xb32(%rip)        # 2048 <std::ios_base::Init::Init()@GLIBCXX_3.4>
    1516:   68 03 00 00 00          pushq  $0x3
    151b:   e9 b0 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001520 <__cxa_atexit@plt>:
    1520:   ff 25 2a 0b 00 00       jmpq   *0xb2a(%rip)        # 2050 <__cxa_atexit@GLIBC_2.2.5>
    1526:   68 04 00 00 00          pushq  $0x4
    152b:   e9 a0 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001530 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt>:
    1530:   ff 25 22 0b 00 00       jmpq   *0xb22(%rip)        # 2058 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@GLIBCXX_3.4>
    1536:   68 05 00 00 00          pushq  $0x5
    153b:   e9 90 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001540 <std::basic_ostream<char, std::char_traits<char> >& std::basic_ostream<char, std::char_traits<char> >::_M_insert<void const*>(void const*)@plt>:
    1540:   ff 25 1a 0b 00 00       jmpq   *0xb1a(%rip)        # 2060 <std::basic_ostream<char, std::char_traits<char> >& std::basic_ostream<char, std::char_traits<char> >::_M_insert<void const*>(void const*)@GLIBCXX_3.4.9>
    1546:   68 06 00 00 00          pushq  $0x6
    154b:   e9 80 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001550 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>:
    1550:   ff 25 12 0b 00 00       jmpq   *0xb12(%rip)        # 2068 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@GLIBCXX_3.4>
    1556:   68 07 00 00 00          pushq  $0x7
    155b:   e9 70 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001560 <_Unwind_Resume@plt>:
    1560:   ff 25 0a 0b 00 00       jmpq   *0xb0a(%rip)        # 2070 <_Unwind_Resume@GCC_3.0>
    1566:   68 08 00 00 00          pushq  $0x8
    156b:   e9 60 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001570 <__cxa_begin_catch@plt>:
    1570:   ff 25 02 0b 00 00       jmpq   *0xb02(%rip)        # 2078 <__cxa_begin_catch@CXXABI_1.3>
    1576:   68 09 00 00 00          pushq  $0x9
    157b:   e9 50 ff ff ff          jmpq   14d0 <_fini+0x1c>

0000000000001580 <std::terminate()@plt>:
    1580:   ff 25 fa 0a 00 00       jmpq   *0xafa(%rip)        # 2080 <std::terminate()@GLIBCXX_3.4>
    1586:   68 0a 00 00 00          pushq  $0xa
    158b:   e9 40 ff ff ff          jmpq   14d0 <_fini+0x1c>
```
