# MEC202 - ESP32-S3 舵机接线说明

本项目当前测试代码位于 `main/main.ino`，用于测试两个舵机往复运动：

- `RDS3115MG`（信号脚：`GPIO4`）
- `DS3218`（信号脚：`GPIO5`）

## 1. 当前接线

### RDS3115MG
- 信号线 -> `ESP32-S3 GPIO4`
- 电源正极（红）-> 外部 `+5V`
- 电源负极（黑）-> 外部 `GND`

### DS3218
- 信号线 -> `ESP32-S3 GPIO5`
- 电源正极（红）-> 外部 `+5V`
- 电源负极（棕）-> 外部 `GND`

### 共地（必须）
- `ESP32-S3 GND` 必须连接到外部电源 `GND`
- 两个舵机 `GND` 与 `ESP32-S3 GND` 必须共地

## 2. 供电要求

- 舵机请使用外部电源，不要直接由开发板 `5V` 引脚供电
- 建议电源规格：`5V 4A` 及以上（建议 `5V 5A` 更稳）

## 3. 串口与运行现象

- 串口波特率：`115200`
- 烧录成功后串口应看到：
  - `Reciprocating test started.`
  - `RDS3115MG -> GPIO4, DS3218 -> GPIO5`
  - 循环打印 `RDS3115 sweep` 与 `DS3218 sweep`

## 4. 常见问题

- 若出现 `ERROR: ledcAttach failed on GPIOx`
  - 先确认代码中 `LEDC_BITS` 为 `14`（ESP32-S3 最大 14-bit）
  - 再确认板型选择为 `ESP32S3 Dev Module`
- 若舵机只抖一下或不动
  - 优先检查外部电源能力是否不足
  - 再检查是否正确共地
  - 最后检查信号线是否接到 `GPIO4/GPIO5`
