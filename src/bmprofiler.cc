#include "bmprofiler.h"

#include <chrono>

#define CALL_STUB(func, ...)                                                  \
  do {                                                                        \
    auto start_ = std::chrono::high_resolution_clock::now();                  \
    auto ret = func(__VA_ARGS__);                                             \
    auto end_ = std::chrono::high_resolution_clock::now();                    \
    auto duration =                                                           \
        std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_); \
    log_info("function [%s] cost time: [%d] us", __func__, duration.count()); \
    wrapper.updateMap(__func__, duration.count());                            \
    return ret;                                                               \
  } while (false)

// TODO: 如何优化下面的逻辑？

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

  *(void**)(&bmcvWrapper) =
      wrapper.searchSymbol("bmcv_image_vpp_convert_padding");

  CALL_STUB(bmcvWrapper, handle, output_num, input, output, padding_attr,
            crop_rect, algorithm);
}
bool bmrt_launch_tensor_ex(void* p_bmrt, const char* net_name,
                           const bm_tensor_t input_tensors[], int input_num,
                           bm_tensor_t output_tensors[], int output_num,
                           bool user_mem, bool user_stmode) {
  bool (*bmrtWrapper)(void* p_bmrt, const char* net_name,
                      const bm_tensor_t input_tensors[], int input_num,
                      bm_tensor_t output_tensors[], int output_num,
                      bool user_mem, bool user_stmode);
  *(void**)(&bmrtWrapper) = wrapper.searchSymbol("bmrt_launch_tensor_ex");
  CALL_STUB(bmrtWrapper, p_bmrt, net_name, input_tensors, input_num,
            output_tensors, output_num, user_mem, user_stmode);
}