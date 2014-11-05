// v7.2 update 02 - 64-bit
#if defined(_WIN64)
// OnToolHitTest handlers return INT_PTR - code in 32 bit gets away with 
// int, which allows VC6 compilation as well. In 64 bit INT_PTR needed,
// so we'll use this define - TD
#define UGINTRET INT_PTR

#define PtrToInt(x) PtrToInt((VOID*)(x))	// 64 bit version expects void*, not INT_PTR

#else
#define UGINTRET int
#endif

#if _MSC_VER < 1400

#ifndef GetWindowLongPtr
#define GetWindowLongPtr GetWindowLong
#endif

#ifndef SetWindowLongPtr
#define SetWindowLongPtr SetWindowLong
#endif

#ifndef GetClassLongPtr
#define GetClassLongPtr GetClassLong
#endif

#ifndef SetClassLongPtr
#define SetClassLongPtr SetClassLong
#endif

#ifndef ULongToPtr
#define ULongToPtr(x) x
#endif

#ifndef LongToPtr
#define LongToPtr(x) x
#endif

#ifndef PtrToUint
#define PtrToUint(x) x
#endif

#ifndef PtrToInt
#define PtrToInt(x) x
#endif

typedef DWORD DWORD_PTR;
typedef LONG LONG_PTR;
typedef ULONG ULONG_PTR;

// Frustratingly, INT_PTR is an int in VC2005, and a long in VC6, so we can't define it here, the code needs to just handle it elsewhere

#endif