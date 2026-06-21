#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct our_driver_param {
        uint32_t param;
} our_driver_t;

void our_driver_custom_param(const struct device *dev, uint32_t param);

#ifdef __cplusplus
}
#endif

#endif /* OUR_DRIVER_H */
