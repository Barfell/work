SET PATH=D:\Program Files\mdk\ARM\ARMCC\bin\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\ATMEL Corporation\AT91-ISP v1.13\Library\;C:\Program Files (x86)\ATMEL Corporation\AT91-ISP v1.13\sam-ba 2.9
SET CPU_TYPE=STM32F407VG
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=SCT
SET CPU_CLOCK=0x00B71B00
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\freqmeasurement.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\temperature.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\485.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\misc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_adc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_crc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_dma.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_exti.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_flash.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_fsmc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_gpio.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_iwdg.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_pwr.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_rcc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_rtc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_spi.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_syscfg.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_tim.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_usart.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_wwdg.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_adc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_init.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_io_control.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_rtc.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_sst25vf064.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_usart.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\bsp_flash.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f4xx_it.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmAsm" --Via ".\startup_stm32f40xx._ia"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\system_stm32f4xx.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\tools.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\main.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\dtu.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\protocol.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\serial.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\testdtu.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\flash.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmCC" --Via ".\kernal.__i"
"D:\Program Files\mdk\ARM\ARMCC\bin\ArmLink" --Via ".\project.lnp"
"D:\Program Files\mdk\ARM\ARMCC\bin\fromelf.exe" ".\project.axf" --i32combined --output ".\project.hex"
D:\Program Files\mdk\ARM\ARMCC\bin\fromelf.exe --bin --output .\bin\123.bin .\project.axf
