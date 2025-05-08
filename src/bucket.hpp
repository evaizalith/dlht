#ifndef EVA_DLHT_IMPL_BUCKET
#define EVA_DLHT_IMPL_BUCKET

#include <cstdint>

#define CACHE_LINE_SIZE 64 // Used to determine alignment of structs along the cache line

/* 
 * The following structs provide the most basic data structures for the DLHT.
 * They are specifically designed to be aligned along 64 byte cache lines for
 * maximal data transfer.
 */

// slot_t provides basic key-value stores
struct alignas(16) slot_t {
    uint64_t key;
    uint64_t value;
};

/* 
 * We make use of two 4-byte pointers for the links to allow for maximal data storage 
 * while retaining 64 byte cache alignment.
 *
 * Each primary bucket is stored in the bin array and links to up to 3 link buckets
 * stored in the link array, collectively storing up to 15 slots (240 bytes) of data
 * and all associated metadata (just 16 bytes), neatly fitting into 256 bytes.
 */
struct alignas(CACHE_LINE_SIZE) primary_bucket_t {
    uint64_t header;            // (2-bit bin state, 15 * 2-bit slot state, 32-bit version)
    uint32_t link_1, link_2;   // Links up to 3 link buckets (latter two are consecutive in link array)
    slot_t slots[3];
};

struct alignas(CACHE_LINE_SIZE) link_bucket_t {
    slot_t slots[4];
};

#endif
