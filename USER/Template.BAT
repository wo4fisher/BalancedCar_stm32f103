SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Users\zhuwei\AppData\Local\Microsoft\WindowsApps;
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Template
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "..\obj\startup_stm32f10x_md._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\minibalance.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\delay.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\sys.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\led.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\timer.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\i2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\mpu6050.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\imu.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "..\OBJ\Minibalance.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "..\OBJ\Minibalance.axf" --i32combined --output "..\OBJ\Minibalance.hex"
