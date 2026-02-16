# 🎄 C语言简易动态圣诞树 (Christmas Console Animation)

这是一个基于 C 语言和 Windows API 制作的控制台简易动画程序。
<img width="578" height="394" alt="image" src="https://github.com/user-attachments/assets/056ccfac-8a03-44d1-9f20-4c2f28e87196" />

## ✨ 核心功能
- **动态雪花**：支持最多 1000 颗雪花。
- **流水灯**：圣诞树饰灯随帧率变换颜色。
- **动态 UI 面板**：按 TAB 键可实时查看当前雪花数量和刷新频率。
- **即时交互**：运行过程中可随时通过键盘调整画面逻辑。

## 🎮 交互方式
程序运行期间，可通过以下按键进行实时控制：

| 按键 | 功能说明 |
| :--- | :--- |
| **W** | **加快动画速度** (减少延迟) |
| **S** | **减慢动画速度** (增加延迟) |
| **A** | **减少雪花数量** |
| **D** | **增加雪花数量** |
| **TAB** | **显示/隐藏 状态信息面板** |
| **ESC** | **退出程序** |

## 🛠️ 自定义指南
如果你想修改圣诞下方的祝福语内容或颜色，请在代码中找到 `drawGreeting` 函数：
1. 定位到第 **35 行** 左右。
2. 修改 `greetings` 数组内的字符串内容。
3. 修改 `colors`  数组的颜色内容（BLACK, BLUE, GREEN, CYAN, RED,PURPL, BROWN , WHITE, YELLOW , BRIGHT_WHITE）。
4. 请注意保持字符串长度适中，以维持视觉上的居中效果。

## 🚀 运行环境
- **系统要求**：Windows 操作系统的控制台环境。
- **所需库文件**：`stdio.h`, `stdlib.h`, `windows.h`, `time.h`, `conio.h`。
- **推荐工具**：Dev-C++, Visual Studio (带 C/C++ 环境), 或 Code::Blocks。

---
**Merry Christmas!** 🎅❄️
