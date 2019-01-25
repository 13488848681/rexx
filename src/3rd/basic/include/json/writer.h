#ifndef JSON_WRITER_H_INCLUDED
# define JSON_WRITER_H_INCLUDED

# include "value.h"
# include <vector>
# include <string>
# include <iostream>

namespace Json {

   class Value;

   /** \brief Abstract class for writers.
    */
   class JSON_API Writer
   {
   public:
      virtual ~Writer();

      virtual std::string write( const Value &root ) = 0;
   };


   class JSON_API FastWriter : public Writer
   {
   public:
      FastWriter();
      virtual ~FastWriter(){}

      void enableYAMLCompatibility();

   public: // overridden from Writer
      virtual std::string write( const Value &root );

   private:
      void writeValue( const Value &value );

      std::string document_;
      bool yamlCompatiblityEnabled_;
   };


   class JSON_API StyledWriter: public Writer
   {
   public:
      StyledWriter();
      virtual ~StyledWriter(){}

   public: // overridden from Writer
      /** \brief Serialize a Value in <a HREF="http://www.json.org">JSON</a> format.
       * \param root Value to serialize.
       * \return String containing the JSON document that represents the root value.
       */
      virtual std::string write( const Value &root );

   private:
      void writeValue( const Value &value );
      void writeArrayValue( const Value &value );
      bool isMultineArray( const Value &value );
      void pushValue( const std::string &value );
      void writeIndent();
      void writeWithIndent( const std::string &value );
      void indent();
      void unindent();
      void writeCommentBeforeValue( const Value &root );
      void writeCommentAfterValueOnSameLine( const Value &root );
      bool hasCommentForValue( const Value &value );
      static std::string normalizeEOL( const std::string &text );

      typedef std::vector<std::string> ChildValues;

      ChildValues childValues_;
      std::string document_;
      std::string indentString_;
      int rightMargin_;
      int indentSize_;
      bool addChildValues_;
   };


   class JSON_API StyledStreamWriter
   {
   public:
      StyledStreamWriter( std::string indentation="\t" );
      ~StyledStreamWriter(){}

   public:
      /** \brief Serialize a Value in <a HREF="http://www.json.org">JSON</a> format.
       * \param out Stream to write to. (Can be ostringstream, e.g.)
       * \param root Value to serialize.
       * \note There is no point in deriving from Writer, since write() should not return a value.
       */
      void write( std::ostream &out, const Value &root );

   private:
      void writeValue( const Value &value );
      void writeArrayValue( const Value &value );
      bool isMultineArray( const Value &value );
      void pushValue( const std::string &value );
      void writeIndent();
      void writeWithIndent( const std::string &value );
      void indent();
      void unindent();
      void writeCommentBeforeValue( const Value &root );
      void writeCommentAfterValueOnSameLine( const Value &root );
      bool hasCommentForValue( const Value &value );
      static std::string normalizeEOL( const std::string &text );

      typedef std::vector<std::string> ChildValues;

      ChildValues childValues_;
      std::ostream* document_;
      std::string indentString_;
      int rightMargin_;
      std::string indentation_;
      bool addChildValues_;
   };

   std::string JSON_API valueToString( Int value );
   std::string JSON_API valueToString( UInt value );
   std::string JSON_API valueToString( double value );
   std::string JSON_API valueToString( bool value );
   std::string JSON_API valueToQuotedString( const char *value );

   /// \brief Output using the StyledStreamWriter.
   /// \see Json::operator>>()
   std::ostream& operator<<( std::ostream&, const Value &root );

} // namespace Json



#endif // JSON_WRITER_H_INCLUDED
