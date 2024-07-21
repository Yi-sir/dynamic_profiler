# 动态插桩


本仓库是一个动态插桩的示例

## 使用方法

### 编译

```bash
cmake ..
make -j
```

### 使用

假定 `file` 是将要统计性能的程序，其运行方式为
```bash
./file arg1 arg2
```

将命令修改为
```bash
LD_PRELOAD="./libprofiler.so" ./file arg1 arg2
```

可以看到，程序的输出中出现了
```text
function [bmcv_image_vpp_convert_padding] cost time: [490] us
```

这样的打印。


## 说明

> 动态插桩只有当显式将此so设置到环境变量时才会生效。如果未设置，本so将不参与程序运行

> python程序使用方法与C++相同，设置`LD_PRELOAD`即可