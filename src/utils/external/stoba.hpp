//  Credits: @cristeigabriel
//  https://github.com/cristeigabriel/compiletime-string-to-bytearray

#ifndef _STOBA_HPP
#define _STOBA_HPP

#include <iostream>
#include <memory>
#include <array>
#include <utility>
#include <string>

namespace stoba
{
	template <size_t N>
	struct ct_string
	{
		constexpr ct_string( const char *str )
		{
			for( auto i = 0u; i != N; ++i )
			{
				content[i] = str[i];
			}
		}

		constexpr operator char const *( ) const
		{
			return content;
		}

		constexpr auto get() const
		{
			return operator const char *( );
		}

		char content[N + 1]{};
	};

	template<size_t N>
	ct_string( char const ( & )[N] )->ct_string<N - 1>;

	constexpr size_t _str_length( const char *str )
	{
		return *str ? 1u + _str_length( str + 1u ) : 0u;
	}

	//	Returns the occurences of a wildcard in a string alongside with the string
	template <char wildcard, ct_string str>
	constexpr auto _grab_string_data()
	{
		auto count = 1u;

		for( auto i = 0u; i < _str_length( str.get() ); ++i )
		{
			if( str.get()[i] == wildcard )
			{
				++count;
			}
		}

		return std::make_pair( count, str.get() );
	}

	//	@sean :)
	template <typename T>
	constexpr int _char_to_int( const T &ch )
	{
		if( ch >= '0' && ch <= '9' )
			return ch - '0';

		if( ch >= 'A' && ch <= 'F' )
			return ch - 'A' + 10;

		return ch - 'a' + 10;
	};

	//	construct a base16 hex and emplace it at make_count
	//	change 16 to 256 if u want the result to be when:
	//	sig[0] == 0xa && sig[1] == 0xb = 0xa0b
	//	or leave as is for the scenario to return 0xab
	template <typename T, T F = 16>
	constexpr auto _concate_hex( const T &a, const T &b )
	{
		return T( F ) * a + b;
	}

	struct detail
	{
		constexpr static auto delimiting_wildcard = ' ';
		constexpr static auto skip_wildcard = '?';
		constexpr static auto hex_factor = 16;
	};

	template <class Detail>
	struct data
	{
		template <ct_string str>
		constexpr static auto get()
		{
			return _grab_string_data<Detail::delimiting_wildcard, str>();
		}
	};

	template <ct_string str>
	constexpr auto _generate_data()
	{
		return data<detail>::get<str>();
	}

	template <ct_string str>
	constexpr auto make()
	{
		constexpr auto result = _generate_data<str>();
		constexpr auto delimiter_count = result.first;
		constexpr auto sig = result.second;
		constexpr auto sig_length = _str_length( sig );

		static_assert( delimiter_count > 1, "delimiter count must be bigger than 1" );
		static_assert( sig_length > 0, "sig length must be bigger than 0" );

		//	resulting byte array, for delimiter_count skips we should have delimiter_count integers
		std::array<int, delimiter_count> ret{};

		//	list of skips that point to the position of the delimiter wildcard in skip
		std::array<size_t, delimiter_count> skips{};

		//	current skip
		auto skip_count = 0u;

		//	character count, traversed for skip
		auto skip_traversed_character_count = 0u;
		for( auto i = 0u; i < sig_length; ++i )
		{
			if( sig[i] == detail::delimiting_wildcard )
			{
				skips[skip_count] = skip_traversed_character_count;
				++skip_count;
			}

			++skip_traversed_character_count;
		}
		//	make count (we will supposedly have at least an instance in our return array)
		auto make_count = 1u;

		//	traverse signature
		for( auto i = 0u; i < sig_length; ++i )
		{
			if( i == 0u )
			{
				//	we don't care about this, and we don't want to use 0
				if( sig[0] == detail::skip_wildcard )
				{
					ret[0] = -1;
					continue;
				}

				ret[0] = _concate_hex<int, detail::hex_factor>( _char_to_int( sig[0] ), _char_to_int( sig[1] ) );
				continue;
			}

			//	make result by skip data
			for( const auto &skip : skips )
			{
				if( ( skip == i ) && skip < sig_length - 1u )
				{
					//	we don't care about this, and we don't want to use 0
					if( sig[i + 1] == detail::skip_wildcard )
					{
						ret[make_count] = -1;
						++make_count;
						continue;
					}

					ret[make_count] = _concate_hex<int, detail::hex_factor>( _char_to_int( sig[i + 1] ), _char_to_int( sig[i + 2] ) );
					++make_count;
				}
			}
		}

		return ret;
	}
}

#endif