
#ifndef BM_HEADER
#define BM_HEADER 1

struct bm_header
{
    uint8_t magic;
    uint8_t info;
} __attribute__((packed));

#define GET_ADDRESS_SIZE(header) (((header).info & 0x0C) >> 2)
#define GET_REGISTER_SIZE(header) ((header).info & 0x03)

const char *get_size_string(uint8_t a)
{
    switch (a)
    {
        case 0b00: return "8bit";
        case 0b01: return "16bit";
        case 0b10: return "32bit";
        case 0b11: return "64bit";
        default: return "unknown";
    }
}

#endif // BM_HEADER
