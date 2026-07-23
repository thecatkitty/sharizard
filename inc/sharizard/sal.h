#ifndef SHARIZARD_SAL_H
#define SHARIZARD_SAL_H

#ifdef _MSC_VER

#include <sal.h>

#else

#define _In_
#define _In_opt_
#define _In_z_

#define _Out_

#define _Success_(x)

#endif // _MSC_VER

#define shizerr _Success_(return >= 0) int

#endif // SHARIZARD_SAL_H
