# Wokwi Study - Arduino Uno 练习项目

使用 **VSCode + PlatformIO + Wokwi** 进行 Arduino Uno 模拟练习。

## 项目结构

```
wokwi_study/
├── platformio.ini      # PlatformIO 配置（Uno）
├── src/
│   └── main.cpp        # 主程序（当前是 Blink）
├── diagram.json        # Wokwi 电路图
├── wokwi.toml          # Wokwi 仿真配置
└── README.md
```

## 使用方法

1. 用 VSCode 打开本项目文件夹
2. 确保已安装扩展：
   - PlatformIO IDE
   - Wokwi for VS Code
3. 登录 Wokwi 账号（扩展会提示）
4. 按 `Ctrl+Alt+B` 或点击 PlatformIO 的 Build 按钮编译
5. 点击 Wokwi 扩展的 **Start Simulator** 按钮启动仿真

## 当前示例

- 板载 LED（pin 9,10,11） + 外接红灯,绿灯，黄灯 + 220Ω 电阻
- 实现红绿灯
