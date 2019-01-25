
#ifndef _PCRECPP_H
#define _PCRECPP_H
#include <string>
#include <pcre.h>
#include <pcrecpparg.h>   // defines the Arg class
// This isn't technically needed here, but we include it
// anyway so folks who include pcrecpp.h don't have to.
#include <pcre_stringpiece.h>

namespace pcrecpp {

#define PCRE_SET_OR_CLEAR(b, o) \
    if (b) all_options_ |= (o); else all_options_ &= ~(o); \
    return *this

#define PCRE_IS_SET(o)  \
        (all_options_ & o) == o

/***** Compiling regular expressions: the RE class *****/

// RE_Options allow you to set options to be passed along to pcre,
// along with other options we put on top of pcre.
// Only 9 modifiers, plus match_limit and match_limit_recursion,
// are supported now.
class PCRECPP_EXP_DEFN RE_Options {
 public:
  // constructor
  RE_Options() : match_limit_(0), match_limit_recursion_(0), all_options_(0) {}

  // alternative constructor.
  // To facilitate transfer of legacy code from C programs
  //
  // This lets you do
  //    RE(pattern, RE_Options(PCRE_CASELESS|PCRE_MULTILINE)).PartialMatch(str);
  // But new code is better off doing
  //    RE(pattern,
  //      RE_Options().set_caseless(true).set_multiline(true)).PartialMatch(str);
  RE_Options(int option_flags) : match_limit_(0), match_limit_recursion_(0),
                                 all_options_(option_flags) {}
  // we're fine with the default destructor, copy constructor, etc.

  // accessors and mutators
  int match_limit() const { return match_limit_; };
  RE_Options &set_match_limit(int limit) {
    match_limit_ = limit;
    return *this;
  }

  int match_limit_recursion() const { return match_limit_recursion_; };
  RE_Options &set_match_limit_recursion(int limit) {
    match_limit_recursion_ = limit;
    return *this;
  }

  bool caseless() const {
    return PCRE_IS_SET(PCRE_CASELESS);
  }
  RE_Options &set_caseless(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_CASELESS);
  }

  bool multiline() const {
    return PCRE_IS_SET(PCRE_MULTILINE);
  }
  RE_Options &set_multiline(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_MULTILINE);
  }

  bool dotall() const {
    return PCRE_IS_SET(PCRE_DOTALL);
  }
  RE_Options &set_dotall(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_DOTALL);
  }

  bool extended() const {
    return PCRE_IS_SET(PCRE_EXTENDED);
  }
  RE_Options &set_extended(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_EXTENDED);
  }

  bool dollar_endonly() const {
    return PCRE_IS_SET(PCRE_DOLLAR_ENDONLY);
  }
  RE_Options &set_dollar_endonly(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_DOLLAR_ENDONLY);
  }

  bool extra() const {
    return PCRE_IS_SET(PCRE_EXTRA);
  }
  RE_Options &set_extra(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_EXTRA);
  }

  bool ungreedy() const {
    return PCRE_IS_SET(PCRE_UNGREEDY);
  }
  RE_Options &set_ungreedy(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_UNGREEDY);
  }

  bool utf8() const {
    return PCRE_IS_SET(PCRE_UTF8);
  }
  RE_Options &set_utf8(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_UTF8);
  }

  bool no_auto_capture() const {
    return PCRE_IS_SET(PCRE_NO_AUTO_CAPTURE);
  }
  RE_Options &set_no_auto_capture(bool x) {
    PCRE_SET_OR_CLEAR(x, PCRE_NO_AUTO_CAPTURE);
  }

  RE_Options &set_all_options(int opt) {
    all_options_ = opt;
    return *this;
  }
  int all_options() const {
    return all_options_ ;
  }

  // TODO: add other pcre flags

 private:
  int match_limit_;
  int match_limit_recursion_;
  int all_options_;
};

// These functions return some common RE_Options
static inline RE_Options UTF8() {
  return RE_Options().set_utf8(true);
}

static inline RE_Options CASELESS() {
  return RE_Options().set_caseless(true);
}
static inline RE_Options MULTILINE() {
  return RE_Options().set_multiline(true);
}

static inline RE_Options DOTALL() {
  return RE_Options().set_dotall(true);
}

static inline RE_Options EXTENDED() {
  return RE_Options().set_extended(true);
}

// Interface for regular expression matching.  Also corresponds to a
// pre-compiled regular expression.  An "RE" object is safe for
// concurrent use by multiple threads.
class PCRECPP_EXP_DEFN RE {
 public:
  // We provide implicit conversions from strings so that users can
  // pass in a string or a "const char*" wherever an "RE" is expected.
  RE(const string& pat) { Init(pat, NULL); }
  RE(const string& pat, const RE_Options& option) { Init(pat, &option); }
  RE(const char* pat) { Init(pat, NULL); }
  RE(const char* pat, const RE_Options& option) { Init(pat, &option); }
  RE(const unsigned char* pat) {
    Init(reinterpret_cast<const char*>(pat), NULL);
  }
  RE(const unsigned char* pat, const RE_Options& option) {
    Init(reinterpret_cast<const char*>(pat), &option);
  }

  // Copy constructor & assignment - note that these are expensive
  // because they recompile the expression.
  RE(const RE& re) { Init(re.pattern_, &re.options_); }
  const RE& operator=(const RE& re) {
    if (this != &re) {
      Cleanup();

      // This is the code that originally came from Google
      // Init(re.pattern_.c_str(), &re.options_);

      // This is the replacement from Ari Pollak
      Init(re.pattern_, &re.options_);
    }
    return *this;
  }


  ~RE();

  // The string specification for this RE.  E.g.
  //   RE re("ab*c?d+");
  //   re.pattern();    // "ab*c?d+"
  const string& pattern() const { return pattern_; }

  // If RE could not be created properly, returns an error string.
  // Else returns the empty string.
  const string& error() const { return *error_; }

  /***** The useful part: the matching interface *****/

  // This is provided so one can do pattern.ReplaceAll() just as
  // easily as ReplaceAll(pattern-text, ....)

  bool FullMatch(const StringPiece& text,
                 const Arg& ptr1 = no_arg,
                 const Arg& ptr2 = no_arg,
                 const Arg& ptr3 = no_arg,
                 const Arg& ptr4 = no_arg,
                 const Arg& ptr5 = no_arg,
                 const Arg& ptr6 = no_arg,
                 const Arg& ptr7 = no_arg,
                 const Arg& ptr8 = no_arg,
                 const Arg& ptr9 = no_arg,
                 const Arg& ptr10 = no_arg,
                 const Arg& ptr11 = no_arg,
                 const Arg& ptr12 = no_arg,
                 const Arg& ptr13 = no_arg,
                 const Arg& ptr14 = no_arg,
                 const Arg& ptr15 = no_arg,
                 const Arg& ptr16 = no_arg) const;

  bool PartialMatch(const StringPiece& text,
                    const Arg& ptr1 = no_arg,
                    const Arg& ptr2 = no_arg,
                    const Arg& ptr3 = no_arg,
                    const Arg& ptr4 = no_arg,
                    const Arg& ptr5 = no_arg,
                    const Arg& ptr6 = no_arg,
                    const Arg& ptr7 = no_arg,
                    const Arg& ptr8 = no_arg,
                    const Arg& ptr9 = no_arg,
                    const Arg& ptr10 = no_arg,
                    const Arg& ptr11 = no_arg,
                    const Arg& ptr12 = no_arg,
                    const Arg& ptr13 = no_arg,
                    const Arg& ptr14 = no_arg,
                    const Arg& ptr15 = no_arg,
                    const Arg& ptr16 = no_arg) const;

  bool Consume(StringPiece* input,
               const Arg& ptr1 = no_arg,
               const Arg& ptr2 = no_arg,
               const Arg& ptr3 = no_arg,
               const Arg& ptr4 = no_arg,
               const Arg& ptr5 = no_arg,
               const Arg& ptr6 = no_arg,
               const Arg& ptr7 = no_arg,
               const Arg& ptr8 = no_arg,
               const Arg& ptr9 = no_arg,
               const Arg& ptr10 = no_arg,
               const Arg& ptr11 = no_arg,
               const Arg& ptr12 = no_arg,
               const Arg& ptr13 = no_arg,
               const Arg& ptr14 = no_arg,
               const Arg& ptr15 = no_arg,
               const Arg& ptr16 = no_arg) const;

  bool FindAndConsume(StringPiece* input,
                      const Arg& ptr1 = no_arg,
                      const Arg& ptr2 = no_arg,
                      const Arg& ptr3 = no_arg,
                      const Arg& ptr4 = no_arg,
                      const Arg& ptr5 = no_arg,
                      const Arg& ptr6 = no_arg,
                      const Arg& ptr7 = no_arg,
                      const Arg& ptr8 = no_arg,
                      const Arg& ptr9 = no_arg,
                      const Arg& ptr10 = no_arg,
                      const Arg& ptr11 = no_arg,
                      const Arg& ptr12 = no_arg,
                      const Arg& ptr13 = no_arg,
                      const Arg& ptr14 = no_arg,
                      const Arg& ptr15 = no_arg,
                      const Arg& ptr16 = no_arg) const;

  bool Replace(const StringPiece& rewrite,
               string *str) const;

  int GlobalReplace(const StringPiece& rewrite,
                    string *str) const;

  bool Extract(const StringPiece &rewrite,
               const StringPiece &text,
               string *out) const;

  // Escapes all potentially meaningful regexp characters in
  // 'unquoted'.  The returned string, used as a regular expression,
  // will exactly match the original string.  For example,
  //           1.5-2.0?
  // may become:
  //           1\.5\-2\.0\?
  // Note QuoteMeta behaves the same as perl's QuoteMeta function,
  // *except* that it escapes the NUL character (\0) as backslash + 0,
  // rather than backslash + NUL.
  static string QuoteMeta(const StringPiece& unquoted);


  /***** Generic matching interface *****/

  // Type of match (TODO: Should be restructured as part of RE_Options)
  enum Anchor {
    UNANCHORED,         // No anchoring
    ANCHOR_START,       // Anchor at start only
    ANCHOR_BOTH         // Anchor at start and end
  };

  // General matching routine.  Stores the length of the match in
  // "*consumed" if successful.
  bool DoMatch(const StringPiece& text,
               Anchor anchor,
               int* consumed,
               const Arg* const* args, int n) const;

  // Return the number of capturing subpatterns, or -1 if the
  // regexp wasn't valid on construction.
  int NumberOfCapturingGroups() const;

  // The default value for an argument, to indicate the end of the argument
  // list. This must be used only in optional argument defaults. It should NOT
  // be passed explicitly. Some people have tried to use it like this:
  //
  //   FullMatch(x, y, &z, no_arg, &w);
  //
  // This is a mistake, and will not work.
  static Arg no_arg;

 private:

  void Init(const string& pattern, const RE_Options* options);
  void Cleanup();

  // Match against "text", filling in "vec" (up to "vecsize" * 2/3) with
  // pairs of integers for the beginning and end positions of matched
  // text.  The first pair corresponds to the entire matched text;
  // subsequent pairs correspond, in order, to parentheses-captured
  // matches.  Returns the number of pairs (one more than the number of
  // the last subpattern with a match) if matching was successful
  // and zero if the match failed.
  // I.e. for RE("(foo)|(bar)|(baz)") it will return 2, 3, and 4 when matching
  // against "foo", "bar", and "baz" respectively.
  // When matching RE("(foo)|hello") against "hello", it will return 1.
  // But the values for all subpattern are filled in into "vec".
  int TryMatch(const StringPiece& text,
               int startpos,
               Anchor anchor,
               bool empty_ok,
               int *vec,
               int vecsize) const;

  // Append the "rewrite" string, with backslash subsitutions from "text"
  // and "vec", to string "out".
  bool Rewrite(string *out,
               const StringPiece& rewrite,
               const StringPiece& text,
               int *vec,
               int veclen) const;

  // internal implementation for DoMatch
  bool DoMatchImpl(const StringPiece& text,
                   Anchor anchor,
                   int* consumed,
                   const Arg* const args[],
                   int n,
                   int* vec,
                   int vecsize) const;

  // Compile the regexp for the specified anchoring mode
  pcre* Compile(Anchor anchor);

  string        pattern_;
  RE_Options    options_;
  pcre*         re_full_;       // For full matches
  pcre*         re_partial_;    // For partial matches
  const string* error_;         // Error indicator (or points to empty string)
};

}   // namespace pcrecpp

#endif /* _PCRECPP_H */
