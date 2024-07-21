#ifndef BMPROFILER_H_
#define BMPROFILER_H_

#include <dlfcn.h>

#include <iostream>

#include "bmcv_api_ext.h"
#include "bmlib_runtime.h"
#include "log.h"

static const char* BMCV_LIBRARY_FILE_NAME =
    "/opt/sophon/libsophon-current/lib/libbmcv.so.0.7.3";
static const char* BMLIB_LIBRARY_FILE_NAME = "";

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