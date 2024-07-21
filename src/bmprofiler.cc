#include "bmprofiler.h"

#include <chrono>

#define CALL_STUB(func, ret, ...)                                             \
  do {                                                                        \
    auto start_ = std::chrono::high_resolution_clock::now();                  \
    ret = func(__VA_ARGS__);                                                  \
    auto end_ = std::chrono::high_resolution_clock::now();                    \
    auto duration =                                                           \
        std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_); \
    log_info("function [%s] cost time: [%d] us", __func__, duration.count()); \
  } while (false)

// Define your stub below
bm_status_t bmcv_image_vpp_convert_padding(bm_handle_t handle, int output_num,
                                           bm_image input, bm_image* output,
                                           bmcv_padding_atrr_t* padding_attr,
                                           bmcv_rect_t* crop_rect,
                                           bmcv_resize_algorithm algorithm) {
  bm_status_t (*bmcvWrapper)(
      bm_handle_t handle, int output_num, bm_image input, bm_image* output,
      bmcv_padding_atrr_t* padding_attr, bmcv_rect_t* crop_rect,
      bmcv_resize_algorithm algorithm);
  bm_status_t ret;

  *(void**)(&bmcvWrapper) =
      dlsym(wrapper.getBmcvHandle(), "bmcv_image_vpp_convert_padding");

  CALL_STUB(bmcvWrapper, ret, handle, output_num, input, output, padding_attr,
            crop_rect, algorithm);
  return ret;
}
