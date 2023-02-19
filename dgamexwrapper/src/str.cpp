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

#include "str.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#pragma warning(disable : 4244)     // 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 4710)     // function 'blah' not inlined
#endif

static const int STR_ALLOC_GRAN = 20;

char *str::tolower
   (
   char *s1
   )
   
   {
   char *s;

   s = s1;
	while( *s )
      {
      *s = ::tolower( *s );
		s++;
	   }
   
   return s1;
   }

char *str::toupper
   (
   char *s1
   )
   
   {
   char *s;

   s = s1;
	while( *s )
      {
      *s = ::toupper( *s );
		s++;
	   }
   
   return s1;
   }

int str::icmpn
   (
   const char *s1, 
   const char *s2, 
   size_t n
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- )
         {
         // strings are equal until end point
			return 0;
		   }
		
		if ( c1 != c2 )
         {
			if ( c1 >= 'a' && c1 <= 'z' )
            {
				c1 -= ( 'a' - 'A' );
			   }

			if ( c2 >= 'a' && c2 <= 'z' )
            {
				c2 -= ( 'a' - 'A' );
			   }

			if ( c1 < c2 )
            {
            // strings less than
				return -1;
			   }
         else if ( c1 > c2 ) 
            {
            // strings greater than
            return 1;
            }
		   }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

int str::icmp
   (
   const char *s1,
   const char *s2
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( c1 != c2 )
         {
			if ( c1 >= 'a' && c1 <= 'z' )
            {
				c1 -= ( 'a' - 'A' );
			   }

			if ( c2 >= 'a' && c2 <= 'z' )
            {
				c2 -= ( 'a' - 'A' );
			   }

			if ( c1 < c2 )
            {
            // strings less than
				return -1;
			   }
         else if ( c1 > c2 ) 
            {
            // strings greater than
            return 1;
            }
		   }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

int str::cmpn
   (
   const char *s1, 
   const char *s2, 
   size_t n
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( !n-- )
         {
         // strings are equal until end point
			return 0;
		   }
		
		if ( c1 < c2 )
         {
         // strings less than
			return -1;
			}
      else if ( c1 > c2 ) 
         {
         // strings greater than
         return 1;
         }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

int str::cmp
   (
   const char *s1, 
   const char *s2
   )
   
   {
	int c1;
   int c2;
	
	do 
      {
		c1 = *s1++;
		c2 = *s2++;

		if ( c1 < c2 )
         {
         // strings less than
			return -1;
			}
      else if ( c1 > c2 ) 
         {
         // strings greater than
         return 1;
         }
	   } 
   while( c1 );
	
   // strings are equal
	return 0;
   }

/*
============
IsNumeric

Checks a string to see if it contains only numerical values.
============
*/
bool str::isNumeric
   (
   const char *str
   )

   {
	size_t len;
	size_t i;
	bool dot;

	if ( *str == '-' )
		{
		str++;
		}

	dot = false;
	len = strlen( str );
	for( i = 0; i < len; i++ )
		{
		if ( !isdigit( str[ i ] ) )
			{
			if ( ( str[ i ] == '.' ) && !dot )
				{
				dot = true;
				continue;
				}
			return false;
			}
		}

	return true;
   }

str operator+
   (
   const str& a,
   const float b
   )

   {
   char text[ 20 ];

	str result( a );

   sprintf( text, "%f", b );
	result.append( text );

	return result;
   }

str operator+
   (
   const str& a,
   const int b
   )

   {
   char text[ 20 ];

	str result( a );

   sprintf( text, "%d", b );
	result.append( text );

	return result;
   }

str operator+
   (
   const str& a,
   const unsigned b
   )

   {
   char text[ 20 ];

	str result( a );

   sprintf( text, "%u", b );
	result.append( text );

	return result;
   }

str& str::operator+=
	(
	const float a
	)

	{
   char text[ 20 ];

   sprintf( text, "%f", a );
	append( text );

   return *this;
	}

str& str::operator+=
	(
	const int a
	)

	{
   char text[ 20 ];

   sprintf( text, "%d", a );
	append( text );

   return *this;
	}

str& str::operator+=
	(
	const unsigned a
	)

	{
   char text[ 20 ];

   sprintf( text, "%u", a );
	append( text );

   return *this;
	}

str& str::operator-=
	(
	int c
	)

{
	if( !m_data )
	{
		return *this;
	}

	if( !m_data->len )
	{
		return *this;
	}

	m_data->len -= c;
	if( m_data->len < 0 )
	{
		m_data->len = 0;
	}

	EnsureDataWritable();

	m_data->data[ m_data->len ] = 0;

	return *this;
}

str& str::operator--( int )
{
	*this -= 1;
	return *this;
}

void str::CapLength 
   (
   size_t newlen 
   )

   {
   assert ( m_data );
   
   if ( length() <= newlen )
      return;

   EnsureDataWritable ();

   m_data->data[newlen] = 0;
   m_data->len = newlen;
   }

void str::EnsureDataWritable 
	(
	void
	)

{
	strdata *olddata;
	size_t len;

	if( !m_data )
		return;

	if( !m_data->refcount )
		return;

	olddata = m_data;
	len = length();

	m_data = new strdata;

	//FILE *pFile;
	//pFile = fopen("myfile.txt", "w");
	//fprintf(pFile, "m_data %p\n", (void*)(m_data));
	//fclose(pFile);
	EnsureAlloced( len + 1, false );
	strncpy( m_data->data, olddata->data, len + 1 );
	m_data->len = len;

	olddata->DelRef();
}

void str::EnsureAlloced 
	(
	size_t amount,
	bool keepold
	)

{
	if( !m_data )
	{
		if( amount > 1 )
		{
			//FILE *pFile;
			//pFile = fopen("myfile.txt", "w");
			m_data = new strdata;
			//fprintf(pFile, "m_data %p\n", (void*)(m_data));

			m_data->data = (char*)MemoryMalloc(sizeof(char)* amount);// new char[amount];
			//fprintf(pFile, "m_data->data %p\n", (void*)(m_data->data));
			//fclose(pFile);

			m_data->alloced = amount;

			m_data->data[ 0 ] = '\0';

			return;
		}

		if( !m_data )
		{
			return;
		}
	}

	// Now, let's make sure it's writable
	EnsureDataWritable();

	char *newbuffer;
	bool wasalloced = ( m_data->alloced != 0 );

	if( amount < m_data->alloced )
		return;

	assert( amount );

	if( amount == 1 )
	{
		m_data->alloced = 1;
	}
	else
	{
		size_t newsize, mod;

		mod = amount % STR_ALLOC_GRAN;

		if( !mod )
			newsize = amount;
		else
			newsize = amount + STR_ALLOC_GRAN - mod;

		m_data->alloced = newsize;
	}

	newbuffer = (char*)MemoryMalloc(sizeof(char)* m_data->alloced);// new char[ m_data->alloced ];

	if( wasalloced && keepold )
	{
		strcpy( newbuffer, m_data->data );
	}

	if( m_data->data )
	{
		MemoryFree(m_data->data);//delete[] m_data->data;
	}

	m_data->data = newbuffer;
}

void str::BackSlashesToSlashes
   (
   void
   )

   {
   size_t i;

   EnsureDataWritable ();

   for ( i=0; i < m_data->len; i++ )
      {
      if ( m_data->data[i] == '\\' )
         m_data->data[i] = '/';
      }
   }

void str::SlashesToBackSlashes
   (
   void
   )

   {
   size_t i;

   EnsureDataWritable ();

   for ( i=0; i < m_data->len; i++ )
      {
      if ( m_data->data[i] == '/' )
         m_data->data[i] = '\\';
      }
   }

void str::DefaultExtension(const char *extension)
{
	EnsureDataWritable();

	const char* src = m_data->data + m_data->len - 1;

	while (*src != '/' && src != m_data->data)
	{
		if (*src == '.')
		{
			// it has an extension
			return;
		}
		src--;
	}

	append(".");
	append(extension);
}

const char* str::GetExtension() const
{
	size_t length, i;

	length = m_data->len - 1;
	i = length;

	while (m_data->data[i] != '.')
	{
		i--;
		if (m_data->data[i] == '/' || i == 0)
		{
			return ""; // no extension
		}
	}

	return &m_data->data[i + 1];
}

void str::StripExtension()
{
	EnsureDataWritable();

	size_t i = m_data->len;
	while (i > 0 && m_data->data[i] != '.')
	{
		i--;
		if (m_data->data[i] == '/')
			return; // no extension
	}
	if (i)
	{
		m_data->len = i;
		m_data->data[m_data->len] = 0;

		EnsureDataWritable();
	}
}

void str::SkipFile()
{
	EnsureDataWritable();

	size_t i = m_data->len;
	while (i > 0 && m_data->data[i] != '/' && m_data->data[i] != '\\')
	{
		i--;
	}
	m_data->len = i;
	m_data->data[m_data->len] = 0;

	EnsureDataWritable();
}

void str::SkipPath()
{
	EnsureDataWritable();

	const char *pathname = m_data->data;
	const char *last;

	last = m_data->data;
	while (*pathname)
	{
		if (*pathname == '/' || *pathname == '\\')
			last = pathname + 1;
		pathname++;
	}

	size_t lastpos = last - m_data->data;
	if (lastpos > 0)
	{
		size_t length = m_data->len - lastpos;
		for (size_t i = 0; i < length; i++)
		{
			m_data->data[i] = last[i];
		}

		m_data->len = length;
		m_data->data[length] = 0;

		EnsureDataWritable();
	}
}

void str::snprintf 
   (
   char *dst,
   int size,
   const char *fmt, 
   ...
   )

   {
   char buffer[0x10000];
	int		len;
	va_list		argptr;

	va_start (argptr,fmt);
	len = vsprintf (buffer,fmt,argptr);
	va_end (argptr);
	
   assert ( len < size );

   strncpy (dst, buffer, size-1);
   }

void str::strip( void )
{
	char *last;
	char *s;
	size_t i;

	if( m_data == NULL || m_data->data == NULL ) return;
	s = m_data->data;
	while( isspace( ( int )*s ) && *s ) s++;

	last = s + m_data->len - ( s - m_data->data );
	while( last > s ) {
		if( !isspace( ( int )*( last - 1 ) ) )
			break;
		last--;
	}

	*last = '\0';

	m_data->len = last - s;
	for( i = 0; i < m_data->len + 1; i++ )
	{
		m_data->data[ i ] = s[ i ];
	}

	EnsureDataWritable();
}

char *strstrip( char *string )
{
	char *last;
	char *s;

	s = string;
	while( isspace( ( int )*s ) && *s ) s++;

	last = s + strlen( s ) - ( s - string );
	while( last > s ) {
		if( !isspace( ( int )*( last - 1 ) ) )
			break;
		last--;
	}

	*last = '\0';

	return s;
}

char *strlwc( char *string )
{
	char *s = string;
	while( *s )
	{
		*s = tolower( *s );
		s++;
	}

	return s;
}

#ifdef _WIN32
#pragma warning(disable : 4189)		// local variable is initialized but not referenced
#endif

/*
=================
TestStringClass

This is a fairly rigorous test of the str class's functionality.
Because of the fairly global and subtle ramifications of a bug occuring
in this class, it should be run after any changes to the class.
Add more tests as functionality is changed.  Tests should include
any possible bounds violation and NULL data tests.
=================
*/
void TestStringClass
	(
	void 
	)

	{
	char	ch;							// ch == ?
	str	*t;							// t == ?
	str	a;								// a.len == 0, a.data == "\0"
	str	b;								// b.len == 0, b.data == "\0"
	str	c( "test" );				// c.len == 4, c.data == "test\0"
	str	d( c );						// d.len == 4, d.data == "test\0"
	str	e( reinterpret_cast<const char *>(NULL) );					
                                 // e.len == 0, e.data == "\0"					ASSERT!
	size_t	i;								// i == ?

	i = a.length();					// i == 0
	i = c.length();					// i == 4

	const char *s1 = a.c_str();	// s1 == "\0"
	const char *s2 = c.c_str();	// s2 == "test\0"

	t = new str();						// t->len == 0, t->data == "\0"
	delete t;							// t == ?

	b = "test";							// b.len == 4, b.data == "test\0"
	t = new str( "test" );			// t->len == 4, t->data == "test\0"
	delete t;							// t == ?

	a = c;								// a.len == 4, a.data == "test\0"
//   a = "";
   a = NULL;							// a.len == 0, a.data == "\0"					ASSERT!
	a = c + d;							// a.len == 8, a.data == "testtest\0"
	a = c + "wow";						// a.len == 7, a.data == "testwow\0"
	a = c + reinterpret_cast<const char *>(NULL);
                                 // a.len == 4, a.data == "test\0"			ASSERT!
	a = "this" + d;					// a.len == 8, a.data == "thistest\0"
	a = reinterpret_cast<const char *>(NULL) + d;
                                 // a.len == 4, a.data == "test\0"			ASSERT!
	a += c;								// a.len == 8, a.data == "testtest\0"
	a += "wow";							// a.len == 11, a.data == "testtestwow\0"
	a += reinterpret_cast<const char *>(NULL);
                                 // a.len == 11, a.data == "testtestwow\0"	ASSERT!

	a = "test";							// a.len == 4, a.data == "test\0"
	ch = a[ 0 ];						// ch == 't'
	ch = a[ -1 ];						// ch == 0											ASSERT!
	ch = a[ 1000 ];					// ch == 0											ASSERT!
	ch = a[ 0 ];						// ch == 't'
	ch = a[ 1 ];						// ch == 'e'
	ch = a[ 2 ];						// ch == 's'
	ch = a[ 3 ];						// ch == 't'
	ch = a[ 4 ];						// ch == '\0'										ASSERT!
	ch = a[ 5 ];						// ch == '\0'										ASSERT!

	a[ 1 ] = 'b';						// a.len == 4, a.data == "tbst\0"
	a[ -1 ] = 'b';						// a.len == 4, a.data == "tbst\0"			ASSERT!
	a[ 0 ] = '0';						// a.len == 4, a.data == "0bst\0"
	a[ 1 ] = '1';						// a.len == 4, a.data == "01st\0"
	a[ 2 ] = '2';						// a.len == 4, a.data == "012t\0"
	a[ 3 ] = '3';						// a.len == 4, a.data == "0123\0"
	a[ 4 ] = '4';						// a.len == 4, a.data == "0123\0"			ASSERT!
	a[ 5 ] = '5';						// a.len == 4, a.data == "0123\0"			ASSERT!
	a[ 7 ] = '7';						// a.len == 4, a.data == "0123\0"			ASSERT!

	a = "test";							// a.len == 4, a.data == "test\0"
	b = "no";							// b.len == 2, b.data == "no\0"

	i = ( a == b );					// i == 0
	i = ( a == c );					// i == 1

	i = ( a == "blow" );				// i == 0
	i = ( a == "test" );				// i == 1
	i = ( a == NULL );				// i == 0											ASSERT!

	i = ( "test" == b );				// i == 0
	i = ( "test" == a );				// i == 1
	i = ( NULL == a );				// i == 0											ASSERT!

	i = ( a != b );					// i == 1
	i = ( a != c );					// i == 0

	i = ( a != "blow" );				// i == 1
	i = ( a != "test" );				// i == 0
	i = ( a != NULL );				// i == 1											ASSERT!

	i = ( "test" != b );				// i == 1
	i = ( "test" != a );				// i == 0
	i = ( NULL != a );				// i == 1											ASSERT!

   a = "test";                   // a.data == "test"
   b = a;                        // b.data == "test"

   a = "not";                   // a.data == "not", b.data == "test"

   a = b;                        // a.data == b.data == "test"

   a += b;                       // a.data == "testtest", b.data = "test"

   a = b;

   a[1] = '1';                   // a.data = "t1st", b.data = "test"
	}

#ifdef _WIN32
#pragma warning(default : 4189)		// local variable is initialized but not referenced
#pragma warning(disable : 4514)     // unreferenced inline function has been removed
#endif

char str::operator[](intptr_t index) const
{
	assert(m_data);

	if (!m_data)
		return 0;

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert((index >= 0) && (index < (int)m_data->len));

	// In release mode, give them a null character
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ((index < 0) || (index >= (int)m_data->len))
	{
		return 0;
	}

	return m_data->data[index];
}

size_t str::length(void) const
{
	return (m_data != NULL) ? m_data->len : 0;
}

str::~str()
{
	if (m_data)
	{
		m_data->DelRef();
		m_data = NULL;
	}
}

str::str() : m_data(NULL)
{

}

str::str
(
	const char *text
) : m_data(NULL)

{
	size_t len;

	assert(text);
	if (*text)
	{
		len = strlen(text);

		if (len)
		{
			EnsureAlloced(len + 1);
			strcpy(m_data->data, text);
			m_data->len = len;
		}
	}
}

str::str
(
	const str& text
) : m_data(NULL)

{
	if (text.m_data)
		text.m_data->AddRef();

	if (m_data)
		m_data->DelRef();

	m_data = text.m_data;
}

str::str
(
	const str text,
	size_t start,
	size_t end
) : m_data(NULL)

{
	size_t i;
	size_t len;

	if (end > text.length())
	{
		end = text.length();
	}

	if (start > text.length())
	{
		start = text.length();
	}

	len = end - start;
	if (len < 0)
	{
		len = 0;
	}

	EnsureAlloced(len + 1);

	for (i = 0; i < len; i++)
	{
		m_data->data[i] = text[start + i];
	}

	m_data->data[len] = 0;
	m_data->len = len;
}

str::str
(
	const char ch
) : m_data(NULL)

{
	EnsureAlloced(2);

	m_data->data[0] = ch;
	m_data->data[1] = 0;
	m_data->len = 1;
}

str::str
(
	const float num
) : m_data(NULL)

{
	char text[32];
	size_t len;

	sprintf(text, "%.3f", num);
	len = strlen(text);
	EnsureAlloced(len + 1);
	strcpy(m_data->data, text);
	m_data->len = len;
}

str::str
(
	const int num
) : m_data(NULL)

{
	char text[32];
	size_t len;

	sprintf(text, "%d", num);
	len = strlen(text);
	EnsureAlloced(len + 1);
	strcpy(m_data->data, text);
	m_data->len = len;
}

str::str
(
	const unsigned num
) : m_data(NULL)

{
	char text[32];
	size_t len;

	sprintf(text, "%u", num);
	len = strlen(text);
	EnsureAlloced(len + 1);
	strcpy(m_data->data, text);
	m_data->len = len;
}

const char *str::c_str(void) const
{
	if (m_data)
	{
		return m_data->data;
	}
	else
	{
		return "";
	}
}

void str::append
(
	const char *text
)

{
	size_t len;

	assert(text);

	if (text)
	{
		len = length();
		len += strlen(text);
		EnsureAlloced(len + 1);

		strcat(m_data->data, text);
		m_data->len = len;
	}
}

void str::append
(
	const str& text
)

{
	size_t len;

	len = length();
	len += text.length();
	EnsureAlloced(len + 1);

	strcat(m_data->data, text.c_str());
	m_data->len = len;
}


char& str::operator[]
(
	intptr_t index
	)

{
	// Used for result for invalid indices
	static char dummy = 0;
	assert(m_data);

	// We don't know if they'll write to it or not
	// if it's not a const object
	EnsureDataWritable();

	if (!m_data)
		return dummy;

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert((index >= 0) && (index < (int)m_data->len));

	// In release mode, let them change a safe variable
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ((index < 0) || (index >= (int)m_data->len))
	{
		return dummy;
	}

	return m_data->data[index];
}

void str::operator=
	(
		const str& text
		)

{
	// adding the reference before deleting our current reference prevents
	// us from deleting our string if we are copying from ourself
	if (text.m_data)
		text.m_data->AddRef();

	if (m_data)
		m_data->DelRef();

	m_data = text.m_data;
}

void str::operator=
	(
		const char *text
		)

{
	size_t len;

	assert(text);

	if (m_data)
	{
		if (text == m_data->data)
			return; // Copying same thing.  Punt.

		m_data->DelRef();
		m_data = NULL;
	}

	if (*text)
	{
		len = strlen(text);

		//FILE *pFile;
		//pFile = fopen("myfile.txt", "w");
		m_data = new strdata;
		m_data->len = len;
		m_data->alloced = len + 1;
		m_data->data = (char*)MemoryMalloc(sizeof(char) * (len + 1));//new char[len + 1];
		//fprintf(pFile, "m_data %p\n", (void*)(m_data));
		//fprintf(pFile, "m_data->data %p\n", (void*)(m_data->data));
		//fclose(pFile);
		strcpy(m_data->data, text);
	}
}

str operator+
	(
		const str& a,
		const str& b
		)

{
	str result(a);

	result.append(b);

	return result;
}

str operator+
	(
		const str& a,
		const char *b
		)

{
	str result(a);

	result.append(b);

	return result;
}

str operator+
	(
		const char *a,
		const str& b
		)

{
	str result(a);

	result.append(b);

	return result;
}

str operator+
	(
		const str& a,
		const bool b
		)

{
	str result(a);

	result.append(b ? "true" : "false");

	return result;
}

str operator+
	(
		const str& a,
		const char b
		)

{
	char text[2];

	text[0] = b;
	text[1] = 0;

	return a + text;
}

str& str::operator+=
	(
		const str& a
		)

{
	append(a);
	return *this;
}

str& str::operator+=
	(
		const char *a
		)

{
	append(a);
	return *this;
}

str& str::operator+=
	(
		const char a
		)

{
	char text[2];

	text[0] = a;
	text[1] = 0;
	append(text);

	return *this;
}

str& str::operator+=
	(
		const bool a
		)

{
	append(a ? "true" : "false");
	return *this;
}

bool operator==
	(
		const str& a,
		const str& b
		)

{
	return (!strcmp(a.c_str(), b.c_str()));
}

bool operator==
	(
		const str& a,
		const char *b
		)

{
	assert(b);
	if (!b)
	{
		return false;
	}
	return (!strcmp(a.c_str(), b));
}

bool operator==
	(
		const char *a,
		const str& b
		)

{
	assert(a);
	if (!a)
	{
		return false;
	}
	return (!strcmp(a, b.c_str()));
}

bool operator!=
	(
		const str& a,
		const str& b
		)

{
	return !(a == b);
}

bool operator!=
	(
		const str& a,
		const char *b
		)

{
	return !(a == b);
}

bool operator!=
	(
		const char *a,
		const str& b
		)

{
	return !(a == b);
}

int str::icmpn
(
	const char *text,
	size_t n
) const

{
	assert(m_data);
	assert(text);

	return str::icmpn(m_data->data, text, n);
}

int str::icmpn
(
	const str& text,
	size_t n
) const

{
	assert(m_data);
	assert(text.m_data);

	return str::icmpn(m_data->data, text.m_data->data, n);
}

int str::icmp
(
	const char *text
) const

{
	assert(m_data);
	assert(text);

	return str::icmp(m_data->data, text);
}

int str::icmp
(
	const str& text
) const

{
	assert(c_str());
	assert(text.c_str());

	return str::icmp(c_str(), text.c_str());
}

int str::cmpn
(
	const char *text,
	size_t n
) const

{
	assert(c_str());
	assert(text);

	return str::cmpn(c_str(), text, n);
}

int str::cmpn
(
	const str& text,
	size_t n
) const

{
	assert(c_str());
	assert(text.c_str());

	return str::cmpn(c_str(), text.c_str(), n);
}

void str::tolower
(
	void
)

{
	assert(m_data);

	EnsureDataWritable();

	str::tolower(m_data->data);
}

void str::toupper
(
	void
)

{
	assert(m_data);

	EnsureDataWritable();

	str::toupper(m_data->data);
}

bool str::isNumeric
(
	void
) const

{
	assert(m_data);
	return str::isNumeric(m_data->data);
}

str::operator const char *
	(
		void
		) const

{
	return c_str();
}
