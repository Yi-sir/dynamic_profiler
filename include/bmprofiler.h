#ifndef BMPROFILER_H_
#define BMPROFILER_H_

#include <dlfcn.h>

#include <iostream>

#include "bmcv_api_ext.h"
#include "bmlib_runtime.h"
#include "log.h"

static const char* BMCV_LIBRARY_FILE_NAME =
    "/opt/sophon/libsophon-current/lib/libbmcv.so";
static const char* BMLIB_LIBRARY_FILE_NAME =
    "/opt/sophon/libsophon-current/lib/libbmlib.so";

// TODO:
// 把bmHandle里的void*改成vector，上面的filename改成一个char**
// 初始化时遍历所有的char*，全都打开并把句柄添加到vector
// 搜索时在所有的句柄里搜索
// 析构时释放所有句柄

class bmHandle {
 public:
  bmHandle() = delete;
  bmHandle(const std::string bmcvLibName, const std::string bmlibLibName) {
    if (bmcvLibName != "") {
      bmcvHandle = dlopen(bmcvLibName.c_str(), RTLD_NOW | RTLD_GLOBAL);
      if (bmcvHandle == nullptr) {
        std::cerr << "dlopen failed" << std::endl;
        log_error("dlopen failed [%s]", bmcvLibName.c_str());
        exit(-1);
      }
    }
    if (bmlibLibName != "") {
      bmlibHandle = dlopen(bmlibLibName.c_str(), RTLD_NOW | RTLD_GLOBAL);
      if (bmlibHandle == nullptr) {
        log_error("dlopen failed [%s]", bmlibLibName.c_str());
        exit(-1);
      }
    }
    log_info("load library [%s], [%s] successfully", bmcvLibName.c_str(),
             bmlibLibName.c_str());
  }
  ~bmHandle() {
    if (bmcvHandle) {
      dlclose(bmcvHandle);
    }
    if (bmlibHandle) {
      dlclose(bmlibHandle);
    }
  }

  void* getBmcvHandle() const { return bmcvHandle; }
  void* getBmlibHandle() const { return bmlibHandle; }

 private:
  void* bmcvHandle = nullptr;
  void* bmlibHandle = nullptr;
};

bmHandle wrapper(BMCV_LIBRARY_FILE_NAME, BMLIB_LIBRARY_FILE_NAME);

#endif