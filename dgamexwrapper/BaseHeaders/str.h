/*
===========================================================================
Copyright (C) 2015 the OpenMoHAA team

This file is part of OpenMoHAA source code.

OpenMoHAA source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

OpenMoHAA source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenMoHAA source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

// str.cpp: Simple, DLL portable string class
//

#ifndef __STR_H__
#define __STR_H__

#include <assert.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#pragma warning(disable : 4710)     // function 'blah' not d
#endif

void TestStringClass();
extern void *__cdecl  MemoryMalloc(int size);
extern void __cdecl  MemoryFree(void * ptr);

class strdata
   {
   public:
      strdata () : len( 0 ), refcount ( 0 ), data ( NULL ), alloced ( 0 ) {}
      ~strdata () 
         {
		  if (data)
			MemoryFree(data);//delete[] data;
         }

      void AddRef () { refcount++; }
      bool DelRef () // True if killed
         {
         refcount--;
         if ( refcount < 0 )
            {
            delete this;
            return true;
            }
         
         return false;
         }

	  void* operator new(size_t n)
	  {
		  return MemoryMalloc(n);
	  }
	  void operator delete(void* n)
	  {
		  MemoryFree(n);
	  }
	  void operator delete[](void* n)
	  {
		  MemoryFree(n);
	  }
      char *data;
      int refcount;
      size_t alloced;
      size_t len;
   };

class str
	{
	protected:

		friend class		Archiver;
      strdata           *m_data;
      void              EnsureAlloced ( size_t, bool keepold = true );
      void              EnsureDataWritable ();

  	public:
								~str();
								str();
								str( const char *text );
								str( const str& string );
								str( const str string, size_t start, size_t end );
								str( const char ch );
								str( const int num );
								str( const float num );
								str( const unsigned num );


					size_t		length( void ) const;
		const		char *	c_str( void ) const;

					void		append( const char *text );
					void		append( const str& text );

					char		operator[]( intptr_t index ) const;
					char&		operator[]( intptr_t index );

					void		operator=( const str& text );
					void		operator=( const char *text );

		friend	str		operator+( const str& a, const str& b );
		friend	str		operator+( const str& a, const char *b );
		friend	str		operator+( const char *a, const str& b );

      friend	str		operator+( const str& a, const float b );
      friend	str		operator+( const str& a, const int b );
      friend	str		operator+( const str& a, const unsigned b );
      friend	str		operator+( const str& a, const bool b );
      friend	str		operator+( const str& a, const char b );

					str&		operator+=( const str& a );
					str&		operator+=( const char *a );
					str&		operator+=( const float a );
					str&		operator+=( const char a );
					str&		operator+=( const int a );
					str&		operator+=( const unsigned a );
					str&		operator+=( const bool a );

					str&		operator-=( int c );
					str&		operator--( int );

		friend	bool		operator==(	const str& a, const str& b );
		friend	bool		operator==(	const str& a, const char *b );
		friend	bool		operator==(	const char *a, const str& b );

		friend	bool		operator!=(	const str& a, const str& b );
		friend	bool		operator!=(	const str& a, const char *b );
		friend	bool		operator!=(	const char *a, const str& b );

                        operator const char * () const;

						void* operator new(size_t n)
						{
							return MemoryMalloc(n);
						}

               int      icmpn( const char *text, size_t n ) const;
			   int      icmpn( const str& text, size_t n ) const;
               int      icmp( const char *text ) const;
               int      icmp( const str& text ) const;
			   int      cmpn( const char *text, size_t n ) const;
			   int      cmpn( const str& text, size_t n ) const;

               void     tolower( void );
               void     toupper( void );

      static   char     *tolower( char *s1 );
      static   char     *toupper( char *s1 );

	  static   int      icmpn( const char *s1, const char *s2, size_t n );
      static   int      icmp( const char *s1, const char *s2 );
	  static   int      cmpn( const char *s1, const char *s2, size_t n );
      static   int      cmp( const char *s1, const char *s2 );

      static   void     snprintf ( char *dst, int size, const char *fmt, ... );
			   void		strip( void );

      static   bool	   isNumeric( const char *str );
               bool	   isNumeric( void ) const;

               void     CapLength ( size_t newlen );

			   void     BackSlashesToSlashes();
			   void     SlashesToBackSlashes();
			   void		DefaultExtension(const char *extension);
			   const char* GetExtension() const;
			   void		StripExtension();
			   void		SkipFile();
			   void		SkipPath();
   };

   typedef unsigned int const_str;

   char *strstrip(char *string);
   char *strlwc(char *string);

#endif
