

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

/* 
 * @$Id$ 
 */

//  STLPort standard library config:

#if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
#  include <utility>
#  if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
#      error "This is not STLPort!"
#  endif
#endif

//
// __STL_STATIC_CONST_INIT_BUG implies AMBULANT_NO_LIMITS_COMPILE_TIME_CONSTANTS
// for versions prior to 4.1(beta)
//
#if (defined(__STL_STATIC_CONST_INIT_BUG) || defined(_STLP_STATIC_CONST_INIT_BUG)) && (__SGI_STL_PORT <= 0x400)
#  define AMBULANT_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

//
// If STLport thinks that there is no partial specialisation, then there is no
// std::iterator traits:
//
#if !(defined(_STLP_CLASS_PARTIAL_SPECIALIZATION) || defined(__STL_CLASS_PARTIAL_SPECIALIZATION))
#  define AMBULANT_NO_STD_ITERATOR_TRAITS
#endif

//
// No new style iostreams on GCC without STLport's iostreams enabled:
//
#if (defined(__GNUC__) && (__GNUC__ < 3)) && !(defined(__SGI_STL_OWN_IOSTREAMS) || defined(_STLP_OWN_IOSTREAMS))
#error Compiler too old for Ambulant
#endif

//
// No new iostreams implies no std::locale, and no std::stringstream:
//
#if defined(__STL_NO_IOSTREAMS) || defined(__STL_NO_NEW_IOSTREAMS) || defined(_STLP_NO_IOSTREAMS) || defined(_STLP_NO_NEW_IOSTREAMS)
#  define AMBULANT_NO_STD_LOCALE
#error Compiler too old for Ambulant
#endif

//
// If the streams are not native, and we have a "using ::x" compiler bug
// then the io stream facets are not available in namespace std::
//
#if !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(AMBULANT_NO_USING_TEMPLATE) && !defined(__BORLANDC__)
#  define AMBULANT_NO_STD_LOCALE
#endif
#if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_NAMESPACES) && defined(AMBULANT_NO_USING_TEMPLATE) && !defined(__BORLANDC__)
#  define AMBULANT_NO_STD_LOCALE
#endif

//
// Without member template support enabled, their are no template
// iterate constructors, and no std::allocator:
//
#if !(defined(__STL_MEMBER_TEMPLATES) || defined(_STLP_MEMBER_TEMPLATES))
#  define AMBULANT_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define AMBULANT_NO_STD_ALLOCATOR
#endif
//
// however we always have at least a partial allocator:
//
#define AMBULANT_HAS_PARTIAL_STD_ALLOCATOR

#if !defined(_STLP_MEMBER_TEMPLATE_CLASSES)
#  define AMBULANT_NO_STD_ALLOCATOR
#endif

//
// We always have SGI style hash_set, hash_map, and slist:
//
#define AMBULANT_HAS_HASH
#define AMBULANT_HAS_SLIST

//
// STLport does a good job of importing names into namespace std::,
// but doesn't always get them all, define AMBULANT_NO_STDC_NAMESPACE, since our
// workaround does not conflict with STLports:
//
//
// Harold Howe says:
// Borland switched to STLport in BCB6. Defining AMBULANT_NO_STDC_NAMESPACE with
// BCB6 does cause problems. If we detect C++ Builder, then don't define 
// AMBULANT_NO_STDC_NAMESPACE
//
#if !defined(__BORLANDC__)
//
// If STLport is using it's own namespace, and the real names are in
// the global namespace, then we duplicate STLport's using declarations
// (by defining AMBULANT_NO_STDC_NAMESPACE), we do this because STLport doesn't
// necessarily import all the names we need into namespace std::
// 
#  if (defined(__STL_IMPORT_VENDOR_CSTD) \
         || defined(__STL_USE_OWN_NAMESPACE) \
         || defined(_STLP_IMPORT_VENDOR_CSTD) \
         || defined(_STLP_USE_OWN_NAMESPACE)) \
      && (defined(__STL_VENDOR_GLOBAL_CSTD) || defined (_STLP_VENDOR_GLOBAL_CSTD))
#     define AMBULANT_NO_STDC_NAMESPACE
#     define AMBULANT_NO_EXCEPTION_STD_NAMESPACE
#  endif
#elif __BORLANDC__ < 0x560
// STLport doesn't import std::abs correctly:
#include <stdlib.h>
namespace std { using ::abs; }
// and strcmp/strcpy don't get imported either ('cos they are macros)
#include <string.h>
#ifdef strcpy
#  undef strcpy
#endif
#ifdef strcmp
#  undef strcmp
#endif
#ifdef _STLP_VENDOR_CSTD
namespace std{ using _STLP_VENDOR_CSTD::strcmp; using _STLP_VENDOR_CSTD::strcpy; }
#endif
#endif

//
// std::use_facet may be non-standard, uses a class instead:
//
#if defined(__STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS) || defined(_STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS)
#  define AMBULANT_NO_STD_USE_FACET
#  define AMBULANT_HAS_STLP_USE_FACET
#endif

//
// If STLport thinks there are no wide functions, <cwchar> etc. is not working; but
// only if AMBULANT_NO_STDC_NAMESPACE is not defined (if it is then we do the import 
// into std:: ourselves).
//
#if defined(_STLP_NO_NATIVE_WIDE_FUNCTIONS) && !defined(AMBULANT_NO_STDC_NAMESPACE)
#  define AMBULANT_NO_CWCHAR
#  define AMBULANT_NO_CWCTYPE
#endif

//
// Borland ships a version of STLport with C++ Builder 6 that lacks
// hashtables and the like:
//
#if defined(__BORLANDC__) && (__BORLANDC__ == 0x560)
#  undef AMBULANT_HAS_HASH
#endif


#define AMBULANT_STDLIB "STLPort standard library version " AMBULANT_STRINGIZE(__SGI_STL_PORT)







