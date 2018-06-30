// 2018-06-30T16:08+08:00
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define ADC_BITS (24)
#define TO_mv(data) ((data) * 5.324681599934896e-05)


// Data in AD_buffer is 24-bit signed integer.
char AD_buffer[] =
{
      0,  75,  50,
      0,  74, 142,
    255, 226, 218,
      6, 160, 254,
    253, 208,  83,
    255, 226, 218,
    255, 242, 130,
};


#define SAMPLES  (sizeof(AD_buffer) / (ADC_BITS / 8))


union AD_SAMPLE_T
{
#ifdef __cplusplus
    AD_SAMPLE_T()
    {
        value = 0;
    }
#endif

    char    buffer[4];
    int32_t value;
};

typedef union AD_SAMPLE_T AD_SAMPLE;


void unpack_v0()
{
    int i;

    puts("------------------------------ unpack_v0 ------------------------------");

    for (i = 0; i < SAMPLES; ++i)
    {
        const char *channel = AD_buffer + i * (ADC_BITS / 8);
        unsigned char temp_buffer[4] = { 0 };
        unsigned char channel_buffer[4] = { 0 };
        int32_t data;

        memcpy(temp_buffer, channel, (ADC_BITS / 8));

        // Before unpacking...
        printf("%d,%d,%d,%d -> ", temp_buffer[0], temp_buffer[1], temp_buffer[2], temp_buffer[3]);

        channel_buffer[1] = temp_buffer[2];
        channel_buffer[2] = temp_buffer[1];
        channel_buffer[3] = temp_buffer[0];

        data = *(int32_t *)channel_buffer / 256;

        // After unpacking...
        *(int32_t *)temp_buffer = data;
        printf("%d,%d,%d,%d (%.4f)\n",
               temp_buffer[0], temp_buffer[1], temp_buffer[2], temp_buffer[3],
               TO_mv(data));
    }
}


void unpack_v1()
{
    int i;

    puts("------------------------------ unpack_v1 ------------------------------");

    for (i = 0; i < SAMPLES; ++i)
    {
        const char *channel = AD_buffer + i * (ADC_BITS / 8);
        unsigned char temp_buffer[4] = { 0 };
        unsigned char channel_buffer[4] = { 0 };
        int32_t data;

        memcpy(temp_buffer, channel, (ADC_BITS / 8));

        // Before unpacking...
        printf("%d,%d,%d,%d -> ", temp_buffer[0], temp_buffer[1], temp_buffer[2], temp_buffer[3]);

        channel_buffer[0] = temp_buffer[2];
        channel_buffer[1] = temp_buffer[1];
        channel_buffer[2] = temp_buffer[0];

        data = *(int32_t *)channel_buffer;

        // After unpacking...
        *(int32_t *)temp_buffer = data;
        printf("%d,%d,%d,%d (%.4f)\n",
               temp_buffer[0], temp_buffer[1], temp_buffer[2], temp_buffer[3],
               TO_mv(data));
    }
}


void unpack_v2()
{
    int i;

    puts("------------------------------ unpack_v2 ------------------------------");

    for (i = 0; i < SAMPLES; ++i)
    {
        const unsigned char *channel = (unsigned char *)AD_buffer + i * (ADC_BITS / 8);
        AD_SAMPLE ad24;
        ad24.value = 0;

        unsigned char temp_buffer[4] = { 0 };
        int32_t data;

        // Before unpacking...
        printf("%d,%d,%d,%d -> ", channel[0], channel[1], channel[2], 0);

        ad24.buffer[2] = channel[0];
        ad24.buffer[1] = channel[1];
        ad24.buffer[0] = channel[2];

        data = ad24.value;

        // After unpacking...
        *(int32_t *)temp_buffer = data;
        printf("%d,%d,%d,%d (%.4f)\n",
               temp_buffer[0], temp_buffer[1], temp_buffer[2], temp_buffer[3],
               TO_mv(data));
    }
}


int main()
{
    unpack_v0();
    unpack_v1();
    unpack_v2();

    return 0;
}


// References:
// https://stackoverflow.com/questions/321351/initializing-a-union-with-a-non-trivial-constructor
