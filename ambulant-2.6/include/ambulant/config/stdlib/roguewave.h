

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

/* 
 * @$Id$ 
 */

//  Rogue Wave std lib:

#if !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)
#  include <utility>
#  if !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)
#     error This is not the Rogue Wave standard library
#  endif
#endif
//
// figure out a consistent version number:
//
#ifndef _RWSTD_VER
#  define AMBULANT_RWSTD_VER 0x010000
#elif _RWSTD_VER < 0x010000
#  define AMBULANT_RWSTD_VER (_RWSTD_VER << 8)
#else
#  define AMBULANT_RWSTD_VER _RWSTD_VER
#endif

#ifndef _RWSTD_VER
#  define AMBULANT_STDLIB "Rogue Wave standard library version (Unknown version)"
#else
#  define AMBULANT_STDLIB "Rogue Wave standard library version " AMBULANT_STRINGIZE(_RWSTD_VER)
#endif

//
// Prior to version 2.2.0 the primary template for std::numeric_limits
// does not have compile time constants, even though specializations of that
// template do:
//
#if AMBULANT_RWSTD_VER < 0x020200
#  define AMBULANT_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

#if AMBULANT_RWSTD_VER <= 0x020101
#  define AMBULANT_NO_LONG_LONG_NUMERIC_LIMITS
# endif

//
// Borland version of numeric_limits lacks __int64 specialisation:
//
#ifdef __BORLANDC__
#  define AMBULANT_NO_MS_INT64_NUMERIC_LIMITS
#endif

//
// No std::iterator if it can't figure out default template args:
//
#if defined(_RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES) || defined(RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES) || (AMBULANT_RWSTD_VER < 0x020000)
#  define AMBULANT_NO_STD_ITERATOR
#endif

//
// No iterator traits without partial specialization:
//
#if defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) || defined(RWSTD_NO_CLASS_PARTIAL_SPEC)
#  define AMBULANT_NO_STD_ITERATOR_TRAITS
#endif

//
// Prior to version 2.0, std::auto_ptr was buggy, and there were no
// new-style iostreams, and no conformant std::allocator:
//
#if (AMBULANT_RWSTD_VER < 0x020000)
#error Compiler too old for Ambulant
#endif

//
// No template iterator constructors without member template support:
//
#if defined(RWSTD_NO_MEMBER_TEMPLATES) || defined(_RWSTD_NO_MEMBER_TEMPLATES)
#  define AMBULANT_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#endif

//
// RW defines _RWSTD_ALLOCATOR if the allocator is conformant and in use
// (the or _HPACC_ part is a hack - the library seems to define _RWSTD_ALLOCATOR
// on HP aCC systems even though the allocator is in fact broken):
//
#if !defined(_RWSTD_ALLOCATOR) || (defined(__HP_aCC) && __HP_aCC <= 33100)
#  define AMBULANT_NO_STD_ALLOCATOR
#endif

//
// If we have a std::locale, we still may not have std::use_facet:
//
#if defined(_RWSTD_NO_TEMPLATE_ON_RETURN_TYPE) && !defined(AMBULANT_NO_STD_LOCALE)
#  define AMBULANT_NO_STD_USE_FACET
#  define AMBULANT_HAS_TWO_ARG_USE_FACET
#endif

//
// There's no std::distance prior to version 2, or without
// partial specialization support:
//
#if (AMBULANT_RWSTD_VER < 0x020000) || defined(_RWSTD_NO_CLASS_PARTIAL_SPEC)
    #define AMBULANT_NO_STD_DISTANCE
#endif

//
// Some versions of the rogue wave library don't have assignable
// OutputIterators:
//
#if AMBULANT_RWSTD_VER < 0x020100
#  define AMBULANT_NO_STD_OUTPUT_ITERATOR_ASSIGN
#endif


