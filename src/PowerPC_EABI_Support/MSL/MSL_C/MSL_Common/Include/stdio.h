#ifndef MSL_STDIO_H_
#define MSL_STDIO_H_

#include "char_io.h" // IWYU pragma: export
#include "file_io.h" // IWYU pragma: export
#include "printf.h" // IWYU pragma: export
#include "extras.h" // IWYU pragma: export

#define stdin (&__files._stdin)
#define stdout (&__files._stdout)
#define stderr (&__files._stderr)

#endif
