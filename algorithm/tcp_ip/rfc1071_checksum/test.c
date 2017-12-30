#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "rfc1071_checksum.h"


typedef struct
{
    uint16_t sport;
    uint16_t dport;
    uint16_t len;
    uint16_t chksum;
} udp_segment_t;


uint16_t udp_segment_chksum(const udp_segment_t *segment)
{
    assert(segment != NULL);
    return ~(uint16_t)(segment->sport + segment->dport + segment->len);
}


udp_segment_t udp_segment_init(uint16_t sport, uint16_t dport, uint16_t len)
{
    udp_segment_t segment = { sport, dport, len };
    //segment.chksum = rfc1071_checksum(&segment, 6);
    segment.chksum = udp_segment_chksum(&segment);
    return segment;
}


bool is_udp_segment_modified(const udp_segment_t *segment)
{
    assert(segment != NULL);
    return ((uint16_t)(segment->sport + segment->dport + segment->len + segment->chksum) != 0xffff);
}


#define DUMP_UDP_SEGMENT(segment) printf("[sport:%04x][dport:%04x][len:%04x][chksum:%04x] Modified: %d.\n", segment.sport, segment.dport, segment.len, segment.chksum, is_udp_segment_modified(&segment))


int main()
{
    udp_segment_t segment = udp_segment_init(0, 0, 0);
    DUMP_UDP_SEGMENT(segment);

    segment = udp_segment_init(0x6660, 0x5555, 0x8f0c);
    DUMP_UDP_SEGMENT(segment);

    segment.len = 0;
    DUMP_UDP_SEGMENT(segment);

    return 0;
}
