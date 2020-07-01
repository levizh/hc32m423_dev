
del *.h
del *.svd
del *.sfr
python csvtool.exe
rem del *.pyc

"%cd%"\SVDConv.exe HDSC_HC32M423.svd --generate=sfr > log.txt

rem copy headfile to ddl\common
copy "%cd%"\HC32M423.h "%cd%"\..\00_ddl\hc32m423_ddl\mcu\common

rem copy SVD to ddl\iar
copy "%cd%"\HDSC_HC32M423.svd "%cd%"\..\00_ddl\hc32m423_ddl\mcu\EWARM

rem copy SVD to ddl\gcc
copy "%cd%"\HDSC_HC32M423.svd "%cd%"\..\00_ddl\hc32m423_ddl\mcu\GCC\SVD

rem copy SFR to ddl\mdk
copy "%cd%"\HDSC_HC32M423.SFR "%cd%"\..\00_ddl\hc32m423_ddl\mcu\MDK

rem copy svd to ide\iar
copy "%cd%"\HDSC_HC32F4A0SIHB.svd "%cd%"\..\02_ide\IAR_IDE\config\debugger\HDSC\HC32F4A0SIHB.svd
copy "%cd%"\HDSC_HC32F4A0SITB.svd "%cd%"\..\02_ide\IAR_IDE\config\debugger\HDSC\HC32F4A0SITB.svd
copy "%cd%"\HDSC_HC32F4A0RITB.svd "%cd%"\..\02_ide\IAR_IDE\config\debugger\HDSC\HC32F4A0RITB.svd
copy "%cd%"\HDSC_HC32F4A0PITB.svd "%cd%"\..\02_ide\IAR_IDE\config\debugger\HDSC\HC32F4A0PITB.svd

rem copy SFR to ide\mdk
copy "%cd%"\HDSC_HC32F4A0.sfr "%cd%"\..\02_ide\MDK_IDE\files\SVD\HC32F4A0.sfr
copy "%cd%"\HDSC_HC32F4A0SIHB.sfr "%cd%"\..\02_ide\MDK_IDE\files\SVD\HC32F4A0SIHB.sfr
copy "%cd%"\HDSC_HC32F4A0SITB.sfr "%cd%"\..\02_ide\MDK_IDE\files\SVD\HC32F4A0SITB.sfr
copy "%cd%"\HDSC_HC32F4A0RITB.sfr "%cd%"\..\02_ide\MDK_IDE\files\SVD\HC32F4A0RITB.sfr
copy "%cd%"\HDSC_HC32F4A0PITB.sfr "%cd%"\..\02_ide\MDK_IDE\files\SVD\HC32F4A0PITB.sfr

rem copy .h to ide\mdk
copy "%cd%"\HC32F4A0.h "%cd%"\..\02_ide\MDK_IDE\files\Device\Include
copy "%cd%"\HC32F4A0SIHB.h "%cd%"\..\02_ide\MDK_IDE\files\Device\Include
copy "%cd%"\HC32F4A0SITB.h "%cd%"\..\02_ide\MDK_IDE\files\Device\Include
copy "%cd%"\HC32F4A0RITB.h "%cd%"\..\02_ide\MDK_IDE\files\Device\Include
copy "%cd%"\HC32F4A0PITB.h "%cd%"\..\02_ide\MDK_IDE\files\Device\Include

rem copy .h to ide/cmsis
copy "%cd%"\HC32F4A0.h "%cd%"\..\02_ide\CMSIS_PACK\files\Device\Include
copy "%cd%"\HC32F4A0SIHB.h "%cd%"\..\02_ide\CMSIS_PACK\files\Device\Include
copy "%cd%"\HC32F4A0SITB.h "%cd%"\..\02_ide\CMSIS_PACK\files\Device\Include
copy "%cd%"\HC32F4A0RITB.h "%cd%"\..\02_ide\CMSIS_PACK\files\Device\Include
copy "%cd%"\HC32F4A0PITB.h "%cd%"\..\02_ide\CMSIS_PACK\files\Device\Include

rem copy SFR/SVD to ide\cmsis
copy "%cd%"\HDSC_HC32F4A0.sfr "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0.sfr
copy "%cd%"\HDSC_HC32F4A0SIHB.sfr "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0SIHB.sfr
copy "%cd%"\HDSC_HC32F4A0SITB.sfr "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0SITB.sfr
copy "%cd%"\HDSC_HC32F4A0RITB.sfr "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0RITB.sfr
copy "%cd%"\HDSC_HC32F4A0PITB.sfr "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0PITB.sfr

copy "%cd%"\HDSC_HC32F4A0SIHB.svd "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0SIHB.svd
copy "%cd%"\HDSC_HC32F4A0SIHB.svd "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0SITB.svd
copy "%cd%"\HDSC_HC32F4A0SIHB.svd "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0RITB.svd
copy "%cd%"\HDSC_HC32F4A0SIHB.svd "%cd%"\..\02_ide\CMSIS_PACK\files\SVD\HC32F4A0PITB.svd


