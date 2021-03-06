/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

//////////////////////////////////////////////////////////////////////////
/*
    C++ features support, must be one of: (NX_SP_XX)

    CXX11_TYPE_TRAITS   - <type_traits>
    CXX11_TUPLE         - std::tuple
    CXX11_STACK_SWAP    - std::stack/std::queue/std::priority_queue's swap
    CXX11_ARRAY         - std::array
    CXX11_FORWARD_LIST  - std::forward_list
    CXX11_UNORDERED_MAP - std::unordered_map
    CXX11_UNORDERED_SET - std::unordered_set
    CXX11_NULLPTR       - nullptr
    CXX11_AUTO          - auto
    CXX11_RVALUE_REF    - Rvalue references
    CXX11_PERFECT_FWD   - Perfect Forwarding
    CXX11_SATIC_ASSERT  - static_assert
    CXX11_ALIAS         - Type alias, alias template
    CXX11_RANGEFOR      - Range-based for-loop
    CXX11_NOEXCEPT      - noexcept
    CXX11_CHAR_TYPE     - char16_t/char32_t
    CXX11_TEMPLATES     - Variadic templates
    CXX11_TEMPLATES_EX  - Extending variadic template template parameters
    CXX11_DELEGATING    - Delegating constructors
    CXX11_INHERITING    - Inheriting constructors
    CXX11_ALIGNMENT     - Alignment
    CXX11_INITIALIZER   - Initializer lists
    CXX11_LAMBDA        - Lambda expressions
*/
//////////////////////////////////////////////////////////////////////////

#define NX_CHECK_GNUC(ver, minor, patch) \
    defined(__GNUC__) /* >= ver.minor.patch */ && \
          ((__GNUC__ > (ver)) || ((__GNUC__ == (ver)) && \
          ((__GNUC_MINOR__ > (minor)) || ((__GNUC_MINOR__ == (minor)) && \
           (__GNUC_PATCHLEVEL__ >= (patch)) ) ) ) )

#define NX_CHECK_CLANG(ver, minor, patch) \
    defined(__clang__) /* >= ver.minor.patch */ && \
          ((__clang_major__ > (ver)) || ((__clang_major__ == (ver)) && \
          ((__clang_minor__ > (minor)) || ((__clang_minor__ == (minor)) && \
          (__clang_patchlevel__ >= (patch)) ) ) ) )

/*
    Microsoft Visual C++

    Start from Visual Studio 2010
    See: http://msdn.microsoft.com/en-us/library/hh567368.aspx
*/

#if defined(NX_CC_MSVC)

#   if (NX_CC_MSVC >= 1600)
#       define NX_SP_CXX11_STACK_SWAP
#       define NX_SP_CXX11_ARRAY
#       define NX_SP_CXX11_FORWARD_LIST
#       define NX_SP_CXX11_UNORDERED_MAP
#       define NX_SP_CXX11_UNORDERED_SET
#       define NX_SP_CXX11_NULLPTR
#       define NX_SP_CXX11_AUTO
#       define NX_SP_CXX11_RVALUE_REF
#       define NX_SP_CXX11_SATIC_ASSERT
#       define NX_SP_CXX11_LAMBDA
#   endif
#   if (NX_CC_MSVC >= 1700)
#       define NX_SP_CXX11_TYPE_TRAITS
#       define NX_SP_CXX11_PERFECT_FWD
#       define NX_SP_CXX11_RANGEFOR
#   endif
#   if (NX_CC_MSVC >= 1800)
#       define NX_SP_CXX11_ALIAS
#       define NX_SP_CXX11_TEMPLATES
#       define NX_SP_CXX11_TEMPLATES_EX
#       define NX_SP_CXX11_TUPLE
#       define NX_SP_CXX11_DELEGATING
#       define NX_SP_CXX11_INITIALIZER
#   endif

#elif defined(NX_CC_GNUC)

/*
    C++ front-end for the LLVM compiler

    Start from Clang 2.9 (with Rvalue references)
    So I can just use __cxx_rvalue_references__ to check C++11 support.
    See: http://clang.llvm.org/cxx_status.html
*/

#if defined(NX_CC_CLANG)

#if __has_feature(__cxx_rvalue_references__)

#   if NX_CHECK_CLANG(2, 9, 0)
#       define NX_SP_CXX11_TYPE_TRAITS
#       define NX_SP_CXX11_STACK_SWAP
#       define NX_SP_CXX11_ARRAY
#       define NX_SP_CXX11_FORWARD_LIST
#       define NX_SP_CXX11_UNORDERED_MAP
#       define NX_SP_CXX11_UNORDERED_SET
#       define NX_SP_CXX11_AUTO
#       define NX_SP_CXX11_RVALUE_REF
#       define NX_SP_CXX11_SATIC_ASSERT
#       define NX_SP_CXX11_CHAR_TYPE
#       define NX_SP_CXX11_TEMPLATES
#       define NX_SP_CXX11_TEMPLATES_EX
#       define NX_SP_CXX11_TUPLE
#   endif
#   if NX_CHECK_CLANG(3, 0, 0)
#       define NX_SP_CXX11_NULLPTR
#       define NX_SP_CXX11_ALIAS
#       define NX_SP_CXX11_RANGEFOR
#       define NX_SP_CXX11_NOEXCEPT
#       define NX_SP_CXX11_DELEGATING
#   endif
#   if NX_CHECK_CLANG(3, 1, 0)
#       define NX_SP_CXX11_INITIALIZER
#       define NX_SP_CXX11_LAMBDA
#   endif
#   if NX_CHECK_CLANG(3, 3, 0)
#       define NX_SP_CXX11_INHERITING
#       define NX_SP_CXX11_ALIGNMENT
#   endif

#endif/*__has_feature(__cxx_rvalue_references__)*/

/*
    GNU C++

    Start from GCC 4.3
    See: http://gcc.gnu.org/projects/cxx0x.html
*/

#elif (defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L))

#   if NX_CHECK_GNUC(4, 3, 0)
#       define NX_SP_CXX11_TYPE_TRAITS
#       define NX_SP_CXX11_STACK_SWAP
#       define NX_SP_CXX11_ARRAY
#       define NX_SP_CXX11_FORWARD_LIST
#       define NX_SP_CXX11_UNORDERED_MAP
#       define NX_SP_CXX11_UNORDERED_SET
#       define NX_SP_CXX11_RVALUE_REF
#       define NX_SP_CXX11_SATIC_ASSERT
#       define NX_SP_CXX11_TEMPLATES
#       define NX_SP_CXX11_TUPLE
#   endif
#   if NX_CHECK_GNUC(4, 4, 0)
#       define NX_SP_CXX11_AUTO
#       define NX_SP_CXX11_CHAR_TYPE
#       define NX_SP_CXX11_TEMPLATES_EX
#       define NX_SP_CXX11_INITIALIZER
#   endif
#   if NX_CHECK_GNUC(4, 5, 0)
#       define NX_SP_CXX11_LAMBDA
#   endif
#   if NX_CHECK_GNUC(4, 6, 0)
#       define NX_SP_CXX11_NULLPTR
#       define NX_SP_CXX11_RANGEFOR
#       define NX_SP_CXX11_NOEXCEPT
#   endif
#   if NX_CHECK_GNUC(4, 7, 0)
#       define NX_SP_CXX11_ALIAS
#       define NX_SP_CXX11_DELEGATING
#   endif
#   if NX_CHECK_GNUC(4, 8, 0)
#       define NX_SP_CXX11_INHERITING
#       define NX_SP_CXX11_ALIGNMENT
#   endif

#endif/*defined(NX_CC_GNUC)*/

#endif

//////////////////////////////////////////////////////////////////////////
