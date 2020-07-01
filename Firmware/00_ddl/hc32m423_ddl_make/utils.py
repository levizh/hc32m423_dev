# coding=gb2312
import re
import datetime
import os

ErrorPatten = re.compile(r'errors:\s*([\w]+)')
WarningPatten = re.compile(r'warnings:\s*([\w]+)')

#driver
SrcPatten = re.compile(r'#define\s*DDL_(\w+)_ENABLE\s*\(DDL_ON\)')
#midware file
MidPatten = re.compile(r'#define\s*MW_(\w+)_ENABLE\s*\(MW_ON\)')
#midware c
MidCPatten = re.compile(r'#include\s*"([\w]+).[\w]+"\s*')
#usb_lib control
UsbLibPatten = re.compile(r'#define\s*USBLIB_(\w+)\s*\(DDL_ON\)')
#usb ctl_drv
UsbCtlPatten = re.compile(r'#define\s*CTL_DRV_(\w+)\s*\(DDL_ON\)')
#usb device class
UsbDevPatten = re.compile(r'#define\s*DEVICE_CLASS_(\w+)\s*\(DDL_ON\)')
#usb host class
UsbHostPatten = re.compile(r'#define\s*HOST_CLASS_(\w+)\s*\(DDL_ON\)')
#bsp
BspPatten = re.compile(r'#define\s*BSP_(\w+)\s*\(BSP_ON\)')
BspPatten1 = re.compile(r'#define\s*BSP_EV_HC32M423\s*\(BSP_(\w+)\)')
#Example name
Examplepatten = re.compile(r"_(\w+)_source")
def find_inc(file):
    m = []
    f1 = open(file)
    buff_out = f1.read()
    f1.close()
    m = SrcPatten.findall(buff_out)
    if 'EKEY' in m:
        m[m.index('EKEY')] = 'INTERRUPTS'
    if 'EXINT_NMI' in m:
        m[m.index('EXINT_NMI')] = 'INTERRUPTS'
    m = list(set(m))
    return m

#find midware
def find_mid(file):
    m = []
    f1 = open(file)
    buff_out = f1.read()
    f1.close()
    m = MidPatten.findall(buff_out)
    return m

#find example name list
def find_example(file):
    m = []
    f1 = open(file)
    buff_out = f1.read()
    f1.close()
    m = Examplepatten.findall(buff_out)
    return m

def find_c (list):
    m = []
    for l in list:
        if(l.split('.')[-1] == 'c'):
            m.append(l)
    return m

#find BSP
def find_bsp(file):
    m = []
    f1 = open(file)
    buff_out = f1.read()
    f1.close()
    n = BspPatten.findall(buff_out)
    m = BspPatten1.findall(buff_out)
    m += n
    '''if n != '':
        SpeacNum = 0
        str = '#define BSP_TCA9539_ENABLE' + 18 * '' + '(BSP_ON)'
        f1 = open(file, 'w')
        buff_out = re.sub('#define\s*BSP_TCA9539_ENABLE\s*\(BSP_OFF\)', str,  buff_out)
        buff_out = re.sub('#define\s*DDL_GPIO_ENABLE\s*\(DDL_OFF\)',    '#define DDL_GPIO_ENABLE                     (DDL_ON)', buff_out)
        buff_out = re.sub('#define\s*DDL_INTERRUPTS_ENABLE\s*\(DDL_OFF\)', '#define DDL_INTERRUPTS_ENABLE                   (DDL_ON)', buff_out)
        buff_out = re.sub('#define\s*DDL_KEYSCAN_ENABLE\s*\(DDL_OFF\)', '#define DDL_KEYSCAN_ENABLE                            (DDL_ON)', buff_out)
        buff_out = re.sub('#define\s*DDL_I2C_ENABLE\s*\(DDL_OFF\)',    '#define DDL_I2C_ENABLE                                (DDL_ON)', buff_out)
        buff_out = re.sub('#define\s*DDL_PWC_ENABLE\s*\(DDL_OFF\)',    '#define DDL_PWC_ENABLE                                (DDL_ON)', buff_out)
        f1.write(buff_out)
        f1.close()
        '''
    return m

###解析IAR的命令返回值， 得到错误和警告个数
def get_cmd_result(cmd_str):
    ### return error and warning counter
    errcnt = 0
    warncnt = 0

    m = ErrorPatten.search(cmd_str.decode())

    if m:
        g = m.group(1)
        g = g.lower()

        if('none' == g or '0' == g):
            pass
        else:
            errcnt += int(g)
    else:
        errcnt += 1
   
    m = WarningPatten.search(cmd_str.decode())

    if m:
        g = m.group(1)
        g = g.lower()

        if('none' == g or '0' == g):
            pass
        else:
            warncnt += int(g)
    else:
        warncnt += 1

    return errcnt, warncnt


###解析Keil的命令返回值， 得到错误和警告个数
KeilErrPatten = re.compile(r'(\d+) Error')
KeilWarnPatten = re.compile(r'(\d+) Warning')

def get_keil_result(cmd_str):
    ### return error and warning counter
    errcnt = 0
    warncnt = 0

    m = KeilErrPatten.search(cmd_str)

    if m:
        g = m.group(1)
        g = g.lower()

        if('none' == g or '0' == g):
            pass
        else:
            errcnt += int(g)
    else:
        errcnt += 1
   
    m = KeilWarnPatten.search(cmd_str)

    if m:
        g = m.group(1)
        g = g.lower()

        if('none' == g or '0' == g):
            pass
        else:
            warncnt += int(g)
    else:
        warncnt += 1

    return errcnt, warncnt



def ToDOSPath(str):
    return '"' + str + '"'


def writeLog(filepath, strlog):

    now = datetime.datetime.now()
    TimeStr = now.strftime("%Y-%m-%d %H:%M:%S")
    TimeStr += os.linesep

    if ( not os.path.exists(filepath)) and (''!=filepath) :
        os.makedirs(filepath)

    if ''!= filepath:
        filename = filepath+os.sep + 'log.log'
    else:
        filename = 'main.log'

    f = open(filename,'ab')
    f.write(TimeStr)

    lines = strlog.split(os.linesep)

    for l in lines:
        l = "%24s%s"  %(' ', l)
        l += os.linesep
        f.write(l)
    
    f.write(os.linesep)
    f.close()
    