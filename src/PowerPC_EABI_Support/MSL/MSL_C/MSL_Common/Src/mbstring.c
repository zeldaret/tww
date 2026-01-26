#include "mbstring.h"
#include "string.h"

static int is_utf8_complete(const char* s, size_t n)
{
	if (n == 0) { // must have more than zero characters
		return -1;
	}

	if (s[0] == 0x00) { // first char is 0
		return 0;
	}

	if ((s[0] & 0x80) == 0x00) {
		return (1);
	} else if ((s[0] & 0xe0) == 0xc0) {
		if (n >= 2) {
			if ((*(s + 1) & 0x80) == 0x80) {
				return 2;
			}
			return -1;
		}
		return -2;
	} else if ((s[0] & 0xf0) == 0xe0) {
		if (n >= 3) {
			if ((s[1] & 0x80) == 0x80) {
				if ((s[2] & 0x80) == 0x80) {
					return 3;
				}
			}
			return -1;
		} else if ((n == 2 && ((s[1] & 0x80) == 0x80)) || n == 1) {
			return -2;
		}
		return -1;
	} else {
		return (-1);
	}
}

int utf8_to_unicode(wchar_t* pwc, const char* s, size_t n) {
	/* Nonmatching */
}

int mbtowc(wchar_t* pwc, const char* s, size_t n) {
	return utf8_to_unicode(pwc, s, n);
}

static int unicode_to_UTF8(char* s, wchar_t wchar) {
	int number_of_bytes;
	wchar_t wide_char;
	char* target_ptr;
	char first_byte_mark[4] = { 0x00, 0x00, 0xc0, 0xe0 };

	if (!s)
		return (0);

	wide_char = wchar;
	if (wide_char < 0x0080)
		number_of_bytes = 1;
	else if (wide_char < 0x0800)
		number_of_bytes = 2;
	else
		number_of_bytes = 3;

	target_ptr = s + number_of_bytes;

	switch (number_of_bytes) {
	case 3:
		*--target_ptr = (wide_char & 0x003f) | 0x80;
		wide_char >>= 6;
	case 2:
		*--target_ptr = (wide_char & 0x003f) | 0x80;
		wide_char >>= 6;
	case 1:
		*--target_ptr = wide_char | first_byte_mark[number_of_bytes];
	}

	return number_of_bytes;
}

inline int wctomb(char* s, wchar_t wchar) { return (unicode_to_UTF8(s, wchar)); }

size_t wcstombs(char* s, const wchar_t* pwcs, size_t n) {
	int chars_written = 0;
	int result;
	char temp[3];
	wchar_t* source;

	if (!s || !pwcs)
		return (0);

	source = (wchar_t*)pwcs;
	while (chars_written <= n) {
		if (!*source) {
			*(s + chars_written) = '\0';
			break;
		} else {
			result = wctomb(temp, *source++);
			if ((chars_written + result) <= n) {
				strncpy(s + chars_written, temp, result);
				chars_written += result;
			} else
				break;
		}
	}

	return chars_written;
}
