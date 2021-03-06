#include "cardinal_datacenter.h"

#if CARDINAL_USE_MEMORY

#include <string.h>
#include <stdio.h>

#include "cardinal_config.h"
#include "cardinal_value.h"
#include "cardinal_debug.h"

#include "cardinal_native.h"

static const char* libSource =
"class Memory {}\n";


///////////////////////////////////////////////////////////////////////////////////
//// Memory
///////////////////////////////////////////////////////////////////////////////////

DEF_NATIVE(ptr_get)
	if (IS_POINTER(args[0])) {
		void* ptr = AS_POINTER(args[0]);
		RETURN_OBJ( ((Obj*) ptr) );
	} else {
		RETURN_VAL(args[0]);
	}
END_NATIVE

DEF_NATIVE(ptr_toString)
	char buffer[25];
	int length = sprintf(buffer, "[pointer %p]", AS_POINTER(args[0]));
	RETURN_VAL(cardinalNewString(vm, buffer, length));
END_NATIVE

DEF_NATIVE(ptr_kill)
	Obj* ptr = (Obj*) AS_POINTER(args[0]);
	cardinalFreeObjContent(vm, ptr);
	ptr->classObj = vm->metatable.nullClass;
	RETURN_PTR(AS_OBJ(args[0]));
END_NATIVE

DEF_NATIVE(ptr_realloc)
	if (IS_POINTER(args[1]) && IS_NUM(args[2])) {
		void* ptr = AS_POINTER(args[1]);
		double size = AS_NUM(args[2]);
		RETURN_PTR(realloc(ptr, size));
	} else {
		RETURN_VAL(args[0]);
	}
END_NATIVE

DEF_NATIVE(ptr_malloc)
	double size = AS_NUM(args[1]);
	RETURN_PTR(malloc((int) size));
END_NATIVE

DEF_NATIVE(ptr_valloc)
	double size = AS_NUM(args[1]);
	RETURN_PTR(malloc((int) size * sizeof(Value)) );
END_NATIVE

DEF_NATIVE(ptr_vrealloc)
	if (IS_POINTER(args[1]) && IS_NUM(args[2])) {
		void* ptr = AS_POINTER(args[1]);
		double size = AS_NUM(args[2]);
		RETURN_PTR(realloc(ptr, (int) size *  sizeof(Value) ));
	} else {
		RETURN_VAL(args[0]);
	}
END_NATIVE

DEF_NATIVE(ptr_dealloc)
	if (IS_POINTER(args[1])) {
		free(AS_POINTER(args[1]));
		RETURN_PTR(NULL);
	} else {
		RETURN_VAL(args[0]);
	}
END_NATIVE

DEF_NATIVE(ptr_eqeq)
	if (!IS_POINTER(args[1])) RETURN_FALSE;
	RETURN_BOOL(AS_POINTER(args[0]) == AS_POINTER(args[1]));
END_NATIVE

DEF_NATIVE(ptr_bangeq)
	if (!IS_POINTER(args[1])) RETURN_TRUE;
	RETURN_BOOL(AS_POINTER(args[0]) != AS_POINTER(args[1]));
END_NATIVE

DEF_NATIVE(ptr_subscript)
	void* ptr = AS_POINTER(args[0]);
	int ind = (double) AS_NUM(args[1]);
	RETURN_VAL( ( (Value*) ptr)[ind] );
END_NATIVE

DEF_NATIVE(ptr_subscriptSetter)
	void* ptr = AS_POINTER(args[0]);
	int ind = (double) AS_NUM(args[1]);
	( (Value*) ptr)[ind] = args[2];
	RETURN_VAL(args[0]);
END_NATIVE

DEF_NATIVE(ptr_getSingleValue)
	void* ptr = AS_POINTER(args[0]);
	RETURN_VAL( ( (Value*) ptr)[0] );
END_NATIVE

DEF_NATIVE(ptr_setSingleValue)
	void* ptr = AS_POINTER(args[0]);
	( (Value*) ptr)[0] = args[1];
	RETURN_VAL(args[0]);
END_NATIVE

DEF_NATIVE(ptr_plus)
	void* ptr = AS_POINTER(args[0]);
	if (IS_POINTER(args[1])) {
		void* other = AS_POINTER(args[1]);
		RETURN_PTR( (char*) ptr + (cardinal_integer) other) ;
	} else if (IS_NUM(args[1])) {
		cardinal_integer other = (cardinal_integer) AS_NUM(args[1]);
		RETURN_PTR(  (char*) ptr + (cardinal_integer) other) ;
	} else {
		RETURN_ERROR("Right operand must be a number or pointer.")
	}
END_NATIVE

DEF_NATIVE(ptr_min)
	void* ptr = AS_POINTER(args[0]);
	if (IS_POINTER(args[1])) {
		void* other = AS_POINTER(args[1]);
		RETURN_PTR(  (char*) ptr - (cardinal_integer) other) ;
	} else if (IS_NUM(args[1])) {
		cardinal_integer other = (cardinal_integer) AS_NUM(args[1]);
		RETURN_PTR( (char*) ptr - (cardinal_integer) other) ;
	} else {
		RETURN_ERROR("Right operand must be a number or pointer.")
	}
END_NATIVE

DEF_NATIVE(ptr_or)
	void* ptr = AS_POINTER(args[0]);
	if (IS_POINTER(args[1])) {
		void* other = AS_POINTER(args[1]);
		RETURN_PTR( MASK_POINTER(  (cardinal_integer) ptr | (cardinal_integer) other) );
	} else if (IS_NUM(args[1])) {
		cardinal_integer other = (cardinal_integer) AS_NUM(args[1]);
		RETURN_PTR( MASK_POINTER(  (cardinal_integer) ptr | (cardinal_integer) other) );
	} else {
		RETURN_ERROR("Right operand must be a number or pointer.")
	}
END_NATIVE

DEF_NATIVE(ptr_and)
	void* ptr = AS_POINTER(args[0]);
	if (IS_POINTER(args[1])) {
		void* other = AS_POINTER(args[1]);
		RETURN_PTR( MASK_POINTER(  (cardinal_integer) ptr & (cardinal_integer) other) );
	} else if (IS_NUM(args[1])) {
		cardinal_integer other = (cardinal_integer) AS_NUM(args[1]);
		RETURN_PTR( MASK_POINTER(  (cardinal_integer) ptr & (cardinal_integer) other) );
	} else {
		RETURN_ERROR("Right operand must be a number or pointer.")
	}
END_NATIVE

DEF_NATIVE(ptr_not)
	void* ptr = AS_POINTER(args[0]);
	RETURN_PTR( MASK_POINTER( ~((cardinal_integer) ptr)) );
END_NATIVE

DEF_NATIVE(ptr_ls)
	void* ptr = AS_POINTER(args[0]);
	if (IS_NUM(args[1])) {
		cardinal_integer other = (cardinal_integer) AS_NUM(args[1]);
		RETURN_PTR( MASK_POINTER( (cardinal_integer) ptr << (cardinal_integer) other) );
	} else {
		RETURN_ERROR("Right operand must be a number.")
	}
END_NATIVE

DEF_NATIVE(ptr_rs)
	void* ptr = AS_POINTER(args[0]);
	if (IS_NUM(args[1])) {
		cardinal_integer other = (cardinal_integer) AS_NUM(args[1]);
		RETURN_PTR( MASK_POINTER( (cardinal_integer) ptr >> (cardinal_integer) other) );
	} else {
		RETURN_ERROR("Right operand must be a number.")
	}
END_NATIVE

DEF_NATIVE(ptr_l)
	if (!IS_POINTER(args[1])) RETURN_FALSE;
	RETURN_BOOL(AS_POINTER(args[0]) < AS_POINTER(args[1]));
END_NATIVE

DEF_NATIVE(ptr_le)
	if (!IS_POINTER(args[1])) RETURN_TRUE;
	RETURN_BOOL(AS_POINTER(args[0]) <= AS_POINTER(args[1]));
END_NATIVE

DEF_NATIVE(ptr_g)
	if (!IS_POINTER(args[1])) RETURN_FALSE;
	RETURN_BOOL(AS_POINTER(args[0]) > AS_POINTER(args[1]));
END_NATIVE

DEF_NATIVE(ptr_ge)
	if (!IS_POINTER(args[1])) RETURN_TRUE;
	RETURN_BOOL(AS_POINTER(args[0]) >= AS_POINTER(args[1]));
END_NATIVE

#define DEF_GET(type, name)		DEF_NATIVE(ptr_##name) \
							void* ptr = AS_POINTER(args[0]); \
							int ind = (double) AS_NUM(args[1]); \
							RETURN_NUM( ( (type*) ptr)[ind] ); \
						END_NATIVE
						
#define DEF_SET(type, name)		DEF_NATIVE(ptr_set##name) \
							void* ptr = AS_POINTER(args[0]); \
							int ind = (double) AS_NUM(args[1]); \
							( (type*) ptr)[ind] = (type) AS_NUM(args[2]); \
							RETURN_VAL(args[0]); \
						END_NATIVE
						
#define DEF_GETTER(type, name)		DEF_NATIVE(ptr_getSingle##name) \
							void* ptr = AS_POINTER(args[0]); \
							RETURN_NUM( ( (type*) ptr)[0] ); \
						END_NATIVE
						
#define DEF_SETTER(type, name)		DEF_NATIVE(ptr_setSingle##name) \
							void* ptr = AS_POINTER(args[0]); \
							( (type*) ptr)[0] = (type) AS_NUM(args[1]); \
							RETURN_VAL(args[0]); \
						END_NATIVE

DEF_GET(cardinalByte, byte);
DEF_SET(cardinalByte, byte);

DEF_GET(cardinalShort, short);
DEF_SET(cardinalShort, short);

DEF_GET(cardinalInt, int);
DEF_SET(cardinalInt, int);

DEF_GET(cardinalLong, long);
DEF_SET(cardinalLong, long);

DEF_GET(cardinalsByte, sbyte);
DEF_SET(cardinalsByte, sbyte);

DEF_GET(cardinalsShort, sshort);
DEF_SET(cardinalsShort, sshort);

DEF_GET(cardinalsInt, sint);
DEF_SET(cardinalsInt, sint);

DEF_GET(cardinalsLong, slong);
DEF_SET(cardinalsLong, slong);

DEF_GETTER(cardinalByte, byte);
DEF_SETTER(cardinalByte, byte);

DEF_GETTER(cardinalShort, short);
DEF_SETTER(cardinalShort, short);

DEF_GETTER(cardinalInt, int);
DEF_SETTER(cardinalInt, int);

DEF_GETTER(cardinalLong, long);
DEF_SETTER(cardinalLong, long);

DEF_GETTER(cardinalsByte, sbyte);
DEF_SETTER(cardinalsByte, sbyte);

DEF_GETTER(cardinalsShort, sshort);
DEF_SETTER(cardinalsShort, sshort);

DEF_GETTER(cardinalsInt, sint);
DEF_SETTER(cardinalsInt, sint);

DEF_GETTER(cardinalsLong, slong);
DEF_SETTER(cardinalsLong, slong);

///////////////////////////////////////////////////////////////////////////////////
//// OBJECT
///////////////////////////////////////////////////////////////////////////////////

DEF_NATIVE(object_unplug)
	if (IS_OBJ(args[0])) {
		Obj* obj = AS_OBJ(args[0]);
		cardinalRemoveGCObject(vm, obj);
	}
	RETURN_VAL(args[0]);
END_NATIVE

DEF_NATIVE(object_plugin)
	if (IS_OBJ(args[0])) {
		Obj* obj = AS_OBJ(args[0]);
		cardinalAddGCObject(vm, obj);
	}
	RETURN_VAL(args[0]);
END_NATIVE

DEF_NATIVE(object_getAddress)
	RETURN_PTR(AS_OBJ(args[0]));
END_NATIVE

DEF_NATIVE(object_delete)
	Obj* ptr = AS_OBJ(args[0]);
	cardinalFreeObjContent(vm, ptr);
	ptr->classObj = vm->metatable.nullClass;
	RETURN_NULL;
END_NATIVE

DEF_NATIVE(object_transfer)
	cardinalRemoveGCObject(vm, AS_OBJ(args[0]));
	RETURN_PTR(AS_OBJ(args[0]));
END_NATIVE

#define SIZEOF(size, name) \
	DEF_NATIVE(sizeof_##name) \
		RETURN_NUM(size); \
	END_NATIVE

SIZEOF( (sizeof(Value)), ptr)
SIZEOF( (sizeof(Value)), bool)
SIZEOF( (sizeof(Value)), num)
SIZEOF( (sizeof(Value)), null)

SIZEOF( (sizeof(ObjInstance)), object)
SIZEOF( (sizeof(ObjFiber)), fiber)
SIZEOF( (sizeof(ObjFn)), fn)
SIZEOF( (sizeof(ObjList)), list)
SIZEOF( (sizeof(ObjString)), string)
SIZEOF( (sizeof(ObjRange)), range)
SIZEOF( (sizeof(ObjTable)), table)
SIZEOF( (sizeof(ObjMap)), map)
SIZEOF( (sizeof(ObjModule)), module)
SIZEOF( (sizeof(ObjMethod)), method)
SIZEOF( (sizeof(ObjClass)), class)

SIZEOF( (sizeof(ObjFiber)), fibero)
SIZEOF( (sizeof(ObjFn)), fno)
SIZEOF( (sizeof(ObjList)), listo)
SIZEOF( (sizeof(ObjString)), stringo)
SIZEOF( (sizeof(ObjRange)), rangeo)
SIZEOF( (sizeof(ObjTable)), tableo)
SIZEOF( (sizeof(ObjMap)), mapo)
SIZEOF( (sizeof(ObjModule)), moduleo)
SIZEOF( (sizeof(ObjMethod)), methodo)

///////////////////////////////////////////////////////////////////////////////////
//// Methods
///////////////////////////////////////////////////////////////////////////////////

void bindPointerClass(CardinalVM* vm) {
	vm->metatable.pointerClass = AS_CLASS(cardinalFindVariable(vm, "Memory"));
	
	// Get the memory for objects
	NATIVE(vm->metatable.pointerClass, "*", ptr_get);
	NATIVE(vm->metatable.pointerClass, "kill()", ptr_kill);
	
	// Memory allocation
	NATIVE(vm->metatable.pointerClass->obj.classObj, "malloc(_)", ptr_malloc);
	NATIVE(vm->metatable.pointerClass->obj.classObj, "realloc(_,_)", ptr_realloc);
	NATIVE(vm->metatable.pointerClass->obj.classObj, "free(_)", ptr_dealloc);
	NATIVE(vm->metatable.pointerClass->obj.classObj, "valloc(_)", ptr_valloc);	
	NATIVE(vm->metatable.pointerClass->obj.classObj, "vrealloc(_)", ptr_vrealloc);
	
	NATIVE(vm->metatable.pointerClass, "[_]", ptr_subscript);
	NATIVE(vm->metatable.pointerClass, "[_]=(_)", ptr_subscriptSetter);
	NATIVE(vm->metatable.pointerClass, "toString", ptr_toString);
	
	// Used to write to the memory
	NATIVE(vm->metatable.pointerClass, "i8(_)", ptr_sbyte);
	NATIVE(vm->metatable.pointerClass, "i8(_,_)", ptr_setsbyte);
	NATIVE(vm->metatable.pointerClass, "ui8(_)", ptr_byte);
	NATIVE(vm->metatable.pointerClass, "ui8(_,_)", ptr_setbyte);
	NATIVE(vm->metatable.pointerClass, "i16(_)", ptr_sshort);
	NATIVE(vm->metatable.pointerClass, "i16(_,_)", ptr_setsshort);
	NATIVE(vm->metatable.pointerClass, "ui16(_)", ptr_short);
	NATIVE(vm->metatable.pointerClass, "ui16(_,_)", ptr_setshort);
	NATIVE(vm->metatable.pointerClass, "i32(_)", ptr_sint);
	NATIVE(vm->metatable.pointerClass, "i32(_,_)", ptr_setsint);
	NATIVE(vm->metatable.pointerClass, "ui32(_)", ptr_int);
	NATIVE(vm->metatable.pointerClass, "ui32(_,_)", ptr_setint);
	NATIVE(vm->metatable.pointerClass, "i64(_)", ptr_slong);
	NATIVE(vm->metatable.pointerClass, "i64(_,_)", ptr_setslong);
	NATIVE(vm->metatable.pointerClass, "ui64(_)", ptr_long);
	NATIVE(vm->metatable.pointerClass, "ui64(_,_)", ptr_setlong);
	
	NATIVE(vm->metatable.pointerClass, "i8", ptr_getSinglesbyte);
	NATIVE(vm->metatable.pointerClass, "i8=(_)", ptr_setSinglesbyte);
	NATIVE(vm->metatable.pointerClass, "ui8", ptr_getSinglebyte);
	NATIVE(vm->metatable.pointerClass, "ui8=(_)", ptr_setSinglebyte);
	NATIVE(vm->metatable.pointerClass, "i16", ptr_getSinglesshort);
	NATIVE(vm->metatable.pointerClass, "i16=(_)", ptr_setSinglesshort);
	NATIVE(vm->metatable.pointerClass, "ui16", ptr_getSingleshort);
	NATIVE(vm->metatable.pointerClass, "ui16=(_)", ptr_setSingleshort);
	NATIVE(vm->metatable.pointerClass, "i32", ptr_getSinglesint);
	NATIVE(vm->metatable.pointerClass, "i32=(_)", ptr_setSinglesint);
	NATIVE(vm->metatable.pointerClass, "ui32", ptr_getSingleint);
	NATIVE(vm->metatable.pointerClass, "ui32=(_)", ptr_setSingleint);
	NATIVE(vm->metatable.pointerClass, "i64", ptr_getSingleslong);
	NATIVE(vm->metatable.pointerClass, "i64=(_)", ptr_setSingleslong);
	NATIVE(vm->metatable.pointerClass, "ui64", ptr_getSinglelong);
	NATIVE(vm->metatable.pointerClass, "ui64=(_)", ptr_setSinglelong);
	
	NATIVE(vm->metatable.pointerClass, "value(_)", ptr_subscript);
	NATIVE(vm->metatable.pointerClass, "value(_,_)", ptr_subscriptSetter);
	NATIVE(vm->metatable.pointerClass, "value", ptr_getSingleValue);
	NATIVE(vm->metatable.pointerClass, "value=(_)", ptr_setSingleValue);
	
	// An object can be manually created using:
	// ptr.constructor(arguments, classToInstantiate)
	// This uses the memory from [ptr] to create a new instance from
	// [classToInstantiate] with the called constructor and the given
	// arguments
	
	// Arithmetic on pointers
	NATIVE(vm->metatable.pointerClass, "+(_)", ptr_plus);
	NATIVE(vm->metatable.pointerClass, "-(_)", ptr_min);
	NATIVE(vm->metatable.pointerClass, "<(_)", ptr_l);
	NATIVE(vm->metatable.pointerClass, "<=(_)", ptr_le);
	NATIVE(vm->metatable.pointerClass, ">(_)", ptr_g);
	NATIVE(vm->metatable.pointerClass, "<=(_)", ptr_ge);
	NATIVE(vm->metatable.pointerClass, "~", ptr_not);
	NATIVE(vm->metatable.pointerClass, "&(_)", ptr_and);
	NATIVE(vm->metatable.pointerClass, "|(_)", ptr_or);
	NATIVE(vm->metatable.pointerClass, "<<(_)", ptr_ls);
	NATIVE(vm->metatable.pointerClass, ">>(_)", ptr_rs);
	
	// Manipulation
	NATIVE(vm->metatable.pointerClass, "==(_)", ptr_eqeq);
	NATIVE(vm->metatable.pointerClass, "!=(_)", ptr_bangeq);
}

void sizeOfClasses(CardinalVM* vm) {
	// Add sizeof to all classes
	NATIVE(vm->metatable.pointerClass, "sizeof", sizeof_ptr);
	NATIVE(vm->metatable.boolClass, "sizeof", sizeof_bool);
	NATIVE(vm->metatable.numClass, "sizeof", sizeof_num);
	NATIVE(vm->metatable.nullClass, "sizeof", sizeof_null);
	
	NATIVE(vm->metatable.objectClass, "sizeof", sizeof_object);
	NATIVE(vm->metatable.fiberClass, "sizeof", sizeof_fibero);
	NATIVE(vm->metatable.fnClass, "sizeof", sizeof_fno);
	NATIVE(vm->metatable.listClass, "sizeof", sizeof_listo);
	NATIVE(vm->metatable.stringClass, "sizeof", sizeof_stringo);
	NATIVE(vm->metatable.rangeClass, "sizeof", sizeof_rangeo);
	NATIVE(vm->metatable.tableClass, "sizeof", sizeof_tableo);
	NATIVE(vm->metatable.mapClass, "sizeof", sizeof_mapo);
	NATIVE(vm->metatable.moduleClass, "sizeof", sizeof_moduleo);
	NATIVE(vm->metatable.methodClass, "sizeof", sizeof_methodo);
	NATIVE(vm->metatable.classClass, "sizeof", sizeof_class);
	
	NATIVE(vm->metatable.pointerClass->obj.classObj, "sizeof", sizeof_ptr);
	NATIVE(vm->metatable.boolClass->obj.classObj, "sizeof", sizeof_bool);
	NATIVE(vm->metatable.numClass->obj.classObj, "sizeof", sizeof_num);
	NATIVE(vm->metatable.fiberClass->obj.classObj, "sizeof", sizeof_fiber);
	NATIVE(vm->metatable.fnClass->obj.classObj, "sizeof", sizeof_fn);
	NATIVE(vm->metatable.listClass->obj.classObj, "sizeof", sizeof_list);
	NATIVE(vm->metatable.nullClass->obj.classObj, "sizeof", sizeof_null);
	NATIVE(vm->metatable.stringClass->obj.classObj, "sizeof", sizeof_string);
	NATIVE(vm->metatable.rangeClass->obj.classObj, "sizeof", sizeof_range);
	NATIVE(vm->metatable.tableClass->obj.classObj, "sizeof", sizeof_table);
	NATIVE(vm->metatable.mapClass->obj.classObj, "sizeof", sizeof_map);
	NATIVE(vm->metatable.moduleClass->obj.classObj, "sizeof", sizeof_module);
	NATIVE(vm->metatable.methodClass->obj.classObj, "sizeof", sizeof_method);
}

void cardinalInitialiseManualMemoryManagement(CardinalVM* vm) {
	NATIVE(vm->metatable.objectClass, "decoupleGC()", object_unplug);
	NATIVE(vm->metatable.objectClass, "coupleToGC()", object_plugin);
	NATIVE(vm->metatable.objectClass, "&", object_getAddress);
	NATIVE(vm->metatable.objectClass, "delete()", object_delete);
	NATIVE(vm->metatable.objectClass, "transfer()", object_transfer);
}

// The method binds the DataCenter to the VM 
// The Data Center can be used to store elements
void cardinalInitializeDataCenter(CardinalVM* vm) {
	cardinalInterpret(vm, "", libSource);

	bindPointerClass(vm);
	sizeOfClasses(vm);
}

#endif