
/* Precaution to avoid an error easily made by the application programmer. */
#ifdef SPINNERACTOR_API
#error Leave the internal SPINNERACTOR_API define alone.
#endif /* SPINNERACTOR_API */

/*
  On MSWindows platforms, one of these defines must always be set when
  building application programs:

   - "MLE_DLL", when the application programmer is using the
     library in the form of a dynamic link library (DLL)

   - "MLE_NOT_DLL", when the application programmer is using the
     library in the form of a static object library (LIB)

  Note that either MLE_DLL or MLE_NOT_DLL _must_ be defined by
  the application programmer on MSWindows platforms, or else the
  #error statement will hit. Set up one or the other of these two
  defines in your compiler environment according to how the library
  was built -- as a DLL (use "MLE_DLL") or as a LIB (use
  "MLE_NOT_DLL").

  (Setting up defines for the compiler is typically done by either
  adding something like "/DMLE_DLL" to the compiler's argument
  line (for command-line build processes), or by adding the define to
  the list of preprocessor symbols in your IDE GUI (in the MSVC IDE,
  this is done from the "Project"->"Settings" menu, choose the "C/C++"
  tab, then "Preprocessor" from the dropdown box and add the
  appropriate define)).

  It is extremely important that the application programmer uses the
  correct define, as using "MLE_NOT_DLL" when "MLE_DLL" is
  correct is likely to cause mysterious crashes.
 */

// Magic Lantern export rules.
# ifdef SPINNERACTOR_EXPORTS
#   ifdef MLE_MAKE_DLL
#     define SPINNERACTOR_API __declspec(dllexport)
#   endif /* MLE_MAKE_DLL */
# else /* ! SPINNERACTOR_EXPORTS */
#   ifdef MLE_DLL
#     define SPINNERACTOR_API __declspec(dllimport)
#   else /* ! MLE_DLL */
#     ifndef MLE_NOT_DLL
#       error Define either MLE_DLL or MLE_NOT_DLL as appropriate for your linkage! See SpinnerActor.h for further instructions.
#     endif /* MLE_NOT_DLL */
#   endif /* ! MLE_DLL */
# endif /* ! SPINNERACTOR_EXPORTS */

/* Empty define to avoid errors when _not_ compiling an MSWindows DLL */
#ifndef SPINNERACTOR_API
# define SPINNERACTOR_API
#endif /* ! SPINNERACTOR_API */
