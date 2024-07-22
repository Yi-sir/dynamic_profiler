#ifndef BMPROFILER_H_
#define BMPROFILER_H_

#include <dlfcn.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "bmcv_api_ext.h"
#include "bmruntime_interface.h"
#include "log.h"

static const char* SHARED_OBJECT_FILES[] = {
    "/opt/sophon/libsophon-current/lib/libbmcv.so",
    "/opt/sophon/libsophon-current/lib/libbmlib.so",
    "/opt/sophon/libsophon-current/lib/libbmrt.so"};

using sharedObjectHandle = void*;
using functionPtr = void*;

class bmHandle {
 public:
  bmHandle() {
    for (auto& sharedObjectFile : SHARED_OBJECT_FILES) {
      sharedObjectHandle handle =
          dlopen(sharedObjectFile, RTLD_NOW | RTLD_GLOBAL);
      if (handle == nullptr) {
        log_error("dlopen failed [%s]", sharedObjectFile);
      } else {
        handles.push_back(handle);
      }
    }
  }

  ~bmHandle() {
    for (auto& handle : handles) {
      dlclose(handle);
    }
    summary();
  }

  functionPtr searchSymbol(const char* funcName) {
    functionPtr ptr = nullptr;
    for (auto& handle : handles) {
      ptr = dlsym(handle, funcName);
      if (ptr) return ptr;
    }
    log_error("search symbol failed, [%s]", funcName);
    return ptr;
  }

  void updateMap(const char* funcName, long timeCost) {
    timeCostMap[funcName].push_back(timeCost);
    return;
  }

  void summary() {
    log_info("====== SUMMARY START ======");
    for (auto& [k, v] : timeCostMap) {
      auto maxTime = *std::max_element(std::begin(v), std::end(v));
      auto minTime = *std::min_element(std::begin(v), std::end(v));
      auto sumTime = std::accumulate(std::begin(v), std::end(v), 0);
      auto avgTime = sumTime / (float)v.size();
      log_info(
          "Func: [%s], max time cost: [%d], min time cost: [%d], avg time "
          "cost: [%.2f]",
          k, maxTime, minTime, avgTime);
    }
    log_info("======= SUMMARY END =======");
  }

 private:
  std::vector<sharedObjectHandle> handles;
  std::map<const char*, std::vector<long>> timeCostMap;
};

bmHandle wrapper;

#endif