
#define max(a, b) \
    ({ typeof (a) _a = (a); typeof (b) _b = (b); _a > _b ? _a : _b; })
#define min(a, b) \
    ({ typeof (a) _a = (a); typeof (b) _b = (b); _a < _b ? _a : _b; })
#define limit(a, min, max) \
    ({ typeof (a) _a = (a); typeof(min) _min = min; typeof(max) _max = max; \
    _a < _min ? _min : (_a > _max ? _max : _a); })

#define mul(a, b) \
    ({ typeof(a) __result; if (__builtin_mul_overflow(a, b, &__result)) \
    { error = ERROR_BAD_ARGUMENTS; __result = 0; } __result; })

#define add(a, b) \
    ({ typeof(a) __result; if (__builtin_add_overflow(a, b, &__result)) \
    { error = ERROR_BAD_ARGUMENTS; __result = 0; } __result; })

static inline
size_t max_size(uint8_t number, ...)
{
    size_t a, max;
    va_list ap;

    if (number == 0)
    {
        return SIZE_MAX;
    }

    va_start(ap, number);

    max = va_arg(ap, size_t);
    number -= 1;

    while (number != 0)
    {
        a = va_arg(ap, size_t);
        if (a < max)
            max = a;

        number -= 1;
    }

    va_end(ap);

    return max;
}

static inline
size_t min_size(uint8_t number, ...)
{
    size_t a, min;
    va_list ap;

    if (number == 0)
        return 0;

    va_start(ap, number);

    min = va_arg(ap, size_t);
    number -= 1;

    while (number != 0)
    {
        a = va_arg(ap, size_t);
        if (a < min)
            min = a;

        number -= 1;
    }

    va_end(ap);

    return min;
}
