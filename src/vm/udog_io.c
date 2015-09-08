#include "udog_io.h"
#include "udog_value.h"
#include "udog_vm.h"

#if UDOG_USE_LIB_IO

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_READ_LEN 1024

// This string literal is generated automatically from io.udog. Do not edit.
static const char* libSource =
"class IO {\n"
"  static println {\n"
"    IO.writeString_(\"\n\")\n"
"  }\n"
"\n"
"  static print(obj) {\n"
"    IO.writeObject_(obj)\n"
"    return obj\n"
"  }\n"
"\n"
"  static print(a1, a2) {\n"
"    printList_([a1, a2])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3) {\n"
"    printList_([a1, a2, a3])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4) {\n"
"    printList_([a1, a2, a3, a4])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5) {\n"
"    printList_([a1, a2, a3, a4, a5])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6) {\n"
"    printList_([a1, a2, a3, a4, a5, a6])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15])\n"
"  }\n"
"\n"
"  static print(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) {\n"
"    printList_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16])\n"
"  }\n"
"\n"
"  static printList_(objects) {\n"
"    for (object in objects) IO.writeObject_(object)\n"
"  }\n"
"  \n"
"   static println(obj) {\n"
"    IO.writeObject_(obj)\n"
"    IO.writeString_(\"\n\")\n"
"    return obj\n"
"  }\n"
"\n"
"  static println(a1, a2) {\n"
"    printListln_([a1, a2])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3) {\n"
"    printListln_([a1, a2, a3])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4) {\n"
"    printListln_([a1, a2, a3, a4])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5) {\n"
"    printListln_([a1, a2, a3, a4, a5])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15])\n"
"  }\n"
"\n"
"  static println(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) {\n"
"    printListln_([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16])\n"
"  }\n"
"\n"
"  static printListln_(objects) {\n"
"    for (object in objects) IO.writeObject_(object)\n"
"    IO.writeString_(\"\n\")\n"
"  }\n"
"\n"
"  static write(obj) {\n"
"    IO.writeObject_(obj)\n"
"    return obj\n"
"  }\n"
"\n"
"  static read(prompt) {\n"
"    if (!(prompt is String)) Fiber.abort(\"Prompt must be a string.\")\n"
"    IO.write(prompt)\n"
"    return IO.read\n"
"  }\n"
"\n"
"  static writeObject_(obj) {\n"
"    var string = obj.toString\n"
"    if (string is String) {\n"
"      IO.writeString_(string)\n"
"    } else {\n"
"      IO.writeString_(\"[invalid toString]\")\n"
"    }\n"
"  }\n"
"}\n";

static void ioWriteString(UDogVM* vm) {
	const char* s = udogGetArgumentString(vm, 1);
	vm->printFunction("%s", s);
}

static void ioRead(UDogVM* vm) {
	char buffer[MAX_READ_LEN];
	char* result = fgets(buffer, MAX_READ_LEN, stdin);

	if (result == NULL) {
		udogReturnString(vm, buffer, (int)strlen(buffer));
		return;
	}

	udogReturnString(vm, buffer, (int)strlen(buffer));
}

static void ioClock(UDogVM* vm) {
	udogReturnDouble(vm, (double)clock() / CLOCKS_PER_SEC);
}

static void ioTime(UDogVM* vm) {
	udogReturnDouble(vm, (double)time(NULL));
}

void udogLoadIOLibrary(UDogVM* vm) {
	udogInterpret(vm, "", libSource);
	udogDefineStaticMethod(vm, NULL, "IO", "writeString_(_)", ioWriteString);
	udogDefineStaticMethod(vm, NULL, "IO", "clock", ioClock);
	udogDefineStaticMethod(vm, NULL, "IO", "time", ioTime);
	udogDefineStaticMethod(vm, NULL, "IO", "read", ioRead);
}

#endif
