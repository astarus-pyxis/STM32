#ifndef ERRORS_H
// Header guard to prevent multiple inclusions
#define ERRORS_H

typedef enum
{
    OK                  = 0,    // Cannot use enumerator 'SUCCESS', already used in the HAL
    ERROR_FROM_HAL      = 1,    // Cannot use enumerator 'HAL_ERROR', already used in the HAL
    INVALID_ARGUMENT    = 2,
    NULL_POINTER        = 3,

} error_t;

#endif  // ERRORS_H
