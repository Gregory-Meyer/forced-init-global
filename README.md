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
ctor
dtor
```

Here's is the disassembled executable:

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
    1013:   4c 8d 05 46 02 00 00    lea    0x246(%rip),%r8        # 1260 <__libc_csu_fini>
    101a:   48 8d 0d cf 01 00 00    lea    0x1cf(%rip),%rcx        # 11f0 <__libc_csu_init>
    1021:   48 8d 3d d8 00 00 00    lea    0xd8(%rip),%rdi        # 1100 <main>
    1028:   ff 15 ea 21 00 00       callq  *0x21ea(%rip)        # 3218 <__libc_start_main@GLIBC_2.2.5>
    102e:   f4                      hlt    
    102f:   cc                      int3   

0000000000001030 <deregister_tm_clones>:
    1030:   48 8d 3d d9 0f 00 00    lea    0xfd9(%rip),%rdi        # 2010 <__TMC_END__>
    1037:   48 8d 05 d2 0f 00 00    lea    0xfd2(%rip),%rax        # 2010 <__TMC_END__>
    103e:   48 39 f8                cmp    %rdi,%rax
    1041:   74 15                   je     1058 <deregister_tm_clones+0x28>
    1043:   48 8b 05 de 21 00 00    mov    0x21de(%rip),%rax        # 3228 <_ITM_deregisterTMCloneTable@Base>
    104a:   48 85 c0                test   %rax,%rax
    104d:   74 09                   je     1058 <deregister_tm_clones+0x28>
    104f:   ff e0                   jmpq   *%rax
    1051:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)
    1058:   c3                      retq   
    1059:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001060 <register_tm_clones>:
    1060:   48 8d 3d a9 0f 00 00    lea    0xfa9(%rip),%rdi        # 2010 <__TMC_END__>
    1067:   48 8d 35 a2 0f 00 00    lea    0xfa2(%rip),%rsi        # 2010 <__TMC_END__>
    106e:   48 29 fe                sub    %rdi,%rsi
    1071:   48 c1 fe 03             sar    $0x3,%rsi
    1075:   48 89 f0                mov    %rsi,%rax
    1078:   48 c1 e8 3f             shr    $0x3f,%rax
    107c:   48 01 c6                add    %rax,%rsi
    107f:   48 d1 fe                sar    %rsi
    1082:   74 14                   je     1098 <register_tm_clones+0x38>
    1084:   48 8b 05 a5 21 00 00    mov    0x21a5(%rip),%rax        # 3230 <_ITM_registerTMCloneTable@Base>
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
    10ae:   48 83 3d 82 21 00 00    cmpq   $0x0,0x2182(%rip)        # 3238 <__cxa_finalize@GLIBC_2.2.5>
    10b5:   00 
    10b6:   48 89 e5                mov    %rsp,%rbp
    10b9:   74 0d                   je     10c8 <__do_global_dtors_aux+0x28>
    10bb:   48 8b 3d 46 0f 00 00    mov    0xf46(%rip),%rdi        # 2008 <__dso_handle>
    10c2:   ff 15 70 21 00 00       callq  *0x2170(%rip)        # 3238 <__cxa_finalize@GLIBC_2.2.5>
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
    1113:   48 8b 1d 26 21 00 00    mov    0x2126(%rip),%rbx        # 3240 <std::cout@GLIBCXX_3.4>
    111a:   48 8d 35 db f7 ff ff    lea    -0x825(%rip),%rsi        # 8fc <_IO_stdin_used+0x4>
    1121:   ba 07 00 00 00          mov    $0x7,%edx
    1126:   48 89 df                mov    %rbx,%rdi
    1129:   e8 82 01 00 00          callq  12b0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    112e:   e8 9d 00 00 00          callq  11d0 <client::foo()>
    1133:   48 89 df                mov    %rbx,%rdi
    1136:   89 c6                   mov    %eax,%esi
    1138:   e8 83 01 00 00          callq  12c0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>
    113d:   48 89 c3                mov    %rax,%rbx
    1140:   48 8d 35 bd f7 ff ff    lea    -0x843(%rip),%rsi        # 904 <_IO_stdin_used+0xc>
    1147:   ba 08 00 00 00          mov    $0x8,%edx
    114c:   48 89 c7                mov    %rax,%rdi
    114f:   e8 5c 01 00 00          callq  12b0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    1154:   e8 87 00 00 00          callq  11e0 <client::bar()>
    1159:   48 89 df                mov    %rbx,%rdi
    115c:   89 c6                   mov    %eax,%esi
    115e:   e8 5d 01 00 00          callq  12c0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>
    1163:   c6 44 24 07 0a          movb   $0xa,0x7(%rsp)
    1168:   48 8d 74 24 07          lea    0x7(%rsp),%rsi
    116d:   ba 01 00 00 00          mov    $0x1,%edx
    1172:   48 89 c7                mov    %rax,%rdi
    1175:   e8 36 01 00 00          callq  12b0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    117a:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    1181:   00 00 
    1183:   48 3b 44 24 08          cmp    0x8(%rsp),%rax
    1188:   75 08                   jne    1192 <main+0x92>
    118a:   31 c0                   xor    %eax,%eax
    118c:   48 83 c4 10             add    $0x10,%rsp
    1190:   5b                      pop    %rbx
    1191:   c3                      retq   
    1192:   e8 39 01 00 00          callq  12d0 <__stack_chk_fail@plt>
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
    11ab:   e8 30 01 00 00          callq  12e0 <std::ios_base::Init::Init()@plt>
    11b0:   48 8b 3d 91 20 00 00    mov    0x2091(%rip),%rdi        # 3248 <std::ios_base::Init::~Init()@GLIBCXX_3.4>
    11b7:   48 8d 15 4a 0e 00 00    lea    0xe4a(%rip),%rdx        # 2008 <__dso_handle>
    11be:   48 89 de                mov    %rbx,%rsi
    11c1:   5b                      pop    %rbx
    11c2:   e9 29 01 00 00          jmpq   12f0 <__cxa_atexit@plt>
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

00000000000011e0 <client::bar()>:
    11e0:   b8 0a 00 00 00          mov    $0xa,%eax
    11e5:   c3                      retq   
    11e6:   cc                      int3   
    11e7:   cc                      int3   
    11e8:   cc                      int3   
    11e9:   cc                      int3   
    11ea:   cc                      int3   
    11eb:   cc                      int3   
    11ec:   cc                      int3   
    11ed:   cc                      int3   
    11ee:   cc                      int3   
    11ef:   cc                      int3   

00000000000011f0 <__libc_csu_init>:
    11f0:   f3 0f 1e fa             endbr64 
    11f4:   41 57                   push   %r15
    11f6:   49 89 d7                mov    %rdx,%r15
    11f9:   41 56                   push   %r14
    11fb:   49 89 f6                mov    %rsi,%r14
    11fe:   41 55                   push   %r13
    1200:   41 89 fd                mov    %edi,%r13d
    1203:   41 54                   push   %r12
    1205:   4c 8d 25 fc 1d 00 00    lea    0x1dfc(%rip),%r12        # 3008 <__frame_dummy_init_array_entry>
    120c:   55                      push   %rbp
    120d:   48 8d 2d 04 1e 00 00    lea    0x1e04(%rip),%rbp        # 3018 <__init_array_end>
    1214:   53                      push   %rbx
    1215:   4c 29 e5                sub    %r12,%rbp
    1218:   48 83 ec 08             sub    $0x8,%rsp
    121c:   67 e8 46 00 00 00       addr32 callq 1268 <_init>
    1222:   48 c1 fd 03             sar    $0x3,%rbp
    1226:   74 1e                   je     1246 <__libc_csu_init+0x56>
    1228:   31 db                   xor    %ebx,%ebx
    122a:   66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
    1230:   4c 89 fa                mov    %r15,%rdx
    1233:   4c 89 f6                mov    %r14,%rsi
    1236:   44 89 ef                mov    %r13d,%edi
    1239:   41 ff 14 dc             callq  *(%r12,%rbx,8)
    123d:   48 83 c3 01             add    $0x1,%rbx
    1241:   48 39 dd                cmp    %rbx,%rbp
    1244:   75 ea                   jne    1230 <__libc_csu_init+0x40>
    1246:   48 83 c4 08             add    $0x8,%rsp
    124a:   5b                      pop    %rbx
    124b:   5d                      pop    %rbp
    124c:   41 5c                   pop    %r12
    124e:   41 5d                   pop    %r13
    1250:   41 5e                   pop    %r14
    1252:   41 5f                   pop    %r15
    1254:   c3                      retq   
    1255:   66 66 2e 0f 1f 84 00    data16 nopw %cs:0x0(%rax,%rax,1)
    125c:   00 00 00 00 

0000000000001260 <__libc_csu_fini>:
    1260:   f3 0f 1e fa             endbr64 
    1264:   c3                      retq   

Disassembly of section .init:

0000000000001268 <_init>:
    1268:   f3 0f 1e fa             endbr64 
    126c:   48 83 ec 08             sub    $0x8,%rsp
    1270:   48 8b 05 a9 1f 00 00    mov    0x1fa9(%rip),%rax        # 3220 <__gmon_start__@Base>
    1277:   48 85 c0                test   %rax,%rax
    127a:   74 02                   je     127e <_init+0x16>
    127c:   ff d0                   callq  *%rax
    127e:   48 83 c4 08             add    $0x8,%rsp
    1282:   c3                      retq   

Disassembly of section .fini:

0000000000001284 <_fini>:
    1284:   f3 0f 1e fa             endbr64 
    1288:   48 83 ec 08             sub    $0x8,%rsp
    128c:   48 83 c4 08             add    $0x8,%rsp
    1290:   c3                      retq   

Disassembly of section .plt:

00000000000012a0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt-0x10>:
    12a0:   ff 35 72 0d 00 00       pushq  0xd72(%rip)        # 2018 <__TMC_END__+0x8>
    12a6:   ff 25 74 0d 00 00       jmpq   *0xd74(%rip)        # 2020 <__TMC_END__+0x10>
    12ac:   0f 1f 40 00             nopl   0x0(%rax)

00000000000012b0 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>:
    12b0:   ff 25 72 0d 00 00       jmpq   *0xd72(%rip)        # 2028 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@GLIBCXX_3.4.9>
    12b6:   68 00 00 00 00          pushq  $0x0
    12bb:   e9 e0 ff ff ff          jmpq   12a0 <_fini+0x1c>

00000000000012c0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>:
    12c0:   ff 25 6a 0d 00 00       jmpq   *0xd6a(%rip)        # 2030 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@GLIBCXX_3.4>
    12c6:   68 01 00 00 00          pushq  $0x1
    12cb:   e9 d0 ff ff ff          jmpq   12a0 <_fini+0x1c>

00000000000012d0 <__stack_chk_fail@plt>:
    12d0:   ff 25 62 0d 00 00       jmpq   *0xd62(%rip)        # 2038 <__stack_chk_fail@GLIBC_2.4>
    12d6:   68 02 00 00 00          pushq  $0x2
    12db:   e9 c0 ff ff ff          jmpq   12a0 <_fini+0x1c>

00000000000012e0 <std::ios_base::Init::Init()@plt>:
    12e0:   ff 25 5a 0d 00 00       jmpq   *0xd5a(%rip)        # 2040 <std::ios_base::Init::Init()@GLIBCXX_3.4>
    12e6:   68 03 00 00 00          pushq  $0x3
    12eb:   e9 b0 ff ff ff          jmpq   12a0 <_fini+0x1c>

00000000000012f0 <__cxa_atexit@plt>:
    12f0:   ff 25 52 0d 00 00       jmpq   *0xd52(%rip)        # 2048 <__cxa_atexit@GLIBC_2.2.5>
    12f6:   68 04 00 00 00          pushq  $0x4
    12fb:   e9 a0 ff ff ff          jmpq   12a0 <_fini+0x1c>
```

And here's the disassembled library:

```
libglobal.so:     file format elf64-x86-64


Disassembly of section .text:

0000000000001000 <deregister_tm_clones>:
    1000:   48 8d 3d 09 10 00 00    lea    0x1009(%rip),%rdi        # 2010 <__TMC_END__>
    1007:   48 8d 05 02 10 00 00    lea    0x1002(%rip),%rax        # 2010 <__TMC_END__>
    100e:   48 39 f8                cmp    %rdi,%rax
    1011:   74 15                   je     1028 <deregister_tm_clones+0x28>
    1013:   48 8b 05 ee 21 00 00    mov    0x21ee(%rip),%rax        # 3208 <_ITM_deregisterTMCloneTable@Base>
    101a:   48 85 c0                test   %rax,%rax
    101d:   74 09                   je     1028 <deregister_tm_clones+0x28>
    101f:   ff e0                   jmpq   *%rax
    1021:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)
    1028:   c3                      retq   
    1029:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001030 <register_tm_clones>:
    1030:   48 8d 3d d9 0f 00 00    lea    0xfd9(%rip),%rdi        # 2010 <__TMC_END__>
    1037:   48 8d 35 d2 0f 00 00    lea    0xfd2(%rip),%rsi        # 2010 <__TMC_END__>
    103e:   48 29 fe                sub    %rdi,%rsi
    1041:   48 c1 fe 03             sar    $0x3,%rsi
    1045:   48 89 f0                mov    %rsi,%rax
    1048:   48 c1 e8 3f             shr    $0x3f,%rax
    104c:   48 01 c6                add    %rax,%rsi
    104f:   48 d1 fe                sar    %rsi
    1052:   74 14                   je     1068 <register_tm_clones+0x38>
    1054:   48 8b 05 b5 21 00 00    mov    0x21b5(%rip),%rax        # 3210 <_ITM_registerTMCloneTable@Base>
    105b:   48 85 c0                test   %rax,%rax
    105e:   74 08                   je     1068 <register_tm_clones+0x38>
    1060:   ff e0                   jmpq   *%rax
    1062:   66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
    1068:   c3                      retq   
    1069:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001070 <__do_global_dtors_aux>:
    1070:   f3 0f 1e fa             endbr64 
    1074:   80 3d 85 2f 00 00 00    cmpb   $0x0,0x2f85(%rip)        # 4000 <completed.7287>
    107b:   75 33                   jne    10b0 <__do_global_dtors_aux+0x40>
    107d:   55                      push   %rbp
    107e:   48 83 3d 92 21 00 00    cmpq   $0x0,0x2192(%rip)        # 3218 <__cxa_finalize@GLIBC_2.2.5>
    1085:   00 
    1086:   48 89 e5                mov    %rsp,%rbp
    1089:   74 0d                   je     1098 <__do_global_dtors_aux+0x28>
    108b:   48 8b 3d 6e 0f 00 00    mov    0xf6e(%rip),%rdi        # 2000 <__dso_handle>
    1092:   ff 15 80 21 00 00       callq  *0x2180(%rip)        # 3218 <__cxa_finalize@GLIBC_2.2.5>
    1098:   e8 63 ff ff ff          callq  1000 <deregister_tm_clones>
    109d:   c6 05 5c 2f 00 00 01    movb   $0x1,0x2f5c(%rip)        # 4000 <completed.7287>
    10a4:   5d                      pop    %rbp
    10a5:   c3                      retq   
    10a6:   66 2e 0f 1f 84 00 00    nopw   %cs:0x0(%rax,%rax,1)
    10ad:   00 00 00 
    10b0:   c3                      retq   
    10b1:   66 66 2e 0f 1f 84 00    data16 nopw %cs:0x0(%rax,%rax,1)
    10b8:   00 00 00 00 
    10bc:   0f 1f 40 00             nopl   0x0(%rax)

00000000000010c0 <frame_dummy>:
    10c0:   f3 0f 1e fa             endbr64 
    10c4:   e9 67 ff ff ff          jmpq   1030 <register_tm_clones>
    10c9:   cc                      int3   
    10ca:   cc                      int3   
    10cb:   cc                      int3   
    10cc:   cc                      int3   
    10cd:   cc                      int3   
    10ce:   cc                      int3   
    10cf:   cc                      int3   

00000000000010d0 <global::detail::_init()>:
    10d0:   53                      push   %rbx
    10d1:   48 81 ec 10 02 00 00    sub    $0x210,%rsp
    10d8:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    10df:   00 00 
    10e1:   48 89 84 24 08 02 00    mov    %rax,0x208(%rsp)
    10e8:   00 
    10e9:   b8 01 00 00 00          mov    $0x1,%eax
    10ee:   f0 0f c1 05 0e 2f 00    lock xadd %eax,0x2f0e(%rip)        # 4004 <refcount>
    10f5:   00 
    10f6:   85 c0                   test   %eax,%eax
    10f8:   75 37                   jne    1131 <global::detail::_init()+0x61>
    10fa:   48 8d 35 59 f7 ff ff    lea    -0x8a7(%rip),%rsi        # 85a <GCC_except_table1+0x16>
    1101:   48 8d 5c 24 08          lea    0x8(%rsp),%rbx
    1106:   ba 10 00 00 00          mov    $0x10,%edx
    110b:   48 89 df                mov    %rbx,%rdi
    110e:   e8 2d 01 00 00          callq  1240 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt>
    1113:   48 8d 35 3a f7 ff ff    lea    -0x8c6(%rip),%rsi        # 854 <GCC_except_table1+0x10>
    111a:   ba 05 00 00 00          mov    $0x5,%edx
    111f:   48 89 df                mov    %rbx,%rdi
    1122:   e8 29 01 00 00          callq  1250 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    1127:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    112c:   e8 2f 01 00 00          callq  1260 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    1131:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    1138:   00 00 
    113a:   48 3b 84 24 08 02 00    cmp    0x208(%rsp),%rax
    1141:   00 
    1142:   75 09                   jne    114d <global::detail::_init()+0x7d>
    1144:   48 81 c4 10 02 00 00    add    $0x210,%rsp
    114b:   5b                      pop    %rbx
    114c:   c3                      retq   
    114d:   e8 1e 01 00 00          callq  1270 <__stack_chk_fail@plt>
    1152:   48 89 c3                mov    %rax,%rbx
    1155:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    115a:   e8 01 01 00 00          callq  1260 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    115f:   48 89 df                mov    %rbx,%rdi
    1162:   e8 19 01 00 00          callq  1280 <_Unwind_Resume@plt>
    1167:   66 0f 1f 84 00 00 00    nopw   0x0(%rax,%rax,1)
    116e:   00 00 

0000000000001170 <global::detail::_deinit()>:
    1170:   53                      push   %rbx
    1171:   48 81 ec 10 02 00 00    sub    $0x210,%rsp
    1178:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    117f:   00 00 
    1181:   48 89 84 24 08 02 00    mov    %rax,0x208(%rsp)
    1188:   00 
    1189:   f0 83 2d 73 2e 00 00    lock subl $0x1,0x2e73(%rip)        # 4004 <refcount>
    1190:   01 
    1191:   75 37                   jne    11ca <global::detail::_deinit()+0x5a>
    1193:   48 8d 35 c0 f6 ff ff    lea    -0x940(%rip),%rsi        # 85a <GCC_except_table1+0x16>
    119a:   48 8d 5c 24 08          lea    0x8(%rsp),%rbx
    119f:   ba 01 00 00 00          mov    $0x1,%edx
    11a4:   48 89 df                mov    %rbx,%rdi
    11a7:   e8 94 00 00 00          callq  1240 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt>
    11ac:   48 8d 35 b2 f6 ff ff    lea    -0x94e(%rip),%rsi        # 865 <GCC_except_table1+0x21>
    11b3:   ba 05 00 00 00          mov    $0x5,%edx
    11b8:   48 89 df                mov    %rbx,%rdi
    11bb:   e8 90 00 00 00          callq  1250 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
    11c0:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    11c5:   e8 96 00 00 00          callq  1260 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    11ca:   64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    11d1:   00 00 
    11d3:   48 3b 84 24 08 02 00    cmp    0x208(%rsp),%rax
    11da:   00 
    11db:   75 09                   jne    11e6 <global::detail::_deinit()+0x76>
    11dd:   48 81 c4 10 02 00 00    add    $0x210,%rsp
    11e4:   5b                      pop    %rbx
    11e5:   c3                      retq   
    11e6:   e8 85 00 00 00          callq  1270 <__stack_chk_fail@plt>
    11eb:   48 89 c3                mov    %rax,%rbx
    11ee:   48 8d 7c 24 08          lea    0x8(%rsp),%rdi
    11f3:   e8 68 00 00 00          callq  1260 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>
    11f8:   48 89 df                mov    %rbx,%rdi
    11fb:   e8 80 00 00 00          callq  1280 <_Unwind_Resume@plt>

Disassembly of section .init:

0000000000001200 <_init>:
    1200:   f3 0f 1e fa             endbr64 
    1204:   48 83 ec 08             sub    $0x8,%rsp
    1208:   48 8b 05 f1 1f 00 00    mov    0x1ff1(%rip),%rax        # 3200 <__gmon_start__@Base>
    120f:   48 85 c0                test   %rax,%rax
    1212:   74 02                   je     1216 <_init+0x16>
    1214:   ff d0                   callq  *%rax
    1216:   48 83 c4 08             add    $0x8,%rsp
    121a:   c3                      retq   

Disassembly of section .fini:

000000000000121c <_fini>:
    121c:   f3 0f 1e fa             endbr64 
    1220:   48 83 ec 08             sub    $0x8,%rsp
    1224:   48 83 c4 08             add    $0x8,%rsp
    1228:   c3                      retq   

Disassembly of section .plt:

0000000000001230 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt-0x10>:
    1230:   ff 35 e2 0d 00 00       pushq  0xde2(%rip)        # 2018 <__TMC_END__+0x8>
    1236:   ff 25 e4 0d 00 00       jmpq   *0xde4(%rip)        # 2020 <__TMC_END__+0x10>
    123c:   0f 1f 40 00             nopl   0x0(%rax)

0000000000001240 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@plt>:
    1240:   ff 25 e2 0d 00 00       jmpq   *0xde2(%rip)        # 2028 <std::basic_ofstream<char, std::char_traits<char> >::basic_ofstream(char const*, std::_Ios_Openmode)@GLIBCXX_3.4>
    1246:   68 00 00 00 00          pushq  $0x0
    124b:   e9 e0 ff ff ff          jmpq   1230 <_fini+0x14>

0000000000001250 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>:
    1250:   ff 25 da 0d 00 00       jmpq   *0xdda(%rip)        # 2030 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@GLIBCXX_3.4.9>
    1256:   68 01 00 00 00          pushq  $0x1
    125b:   e9 d0 ff ff ff          jmpq   1230 <_fini+0x14>

0000000000001260 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@plt>:
    1260:   ff 25 d2 0d 00 00       jmpq   *0xdd2(%rip)        # 2038 <std::basic_ofstream<char, std::char_traits<char> >::~basic_ofstream()@GLIBCXX_3.4>
    1266:   68 02 00 00 00          pushq  $0x2
    126b:   e9 c0 ff ff ff          jmpq   1230 <_fini+0x14>

0000000000001270 <__stack_chk_fail@plt>:
    1270:   ff 25 ca 0d 00 00       jmpq   *0xdca(%rip)        # 2040 <__stack_chk_fail@GLIBC_2.4>
    1276:   68 03 00 00 00          pushq  $0x3
    127b:   e9 b0 ff ff ff          jmpq   1230 <_fini+0x14>

0000000000001280 <_Unwind_Resume@plt>:
    1280:   ff 25 c2 0d 00 00       jmpq   *0xdc2(%rip)        # 2048 <_Unwind_Resume@GCC_3.0>
    1286:   68 04 00 00 00          pushq  $0x4
    128b:   e9 a0 ff ff ff          jmpq   1230 <_fini+0x14>
```
